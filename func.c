#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int movementClock = 0;

void moveGhost(x, y);
void movePacman(x, y);

void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}


entity pacman = {.x = 0, .y = 0, .height = 5, .width = 5, .dir = 'e'};
entity ghost1 = {.x = 5, .y = 9, .height = 5, .width = 5, .dir = 'e'};
entity ghost2 = {.x = 32, .y = 16, .height = 5, .width = 5, .dir = 'w'};

void checkButtons(){
  int btns; 
  btns = (PORTF >> 1) & 0x1; // check button 1
  btns = btns | ((PORTD >> 4) & 0xE); // check button 2-4

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
  }
}

int count = 0;
void updateGhost(entity *ghost){
  if (count % 5 == 0){
    if(ghost->dir == 'e') ghost->dir = 's';
    else if(ghost->dir == 's') ghost->dir = 'w';
    else if(ghost->dir == 'w') ghost->dir = 'n';
    else  ghost->dir = 'e';
  }
  if(ghost->dir == 'e'){
    ghost->x = ghost->x + 1;
    moveGhost(ghost->x, ghost->y);
  }
  else if(ghost->dir == 'w'){
    ghost->x = ghost->x - 1;
    moveGhost(ghost->x, ghost->y);
  }
  else if(ghost->dir == 's'){
    ghost->y = ghost->y + 1;
    moveGhost(ghost->x, ghost->y);
  }
  else {
    ghost->y = ghost->y - 1;
    moveGhost(ghost->x, ghost->y);
  }
}


void updatePacman(){
  if(pacman.dir == 'w'){
    pacman.x = pacman.x - 1;
    movePacman(pacman.x, pacman.y);
  }
  if(pacman.dir == 's'){
    pacman.y = pacman.y - 1;
    movePacman(pacman.x, pacman.y);
  }
  if(pacman.dir == 'n'){
    pacman.y = pacman.y + 1;
    movePacman(pacman.x, pacman.y);
  }
  if(pacman.dir == 'e'){
    pacman.x = pacman.x + 1;
    movePacman(pacman.x, pacman.y);
  }
}


/* Interrupt Service Routine */
void user_isr( void )
{
  IFSCLR(0) = (1 << 8);

  clearDisplay();
  checkButtons();

   if(movementClock == 4){
    movementClock = 0;
    updatePacman();
    updateGhost(&ghost1);
    updateGhost(&ghost2);
    display2dToArray();
    addWalls();
    display_image(0, display);
    count++;
  } 

  movementClock++;
}