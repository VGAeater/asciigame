#include <stdio.h>
#include <stdlib.h>

#include "term.h"
#include "engine.h"
#include "drawing.h"
#include "global.h"
#include "fight1.h"
#include "intro.h"


typedef struct S_intro_State S_intro_State;

struct S_intro_State {
	void ( *keyboard_handler )( void* data, int ch );
	int done;
};

void S_intro_keyboard_handler( void* data, int ch );
RunResult S_intro_run( Scene self );
void S_intro_cleanup( Scene self );

void S_intro_keyboard_handler( void* data, int ch ) {
	g_keyboard_handler( ch );

	S_intro_State* state = ( S_intro_State* )data;

	if ( e_game_paused ) {
		return;
	}

	if ( ch == '\n' ) {
		state->done = 1;
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

	d_str( 4, 12, "There will be a cutscene here but im lazy and animations are hard :<" );
	d_str( 12, 60, "HOW TO PLAY:" );
	d_str( 13, 64, "Typing a spell casts it" );
	d_str( 14, 64, "Typing it wrong hurts the wand" );
	d_str( 16, 60, "STARTING SPELLS:" );
	d_str( 17, 64, "heal -- heals a little" );
	d_str( 18, 64, "hurt -- deals a little damage" );

	if ( state->done ) {
		output.change = 1;
		output.next = S_fight1();
	}

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

	state->done = 0;

	e_keyboard_handler = state->keyboard_handler;
	e_keyboard_args = state;

	return self;
}


