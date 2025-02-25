#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "term.h"
#include "engine.h"
#include "drawing.h"
#include "global.h"

#define HEALTH_Y 2
#define HEALTH_X 104

#define WAND_Y 2
#define WAND_X 118

#define NOTES_Y 28
#define NOTES_X 101

#define NOTE_AMOUNT 4
#define NOTE_LENGTH 26


volatile int resized = 0;

volatile int g_running = 1;
int g_too_small = 0;

int g_typing = 0;

char notes[NOTE_AMOUNT][NOTE_LENGTH + 1];
int selected_note = -1;

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

void draw_outline() {
	FORE_COLOR( e_game_paused ? YELLOW : YELLOW_HIGH );
	d_rect( IMAGE_Y - 1, IMAGE_X - 1, IMAGE_HEIGHT + 2, IMAGE_WIDTH + 2 );
	FORE_COLOR( e_game_paused ? YELLOW_HIGH : YELLOW );
	d_rect( BAR_Y - 1, BAR_X - 1, BAR_HEIGHT + 2, BAR_WIDTH + 2 );

	FORE_COLOR( YELLOW_HIGH );
	if ( e_game_paused ) {
		d_str( BAR_Y - 1, BAR_X, "╡TAB╞╡Q╞" );
	} else {
		d_str( IMAGE_Y - 1, IMAGE_X, "╡ESC╞" );
	}
	DEFAULT();
}

void resize() {
	resized = 0;

	check_size();

	d_offset_y = ( t_row - TOTAL_HEIGHT ) / 2 + 1;
	d_offset_x = ( t_col - TOTAL_WIDTH ) / 2 + 1;
}

void g_keyboard_handler( int ch ) {
	if ( ch == ESC ) {
		e_game_paused = !e_game_paused;
		return;
	}
	if ( !e_game_paused ) {
		return;
	}
	if ( ch == '\t' ) {
		selected_note++;
		if ( selected_note > 3 ) {
			selected_note = -1;
		}
		return;
	}

	if ( selected_note == -1 ) {
		if ( ch == 'q' ) {
			g_running = 0;
		}
		return;
	}

	if ( ch >= ' ' && ch <= '~' ) {
		int len = strlen( notes[selected_note] );
		if ( len == NOTE_LENGTH ) {
			return;
		}
		notes[selected_note][len] = ch;
		notes[selected_note][len + 1] = 0;
		return;
	}
	if ( ch == DEL ) {
		int len = strlen( notes[selected_note] );
		if ( len == 0 ) {
			return;
		}
		notes[selected_note][len - 1] = 0;
		return;
	}
}

void g_init() {
	FILE* health_file = fopen( "assets/health.apic", "r" );
	FILE* wand_file = fopen( "assets/wand.apic", "r" );
	health_bar = d_load_image( health_file );
	wand_bar = d_load_image( wand_file );
	fclose( health_file );
	fclose( wand_file );

	FILE* notes_file = fopen( "data/notes.txt", "r" );

	for ( int i = 0; i < NOTE_AMOUNT; i++ ) {
		int j;
		for ( j = 0; j < NOTE_LENGTH; j++ ) {
			int ch;
			if ( ( ch = getc( notes_file ) ) == '\n' ) {
				break;
			}
			notes[i][j] = ch;
		}
		notes[i][j] = '\0';
	}

	e_sigwinch_handler = &sigwinch_handler;

	resize();
}

void g_run() {
	if ( resized ) {
		resize();
	}

	CLEAR();

	draw_outline();

	fputs( "\e[31m", stdout );
	d_draw_image( health_bar, HEALTH_Y, HEALTH_X );
	fputs( "\e[33m", stdout );
	d_draw_image( wand_bar, WAND_Y, WAND_X );
	DEFAULT();

	for ( int i = 0; i < NOTE_AMOUNT; i++ ) {
		if ( i == selected_note ) {
			fputs( "\e[47;97m", stdout );
		}
		d_str( NOTES_Y + i, NOTES_X, notes[i] );
		DEFAULT();
	}
}

void g_cleanup() {
	d_free_image( health_bar );
	d_free_image( wand_bar );
}

