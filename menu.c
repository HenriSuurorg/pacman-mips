#include<stdio.h>
#include<stdint.h>
#include<pic32mx.h>
#include"mipslab.h"

void highscore()
{
    char alphabets[26] = 
    {'a','b','c','d','e','f','g','h','i','j','k','l',
    'm','n','o','p','q','r','s','t','u','v','w','x',
    'y','z'};

    int i=0, a=0;
    int btnbool=0;
    char highscore_Name[3] = "aaa";
    display_string(0, "hahahahha");
    display_update();
    while (i < 3){
        display_string(1, highscore_Name);
        display_update();
        if (a >= 0 && a < 26){
            if(btn1){
                a++;
                highscore_Name[i] = alphabets[a];
                display_string(0, highscore_Name);
                display_update();
            }
            else if(btn2){
                a--; 
                highscore_Name[i] = alphabets[a];
                display_string(0, highscore_Name);
                display_update();
            }
            else if(btn3){
                a = 0;
                i++;
            }
            else if(btn4 && i > 0){
                a = 0;
                i--;
            }
        }
        else if (a < 0){
            a = 26;
        }
        else {
            a = 0;
        }
    }
/* 
    while(i < 3 ){
        if(!btnbool){
            if(a>0 && a<26){
                if(btn1){ 
                    a+=1; display_string(0,highscore_Name);display_update();
                }
                else if(btn2){
                    a-=1; display_string(0,highscore_Name);display_update();
                }
                else if(btn3){
                    highscore_Name[i] = alphabets[a];
                    btnbool = 1;
                }
                else if(btn4){
                    highscore_Name[i] = " ";
                }
            }
            else if(a<0){
                a=26;
            }
            else{
                a=0;
            }
        }
        else{
            i++;
            a=0;
            btnbool = 0;
        }
    }
    gameState = 0; */
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