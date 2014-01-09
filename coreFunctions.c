/*
 * File:   coreFunctions.c
 * Author: Martin Winged
 */

#include <curses.h>
#include "myhead.h"
#include <windows.h>
#include <assert.h>

int curX, curY;

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

/*Syntax: invardTextLineSlide(line, "text to print")*/
/*Stylish animation of one line of text*/
void invardTextLineSlide(int line, char* whatToPrint)
{
	int j, i, length, begin;
    length = stringLength(whatToPrint);
    /*Check parity of length*/
    if (length%2 == 1)
    {
        j = 40 + ((length+1)/2);
    }
    else
    {
        j = 40 + (length/2);
    }
    i = 40 - (length/2);
    /*Will print chosen line from 'borders' of the line, inwards*/
    for (begin = 0; begin <= length; begin++)
    {
        move(line,i);
        printw("%c",whatToPrint[begin]);
        move(line,j);
        printw("%c",whatToPrint[length]);
        wrefresh(stdscr);
        Sleep (FASTSPEED);
        length--;
        j--;
        i++;
    }
}
/*End of invardTextLineSlide*/

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
	for (i = 0; i <= WIDTH-1; i++)
	{
		printw("%c",asciiTerminal[i][whatLine]);
	}
}
/*End of printLine*/

/*Syntax: printFrom(20, 34, "clear"/"otherstring")*/
/*Same as mvprintw(); but in addition, it prints the background array too*/
void printFrom(int row, int column, char* text)
{
	int i = 0, length = 0;

	length = stringLength(text);

	/*Let's first clear what has been written here*/
	move(row, 0);
	for (i = 0; i <= WIDTH-1; i++)
	{
		printw("%c", asciiTerminal[i][row-1]);
	}

	/*And now write what we wan't to write there*/
	move(row, column);
	for (i = 0; i <= length; i++)
	{
		printw("%c", text[i]);
		wrefresh(stdscr);
		Sleep (TSPEED);
	}
	/*Move the cursor back to the place where it was*/
	move (curY, curX);
}
/*End of printFrom*/

/*Syntax: invardArrayLineSlide(line, print/clear)*/
/*Stylish animation of one line of array*/
void f_invardArrayLineSlide(int line, char* whatToDo)
{
	int j = WIDTH, i;

	/*Will print chosen line from 'borders' of the line, inwards*/
	if (strcmp(whatToDo, "print") == 0)
	{
		for (i = 0; i <= j; i++)
		{
			move(line,i);
			printw("%c",asciiTerminal[i][line-1]);
			move(line,j);
			printw("%c",asciiTerminal[j][line-1]);
			wrefresh(stdscr);
			j--;
			Sleep (FASTSPEED);
		}
		int center = WIDTH/2;
		move(line, center);
		printw("%c",asciiTerminal[center][line-1]);
	}
	/*Will clear chosen line from 'borders' of the line, inwards*/
	else if (strcmp(whatToDo, "clear") == 0)
	{
		for (i = 0; i <= j; i++)
		{
			move(line,i);
			printw(" ");
			move(line,j);
			printw(" ");
			wrefresh(stdscr);
			j--;
			Sleep (FASTSPEED);
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
/*End of invardArrayLineSlide*/

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
		Sleep (NORMSPEED);
	}
	i = 0;

	/*De-print it*/
	for (i = 0; i <= length; i++)
	{
		move(line, origin+i);
		printw(" ");
		wrefresh(stdscr);
		Sleep (NORMSPEED);
	}
}
/*End of neonAnimation*/

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
	move(row, 0);
	for (i = 0; i <= WIDTH-1; i++)
	{
		printw("%c", asciiTerminal[i][row-1]);
	}
	/*And now write what we wan't to write there*/
	move(row, 4);
	for (i = 0; i <= length; i++)
	{
        printw("%c", text[i]);
		wrefresh(stdscr);
		Sleep (TSPEED);
	}
    /*Storage the cursor's position in order to make printFrom place the cursor
    in the right place*/
	move(row,4 + i-1);
	getyx(curscr, curY, curX);
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
	int whichLine = 0;

    silenceOn();
	for (whichLine = 0; whichLine <= 23; whichLine++)
	{
        clearLine(whichLine);
	}
	wrefresh(stdscr);
	silenceOff();
}
/*End of clearTerminal*/

/*Syntax: showCommanderInfo("Your fot size don't match", 1);*/
/*It shows provided message clearing whole commanding area and then printing it
 *there, and then waiting for key press (0 turns of waiting, and 2 turns on
 *automatic waiting).*/
void showCommanderInfo(char* textToShow, int wantToWait)
{
	silenceOn();
	clearCommander(0);
	int length;
	length = stringLength(textToShow);

    /*Make sure the text will fit in 3 lines*/
    if (length > 210)
    {
		perror ("The string is to long to display");
		assert(!TRUE);
    }
    /*If the string will fit in one line*/
	if (length <= 70)
    {
        printFrom(20, 4, textToShow);
    }
    /*If the string won't fit in one line*/
    else
    {
        int iS = 0, iP = 0, line = 20;
        char textToPrint[70];
        /*Copy 70 chars into another string in order to print it later*/
        while (iS <= 69)
        {
            textToPrint[iP] = textToShow[iS];
            iS++;
            iP++;
        }
        /*In order to not cut words into pieces*/
        /*If the next char would NOT be a white char*/
        while (textToShow[iS] != ' ')
        {
            /*Head back till it will reach white char*/
            textToPrint[iP] = '\0';
            iP--;
            iS--;
            assert(iP > 0);
        }
        printFrom(line, 4, textToPrint);
        line++;
        /*If the string won't fit in two lines*/
        if (length > 140)
        {
            iP = 0;
            /*Skip white char*/
            iS++;
            /*Beginning from current char (i), copy 70 chars into another string
            in order to print it later*/
            while (iS <= 140)
            {
                textToPrint[iP] = textToShow[iS];
                iP++;
                iS++;
            }
            /*In order to not cut words into pieces*/
            /*If the next char would NOT be a white char*/
            while (textToShow[iS] != ' ')
            {
                /*Head back till it will reach white char*/
                textToPrint[iP] = '\0';
                iP--;
                iS--;
                assert(iP > 0);
            }
            printFrom(line, 4, textToPrint);
            line++;
            iP = 0;
            /*Skip white char*/
            iS++;
            /*Print remaining text*/
            while (iS <= length)
            {
                /*If the text would not be printer even than*/
                if (iP > 69)
                {
                    textToPrint[69] = '/';
                    break;
                }
                textToPrint[iP] = textToShow[iS];
                iS++;
                iP++;
            }
            printFrom(line, 4, textToPrint);
        }
        /*If the string will fit in two lines*/
        else
        {
            iP = 0;
            /*Print remaining text, skip white char*/
            iS++;
            while (iS <= length)
            {
                /*If the text would not be printed even than, print what can be
                printed*/
                if (iP > 69)
                {
                    textToPrint[69] = '/';
                    break;
                }
                textToPrint[iP] = textToShow[iS];
                iS++;
                iP++;
            }
            printFrom(line, 4, textToPrint);
        }
    }
	wrefresh(stdscr);
	if (wantToWait == 1)
    {
        waitingArrows();
        clearCommander(0);
    }
    else if (wantToWait == 2)
    {
        Sleep (WAIT);
        clearCommander(0);
    }
	silenceOff();
}
/*End of showCommanderInfo*/

/*Syntax: clearLine(line);*/
/*Clears line by printing background array on top of everything*/
void clearLine(int whichLine)
{
	int i = 0;

	move(whichLine, 0);
	for (i = 0; i <= WIDTH; i++)
	{
		printw("%c", asciiTerminal[i][whichLine-1]);
	}
	wrefresh(stdscr);
}
/*End of clearLine*/

/*Syntax: waitingArrows()*/
/*This will display arrows animation on the right bottom part of console*/
void waitingArrows()
{
    silenceOn();
    int c = 0, i = 67, k;
    flushinp();
    timeout (0);
    while (1 == 1)
    {
        for (k = 1; k < 6; k++)
        {
            c = getch();
            if (c == 10) break;
            if (k%2 == 1)
            {
                mvprintw(23, i, ">");
            }
            else
            {
                mvprintw(23, i, " ");
                i++;
                Sleep(NORMSPEED);
                mvprintw(23, i, " ");
            }
            i++;
            wrefresh(stdscr);
            c = getch();
            if (c == 10) break;
            Sleep(NORMSPEED);
        }
        if (c == 10) break;
        i -= 8;
        for (k = 1; k <= 9; k++)
        {
            c = getch();
            if (c == 10) break;
            mvprintw(23, i, " ");
            i++;
            wrefresh(stdscr);
            Sleep(NORMSPEED);
        }
        if (c == 10) break;
        i -= 8;
    }
    timeout (-1);
    silenceOff();
    clearLine(23);
}

/*Syntax: clearCommander(0);*/
/*This will clear only the commanding area, if 1 instead of 0 - will wait for
 *key press*/
void clearCommander(int wantToWait)
{
    if (wantToWait == 1)
    {
        waitingArrows();
    }
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

/*Syntax: displaySense(hearing, "Something is scratching the doors behind me")*/
/*This function is similar to showCommanderInfo, but rewritten to fit senses
 *lines*/
void f_displaySense(char* whatSense, char* textToShow)
{
	silenceOn();
	int length, whatLine, half;
	length = stringLength(textToShow);

    if (strcmp(whatSense, "hearing") == 0)
    {
        whatLine = 2;
    }
    else if (strcmp(whatSense, "sight") == 0)
    {
        whatLine = 4;
    }
    else if (strcmp(whatSense, "pain") == 0)
    {
        whatLine = 6;
    }
    else if (strcmp(whatSense, "smell") == 0)
    {
        whatLine = 8;
    }
    else if (strcmp(whatSense, "balance") == 0)
    {
        whatLine = 10;
    }
    else if (strcmp(whatSense, "touch") == 0)
    {
        whatLine = 12;
    }
    else if (strcmp(whatSense, "taste") == 0)
    {
        whatLine = 14;
    }
    else if (strcmp(whatSense, "other") == 0)
    {
        whatLine = 16;
    }
    /*If mistyped the sense*/
    else
    {
		perror ("Provided sense is not in senses speck");
		assert(!TRUE);
    }

    /*Make sure the text will fit in 2 lines*/
    if (length > 120)
    {
		perror ("The string is to long to display");
		assert(!TRUE);
    }
    /*If the string will fit in one line*/
	if (length <= 60)
    {
        /*Center it and then print*/
        half = stringLength(textToShow)/2;
        printFrom(whatLine, (WIDTH/2) - half, textToShow);
    }
    /*If the string won't fit in one line*/
    else
    {
        int iS = 0, iP = 0;
        char textToPrint[60];
        /*Copy 60 chars into another string in order to print it later*/
        while (iS <= 59)
        {
            textToPrint[iP] = textToShow[iS];
            iS++;
            iP++;
        }
        /*In order to not cut words into pieces*/
        /*If the next char would NOT be a white char*/
        while (textToShow[iS] != ' ')
        {
            /*Head back till it will reach white char*/
            textToPrint[iP] = '\0';
            iP--;
            iS--;
            assert(iP > 0);
        }
        half = stringLength(textToPrint)/2;
        printFrom(whatLine, (WIDTH/2) - half, textToPrint);
        whatLine++;
        iP = 0;
        /*Skip white char*/
        iS++;
        /*Print remaining text*/
        while (iS <= length)
        {
            /*If the text would not be printed even than, print what can be
            printed*/
            if (iP > 59)
            {
                textToPrint[59] = '/';
                break;
            }
            textToPrint[iP] = textToShow[iS];
            iS++;
            iP++;
        }
        half = stringLength(textToPrint)/2;
        printFrom(whatLine, (WIDTH/2) - half, textToPrint);
    }
	silenceOff();
}
/*End of f_displaySense*/

/*Syntax: printCenter(20, "Menu", 0);*/
/*if last number is 1, it will appear with animation*/
void printCenter(int line, char* whatToPrint, int wantToAnim)
{
	int i = 0, origin = 0, length = 0;

	length = stringLength(whatToPrint);
	origin = 40 - (length/2);

	/*Print it on the center of chosen line*/
	if (wantToAnim == 1)
    {
        for (i = 0; i <= length; i++)
        {
            move(line, origin+i);
            printw("%c", whatToPrint[i]);
            wrefresh(stdscr);
            Sleep (TSPEED);
        }
    }
    else
    {
        for (i = 0; i <= length; i++)
        {
            move(line, origin+i);
            printw("%c", whatToPrint[i]);
        }
        wrefresh(stdscr);
    }
}
/*End of printCenter*/

/*Syntax: twoChoices(22, "Yes", "No");*/
/*Prints quick choice menu*/
int twoChoices(int line, char* choice1, char* choice2)
{
    silenceOn();
    int posAct = 1;
    int input = 0;
    const short int posMin = 1;
    const short int posMax = 2;

    clearLine(line);
    cutAndPrint(line, 2, 1, choice1);
    cutAndPrint(line, 2, 2, choice2);
    wrefresh(stdscr);

    /*Repeating menu loop*/
    while (1 == 1)
    {
        silenceOn();

        input = 0;
        /*Text appearance loop*/
        while (1 == 1)
        {
            if (input == KEY_RIGHT)
            {
                posAct++;
            }
            else if (input == KEY_LEFT)
            {
                posAct--;
            }
            /*If ENTER is pressed, exit the loop*/
            else if (input == 10)
            {
                break;
            }
            /*In case if moved outside the min and max boundary*/
            if (posAct > posMax)
            {
                posAct = posMax;
            }
            else if (posAct < posMin)
            {
                posAct = posMin;
            }
            /*Change the text appearance*/
            switch(posAct)
            {
                case 1:
                    attron(A_REVERSE);
                    cutAndPrint(line, 2, 1, choice1);
                    attroff(A_REVERSE);
                    cutAndPrint(line, 2, 2, choice2);
                    wrefresh(stdscr);
                    break;
                case 2:
                    cutAndPrint(line, 2, 1, choice1);
                    attron(A_REVERSE);
                    cutAndPrint(line, 2, 2, choice2);
                    attroff(A_REVERSE);
                    wrefresh(stdscr);
                    break;
            }
            /*Wait for input*/
            flushinp();
            input = getch();
        }
        switch (posAct)
        {
            case 1:
                clearLine(line);
                return TRUE;
                break;
            case 2:
                clearLine(line);
                return FALSE;
                break;
        }
    }
	return FALSE;
    silenceOff();
}
/*End of twoChoices*/

/*Syntax: splitAndPrint(2,1, "Yes");*/
/*The command above will cut the area of the line into 2 equal distances and
then print on chosen cut "Yes"*/
void cutAndPrint(int line, int howMany, int onWhatCut, char* textToPrint)
{
    assert (howMany <= 79);
    int length = stringLength(textToPrint);
    mvprintw(line, WIDTH/(howMany+1)*onWhatCut - (length/2), textToPrint);
}
/*End of splitAndPrint*/

/*Syntax: thrillerAnimation("Logging in", "Logged in");*/
void thrillerAnimation(char* text1, char* text2, int howManyDots)
{
    silenceOn();
    clearCommander(0);
    int length, i, length2;
    length = stringLength(text1);
    length2 = stringLength(text2);

    for (i = 4; i <= length+4; i++)
    {
        mvprintw(20, i, "%c", text1[i-4]);
        wrefresh(stdscr);
        Sleep (FASTSPEED);
    }
    mvprintw(20, i, ": ");
    wrefresh(stdscr);
    Sleep(FASTSPEED);
    i += 2;

    int j, k;
    for (k = 0; k < howManyDots; k++)
    {
        for (j = 0; j <= 5; j++)
        {
            if (j%2 == 0)
            {
                mvprintw(20, i, ".");
            }
            else
            {
                mvprintw(20, i, " ");
            }
            i++;
            wrefresh(stdscr);
            Sleep(SLOWSPEED);
        }
        i -= 6;
        for (j = 0; j <= 5; j++)
        {
                mvprintw(20, i, " ");
            i++;
            wrefresh(stdscr);
            Sleep(SLOWSPEED);
        }
        i -= 6;
    }
    for (i = 4 + length + 3; i <= 4 + length + 2 + length2; i++)
    {
        mvprintw(20, i, "%c", text2[i- (4 + length + 3)]);
        wrefresh(stdscr);
        Sleep (FASTSPEED);
    }
    timeout (0);
    for (i = 0; i <= 9; i++)
    {
        j = getch();
        if (j == 10) break;
        Sleep (WAIT/10);
    }
    timeout (-1);
    clearTerminal();
    silenceOff();
}
/*End of thrillerAnimation*/
