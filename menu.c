#include<stdio.h>
#include<stdint.h>
#include<pic32mx.h>
#include"mipslab.h"

void highscore()
{
    return;
}

int instrState = 0;
void instructions()
{
    char instructions1[4][16] = 
    {
        "EAT ALL THE     ",
        "ORBS BEFORE     ",
        "THE GHOSTS      ",
        "GET TO YOU      "
    };
    char instructions2[4][16] = 
    {
        "BTN4 - LEFT ",
        "BTN3 - RIGHT",
        "BTN2 - DOWN ",
        "BTN1 - UP   "
    };
    if (instrState == 0){
        if(btn1 || btn2 || btn3 || btn4 ) instrState = 1;
        display_string(0,instructions1[0]);
        display_string(1,instructions1[1]);
        display_string(2,instructions1[2]);
        display_string(3,instructions1[3]);
        display_update();
    }

    if (instrState == 1){
    display_string(0,instructions2[0]);
    display_string(1,instructions2[1]);
    display_string(2,instructions2[2]);
    display_string(3,instructions2[3]);
    display_update();
    instrState = 0;
    if(btn1 || btn2 || btn3 || btn4 ) gameState = 0;
    }
}
void credits()
{
    char options[4][16] = 
    {
        "ADITYA GUPTA    ",
        "HENRI J SUURORG ",
        "                ",
        "ANY BTN -> EXIT "
    };

    display_string(0,options[0]);
    display_string(1,options[1]);
    display_string(2,options[2]);
    display_string(3,options[3]);
    display_update();

  if(btn1 | btn2 | btn3 | btn4) gameState = 0;
}

 void menu() // add this code the existing main in form of menu function call
{
    checkButtons();
    char options[4][16] = 
    {
        "B1->PLAY        ",
        "B2->HIGHSCORE   ",
        "B3->CREDITS     ",
        "B4->INSTRUCTIONS"
    };

    display_string(0,options[0]);
    display_string(1,options[1]);
    display_string(2,options[2]);
    display_string(3,options[3]);
    display_update();
    
    if(btn1 == 1){
        gameState = 3;
    }
    else if(btn2 == 1){
        gameState = 6;
    }
    else if(btn3 == 1){
        gameState = 2;
    }
    else if(btn4 == 1){
        gameState = 1;
    }
    }