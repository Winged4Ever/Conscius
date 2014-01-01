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
	drawInterface();
	if (mainTerminal() != EXIT)
	{
		unlockInterface();
		playGame();
		clearTerminal();
		lockInterface();
	}
	closeInterface();
	endwin();
	return 0;
}
/*End of main*/

