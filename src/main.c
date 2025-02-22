#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "term.h"
#include "engine.h"
#include "drawing.h"
#include "global.h"

#include "menu.h"


int main() {
	e_init();

	g_init();

	S_menu();

	while ( g_running ) {
		e_run();
		g_run();

		MOVE( t_row, 0 );
		printf( "%lf", 1 / e_delta_time );

		fflush( stdout );

		usleep( 10000 );
	}

	e_stop();

	if ( g_too_small ) {
		puts( "window too small." );
	}

	return 0;
}
