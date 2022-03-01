#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

void chooseRandomDir(char dir, entity *ghost){
    char allDirs[4] = {'e', 'w', 's', 'n'};
    char availableDirs[3];

    int i;    
    int j = 0;
    for (i = 0; i < 4; i++){
        char cur = allDirs[i];
        if(checkCollisionWithWall(cur, ghost) == 0) {
            availableDirs[j++] = cur;
            ghost->dir = cur;
        }
    }
}

void updateGhost(entity *ghost){
    char dir = ghost -> dir;
    if (checkCollisionWithWall(ghost -> dir, ghost) == 1) chooseRandomDir(dir, ghost);

    if(dir == 'e'){
        ghost->x = ghost->x + 1;
        moveGhost(ghost->x, ghost->y);
    }
    else if(dir == 'w'){
        ghost->x = ghost->x - 1;
        moveGhost(ghost->x, ghost->y);
    }
    else if(dir == 's'){
        ghost->y = ghost->y + 1;
        moveGhost(ghost->x, ghost->y);
    }
    else {
        ghost->y = ghost->y - 1;
    moveGhost(ghost->x, ghost->y);
  }
}