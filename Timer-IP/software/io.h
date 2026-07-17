#include <stdint.h>

#define IO_BASE       0x400000
#define IO_LEDS       4
#define IO_UART_DAT   8
#define IO_UART_CNTL  16
#define IO_GPIO       32
#define IO_TIMER      64

#define IO_IN(port)       *(volatile uint32_t*)(IO_BASE + port)
#define IO_OUT(port,val)  *(volatile uint32_t*)(IO_BASE + port)=(val)

#define TIMER_CTRL   (*(volatile uint32_t*)(IO_BASE + IO_TIMER + 0x0))
#define TIMER_LOAD   (*(volatile uint32_t*)(IO_BASE + IO_TIMER + 0x4))
#define TIMER_VALUE  (*(volatile uint32_t*)(IO_BASE + IO_TIMER + 0x8))
#define TIMER_STATUS (*(volatile uint32_t*)(IO_BASE + IO_TIMER + 0xC))
