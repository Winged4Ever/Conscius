#include <curses.h>
#include "myhead.h"
//#include <string.h>

/*Matrix is made of 80x24 characters + one '\n' on each of the line*/
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
	endwin();
	return 0;
}
/*End of main*/

void drawInterface()
{
	arrayTheArt();
	moveAndPrint(18, 18);
	ejectAnimation(19, down);
	ejectAnimation(17, up);
	move(20,7);
}
/*End of drawInterface*/

void arrayTheArt()
{
	/*Really don't know why it has to be 82, but in any other case it just 
	 * doesn't work*/
	static char translate[82];
	static int i = 0, j = 0;
	
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

/*This function will print chosen line from loaded array*/
void printLine(int curLine)
{
	static int i = 0;
	for (i; asciiTerminal[i][curLine] != '\n'; i++)
	{
		printw("%c",asciiTerminal[i][curLine]);
	}
}
/*End of printLine*/

/*Syntax: moveAndPrint(where, what line)*/
void moveAndPrint(int where, int what)
{
	move (where, 0);
	printLine(what);
}
/*End of moveAndPrint*/

/*Syntax: ejectAnimation(from which line, in what direction)*/
void f_ejectAnimation(int from, char* direction)
{
	static int i = 0, z = 0, j = 0, counter = 0, linesLeft = 0;
	if (strcmp(direction, "down") == 0)
	{
		linesLeft = (HEIGHT - from + 1);
		for (counter; counter <= linesLeft; counter++)
		{
			for (z; z <= j; z++)
			{
				moveAndPrint((from + z), (HEIGHT - j + z));
			}
			z = 0;
			j++;
			wrefresh(stdscr);
			SLEEP (100);
		}
	}
	else if (strcmp(direction, "up") == 0)
	{
		linesLeft = from;
		for (counter; counter <= linesLeft; counter++)
		{
			for (z; z <= j; z++)
			{
				moveAndPrint((from - z), (1 + j - z));
			}
			z = 0;
			j++;
			wrefresh(stdscr);
			SLEEP (100);
		}
	}
}
/*End of ejectAnimation*/

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

int checkUsername(char* username)
{
	static int found;

	if (found == TRUE)
	{
		return TRUE;
	}
	return FALSE;
}
/*End of checkUsername*/

int checkPassword(char* username)
{
	static int found;

	if (found == TRUE)
	{
		return TRUE;
	}
	return FALSE;
}

void createAccount()
{
	/*TODO: Exclude the usage of words : exit, create*/
	cleanMind();

}
/*End of createAccount*/

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
