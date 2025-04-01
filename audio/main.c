#include <stdlib.h>
#include <unistd.h>

#include "audio.h"

int main() {
	Sound sound;

	a_init();

	a_load_audio( "audio.wav", &sound );

	a_play_audio( &sound, 0 );

	while ( 1 ) {
		usleep(1000);
	}

	a_cleanup();
}

// WHEN SOUND IS NEEDED, PLAY SOUND
// WHEN AUDIO IS CALLED, RETURN FILE DATA
