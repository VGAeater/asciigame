#ifndef GLOBAL_H_
#define GLOBAL_H_

#define TOTAL_HEIGHT 34
#define TOTAL_WIDTH 130

#define IMAGE_Y 1
#define IMAGE_X 1

#define IMAGE_HEIGHT 32
#define IMAGE_WIDTH 96

#define BAR_Y 1
#define BAR_X 99

#define BAR_HEIGHT 32
#define BAR_WIDTH 30

#define HEALTH_Y 2
#define HEALTH_X 104

#define WAND_Y 2
#define WAND_X 118

typedef struct {
	void ( *init )( void );
	void ( *run )( void );
	void ( *cleanup )( void );
} Scene;

extern volatile int g_running;
extern int g_too_small;

void g_init();

void g_run();

void g_cleanup();

#endif
