#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "term.h"
#include "engine.h"
#include "drawing.h"

#define TOTAL_HEIGHT 34
#define TOTAL_WIDTH 130

#define IMAGE_HEIGHT 32
#define IMAGE_WIDTH 96


bool running = true;
bool too_small = false;
bool resized = false;

int offset_x, offset_y;

void check_size() {
	if ( t_row < TOTAL_HEIGHT || t_col < TOTAL_WIDTH ) {
		too_small = true;
		running = false;
	}
}

void keyboard_handler( int ch ) {
	if ( ch == 'q' ) {
		running = false;
	}
	/* handle keyboard stuff */
}

void sigwinch_handler() {
	resized = true;
}

void resize() {
	resized = false;

	check_size();

	CLEAR();

	offset_y = ( t_row - TOTAL_HEIGHT ) / 2 + 1;
	offset_x = ( t_col - TOTAL_WIDTH ) / 2 + 1;

	FORE_COLOR( YELLOW_HIGH );
	d_rect( offset_y, offset_x, TOTAL_HEIGHT, IMAGE_WIDTH + 2 );
	d_rect( offset_y, offset_x + IMAGE_WIDTH + 2, TOTAL_HEIGHT, TOTAL_WIDTH - IMAGE_WIDTH - 2 );
	DEFAULT();
}

int main() {
	FILE* test_file = fopen( "assets/menu.avid", "r" );
	Video test_video = d_load_video( test_file );
	float video_start_time = 1;
	fclose( test_file );

	e_keyboard_handler = &keyboard_handler;
	e_sigwinch_handler = &sigwinch_handler;

	e_init();

	resize();

	while ( running ) {
		if ( resized ) {
			resize();
		}

		double delta_time = e_delta();
		/* draw and stuff */
		//usleep( 10000 );

		//FORE_COLOR( YELLOW );
		//d_str( offset_y + 1, offset_x + 1, "this is yellow" );
		//DEFAULT();
		//for ( int y = 0; y < 6; y++ ) {
		//	MOVE( offset_y + 2 + y, offset_x + 1 );
		//	for ( int x = 0; x < 36; x++ ) {
		//		FORE_COLOR( 16 + y * 36 + x );
		//		fputs( "#", stdout );
		//	}
		//}
		//DEFAULT();

		int frame = ( int )( ( e_game_time - video_start_time ) * test_video.fps * 2 );
		if ( frame < 0 ) { frame = 0; }
		if ( frame >= test_video.frames ) { frame = test_video.frames - 1; }
		d_draw_video( test_video, offset_y + 1, offset_x + 1, frame );
		MOVE( t_row, 0 );
		printf( "%lf", 1 / delta_time );

		fflush( stdout );
	}

	e_stop();

	if ( too_small ) {
		puts( "window too small." );
	}

	return 0;
}
