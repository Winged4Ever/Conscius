#include <curses.h>
#include "myhead.h"
/*Include Sleep function*/
#include <windows.h>
#include <assert.h>

/*'Matrix' is made of 80x24 characters + one '\n' on each of the line*/
char asciiTerminal[WIDTH][HEIGHT];
char username;

int main()
{
	initscr();
	wclear(stdscr);
	drawInterface();
//	if (userLogin() != EXIT)
//	{
		unlockInterface();
		getch();
//		playGame(&username);
//	}
	lockInterface();
	endwin();
	return 0;
}
/*End of main*/

/*Syntax: drawInterface()*/
void drawInterface()
{
	/*Turn the visibility of the cursor for the animation time*/
	curs_set(0);
	neonAnimation(. . . LOADING . . ., 18);
	Sleep (60);
	arrayTheArt();
	invardLineSlide(18, print);
	ejectAnimation(19, down);
	Sleep (60);
	ejectAnimation(17, up);
	/*Set the cursor inside the commanding area*/
	CUR;
	curs_set(1);
}
/*End of drawInterface*/

/*Syntax: invardLineSlide(line, print/clear)*/
void f_invardLineSlide(int line, char* whattodo)
{
	int j = WIDTH-1, i;
	
	/*Will print chosen line from 'borders' of the line, inwards*/
	if (strcmp(whattodo, "print") == 0)
	{
		for (i = 0; i != j; i++)
		{
			move(line,i);
			printw("%c",asciiTerminal[i][line-1]);
			move(line,j);
			printw("%c",asciiTerminal[j][line-1]);
			wrefresh(stdscr);
			j--;
			Sleep (10);
		}
		int center = WIDTH/2;
		move(line, center);
		printw("%c",asciiTerminal[center][line-1]);
	}
	/*Will clear chosen line from 'borders' of the line, inwards*/
	else if (strcmp(whattodo, "clear") == 0)
	{
		for (i = 0; i != j; i++)
		{
			move(line,i);
			printw(" ");
			move(line,j);
			printw(" ");
			wrefresh(stdscr);
			j--;
			Sleep (10);
		}
		int center = WIDTH/2;
		move(line,center);
		printw(" ");
	}
	else
	{
		perror ("Invalid option");
		assert(!TRUE);
	}
	wrefresh(stdscr);
}
/*End of invardLineSlide*/

/*Syntax: neonAnimation(text, in what line)*/
void f_neonAnimation(char* text, int line)
{
	int length = 0, i, origin = 0;
	
	/*Calculate string length*/
	while(text[length] != '\0')
	{
		length++;
	}
	origin = 40 - (length/2);
	
	/*Print it on the center of chosen line*/
	for (i = 0; i <= length; i++)
	{
		move(line, origin+i);
		printw("%c", text[i]);
		wrefresh(stdscr);
		Sleep (40);
	}
	i = 0;
	
	/*De-print it*/
	for (i = 0; i <= length; i++)
	{
		move(line, origin+i);
		printw(" ");
		wrefresh(stdscr);
		Sleep (40);
	}
}
/*End of f_neonAnimation*/

/*Syntax: arrayTheArt()*/
void arrayTheArt()
{
	/*Really don't know why it has to be 82, but in any other case it just 
	 * doesn't work*/
	char translate[82];
//	memset(translate, '\0', sizeof(translate));
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
/*End of arrayTheFile*/

/*Syntax: printLine(line from loaded array)*/
void printLine(int whatLine)
{
	int i = 0;
	
	/*Loads to the buffer one chosen row from the array*/
	for (i = 0; i <= 81; i++)
	{
		printw("%c",asciiTerminal[i][whatLine]);
	}
}
/*End of printLine*/

/*Syntax: moveAndPrint(what row, what line)*/
/*This will print chosen line from preloaded asciiTerminal array into chosen
 row in the terminal (but it will not refresh the window itself)*/
void moveAndPrint(int where, int whatLine)
{
	move (where, 0);
	/*-1 cause of the fact that arrays begins from position 0*/
	printLine(whatLine-1);
}
/*End of moveAndPrint*/

/*Syntax: ejectAnimation(from which line, in what direction)*/
void f_ejectAnimation(int from, char* direction)
{
	int z = 0, j = 0, counter = 0, linesLeft = 0;
	
	if (strcmp(direction, "down") == 0)
	{
		linesLeft = (HEIGHT - from + 1);
		
		/*E.g. if 'from' = 17, the first printing step will print out in 17th
		 row the content of 24th line, and on the next step - 17|23 and 18|24,
		 and on the third step - 17|22, 18|23. 19|24, and so on, till it will
		 reach the last terminal's row*/
		for (counter = 0; counter < linesLeft; counter++)
		{
			for (z = 0; z <= j; z++)
			{
				moveAndPrint((from + z), (HEIGHT - j + z));
			}
			z = 0;
			j++;
			wrefresh(stdscr);
			/*Wait some time before printing next animation's step*/
			Sleep (60);
		}
	}
	else if (strcmp(direction, "up") == 0)
	{
		linesLeft = from;
		
		/*E.g. if 'from' = 17, the first printing step will print out in 17th
		 row the content of 1st line, and on the next step - 17|2 and 16|1,
		 and on the third step - 17|3, 16|2. 15|3, and so on, till it will
		 reach the first terminal's row*/
		for (counter = 0; counter < linesLeft; counter++)
		{
			for (z = 0; z <= j; z++)
			{
				moveAndPrint((from - z), (1 + j - z));
			}
			z = 0;
			j++;
			wrefresh(stdscr);
			/*Wait some time before printing next animation's step*/
			Sleep (33);
		}
	}
	/*If provided an unknown direction*/
	else
	{
		perror ("Invalid direction");
		assert(!TRUE);
	}
}
/*End of ejectAnimation*/

/*Syntax: pushAnimation(to which line, in what direction)*/
void f_pushAnimation(int to, char* direction)
{
	int j;
	
	if (strcmp(direction, "down") == 0)
	{
		/*Do it till whole area will be covered with lines with white chars*/
		for (j = 0; j <= to; j++)
		{
			moveAndPrint(j, 25);
			/*Reload one animation step*/
			wrefresh(stdscr);
			/*Wait some time before printing next animation's step*/
			Sleep (60);
		}	
	}
	else if (strcmp(direction, "up") == 0)
	{
		/*Do it till whole area will be covered with lines with white chars*/
		for (j = 24; j >= to; j--)
		{
			moveAndPrint(j, 25);
			/*Reload one animation step*/
			wrefresh(stdscr);
			/*Wait some time before printing next animation's step*/
			Sleep (60);
		}	
	}
	/*If provided an unknown direction*/
	else
	{
		perror ("Invalid direction");
		assert(!TRUE);
	}
}
/*End of pushAnimation*/

/*Syntax: unlockInterface()*/
void unlockInterface()
{
	/*Turn off visibility of the cursor until end of this animation*/
	curs_set(0);
	int row, i, k, z, j, m = 43;
	
	/*Move '=( @' till it reaches the last '-' char*/
	for (i = 35; i >= 5; i--)
	{
		m++;
		for (row = 1; row <= 15; row += 2)
		{
			k = 0;
			/*4, because of (4+1) characters are moving(1 white char at the 
			 end of every step)*/
			for (z = 0; z <=4; z++)
			{
				if (z == 4)
				{
					asciiTerminal[i+k][row] = ' ';
					asciiTerminal[m-k][row] = ' ';
				}
				else
				{
					asciiTerminal[i+k][row] = asciiTerminal[i+k+1][row];
					asciiTerminal[m-k][row] = asciiTerminal[m-(k+1)][row];
				}
				k++;
			}
		}
		/*Print those lines every step*/
		for (j = 2; j <= 16; j += 2)
		{
			moveAndPrint(j,j);
		}
		wrefresh(stdscr);
		Sleep (30);
	}
	/*Make the cursor visible again and set it onto default position*/
	CUR;
	curs_set(1);
}
/*End of unlockInterface*/

/*Syntax: lockInterface()*/
void lockInterface()
{
	/*Turn off visibility of the cursor, this time permamently*/
	curs_set(0);
	int row, i, k, z, j, m = 75;
	
	/*Move '=( @' till it reaches the center*/
	for (i = 5; i <= 35; i++)
	{
		m--;
		/*Do it for all rows*/
		for (row = 1; row <= 15; row += 2)
		{
			k = 4;
			/*4, because of (4+1) characters are moving(1 '-' char at the 
			 beginning of every step)*/
			for (z = 0; z <= 4; z++)
			{
				if (z == 4)
				{
					asciiTerminal[i+k][row] = '-';
					asciiTerminal[m-k][row] = '-';
				}
				else
				{
					asciiTerminal[i+k][row] = asciiTerminal[i+(k-1)][row];
					asciiTerminal[m-k][row] = asciiTerminal[m-(k-1)][row];
				}
				k--;
			}
		}
		/*Print those lines every step*/
		for (j = 2; j <= 16; j += 2)
		{
			moveAndPrint(j,j);
		}
		/*Reload buffer each step*/
		wrefresh(stdscr);
		Sleep (30);
	}
	/*Other closing animations*/
	pushAnimation(17, down);
	pushAnimation(19, up);
	invardLineSlide(18, clear);
}
/*End of lockInterface*/

