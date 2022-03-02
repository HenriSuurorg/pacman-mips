#include "pic32mx.h"  /* Declarations of system-specific addresses etc */

void init_pin() {
    AD1PCFG = 0xFBFF;
    AD1CON1 = 4 << 8 | 7 << 5;
    AD1CHS = 1 << 17;
    TRISBSET = 1 << 11;
    AD1CON2 = 0;
    AD1CON3SET = 1 << 15;

    /* Set up output pins */

    /* Turn on ADC */
    AD1CON1SET = 1 << 15;
}

unsigned int seed() {
    int n = 8;
    unsigned int seed = n;
    for (; n > 0; n--) {
        /* Start sampling, wait until conversion is done */
        AD1CON1 |= (0x2);
        while (!(AD1CON1 & (0x2)))
            seed ^= ADC1BUF0 + TMR2;
        while (!(AD1CON1 & 0x1))
            seed ^= ADC1BUF0 + TMR2;

        /* Get the analog value */
        seed ^= ADC1BUF0 + TMR2;
    }
    return seed;
}