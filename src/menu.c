#include <stdio.h>
#include <stdlib.h>

#include "term.h"
#include "engine.h"
#include "drawing.h"
#include "global.h"


#define TEXT_X 75
#define TEXT_Y 8

float video_start_time = -1;

Image menu_image;
Video menu_video;

void S_menu_keyboard_handler( int ch ) {
	switch ( ch ) {
		case 'q':
			g_running = 0;
			break;
		case '\n':
			if ( video_start_time == -1 ) {
				video_start_time = e_game_time;
			}
			break;
	}
}

void S_menu_init() {
	FILE* menu_image_file = fopen( "assets/menu.apic", "r" );
	menu_image = d_load_image( menu_image_file );
	fclose( menu_image_file );
	FILE* menu_video_file = fopen( "assets/menu.avid", "r" );
	menu_video = d_load_video( menu_video_file );
	fclose( menu_video_file );

	e_keyboard_handler = &S_menu_keyboard_handler;
}

void S_menu_run() {
	if ( video_start_time == -1 ) {
		d_draw_image( menu_image, IMAGE_Y, IMAGE_X );
		DEFAULT();
		d_str( TEXT_Y, TEXT_X, "[Ent] Start" );
		d_str( TEXT_Y + 2, TEXT_X, "[q] Quit" );
	} else {
		int frame = ( int )( ( e_game_time - video_start_time ) * menu_video.fps );
		if ( frame < 0 ) { frame = 0; }
		if ( frame >= menu_video.frames ) { frame = menu_video.frames - 1; }
		d_draw_video( menu_video, IMAGE_Y, IMAGE_X, frame );
		DEFAULT();
	}
}

void S_menu_cleanup() {
	d_free_image( menu_image );
	d_free_video( menu_video );
}

void S_menu() {
	S_menu_init();

	g_curr_run = &S_menu_run;
}

