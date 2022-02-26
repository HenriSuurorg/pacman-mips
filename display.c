#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>


void setDisplay2d(int x, int y, int width, int height)  {
    int r, c, page;
    uint8_t powerOfTwo = 1;
    uint8_t oledN = 0;

    for (r = 0; r < 32; r++) {
        for(c = 0; c < 128; c++){
            if(r >= y && r <= (y + height) && c >= x && c <= (x + width))
                display2d[r][c] = 1;
        }
    }

    for (page = 0; page < 4; page++){
        for(c = 0; c < 128; c++){
            powerOfTwo = 1;
            oledN = 0;

            for(r = 0; r < 8; r++){
                if(display2d[8 * page + r][c]){
                    oledN |= powerOfTwo;
                }
                powerOfTwo <<= 1;
            }
            display[c + page * 128] = oledN;
        }
    }

}

void clearDisplay(){
    int r, c, i;

    for(r = 0; r < 32; r++){
        for(c = 0; c < 128; c++)
            display2d[r][c] = 0;
    }

    for (i = 0; i < 512; i++)
        display[i] = 0;
}