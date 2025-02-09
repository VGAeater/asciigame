#ifndef DRAWING_H_
#define DRAWING_H_

#define SL_H "─"
#define SL_V "│"
#define SL_UL "┌"
#define SL_UR "┐"
#define SL_LL "└"
#define SL_LR "┘"
#define SL_TU "┴"
#define SL_TD "┬"
#define SL_TL "┤"
#define SL_TR "├"
#define SL_T "┼"

#define DL_H "═"
#define DL_V "║"
#define DL_UL "╔"
#define DL_UR "╗"
#define DL_LL "╚"
#define DL_LR "╝"
#define DL_TU "╩"
#define DL_TD "╦"
#define DL_TL "╣"
#define DL_TR "╠"
#define DL_T "╬"


extern int d_offset_x, d_offset_y;

//╒╓╕╖╘╙╛╜╞╟╡╢╤╥╧╨╪╫

typedef struct {
	int width;	/* not limit of data[0] width simply symbolic */
	int height;
	char** data;
} Image;

typedef struct {
	int width;	/* not limit of data[0][0] width simply symbolic */
	int height;
	int frames;
	int fps;
	char*** data;
} Video;

void d_hline( int y, int x, char* str, int length );

void d_vline( int y, int x, char* str, int length );

void d_str( int y, int x, char* str );

void d_rect( int y, int x, int height, int width );

void d_free_image( Image image );

void d_free_video( Video video );

Image d_load_image( FILE* fptr );

Video d_load_video( FILE* fptr );

void d_draw_image( Image image, int y, int x );

void d_draw_video( Video video, int y, int x, int frame );

#endif

