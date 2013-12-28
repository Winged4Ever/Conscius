/* 
 * File:   coreFunctions.c
 * Author: Martin Winged
 */

#include <curses.h>
#include "myhead.h"
#include <windows.h>
#include <assert.h>

/*Syntax: stringLength(var/"abc")*/
/*Measures provided string's length*/
int stringLength(char* text)
{
	int length = 0;
	while(text[length] != '\0')
	{
		length++;
	}
	return length;
}
/*End of stringLength*/

/*Syntax: arrayTheArt()*/
/*Translates file (for now only "asciiart.txt" into array*/
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
/*End of arrayTheFile*/

/*Syntax: printLine(line from loaded array)*/
/*It's printing on current position, chosen line from asciiTerminal array*/
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

/*Syntax: printFrom(20, 34, "clear"/"otherstring")*/
/*Same as mvprintw();*/
void printFrom(int row, int column, char* text)
{
	int i = 0, length = 0;

	length = stringLength(text);
	/*TODO: Temporary solution for too long strings, need to refine it*/
	if (length > 70)
	{
		length = 70;
	}
	
	/*Let's first clear what has been written here*/
	move(row, column);
	for (i = 0; i <= WIDTH-1; i++)
	{
		printw("%c", asciiTerminal[column+i][row-1]);
	}
	
	/*And now write what we wan't to write there*/
	move(row, column);
	for (i = 0; i <= length; i++)
	{
		printw("%c", text[i]);
	}
}
/*End of printFrom*/

/*Syntax: printAndWriteFrom(20, "string")*/
/*This function additionally moves the cursor just behind the string that has
 *been just printed*/
void printAndWriteFrom(int row, char* text)
{
	int i = 0, length = 0;

	length = stringLength(text);
	/*TODO: Temporary solution for too long strings, need to refine it*/
	if (length > 70)
	{
		length = 70;
	}
	
	/*Let's first clear what has been written here*/
	move(row, 4);
	for (i = 0; i <= WIDTH-1; i++)
	{
		printw("%c", asciiTerminal[4+i][row-1]);
	}
	
	/*And now write what we wan't to write there*/
	move(row, 4);
	for (i = 0; i <= length; i++)
	{
		printw("%c", text[i]);
	}
	move(row,4 + i);
	wrefresh(stdscr);
}
/*End of printAndWriteFrom*/

/*Syntax: moveAndPrint(what row, what line)*/
/*Move to chosen line, than print chosen line from asciiTerminal*/
/*This will print chosen line from preloaded asciiTerminal array into chosen
 row in the terminal (but it will not refresh the window itself)*/
void moveAndPrint(int where, int whatLine)
{
	move (where, 0);
	/*-1 cause of the fact that arrays begins from position 0*/
	printLine(whatLine-1);
}
/*End of moveAndPrint*/

/*Syntax: readPassword(&prompt)*/
/*It reads user's input and save it to 'pass' variable while showing only 
 * star symbols*/
int readPassword(char* password)
{
	int x = 0, y = 0;
	
	/*Echo off, so no entered characters would be shown*/
	noecho();
	char c;
	int i = 0;
	
	/*Password cannot be longer than 20 chars*/
	while (1 == 1)
	{
		/*Wait for input*/
		c = getch();
		/*If ENTER is being pressed*/
		if (c == 10)
		{
			i++;
			break;
		}
		/*If BCKSPC is being pressed*/
		else if (c == 8)
		{
			/*Check if not reached zero-pos char yet*/
			if (i != 0)
			{
				/*Delete last star and back one step*/
				printw("\b ");
				getyx(curscr, y, x);
				move(y, x-1);
				i--;
				password[i] = '\0';
			}
			continue;
		}
		/*If ESC is being pressed*/
		else if (c == 27)
		{
			strcpy(password, "exit");
			return FALSE;
		}
		/*If valid key is being pressed*/
		else
		{
			/*Assign the pressed key as a part of entered password*/
			password[i] = c;
			/*Print on screen * instead of characters*/
			printw("*");
			i++;
		}
	}
	password[i] = '\n';
	/*Turn back echo on*/
	echo();
	return TRUE;
}
/*End of readPassword*/

/*Syntax: clearTerminal()*/
/*It clears whole terminal (prints background interface)*/
void clearTerminal()
{
	int i = 0, j = 0;
	
	for (j = 0; j <= 23; j++)
	{
		for (i = 0; i <= 80; i++)
		{
			printw("%c",asciiTerminal[i][j]);
		}
		wrefresh(stdscr);
		Sleep (60);
	}
}
/*End of clearTerminal*/

/*Syntax: showCommanderInfo("Your fot size don't match");*/
/*It shows provided message clearing whole commanding area and then printing it
 *there*/
void showCommanderInfo(char* whattoshow)
{
	silenceOn();
	clearCommander();
	printFrom(20, 4, whattoshow);
	wrefresh(stdscr);
	getch();
	clearCommander();
	silenceOff();
}
/*End of showCommanderInfo*/

/*Syntax: clearLine(line);*/
/*Clears line by printing background array on top of everything*/
void clearLine(int whichline)
{
	int i = 0;
	
	move(whichline, 0);
	for (i = 0; i <= WIDTH-1; i++)
	{
		printw("%c", asciiTerminal[0+i][whichline-1]);
	}
	wrefresh(stdscr);
}
/*End of clearLine*/

/*Syntax: clearCommander();*/
/*This will clear only the commanding area*/
void clearCommander()
{
	clearLine(20);
	clearLine(21);
	clearLine(22);
}
/*End of clearCommander*/

/*Syntax: silenceOn();*/
/*Turns off echo and cursor visibility*/
void silenceOn()
{
	noecho();
	curs_set(0);
}
/*End of silenceOn*/

/*Syntax: silenceOff();*/
/*Turns on echo and cursor visibility*/
void silenceOff()
{
	echo();
	curs_set(1);
}
/*End of silenceOff*/

/*Syntax: checkPassword(&prompt)*/
/*Compares provided string with 'pass' variable*/
int checkPassword(char* password)
{
	/*If provided password match*/
	if (strcmp(pass, password) == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	return 0;
}