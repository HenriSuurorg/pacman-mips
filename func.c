#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

void displayGhost(x, y);
void displayPacman(x, y);

void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}


entity pacman = {.x = 0, .y = 0, .height = 5, .width = 5, .dir = 'e'};

void checkButtons(){
  int btns; 
  btns = (PORTF >> 1) & 0x1; // check button 1
  btns = btns | ((PORTD >> 4) & 0xE); // check button 2-4
/*
  if (btns){
    if(btns & 0x8){
      pacman.dir = 'w';
    }

    if(btns & 0x4){
      pacman.dir = 's';
    }
    
    if(btns & 0x2){
      pacman.dir = 'n';
    }

    if(btns & 0x1){
      pacman.dir = 'e';
    }
  } */

    if (btns){
    if(btns & 0x8){
      pacman.dir = 'w';
    }

    if(btns & 0x4){
      pacman.dir = 'n';
    }
    
    if(btns & 0x2){
      pacman.dir = 's';
    }

    if(btns & 0x1){
      pacman.dir = 'e';
    }
  }
}



void updatePacman(){
  if(pacman.dir == 'w'){
    clearDisplay();
    pacman.x = pacman.x - 1;
    displayPacman(pacman.x, pacman.y);
  }
  if(pacman.dir == 's'){
    clearDisplay();
    pacman.y = pacman.y - 1;
    displayPacman(pacman.x, pacman.y);
  }
  if(pacman.dir == 'n'){
    clearDisplay();
    pacman.y = pacman.y + 1;
    displayPacman(pacman.x, pacman.y);
  }
  if(pacman.dir == 'e'){
    clearDisplay();
    pacman.x = pacman.x + 1;
    displayPacman(pacman.x, pacman.y);
  }
}


/* Interrupt Service Routine */
void user_isr( void )
{
  IFSCLR(0) = (1 << 8);
  checkButtons();
  updatePacman();
}