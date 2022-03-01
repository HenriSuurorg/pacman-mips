#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int movementClock = 0;

void moveGhost(int x, int y);
void movePacman(int x, int y);

void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}


entity pacman = {.x = 1, .y = 1, .height = 5, .width = 5, .dir = 'e'};
entity ghost1 = {.x = 1, .y = 31, .height = 5, .width = 5, .dir = 'e'};
entity ghost2 = {.x = 1, .y = 1, .height = 5, .width = 5, .dir = 'w'};


void checkButtons(){
  int btns; 
  btns = (PORTF >> 1) & 0x1; // check button 1
  btns = btns | ((PORTD >> 4) & 0xE); // check button 2-4

  if (btns){
    if((btns & 0x8) && checkCollisionWithWall('w', &pacman) == 0){
      pacman.dir = 'w';
    }

    if((btns & 0x4) && checkCollisionWithWall('n', &pacman) == 0){
      pacman.dir = 'n';
    }
    
    if((btns & 0x2) && checkCollisionWithWall('s', &pacman) == 0){
      pacman.dir = 's';
    }

    if((btns & 0x1) && checkCollisionWithWall('e', &pacman) == 0){
      pacman.dir = 'e';
    }
  }
}


void updatePacman(){
  if(pacman.dir == 'w'){
    pacman.x = pacman.x - 1;
  }
  else if(pacman.dir == 's'){
    pacman.y = pacman.y + 1;
  }
  else if(pacman.dir == 'n'){
    pacman.y = pacman.y - 1;
  }
  if(pacman.dir == 'e'){
    pacman.x = pacman.x + 1;
  }
}


/* Interrupt Service Routine */
void user_isr( void )
{
  IFSCLR(0) = (1 << 8);

  clearDisplay();
  checkButtons();

  if(movementClock == 2){
    movementClock = 0;
    if(checkCollisionWithWall(pacman.dir, &pacman) == 0) updatePacman();
    movePacman(pacman.x, pacman.y);

    updateGhost(&ghost1);
    updateGhost(&ghost2);

    display2dToArray();
    addWallsAndOrbs();
    display_image(0, display);
  } 

  movementClock++;
}