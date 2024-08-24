
#ifdef USE_ADVANCED_CLASS
#if defined(PCLASS_HEADER) || defined(PCLASS_BOTH)

typedef enum {
	PCLASS_NONE,
	PCLASS_BFG,
	PCLASS_LIGHTNING,
	PCLASS_RAILGUN,
	PCLASS_LIGHTWEIGHT,
	PCLASS_HEAVYWEIGHT,
	PCLASS_RPG,
	PCLASS_SCOUT,
	PCLASS_GUARD,
	PCLASS_DOUBLER = PCLASS_HEAVYWEIGHT,
	PCLASS_AMMOREGEN = PCLASS_LIGHTWEIGHT,

	PCLASS_HUMAN,
	PCLASS_BARD,
	PCLASS_CLERIC,
	PCLASS_DRUID,
	PCLASS_FIGHTER,
	PCLASS_MONK,
	PCLASS_PALADIN,
	PCLASS_RANGER,
	PCLASS_ROGUE,
	PCLASS_SORCERER,
	PCLASS_WARLOCK,
	PCLASS_WIZARD,

	PCLASS_HUMAN_COUNT,

	PCLASS_FREEZE,
	PCLASS_ANTIGRAVITY,
	PCLASS_ROUND, // for ball physics

	// begin classes of monsters, not interested in item pickups
	PCLASS_MONSTER,
	PCLASS_BARBARIAN,
	PCLASS_KLESK,
	PCLASS_BONES,
	PCLASS_SORLAG,
	PCLASS_VISOR,
	PCLASS_TANK,
	PCLASS_TANKJR,
	PCLASS_SHAMBLER, // shambler
	PCLASS_DRAGON, // always flies because i lack animation ambition
	PCLASS_BERSERKER,
	PCLASS_GUNNER,
	PCLASS_VORE,

	PCLASS_MONSTER_COUNT,

	PCLASS_NUM_CLASSES
} pclass_t;

#endif
#ifndef PCLASS_HEADER

char *humans[MAX_QPATH] = {
	"doom",
	"biker",
	"sarge",
	"crash",
	"grunt",
	"hunter",
	"mynx",
	"ranger",
	"razor",
	"pi",
	"anarki",
	"slash",
	"keel",
	"major",
	"bitterman",
	"xearo",
	"lucy",
	"james",
	"janet",
	"\0"
};
int humans_count = 19;


char *monsters[MAX_QPATH] = {
	"hknight",
	"shalrath",
	"shambler",
	"ogre",
	"enforcer",
	"berserker",
	"dog",
	"tank",
	"tankjr",
	"widow",
	"bitch",
	"hover",
	"insane",
	"mummy",
	"mutant",
	"sorlag",
	"klesk",
	"orbb",
	"bones",
	"visor",
	"uriel",
	"fritzkrieg",
	"wrath",
	"\0"
};
int monsters_count = 23;

pclass_t BG_PlayerClassFromModel(const char *model) {
//     return PCLASS_DRAGON;
  if (Q_stristr (model, "sarge"))
     return PCLASS_RANGER;
  else if (Q_stristr (model, "visor"))
     return PCLASS_VISOR;
  else if (Q_stristr (model, "sorlag"))
     return PCLASS_SORLAG;
  else if (Q_stristr (model, "bones"))
     return PCLASS_BONES;
  else if (Q_stristr (model, "klesk"))
     return PCLASS_KLESK;
	else if (Q_stristr (model, "tank"))
     return PCLASS_TANK;
  else if (Q_stristr (model, "tankjr"))
     return PCLASS_TANKJR;
 	else if (!Q_stricmp (model, "biker/red"))
     return PCLASS_BFG;
  else if (!Q_stricmp (model, "anarki/blue"))
     return PCLASS_LIGHTNING;
  else if (!Q_stricmp (model, "grunt/red"))
     return PCLASS_RAILGUN;
  else if (Q_stristr (model, "shambler"))
     return PCLASS_SHAMBLER;
  else if (Q_stristr (model, "dragon"))
     return PCLASS_DRAGON;
  else if (Q_stristr (model, "berserker"))
     return PCLASS_BERSERKER;
  else if (Q_stristr (model, "infantry"))
     return PCLASS_GUNNER;
  else if (Q_stristr (model, "monkey"))
     return PCLASS_ROUND;
  else if (Q_stristr (model, "shalrath"))
     return PCLASS_VORE;
  else {
		int i;

		for(i = 0; i < humans_count; i++) {
			if(Q_stristr (model, humans[i])) {
				return PCLASS_HUMAN;
			}
		}
		for(i = 0; i < monsters_count; i++) {
			if(Q_stristr (model, monsters[i])) {
				return PCLASS_MONSTER;
			}
		}

		return PCLASS_NONE;
  }
}

#endif

#endif

