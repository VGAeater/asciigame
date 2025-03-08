#include "term.h"

#ifndef SPELLS_H_
#define SPELLS_H_

#define TARGET_SELF 0
#define TARGET_NEAREST 1
#define TARGET_AOE 2
#define TARGET_MAIN 3


typedef struct Spell Spell;
typedef struct ActiveSpell ActiveSpell;

struct Spell {
	char* name;	// name of the spell
	float damage;	// damage dealt
	float healing;	// amount healed
	float block;	// damage blocking can absorb
	int target;	// selected target
	float time;	// time effect is spread over
	float aoe;	// only effective when TARGET_AOE
	int color;	// color of the spell
};

struct ActiveSpell {
	ActiveSpell* next;
	Spell spell;
	float start_time;
	float delt;	// 0-1 percent of effect delt
};

extern Spell spells[];

extern ActiveSpell* active_spells;

void s_keyboard_handler( int ch );
void s_init();
void s_run();
void s_cleanup();

#endif
