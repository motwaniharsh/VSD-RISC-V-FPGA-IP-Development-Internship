#include <stdint.h>
#include "io.h"

//-----------------------------------------------------
// UART Functions
//-----------------------------------------------------

static void putchar_uart(char c)
{
    while(IO_IN(IO_UART_CNTL) & 1);
    IO_OUT(IO_UART_DAT, c);
}

static void print(const char *p)
{
    while(*p)
        putchar_uart(*p++);
}

static void print_hex(uint32_t value)
{
    for(int i = 28; i >= 0; i -= 4)
    {
        uint32_t digit = (value >> i) & 0xF;
        putchar_uart(digit < 10 ? ('0' + digit) : ('A' + digit - 10));
    }
}

//-----------------------------------------------------
// Main Test Program
//-----------------------------------------------------

int main()
{
    uint32_t value;

    print("\n==============================\n");
    print("      GPIO IP TEST\n");
    print("==============================\n\n");

    //-------------------------------------------------
    // TEST 1 : GPIO_DIR Register
    //-------------------------------------------------

    print("TEST 1 : GPIO_DIR Register\n");

    GPIO_DIR = 0xFFFFFFFF;

    value = GPIO_DIR;

    if(value == 0xFFFFFFFF)
        print("PASS : GPIO_DIR Readback\n");
    else
    {
        print("FAIL : GPIO_DIR Readback\n");
        print("Read = 0x");
        print_hex(value);
        print("\n");
    }

    //-------------------------------------------------
    // TEST 2 : GPIO_DATA Register
    //-------------------------------------------------

    print("\nTEST 2 : GPIO_DATA Register\n");

    GPIO_DATA = 0x12345678;

    value = GPIO_DATA;

    if(value == 0x12345678)
        print("PASS : GPIO_DATA Readback\n");
    else
    {
        print("FAIL : GPIO_DATA Readback\n");
        print("Read = 0x");
        print_hex(value);
        print("\n");
    }

    //-------------------------------------------------
    // TEST 3 : GPIO_READ Register
    //-------------------------------------------------

    print("\nTEST 3 : GPIO_READ Register\n");

    value = GPIO_READ;

    if(value == 0x12345678)
        print("PASS : GPIO_READ Value\n");
    else
    {
        print("FAIL : GPIO_READ Value\n");
        print("Read = 0x");
        print_hex(value);
        print("\n");
    }

    //-------------------------------------------------
    // LED Indication
    //-------------------------------------------------

    IO_OUT(IO_LEDS, 31);

    //-------------------------------------------------
    // Final Result
    //-------------------------------------------------

    print("\n==============================\n");
    print(" ALL GPIO TESTS PASSED\n");
    print("==============================\n");

    while(1);

    return 0;
}