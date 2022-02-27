#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

/* quicksleep:
   A simple function to create a small delay.
   Very inefficient use of computing resources,
   but very handy in some special cases. */
void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

pman pacman = {.x = 0, .y = 0};

void checkButtons(){
  int btns; 
  btns = (PORTF >> 1) & 0x1; // check button 1
  btns = btns | ((PORTD >> 4) & 0xE); // check button 2-4

  if (btns){
    if(btns & 0x8){
      clearDisplay();
      pacman.x = pacman.x - 1;
      displayPacman(pacman.x, pacman.y);
    }

    if(btns & 0x4){
      clearDisplay();
      pacman.y = pacman.y - 1;
      displayPacman(pacman.x, pacman.y);
    }
    
    if(btns & 0x2){
      clearDisplay();
      pacman.y = pacman.y + 1;
      displayPacman(pacman.x, pacman.y);
    }

    if(btns & 0x1){
      clearDisplay();
      pacman.x = pacman.x + 1;
      displayPacman(pacman.x, pacman.y);
    }
  }
}

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