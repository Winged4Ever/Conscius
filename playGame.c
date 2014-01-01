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
    displaySense(hearing, "Test #1");
    displaySense(sight, "Test #2 : This text is supposed to be longer than "
                 "60 characters to test the feature of cutting into two lines");
    getch();
}
