#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"

void displayGhost(x, y){
  setDisplay2d(x + 1, y + 0, 2, 0);
  setDisplay2d(x + 0, y + 1, 0, 3);
  setDisplay2d(x + 4, y + 1, 0, 3);
  setDisplay2d(x + 1, y + 2, 2, 1);
  setDisplay2d(x + 2, y + 1, 0, 3);
  display_image(0, display);
}

void displayPacman(x, y){
  setDisplay2d(x + 1, y + 0, 3, 0);
  setDisplay2d(x + 0, y + 1, 3, 0);
  setDisplay2d(x + 0, y + 2, 2, 0);
  setDisplay2d(x + 0, y + 3, 3, 0);
  setDisplay2d(x + 1, y + 4, 3, 0);
  display_image(0, display);
}

void labinit( void ){
  TRISD = TRISD & 0xf01f;
  TRISD += 0xfe0;
  TRISF = TRISF | (0x20);

  T2CONSET = 0 << 15; // turn timer on
  TMR2 = 0; // set timer to 0
  T2CONSET = 0x70; // set the prescaling to 1:256 
  PR2 = 7812; // set period to 25ms;
  IFSCLR(0) = 1 << 8; // set timer interupt flag to 0
  T2CONSET = 1 << 15; // start the timer
  IECSET(0) = (1 << 8); // timer 2 interrupt enable to 1 
  IPCSET(2) = 0x1f; // set timer2 interrupt priority and sub-priority control to 1 

  enable_interrupt();
  clearDisplay();
  display_image(0, display);
}