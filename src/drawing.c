#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "drawing.h"
#include "term.h"

#define MAX_BUFFER 4096


void d_hline( int y, int x, char* str, int length ) {
	MOVE( y, x );

	for ( int i = 0; i < length; i++ ) {
		fputs( str, stdout );
	}
}

void d_vline( int y, int x, char* str, int length ) {
	for ( int i = 0; i < length; i++ ) {
		MOVE( y + i, x );
		fputs( str, stdout );
	}
}

void d_str( int y, int x, char* str ) {
	MOVE( y, x );
	fputs( str, stdout );
}

void d_rect( int y, int x, int height, int width ) {
	d_hline( y,              x, DL_H, width );
	d_hline( y + height - 1, x, DL_H, width );
	d_vline( y, x,              DL_V, height );
	d_vline( y, x + width - 1,  DL_V, height );
	d_str( y,              x,             DL_UL );
	d_str( y,              x + width - 1, DL_UR );
	d_str( y + height - 1, x,             DL_LL );
	d_str( y + height - 1, x + width - 1, DL_LR );
}

int d_load_frame( FILE* fptr, char** frame, int height ) {
	char* buffer = calloc( MAX_BUFFER, sizeof( char ) );

	for ( int y = 0; y < height; y++ ) {
		int ch;
		int i = 0;

		while ( ( ch = getc( fptr ) ) != '\n' ) {
			if ( ch == EOF || i == MAX_BUFFER ) {
				free( buffer );

				return -1;
			}

			buffer[i] = ch;

			i++;
		}

		frame[y] = calloc( i, sizeof( char ) );
		memcpy( frame[y], buffer, ( i - 1 ) * sizeof( char ) );
		frame[y][i] = '\0';
	}

	free( buffer );

	return 0;
}

void d_free_frame( char** frame, int height ) {
	for ( int i = 0; i < height; i++ ) {
		free( frame );
	}
	free( frame );
}

void d_free_image( Image image ) {
	d_free_frame( image.data, image.height );
}

void d_free_video( Video video ) {
	for ( int i = 0; i < video.frames; i++ ) {
		d_free_frame( video.data[i], video.height );
	}
	free( video.data );
}

Image d_load_image( FILE* fptr ) {
	Image image;

	fscanf( fptr, "%d\n", &image.width );
	fscanf( fptr, "%d\n", &image.height );

	image.data = calloc( image.height, sizeof( char* ) );

	if ( d_load_frame( fptr, image.data, image.height ) != 0 ) {
		d_free_image( image );

		image.width = -1;
		image.height = -1;
	}

	return image;
}

Video d_load_video( FILE* fptr ) {
	Video video;

	fscanf( fptr, "%d\n", &video.width );
	fscanf( fptr, "%d\n", &video.height );
	fscanf( fptr, "%d\n", &video.frames );
	fscanf( fptr, "%d\n", &video.fps );

	video.data = calloc( video.frames, sizeof( char** ) );

	for ( int i = 0; i < video.frames; i++ ) {
		video.data = calloc( video.height, sizeof( char* ) );

		if ( d_load_frame( fptr, video.data[i], video.height ) != 0 ) {
			d_free_video( video );

			video.width = -1;
			video.height = -1;

			break;
		}
	}

	return video;
}

