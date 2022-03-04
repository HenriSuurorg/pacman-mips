#include<stdio.h>
#include<stdint.h>
#include<pic32mx.h>
#include"mipslab.h"

char highscore_Name[16] = "aaa             ";
char* highscoreName()
{
    char alphabets[26] = 
    {'a','b','c','d','e','f','g','h','i','j','k','l',
    'm','n','o','p','q','r','s','t','u','v','w','x',
    'y','z'};

    int i=0, a=0;
    //int btnbool=0;
        // int btnFlag1 = 0;
        // int btnFlag2 = 0;
        // int btnFlag3 = 0;
        // int btnFlag4 = 0;
    while (i < 3){
        // display_string(0, highscore_Name);
        // display_update();
        checkButtons();
        display_string(0, highscore_Name);
        display_string(2, "B4 UP | B3 DOWN");
        display_string(3, "B2 Y  | B1 N   ");
        display_update();

        if(btn4 == 1){
            // btn4count++;
            // a += btn4count;
            a++;
            if (a > 25){
                a = 0;
            }
            highscore_Name[i] = alphabets[a%26];
            while (btn4 == 1){
            checkButtons();
        }
            // display_string(0, highscore_Name);
            // display_update();
        }
        if(btn3 == 1){
            // btn3count++;
            // a -= btn3count; 
            a--;
            if(a < 0){
                a = 25;
            }
            highscore_Name[i] = alphabets[a%26];
            while (btn3 == 1){
                checkButtons();
            }
        }
        if(btn2 == 1){
            a = 0;
            i++;
            while (btn2 == 1){
                checkButtons();
            }
        }
        if(btn1  == 1 && i > 0){
            a = 0;
            i--;
            while (btn1 == 1){
            checkButtons();
            }
        }
    }
    if (i == 3) 
    //     highscoreStringSaved = highscore_Name; 
        return highscore_Name;
}
void highscore(){
    // int i;
    // for(i = 0;i < 3;i++){
        // highscoreNames[i][16] = highscoreName();
    //}
    static int highscoreIndex = 0;
    
    highscoresNames[highscoreIndex++] = highscoreName();

    if (highscoreIndex > 3)
        highscoreIndex = 0;

    gameState = 0;
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

//   if(btn1 | btn2 | btn3 | btn4) gameState = 0;
if(btn1 == 1){
        gameState = 0;
        while (btn1 == 1){
            checkButtons();
        }
    }
    else if(btn2 == 1){
        gameState = 0;
        while (btn2 == 1){
            checkButtons();
        }
    }
    else if(btn3 == 1){
        gameState = 0;
        while (btn3 == 1){
            checkButtons();
        }
    }
    else if(btn4 == 1){
        gameState = 0;
        while (btn4 == 1){
            checkButtons();
        }
    }
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
        while (btn1 == 1){
            checkButtons();
        }
    }
    else if(btn2 == 1){
        gameState = 6;
        while (btn2 == 1){
            checkButtons();
        }
    }
    else if(btn3 == 1){
        gameState = 2;
        while (btn3 == 1){
            checkButtons();
        }
    }
    else if(btn4 == 1){
        gameState = 1;
        while (btn4 == 1){
            checkButtons();
        }
    }
}