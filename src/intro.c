#include <stdio.h>
#include <stdlib.h>

#include "term.h"
#include "engine.h"
#include "drawing.h"
#include "global.h"
#include "intro.h"


void S_intro_keyboard_handler( void* data, int ch );
RunResult S_intro_run( Scene self );
void S_intro_cleanup( Scene self );

void S_intro_keyboard_handler( void* data, int ch ) {
	g_keyboard_handler( ch );

	if ( e_game_paused ) {
		return;
	}

	//switch ( ch ) {
	//}
}

RunResult S_intro_run( Scene self ) {
	S_intro_State* state = self.state;

	RunResult output;

	output.change = 0;

	FORE_COLOR( WHITE_HIGH );
	for ( int i = 0; i < 8; i++ ) {
		d_str( 25+i, 1, "████████████████████████████████████████████████████████████████████████████████████████████████" );
	}
	DEFAULT();

	return output;
}

void S_intro_cleanup( Scene self ) {
	free( self.state );
}

Scene S_intro() {
	Scene self;

	S_intro_State* state = malloc( sizeof( S_intro_State ) );
	self.state = state;

	self.run = &S_intro_run;
	self.cleanup = &S_intro_cleanup;
	state->keyboard_handler = &S_intro_keyboard_handler;

	e_keyboard_handler = state->keyboard_handler;
	e_keyboard_args = state;

	return self;
}


