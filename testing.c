#include <curses.h>
#include "myhead.h"
#include <string.h>
#include <assert.h>

char asciiTerminal[WIDTH][HEIGHT];
int length;

int main()
{
	initscr();
	wclear(stdscr);
	while (1)
	{
		char c = getch();
		printw("You have pressed: %d\n",c);
	}
	wrefresh(stdscr);
	endwin();
	return 0;
}

