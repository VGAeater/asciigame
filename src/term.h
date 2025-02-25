#ifndef TERM_H_

#include <stdio.h>

#define TERM_H_

#define MOVE( y, x ) printf( "\e[%d;%dH", y, x )
#define CLEAR() fputs( "\e[H\e[J", stdout )
#define HIDE() fputs( "\e[?25l", stdout )
#define SHOW() fputs( "\e[?25h", stdout )

#define FORE_COLOR( n ) printf( "\e[38;5;%dm", n )
#define BACK_COLOR( n ) printf( "\e[48;5;%dm", n )
#define DEFAULT() fputs( "\e[0m", stdout )

#define BLACK 0
#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define MAGENTA 5
#define CYAN 6
#define WHITE 7

#define BLACK_HIGH 8
#define RED_HIGH 9
#define GREEN_HIGH 10
#define YELLOW_HIGH 11
#define BLUE_HIGH 12
#define MAGENTA_HIGH 13
#define CYAN_HIGH 14
#define WHITE_HIGH 15

#define ESC 27
#define DEL 127


extern int t_row, t_col;

extern void t_init();

extern void t_cleanup();

extern void t_getsize();

#endif
