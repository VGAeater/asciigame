#include <string.h>
#include <stdlib.h>

#include "global.h"
#include "term.h"
#include "engine.h"
#include "drawing.h"
#include "spells.h"

#define MAX_SPELL_BUFFER 64


Spell spells[] = {
	{ "heal", 0, 10, TARGET_SELF, 0, 0, GREEN_HIGH },
	{ "hurt", 10, 0, TARGET_NEAREST, 0, 0, RED },
};

ActiveSpell* active_spells = NULL;

int amount_of_spells = sizeof( spells ) / sizeof( Spell );

char* spell_buffer;

void s_init() {
	spell_buffer = malloc( sizeof( char ) * MAX_SPELL_BUFFER );
	*spell_buffer = '\0';
}

void s_keyboard_handler( int ch ) {
	if ( ch >= ' ' && ch <= '~' ) {
		int len = strlen( spell_buffer );
		if ( len == MAX_SPELL_BUFFER ) {
			return;
		}
		spell_buffer[len] = ch;
		spell_buffer[len + 1] = '\0';
		return;
	}

	if ( ch == DEL ) {
		int len = strlen( spell_buffer );
		if ( len == 0 ) {
			return;
		}
		spell_buffer[len - 1] = '\0';
		return;
	}

	if ( ch == '\n' ) {
		for ( int i = 0; i < amount_of_spells; i++ ) {
			if ( strcmp( spell_buffer, spells[i].name ) ) {
				g_wand_health -= g_wand_penalty;
				continue;
			}

			ActiveSpell* spell_tracker = malloc( sizeof( ActiveSpell ) );

			spell_tracker->next = active_spells;
			spell_tracker->spell = spells[i];
			spell_tracker->start_time = e_game_time;
			spell_tracker->delt = 0;

			active_spells = spell_tracker;
			break;
		}
		*spell_buffer = '\0';
	}
}

void s_run() {
	FORE_COLOR( e_game_paused ? YELLOW : YELLOW_HIGH );
	d_str( TOTAL_HEIGHT - 1, 1, "╡" );
	d_str( TOTAL_HEIGHT - 1, 66, "╞" );
	d_hline( TOTAL_HEIGHT - 1, 2, " ", 64 );
	d_str( TOTAL_HEIGHT - 1, 2, spell_buffer );
	DEFAULT();

	ActiveSpell* prev = active_spells;
	ActiveSpell* spell_tracker = active_spells;
	while ( spell_tracker ) {
		if ( spell_tracker->delt >= 1 ) {
			spell_tracker = prev->next = spell_tracker->next;
			free( spell_tracker );
			continue;
		}
		prev = spell_tracker;
		spell_tracker = spell_tracker->next;
	}
}

void s_cleanup() {
	free( spell_buffer );
}
