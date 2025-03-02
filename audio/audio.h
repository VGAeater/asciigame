#ifndef AUDIO_H_
#define AUDIO_H_

#include <sndfile.h>

typedef struct {
	float* data;
	SF_INFO info;
} Sound;

typedef struct CallbackIndex CallbackIndex;

struct CallbackIndex {
	CallbackIndex* next;
	Sound* sound;
	double start_time;
};

int a_init();

int a_load_audio( const char* filename, Sound* sound );

int a_play_audio( Sound* sound, double start_time );

int a_cleanup();

#endif
