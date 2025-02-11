#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "term.h"
#include "engine.h"
#include "drawing.h"

#define TOTAL_HEIGHT 34
#define TOTAL_WIDTH 130

#define IMAGE_Y 1
#define IMAGE_X 1

#define IMAGE_HEIGHT 32
#define IMAGE_WIDTH 96

#define BAR_Y 1
#define BAR_X 99

#define BAR_HEIGHT 32
#define BAR_WIDTH 30

#define HEALTH_Y 2
#define HEALTH_X 104

#define WAND_Y 2
#define WAND_X 118


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

	d_offset_y = ( t_row - TOTAL_HEIGHT ) / 2 + 1;
	d_offset_x = ( t_col - TOTAL_WIDTH ) / 2 + 1;

	FORE_COLOR( YELLOW_HIGH );
	d_rect( IMAGE_Y - 1, IMAGE_X - 1, IMAGE_HEIGHT + 2, IMAGE_WIDTH + 2 );
	d_rect( BAR_Y - 1, BAR_X - 1, BAR_HEIGHT + 2, BAR_WIDTH + 2 );
	d_str( IMAGE_Y - 1, IMAGE_X, "╡ESC╞" );
	DEFAULT();
}

int main() {
	FILE* test_file = fopen( "assets/menu.avid", "r" );
	FILE* health_file = fopen( "assets/health.apic", "r" );
	FILE* wand_file = fopen( "assets/wand.apic", "r" );
	Video test_video = d_load_video( test_file );
	Image health_bar = d_load_image( health_file );
	Image wand_bar = d_load_image( wand_file );
	float video_start_time = 1;
	fclose( test_file );
	fclose( health_file );
	fclose( wand_file );

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

		int frame = ( int )( ( e_game_time - video_start_time ) * test_video.fps * 2 );
		if ( frame < 0 ) { frame = 0; }
		if ( frame >= test_video.frames ) { frame = test_video.frames - 1; }
		d_draw_video( test_video, IMAGE_Y, IMAGE_X, frame );
		DEFAULT();

		fputs( "\e[31m", stdout );
		d_draw_image( health_bar, HEALTH_Y, HEALTH_X );
		fputs( "\e[33m", stdout );
		d_draw_image( wand_bar, WAND_Y, WAND_X );
		DEFAULT();

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
