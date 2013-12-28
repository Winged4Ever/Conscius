/* 
 * File:   main.c
 * Author: Martin Winged
 */

#include <curses.h>
#include "myhead.h"
#include <windows.h>
#include <assert.h>

/*'Matrix' is made of 80x24 characters + one '\n' on each of the line*/
char asciiTerminal[WIDTH][HEIGHT];
char username[20], pass[20];

/*Syntax: drawInterface()*/
/*Draws the interface from asciiTerminal array*/
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
	printAndWriteFrom(20, "> ");
	silenceOff();
}
/*End of drawInterface*/

/*Syntax: invardLineSlide(line, print/clear)*/
/*Stylish animation of one line*/
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
/*Even more stylish animation of provided string*/
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

/*Syntax: ejectAnimation(from which line, in what direction)*/
/*Ejecting animation from chosen line, pointed upward or downward*/
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
/*De-ejecting animation from chosen line, pointed upward or downward*/
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
/*Opening animation of upper part of terminal*/
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
	printAndWriteFrom(20, "> ");
	silenceOff();
}
/*End of unlockInterface*/

/*Syntax: lockInterface()*/
/*Closing animation of upper part of terminal*/
void lockInterface()
{
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
	silenceOff();
}
/*End of lockInterface*/

/*Syntax: mainTerminal()*/
/*Menu phase of command-receiving mechanism*/
int mainTerminal()
{	
	char prompt[20];

	while (1 == 1)
	{
		clearCommander();
		/*Print info about help*/
		printFrom(22, 6, "Type 'help' to display help entry");
		printAndWriteFrom(20, "> ");
		
		/*Wait for input*/
		fflush(stdin);
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
/*Identifying phase in menu*/
int userIdentify()
{
	extern char username[20];
	char prompt[20];

	clearCommander();

	/*Username step*/
	while (1 == 1)	
	{
		printFrom(22, 4, "Type 'exit' to break identifying process ");
		printAndWriteFrom(20, "Username: ");
		
		/*Wait for input*/
		getstr(prompt);
		/*If the player would like to exit the logging menu*/
		if (strcmp(prompt, "exit") == 0)
		{
			break;
		}
		/*If provided username do not exist*/
		else if (checkUsername(prompt) == FALSE)
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
		memset (prompt, '\0', sizeof(prompt));
		clearCommander();
		while (1 == 1)
		{
			printAndWriteFrom(20, "Password: ");
			
			readPassword(prompt);
			if (strcmp(prompt, "exit") == 0)
			{
				showCommanderInfo("Identifying has being canceled");
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
				showCommanderInfo("Successfully logged in");
				return TRUE;
			}
		}
		break;
	}
	return 0;
}
/*End of userIdentify*/

/*Syntax: checkUsername(&prompt)*/
/*Checks if provided string has been recorded in accounts.dat file as an
 *username*/
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
	/*If successfully open the file*/
	else
	{
		while(fgets (found, sizeof(found) ,pFile) != !EOF)
		{
			for (i = 2; found[i] != '\n'; i++)
			{
				/*Translate to the actual username string (without "u ") so 
				 * that it  could be checked later*/
				check[i-2] = found[i];
			}

			/*If username match*/
			if (strcmp(check, username) == 0)
			{
				/*Get to next line and capture what is the password to this
				 account so it would be compared later while asking for pass*/
				fgets (found, sizeof(found) ,pFile);
				for (i = 2; found[i] != '\n' ; i++)
				{
					pass[i-2] = found[i];
				}
				/*End string with terminating character*/
				pass[i-1] = '\n';
				return TRUE;
			}
			else
			{
				/*Skip next line (where password is stored)*/
				fgets (found, sizeof(found) ,pFile);
			}
		}
	}
	/*When reached end of file and not found anything*/
	fclose (pFile);
	return FALSE;
}
/*End of checkUsername*/

/*Syntax: createAccount()*/
/*Account creation phase*/
int createAccount()
{
	char prompt[20], temp_pass[20], temp_username[20];
	
	clearCommander();
	
	while (1 == 1)
	{
		/*Username step*/
		printFrom(22, 4, "Type 'exit' to break identifying process ");
		printAndWriteFrom(20, "Type your username: ");
		
		getstr(prompt);	
		/*If entered different string than exit*/
		if (strcmp(prompt, "exit") != 0)
		{
			strcpy(temp_username, prompt);
		}
		/*If the player want to break account creation process */
		else
		{
			break;
		}
				
		/*Password step*/
		clearCommander();
		while (1 == 1)
		{
			printFrom(22, 4, "Your password should be 4 - 20 characters long");
			printAndWriteFrom(20, "Type your password: ");
			
			readPassword(prompt);
			/*If the player haven't pressed ESC*/
			if (strcmp(prompt, "exit") != 0)
			{
				while (1 == 1)
				{
					strcpy(temp_pass, prompt);
					clearLine(22);
					printAndWriteFrom(20, "Type your password again: ");

					/*Read password again in case of mistypes*/
					readPassword(prompt);
					/*If the player had pressed ESC*/
					if (strcmp(prompt, "exit") == 0)
					{
						showCommanderInfo("Account creation has being canceled");
						break;
					}
					/*If entered password match*/
					else if (strcmp(prompt, temp_pass) == 0)
					{
						/*Will form those strings adequately to other lines in
						 * accounts.dat*/
						char u[20], p[20];
						int i = 0;
						
						strcpy(u, "u ");
						strcpy(p, "p ");
						
						for (i = 0; i <= stringLength(temp_username); i++)
						{
							u[i+2] = temp_username[i];
						}
						u[i+3] = '\n';
						
						for (i = 0; i <= stringLength(temp_pass); i++)
						{
							p[i+2] = temp_pass[i];
						}
						p[i+3] = '\n';
						
						/*Write at the end of file this data*/
						FILE *pFile = fopen ("accounts.dat" , "a");
						/*If file cannot be opened, show an error and then 
						 * crash*/
						if (pFile == NULL)
						{
							perror ("Error opening file");
							assert(!TRUE);
						}
						/*If successfully open the file*/
						else
						{
							/*Jump to the next line*/
							fputs("\n", pFile);
							fputs(u, pFile);
							/*Jump to the next line*/
							fputs("\n", pFile);
							fputs(p, pFile);
							
							showCommanderInfo("Account has been successfully "
									"created");
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
			else
			{
				showCommanderInfo("Account creation has being canceled");
				break;
			}
		}
		break;
	}
	return 0;
}
/*End of createAccount*/

/*Syntax showHelp(aboutwhat)*/
/*It shows help info about chosen part of program*/
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
	silenceOff();

}
/*End of showHelp*/

/*Syntax: closeInterface();*/
/*Closing animation of interface*/
void closeInterface()
{
	/*Turn off visibility of the cursor, this time permamently*/
	silenceOn();
	pushAnimation(17, down);
	pushAnimation(19, up);
	invardLineSlide(18, clear);
}
/*End of closeInterface*/
