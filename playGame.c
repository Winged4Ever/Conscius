/*
 * File:   playGame.c
 * Author: Martin Winged
 */

#include <curses.h>
#include "myhead.h"
#include <windows.h>
#include <assert.h>

char input[20];

int playGame()
{
    if (firstTimePlayed() == TRUE)
    {
        thrillerAnimation("Checking progress", "No previous signs of data", 1);
        showTutorial();
    }
    else
    {
        thrillerAnimation("Checking progress", "Progress has been loaded", 1);
        loadGame();
    }
    showCommanderInfo("Function is in build", 2);
    return 0;
}
/*End of playGame*/

int firstTimePlayed()
{
    return TRUE;
}
/*End of firstTimePlayed*/


void showTutorial()
{
    showCommanderInfo("Hi! It seems that it's your first time inside Conscius."
                      " I suggest you taking a short tutorial tour in order to"
                      " know the mechanical way that this game works.", 1);
    printCenter(20, "Do you want to undergo the introducing training?", 1);
    if (twoChoices(22, "Yes", "No") == FALSE)
    {
        showCommanderInfo("In that case have nice and profound adventures!", 2);
        unlockInterface();
    }
    else
    {
//        thrillerAnimation("Connecting with supervisor", "Connected", 2);
        showCommanderInfo("Oh, hi there! I'll speak to you soon, I just need to"
                          " do one quick... thing. Take this for now:", 0);
        unlockInterface();
        displaySense(hearing, "HEARING");
        displaySense(sight, "SIGHT");
        displaySense(pain, "PAIN");
        displaySense(smell, "SMELL");
        displaySense(balance, "BALANCE");
        displaySense(touch, "TOUCH");
        displaySense(taste, "TASTE");
        displaySense(other, "THOUGHTS AND OTHER SENSES");
        clearCommander(1);
    }
}
/*End of showTutorial*/

int loadGame()
{
    return 0;
}
/*End of loadGame*/
