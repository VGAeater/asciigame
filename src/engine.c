#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>

#include "term.h"
#include "engine.h"


void* input_thread_function( void* args );
void sigwinch_function();

struct timespec last_time;
double e_game_time = 0;
double e_game_speed = 1;
int e_game_paused = 0;
double e_delta_time = 0;

void* e_keyboard_args;

pthread_t input_thread_id;
void ( *e_keyboard_handler )( void*, int );
void ( *e_sigwinch_handler )();

void e_init() {
	t_init();

	signal( SIGWINCH, sigwinch_function );

	pthread_create( &( input_thread_id ), NULL, &input_thread_function, NULL );

	clock_gettime( CLOCK_MONOTONIC, &last_time );
}

void e_stop() {
	pthread_cancel( input_thread_id );
	t_cleanup();
}

void e_run() {
	struct timespec curr_time;

	clock_gettime( CLOCK_MONOTONIC, &curr_time );

	struct timespec delta_timespec;
	delta_timespec.tv_sec = curr_time.tv_sec - last_time.tv_sec;
	delta_timespec.tv_nsec = curr_time.tv_nsec - last_time.tv_nsec;

	e_delta_time = ( double )delta_timespec.tv_sec + ( ( double )delta_timespec.tv_nsec / 1000000000 );
	last_time = curr_time;

	if ( !e_game_paused ) {
		e_game_time += e_delta_time * e_game_speed;
	}
}

void* input_thread_function( void* args ) {
	while ( 1 ) {
		int ch = getchar();

		if ( e_keyboard_handler != NULL ) {
			e_keyboard_handler( e_keyboard_args, ch );
		}
	}
}

void sigwinch_function() {
	t_getsize();

	if ( e_sigwinch_handler != NULL ) {
		e_sigwinch_handler();
	}
}

