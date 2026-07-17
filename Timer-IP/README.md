# Timer IP for VSDSquadron RISC-V SoC

A configurable **32-bit memory-mapped Timer IP** designed for the VSDSquadron FPGA RISC-V System-on-Chip. The IP supports **One-Shot**, **Periodic**, and **Programmable Prescaler** modes and can be easily integrated into the VSDSquadron SoC architecture for timing, delay generation, and periodic event applications.

---

## Overview

The **Timer IP** is a configurable **32-bit memory-mapped peripheral** developed for the **VSDSquadron RISC-V System-on-Chip**. It provides programmable timing functionality through a simple register-based interface, allowing software running on the RISC-V processor to generate delays, periodic events, and software-controlled timing operations.

The IP is designed to integrate seamlessly with the existing VSDSquadron SoC architecture using a standard memory-mapped interface. It requires no modifications to the processor core and can be controlled entirely through software by accessing its control and status registers.

The Timer IP was developed in **Verilog HDL**, verified through **RTL simulation**, and successfully validated on the **VSDSquadron FPGA Mini Board**.

### Typical Applications

- Software delay generation
- Periodic task scheduling
- Time measurement
- Event timeout monitoring
- Embedded system timing applications
- General-purpose timing peripheral for RISC-V based SoCs

---

## Features

- 32-bit programmable countdown timer
- Memory-mapped register interface
- One-Shot operating mode
- Periodic (Auto-Reload) operating mode
- Programmable clock prescaler
- Configurable countdown value
- Current timer value readback
- Timeout status flag with Write-1-to-Clear (W1C) support
- Simple software-controlled operation
- Designed for seamless integration with the VSDSquadron RISC-V SoC
- Verified through RTL simulation using Icarus Verilog and GTKWave
- Successfully validated on the VSDSquadron FPGA Mini Board

### Specifications

| Parameter | Value |
|-----------|-------|
| Data Width | 32 bits |
| Register Interface | Memory-Mapped |
| Operating Modes | One-Shot, Periodic |
| Prescaler | Programmable |
| Status Flag | Timeout |
| Clock Source | System Clock |
| Software Interface | Memory-Mapped Registers |
| Hardware Language | Verilog HDL |
| Target Platform | VSDSquadron FPGA Mini |

### Current Limitations

- Single timer instance
- Polling-based operation (no interrupt support)
- Single timeout output
- Designed for the VSDSquadron RISC-V SoC architecture

---

## Repository Structure

```text
Timer-IP/
│
├── README.md                  # Project overview and quick start guide
│
├── RTL/
│   └── timer_ip.v             # Timer IP RTL implementation
│
├── software/
│   ├── timer_test.c           # Example application demonstrating Timer IP usage
│   └── io.h                   # Memory-mapped register definitions
│
└── docs/
    ├── IP_User_Guide.md       # Complete IP documentation
    ├── Register_Map.md        # Register descriptions and bit definitions
    ├── Integration_Guide.md   # Steps to integrate the IP into the VSDSquadron SoC
    └── Example_Usage.md        # Software programming examples
```
---

## Quick Start

Follow these steps to integrate and use the Timer IP in your VSDSquadron RISC-V SoC:

1. Copy the `timer_ip.v` file from the `rtl/` directory into your SoC project.
2. Instantiate the Timer IP in your top-level SoC design.
3. Connect the memory-mapped bus signals and assign the Timer IP to an unused address range.
4. Include the register definitions from `software/io.h` in your firmware project.
5. Use the example program provided in `software/timer_test.c` to verify the functionality of the Timer IP.
6. Build the firmware, program the FPGA, and observe the expected UART output.

---

## Documentation

Detailed documentation for the Timer IP is organized into the following guides:

| Document | Description |
|----------|-------------|
| [**IP_User_Guide.md**](docs/IP_User_Guide.md) | Provides an overview of the Timer IP, including its architecture, features, operating modes, and typical applications. |
| [**Register_Map.md**](docs/Register_Map.md) | Describes the memory-mapped registers, bit fields, reset values, and register access behavior. |
| [**Integration_Guide.md**](docs/Integration_Guide.md) | Explains how to integrate the Timer IP into the VSDSquadron RISC-V SoC, including RTL modifications, address decoding, and hardware connections. |
| [**Example_Usage.md**](docs/Example_Usage.md) | Demonstrates how to program and use the Timer IP through example C code and expected operation. |

Each document is intended to be self-contained, allowing users to quickly locate the information required for integrating, programming, or understanding the Timer IP.

---

## Validation Status

The Timer IP has been successfully verified at multiple stages of development to ensure correct functionality and reliable operation.

### Functional Verification

- RTL simulation performed using **Icarus Verilog**
- Waveform analysis carried out using **GTKWave**
- Verification of:
  - One-Shot mode
  - Periodic mode
  - Programmable Prescaler
  - Register read/write operations

### Hardware Validation

The Timer IP was successfully integrated into the **VSDSquadron RISC-V SoC** and validated on the **VSDSquadron FPGA Mini Board**.

Hardware testing confirmed:

- Successful Timer IP integration
- Correct memory-mapped register access
- Expected countdown behavior
- Successful execution of example firmware
- Correct UART output during validation

The Timer IP is ready for integration into applications requiring programmable timing functionality on the VSDSquadron FPGA platform.

---

## License

This project was developed as part of the **VSD RISC-V SoC & FPGA Internship** and is intended for educational and research purposes.

---
