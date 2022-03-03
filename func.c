#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
void *stdin, *stdout, *stderr;

void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

int movementClock = 0;
int gameState = 0;

entity pacman = {.x = 1, .y = 1, .dir = 'e', .lives = 3};

int nofGhosts = 3;
entity ghosts[3] = {
  {.x = 60, .y = 8, .dir = 'w', .lives = 1},
  {.x = 60, .y = 8, .dir = 'e', .lives = 1},
  {.x = 60, .y = 8, .dir = 's', .lives = 1}};


int btn1, btn2, btn3, btn4;
void checkButtons(){
  int btns; 
  btns = (PORTF >> 1) & 0x1; // check button 1
  btns = btns | ((PORTD >> 4) & 0xE); // check button 2-4

  btn1 = 0;
  btn2 = 0;
  btn3 = 0;
  btn4 = 0;

  if (btns){
    if(btns & 0x8) btn4 = 1;
    else if(btns & 0x4) btn3 = 1;
    else if(btns & 0x2) btn2 = 1;
    else if(btns & 0x1) btn1 = 1;
  }
}

void game(){
    int i;

    movementClock = 0;
    updatePacman(&pacman);
    checkCollisionWithOrb(&pacman);
    for (i = 0; i < nofGhosts; i++) checkCollisionWithGhost(&pacman, &ghosts[i]);
    movePacman(pacman.x, pacman.y, pacman.dir);

    for (i = 0; i < nofGhosts; i++) updateGhost(&ghosts[i]);

    display2dToArray();
    addWallsAndOrbs();
    display_image(0, display);
}


/* Interrupt Service Routine */
void user_isr( void )
{
  clearDisplay();
  checkButtons();

  if(gameState == 0) menu(); // menu
  else if(gameState == 1) instructions(); // instructions 
  else if(gameState == 2) credits(); // credits
  else if(gameState == 3 && movementClock == 2) game();
  else if(gameState == 4){credits();} // game over
  else if (gameState == 5)gameState3(); // enter highscore
  else{gameState3();} // view highscore
  movementClock++;

  IFSCLR(0) = (1 << 8); 
}