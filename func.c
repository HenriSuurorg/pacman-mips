#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

/* Declare a helper function which is local to this file */
static void num32asc( char * s, int ); 



/* Helper function, local to this file.
   Converts a number to hexadecimal ASCII digits. */
static void num32asc( char * s, int n ) 
{
  int i;
  for( i = 28; i >= 0; i -= 4 )
    *s++ = "0123456789ABCDEF"[ (n >> i) & 15 ];
}

void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}


void checkButtons(){
  int btns; 
  btns = (PORTF >> 1) & 0x1; // check button 1
  btns = btns | ((PORTD >> 4) & 0xE); // check button 2-4

  if (btns){
    if(btns & 0x8){
      clearDisplay();
      setDisplay2d(0, 16, 128, 16);
      display_image(0, display);
    }

    if(btns & 0x4){
      clearDisplay();
      setDisplay2d(0, 0, 64, 32);
      display_image(0, display);
    }
    
    if(btns & 0x2){
      clearDisplay();
      setDisplay2d(64, 0, 64, 32);
      display_image(0, display);
    }

    if(btns & 0x1){
      clearDisplay();
      setDisplay2d(0, 0, 128, 16);
      display_image(0, display);
    }
  }
}