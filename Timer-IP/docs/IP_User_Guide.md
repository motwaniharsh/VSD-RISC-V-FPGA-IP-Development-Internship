# Timer IP User Guide

## 1. Introduction

The Timer IP is a configurable 32-bit memory-mapped peripheral designed for the VSDSquadron RISC-V System-on-Chip. It provides programmable timing functionality through a simple software-controlled interface, enabling applications such as delay generation, periodic event scheduling, timeout monitoring, and general-purpose timing operations.

The IP has been developed using Verilog HDL and is intended to integrate seamlessly into the VSDSquadron SoC architecture. It is controlled entirely through memory-mapped registers, allowing software running on the RISC-V processor to configure and monitor timer operation without requiring modifications to the processor core.

This guide describes the architecture, functionality, operating modes, clocking requirements, and design considerations of the Timer IP. Detailed register descriptions and software programming information are provided separately in the accompanying documentation.

---

## 2. IP Overview

The Timer IP is a programmable hardware peripheral that generates precise timing events under software control. It operates as a **32-bit countdown timer**, where software loads an initial count value, configures the desired operating mode, and starts the timer through memory-mapped control registers.

Once enabled, the timer decrements its internal counter on each clock cycle (or after a programmable prescaler interval). When the counter reaches zero, the Timer IP sets a timeout status flag. Depending on the selected operating mode, the timer either stops (One-Shot mode) or automatically reloads the initial count value and continues operation (Periodic mode).

The Timer IP is implemented as a memory-mapped peripheral, allowing the RISC-V processor to access its registers using standard load and store instructions. This simplifies software development while maintaining a lightweight hardware implementation suitable for FPGA-based embedded systems.

The IP is fully synchronous with the system clock and requires only a clock and reset signal for operation. No additional external hardware or dedicated peripherals are required for its functionality.

---

## 3. Features

The Timer IP provides the following features to support programmable timing operations in embedded systems:

### 3.1 32-bit Countdown Timer

Implements a 32-bit programmable countdown timer capable of generating timing intervals over a wide range depending on the system clock frequency.

### 3.2 One-Shot Mode

In One-Shot mode, the timer begins counting down from the programmed load value and automatically stops when the counter reaches zero. This mode is suitable for implementing software delays and timeout operations.

### 3.3 Periodic Mode

In Periodic mode, the timer automatically reloads the programmed load value after reaching zero and continues counting without software intervention. This enables periodic event generation and repetitive timing operations.

### 3.4 Programmable Prescaler

An integrated programmable prescaler allows the timer clock to be divided before reaching the countdown counter. This increases the maximum achievable timing interval without requiring a larger counter.

### 3.5 Memory-Mapped Register Interface

The Timer IP is accessed through a memory-mapped register interface, allowing the RISC-V processor to configure, control, and monitor the timer using standard load and store instructions.

### 3.6 Current Counter Readback

Software can read the current countdown value at any time, making it possible to monitor timer progress or measure elapsed time.

### 3.7 Timeout Status Flag

When the countdown reaches zero, the Timer IP sets a timeout status flag that can be polled by software to detect timer completion.

### 3.8 Simple SoC Integration

The Timer IP is designed for straightforward integration into the VSDSquadron RISC-V SoC with minimal RTL modifications and a standard memory-mapped interface.

---

## 4. Applications

The Timer IP is a general-purpose timing peripheral that can be used in a wide range of embedded and FPGA-based applications. Its programmable countdown functionality makes it suitable for both simple delay generation and periodic event scheduling.

Typical applications include:

- **Software Delay Generation**  
  Generate precise software-controlled delays without implementing delay loops that consume processor resources.

- **Periodic Task Scheduling**  
  Trigger repetitive software tasks at fixed time intervals using the Periodic operating mode.

- **Timeout Monitoring**  
  Detect timeout conditions for communication protocols, peripheral interfaces, or software operations.

- **Event Timing**  
  Measure the duration of software or hardware events by monitoring the timer's countdown value.

- **Embedded Control Systems**  
  Provide timing functionality for control algorithms, state machines, and real-time embedded applications.

- **General-Purpose SoC Peripheral**  
  Serve as a reusable timing module that can be integrated into custom RISC-V System-on-Chip designs for FPGA-based development.

---

## 5. Architecture Overview

The Timer IP is organized as a collection of functional blocks that work together to provide programmable timing functionality. The processor interacts with the Timer IP through a memory-mapped register interface, allowing software to configure operating modes, load timer values, monitor timer status, and control timer execution.

At the heart of the IP is a **32-bit countdown counter** that decrements on every timer clock. Before reaching the counter, the system clock can optionally pass through a **programmable prescaler**, allowing slower countdown rates and longer timing intervals without increasing the counter width.

A **Control Unit** interprets the configuration stored in the control register to determine whether the timer operates in **One-Shot** or **Periodic** mode. When the countdown reaches zero, the control logic sets the timeout status flag. In Periodic mode, the counter is automatically reloaded with the programmed load value and counting continues. In One-Shot mode, the timer stops after the timeout event.

The register interface provides software access to the control, load, current value, and status registers through the system bus. This allows the RISC-V processor to initialize, start, monitor, and stop the timer using standard memory-mapped read and write operations.

The overall architecture is fully synchronous with the system clock and requires only clock and reset inputs, making the IP lightweight, portable, and easy to integrate into FPGA-based System-on-Chip designs.

---

## 6. Block Diagram

![Timer IP Block Diagram](images/block_diagram.png)

**Figure 1.** Block diagram of the Timer IP showing the register interface, control logic, programmable prescaler, countdown counter, timeout detection logic, and communication with the RISC-V processor.

---

## 7. Functional Description

The Timer IP consists of several functional blocks that operate together to provide programmable timing functionality. Each block has a specific role in the timer's operation.

### 7.1 Register Interface

The register interface provides the communication channel between the RISC-V processor and the Timer IP. Through memory-mapped registers, software can configure the timer, load countdown values, monitor timer status, and read the current counter value. This interface allows seamless software control using standard memory read and write operations.

### 7.2 Control Logic

The control logic manages the overall operation of the Timer IP. It interprets the configuration written by software, enables or disables the timer, selects the operating mode, and controls the behavior of the countdown counter. It also generates the appropriate actions when the timer reaches zero.

### 7.3 Load Register

The Load Register stores the initial countdown value programmed by software. Whenever the timer is started, this value is loaded into the countdown counter. In Periodic mode, the same value is automatically reloaded after every timeout event.

### 7.4 Programmable Prescaler

The programmable prescaler divides the system clock before it reaches the countdown counter. This allows the timer to generate longer delays without increasing the counter width. The prescaler value is configurable through software, enabling different timing resolutions depending on the application requirements.

### 7.5 32-bit Countdown Counter

The countdown counter is the core component of the Timer IP. Once enabled, it decrements from the loaded value toward zero. The current counter value can be read by software at any time, allowing applications to monitor timer progress or measure elapsed time.

### 7.6 Timeout Detection Logic

The timeout detection logic continuously monitors the countdown counter. When the counter reaches zero, it generates a timeout event that updates the timer status and determines the next action based on the selected operating mode.

### 7.7 Status Logic

The status logic maintains the timeout status flag, allowing software to determine whether a timeout event has occurred. The status flag remains set until it is cleared by software, enabling reliable polling-based operation.

---

## 8. Operating Modes

The Timer IP supports two operating modes that provide flexibility for different timing applications. The desired mode is selected through the control register before enabling the timer.

### 8.1 One-Shot Mode

In One-Shot mode, the timer performs a single countdown operation. After the timer is enabled, the countdown counter is loaded with the programmed value and begins decrementing. When the counter reaches zero, the timeout status flag is asserted and the timer automatically stops. To start another countdown, software must reload the timer (if required) and enable it again.

This mode is typically used for:

- Software delay generation
- Timeout detection
- Single-event timing operations
- Non-repetitive timing tasks

**Operation Sequence**

1. Software writes the desired countdown value.
2. Software configures the timer for One-Shot mode.
3. The timer is enabled.
4. The counter decrements toward zero.
5. Upon reaching zero:
   - The timeout status flag is set.
   - The timer stops automatically.
6. Software clears the timeout flag before the next operation.

---

### 8.2 Periodic Mode

In Periodic mode, the timer continuously generates periodic timeout events without requiring software intervention after every countdown cycle. When the counter reaches zero, the timeout status flag is asserted, the original load value is automatically reloaded, and the countdown immediately begins again.

This mode is suitable for applications requiring repetitive timing intervals.

Typical applications include:

- Periodic software task scheduling
- System heartbeat generation
- Repetitive event timing
- Continuous monitoring applications

**Operation Sequence**

1. Software writes the desired countdown value.
2. Software configures the timer for Periodic mode.
3. The timer is enabled.
4. The counter decrements toward zero.
5. Upon reaching zero:
   - The timeout status flag is set.
   - The load value is automatically reloaded.
   - A new countdown cycle begins immediately.
6. The process repeats until the timer is disabled by software.

---

### 8.3 Prescaler Operation

The Timer IP includes a programmable prescaler that divides the system clock before it drives the countdown counter. By increasing the prescaler value, the effective timer frequency is reduced, allowing significantly longer timing intervals while maintaining a 32-bit counter.

The prescaler operates transparently to software and affects both One-Shot and Periodic modes. A prescaler value of zero results in the counter decrementing at the system clock rate, while higher values proportionally increase the countdown duration.

The programmable prescaler provides flexibility in selecting the desired timing resolution without requiring modifications to the timer hardware.

---

## 9. Clock & Reset

The Timer IP is a fully synchronous peripheral that operates using the system clock provided by the VSDSquadron RISC-V SoC. All internal registers, control logic, and the countdown counter are updated on the rising edge of the system clock, ensuring deterministic and reliable operation.

### 9.1 Clock

The Timer IP uses the system clock as its primary timing source. In the reference implementation, the IP operates with the **12 MHz system clock** generated by the VSDSquadron FPGA platform. The programmable prescaler allows the effective timer frequency to be reduced, enabling longer timing intervals while maintaining a 32-bit counter.

The Timer IP does not require any additional external clocks or clock management circuitry.

### 9.2 Reset

The Timer IP includes a synchronous reset input that initializes the peripheral to a known state during system startup.

When reset is asserted:

- The countdown counter is cleared.
- The control register is reset to its default configuration.
- The load register is cleared.
- The timeout status flag is cleared.
- Timer operation is disabled.

After reset is deasserted, the Timer IP remains idle until software configures the required registers and enables the timer.

### 9.3 Initialization Sequence

A typical initialization sequence is as follows:

1. Program the desired countdown value.
2. Configure the timer operating mode.
3. Configure the prescaler (if required).
4. Enable the timer.
5. Monitor the timeout status through software.

---

## 10. Memory Interface Overview

The Timer IP is implemented as a **memory-mapped peripheral**, allowing the RISC-V processor to access and control the timer using standard load and store instructions. The processor communicates with the Timer IP through a dedicated address space within the SoC memory map, eliminating the need for any specialized communication protocol.

The Timer IP exposes a set of control and status registers that enable software to configure the timer, load countdown values, monitor timer progress, and detect timeout events. All register accesses are performed through the processor's standard memory interface, ensuring seamless integration with existing software.

The primary registers provided by the Timer IP include:

- **Control Register (CTRL):** Configures the timer operating mode and enables or disables timer operation.
- **Load Register (LOAD):** Stores the initial countdown value to be loaded into the timer.
- **Value Register (VALUE):** Provides the current countdown value for software monitoring.
- **Status Register (STATUS):** Indicates timeout events and provides timer status information.

The exact register addresses, bit-field definitions, reset values, and read/write behavior are described in detail in the [**Register_Map.md**](Register_Map.md) document.

---

## 11. Design Considerations

The Timer IP has been designed with simplicity, portability, and ease of integration as the primary objectives. The following considerations should be taken into account when integrating the IP into a System-on-Chip design:

- The Timer IP is intended for use as a memory-mapped peripheral and should be assigned a unique address range within the SoC memory map.
- All timer operations are synchronous with the system clock, ensuring deterministic behavior.
- The programmable prescaler allows longer timing intervals without increasing the hardware complexity of the countdown counter.
- The IP is controlled entirely through software and does not require modifications to the RISC-V processor core.
- Polling is used to detect timeout events. Applications requiring interrupt-driven operation may extend the design by adding an interrupt output.
- The modular Verilog implementation allows multiple timer instances to be incorporated into larger SoC designs with appropriate address decoding.

---

## 12. Known Limitations

The current implementation of the Timer IP has the following limitations:

- Supports a single timer channel.
- Does not include interrupt generation; timeout events are detected through software polling.
- Designed for integration with the VSDSquadron RISC-V SoC architecture.
- Timing accuracy depends on the system clock frequency.
- The reference implementation assumes a 12 MHz system clock.
- Power management and clock gating are not implemented.
- Hardware support for timer chaining or cascading is not available in the current version.

---
