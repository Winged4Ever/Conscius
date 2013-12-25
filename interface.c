#include <curses.h>
#include "myhead.h"
/*Include Sleep function*/
#include <windows.h>

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
//		unlockInterface(&asciiTerminal);
//		playGame(&username);
//	}
//	lockInterface(&asciiTerminal);
	getch();
	endwin();
	return 0;
}
/*End of main*/

/*Syntax: drawInterface()*/
void drawInterface()
{
	arrayTheArt();
	moveAndPrint(18, 18);
	wrefresh(stdscr);
	ejectAnimation(19, down);
	ejectAnimation(17, up);
	/*TODO: Finish this function*/
	move(20,6);
}
/*End of drawInterface*/

/*Syntax: arrayTheArt()*/
void arrayTheArt()
{
	/*Really don't know why it has to be 82, but in any other case it just 
	 * doesn't work*/
	char translate[82];
	int i = 0, j = 0;
	
	FILE *pFile = fopen ("asciiart.txt" , "r");
	/*If file cannot be opened, show an error*/
	if (pFile == NULL) perror ("Error opening file");
	else
	{
		/*While still not the end of the file*/
		while(fgets (translate, sizeof(translate) ,pFile) != !EOF)
		{
			/*Set the termination character as a last char*/
			translate[WIDTH] = '\0';
			/*While loop hasn't reached it yet*/
			while (translate[i] != '\0')
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

/*Syntax: moveAndPrint(where, what line)*/
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
			Sleep (40);
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
			Sleep (40);
		}
	}
}
/*End of ejectAnimation*/

/*Syntax: */
int userLogin()
{
	char prompt;

	cleanMind();
	while (1 == 1)
	{
		/*TODO: Each time this loop begins, it should overwrite the line*/
		/*TODO: Turn off terminal's history of entered values*/
		printf("Username: ");
		fgets (prompt , 20 , stdin);
		/*If the player would like to exit the game without loggining in*/
		if (strcmp(prompt, "exit") == 0)
			{
				break;
			}
		/*If the player would like to create a new account*/
		if (strcmp(prompt, "create") == 0)
		{
			createAccount();
			continue;
		}
		/*If provided username do not exist*/
		if (checkUsername(&prompt) == FALSE)
		{
			terminalPrint(i1,"Ivalid username, try again");
			continue;
		}
		strcpy(username, prompt);
		/*If provided username exist*/
		while (1 == 1)
		{
			/*TODO: Each time this loop begins, it should overwrite the line*/
			/*TODO: stars instead of visible password*/
			printf("Password: ");
			fgets (prompt , 20 , stdin);
			if (strcmp(prompt, "exit") == 0)
				{
					break;
				}
			if (checkPassword(&prompt) == FALSE)
			{
				terminalPrint(i1,"Ivalid password, try again");
				continue;
			}
			return 0;
		}
	}
	return EXIT;
}
/*End of userLogin*/

/*Syntax: */
int checkUsername(char* username)
{
	int found;

	if (found == TRUE)
	{
		return TRUE;
	}
	return FALSE;
}
/*End of checkUsername*/

/*Syntax: */
int checkPassword(char* username)
{
	int found;

	if (found == TRUE)
	{
		return TRUE;
	}
	return FALSE;
}

/*Syntax: */
void createAccount()
{
	/*TODO: Exclude the usage of words : exit, create*/
	cleanMind();

}
/*End of createAccount*/

/*Syntax: */
void unlockInterface()
{

}
/*End of unlockInterface*/

/*This function will print things in the terminal*/
/*Syntax: terminalPrint(place, "string");*/
void f_terminalPrint(char *where, char *string)
{
	/*Hearing area*/
	if (strcmp(where, "@") == 0)
	{

	}
	/*First line of input center*/
	if (strcmp(where, "i1") == 0)
	{

	}
}
/*End of f_terminalPrint1*/

/*Syntax: cleanMind();*/
void cleanMind()
{

}
/*End of cleanMind*/

void lockInterface()
{
	cleanMind();

}
/*End of lockInterface*/