// Copyright (C) 1999-2000 Id Software, Inc.
//
// bg_public.h -- definitions shared by both the server game and client game modules

// because games can change separately from the main system version, we need a
// second version that must match between game and cgame
#include "bg_physics.h"

#define	GAME_VERSION		"baseq3-1"

#define	DEFAULT_GRAVITY		800
#define	GIB_HEALTH			-40
#define	ARMOR_PROTECTION	0.66

#define	HEALTH_SOFT_LIMIT	100
#define	AMMO_HARD_LIMIT		200

#define	MAX_ITEMS			1024

#define	RANK_TIED_FLAG		0x4000

#define DEFAULT_SHOTGUN_SPREAD	700
#define DEFAULT_SHOTGUN_COUNT	11

#define	ITEM_RADIUS			15		// item sizes are needed for client side pickup detection

#define	LIGHTNING_RANGE		768

#define	SCORE_NOT_PRESENT	-9999	// for the CS_SCORES[12] when only one player is present

#define	VOTE_TIME			30000	// 30 seconds before vote times out

#define	DROPPED_TIME		30000   // 30 seconds before removing  dropped items

#define	MINS_Z				-24
#define	DEFAULT_VIEWHEIGHT	26
#define CROUCH_VIEWHEIGHT	12
#define	DEAD_VIEWHEIGHT		-16

#define	PM_STEP_HEIGHT		18

//
// config strings are a general means of communicating variable length strings
// from the server to all connected clients.
//

// CS_SERVERINFO and CS_SYSTEMINFO are defined in q_shared.h
#define	CS_MUSIC				2
#define	CS_MESSAGE				3		// from the map worldspawn's message field
#define	CS_MOTD					4		// g_motd string for server message of the day
#define	CS_WARMUP				5		// server time when the match will be restarted
#define	CS_SCORES1				6
#define	CS_SCORES2				7
#define CS_VOTE_TIME			8
#define CS_VOTE_STRING			9
#define	CS_VOTE_YES				10
#define	CS_VOTE_NO				11

#define CS_TEAMVOTE_TIME		12
#define CS_TEAMVOTE_STRING		14
#define	CS_TEAMVOTE_YES			16
#define	CS_TEAMVOTE_NO			18

#define	CS_GAME_VERSION			20
#define	CS_LEVEL_START_TIME		21		// so the timer only shows the current level
#define	CS_INTERMISSION			22		// when 1, fraglimit/timelimit has been hit and intermission will start in a second or two
#define CS_FLAGSTATUS			23		// string indicating flag status in CTF
#define CS_SHADERSTATE			24
#define CS_BOTINFO				25

#define	CS_ITEMS				27		// string of 0's and 1's that tell which items are present

#ifdef USE_ADVANCED_GAMES
#define	CS_SCORES3				28
#define	CS_SCORES4				29
#endif

#define	CS_MODELS					32
#define	CS_SOUNDS					(CS_MODELS+MAX_MODELS)
#define	CS_PLAYERS				(CS_SOUNDS+MAX_SOUNDS)
#define	CS_SKINS					(CS_PLAYERS+MAX_CLIENTS)
#define CS_LOCATIONS			(CS_SKINS+MAX_SKINS)
#define CS_PARTICLES			(CS_LOCATIONS+MAX_LOCATIONS) 

#define CS_MAX					(CS_PARTICLES+MAX_LOCATIONS)

#if (CS_MAX) > MAX_CONFIGSTRINGS
#error overflow: (CS_MAX) > MAX_CONFIGSTRINGS
#endif

typedef enum {
	GT_FFA,				// free for all
	GT_TOURNAMENT,		// one on one tournament
	GT_SINGLE_PLAYER,	// single player ffa

	//-- team games go after this --

	GT_TEAM,			// team deathmatch
	GT_CTF,				// capture the flag
#if defined(MISSIONPACK) || defined(USE_CLASSIC_HUD) || defined(USE_ADVANCED_ITEMS)
	GT_1FCTF,
	GT_OBELISK,
	GT_HARVESTER,
#endif



	GT_MAX_GAME_TYPE
} gametype_t;

typedef enum { GENDER_MALE, GENDER_FEMALE, GENDER_NEUTER } gender_t;

/*
===================================================================================

PMOVE MODULE

The pmove code takes a player_state_t and a usercmd_t and generates a new player_state_t
and some other output data.  Used for local prediction on the client game and true
movement on the server game.
===================================================================================
*/

typedef enum {
	PM_NORMAL,		// can accelerate and turn
#ifdef USE_BIRDS_EYE
	PM_PLATFORM,
	PM_BIRDSEYE,
	PM_THIRDPERSON,
	PM_FOLLOWCURSOR,
#endif

#ifdef USE_AIW
	PM_UPSIDEDOWN,
	PM_REVERSED,
	PM_REVERSEDUPSIDEDOWN,
#endif

	PM_NOCLIP,		// noclip movement
	PM_SPECTATOR,	// still run into walls
	PM_DEAD,		// no acceleration or turning, but free falling
	PM_FREEZE,		// stuck in place with no control
	PM_INTERMISSION,	// no movement or status bar
	PM_SPINTERMISSION,	// no movement or status bar
#if defined(USE_GAME_FREEZETAG) || defined(USE_REFEREE_CMDS)
  PM_FROZEN,
#endif

#ifdef USE_VEHICLES
	PM_VEHICLE,
	PM_VEHICLEMOUSE,
#endif

#ifdef USE_ADVANCED_CLASS
	PM_ROUND, // for neverball/geoball movement
	PM_MONSTER, // not interested in item pickups, they come with special powerups
	PM_STUCKDUCK, // some monsters don't move when crouching, it was really funny to watch
#endif

	PM_LOOKSPLINE, // control look angle from spline
	PM_MOVESPLINE, // control movement from spline
	PM_BOTHSPLINE, // control both from spline
	PM_LOOKQUARTER,
	PM_LOOKHALF, // allow for 180 degree freelook from the angle 
	// specified by camera spline nearest current location

	NUM_PLAYERMOVE,
} pmtype_t;

typedef enum {
	WEAPON_READY, 
	WEAPON_RAISING,
	WEAPON_DROPPING,
	WEAPON_FIRING
} weaponstate_t;

#ifdef USE_ADVANCED_ITEMS


// NOTE: may not have more than 16
typedef enum {
	PW_NONE,

	PW_QUAD = 1,
	PW_REGEN = 2,
	PW_BATTLESUIT = 3,
	PW_HASTE = 4,
	PW_INVIS = 5,
	PW_FLIGHT = 6,

	PW_REDFLAG = 7,
	PW_BLUEFLAG = 8,
	PW_NEUTRALFLAG = 9,

	PW_MAX_POWERUPS = 10,
	// = 10

	PW_SCOUT = 10,
	PW_GUARD = 11,
	PW_DOUBLER = 12,
	PW_AMMOREGEN = 13,
	PW_INVULNERABILITY = 14,

#if defined(USE_ADVANCED_GAMES) || defined(USE_ADVANCED_TEAMS)
	PW_GOLDFLAG = 15,
	PW_GREENFLAG = 16,
#endif

#ifdef USE_ADVANCED_CLASS
	PW_SPECIAL_ABILITY = 17,
#endif
// memory overflow on everything past this in the default mode

#if defined(USE_GAME_FREEZETAG) || defined(USE_REFEREE_CMDS)
  PW_FROZEN = 18,
#endif

#if defined(USE_WEAPON_SPREAD) || defined(USE_RUNES)
  PW_SPREAD = 19,  //Hal9000 spreadfire
#endif

	HI_TELEPORTER = 20,
	HI_MEDKIT = 21,
	HI_KAMIKAZE = 22,
	HI_PORTAL = 23,
	HI_INVULNERABILITY = 24,
	HI_HEALER = 25,

#ifdef USE_VEHICLES
	HI_VEHICLE = 26,
#endif

	HI_NUM_HOLDABLE = 27,

	PW_REGENAMMO = 32,
	PW_GRAVITYSUIT = 33,
	PW_FLASH = 34,
	PW_VISIBILITY = 35,
	PW_SUPERMAN = 36,
	PW_BERSERKER = 37, // same thing as RUNE_BERSERK but non-permanently


#ifdef USE_RUNES
  // 1 - 4
  RUNE_STRENGTH,     // black
  RUNE_REGEN,        // hell
  RUNE_RESIST,       // elder
  RUNE_HASTE,        // earth
  
  // 5 - 8
  RUNE_ENVIRO,       // black
  RUNE_FLIGHT,       // hell
  RUNE_BERSERK,      // elder
  RUNE_RECALL,       // earth
  
  // 9 - 12
  RUNE_ELECTRIC,     // black
  RUNE_CLOAK,        // hell
  RUNE_DIVINE,       // elder
  RUNE_DEATH,        // earth
  
  // 13 - 16
  RUNE_HOLO,         // black
  RUNE_ORB,          // hell
  RUNE_BLINK,        // elder
  RUNE_CAMO,         // earth
  
  // 17 - 20
  RUNE_JUMP,         // black
  RUNE_ACTION,       // hell
  RUNE_VAMPIRE,      // elder
  RUNE_SHIELD,       // earth
  
  // 21 - 24
  RUNE_HEALTH,       // black
  RUNE_RADIO,        // hell
  RUNE_SWITCH,       // elder
  RUNE_ICETRAP,      // earth
  
  // 25 - 28
  RUNE_GRAVITY,      // black
  RUNE_TELE,         // hell
  RUNE_IMPACT,       // elder
  RUNE_VENGEANCE,    // earth
  
  // 29 - 32
  RUNE_SHUBHAT,      // black
  RUNE_REPULSION,    // hell
  RUNE_PHASING,      // elder
  RUNE_SHAMBLER,     // earth
  
  // 33 - 36
  RUNE_DUALRECALL,   // black
  RUNE_WEIRDNESS,    // hell
  RUNE_PHOENIX,      // elder
  RUNE_SPIKECLOUD,   // earth
  
  // 37 - 40
  RUNE_FIREWALK,     // black
  RUNE_GRAPPLE,      // hell
  RUNE_ATHLETIC,     // elder
  RUNE_LUMBERJACK,   // earth
  
  // 41 - 44
  RUNE_HOUNGAN,      // black
  RUNE_PIERCING,     // hell
  RUNE_PRESERVE,     // elder
  RUNE_ZENMONK,      // earth
  
  // 45 - 48
  RUNE_TORCH,        // black
  RUNE_PACKRAT,      // hell
  RUNE_ARMOR,        // elder
  RUNE_QUAD,         // earth
  
  // 49 - 52
  RUNE_JACK,         // black
  RUNE_BLUEGOO,      // hell
  RUNE_BLIZZARD,     // elder
  RUNE_THOR,         // earth
  
  // 53 - 56
  RUNE_SNIPER,       // black
  RUNE_ANTIPACK,     // hell
  RUNE_ANTITELE,     // elder
  RUNE_CLUSTER,      // earth
  
  // 57 - 59
  RUNE_TORNADO,      // black 
  RUNE_REQUIEM,      // hell
  RUNE_LITHIUM,      // elder

#define PW_NUM_RUNES RUNE_LITHIUM-RUNE_STRENGTH
#endif

	PW_NUM_POWERUPS // = 37,

} powerup_t;

#define PW_MAX_ITEMGROUPS (1 << (MAX_POWERUPS - PW_MAX_POWERUPS - 1))

#endif

#ifdef USE_ADVANCED_CLASS
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
	PCLASS_BARBARIAN,
	PCLASS_BARD,
	PCLASS_CLERIC,
	PCLASS_DRUID,
	PCLASS_FIGHTER,
	PCLASS_MONK,
	PCLASS_PALADIN,
	PCLASS_VISOR,
	PCLASS_RANGER,
	PCLASS_ROGUE,
	PCLASS_SORCERER,
	PCLASS_WARLOCK,
	PCLASS_WIZARD,
	PCLASS_FREEZE,
	PCLASS_ANTIGRAVITY,

	PCLASS_ROUND, // for ball physics

	// begin classes of monsters, not interested in item pickups
	PCLASS_MONSTER,
	PCLASS_SHAMBLER, // shambler
	PCLASS_DRAGON, // always flies because i lack animation ambition
	PCLASS_BERSERKER,
	PCLASS_GUNNER,
	PCLASS_VORE,

	PCLASS_MONSTER_COUNT,

	PCLASS_NUM_CLASSES
} pclass_t;
#endif

#ifdef USE_ADVANCED_WEAPONS

typedef enum {
	WP_NONE,
	WP_HANDS = WP_NONE, // class set to 0,1,2 but weapon select set to zero

	// Original ARENA
	WP_GAUNTLET = 1,
	WP_MACHINEGUN = 2,
	WP_SHOTGUN = 3,
	WP_GRENADE_LAUNCHER = 4,
	WP_ROCKET_LAUNCHER = 5,
	WP_LIGHTNING = 6,
	WP_RAILGUN = 7,
	WP_PLASMAGUN = 8,

	WP_CROWBAR = 9,

	WP_MOD_CLASSES = 10,

	// Fun guns and Team Arena
#ifdef USE_PORTALS
	WP_PORTAL_GUN = 10,
#endif
	WP_CHAINSAW = 11,
#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS) || defined(USE_ADVANCED_ITEMS)
	WP_CHAINGUN = 12,
	WP_NAILGUN = 13,
	WP_PROX_LAUNCHER = 14,
#endif
	WP_HOMING_ROCKET = 15,
	WP_THORS_HAMMER = 16,
#ifdef USE_FLAME_THROWER
	WP_FLAME_THROWER = 17,
#endif
	WP_BFG = 18,
#ifdef USE_GRAPPLE
	WP_GRAPPLING_HOOK = 19,
#endif

	// Open Arena
	WP_GAUNTLET2 = 21,
	WP_MACHINEGUN2 = 22,
	WP_SHOTGUN2 = 23,
	WP_GRENADE_LAUNCHER2 = 24,
	WP_ROCKET_LAUNCHER2 = 25,
	WP_LIGHTNING2 = 26,
	WP_RAILGUN2 = 27,
	WP_PLASMAGUN2 = 28,
	WP_BFG2 = 29,

	WP_CROSSBOW = 31,
	WP_ANNIHILATOR = 32,
	WP_TRESPASSER = 33,
	WP_PEACEMAKER = 35,
	WP_INCINERATOR = 36,
	WP_FROSTGUN = 38,
	WP_ICEBEAM = 39,

	// QUAKE 1
	WP_AXE = 41,
	WP_OSCILLATOR = 42,
	WP_MARAUDER = 43,
	WP_TRAILBLAZER = 44,
	WP_ORIGINAL = 45,
	WP_THUNDERBOLT = 46,
	WP_NAILGUN4 = 47,
	WP_CONDUCTOR = 48,

	// Quake 2
	WP_BLASTER = 51,
	WP_STEPCHILD2 = 52,
	WP_TRESPASSER2 = 53,
	WP_BITTERMAN = 53,
	WP_JOKER2 = 54,
	WP_PEACEMAKER2 = 55,
	WP_INCINERATOR2 = 56,
	WP_CHAINGUN2 = 56,
	WP_MALEDICTION = 57,
	WP_MALEDICTION2 = 57,
	WP_EXECUTIONER = 58,
	WP_EXECUTIONER2 = 58,
	WP_BFG10K = 59,

	// Doom 1
	// TODO: fists?
	WP_CHAINSAW3 = 61,
	WP_PISTOL = 62,
	WP_SHOTGUN3 = 63,
	// TODO: grenade 
	WP_ORIGINAL3 = 65,
	// TODO: lighning
	WP_CHAINGUN3 = 67,
	WP_PLASMAGUN3 = 68,
	WP_BFG9000 = 69,

	WP_NUM_WEAPONS = 70,
	WP_PENDING = WP_NUM_WEAPONS, // used in ui_players.c
	WP_MAX_WEAPONS = WP_MOD_CLASSES // for modulo 10 and classing based on 
	// 7 bits * classNum + weaponNum = 64 classes possible or 576 weapons/tools
} weapon_t;

#define WP_MAX_CLASSES (1 << (MAX_WEAPONS - WP_MAX_WEAPONS - 1))

#endif

// pmove->pm_flags
#define	PMF_DUCKED			1
#define	PMF_JUMP_HELD		2
#define	PMF_BACKWARDS_JUMP	8		// go into backwards land
#define	PMF_BACKWARDS_RUN	16		// coast down to backwards run
#define	PMF_TIME_LAND		32		// pm_time is time before rejump
#define	PMF_TIME_KNOCKBACK	64		// pm_time is an air-accelerate only time
#define	PMF_TIME_WATERJUMP	256		// pm_time is waterjump
#define	PMF_RESPAWNED		512		// clear after attack and jump buttons come up
#define	PMF_USE_ITEM_HELD	1024
#define PMF_GRAPPLE_PULL	2048	// pull towards grapple location
#define PMF_FOLLOW			4096	// spectate following another player
#define PMF_SCOREBOARD		8192	// spectate as a scoreboard
#define PMF_INVULEXPAND		16384	// invulnerability sphere set to full size

#define	PMF_ALL_TIMES	(PMF_TIME_WATERJUMP|PMF_TIME_LAND|PMF_TIME_KNOCKBACK)

#define	MAXTOUCH	32
typedef struct {
	// state (in / out)
	playerState_t	*ps;

	// command (in)
	usercmd_t	cmd;
	int			tracemask;			// collide against these types of surfaces
	int			debugLevel;			// if set, diagnostic output will be printed
	qboolean  noFootsteps;
	qboolean	gauntletHit;		// true if a gauntlet attack would actually hit something

	int			framecount;

	// results (out)
	int			numtouch;
	int			touchents[MAXTOUCH];

	vec3_t		mins, maxs;			// bounding box size

	int			watertype;
	int			waterlevel;

	float		xyspeed;

	// for fixed msec Pmove
	int			pmove_fixed;
	int			pmove_msec;


	// callbacks to test the world
	// these will be different functions during game and cgame
	void		(*trace)( trace_t *results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentMask );
	int			(*pointcontents)( const vec3_t point, int passEntityNum );

#ifdef USE_ADVANCED_WEAPONS
	int			classAmmo[WP_NUM_WEAPONS];
	int			classWeapons[WP_NUM_WEAPONS];
	int     weaponClass;
	qboolean classChange;
#endif

#ifdef USE_ADVANCED_ITEMS
	int inventory[PW_NUM_POWERUPS];
#endif

#ifdef USE_ADVANCED_CLASS
	pclass_t playerClass;
#endif

#ifdef USE_VEHICLES
// STONELANCE
        car_t           *car;
        car_t           **cars;

        int                     pDebug;

        qboolean        client;

        qboolean        manualShift;
        collisionDamage_t       damage;

        qboolean        (*frictionFunc)( const carPoint_t *point, float *sCOF, float *kCOF );

        float           car_spring;
        float           car_shock_up;
        float           car_shock_down;
        float           car_swaybar;
        float           car_wheel;
        float           car_wheel_damp;

        float           car_frontweight_dist;
        float           car_IT_xScale;
        float           car_IT_yScale;
        float           car_IT_zScale;
        float           car_body_elasticity;

        float           car_air_cof;
        float           car_air_frac_to_df;
        float           car_friction_scale;
	vec3_t		damageAngles;
	float		  damagePitch;
	float		  damageYaw;
// END

#endif


} pmove_t;

// if a full pmove isn't done on the client, you can just update the angles
void PM_UpdateViewAngles( playerState_t *ps, const usercmd_t *cmd );
void Pmove (pmove_t *pmove);

//===================================================================================


// player_state->stats[] indexes
// NOTE: may not have more than 16
typedef enum {
	STAT_HEALTH,
#if defined(USE_RPG_STATS) || defined(USE_ADVANCED_CLASS) || defined(USE_RUNES)
	STAT_STAMINA,
	STAT_ABILITY,
#endif
	STAT_ENTITY_POINTED,
#ifdef USE_ADVANCED_ITEMS
	STAT_HOLDABLE_AVAILABLE,
	STAT_HOLDABLE_UPDATE,
#else
	STAT_HOLDABLE_ITEM,
#endif
#ifndef USE_ADVANCED_ITEMS
#if defined(MISSIONPACK) || defined(USE_CLASSIC_HUD)
	STAT_PERSISTANT_POWERUP,
#endif
#endif
#ifdef USE_ADVANCED_WEAPONS
	STAT_WEAPONS_AVAILABLE,
	STAT_WEAPONS_UPDATE,
#else
	STAT_WEAPONS,					// 16 bit fields
#endif
	STAT_ARMOR,				
	STAT_DEAD_YAW,					// look this direction when dead (FIXME: get rid of?)
	STAT_CLIENTS_READY,				// bit mask of clients wishing to exit the intermission (FIXME: configstring?)
	STAT_MAX_HEALTH,					// health / armor limit, changable by handicap
#ifdef USE_VEHICLES
	STAT_VEHICLE,
#endif
#ifdef USE_ADVANCED_CLASS
	STAT_PLAYERCLASS,
#endif
#ifndef USE_ADVANCED_ITEMS
#ifdef USE_RUNES
	STAT_RUNE,
#endif
#endif
	STAT_NUM_STATS
} statIndex_t;


// player_state->persistant[] indexes
// these fields are the only part of player_state that isn't
// cleared on respawn
// NOTE: may not have more than 16
typedef enum {
	PERS_SCORE,						// !!! MUST NOT CHANGE, SERVER AND GAME BOTH REFERENCE !!!
	PERS_HITS,						// total points damage inflicted so damage beeps can sound on change
	PERS_RANK,						// player rank or team rank
	PERS_TEAM,						// player team
	PERS_SPAWN_COUNT,				// incremented every respawn
	PERS_PLAYEREVENTS,				// 16 bits that can be flipped for events
	PERS_ATTACKER,					// clientnum of last damage inflicter
	PERS_ATTACKEE_ARMOR,			// health/armor of last person we attacked
	PERS_KILLED,					// count of the number of times you died
	// player awards tracking
	PERS_IMPRESSIVE_COUNT,			// two railgun hits in a row
	PERS_EXCELLENT_COUNT,			// two successive kills in a short amount of time
	PERS_DEFEND_COUNT,				// defend awards
	PERS_ASSIST_COUNT,				// assist awards
	PERS_GAUNTLET_FRAG_COUNT,		// kills with the gauntlet
	PERS_CAPTURES					// captures
} persEnum_t;


// entityState_t->eFlags
#define	EF_DEAD							0x00000001		// don't draw a foe marker over players with EF_DEAD
#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS) || defined(USE_ADVANCED_ITEMS) || defined(USE_RUNES)
#define EF_TICKING					0x00000002		// used to make players play the prox mine ticking sound
#endif
#define	EF_TELEPORT_BIT			0x00000004		// toggled every time the origin abruptly changes
#define	EF_AWARD_EXCELLENT	0x00000008		// draw an excellent sprite
#define EF_PLAYER_EVENT			0x00000010
#define	EF_BOUNCE						0x00000010		// for missiles
#define	EF_BOUNCE_HALF			0x00000020		// for missiles
#define	EF_AWARD_GAUNTLET		0x00000040		// draw a gauntlet sprite
#define	EF_NODRAW						0x00000080		// may have an event, but no model (unspawned items)
#define	EF_FIRING						0x00000100		// for lightning gun
#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS) || defined(USE_RUNES) || defined(USE_SINGLEPLAYER)
#define	EF_KAMIKAZE					0x00000200
#endif
#define	EF_MOVER_STOP				0x00000400		// will push otherwise
#define EF_AWARD_CAP				0x00000800		// draw the capture sprite
#define	EF_TALK							0x00001000		// draw a talk balloon
#define	EF_CONNECTION				0x00002000		// draw a connection trouble sprite
#define	EF_VOTED						0x00004000		// already cast a vote
#define	EF_AWARD_IMPRESSIVE	0x00008000		// draw an impressive sprite
#define	EF_AWARD_DEFEND			0x00010000		// draw a defend sprite
#define	EF_AWARD_ASSIST			0x00020000		// draw a assist sprite
#define EF_AWARD_DENIED			0x00040000		// denied
#define EF_TEAMVOTED				0x00080000		// already cast a team vote

#ifdef USE_VEHICLES
#define EF_REVERSE      		0x00100000
#define EF_BRAKE        		0x00200000
#endif

#define EF_NOPICKUP      		0x00400000

#define EF_TIMER        		0x00000082		// 

#define EF_PERSISTANT ( EF_CONNECTION | EF_VOTED | EF_TEAMVOTED )
#define EF_AWARDS ( EF_AWARD_IMPRESSIVE | EF_AWARD_EXCELLENT | EF_AWARD_GAUNTLET | EF_AWARD_ASSIST | EF_AWARD_DEFEND | EF_AWARD_CAP )

#define EF_NOPREDICT ( EF_AWARDS | EF_PERSISTANT | EF_TALK )


#ifndef USE_ADVANCED_ITEMS


// NOTE: may not have more than 16
typedef enum {
	PW_NONE,

	PW_QUAD,
	PW_BATTLESUIT,
	PW_HASTE,
	PW_INVIS,
	PW_REGEN,
	PW_FLIGHT,

	PW_REDFLAG,
	PW_BLUEFLAG,
	PW_NEUTRALFLAG,

#if defined(USE_ADVANCED_GAMES) || defined(USE_ADVANCED_TEAMS)
	PW_GOLDFLAG,
	PW_GREENFLAG = PW_NEUTRALFLAG,
#endif

#if defined(MISSIONPACK) || defined(USE_RUNES) || defined(USE_ADVANCED_CLASS)
	PW_SCOUT,
	PW_GUARD,
	PW_DOUBLER,
	PW_AMMOREGEN,
	PW_INVULNERABILITY,
#endif

#if defined(USE_GAME_FREEZETAG) || defined(USE_REFEREE_CMDS)
  PW_FROZEN,
#endif

#if defined(USE_WEAPON_SPREAD) || defined(USE_RUNES)
  PW_SPREAD,  //Hal9000 spreadfire
#endif

#ifdef USE_ADVANCED_CLASS
	PW_SPECIAL_ABILITY,
#endif

	PW_NUM_POWERUPS

} powerup_t;

#ifdef USE_RUNES

typedef enum {

  // 1 - 4
  RUNE_STRENGTH,     // black
  RUNE_REGEN,        // hell
  RUNE_RESIST,       // elder
  RUNE_HASTE,        // earth
  
  // 5 - 8
  RUNE_ENVIRO,       // black
  RUNE_FLIGHT,       // hell
  RUNE_BERSERK,      // elder
  RUNE_RECALL,       // earth
  
  // 9 - 12
  RUNE_ELECTRIC,     // black
  RUNE_CLOAK,        // hell
  RUNE_DIVINE,       // elder
  RUNE_DEATH,        // earth
  
  // 13 - 16
  RUNE_HOLO,         // black
  RUNE_ORB,          // hell
  RUNE_BLINK,        // elder
  RUNE_CAMO,         // earth
  
  // 17 - 20
  RUNE_JUMP,         // black
  RUNE_ACTION,       // hell
  RUNE_VAMPIRE,      // elder
  RUNE_SHIELD,       // earth
  
  // 21 - 24
  RUNE_HEALTH,       // black
  RUNE_RADIO,        // hell
  RUNE_SWITCH,       // elder
  RUNE_ICETRAP,      // earth
  
  // 25 - 28
  RUNE_GRAVITY,      // black
  RUNE_TELE,         // hell
  RUNE_IMPACT,       // elder
  RUNE_VENGEANCE,    // earth
  
  // 29 - 32
  RUNE_SHUBHAT,      // black
  RUNE_REPULSION,    // hell
  RUNE_PHASING,      // elder
  RUNE_SHAMBLER,     // earth
  
  // 33 - 36
  RUNE_DUALRECALL,   // black
  RUNE_WEIRDNESS,    // hell
  RUNE_PHOENIX,      // elder
  RUNE_SPIKECLOUD,   // earth
  
  // 37 - 40
  RUNE_FIREWALK,     // black
  RUNE_GRAPPLE,      // hell
  RUNE_ATHLETIC,     // elder
  RUNE_LUMBERJACK,   // earth
  
  // 41 - 44
  RUNE_HOUNGAN,      // black
  RUNE_PIERCING,     // hell
  RUNE_PRESERVE,     // elder
  RUNE_ZENMONK,      // earth
  
  // 45 - 48
  RUNE_TORCH,        // black
  RUNE_PACKRAT,      // hell
  RUNE_ARMOR,        // elder
  RUNE_QUAD,         // earth
  
  // 49 - 52
  RUNE_JACK,         // black
  RUNE_BLUEGOO,      // hell
  RUNE_BLIZZARD,     // elder
  RUNE_THOR,         // earth
  
  // 53 - 56
  RUNE_SNIPER,       // black
  RUNE_ANTIPACK,     // hell
  RUNE_ANTITELE,     // elder
  RUNE_CLUSTER,      // earth
  
  // 57 - 59
  RUNE_TORNADO,      // black 
  RUNE_REQUIEM,      // hell
  RUNE_LITHIUM,      // elder

	RUNE_COUNT

} rune_t;
#define PW_NUM_RUNES RUNE_LITHIUM-RUNE_STRENGTH
#endif

#endif

#ifndef USE_ADVANCED_ITEMS

typedef enum {
	HI_NONE,

	HI_TELEPORTER,
	HI_MEDKIT,
	HI_KAMIKAZE,
	HI_PORTAL,
	HI_INVULNERABILITY,

	HI_NUM_HOLDABLE
} holdable_t;

#endif

#ifndef USE_ADVANCED_WEAPONS

typedef enum {
	WP_NONE,

	WP_GAUNTLET,
	WP_MACHINEGUN,
	WP_SHOTGUN,
	WP_GRENADE_LAUNCHER,
	WP_ROCKET_LAUNCHER,
	WP_LIGHTNING,
	WP_RAILGUN,
	WP_PLASMAGUN,
	WP_BFG,
	WP_GRAPPLING_HOOK,
#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS) || defined(USE_ADVANCED_CLASS)
	WP_NAILGUN,
	WP_PROX_LAUNCHER,
	WP_CHAINGUN,
#endif
#ifdef USE_FLAME_THROWER
	WP_FLAME_THROWER,
#endif
#if defined(USE_ADVANCED_ITEMS) || defined(USE_ADVANCED_CLASS) || defined(USE_HOMING_MISSILE)
	WP_HOMING_ROCKET,
#endif

	WP_NUM_WEAPONS,
	WP_PENDING = WP_NUM_WEAPONS, // used in ui_players.c
	WP_MAX_WEAPONS = 16
} weapon_t;

#endif

// reward sounds (stored in ps->persistant[PERS_PLAYEREVENTS])
#define	PLAYEREVENT_DENIEDREWARD		0x0001
#define	PLAYEREVENT_GAUNTLETREWARD		0x0002
#define PLAYEREVENT_HOLYSHIT			0x0004

// entityState_t->event values
// entity events are for effects that take place relative
// to an existing entities origin.  Very network efficient.

// two bits at the top of the entityState->event field
// will be incremented with each change in the event so
// that an identical event started twice in a row can
// be distinguished.  And off the value with ~EV_EVENT_BITS
// to retrieve the actual event number
#define	EV_EVENT_BIT1		0x00000100
#define	EV_EVENT_BIT2		0x00000200
#define	EV_EVENT_BITS		(EV_EVENT_BIT1|EV_EVENT_BIT2)

#define	EVENT_VALID_MSEC	300

typedef enum {
	EV_NONE,

	EV_FOOTSTEP,
	EV_FOOTSTEP_METAL,
	EV_FOOTSPLASH,
	EV_FOOTWADE,
	EV_SWIM,

	EV_STEP_4,
	EV_STEP_8,
	EV_STEP_12,
	EV_STEP_16,

	EV_FALL_SHORT,
	EV_FALL_MEDIUM,
	EV_FALL_FAR,

	EV_JUMP_PAD,			// boing sound at origin, jump sound on player

	EV_JUMP,
	EV_WATER_TOUCH,	// foot touches
	EV_WATER_LEAVE,	// foot leaves
	EV_WATER_UNDER,	// head touches
	EV_WATER_CLEAR,	// head leaves

	EV_ITEM_PICKUP,			// normal item pickups are predictable
	EV_GLOBAL_ITEM_PICKUP,	// powerup / team sounds are broadcast to everyone

	EV_NOAMMO,
	EV_CHANGE_WEAPON,
	EV_FIRE_WEAPON,

	EV_USE_ITEM0,
	EV_USE_ITEM1,
	EV_USE_ITEM2,
	EV_USE_ITEM3,
	EV_USE_ITEM4,
	EV_USE_ITEM5,
	EV_USE_ITEM6,
	EV_USE_ITEM7,
	EV_USE_ITEM8,
	EV_USE_ITEM9,
	EV_USE_ITEM10,
	EV_USE_ITEM11,
	EV_USE_ITEM12,
	EV_USE_ITEM13,
	EV_USE_ITEM14,
	EV_USE_ITEM15,

	EV_ITEM_RESPAWN,
	EV_ITEM_POP,
	EV_PLAYER_TELEPORT_IN,
	EV_PLAYER_TELEPORT_OUT,

	EV_GRENADE_BOUNCE,		// eventParm will be the soundindex

	EV_GENERAL_SOUND,
	EV_GLOBAL_SOUND,		// no attenuation
	EV_GLOBAL_TEAM_SOUND,

	EV_BULLET_HIT_FLESH,
	EV_BULLET_HIT_WALL,

	EV_MISSILE_HIT,
	EV_MISSILE_MISS,
	EV_MISSILE_MISS_METAL,
	EV_RAILTRAIL,
	EV_SHOTGUN,
	EV_BULLET,				// otherEntity is the shooter

	EV_PAIN,
	EV_DEATH1,
	EV_DEATH2,
	EV_DEATH3,
	EV_OBITUARY,

	EV_POWERUP_QUAD,
	EV_POWERUP_BATTLESUIT,
	EV_POWERUP_REGEN,

	EV_GIB_PLAYER,			// gib a previously living player
	EV_SCOREPLUM,			// score plum

//#ifdef MISSIONPACK
	EV_PROXIMITY_MINE_STICK,
	EV_PROXIMITY_MINE_TRIGGER,
	EV_KAMIKAZE,			// kamikaze explodes
	EV_OBELISKEXPLODE,		// obelisk explodes
	EV_OBELISKPAIN,			// obelisk is in pain
	EV_INVUL_IMPACT,		// invulnerability sphere impact
	EV_JUICED,				// invulnerability juiced effect
	EV_LIGHTNINGBOLT,		// lightning bolt bounced of invulnerability sphere
//#endif

	EV_DEBUG_LINE,
	EV_STOPLOOPINGSOUND,
	EV_TAUNT,
	EV_TAUNT_YES,
	EV_TAUNT_NO,
	EV_TAUNT_FOLLOWME,
	EV_TAUNT_GETFLAG,
	EV_TAUNT_GUARDBASE,
	EV_TAUNT_PATROL,


#if defined(USE_WEAPON_ORDER) || defined(USE_ADVANCED_ITEMS)
  EV_ITEM_PICKUP2,			// had items
  EV_ITEM_PICKUP4,			// had items
  EV_ITEM_PICKUP6,			// had items
#endif
#ifdef USE_ADVANCED_ITEMS
	EV_ITEM_PICKUP3,			// had items
	EV_ITEM_PICKUP5,			// had items
	EV_GLOBAL_ITEM_PICKUP2,
	EV_GLOBAL_ITEM_PICKUP3,
#endif

#ifdef USE_SINGLEPLAYER // entity
	EV_PLAYERSTOP,
	EV_EARTHQUAKE,
	EV_USE,
#endif

#ifdef USE_HEADSHOTS
  EV_GIB_PLAYER_HEADSHOT,
  EV_BODY_NOHEAD,
#endif

#ifdef USE_LV_DISCHARGE
  EV_LV_DISCHARGE,
#endif

#ifdef USE_BIRDS_EYE
	EV_CURSORSTART,
#endif

#ifdef USE_DAMAGE_PLUMS
  EV_DAMAGEPLUM,			// damage plum
#endif

#ifdef USE_RPG_STATS
	EV_HEALTHPLUM,
#endif

#if defined(USE_GAME_FREEZETAG) || defined(USE_REFEREE_CMDS)
  EV_FROZEN,
  EV_UNFROZEN,
#endif

#ifdef USE_ALT_FIRE
  EV_ALTFIRE_WEAPON,
  EV_ALTFIRE_BOTH,
#endif

	EV_MAX,
} entity_event_t;


typedef enum {
	GTS_RED_CAPTURE,
	GTS_BLUE_CAPTURE,
	GTS_RED_RETURN,
	GTS_BLUE_RETURN,
	GTS_RED_TAKEN,
	GTS_BLUE_TAKEN,
	GTS_REDOBELISK_ATTACKED,
	GTS_BLUEOBELISK_ATTACKED,
	GTS_REDTEAM_SCORED,
	GTS_BLUETEAM_SCORED,
	GTS_REDTEAM_TOOK_LEAD,
	GTS_BLUETEAM_TOOK_LEAD,
	GTS_TEAMS_ARE_TIED,
#if defined(USE_ADVANCED_GAMES) || defined(USE_ADVANCED_TEAMS)
	GTS_GOLD_CAPTURE,
	GTS_GREEN_CAPTURE,
	GTS_GOLD_RETURN,
	GTS_GREEN_RETURN,
	GTS_GOLD_TAKEN,
	GTS_GREEN_TAKEN,
	GTS_GOLDTEAM_SCORED,
	GTS_GREENTEAM_SCORED,
	GTS_GOLDTEAM_TOOK_LEAD,
	GTS_GREENTEAM_TOOK_LEAD,
#endif
	GTS_KAMIKAZE
} global_team_sound_t;

// animations
typedef enum {
	BOTH_DEATH1,
	BOTH_DEAD1,
	BOTH_DEATH2,
	BOTH_DEAD2,
	BOTH_DEATH3,
	BOTH_DEAD3,

	TORSO_GESTURE,

	TORSO_ATTACK,
	TORSO_ATTACK2,

	TORSO_DROP,
	TORSO_RAISE,

	TORSO_STAND,
	TORSO_STAND2,

	LEGS_WALKCR,
	LEGS_WALK,
	LEGS_RUN,
	LEGS_BACK,
	LEGS_SWIM,

	LEGS_JUMP,
	LEGS_LAND,

	LEGS_JUMPB,
	LEGS_LANDB,

	LEGS_IDLE,
	LEGS_IDLECR,

	LEGS_TURN,

	TORSO_GETFLAG,
	TORSO_GUARDBASE,
	TORSO_PATROL,
	TORSO_FOLLOWME,
	TORSO_AFFIRMATIVE,
	TORSO_NEGATIVE,

	MAX_ANIMATIONS,

	LEGS_BACKCR,
	LEGS_BACKWALK,
	FLAG_RUN,
	FLAG_STAND,
	FLAG_STAND2RUN,

	TORSO_ATTACK3,
	TORSO_ATTACK4,
	TORSO_ATTACKCR1,
	TORSO_ATTACKCR2,

	MAX_TOTALANIMATIONS
} animNumber_t;


typedef struct animation_s {
	int		firstFrame;
	int		numFrames;
	int		loopFrames;			// 0 to numFrames
	int		frameLerp;			// msec between frames
	int		initialLerp;		// msec to get to first frame
	int		reversed;			// true if animation is reversed
	int		flipflop;			// true if animation should flipflop back to base
} animation_t;


// flip the togglebit every time an animation
// changes so a restart of the same anim can be detected
#define	ANIM_TOGGLEBIT		128


typedef enum {
	TEAM_FREE,
	TEAM_RED,
	TEAM_BLUE,

#if defined(USE_ADVANCED_GAMES) || defined(USE_ADVANCED_TEAMS)
	TEAM_GOLD,
	TEAM_GREEN,
#endif

	TEAM_SPECTATOR,

	TEAM_NUM_TEAMS
} team_t;


typedef enum {
	TAG_NONE = 0,
	TAG_DONTSPAWN,
} tag_t;

// Time between location updates
#define TEAM_LOCATION_UPDATE_TIME		1000

// How many players on the overlay
#define TEAM_MAXOVERLAY		32

//team task
typedef enum {
	TEAMTASK_NONE,
	TEAMTASK_OFFENSE, 
	TEAMTASK_DEFENSE,
	TEAMTASK_PATROL,
	TEAMTASK_FOLLOW,
	TEAMTASK_RETRIEVE,
	TEAMTASK_ESCORT,
	TEAMTASK_CAMP
} teamtask_t;

#ifdef USE_LOCAL_DMG
#define LOCATION_NONE		0x00000000

// Height layers
#define LOCATION_HEAD		0x00000001 // [F,B,L,R] Top of head
#define LOCATION_FACE		0x00000002 // [F] Face [B,L,R] Head
#define LOCATION_SHOULDER	0x00000004 // [L,R] Shoulder [F] Throat, [B] Neck
#define LOCATION_CHEST		0x00000008 // [F] Chest [B] Back [L,R] Arm
#define LOCATION_STOMACH	0x00000010 // [L,R] Sides [F] Stomach [B] Lower Back
#define LOCATION_GROIN		0x00000020 // [F] Groin [B] Butt [L,R] Hip
#define LOCATION_LEG		0x00000040 // [F,B,L,R] Legs
#define LOCATION_FOOT		0x00000080 // [F,B,L,R] Bottom of Feet

// Relative direction strike came from
#define LOCATION_LEFT		0x00000100
#define LOCATION_RIGHT		0x00000200
#define LOCATION_FRONT		0x00000400
#define LOCATION_BACK		0x00000800
#endif

// means of death
typedef enum {
	MOD_UNKNOWN,
	MOD_SHOTGUN,
	MOD_GAUNTLET,
	MOD_MACHINEGUN,
	MOD_GRENADE,
	MOD_GRENADE_SPLASH,
	MOD_ROCKET,
	MOD_ROCKET_SPLASH,
	MOD_PLASMA,
	MOD_PLASMA_SPLASH,
	MOD_RAILGUN,
	MOD_LIGHTNING,
	MOD_BFG,
	MOD_BFG_SPLASH,
	MOD_WATER,
	MOD_SLIME,
	MOD_LAVA,
	MOD_CRUSH,
	MOD_TELEFRAG,
	MOD_FALLING,
	MOD_SUICIDE,
	MOD_TARGET_LASER,
#ifdef USE_MODES_DEATH
	MOD_SPECTATE,
  MOD_VOID,
  MOD_RING_OUT,
  MOD_FROM_GRAVE,
#endif
	MOD_TRIGGER_HURT,
#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS) || defined(USE_ADVANCED_ITEMS) || defined(USE_SINGLEPLAYER)
	MOD_NAIL,
	MOD_CHAINGUN,
	MOD_PROXIMITY_MINE,
	MOD_KAMIKAZE,
	MOD_JUICED,
#endif
#ifdef USE_FLAME_THROWER
  MOD_FLAME_THROWER,
#endif
#ifdef USE_LV_DISCHARGE
  MOD_LV_DISCHARGE,
#endif
#ifdef USE_HEADSHOTS
  MOD_HEADSHOT,
#endif

	MOD_GRAPPLE,

#ifdef USE_VEHICLES
	MOD_HIGH_FORCES,
	MOD_BO_SHOCKS,
	MOD_WORLD_COLLISION,
#endif

#ifdef USE_RUNES
	MOD_RUNE_STRENGTH,
	MOD_RUNE_BERSERK,
	MOD_RUNE_PIERCING,
	MOD_RUNE_DIVINITY,
#endif

	MOD_MAX
} meansOfDeath_t;


//---------------------------------------------------------

// gitem_t->type
typedef enum {
	IT_BAD,
	IT_WEAPON,				// EFX: rotate + upscale + minlight
	IT_AMMO,				// EFX: rotate
	IT_ARMOR,				// EFX: rotate + minlight
	IT_HEALTH,				// EFX: static external sphere + rotating internal
	IT_POWERUP,				// instant on, timer based
							// EFX: rotate + external ring that rotates
	IT_HOLDABLE,			// single use, holdable item
							// EFX: rotate + bob
	IT_PERSISTANT_POWERUP,
	IT_TEAM,
#if defined(USE_ADVANCED_ITEMS) || defined(USE_ADVANCED_CLASS)
	IT_WEAPON2,  //  stationary
	IT_AMMO2,  //  stationary
	IT_ARMOR2,      // like the name implies, quake2 pickups are stationary
	IT_HEALTH2,  //  stationary
	IT_POWERUP2,  //  stationary
	IT_HOLDABLE2,  //  stationary
	IT_PERSISTANT_POWERUP2, //  stationary
	IT_TEAM2, //  stationary
#endif
	IT_NUM_TYPES
} itemType_t;

#define MAX_ITEM_MODELS 4

typedef struct gitem_s {
	const char	*classname;	// spawning name
	char		*pickup_sound;
	char		*world_model[MAX_ITEM_MODELS];

	char		*icon;
	char		*pickup_name;	// for printing on pickup

	int			quantity;		// for ammo how much, or duration of powerup
	itemType_t  giType;			// IT_* flags

	int			const giTag;

	char		const *precaches;		// string of all models and images this item will use
	char		const *sounds;		// string of all sounds this item will use
	char		*skinNames[MAX_ITEM_MODELS];
	animation_t animation;
	int renderfx;
} gitem_t;

// included in both the game dll and the client
extern	gitem_t	bg_itemlist[];
extern	int		bg_numItems;

gitem_t	*BG_FindItem( const char *pickupName );
gitem_t	*BG_FindItemForWeapon( weapon_t weapon );
gitem_t	*BG_FindAmmoForWeapon( weapon_t weapon );
gitem_t	*BG_FindItemForPowerup( powerup_t pw );
#ifdef USE_ADVANCED_CLASS
pclass_t BG_PlayerClassFromModel(const char *model);
#endif
#ifdef USE_RUNES
gitem_t	*BG_FindItemForRune( int r );
#endif
#ifndef USE_ADVANCED_ITEMS
gitem_t	*BG_FindItemForHoldable( holdable_t pw );
#endif
#define	ITEM_INDEX(x) ((x)-bg_itemlist)

qboolean BG_CanItemBeGrabbed( int gametype, const entityState_t *ent,
#ifdef USE_ADVANCED_ITEMS
	const int *inventory, 
#endif
#ifdef USE_ADVANCED_CLASS
	int playerClass, 
#endif
#ifdef USE_ADVANCED_WEAPONS
	int classWeapons[WP_MAX_WEAPONS],
	int classAmmo[WP_MAX_WEAPONS],
#endif
	const playerState_t *ps
);

// g_dmflags->integer flags
#define	DF_NO_FALLING			8
#define DF_FIXED_FOV			16
#define	DF_NO_FOOTSTEPS			32

// content masks
#define	MASK_ALL				(-1)
#define	MASK_SOLID				(CONTENTS_SOLID)
#define	MASK_PLAYERSOLID		(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_BODY)
#define	MASK_DEADSOLID			(CONTENTS_SOLID|CONTENTS_PLAYERCLIP)
#define	MASK_WATER				(CONTENTS_WATER|CONTENTS_LAVA|CONTENTS_SLIME)
#define	MASK_OPAQUE				(CONTENTS_SOLID|CONTENTS_SLIME|CONTENTS_LAVA)
#define	MASK_SHOT				(CONTENTS_SOLID|CONTENTS_BODY|CONTENTS_CORPSE)


//
// entityState_t->eType
//
typedef enum {
	ET_GENERAL,
	ET_PLAYER,
	ET_ITEM,
	ET_MISSILE,
	ET_MOVER,
	ET_BEAM,
	ET_PORTAL,
	ET_SPEAKER,
	ET_PUSH_TRIGGER,
	ET_TELEPORT_TRIGGER,
	ET_INVISIBLE,
	ET_GRAPPLE,				// grapple hooked on wall
	ET_TEAM,
#ifdef USE_LASER_SIGHT
  ET_LASER,         // lasersight entity type
#endif
#ifdef USE_BIRDS_EYE
	ET_CURSOR,
#endif

	ET_EVENTS				// any of the EV_* events can be added freestanding
							// by setting eType to ET_EVENTS + eventNum
							// this avoids having to set eFlags and eventNum
} entityType_t;

// calculated by modulus.c for appropriate dividers:
#define TMOD_004  4272943
#define TMOD_075  2292106
#define TMOD_1000 5730265
#define TMOD_2000 5730265

void	BG_EvaluateTrajectory( const trajectory_t *tr, int atTime, vec3_t result );
void	BG_EvaluateTrajectoryDelta( const trajectory_t *tr, int atTime, vec3_t result );

void	BG_AddPredictableEventToPlayerstate( entity_event_t newEvent, int eventParm, playerState_t *ps, int entityNum );

void BG_TouchJumpPad( playerState_t *ps, entityState_t *jumppad
#ifdef USE_ADVANCED_ITEMS
, const int *inventory
#endif
#ifdef USE_ADVANCED_CLASS
, const int playerClass 
#endif
);

void	BG_PlayerStateToEntityState( playerState_t *ps, entityState_t *s, qboolean snap );
void	BG_PlayerStateToEntityStateExtraPolate( playerState_t *ps, entityState_t *s, int time, qboolean snap );

qboolean	BG_PlayerTouchesItem( playerState_t *ps, entityState_t *item, int atTime );


#define ARENAS_PER_TIER		4
#define MAX_ARENAS			1024
#define	MAX_ARENAS_TEXT		8192

#define MAX_BOTS			1024
#define MAX_BOTS_TEXT		8192


// Kamikaze

// 1st shockwave times
#define KAMI_SHOCKWAVE_STARTTIME		0
#define KAMI_SHOCKWAVEFADE_STARTTIME	1500
#define KAMI_SHOCKWAVE_ENDTIME			2000
// explosion/implosion times
#define KAMI_EXPLODE_STARTTIME			250
#define KAMI_IMPLODE_STARTTIME			2000
#define KAMI_IMPLODE_ENDTIME			2250
// 2nd shockwave times
#define KAMI_SHOCKWAVE2_STARTTIME		2000
#define KAMI_SHOCKWAVE2FADE_STARTTIME	2500
#define KAMI_SHOCKWAVE2_ENDTIME			3000
// radius of the models without scaling
#define KAMI_SHOCKWAVEMODEL_RADIUS		88
#define KAMI_BOOMSPHEREMODEL_RADIUS		72
// maximum radius of the models during the effect
#define KAMI_SHOCKWAVE_MAXRADIUS		1320
#define KAMI_BOOMSPHERE_MAXRADIUS		720
#define KAMI_SHOCKWAVE2_MAXRADIUS		704


#define MAX_MAP_SIZE 65536

// custom functions
#ifdef BUILD_GAME_STATIC
intptr_t CG_Call( int command, int arg0, int arg1, int arg2 );
intptr_t G_Call( int command, int arg0, int arg1, int arg2 );
intptr_t UI_Call( int command, int arg0, int arg1, int arg2 );
#endif

int BG_sprintf( char *buf, const char *format, ... );
int ED_vsprintf( char *buffer, const char *fmt, va_list argptr );

char *strtok( char *strToken, const char *strDelimit );
char *EncodedString( const char *str );
char *DecodedString( const char *str );

void BG_CleanName( const char *in, char *out, int outSize, const char *blankString );
char *BG_StripColor( char *string );

void Q_strcpy( char *dst, const char *src );
char *Q_stradd( char *dst, const char *src );
int Q_sscanf( const char *buffer, const char *fmt, ... );

qboolean replace1( const char match, const char replace, char *str );

qboolean  BigEndian( void );

//#endif // __BG_PUBLIC_H
#define MAX_MAP_SIZE 65536

// Tracemap
#ifdef CGAME
void CG_GenerateTracemap( void );
#endif // CGAMEDLL
qboolean BG_LoadTraceMap( char *rawmapname, vec2_t world_mins, vec2_t world_maxs );
float BG_GetSkyHeightAtPoint( vec3_t pos );
float BG_GetSkyGroundHeightAtPoint( vec3_t pos );
float BG_GetGroundHeightAtPoint( vec3_t pos );
int BG_GetTracemapGroundFloor( void );
int BG_GetTracemapGroundCeil( void );
