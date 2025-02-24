#include "drawing.h"
#include "global.h"

#ifndef MENU_H_
#define MENU_H_

typedef struct S_menu_State S_menu_State;

struct S_menu_State {
	void ( *keyboard_handler )( void* data, int ch );
	float video_start_time;
	Image menu_image;
	Video menu_video;
};

Scene S_menu();

#endif
