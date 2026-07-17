# Integration Guide

## 1. Introduction

This guide explains how to integrate the Timer IP into a VSDSquadron RISC-V System-on-Chip (SoC). The Timer IP is designed as a memory-mapped peripheral and can be incorporated into the existing SoC architecture with minimal RTL modifications.

The integration process involves adding the Timer IP RTL module, assigning it a memory-mapped address range, connecting it to the system bus, updating the software register definitions, and verifying functionality using the provided example application.

---

## 2. Prerequisites

Before integrating the Timer IP, ensure the following requirements are met:

- VSDSquadron RISC-V SoC source code
- VSDSquadron FPGA Mini Board
- Verilog HDL development environment
- Icarus Verilog (for simulation)
- GTKWave (for waveform analysis)
- RISC-V GCC toolchain
- FPGA synthesis and programming tools

---

## 3. Required Files

The following files are required for Timer IP integration:

| File | Description |
|------|-------------|
| `rtl/timer_ip.v` | Timer IP RTL implementation |
| `software/io.h` | Memory-mapped register definitions |
| `software/timer_test.c` | Example software demonstrating Timer IP operation |

---

## 4. Hardware Integration

The Timer IP is integrated into the VSDSquadron RISC-V SoC as a memory-mapped peripheral connected to the processor's I/O bus. It communicates with the processor using the standard memory-mapped interface consisting of address, write data, read data, write enable, clock, and reset signals.

### Integration Signals

| Signal | Direction | Description |
|---------|-----------|-------------|
| `clk` | Input | System clock |
| `reset` | Input | System reset |
| `we` | Input | Register write enable |
| `addr[3:0]` | Input | Register address |
| `wdata[31:0]` | Input | Write data bus |
| `rdata[31:0]` | Output | Read data bus |
| `timeout` | Output | Timer timeout indication |

The Timer IP does not require any dedicated FPGA I/O pins. All communication occurs internally through the SoC bus, making integration straightforward and independent of external hardware connections.

---

## 5. Memory Map Integration

The Timer IP is assigned a dedicated address region within the VSDSquadron RISC-V SoC memory map.

### Base Address

| Peripheral | Base Address |
|------------|--------------|
| Timer IP | `0x400040` |

### Register Offsets

| Register | Offset |
|----------|---------|
| CTRL | `0x00` |
| LOAD | `0x04` |
| VALUE | `0x08` |
| STATUS | `0x0C` |

Software accesses the Timer IP using standard memory read and write operations through these addresses.

The address decoding logic in the SoC should ensure that accesses to this address range are routed to the Timer IP.

---

## 6. RTL Integration

The Timer IP is integrated into the VSDSquadron RISC-V SoC as a memory-mapped peripheral. Integration requires a few modifications to the existing SoC RTL. The following steps describe the complete integration process.


### Step 1: Add the Timer IP RTL File

Add the `timer_ip.v` source file to your FPGA project so that it is compiled together with the remaining SoC modules.


### Step 2: Allocate a Memory-Mapped I/O Address

Assign a dedicated I/O bit for the Timer IP in the memory-mapped I/O space.

```verilog
localparam IO_TIMER_bit = 4;
```

This I/O bit is used by the address decoder to identify accesses intended for the Timer IP.


### Step 3: Declare Internal Signals

Declare the internal signals required for communication between the SoC and the Timer IP.

```verilog
wire [31:0] timer_rdata;
wire timer_timeout;
wire timer_we;
```

These signals are used to transfer read data, generate the write enable signal, and expose the timer timeout output.


### Step 4: Generate the Timer Write Enable Signal

Create a write enable signal that becomes active whenever the processor performs a write operation to the Timer IP address space.

```verilog
assign timer_we =
    isIO &
    mem_wstrb &
    mem_wordaddr[IO_TIMER_bit];
```

This logic ensures that write operations are forwarded only to the Timer IP when its memory-mapped address is selected.


### Step 5: Instantiate the Timer IP

Instantiate the Timer IP and connect it to the system clock, reset, memory-mapped bus, and control signals.

```verilog
timer_ip timer(
    .clk(clk),
    .reset(!resetn),
    .we(timer_we),
    .addr(mem_addr[3:0]),
    .wdata(mem_wdata),
    .rdata(timer_rdata),
    .timeout(timer_timeout)
);
```

The Timer IP receives register addresses and write data from the processor while returning register data through the `timer_rdata` signal. The `timeout` output is available for future extensions such as interrupt generation or event signaling.


### Step 6: Connect the Timer Read Data

Update the SoC read-data multiplexer so that read operations targeting the Timer IP return the appropriate register contents.

```verilog
wire [31:0] IO_rdata =
       mem_wordaddr[IO_UART_CNTL_bit] ? {22'b0,!uart_ready,9'b0} :
       mem_wordaddr[IO_GPIO_bit]      ? gpio_rdata :
       mem_wordaddr[IO_TIMER_bit]     ? timer_rdata :
                                        32'b0;
```

This modification routes the Timer IP read data to the processor whenever the Timer IP address space is accessed.

---

### RTL Integration Flow

```text
                CPU
                 │
         Memory Bus
                 │
        Address Decoder
                 │
        timer_we generated
                 │
        +----------------+
        |   Timer IP     |
        +----------------+
          │          │
      timer_rdata timeout
          │
      IO Read Mux
          │
         CPU
```

After completing these modifications, the Timer IP becomes a fully functional memory-mapped peripheral within the VSDSquadron RISC-V SoC. Software can access the timer registers using standard load and store instructions without requiring any changes to the processor core.

---

## 7. Software Integration

Once the Timer IP has been integrated into the hardware, software can access the timer through its memory-mapped registers. The provided `io.h` file contains register definitions that simplify register access using standard C code.

### Register Definitions

```c
#define TIMER_CTRL   (*(volatile uint32_t*)(IO_BASE + IO_TIMER + 0x0))
#define TIMER_LOAD   (*(volatile uint32_t*)(IO_BASE + IO_TIMER + 0x4))
#define TIMER_VALUE  (*(volatile uint32_t*)(IO_BASE + IO_TIMER + 0x8))
#define TIMER_STATUS (*(volatile uint32_t*)(IO_BASE + IO_TIMER + 0xC))
```

These macros allow software to read from and write to the Timer IP registers using normal memory accesses.


### Programming Sequence

A typical software sequence for operating the Timer IP is shown below:

1. Write the desired countdown value to the **LOAD** register.
2. Configure the **CTRL** register by selecting the operating mode and enabling the timer.
3. Optionally configure the prescaler if longer timing intervals are required.
4. Poll the **STATUS** register until the timeout flag is asserted.
5. Clear the timeout flag by writing a `1` to the STATUS register.


### Example Firmware

An example application (`timer_test.c`) is provided in the `software/` directory. The program demonstrates:

- One-Shot mode operation
- Periodic mode operation
- Programmable prescaler functionality
- Register read/write verification

The example firmware can be used directly to validate successful Timer IP integration on the VSDSquadron FPGA Mini Board.

---

## 8. Build & Run

After completing both the RTL and software integration, build the firmware and program the FPGA using the standard VSDSquadron build flow.

Typical workflow:

1. Compile the firmware.
2. Generate the firmware memory image.
3. Synthesize the FPGA design.
4. Program the FPGA.
5. Open the UART terminal.
6. Execute the example firmware and verify the expected output.

Refer to the VSDSquadron project documentation for the exact build commands applicable to your development environment.

---

## 9. Hardware Test Setup

The Timer IP was validated on the VSDSquadron FPGA Mini Board. Since the example firmware reports test results through UART, a CH340 USB-to-UART converter was used to monitor the serial output on a host computer.

### Hardware Connections

| CH340 USB-to-UART Module | VSDSquadron FPGA Mini Board |
|---------------------------|-----------------------------|
| TX                        | RX (Pin 3)                  |
| RX                        | TX (Pin 4)                  |
| GND                       | GND (Pin 23)                |
| VCC (3.3 V)               | 3.3 V Jumper Installed      |

### Serial Terminal Configuration

| Parameter | Value |
|-----------|-------|
| Baud Rate | 9600 |
| Data Bits | 8 |
| Parity | None |
| Stop Bits | 1 |

After programming the FPGA, the board was connected to a host computer through the CH340 USB-to-UART converter. A serial terminal configured with the above settings was used to monitor the UART messages printed by the example firmware during Timer IP validation.

---

## 10. Validation

After successful integration, the Timer IP should operate as expected when running the example firmware.

The validation process confirms:

- Successful memory-mapped register access
- Correct One-Shot mode operation
- Correct Periodic mode operation
- Proper prescaler functionality
- Accurate timeout flag generation
- Successful register readback

A successful validation indicates that the Timer IP has been correctly integrated into the VSDSquadron RISC-V SoC.

---

## 11. Troubleshooting

| Issue | Possible Cause | Solution |
|--------|----------------|----------|
| Timer does not start | Timer not enabled | Verify the ENABLE bit in the CTRL register. |
| Countdown value does not change | Incorrect LOAD value or clock connection | Verify the LOAD register and system clock. |
| Timeout flag never sets | Timer configuration incorrect | Check the operating mode and prescaler configuration. |
| Register reads return incorrect values | Address decoding error | Verify the Timer IP base address and address decoder. |
| Software cannot access the Timer | Memory map not updated | Confirm the Timer IP is correctly connected to the SoC bus. |
| Unexpected timer behavior | Reset or clock not connected correctly | Verify the clock and reset connections to the Timer IP. |

---
