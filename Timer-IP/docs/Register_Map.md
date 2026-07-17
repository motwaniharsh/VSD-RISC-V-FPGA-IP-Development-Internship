# Register Map

## 1. Introduction

The Timer IP is controlled through a set of memory-mapped registers that allow software to configure timer operation, monitor the countdown process, and detect timeout events. The registers are accessible through standard memory read and write operations performed by the RISC-V processor.

This document describes the register layout, access permissions, reset values, and functional behavior of each register implemented in the Timer IP.

---

## 2. Register Summary

The Timer IP occupies a 16-byte memory region starting at the base address **0x400040** within the VSDSquadron RISC-V SoC memory map.

| Offset | Address | Register | Access | Description |
|---------|----------|----------|--------|-------------|
| 0x00 | 0x400040 | CTRL | R/W | Timer control register |
| 0x04 | 0x400044 | LOAD | R/W | Initial countdown value |
| 0x08 | 0x400048 | VALUE | R | Current timer value |
| 0x0C | 0x40004C | STATUS | R/W | Timer status register |

---

## 3. CTRL Register

**Offset:** `0x00`  
**Address:** `0x400040`  
**Access:** Read/Write  
**Reset Value:** `0x00000000`

The Control Register configures the operating mode and enables the Timer IP.

### Register Layout

| Bits | Name | Access | Description |
|------|------|--------|-------------|
| 31:16 | Reserved | R | Reserved. Read as zero. |
| 15:8 | PRESCALER_DIV | R/W | Prescaler divider value. Used only when the prescaler is enabled. |
| 7:3 | Reserved | R | Reserved. Read as zero. |
| 2 | PRESCALER_EN | R/W | Enables the programmable prescaler. |
| 1 | MODE | R/W | Operating mode (0 = One-Shot, 1 = Periodic). |
| 0 | ENABLE | R/W | Enables timer operation. |

### Bit Descriptions

#### ENABLE (Bit 0)

| Value | Description |
|-------|-------------|
| 0 | Timer Disabled |
| 1 | Timer Enabled |

#### MODE (Bit 1)

| Value | Description |
|-------|-------------|
| 0 | One-Shot Mode |
| 1 | Periodic Mode |

#### PRESCALER_EN (Bit 2)

| Value | Description |
|-------|-------------|
| 0 | Prescaler Disabled |
| 1 | Prescaler Enabled |

#### PRESCALER_DIV (Bits 15:8)

Specifies the prescaler division value used when the prescaler is enabled.

---

## 4. LOAD Register

**Offset:** `0x04`  
**Address:** `0x400044`  
**Access:** Read/Write  
**Reset Value:** `0x00000000`

The Load Register stores the initial countdown value that is loaded into the timer counter when the timer begins operation.

### Register Layout

| Bits | Name | Access | Description |
|------|------|--------|-------------|
|31:0|LOAD_VALUE|R/W|Initial countdown value.|

### Description

Software writes the desired countdown value into this register before enabling the timer.

- In **One-Shot Mode**, this value is loaded once.
- In **Periodic Mode**, the same value is automatically reloaded after every timeout event.

---

## 5. VALUE Register

**Offset:** `0x08`  
**Address:** `0x400048`  
**Access:** Read Only  
**Reset Value:** `0x00000000`

The Value Register contains the current countdown value of the timer.

### Register Layout

| Bits | Name | Access | Description |
|------|------|--------|-------------|
|31:0|CURRENT_VALUE|R|Current timer count.|

### Description

The register is automatically updated by the Timer IP while the timer is running.

Software may read this register at any time to:

- Monitor countdown progress
- Measure elapsed time
- Verify timer operation

---

## 6. STATUS Register

**Offset:** `0x0C`  
**Address:** `0x40004C`  
**Access:** Read/Write  
**Reset Value:** `0x00000000`

The Status Register reports timer timeout events.

### Register Layout

| Bits | Name | Access | Description |
|------|------|--------|-------------|
|31:1|Reserved|R|Reserved. Read as zero.|
|0|TIMEOUT|R/W1C|Timeout Status Flag.|

### TIMEOUT (Bit 0)

| Value | Description |
|-------|-------------|
|0|No timeout event has occurred.|
|1|Timer has reached zero.|

### Clearing the Flag

The timeout flag is cleared by writing a **1** to bit 0 of the STATUS register.

```c
TIMER_STATUS = 1;
```

Writing **0** has no effect.

---

## 7. Register Access Sequence

A typical sequence for operating the Timer IP is shown below.

### One-Shot Mode

1. Write the desired countdown value to the **LOAD** register.
2. Configure the **CTRL** register:
   - Enable timer
   - Select One-Shot mode
   - Configure prescaler (optional)
3. Wait until the **TIMEOUT** flag becomes set.
4. Clear the timeout flag by writing `1` to the **STATUS** register.

---

### Periodic Mode

1. Write the desired countdown value to the **LOAD** register.
2. Configure the **CTRL** register:
   - Enable timer
   - Select Periodic mode
   - Configure prescaler (optional)
3. Monitor the **TIMEOUT** flag.
4. Clear the timeout flag after each timeout event if required.

The timer automatically reloads the programmed countdown value and continues operation until disabled.

---
