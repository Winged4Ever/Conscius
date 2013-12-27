#include <curses.h>
#include "myhead.h"
/*Include Sleep function*/
#include <windows.h>
#include <assert.h>

/*'Matrix' is made of 80x24 characters + one '\n' on each of the line*/
char asciiTerminal[WIDTH][HEIGHT];
char username[20], pass[20];

int main()
{
	initscr();
	wresize(stdscr, 24, 80);
	wclear(stdscr);
	drawInterface();
	if (mainTerminal() != EXIT)
	{
		unlockInterface();
		playGame();
	}
	lockInterface();
	endwin();
	return 0;
}
/*End of main*/

/*Syntax: drawInterface()*/
void drawInterface()
{
	/*Turn the visibility of the cursor for the animation time*/
	silenceOn();
	neonAnimation(". . . LOADING . . .", 18);
	Sleep (60);
	arrayTheArt();
	invardLineSlide(18, print);
	Sleep (60);
	ejectAnimation(19, down);
	Sleep (60);
	ejectAnimation(17, up);
	/*Set the cursor inside the commanding area*/
	printAndWriteFrom(20, 4, "> ");
	silenceOff();
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

/*Syntax: neonAnimation("text", in what line)*/
void neonAnimation(char* text, int line)
{
	int i = 0, origin = 0, length = 0;
	
	length = stringLength(text);
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
/*End of neonAnimation*/

/*Syntax: stringLength(var/"abc")*/
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
void printFrom(int row, int column, char* text)
{
	int i = 0, length = 0;
	
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
		move(row, column);
		for (i = 0; i <= WIDTH-1; i++)
		{
			printw("%c", asciiTerminal[column+i-1][row-1]);
		}
		
		/*And now write what we wan't to write there*/
		move(row, column);
		for (i = 0; i <= length; i++)
		{
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
	printAndWriteFrom(20, 4, "> ");
}
/*End of printFrom*/

/*Syntax: printAndWriteFrom(20, 34, "clear"/"otherstring")*/
/*This function additionally moves the cursor just behind the string*/
void printAndWriteFrom(int row, int column, char* text)
{
	int i = 0, length = 0;
	
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
		move(row, column);
		for (i = 0; i <= WIDTH-1; i++)
		{
			printw("%c", asciiTerminal[column+i-1][row-1]);
		}
		
		/*And now write what we wan't to write there*/
		move(row, column);
		for (i = 0; i <= length; i++)
		{
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
	move(row,column + i);
}
/*End of printAndWriteFrom*/

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
	int j = 0;
	
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
	silenceOn();
	int row = 0, i = 0, k = 0, z = 0, j = 0, m = 43;
	
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
	printAndWriteFrom(20, 4, "> ");
	silenceOff();
}
/*End of unlockInterface*/

/*Syntax: lockInterface()*/
void lockInterface()
{
	/*Turn off visibility of the cursor, this time permamently*/
	silenceOn();
	int row = 0, i = 0, k = 0, z = 0, j = 0, m = 75;
	
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

/*Syntax: mainTerminal()*/
int mainTerminal()
{	
	char prompt[20];
	memset (prompt, '\0', sizeof(prompt));
	silenceOff();
	while (1 == 1)
	{
		/*Print info about help*/
		printFrom(22, 6, "Type 'help' to display help entry");
		wrefresh(stdscr);
		/*Wait for input*/
		getstr(prompt);

		/*If the player would like to identify himself*/
		if (strcmp(prompt, "identify") == 0)
			{
				/*If the player has successfully logged in*/
				if (userIdentify() == TRUE)
				{
					return 0;
				}
				continue;
			}
		/*If the player would like to read help entry*/
		else if (strcmp(prompt, "help") == 0)
			{
				showHelp(mainTerminal);
				continue;
			}
		/*If the player would like to exit the game*/
		else if (strcmp(prompt, "exit") == 0)
			{
				clearCommander();
				return EXIT;
			}
		/*If the player would like to create a new account*/
		else if (strcmp(prompt, "create") == 0)
		{
			createAccount();
			continue;
		}
		/*If the player typed unknown command*/
		else
		{
			showCommanderInfo("Unknown command");
		}
	}
	return 0;
}
/*End of mainTerminal*/

/*Syntax: userIdentify()*/
int userIdentify()
{
	extern char username[20];
	char prompt[20];
	memset (prompt, '\0', sizeof(prompt));

	/*Username step*/
	while (1 == 1)	
	{
		/*Print "Username: " just after > and then move cursor behind string*/
		printAndWriteFrom(20, 6, "Username: ");
		wrefresh(stdscr);
		/*Wait for input*/
		getstr(prompt);
		prompt[21] = '\n';
		
		/*If the player would like to exit the logging menu*/
		if (strcmp(prompt, "exit") == 0)
		{
			break;
		}
		/*If provided username do not exist*/
		if (checkUsername(prompt) == FALSE)
		{
			showCommanderInfo("Invalid username, try again");
			continue;
		}
		/*If provided username exist, assign its string into 'username' variab*/
		else
		{
			int i = 0;
			for (i = 0; prompt[i] != '\0'; ++i)
			{
				username[i] = prompt[i];
			}
		}

		/*Password step*/
		while (1 == 1)
		{
			printAndWriteFrom(20, 6, "Password: ");
			wrefresh(stdscr);
			readPassword(prompt);
			if (strcmp(prompt, "exit") == 0)
			{
				break;
			}
			if (checkPassword(prompt) == FALSE)
			{
				showCommanderInfo("Invalid password, try again");
				continue;
			}
			/*If player had successfully logged in*/
			else
			{
				return TRUE;
			}
		}
		break;
	}
	clearCommander();
	return 0;
}
/*End of userIdentify*/

/*Syntax: readPassword(&prompt)*/
void readPassword(char* password)
{
	/*Echo off, so no entered characters would be shown*/
	noecho();
	char c;
	int i = 0;
	
	/*Password cannot be longer than 20 chars*/
	for (i = 1; i <= 20; i++)
	{
		/*Wait for input*/
		c = getc(stdin);
		/*If ENTER is being pressed*/
		if (c == '\n')
		{
			break;
		}
		/*If BCKSPC is being pressed*/
		else if (c == 8)
		{
			/*Delete last star*/
			printw("\b ");
			continue;
		}
		/*If ESC is being pressed*/
		else if (c == 27)
		{
			strcpy(password, "exit");
			break;;
		}
		/*If valid key is being pressed*/
		else
		{
			/*Assign the pressed key as a part of entered password*/
			password[i-1] = c;
			/*Print on screen * instead of characters*/
			printw("*");
		}
	}
	password[i] = '\n';
	/*Turn back echo on*/
	echo();
}
/*End of readPassword*/

/*Syntax: clearTerminal()*/
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

/*Syntax: checkUsername(&prompt)*/
int checkUsername(char* username)
{
	char found[20], check[20];
	memset (found, '\0', sizeof(found));
	memset (check, '\0', sizeof(check));
	int i = 0;
	
	FILE *pFile = fopen ("accounts.dat" , "r");
	/*If file cannot be opened, show an error and then crash*/
	if (pFile == NULL)
	{
		perror ("Error opening file");
		assert(!TRUE);
	}
	else
	{
		while(fgets (found, sizeof(found) ,pFile) != !EOF)
		{
			/*Till translating does not reached terminating char yet*/
			for (i = 2; found[i] != '\n' || found[i] != '\0' ; i++)
			{
				/*Pass the actual username string to the next string variable 
				 * that will be checked*/
				check[i-2] = found[i];
			}
			/*If username match*/
			if (strcmp(check, username) == 0)
			{
				/*Get to next line and capture what is the password to this
				 account so it would be compared later while asking for pass*/
				fgets (found, sizeof(found) ,pFile);
				for (i = 2; found[i] != '\n' || found[i] != '\0' ; i++)
				{
					pass[i-2] = found[i];
				}
				return TRUE;
			}
			else
			{
				/*Skip next line (where password is stored)*/
				fgets (found, sizeof(found) ,pFile);
			}
		}
		/*When reached end of file and not found anything*/
		return FALSE;
	}
	fclose (pFile);
	return 0;
}
/*End of checkUsername*/

/*Syntax: checkPassword(&prompt)*/
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

/*Syntax: createAccount()*/
int createAccount()
{
	char prompt[20], temp_pass[20], temp_username[20];
	memset (prompt, '\0', sizeof(prompt));
	memset (temp_pass, '\0', sizeof(temp_pass));
	memset (temp_username, '\0', sizeof(temp_username));
	
	while (1 == 1)
	{
		/*Username step*/
		printFrom(20, 6, "Type your username");
		printAndWriteFrom(21, 4, "> ");
		
		
		/*Password step*/
		while (1 == 1)
		{
			printFrom(20, 6, "Type your password");
			printFrom(21, 6, "Your password should be 4 - 20 characters long");
			printAndWriteFrom(22, 4, "> ");
			readPassword(prompt);
			if (strcmp(prompt, "exit") == 0)
			{
				while (1 == 1)
					{
					strcpy(temp_pass, prompt);
					printFrom(20, 6, "Type your password again");
					printFrom(22, 6, "clear");
					printAndWriteFrom(21, 4, "> ");

					readPassword(prompt);
					if (strcmp(prompt, "exit") == 0)
					{
						break;
					}
					/*If entered password match*/
					if (strcmp(prompt, temp_pass) == 0)
					{
						/*Will form those strings adequately to other lines in
						 * accounts.dat*/
						char u[20], p[20];
						memset (u, '\0', sizeof(u));
						memset (p, '\0', sizeof(p));
						int i = 0;
						strcpy(u, "u ");
						strcpy(p, "p ");
						
						for (i = 0; temp_username[i] != '\n'; i++)
						{
							u[i+2] = temp_username[i];
						}
						temp_username[i] = '\n';
						for (i = 0; temp_pass[i] != '\n'; i++)
						{
							p[i+2] = temp_pass[i];
						}
						temp_pass[i] = '\n';
						
						/*Write at the end of file this data*/
						FILE *pFile = fopen ("accounts.dat" , "a");
						/*If file cannot be opened, show an error and then 
						 * crash*/
						if (pFile == NULL)
						{
							perror ("Error opening file");
							assert(!TRUE);
						}
						else
						{
							fputs(u, pFile);
							fputs(p, pFile);
						}
						fclose (pFile);
						return 0;
					}
					/*If entered password don't match*/
					else
					{
						showCommanderInfo("Passwords don't match");
						break;
					}
				}
			}
			break;
		}
		break;
	}
	return 0;
}
/*End of createAccount*/

/*Syntax: showCommanderInfo("Your fot size don't match");*/
void showCommanderInfo(char* whattoshow)
{
	silenceOn();
	clearCommander();
	printFrom(20, 6, whattoshow);
	wrefresh(stdscr);
	getch();
	clearCommander();
	silenceOff();
}
/*End of showCommanderInfo*/

/*Syntax: clearCommander();*/
/*This will clear only the commanding area*/
void clearCommander()
{
	printFrom(20, 1, "clear");
	printFrom(21, 1, "clear");
	printFrom(22, 1, "clear");
}
/*End of clearCommander*/

/*Syntax showHelp(aboutwhat)*/
void f_showHelp(char* aboutwhat)
{
	silenceOn();
	clearCommander();
	/*If called from mainTerminal function*/
	if (strcmp(aboutwhat, "mainTerminal") == 0)
	{
		printFrom(20, 4, "Type 'identify' to login into your existing account");
		printFrom(21, 4, "Type 'create' to create a new account");
		printFrom(22, 4, "Type 'exit' to exit the game");
		wrefresh(stdscr);
	}
	/*If passed invalid help menu*/
	else
	{
		perror("Invalid help menu");
		assert(!TRUE);
	}
	/*Wait till key is being pressed*/
	getch();
	clearCommander();
	silenceOff();

}
/*End of showHelp*/

/*Syntax: silenceOn();*/
void silenceOn()
{
	noecho();
	curs_set(0);
}
/*End of silenceOn*/

/*Syntax: silenceOff();*/
void silenceOff()
{
	echo();
	curs_set(1);
}
/*End of silenceOff*/

/*Syntax: playGame()*/
int playGame()
{
	noecho();
	printFrom(20, 4, "You're playing the game as ");
	printw("%s", username);
	getch();
	echo();
	return 0;
}
/*End of playGame*/
