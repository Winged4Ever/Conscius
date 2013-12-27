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
	arrayTheArt();
	printFrom(20, 10, "11111111111111111111111111111111");
	printAndWriteFrom(21, 7, "nothing");
	getch();
	endwin();
	return 0;
}

/*Syntax: printFrom(20, 34, "clear"/"otherstring")*/
void printFrom(int row, int column, char* text)
{
	extern int length;
	int i = 0;
	
	/*If not provided 'clear' command*/
	if (strcmp(text, "clear") != 0)
	{
		length = stringLength(text);
		/*TODO: Temporary solution for too long strings, need to refine it*/
		if (length > 70)
		{
			length = 70;
		}
		
		/*Let's first clear what has been written here*/
		for (i = 0; i <= WIDTH-1; i++)
		{
			move(row, column+i);
			printw("%c", asciiTerminal[column+i-1][row-1]);
		}
		
		/*And now write what we wan't to write there*/
		for (i = 0; i <= length; i++)
		{
			move(row, column+i);
			printw("%c", text[i]);
		}
	}
	/*If want only to clear the line from this point*/
	else
	{
		move(row, column);
		for (i = 0; i <= WIDTH-1; i++)
		{
			printw("%c", asciiTerminal[column+i-1][row-1]);
		}
		wrefresh(stdscr);
	}
}
/*End of printFrom*/

/*Syntax: printAndWriteFrom(20, 34, "clear"/"otherstring")*/
/*This function additionally moves the cursor just behind the string*/
void printAndWriteFrom(int row, int column, char* text)
{
	extern int length;
	int i = 0;
	
	/*If not provided 'clear' command*/
	if (strcmp(text, "clear") != 0)
	{
		length = stringLength(text);
		/*TODO: Temporary solution for too long strings, need to refine it*/
		if (length > 70)
		{
			length = 70;
		}
		
		/*Let's first clear what has been written here*/
		for (i = 0; i <= WIDTH-1; i++)
		{
			move(row, column+i);
			printw("%c", asciiTerminal[column+i-1][row-1]);
		}
		
		/*And now write what we wan't to write there*/
		for (i = 0; i <= length; i++)
		{
			move(row, column+i);
			printw("%c", text[i]);
		}
	}
	/*If want only to clear the line from this point*/
	else
	{
		move(row, column);
		for (i = 0; i <= WIDTH-1; i++)
		{
			printw("%c", asciiTerminal[column+i-1][row-1]);
		}
		wrefresh(stdscr);
	}
	move(row,column+i);
}
/*End of printAndWriteFrom*/

void arrayTheArt()
{
	/*Really don't know why it has to be 82, but in any other case it just 
	 * doesn't work*/
	char translate[82];
	
	int i = 0, j = 0;
	
	FILE *pFile = fopen ("asciiart.txt" , "r");
	/*If file cannot be opened, show an error and then crash*/
	if (pFile == NULL)
	{
		perror ("Error opening file");
		assert(!TRUE);
	}
	else
	{
		/*While still not the end of the file*/
		while(fgets (translate, sizeof(translate) ,pFile) != !EOF)
		{
			/*Set the termination character as a last char*/
			/*While loop hasn't reached it yet*/
			while (i != WIDTH)
			{
				/*Assign current char into an appropriate array's adress*/
				asciiTerminal[i][j] = translate[i];
				/*Next char*/
				i++;
			}
			/*Next row, reset column counter*/
			i = 0;
			j++;
		}
	}
	fclose (pFile);
}

int stringLength(char* text)
{
	int length = 0;
	while(text[length] != '\0')
	{
		length++;
	}
	return length;
}
