#ifndef MYHEAD_H_
#define MYHEAD_H_

void    drawInterface();
void    f_invardLineSlide(int, char*);
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
void    showCommanderInfo(char*);
void    clearLine(int);
void    clearCommander();
void    f_showHelp(char*);
void    silenceOn();
void    silenceOff();
void    closeInterface();
int     playGame();

#define ejectAnimation(a,b)     f_ejectAnimation(a,#b)
#define pushAnimation(a,b)      f_pushAnimation(a,#b)
#define invardLineSlide(a,b)    f_invardLineSlide(a,#b) 
#define showHelp(a)             f_showHelp(#a)

#define EXIT    2
#define HEIGHT  25
#define WIDTH   81

extern char asciiTerminal[WIDTH][HEIGHT];
extern char username[20], pass[20];

#endif
