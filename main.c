/*
 * File:   main.c
 * Author: Winged
 *
 */

#include <curses.h>
#include "myhead.h"
#include <windows.h>
#include <assert.h>

int main()
{
	initscr();
	wclear(stdscr);
    keypad(stdscr, TRUE);
	drawInterface();
	if (mainTerminal() != EXIT)
	{
		playGame();
		/*After exiting the game*/
		clearTerminal();
		lockInterface();
	}
	closeInterface();

	endwin();
	return 0;
}
/*End of main*/

