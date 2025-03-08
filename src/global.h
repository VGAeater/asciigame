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

typedef struct Scene Scene;
typedef struct RunResult RunResult;

struct Scene {
	RunResult ( *run )( Scene );
	void ( *cleanup )( Scene );
	void* state;
};

struct RunResult {
	int change;
	Scene next;
};

extern double g_health;
extern double g_wand_health;

extern double g_damage_multiplier;
extern double g_wand_penalty;

extern volatile int g_running;
extern int g_too_small;
extern void ( *g_curr_run )( void );

void g_keyboard_handler( int ch );

void g_init();

void g_run();

void g_cleanup();

#endif
