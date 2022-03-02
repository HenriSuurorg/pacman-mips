#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
void *stdin, *stdout, *stderr;

int movementClock = 0;

void moveGhost(int x, int y);

void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}


entity pacman = {.x = 1, .y = 1, .dir = 'e'};

entity ghost1 = {.x = 60, .y = 8, .dir = 'w'};
entity ghost2 = {.x = 60, .y = 8, .dir = 'e'};
entity ghost3 = {.x = 60, .y = 8, .dir = 's'};

int nofGhosts = 3;
entity ghosts[3] = {
  {.x = 60, .y = 8, .dir = 'w'},
  {.x = 60, .y = 8, .dir = 'e'},
  {.x = 60, .y = 8, .dir = 's'}};


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
  clearDisplay();
  checkButtons();

  if(movementClock == 2){
    movementClock = 0;
    if(checkCollisionWithWall(pacman.dir, &pacman) == 0) updatePacman();
    checkCollisionWithOrb(&pacman);
    movePacman(pacman.x, pacman.y, pacman.dir);

    int i;
    for (i = 0; i < nofGhosts; i++) updateGhost(&ghosts[i]);

    display2dToArray();
    addWallsAndOrbs();
    display_image(0, display);
  } 
  movementClock++;

  IFSCLR(0) = (1 << 8);
}