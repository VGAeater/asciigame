## drawing.h
`
void d_hline( int y, int x, char* str, int length );

void d_vline( int y, int x, char* str, int length );

void d_str( int y, int x, char* str );

void d_rect( int y, int x, int height, int width );
`

## term.h
`
extern int t_row, t_col;

extern void t_init();

extern void t_cleanup();

extern void t_getsize();
`

## engine.h
`
extern double e_game_time;
extern double e_game_speed;

extern void ( *e_keyboard_handler )( int );
extern void ( *e_sigwinch_handler )();

extern void e_init();

extern void e_stop();

extern double e_delta();
`
