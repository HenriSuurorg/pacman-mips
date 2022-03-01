#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)


uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
	return SPI2BUF;
}

void display_init(void) {
    DISPLAY_CHANGE_TO_COMMAND_MODE;
	quicksleep(10);
	DISPLAY_ACTIVATE_VDD;
	quicksleep(1000000);
	
	spi_send_recv(0xAE);
	DISPLAY_ACTIVATE_RESET;
	quicksleep(10);
	DISPLAY_DO_NOT_RESET;
	quicksleep(10);
	
	spi_send_recv(0x8D);
	spi_send_recv(0x14);
	
	spi_send_recv(0xD9);
	spi_send_recv(0xF1);
	
	DISPLAY_ACTIVATE_VBAT;
	quicksleep(10000000);
	
	spi_send_recv(0xA1);
	spi_send_recv(0xC8);
	
	spi_send_recv(0xDA);
	spi_send_recv(0x20);
	
	spi_send_recv(0xAF);
}

void display_string(int line, char *s) {
	int i;
	if(line < 0 || line >= 4)
		return;
	if(!s)
		return;
	
	for(i = 0; i < 16; i++)
		if(*s) {
			textbuffer[line][i] = *s;
			s++;
		} else
			textbuffer[line][i] = ' ';
}

void setDisplay2d(int x, int y, int width, int height)  {
    int r, c, page;
    uint8_t powerOfTwo = 1;
    uint8_t oledN = 0;

    for (r = y; r < 32; r++) {
        for(c = x; c < 128; c++){
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

void display_image(int x, const uint8_t *data) {
	int i, j;
	
	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;

		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(x & 0xF);
		spi_send_recv(0x10 | ((x >> 4) & 0xF));
		
		DISPLAY_CHANGE_TO_DATA_MODE;
		
		for(j = 0; j < 128; j++)
			spi_send_recv(data[i*128 + j]);
	}
}

void display_update(void) {
	int r, c;
	for(r = 0; r < 4; r++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;
		spi_send_recv(0x22);
		spi_send_recv(r);
		
		spi_send_recv(0x0);
		spi_send_recv(0x10);
		
		DISPLAY_CHANGE_TO_DATA_MODE;
		
		for(c = 0; c < 128; c++) {
				spi_send_recv(display2d[r][c]);
		}
	}
}

//clear both display2d and display
void clearDisplay(){
    int r, c, i;

    for(r = 0; r < 32; r++){
        for(c = 0; c < 128; c++)
            display2d[r][c] = 0;
    }

    for (i = 0; i < 512; i++)
        display[i] = 0;
}

void displayWalls(){
	setDisplay2d(1, 0, 49, 0);
	setDisplay2d(76, 0, 49, 0);

	setDisplay2d(1, 0, 0, 30);
	setDisplay2d(50, 0, 0, 5);
	setDisplay2d(76, 0, 0, 5);
	setDisplay2d(126, 0, 0, 30);

	setDisplay2d(1, 31, 125, 31);

	setDisplay2d(6, 6, 13, 0);
	setDisplay2d(25, 6, 3, 0);
	setDisplay2d(34, 6, 10, 0);
	setDisplay2d(83, 6, 19, 0);
	setDisplay2d(108, 6, 13, 0);

    setDisplay2d(6, 6, 0, 3);
	setDisplay2d(19, 6, 0, 3);
	setDisplay2d(25, 6, 0, 3);
	setDisplay2d(28, 6, 0, 3);
	setDisplay2d(108, 6, 0, 3);
	setDisplay2d(121, 6, 0, 3);

	setDisplay2d(6, 9, 13, 0);
	setDisplay2d(25, 9, 3, 0);
	setDisplay2d(108, 9, 13, 0);

	setDisplay2d(34, 6, 0, 10);
	setDisplay2d(44, 6, 0, 10);

	setDisplay2d(83, 6, 0, 3);
	setDisplay2d(102, 6, 0, 8);

	setDisplay2d(34, 16, 10, 0);

	setDisplay2d(36, 8, 6, 0);
	setDisplay2d(36, 8, 0, 6);
	setDisplay2d(42, 8, 0, 6);
	setDisplay2d(36, 13, 6, 0);

	setDisplay2d(36, 14, 0, 0);
	setDisplay2d(39, 8, 0, 6);
	setDisplay2d(42, 14, 0, 0);

	setDisplay2d(36, 8, 0, 6);

	setDisplay2d(51, 12, 5, 0);
	setDisplay2d(51, 12, 0, 4);
	setDisplay2d(56, 12, 0, 4);
	setDisplay2d(51, 16, 5, 0);

	setDisplay2d(53, 14, 1, 0);

	setDisplay2d(83, 9, 16, 0);
	setDisplay2d(99, 9, 0, 8);
	setDisplay2d(102, 14, 14, 0);
	setDisplay2d(116, 14, 0, 3);

	setDisplay2d(99, 17, 16, 0);
	
	setDisplay2d(62, 12, 14, 0);
	setDisplay2d(62, 12, 0, 9);
	setDisplay2d(66, 15, 0, 9);
	setDisplay2d(51, 22, 11, 0);

	setDisplay2d(11, 14, 17, 0);
	setDisplay2d(11, 14, 0, 3);
	setDisplay2d(11, 14, 0, 3);
	setDisplay2d(28, 14, 0, 8);
	setDisplay2d(25, 17, 0, 8);
	setDisplay2d(11, 17, 14, 0);
	setDisplay2d(25, 25, 19, 0);
	setDisplay2d(44, 22, 0, 3);

	setDisplay2d(28, 22, 16, 0);

	setDisplay2d(6, 23, 13, 0);
	setDisplay2d(6, 23, 0, 2);
	setDisplay2d(19, 23, 0, 2);
	setDisplay2d(6, 25, 13, 0);

	setDisplay2d(51, 22, 0, 3);
	setDisplay2d(51, 25, 15, 0);
    setDisplay2d(66, 15, 10, 0);
	setDisplay2d(77, 12, 0, 3);

    setDisplay2d(72, 21, 4, 0);
    setDisplay2d(72, 21, 0, 4);
	setDisplay2d(77, 21, 0, 4);
	setDisplay2d(72, 25, 4, 0);
	setDisplay2d(74, 23, 1, 0);

	setDisplay2d(83, 15, 9, 0);
	setDisplay2d(83, 15, 0, 9);
	setDisplay2d(93, 15, 0, 9);
	setDisplay2d(83, 25, 10, 0);

    setDisplay2d(85, 17, 0, 5);
	setDisplay2d(88, 17, 0, 5); 
	setDisplay2d(91, 17, 0, 6);

	setDisplay2d(85, 18, 5, 0);
	setDisplay2d(85, 23, 5, 0);

	setDisplay2d(99, 23, 2, 0);
	setDisplay2d(99, 25, 2, 0);
	setDisplay2d(99, 23, 0, 2);
	setDisplay2d(102, 23, 0, 2);

    setDisplay2d(109, 23, 12, 0);
	setDisplay2d(109, 25, 12, 0);
	setDisplay2d(109, 23, 0, 2);
	setDisplay2d(121, 23, 0, 2);

	setDisplay2d(50, 6, 26, 0);

    // setDisplay2d(0, 6, 0, 6);
	// setDisplay2d(0, 1, 0, 5);
	// setDisplay2d(0, 1, 0, 5);
	// setDisplay2d(0, 1, )

}