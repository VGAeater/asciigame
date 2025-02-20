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

	Scene curr_scene = menu();
	curr_scene.init();

	while ( g_running ) {
		e_run();
		g_run();
		/* draw and stuff */
		//usleep( 10000 );

		curr_scene.run();

		MOVE( t_row, 0 );
		printf( "%lf", 1 / e_delta_time );

		fflush( stdout );
	}

	e_stop();

	if ( g_too_small ) {
		puts( "window too small." );
	}

	return 0;
}
