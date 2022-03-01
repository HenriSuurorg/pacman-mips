#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"

void moveGhost(x, y){
  int i;
  // row 1
  for (i = 1; i < 4; i++) display2d[y][x + i] = 1;
  // row 2 and 5
  for (i = 0; i < 5; i += 2) {
    display2d[y + 1][x + i] = 1;
    display2d[y + 4][x + i] = 1;
    }

  // row 3 and 4
  for (i = 0; i < 5; i++){
    display2d[y + 2][x + i] = 1;
    display2d[y + 3][x + i] = 1;
    }
}

// display 5x5 pacman
void movePacman(x, y){
  int i;
  for (i = 1; i < 5; i++) {
    display2d[y][x + i] = 1; // moves row 1
    display2d[y + 4][x + i] = 1; // moves row 5
    }
  for (i = 0; i < 4; i++){ 
    display2d[y + 1][x + i] = 1; // moves row 2
    display2d[y + 3][x + i] = 1; // moves row 4
  }
  for (i = 0; i < 3; i++) display2d[y + 2][x + i] = 1; // moves row 3
}

void labinit( void ){
  TRISD = TRISD & 0xf01f;
  TRISD += 0xfe0;
  TRISF = TRISF | (0x20);

  T2CONSET = 0 << 15; // turn timer on
  TMR2 = 0; // set timer to 0
  T2CONSET = 0x70; // set the prescaling to 1:256 
  PR2 = 31250/4; // set period to 25ms;
  IFSCLR(0) = 1 << 8; // set timer interupt flag to 0
  T2CONSET = 1 << 15; // start the timer
  IECSET(0) = (1 << 8); // timer 2 interrupt enable to 1 
  IPCSET(2) = 0x1f; // set timer2 interrupt priority and sub-priority control to 1 

  enable_interrupt();
  clearDisplay();
  display_image(0, display);
}


void display2dToArray() {
  int page, c, r;
  uint8_t powerOfTwo = 1;
  uint8_t oledN = 0;

  for(page = 0; page < 4; page++) {
    for(c = 0; c < 128; c++) {
      powerOfTwo = 1;
      oledN = 0;

      for(r = 0; r < 8; r++) {
        if(display2d[8 * page + r][c]) {
          oledN |= powerOfTwo;
        }
        powerOfTwo <<= 1;
      }
      display[c + page * 128] = oledN;
    }
  }
}

// add walls to display
void addWallsAndOrbs(){
int i;
  for (i = 0; i < 512; i++) {
    display[i] = display[i] | walls[i] | orbs[i];
  }
}

// check if entity will collide with wall
int checkCollisionWithWall(char dir, entity *ent){
  int i;
  uint8_t collisionBool = 0;

  for(i = 0; i < 4; i ++){
    if(dir == 'w'){
      collisionBool = collisionBool | walls2d[ent->y + i][ent->x - 1];
    }
    else if(dir == 's'){
      collisionBool = collisionBool | walls2d[ent->y + 5][ent->x + i];
    }
    else if(dir == 'n'){
      collisionBool = collisionBool | walls2d[ent->y - 1][ent->x + i];
    }
    else {
      collisionBool = collisionBool | walls2d[ent->y + i][ent->x + 5];
    }
  }
  return collisionBool;
}