# VSD-RISC-V-FPGA-IP-Development-Internship

Repository documenting tasks, experiments, and learning outcomes from the LNMIIT RISC-V FPGA IP Development Internship conducted by VLSI System Design (VSD).

---

## About the Internship

This internship focuses on understanding the RISC-V ecosystem through hands-on experimentation with Linux-based development environments, RISC-V toolchains, compiler optimizations, instruction-level analysis, simulation, debugging, and FPGA-based IP development workflows. The internship combines software and hardware concepts to provide practical exposure to computer architecture, processor design, verification, and hardware-software co-design methodologies.


---

## Objectives

* Gain hands-on experience with the RISC-V architecture.
* Understand the complete software-to-hardware development flow.
* Learn Linux-based development environments and toolchains.
* Explore compiler optimizations and assembly-level analysis.
* Develop proficiency in FPGA design and IP development workflows.
* Build practical skills in simulation, verification, and hardware implementation.

---

## Task Progress

| Task   | Description                                                     | Status         |
| ------ | --------------------------------------------------------------- | -------------- |
| Task 1 | Introduction to the RISC-V Compilation and Optimization Process | ✅ Completed    |
| Task 2 | SPIKE Simulation and Observation with -O1 and -Ofast            | ✅ Completed    |
| Task 3 | Environment Setup & RISC-V Reference Bring-Up                   | ✅ Completed    |
| Task 4 | Design & Integrate Your First Memory-Mapped IP                  | ✅ Completed    |
| Task 5 | Design & Integrate a Multi-Register GPIO IP                     | ✅ Completed    |
| Task 6 | Timer IP Development for RISC-V SoC (Core Contributor Task)     | ✅ Completed    |
| Task 7 | Commercial-Grade Timer IP Documentation & Release               | ✅ Completed    |

---

## Tasks Overview

### Task 1: Introduction to the RISC-V Compilation and Optimization Process

Topics covered:

* Linux development environment
* C programming fundamentals
* GCC compilation flow
* RISC-V cross-compilation
* Assembly generation using `objdump`
* Instruction-level analysis
* Compiler optimization comparison (`-O1` vs `-Ofast`)

📄 Detailed Report: [Task 1](./Task1/README.md)

---

### Task 2: SPIKE Simulation and Observation with -O1 and -Ofast

Topics covered:

* Execution of RISC-V programs using the SPIKE simulator
* Verification of RISC-V binaries against native GCC execution
* Instruction-level debugging using SPIKE debug mode
* Register observation and analysis
* Understanding RISC-V instructions such as `LUI` and `ADDI`
* Comparison of assembly generated using `-O1` and `-Ofast`
* Development of an AI/ML-inspired application using an Artificial Neuron with ReLU activation
* RISC-V compilation, simulation, and assembly analysis of AI/ML workloads

📄 Detailed Report: [Task 2](./Task2/README.md)

---

### Task 3: Environment Setup & RISC-V Reference Bring-Up

Topics covered:

* GitHub Codespace setup and verification
* RISC-V reference flow validation
* Compilation and execution of RISC-V sample programs
* Understanding the RISC-V software execution flow
* Local Linux environment preparation
* Installation and configuration of the RISC-V GNU Toolchain
* Building and configuring the SPIKE ISA Simulator
* Building and configuring the RISC-V Proxy Kernel (PK)
* Verification of toolchain functionality through simulation and execution of sample programs

📄 Detailed Report: [Task 3](./Task3/README.md)

---

### Task 4: Design & Integrate Your First Memory-Mapped IP

Topics covered:

* GPIO IP design in Verilog
* Integration of a custom peripheral into the RISC-V SoC
* Modification of the SoC memory map
* GPIO read and write operations
* Firmware development for GPIO testing
* RTL simulation using Icarus Verilog
* Waveform analysis using GTKWave
* Verification of GPIO functionality through simulation

📄 Detailed Report: [Task 4](./Task4/README.md)

---

### Task 5: Design & Integrate a Multi-Register GPIO IP

Topics covered:

* Design of a multi-register GPIO IP in Verilog
* Implementation of GPIO_DATA, GPIO_DIR, and GPIO_READ registers
* Internal address decoding for register selection
* Integration of the custom GPIO peripheral into the RISC-V SoC
* Modification of the SoC memory map for GPIO integration
* Memory-mapped read and write operations
* Firmware development for multi-register GPIO testing
* RTL simulation using Icarus Verilog
* Waveform analysis using GTKWave
* Verification of GPIO functionality through RTL simulation

📄 Detailed Report: [Task 5](./Task5/README.md)

---

### Task 6: Timer IP Development for RISC-V SoC (Core Contributor Task)

Topics covered:

- Design of a 32-bit Timer IP in Verilog HDL
- Memory-mapped register interface implementation
- One-Shot timer operation
- Periodic timer with auto-reload functionality
- Programmable prescaler implementation
- Integration of the Timer IP into the RISC-V SoC
- Modification of the SoC memory map and address decoding
- Firmware development for Timer validation
- RTL simulation using Icarus Verilog
- Waveform analysis using GTKWave
- FPGA implementation and hardware validation on the VSDSquadron FPGA Mini
- UART-based verification using a CH340 USB-to-UART converter

📄 **Detailed Report:** [Task 6](Task6/README.md)

---

## Task 7: Commercial-Grade TImer IP Documentation & Release

Topics covered:

- Creation of a commercial-style IP repository structure
- Development of a comprehensive IP User Guide
- Documentation of the Timer IP register map
- RTL integration guide for the VSDSquadron RISC-V SoC
- Software integration and programming examples
- Example firmware usage documentation
- Hardware validation setup and UART test configuration
- Creation of Timer IP architecture and integration flow diagrams
- Preparation of professional GitHub documentation
- Packaging the Timer IP for reusable SoC integration

📄 **Detailed Report:** [Timer IP](Timer-IP)

---

## Internship Information

**Organization:** VLSI System Design (VSD)

**Program:** LNMIIT RISC-V FPGA IP Development Internship

**Institute:** The LNM Institute of Information Technology (LNMIIT), Jaipur

---

## Author

**Harsh Motwani**  
B.Tech. Electronics and Communication Engineering  
The LNM Institute of Information Technology (LNMIIT), Jaipur  

---

## License

This repository is maintained for educational and internship documentation purposes.

---
