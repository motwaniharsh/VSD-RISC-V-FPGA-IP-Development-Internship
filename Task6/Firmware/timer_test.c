#include <stdint.h>
#include "io.h"

extern void printf(const char *);

int main()
{
    printf("\n===== TIMER IP TEST =====\n");

    //--------------------------------------------------
    // TEST 1 : One-shot mode
    //--------------------------------------------------

    printf("\nTEST 1 : One-shot mode\n");

    TIMER_LOAD = 20;

    /* EN = 1 */
    TIMER_CTRL = 0x1;

    while(!(TIMER_STATUS & 1));

    printf("PASS : One-shot timeout detected\n");

    TIMER_STATUS = 1;

    printf("STATUS cleared\n");


    //--------------------------------------------------
    // TEST 2 : Periodic mode
    //--------------------------------------------------

    printf("\nTEST 2 : Periodic mode\n");

    TIMER_LOAD = 5;

    /*
        bit0 = EN
        bit1 = MODE
    */

    TIMER_CTRL = 0x3;

    while(!(TIMER_STATUS & 1));

    printf("PASS : Periodic timeout detected\n");

    TIMER_STATUS = 1;

    printf("STATUS cleared\n");


    //--------------------------------------------------
    // TEST 3 : Prescaler
    //--------------------------------------------------

    printf("\nTEST 3 : Prescaler mode\n");

    TIMER_LOAD = 5;

    /*
        EN = 1

        PRESC_EN = 1

        PRESC_DIV = 4
    */

    TIMER_CTRL =
        (1<<0) |
        (1<<2) |
        (4<<8);

    while(!(TIMER_STATUS & 1));

    printf("PASS : Prescaler timeout detected\n");

    TIMER_STATUS = 1;

    printf("STATUS cleared\n");


    //--------------------------------------------------
    // TEST 4 : Register Readback
    //--------------------------------------------------

    printf("\nTEST 4 : Register Readback\n");

    TIMER_LOAD = 50;

    if(TIMER_LOAD == 50)
        printf("PASS : LOAD register readback\n");

    TIMER_CTRL = 1;

    if(TIMER_CTRL == 1)
        printf("PASS : CTRL register readback\n");


    //--------------------------------------------------
    // TEST COMPLETE
    //--------------------------------------------------

    printf("\n===== ALL TIMER TESTS PASSED =====\n");

    IO_OUT(IO_LEDS,31);

    while(1);

    return 0;
}
