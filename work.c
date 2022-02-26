#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */


/* Interrupt Service Routine */
void user_isr( void )
{
  IFSCLR(0) = (1 << 8);
  checkButtons();

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
