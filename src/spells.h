#ifndef SPELLS_H_
#define SPELLS_H_

#define TARGET_SELF 0
#define TARGET_NEAREST 1
#define TARGET_AOE 2
#define TARGET_MAIN 3

typedef struct Spell Spell;

struct Spell {
	float damage;
	float healing;
	int target;
	float aoe; // only effective when TARGET_AOE
	
};
