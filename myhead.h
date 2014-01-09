/*
 * File:   myhead.h
 * Author: Martin Winged
 */

#ifndef MYHEAD_H_
#define MYHEAD_H_

void    drawInterface();
void    f_invardArrayLineSlide(int, char*);
void    neonAnimation(char*, int);
int     stringLength(char*);
void    arrayTheArt();
void    printLine(int);
void    printFrom(int, int, char*);
void    printAndWriteFrom(int, char*);
void    moveAndPrint(int, int);
void    f_ejectAnimation(int, char*);
void    f_pushAnimation(int, char*);
void    unlockInterface();
void    lockInterface();
int     mainTerminal();
int     userIdentify();
int     readPassword(char*);
void    clearTerminal();
int     checkUsername(char*);
int     checkPassword(char*);
int     createAccount();
void    showCommanderInfo(char*, int);
void    clearLine(int);
void    clearCommander(int);
void    f_showHelp(char*);
void    silenceOn();
void    silenceOff();
void    closeInterface();
int     playGame();
void    f_displaySense(char*, char*);
int     firstTimePlayed();
int     saveGame();
void    showTutorial();
void    printCenter(int, char*, int);
int     identifyMenu();
void    aboutGame();
void    invardTextLineSlide(int, char*);
void    cutAndPrint(int, int, int, char*);
int     twoChoices(int, char*, char*);
void    thrillerAnimation(char*, char*, int);
int     loadGame();
void    waitingArrows();

/*Check what's inside numerical (D) or string (S) variable*/
#define DC(Var) (mvprintw(23, 4, "vCheck: " #Var "= %d", Var));getch();clearLine(23);wrefresh(stdscr);
#define SC(Var) (mvprintw(23, 4, "vCheck: " #Var "= %s", Var));getch();clearLine(23);wrefresh(stdscr);

#define ejectAnimation(a,b)         f_ejectAnimation(a,#b)
#define pushAnimation(a,b)          f_pushAnimation(a,#b)
#define invardArrayLineSlide(a,b)   f_invardArrayLineSlide(a,#b)
#define showHelp(a)                 f_showHelp(#a)
#define displaySense(a,b)           f_displaySense(#a, b)

#define EXIT        2
#define HEIGHT      25
#define WIDTH       80
#define TSPEED      5
#define FASTSPEED   20
#define NORMSPEED   50
#define SLOWSPEED   80
#define WAIT        1000

extern char asciiTerminal[WIDTH][HEIGHT];
extern char username[20], pass[20];
extern int curX, curY;

#endif
