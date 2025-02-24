#include "global.h"

#ifndef INTRO_H_
#define INTRO_H_

typedef struct S_intro_State S_intro_State;

struct S_intro_State {
	void ( *keyboard_handler )( void* data, int ch );
};

Scene S_intro();

#endif
