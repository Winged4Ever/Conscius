#include <curses.h>

int main()
{
	initscr();
	wclear(stdscr);

	getch();
	endwin();
	return 0;
}

