#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <portaudio.h>
#include <string.h>

#include "audio.h"

PaStream* stream;
CallbackIndex callback_list;

#define CHANNELS 2
#define SAMPLERATE 96000
#define FRAMES_PER_BUFFER 2048


int callback( const void* input, void* output, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData );

int a_init() {
	PaError error;

	error = Pa_Initialize();
	if ( error != paNoError ) {
		fputs( "Problem initializing\n", stderr );
		return 1;
	}

	error = Pa_OpenDefaultStream( &stream, 0, CHANNELS, paFloat32, SAMPLERATE, FRAMES_PER_BUFFER, callback, &callback_list );
	if ( error != paNoError ) {
		fputs( "Problem opening Default Stream\n", stderr );
		return 1;
	}

	error = Pa_StartStream( stream );
	if ( error != paNoError ) {
		fputs( "Problem starting Stream\n", stderr );
		return 1;
	}

	return 0;
}

int callback( const void* input, void* output, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData ) {
	CallbackIndex* callback_list = ( CallbackIndex* )userData;

	float* out = ( float* )output;

	memset( out, 0, sizeof( float ) * frameCount * CHANNELS );

	CallbackIndex* curr_element = callback_list;

	while ( curr_element->next != NULL ) {
		curr_element = curr_element->next;

		for ( unsigned long i = 0; i < frameCount; i++ ) {
			PaTime frame_time = timeInfo->outputBufferDacTime - curr_element->start_time + ( double )i / SAMPLERATE;
			unsigned long frame_index = ( unsigned long )( frame_time * ( double )curr_element->sound->info.samplerate ) * curr_element->sound->info.channels;
			for ( int c = 0; c < CHANNELS; c++ ) {
				out[i * CHANNELS + c] += curr_element->sound->data[frame_index + ( unsigned long )( ( double )c / CHANNELS * ( double )curr_element->sound->info.channels )];
			}
		}
	}

	// return paComplete;

	return paContinue;
}

int a_play_audio( Sound* sound, double start_time ) {
	CallbackIndex* curr_element = &callback_list;

	while ( curr_element->next != NULL ) {
		curr_element = curr_element->next;
	}

	curr_element->next = malloc( sizeof( CallbackIndex ) );
	curr_element = curr_element->next;

	curr_element->start_time = start_time + Pa_GetStreamTime( stream );

	curr_element->sound = sound;

	curr_element->next = NULL;

	return 0;
}

int a_cleanup() {
	PaError error = Pa_CloseStream( stream );
	if ( error != paNoError ) {
		fputs( "Problem closing stream\n", stderr );
		return 1;
	}

	error = Pa_Terminate(); 
	if ( error != paNoError ) {
		fputs( "Problem terminating\n", stderr );
		return 1;
	}

	return 0;
}

int a_load_audio( const char* filename, Sound* sound ) {
	SNDFILE* file;

	file = sf_open( filename, SFM_READ, &sound->info );

	if ( sf_error( file ) != SF_ERR_NO_ERROR ) {
		return 1;
	}

	sound->data = malloc( sizeof( float ) * sound->info.frames * sound->info.channels );

	sf_read_float( file, sound->data, sound->info.frames * sound->info.channels );

	sf_close( file );

	return 0;
}
