/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 
   This file modified 2021-02-16 by Henri J. Suurorg

   For copyright and licensing, see file COPYING */
 
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;
int count = 0;
int prime = 1234567;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  if(IFS(0) & (1 << 8)){
  IFSCLR(0) = (1 << 8);
  count++;
  }

  if(IFS(0) & (1 << 15)){
    IFSCLR(0) = (1 << 15);
    (PORTE)++;
    clearDisplay();
    setDisplay2d(5, 5, 20, 5);
    display2dToArray();
    display_image(0, display);
  ;}
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  TRISE = TRISE & 0xffffff00;
  TRISD = TRISD & 0xf01f;
  TRISD += 0xfe0;

  /* turn the timer off to start off with the correct values */
  T2CONSET = 0 << 15;

  /* reset the value of the timer to 0 */
  TMR2 = 0;

  /* set the prescaling to 1:256 - the largest possible  
  (bits 4-6 of T2CONSET are responsible for prescaling) */
  T2CONSET = 0x70;

  /* Prescaling is 1:256 so we have 80 000 000 / 256 = 312 500 for 1s.
  We want 0.1s so we devide 312 500 by 10 to get 31 250  */
  PR2 = 31250;

  /* We reset the timer interrupt flag so it start out at 0 */
  IFSCLR(0) = 1 << 8;

  /* start the timer again, now with the correct values */
  T2CONSET = 1 << 15;

  /* set timer 2 interrupt enable to 1 */
  IECSET(0) = (1 << 8);
  /* set switch 3 interrupt enable to 1 */
  IECSET(0) = (1 << 15);

  /* set interrupt priority and sub-priority control to 1 
  (this is the only interrupt, so shouldn't really matter) */
  IPCSET(2) = 0x1f;
  IPCSET(3) = 0x1f;

  /* enable interrupts on the cpu */
  enable_interrupt();

}

/* This function is called repetitively from the main program */
void labwork( void )
{
}
