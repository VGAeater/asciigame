#include <stdlib.h>
#include <stdio.h>

#include "term.h"
#include "engine.h"
#include "drawing.h"
#include "global.h"

#include "menu.h"


int main() {
	e_init();

	g_init();

	Scene curr_scene = S_menu();

	while ( g_running ) {
		e_run();

		g_run();

		RunResult result = curr_scene.run( curr_scene );

		if ( result.change ) {
			curr_scene.cleanup( curr_scene );
			curr_scene = result.next;
		}

		MOVE( t_row, 0 );
		printf( "%lf", 1 / e_delta_time );

		fflush( stdout );
	}

	curr_scene.cleanup( curr_scene );

	g_cleanup();

	e_stop();

	if ( g_too_small ) {
		puts( "window too small." );
	}

	return 0;
}
