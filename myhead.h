#ifndef MYHEAD_H_
#define MYHEAD_H_

void    drawInterface();
void    arrayTheArt();
void    printLine(int);
void    moveAndPrint(int, int);
void    f_ejectAnimation(int, char*);
int     userLogin();
int     checkUsername(char);
int     checkPassword(char);
void    createAccount();
void    unlockInterface();
void    f_terminalPrint(char, char);
void    cleanMind();
void    lockInterface();
int     playGame(char);

#define terminalPrint(a,b)	f_terminalPrint(#a,b)
#define ejectAnimation(a,b)     f_ejectAnimation(a,#b)

#define EXIT    2
#define HEIGHT  24
#define WIDTH   81

extern char v_asciiTerminal[81][24];

#endif
