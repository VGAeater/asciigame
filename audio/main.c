#include <portaudio.h>
#include <stdlib.h>

#include "audio.h"

int main() {
	Sound sound;

	a_init();

	a_load_audio( "audio2.wav", &sound );

	a_play_audio( &sound, 0 );

	while ( 1 ) {
		Pa_Sleep(100);
	}

	a_cleanup();
}

// WHEN SOUND IS NEEDED, PLAY SOUND
// WHEN AUDIO IS CALLED, RETURN FILE DATA
