# Timer IP Development for RISC-V SoC (Core Contributor Task)

## Objective

The objective of this project is to design and integrate a configurable Timer peripheral that can be accessed through memory-mapped registers.

The project includes:

- RTL implementation of the Timer IP
- Integration into the existing RISC-V SoC
- Memory-mapped register interface
- Software validation using C firmware
- Functional simulation
- Hardware validation on the VSDSquadron FPGA Mini Board

--

## Relevant Files Used

```text
basicRISCV/
│
├── RTL/
│   ├── riscv.v               ← SoC top-level modified for Timer IP integration
│   ├── timer_ip.v            ← Custom Timer peripheral implementation
│   ├── clockworks.v          ← Clock generation and reset circuitry
│   ├── emitter_uart.v        ← UART transmitter for firmware output
│   ├── Makefile              ← Build, synthesis and FPGA programming
│   ├── ice40_stubs.v         ← Simulation stubs for FPGA primitives
│   └── sim.vvp               ← Compiled simulation executable
│
└── Firmware/
    ├── timer_test.c          ← Firmware used to validate the Timer IP
    ├── io.h                  ← Memory-mapped register definitions
    └── timer_test.bram.hex   ← Generated firmware image loaded into memory
```

## File Description

- **`riscv.v`** : Top-level RISC-V SoC design responsible for integrating the CPU, memory, UART, GPIO, and the newly developed Timer IP.

- **`timer_ip.v`** : Custom Timer peripheral implementing a 32-bit programmable countdown timer with one-shot mode, periodic mode, programmable prescaler, and timeout status generation.

- **`clockworks.v`** : Generates the system clock and reset signals required for reliable FPGA operation.

- **`emitter_uart.v`** : UART transmitter module used by the firmware to print validation results to the serial terminal.

- **`Makefile`** : Build automation file used for firmware compilation, RTL synthesis, place-and-route, bitstream generation, simulation, and FPGA programming.

- **`io.h`** : Firmware header file containing the memory-mapped register definitions and peripheral address mapping used by the Timer firmware.

- **`timer_test.c`** : Firmware application developed to verify all Timer IP functionalities, including one-shot mode, periodic mode, prescaler operation, and register readback.

- **`ice40_stubs.v`** : Simulation support module that replaces FPGA-specific primitives during RTL simulation using Icarus Verilog.

- **`timer_test.bram.hex`** : Memory initialization file generated from the Timer firmware and loaded into the SoC instruction memory for simulation and hardware execution.

- **`sim.vvp`** : Compiled Icarus Verilog simulation executable used to perform RTL verification.

--

## Features

- 32-bit programmable countdown timer
- Memory-mapped register interface
- One-shot mode
- Periodic (auto-reload) mode
- Programmable prescaler
- Current timer value readback
- Timeout status flag
- Write-1-to-clear timeout flag
- Integrated with RISC-V SoC
- Validated in simulation and on FPGA hardware

--

## Project Architecture

                 +----------------------+
                 |     RISC-V CPU       |
                 +----------+-----------+
                            |
                  Memory Mapped Bus
                            |
                +-----------+-----------+
                |        Timer IP       |
                +-----------------------+
                | CTRL Register         |
                | LOAD Register         |
                | VALUE Register        |
                | STATUS Register       |
                +-----------------------+
                            |
                     Timeout Signal

--

## Register Map

| Offset | Register | Access | Description |
|--------:|----------|:------:|-------------|
| 0x00 | CTRL | R/W | Timer control register |
| 0x04 | LOAD | R/W | Initial countdown value |
| 0x08 | VALUE | R | Current timer value |
| 0x0C | STATUS | R/W | Timeout status register |

--

