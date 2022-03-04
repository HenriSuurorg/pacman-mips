#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
void *stdin, *stdout, *stderr;
int savedScores[] = {0, 0, 0, 0};
char savedScoreStrings [4][16];
int scoreClock = 0;

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
    if(nofOrbs == 0){gameState=5;}
    if (movementClock >= 5){
      scoreClock++;
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
}


void enterHighScore(){
  int i, j;
  int pos = 3;
 
  char* highscoreNames;
  highscoreNames = highscoreName();
  char posString[4] = "1234";
  int curScore = calculateScore(pacman.lives,scoreClock);
  char scoreString[4];
  sprintf(scoreString, "%d", curScore);
  char stringToSave[16] = " .              ";

  // caluculate where player should be placed on the highscore table
  for(i = 0; i < 4; i++)
    if(curScore > savedScores[i]){
      pos = i;
      break;
      }
  // Create the String that will be saved
  stringToSave[0] = posString[pos];
  for(i = 0; i < 3; i++) {
    stringToSave[3+i] = highscoreNames[i];
    stringToSave[13+i] = scoreString[i];
  }

  // move scores that the current score passes forward
  // not neccessary if the current score will be in pos 4
  if(pos < 4){
    for (i = 3; i > pos; i--){        
      savedScores[i] = savedScores[i-1];
      for(j = 0; j < 16; j++)
        savedScoreStrings[i][j] = savedScoreStrings[i-1][j];
      savedScoreStrings[i][0] = posString[i];
    }

  }
  // enter current score into right position
  savedScores[pos] = curScore;
  for (i = 0; i < 16; i++) 
    savedScoreStrings[pos][i] = stringToSave[i];
    PORTE = 0x7;
    gameState = 6;
}

void viewScore(){
    int i=0;
    for(i=0;i<4;i++){
        display_string(i,savedScoreStrings[i]);
        display_update();
    }
    if(btn1 == 1){
        gameState = 4;
        while (btn1 == 1){
            checkButtons();
        }
    }
    else if(btn2 == 1){
        gameState = 4;
        while (btn2 == 1){
            checkButtons();
        }
    }
    else if(btn3 == 1){
        gameState = 4;
        while (btn3 == 1){
            checkButtons();
        }
    }
    else if(btn4 == 1){
        gameState = 4;
        while (btn4 == 1){
            checkButtons();
        }
    }
}

void gameOver(){
    int i;
    PORTE=0x7;
    pacman.x = 1;
    pacman.y = 1;
    pacman.dir = 'e';
    pacman.lives = 3;
    for (i = 0; i < nofGhosts; i++) {
      ghosts[i].x = 60;
      ghosts[i].y = 8;
    }
    ghosts[0].dir = 'w';
    ghosts[1].dir = 'e';
    ghosts[2].dir = 's';
    orbsRemap();
    orbs2dToArray();
    score = 0;
    scoreClock = 0;
    nofOrbs = 100;
    gameState = 0;
}

/* Interrupt Service Routine */
void user_isr( void )
{
  clearDisplay();
  checkButtons();

  if(gameState == 0) menu(); // menu
  else if(gameState == 1) instructions(); // instructions 
  else if(gameState == 2) credits(); // credits
  else if(gameState == 3) game();
  else if(gameState == 4) gameOver(); // game over
  else if (gameState == 5) enterHighScore(); // enter highscore
  else viewScore(); // view highscore

  movementClock++;

  IFSCLR(0) = (1 << 8); 
}

