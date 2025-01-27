#include <sys/ioctl.h>
#include <stdio.h>
#include <signal.h>
#include <termios.h>

#include "term.h"


int t_row, t_col;

struct termios old_term, curr_term;

void t_init() {
	t_getsize();

	tcgetattr( fileno( stdin ), &old_term );

	curr_term = old_term;

	curr_term.c_lflag &= ~ICANON;	/* raw input */
	curr_term.c_lflag &= ~ECHO;	/* disable echo */

	tcsetattr( 0, TCSANOW, &curr_term );

	HIDE();

	CLEAR();
}

void t_cleanup() {
	tcsetattr( 0, TCSANOW, &old_term );

	CLEAR();

	SHOW();
}

void t_getsize() {
	struct winsize sz;
	ioctl( 0, TIOCGWINSZ, &sz );
	t_row = sz.ws_row;
	t_col = sz.ws_col;
}

