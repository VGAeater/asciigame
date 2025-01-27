#include <wchar.h>
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

void d_free_image( Image image ) {
	for ( int i = 0; i < image.height; i++ ) {
		free( image.data[i] );
	}
	free( image.data );
}

Image d_load_image( FILE* fptr ) {
	Image image;

	char* buffer = calloc( MAX_BUFFER, sizeof( char ) );

	fscanf( fptr, "%d\n", &image.width );
	fscanf( fptr, "%d\n", &image.height );

	image.data = calloc( image.height, sizeof( char* ) );

	for ( int y = 0; y < image.height; y++ ) {
		int ch;
		int i = 0;

		while ( ( ch = getc( fptr ) ) != '\n' ) {
			if ( ch == EOF || i == MAX_BUFFER ) {
				d_free_image( image );

				image.width = -1;
				image.height = -1;

				free( buffer );

				return image;
			}

			buffer[i] = ch;

			i++;
		}

		image.data[y] = calloc( i, sizeof( char ) );
		memcpy( image.data[y], buffer, ( i - 1 ) * sizeof( char ) );
		image.data[y][i] = '\0';
	}

	free( buffer );

	return image;
}

