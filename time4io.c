#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw( void ){
    /* shift the bits right by 8 to get the first switch 
     at the lsb, then mask the 4 switch bits and return */
    return (PORTD >> 8) & 0xf;
}

int getbtns( void ){
    /* shift the bits right by 5 to get the first button 
     at the lsb, then mask the 3 switch bits and return */
    return (PORTD >> 5) & 0x7;
}