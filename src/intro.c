#include <stdio.h>
#include <stdlib.h>

#include "term.h"
#include "engine.h"
#include "drawing.h"
#include "global.h"


void S_intro_keyboard_handler( int ch ) {
	//switch ( ch ) {
	//}
}

void S_intro_init() {
	e_keyboard_handler = &S_intro_keyboard_handler;
}

void S_intro_run() {
}

void S_intro_cleanup() {
}

void S_intro() {
	S_intro_init();

	g_curr_run = &S_intro_run;
}


