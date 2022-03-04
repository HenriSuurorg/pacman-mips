#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int endOfGame(entity pacman){
    gameState = 5;
    livesAtTheEndOfTheGame = pacman.lives;
    return ((pacman.lives == 0) || (score >= 1870)); 
    // Game end condition -> if pacman loses all lives or if pacman manages to collect all orbs 
    //(177; each orb= +10 score)
}

void BonusCalculator(entity pacman){
    if(score >= 1870 ){
    int bonusMultiplier = 100;
    int finalScore = score + (bonusMultiplier * pacman.lives);
    }  
}