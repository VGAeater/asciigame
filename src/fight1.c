#include <stdio.h>
#include <stdlib.h>

#include "term.h"
#include "engine.h"
#include "drawing.h"
#include "global.h"

#include "fight1.h"


typedef struct S_fight1_State S_fight1_State;

struct S_fight1_State {
	void ( *keyboard_handler )( void* data, int ch );
};

void S_fight1_keyboard_handler( void* data, int ch );
RunResult S_fight1_run( Scene self );
void S_fight1_cleanup( Scene self );

void S_fight1_keyboard_handler( void* data, int ch ) {
	g_keyboard_handler( ch );

	S_fight1_State* state = ( S_fight1_State* )data;

	if ( e_game_paused ) {
		return;
	}
}

RunResult S_fight1_run( Scene self ) {
	S_fight1_State* state = self.state;

	RunResult output;

	output.change = 0;

	return output;
}

void S_fight1_cleanup( Scene self ) {
	free( self.state );
}

Scene S_fight1() {
	Scene self;

	S_fight1_State* state = malloc( sizeof( S_fight1_State ) );
	self.state = state;

	self.run = &S_fight1_run;
	self.cleanup = &S_fight1_cleanup;
	state->keyboard_handler = &S_fight1_keyboard_handler;

	e_keyboard_handler = state->keyboard_handler;
	e_keyboard_args = state;

	return self;
}


