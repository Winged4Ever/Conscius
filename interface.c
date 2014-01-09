/*
 * File:   main.c
 * Author: Martin Winged
 */

#include <curses.h>
#include "myhead.h"
#include <windows.h>
#include <assert.h>

char asciiTerminal[WIDTH][HEIGHT];
char username[20], pass[20];

/*Syntax: drawInterface()*/
/*Draws the interface from asciiTerminal array*/
void drawInterface()
{
	/*Turn the visibility of the cursor for the animation time*/
	silenceOn();
	neonAnimation(". . . LOADING . . .", 18);
	arrayTheArt();
	invardArrayLineSlide(18, print);
	ejectAnimation(19, down);
    Sleep (NORMSPEED);
	ejectAnimation(17, up);
	/*Set the cursor inside the commanding area*/
	silenceOff();
}
/*End of drawInterface*/

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
		    /*Wait some time before printing next animation's step*/
            Sleep (NORMSPEED);
			for (z = 0; z <= j; z++)
			{
				moveAndPrint((from + z), (HEIGHT - j + z));
			}
			z = 0;
			j++;
            wrefresh(stdscr);
		}
		/*A little, lazy patch*/
        mvprintw(24, 79, "+");
        wrefresh(stdscr);
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
			Sleep (NORMSPEED);
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
			Sleep (NORMSPEED);
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
			Sleep (NORMSPEED);
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
	for (i = 35; i >= 4; i--)
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
		Sleep (FASTSPEED);
	}
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
	for (i = 5; i <= 36; i++)
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
		Sleep (FASTSPEED);
	}
	silenceOff();
}
/*End of lockInterface*/

/*Syntax: mainTerminal()*/
/*Main menu*/
int mainTerminal()
{
    char opt1[] = "Identify";
    char opt2[] = "About";
    char opt3[] = "Exit";
    int posAct = 1;
    int input = 0;
    const short int posMin = 1;
    const short int posMax = 3;

    clearCommander(0);

    /*Repeating menu loop*/
    while (1 == 1)
    {
        silenceOn();
        /*Let the text be created! Every time!*/
        invardTextLineSlide(20, opt1);
        invardTextLineSlide(21, opt2);
        invardTextLineSlide(22, opt3);
        input = 0;
        /*Text appearance loop*/
        while (1 == 1)
        {
            if (input == KEY_UP)
            {
                posAct--;
            }
            else if (input == KEY_DOWN)
            {
                posAct++;
            }
            /*If ENTER is pressed, exit the loop*/
            else if (input == 10)
            {
                break;
            }
            /*In case if moved outside the min and max boundary*/
            if (posAct > posMax)
            {
                posAct = posMin;
            }
            else if (posAct < posMin)
            {
                posAct = posMax;
            }
            /*Change the text appearance*/
            switch(posAct)
            {
                case 1:
                    attron(A_REVERSE);
                    printCenter(20, opt1, 0);
                    attroff(A_REVERSE);
                    printCenter(21, opt2, 0);
                    printCenter(22, opt3, 0);
                    break;
                case 2:
                    printCenter(20, opt1, 0);
                    attron(A_REVERSE);
                    printCenter(21, opt2, 0);
                    attroff(A_REVERSE);
                    printCenter(22, opt3, 0);
                    break;
                case 3:
                    printCenter(20, opt1, 0);
                    printCenter(21, opt2, 0);
                    attron(A_REVERSE);
                    printCenter(22, opt3, 0);
                    attroff(A_REVERSE);
                    break;
            }
            /*Wait for input*/
            flushinp();
            input = getch();
        }
        switch (posAct)
        {
            case 1:
                /*If the player has successfully logged in*/
                if (identifyMenu() == TRUE)
                {
                    return 0;
                }
                /*If the player has created a new account or left that menu*/
                clearCommander(0);
                break;
            case 2:
                aboutGame();
                clearCommander(0);
                break;
            case 3:
                clearCommander(0);
                return EXIT;
                break;
        }
        /*Run this menu again*/
        continue;
    }
	return 0;
}
/*End of mainTerminal*/

/*Derived sub-menu of main menu*/
int identifyMenu()
{
    char opt1[] = "Existing profile";
    char opt2[] = "New profile";
    char opt3[] = "Back";
    int posAct = 1;
    int input = 0;
    const short int posMin = 1;
    const short int posMax = 3;

    clearCommander(0);

    /*Repeating menu loop*/
    while (1 == 1)
    {
        silenceOn();
        /*Let the text be created!*/
        invardTextLineSlide(20, opt1);
        invardTextLineSlide(21, opt2);
        invardTextLineSlide(22, opt3);
        input = 0;
        /*Text appearance loop*/
        while (1 == 1)
        {
            if (input == KEY_UP)
            {
                posAct--;
            }
            else if (input == KEY_DOWN)
            {
                posAct++;
            }
            /*If ENTER is pressed, exit the loop*/
            else if (input == 10)
            {
                break;
            }
            /*In case if moved outside the min and max boundary*/
            if (posAct > posMax)
            {
                posAct = posMin;
            }
            else if (posAct < posMin)
            {
                posAct = posMax;
            }
            /*Change the text appearance*/
            switch(posAct)
            {
                case 1:
                    attron(A_REVERSE);
                    printCenter(20, opt1, 0);
                    attroff(A_REVERSE);
                    printCenter(21, opt2, 0);
                    printCenter(22, opt3, 0);
                    break;
                case 2:
                    printCenter(20, opt1, 0);
                    attron(A_REVERSE);
                    printCenter(21, opt2, 0);
                    attroff(A_REVERSE);
                    printCenter(22, opt3, 0);
                    break;
                case 3:
                    printCenter(20, opt1, 0);
                    printCenter(21, opt2, 0);
                    attron(A_REVERSE);
                    printCenter(22, opt3, 0);
                    attroff(A_REVERSE);
                    break;
            }
            /*Wait for input*/
            flushinp();
            input = getch();
        }
        switch (posAct)
        {
            case 1:
                /*If the player has successfully logged in*/
                if (userIdentify() == TRUE)
                {
                    return TRUE;
                }
                /*If the player has just left that menu*/
                clearCommander(0);
                break;
            case 2:
                createAccount();
                clearCommander(0);
                break;
            case 3:
                return 0;
                break;
        }
        /*Run this menu again*/
        continue;
    }
	return 0;
}
/*End of identifyMenu*/

int mainTerminal_text()
{
	char prompt[20];

	while (1 == 1)
	{
		clearCommander(0);
		/*Print info about help*/
        printAndWriteFrom(20, "> ");
		printFrom(22, 6, "Type 'help' to display help entry");

		/*Wait for input*/
		flushinp();
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
				clearCommander(0);
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
			showCommanderInfo("Unknown command", 1);
		}
	}
	return 0;
}
/*End of mainTerminal_bu*/

/*Syntax: userIdentify()*/
/*Identifying phase in menu*/
int userIdentify()
{
	extern char username[20];
	char prompt[20];

	clearCommander(0);
	silenceOff();

	/*Username step*/
	while (1 == 1)
	{
		printAndWriteFrom(20, "Username: ");
		printFrom(22, 4, "Type 'exit' to break identifying process ");
		/*Wait for input*/
		flushinp();
		getstr(prompt);
		/*If the player would like to exit the logging menu*/
		if (strcmp(prompt, "exit") == 0)
		{
			break;
		}
		/*If provided username do not exist*/
		else if (checkUsername(prompt) == FALSE)
		{
			thrillerAnimation("Inconsistency detected", "Invalid username, try "
                     "again", 1);
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
		clearCommander(0);
		while (1 == 1)
		{
			printAndWriteFrom(20, "Password: ");

			readPassword(prompt);
			if (strcmp(prompt, "exit") == 0)
			{
				showCommanderInfo("Identifying has being canceled",1 );
				break;
			}
			if (checkPassword(prompt) == FALSE)
			{
				thrillerAnimation("Inconsistency detected", "Invalid password, "
                      "try again", 1);
				continue;
			}
			/*If player had successfully logged in*/
			else
			{
				thrillerAnimation("Logging in", "Successfully logged in", 1);
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
    silenceOff();
	char found[20], check[20];
	memset(found, '\0', sizeof(found));
	memset(check, '\0', sizeof(found));
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
    /*TODO: Check if provided account currently exist*/
	char prompt[20], temp_pass[20], temp_username[20];

	clearCommander(0);
	silenceOff();

	while (1 == 1)
	{
		/*Username step*/
        printAndWriteFrom(20, "Type your username: ");
		printFrom(22, 4, "Type 'exit' to break identifying process ");

        flushinp();
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
		clearCommander(0);
		while (1 == 1)
		{
            printAndWriteFrom(20, "Type your password: ");
			printFrom(22, 4, "Your password should be 4 - 20 characters long");

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
						showCommanderInfo("Account creation has being canceled", 1);
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
									"created", 1);
						}
						fclose (pFile);
						return 0;
					}
					/*If entered password don't match*/
					else
					{
						showCommanderInfo("Passwords don't match", 1);
						break;
					}
				}
			}
			else
			{
				showCommanderInfo("Account creation has being canceled", 1);
				break;
			}
		}
		break;
	}
	return 0;
}
/*End of createAccount*/

/*Syntax showHelp(aboutWhat)*/
/*It shows help info about chosen part of program*/
void f_showHelp(char* aboutWhat)
{
	silenceOn();
	clearCommander(0);
	/*If called from mainTerminal function*/
	if (strcmp(aboutWhat, " ") == 0)
	{
		printFrom(20, 4, " ");
		wrefresh(stdscr);
	}
	/*If passed invalid help menu*/
	else
	{
		perror("Invalid help menu");
		assert(!TRUE);
	}
	/*Wait till key is being pressed*/
	flushinp();
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
	invardArrayLineSlide(18, clear);
}
/*End of closeInterface*/

/*Derived sub-menu of main menu*/
void aboutGame()
{

}
/*End of aboutGame*/
