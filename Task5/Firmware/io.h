#include <stdint.h>

#define IO_BASE       0x400000
#define IO_LEDS       4
#define IO_UART_DAT   8
#define IO_UART_CNTL  16
#define IO_GPIO       32

#define IO_IN(port)       *(volatile uint32_t*)(IO_BASE + port)
#define IO_OUT(port,val)  *(volatile uint32_t*)(IO_BASE + port)=(val)

/* GPIO Control IP Registers */

#define GPIO_DATA (*(volatile uint32_t*)(IO_BASE + IO_GPIO + 0x0))
#define GPIO_DIR  (*(volatile uint32_t*)(IO_BASE + IO_GPIO + 0x4))
#define GPIO_READ (*(volatile uint32_t*)(IO_BASE + IO_GPIO + 0x8))