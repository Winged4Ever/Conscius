#ifndef MYHEAD_H_
#define MYHEAD_H_

void    drawInterface();
void    arrayTheArt();
void    printLine(int);
void    moveAndPrint(int, int);
void    f_ejectAnimation(int, char*);
void    f_pushAnimation(int, char*);
int     userLogin();
int     checkUsername(char);
int     checkPassword(char);
void    createAccount();
void    unlockInterface();
void    f_terminalPrint(char, char);
void    lockInterface();
int     playGame(char);
void    f_neonAnimation(char*, int);
void    f_invardLineSlide(int, char*);

#define terminalPrint(a,b)	f_terminalPrint(#a,b)
#define ejectAnimation(a,b)     f_ejectAnimation(a,#b)
#define pushAnimation(a,b)      f_pushAnimation(a,#b)
#define neonAnimation(a,b)      f_neonAnimation(#a,b)
#define invardLineSlide(a,b)    f_invardLineSlide(a,#b)

#define CUR       move(20,6)

#define EXIT    2
#define HEIGHT  25
#define WIDTH   81

extern char asciiTerminal[WIDTH][HEIGHT];

#endif
