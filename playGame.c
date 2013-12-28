/* 
 * File:   playGame.c
 * Author: Martin Winged
 */

#include <curses.h>
#include "myhead.h"
#include <windows.h>
#include <assert.h>

/*Syntax: playGame()*/
/*TODO*/
int playGame()
{
	noecho();
	printFrom(20, 4, "TEST: You've logged in as ");
	printw("%s", username);
	printFrom(21, 4, "This part of code is not completed yet, press any key "
			"to exit ");
	printFrom(22, 4, "That you for you time spent on testing this game ");
	getch();
	echo();
	return 0;
}
/*End of playGame*/

