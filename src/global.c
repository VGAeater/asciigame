#include <stdio.h>

#include "term.h"
#include "engine.h"
#include "drawing.h"
#include "global.h"


volatile int resized = 0;

volatile int g_running = 1;
int g_too_small = 0;

Image health_bar, wand_bar;

void sigwinch_handler() {
	resized = 1;
}

void check_size() {
	if ( t_row < TOTAL_HEIGHT || t_col < TOTAL_WIDTH ) {
		g_too_small = 1;
		g_running = 0;
	}
}

void resize() {
	resized = 0;

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

void g_init() {
	FILE* health_file = fopen( "assets/health.apic", "r" );
	FILE* wand_file = fopen( "assets/wand.apic", "r" );
	health_bar = d_load_image( health_file );
	wand_bar = d_load_image( wand_file );
	fclose( health_file );
	fclose( wand_file );

	e_sigwinch_handler = &sigwinch_handler;

	resize();
}

void g_run() {
	if ( resized ) {
		resize();
	}

	fputs( "\e[31m", stdout );
	d_draw_image( health_bar, HEALTH_Y, HEALTH_X );
	fputs( "\e[33m", stdout );
	d_draw_image( wand_bar, WAND_Y, WAND_X );
	DEFAULT();
}

void g_cleanup() {
	d_free_image( health_bar );
	d_free_image( wand_bar );
}

