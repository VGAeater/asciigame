#include <stdio.h>
#include <stdlib.h>

#include "term.h"
#include "engine.h"
#include "drawing.h"
#include "global.h"
#include "menu.h"
#include "intro.h"


#define TEXT_X 75
#define TEXT_Y 8

void S_menu_keyboard_handler( void* data, int ch );
RunResult S_menu_run( Scene self );
void S_menu_cleanup( Scene self );

void S_menu_keyboard_handler( void* data, int ch ) {
	S_menu_State* state = ( S_menu_State* )data;

	switch ( ch ) {
		case 'q':
			g_running = 0;
			break;
		case '\n':
			if ( state->video_start_time == -1 ) {
				state->video_start_time = e_game_time;
			}
			break;
	}
}

RunResult S_menu_run( Scene self ) {
	S_menu_State* state = self.state;

	RunResult result;

	result.change = 0;

	if ( state->video_start_time == -1 ) {
		d_draw_image( state->menu_image, IMAGE_Y, IMAGE_X );
		DEFAULT();
		d_str( TEXT_Y, TEXT_X, "[Ent] Start" );
		d_str( TEXT_Y + 2, TEXT_X, "[q] Quit" );
	} else {
		int frame = ( int )( ( e_game_time - state->video_start_time ) * state->menu_video.fps );
		if ( d_clamp_frames( &frame, state->menu_video.frames ) == 1 ) {
			result.change = 1;
			result.next = S_intro();
		}
		d_draw_video( state->menu_video, IMAGE_Y, IMAGE_X, frame );
		DEFAULT();
	}

	return result;
}

void S_menu_cleanup( Scene self ) {
	S_menu_State* state = self.state;

	d_free_image( state->menu_image );
	d_free_video( state->menu_video );

	free( state );
}

Scene S_menu() {
	Scene self;

	S_menu_State* state = malloc( sizeof( S_menu_State ) );
	self.state = state;

	FILE* menu_image_file = fopen( "assets/menu.apic", "r" );
	state->menu_image = d_load_image( menu_image_file );
	fclose( menu_image_file );
	FILE* menu_video_file = fopen( "assets/menu.avid", "r" );
	state->menu_video = d_load_video( menu_video_file );
	fclose( menu_video_file );

	self.run = &S_menu_run;
	self.cleanup = &S_menu_cleanup;
	state->keyboard_handler = &S_menu_keyboard_handler;

	state->video_start_time = -1;

	e_keyboard_handler = state->keyboard_handler;
	e_keyboard_args = state;

	return self;
}

