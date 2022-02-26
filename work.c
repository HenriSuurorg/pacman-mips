#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int count = 0;

char textstring[] = "text, more text, and even more text!";

int getbtns( void ){
  int r;
  r = (PORTF >> 1) & 0x1; // check button 1
  r = r | ((PORTD >> 4) & 0xE); // check button 2-4

  return r&0xF;
}

/* Interrupt Service Routine */
void user_isr( void )
{
    IFSCLR(0) = (1 << 8);
    count++;

    if(count == 50){
      clearDisplay();
      display_image(0, display);
      count = 0;
    }

    int btns = getbtns();

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

/* Lab-specific initialization goes here */
void labinit( void )
{
  TRISD = TRISD & 0xf01f;
  TRISD += 0xfe0;
  TRISF = TRISF | (0x20);

  T2CONSET = 0 << 15; // turn timer on
  TMR2 = 0; // set timer to 0
  T2CONSET = 0x70; // set the prescaling to 1:256 
  PR2 = 31250; // set period
  IFSCLR(0) = 1 << 8; // set timer interupt flag to 0
  T2CONSET = 1 << 15; // start the timer
  IECSET(0) = (1 << 8); // timer 2 interrupt enable to 1 
  IPCSET(2) = 0x1f; // set timer2 interrupt priority and sub-priority control to 1 

  enable_interrupt();

  clearDisplay();
  display_image(0, display);
}

/* This function is called repetitively from the main program */
void labwork( void )
{
}
