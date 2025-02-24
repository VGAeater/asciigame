#ifndef ENGINE_H_
#define ENGINE_H_

extern double e_game_time;
extern double e_game_speed;
extern double e_delta_time;

extern void* e_keyboard_args;

extern void ( *e_keyboard_handler )( void*, int );
extern void ( *e_sigwinch_handler )();

extern void e_init();

extern void e_stop();

extern void e_run();

#endif
