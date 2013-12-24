#include <curses.h>
#include <stdlib.h>
#include "myhead.h"
#include <stdio.h>

int main()
{
	initscr();
	wclear(stdscr);

	getch();
	endwin();
	return 0;
}