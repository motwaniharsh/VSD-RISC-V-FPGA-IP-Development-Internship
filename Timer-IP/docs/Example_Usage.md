# Example Usage

## 1. Introduction

This document demonstrates how to use the Timer IP from software after it has been successfully integrated into the VSDSquadron RISC-V SoC. The examples illustrate the basic programming sequence required to configure, start, monitor, and stop the timer using memory-mapped registers.

The Timer IP is accessed through standard C memory-mapped register definitions provided in `io.h`. The example application `timer_test.c` demonstrates all supported operating modes and can be used to verify correct Timer IP functionality.

---

## 2. Including the Register Definitions

Include the Timer IP register definitions in your application.

```c
#include "io.h"
```

The following memory-mapped registers are available:

```c
#define TIMER_CTRL   (*(volatile uint32_t*)(IO_BASE + IO_TIMER + 0x0))
#define TIMER_LOAD   (*(volatile uint32_t*)(IO_BASE + IO_TIMER + 0x4))
#define TIMER_VALUE  (*(volatile uint32_t*)(IO_BASE + IO_TIMER + 0x8))
#define TIMER_STATUS (*(volatile uint32_t*)(IO_BASE + IO_TIMER + 0xC))
```
---

## 3. One-Shot Timer Example

The following example demonstrates how to configure the Timer IP in One-Shot mode.

### Programming Sequence

1. Write the desired countdown value to the LOAD register.
2. Configure the CTRL register for One-Shot mode.
3. Enable the timer.
4. Poll the STATUS register until the timeout flag is asserted.
5. Clear the timeout flag.

```c
TIMER_LOAD = 100;
TIMER_CTRL = 0x01;

while (!(TIMER_STATUS & 0x01));

TIMER_STATUS = 0x01;
```

In One-Shot mode, the timer stops automatically after reaching zero.

---

## 4. Periodic Timer Example

To generate periodic timeout events, configure the timer in Periodic mode.

```c
TIMER_LOAD = 100;
TIMER_CTRL = 0x03;
```

In this mode, the timer automatically reloads the programmed countdown value after every timeout event and continues counting until disabled by software.

---

## 5. Prescaler Example

The programmable prescaler can be used to generate longer timing intervals.

Example configuration:

```c
TIMER_LOAD = 100;
TIMER_CTRL = (10 << 8) | (1 << 2) | 1;
```

This configuration:

- Enables the timer
- Enables the programmable prescaler
- Sets the prescaler divider value to 10

The countdown counter is decremented only after the programmed number of clock cycles has elapsed.

---

## 6. Reading the Current Timer Value

Software can monitor timer progress by reading the VALUE register.

```c
uint32_t remaining = TIMER_VALUE;
```

The VALUE register always contains the current countdown value while the timer is running.

---

## 7. Clearing the Timeout Flag

When the timer reaches zero, the timeout flag is set in the STATUS register.

The flag is cleared by writing a logic 1 to bit 0.

```c
TIMER_STATUS = 1;
```

This Write-1-to-Clear (W1C) mechanism ensures that software explicitly acknowledges timeout events.

---

## 8. Complete Example Program

A complete demonstration program is provided in the `software/` directory.

```
software/
└── timer_test.c
```

The example application demonstrates:

- One-Shot mode
- Periodic mode
- Programmable prescaler
- Register read/write verification

The program can be compiled and executed directly after integrating the Timer IP into the VSDSquadron RISC-V SoC.

---

## 9. Expected Output

After programming the FPGA and running the example firmware, the UART terminal displays the following output:

```text
===== TIMER IP TEST =====

TEST 1 : One-shot mode
PASS : One-shot timeout detected
STATUS cleared

TEST 2 : Periodic mode
PASS : Periodic timeout detected
STATUS cleared

TEST 3 : Prescaler mode
PASS : Prescaler timeout detected
STATUS cleared

TEST 4 : Register Readback
PASS : LOAD register readback
PASS : CTRL register readback

===== ALL TIMER TESTS PASSED =====
```

The successful completion of all four tests confirms that:

- The One-Shot mode operates correctly.
- The Periodic mode automatically reloads the timer after each timeout.
- The programmable prescaler functions as expected.
- The memory-mapped registers can be written to and read back correctly.

After all tests pass, the firmware turns on all available LEDs by writing the value `31` to the LED output register and then enters an infinite loop.

---
