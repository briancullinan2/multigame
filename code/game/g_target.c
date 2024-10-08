// Copyright (C) 1999-2000 Id Software, Inc.
//
#include "g_local.h"

//==========================================================

/*QUAKED target_give (1 0 0) (-8 -8 -8) (8 8 8)
Gives the activator all the items pointed to.
*/
void Use_Target_Give( gentity_t *ent, gentity_t *other, gentity_t *activator ) {
	gentity_t	*t;
	trace_t		trace;

	if ( !activator->client ) {
		return;
	}

	if ( !ent->target ) {
		return;
	}

	memset( &trace, 0, sizeof( trace ) );
	t = NULL;
	while ( (t = G_Find (t, FOFS(targetname), ent->target)) != NULL ) {
		if ( !t->item ) {
			continue;
		}
		Touch_Item( t, activator, &trace );

		// make sure it isn't going to respawn or show any events
		t->tag = TAG_DONTSPAWN;
		t->nextthink = 0;
		trap_UnlinkEntity( t );
	}
}

void SP_target_give( gentity_t *ent ) {
	ent->use = Use_Target_Give;
}


//==========================================================

/*QUAKED target_remove_powerups (1 0 0) (-8 -8 -8) (8 8 8)
takes away all the activators powerups.
Used to drop flight powerups into death puts.
*/
void Use_target_remove_powerups( gentity_t *ent, gentity_t *other, gentity_t *activator ) {
	if( !activator->client ) {
		return;
	}

#ifdef USE_ADVANCED_ITEMS
	if( activator->client->inventory[PW_REDFLAG] ) {
		Team_ReturnFlag( TEAM_RED );
	} else if( activator->client->inventory[PW_BLUEFLAG] ) {
		Team_ReturnFlag( TEAM_BLUE );
#if defined(USE_ADVANCED_GAMES) || defined(USE_ADVANCED_TEAMS)
	} else if( activator->client->inventory[PW_GOLDFLAG] ) {
		Team_ReturnFlag( TEAM_GOLD );
	} else if( activator->client->inventory[PW_GREENFLAG] ) {
		Team_ReturnFlag( TEAM_GREEN );
#endif
	} else if( activator->client->inventory[PW_NEUTRALFLAG] ) {
		Team_ReturnFlag( TEAM_FREE );
	}
#else
	if( activator->client->ps.powerups[PW_REDFLAG] ) {
		Team_ReturnFlag( TEAM_RED );
	} else if( activator->client->ps.powerups[PW_BLUEFLAG] ) {
		Team_ReturnFlag( TEAM_BLUE );
#if defined(USE_ADVANCED_GAMES) || defined(USE_ADVANCED_TEAMS)
	} else if( activator->client->ps.powerups[PW_GOLDFLAG] ) {
		Team_ReturnFlag( TEAM_GOLD );
	} else if( activator->client->ps.powerups[PW_GREENFLAG] ) {
		Team_ReturnFlag( TEAM_GREEN );
#endif
	} else if( activator->client->ps.powerups[PW_NEUTRALFLAG] ) {
		Team_ReturnFlag( TEAM_FREE );
	}
#endif

#ifdef USE_ADVANCED_ITEMS
	memset( activator->client->inventory, 0, sizeof( activator->client->inventory ) );
	memset( activator->client->ps.powerTimes, 0, sizeof( activator->client->ps.powerTimes ) );
#else
	memset( activator->client->ps.powerups, 0, sizeof( activator->client->ps.powerups ) );
#endif
}

void SP_target_remove_powerups( gentity_t *ent ) {
	ent->use = Use_target_remove_powerups;
}


//==========================================================

/*QUAKED target_delay (1 0 0) (-8 -8 -8) (8 8 8)
"wait" seconds to pause before firing targets.
"random" delay variance, total delay = delay +/- random seconds
*/
void Think_Target_Delay( gentity_t *ent ) {
	G_UseTargets( ent, ent->activator );
}

void Use_Target_Delay( gentity_t *ent, gentity_t *other, gentity_t *activator ) {
	ent->nextthink = level.time + ( ent->wait + ent->random * crandom() ) * 1000;
	ent->think = Think_Target_Delay;
	ent->activator = activator;
}

void SP_target_delay( gentity_t *ent ) {
	// check delay for backwards compatability
	if ( !G_SpawnFloat( "delay", "0", &ent->wait ) ) {
		G_SpawnFloat( "wait", "1", &ent->wait );
	}

	if ( !ent->wait ) {
		ent->wait = 1;
	}
	ent->use = Use_Target_Delay;
}


//==========================================================

/*QUAKED target_score (1 0 0) (-8 -8 -8) (8 8 8)
"count" number of points to add, default 1

The activator is given this many points.
*/
void Use_Target_Score (gentity_t *ent, gentity_t *other, gentity_t *activator) {
	if ( !activator )
		return;
	AddScore( activator, ent->r.currentOrigin, ent->count );
}

void SP_target_score( gentity_t *ent ) {
	if ( !ent->count ) {
		ent->count = 1;
	}
	ent->use = Use_Target_Score;
}


//==========================================================

/*QUAKED target_print (1 0 0) (-8 -8 -8) (8 8 8) redteam blueteam private
"message"	text to print
If "private", only the activator gets the message.  If no checks, all clients get the message.
*/
void Use_Target_Print (gentity_t *ent, gentity_t *other, gentity_t *activator) {
	if ( activator && activator->client && ( ent->spawnflags & 4 ) ) {
		trap_SendServerCommand( activator-g_entities, va("cp \"%s\"", ent->message ));
		return;
	}

	if ( ent->spawnflags & 3 ) {
		if ( ent->spawnflags & 1 ) {
			G_TeamCommand( TEAM_RED, va("cp \"%s\"", ent->message) );
		}
		if ( ent->spawnflags & 2 ) {
			G_TeamCommand( TEAM_BLUE, va("cp \"%s\"", ent->message) );
		}
		return;
	}

	G_BroadcastServerCommand( -1, va("cp \"%s\"", ent->message ));
}

void SP_target_print( gentity_t *ent ) {
	ent->use = Use_Target_Print;
}


//==========================================================


/*QUAKED target_speaker (1 0 0) (-8 -8 -8) (8 8 8) looped-on looped-off global activator
"noise"		wav file to play

A global sound will play full volume throughout the level.
Activator sounds will play on the player that activated the target.
Global and activator sounds can't be combined with looping.
Normal sounds play each time the target is used.
Looped sounds will be toggled by use functions.
Multiple identical looping sounds will just increase volume without any speed cost.
"wait" : Seconds between auto triggerings, 0 = don't auto trigger
"random"	wait variance, default is 0
*/
void Use_Target_Speaker (gentity_t *ent, gentity_t *other, gentity_t *activator) {
	if (ent->spawnflags & 3) {	// looping sound toggles
		if (ent->s.loopSound)
			ent->s.loopSound = 0;	// turn it off
		else
			ent->s.loopSound = ent->noise_index;	// start it
	}else {	// normal sound
		if ( ent->spawnflags & 8 && activator ) {
			G_AddEvent( activator, EV_GENERAL_SOUND, ent->noise_index );
		} else if (ent->spawnflags & 4) {
			G_AddEvent( ent, EV_GLOBAL_SOUND, ent->noise_index );
		} else {
			G_AddEvent( ent, EV_GENERAL_SOUND, ent->noise_index );
		}
	}
}

void SP_target_speaker( gentity_t *ent ) {
	char	buffer[MAX_QPATH];
	char	*s;

	G_SpawnFloat( "wait", "0", &ent->wait );
	G_SpawnFloat( "random", "0", &ent->random );

	if ( !G_SpawnString( "noise", "NOSOUND", &s ) ) {
		G_Error( "target_speaker without a noise key at %s", vtos( ent->s.origin ) );
	}

	// force all client relative sounds to be "activator" speakers that
	// play on the entity that activates it
	if ( s[0] == '*' ) {
		ent->spawnflags |= 8;
	}

	if (!strstr( s, ".wav" )) {
		Com_sprintf (buffer, sizeof(buffer), "%s.wav", s );
	} else {
		Q_strncpyz( buffer, s, sizeof(buffer) );
	}
	ent->noise_index = G_SoundIndex(buffer);

	// a repeating speaker can be done completely client side
	ent->s.eType = ET_SPEAKER;
	ent->s.eventParm = ent->noise_index;
	ent->s.frame = ent->wait * 10;
	ent->s.clientNum = ent->random * 10;


	// check for prestarted looping sound
	if ( ent->spawnflags & 1 )
		ent->s.loopSound = ent->noise_index;
	else
		ent->s.loopSound = 0;

	ent->use = Use_Target_Speaker;

	if (ent->spawnflags & 4) {
		ent->r.svFlags |= SVF_BROADCAST;
	}

	VectorCopy( ent->s.origin, ent->s.pos.trBase );

	// must link the entity so we get areas and clusters so
	// the server can determine who to send updates to
	trap_LinkEntity( ent );
}



//==========================================================

/*QUAKED target_laser (0 .5 .8) (-8 -8 -8) (8 8 8) START_ON
When triggered, fires a laser.  You can either set a target or a direction.
*/
void target_laser_think (gentity_t *self) {
	vec3_t	end;
	trace_t	tr;
	vec3_t	point;

	// if pointed at another entity, set movedir to point at it
	if ( self->enemy ) {
		VectorMA (self->enemy->s.origin, 0.5, self->enemy->r.mins, point);
		VectorMA (point, 0.5, self->enemy->r.maxs, point);
		VectorSubtract (point, self->s.origin, self->movedir);
		VectorNormalize (self->movedir);
	}

	// fire forward and see what we hit
	VectorMA (self->s.origin, 2048, self->movedir, end);

	trap_Trace( &tr, self->s.origin, NULL, NULL, end, self->s.number, CONTENTS_SOLID|CONTENTS_BODY|CONTENTS_CORPSE);

	if ( tr.entityNum ) {
		// hurt it if we can
		G_Damage ( &g_entities[tr.entityNum], self, self->activator, self->movedir, 
			tr.endpos, self->damage, DAMAGE_NO_KNOCKBACK, MOD_TARGET_LASER);
	}

	VectorCopy (tr.endpos, self->s.origin2);

	trap_LinkEntity( self );
	self->nextthink = level.time + FRAMETIME;
}

void target_laser_on (gentity_t *self)
{
	if (!self->activator)
		self->activator = self;
	target_laser_think (self);
}

void target_laser_off (gentity_t *self)
{
	trap_UnlinkEntity( self );
	self->nextthink = 0;
}

void target_laser_use (gentity_t *self, gentity_t *other, gentity_t *activator)
{
	self->activator = activator;
	if ( self->nextthink > 0 )
		target_laser_off (self);
	else
		target_laser_on (self);
}

void target_laser_start (gentity_t *self)
{
	gentity_t *ent;

	self->s.eType = ET_BEAM;

	if (self->target) {
		ent = G_Find (NULL, FOFS(targetname), self->target);
		if (!ent) {
			G_Printf ("%s at %s: %s is a bad target\n", self->classname, vtos(self->s.origin), self->target);
		}
		self->enemy = ent;
	} else {
		G_SetMovedir (self->s.angles, self->movedir);
	}

	self->use = target_laser_use;
	self->think = target_laser_think;

	if ( !self->damage ) {
		self->damage = 1;
	}

	if (self->spawnflags & 1)
		target_laser_on (self);
	else
		target_laser_off (self);
}

void SP_target_laser (gentity_t *self)
{
	// let everything else get spawned before we start firing
	self->think = target_laser_start;
	self->nextthink = level.time + FRAMETIME;
}


//==========================================================

void target_teleporter_use( gentity_t *self, gentity_t *other, gentity_t *activator ) {
	gentity_t	*dest;

	if ( !activator || !activator->client )
		return;
	dest = 	G_PickTarget( self->target );
	if (!dest) {
		G_Printf ("Couldn't find teleporter destination\n");
		return;
	}

	TeleportPlayer( activator, dest->s.origin, dest->s.angles );
}

/*QUAKED target_teleporter (1 0 0) (-8 -8 -8) (8 8 8)
The activator will be teleported away.
*/
void SP_target_teleporter( gentity_t *self ) {
	if (!self->targetname)
		G_Printf("untargeted %s at %s\n", self->classname, vtos(self->s.origin));

	self->use = target_teleporter_use;
}

//==========================================================


/*QUAKED target_relay (.5 .5 .5) (-8 -8 -8) (8 8 8) RED_ONLY BLUE_ONLY RANDOM
This doesn't perform any actions except fire its targets.
The activator can be forced to be from a certain team.
if RANDOM is checked, only one of the targets will be fired, not all of them
*/
void target_relay_use (gentity_t *self, gentity_t *other, gentity_t *activator) {

	if ( ( self->spawnflags & 1 ) && activator && activator->client 
		&& activator->client->sess.sessionTeam != TEAM_RED ) {
		return;
	}
	if ( ( self->spawnflags & 2 ) && activator && activator->client 
		&& activator->client->sess.sessionTeam != TEAM_BLUE ) {
		return;
	}
	if ( self->spawnflags & 4 ) {
		gentity_t	*ent;

		ent = G_PickTarget( self->target );
		if ( ent && ent->use ) {
			ent->use( ent, self, activator );
		}
		return;
	}
	G_UseTargets (self, activator);
}

void SP_target_relay (gentity_t *self) {
	self->use = target_relay_use;
}


//==========================================================

/*QUAKED target_kill (.5 .5 .5) (-8 -8 -8) (8 8 8)
Kills the activator.
*/
void target_kill_use( gentity_t *self, gentity_t *other, gentity_t *activator ) {
	if ( !activator )
		return;
	G_Damage ( activator, NULL, NULL, NULL, NULL, 100000, DAMAGE_NO_PROTECTION, MOD_TELEFRAG);
}

void SP_target_kill( gentity_t *self ) {
	self->use = target_kill_use;
}

/*QUAKED target_position (0 0.5 0) (-4 -4 -4) (4 4 4)
Used as a positional target for in-game calculation, like jumppad targets.
*/
void SP_target_position( gentity_t *self ){
	G_SetOrigin( self, self->s.origin );
}

static void target_location_linkup(gentity_t *ent)
{
	int i;
	int n;

	if (level.locationLinked) 
		return;

	level.locationLinked = qtrue;

	level.locationHead = NULL;

	trap_SetConfigstring( CS_LOCATIONS, "unknown" );

	for (i = 0, ent = g_entities, n = 1;
			i < level.num_entities;
			i++, ent++) {
		if (ent->classname && !Q_stricmp(ent->classname, "target_location")) {
			// lets overload some variables!
			ent->health = n; // use for location marking
			trap_SetConfigstring( CS_LOCATIONS + n, ent->message );
			n++;
			ent->nextTrain = level.locationHead;
			level.locationHead = ent;
		}
	}

	// All linked together now
}

/*QUAKED target_location (0 0.5 0) (-8 -8 -8) (8 8 8)
Set "message" to the name of this location.
Set "count" to 0-7 for color.
0:white 1:red 2:green 3:yellow 4:blue 5:cyan 6:magenta 7:white

Closest target_location in sight used for the location, if none
in site, closest in distance
*/
void SP_target_location( gentity_t *self ){
	self->think = target_location_linkup;
	self->nextthink = level.time + 200;  // Let them all spawn first

	G_SetOrigin( self, self->s.origin );
}

#ifdef USE_SINGLEPLAYER

#define MAX_EXECS 64

char target_execs[MAX_EXECS][MAX_QPATH]; // max of 10 level change entities per level
int num_target_execs=0;

void target_use_exec( gentity_t *self, gentity_t *other, gentity_t *activator ) {
	//char buf[MAX_QPATH];
	//char *nx= target_execs[self->health];
	G_Printf("using exec: %s\n", self->message);
	// the higher the spawnflag the stranger this gets
	// default: Exec Server command like an admin would but from a map trigger
	// 4: send server command to all clients, stuff like \say to print messages
	// 8: send a command to the specific client that activates it
	// 16: send a command to the console of the client that activates it, by prefixing "exec"
	// 32: send a command to the console of all clients by prefixing "exec"
	// the last two are important because it creates a full loop and makes it look
	//   like a server command came from a specific client, covering all bases/entries
	//   16 is how we transfer a client using the \game command to subsequent worlds


	if((self->spawnflags & 32)) {
		trap_SendServerCommand( -1, va("exec %s", self->message ));
	}
	if((self->spawnflags & 16)) {
		trap_SendServerCommand( activator->client - level.clients, va("exec %s", self->message ));
		return;
	}
	if((self->spawnflags & 8)) {
		trap_SendServerCommand( activator->client - level.clients, va("%s", self->message ));
		return;
	}
	if((self->spawnflags & 4)) {
		trap_SendServerCommand( -1, va("%s", self->message ));
		return;
	}
	trap_SendConsoleCommand( EXEC_APPEND, va("%s\n", self->message ) );
}


void SP_target_exec( gentity_t *self ) {
	char *buf;
	char *nx=target_execs[num_target_execs];
	G_SpawnString( "message", "print no command", &buf);

	Com_sprintf(nx,sizeof(target_execs[0]),"load game %s",buf);
	if(nx[0]) {
		if(num_target_execs == MAX_EXECS) {
			// this should be a strange occurance if it happens
			// TODO: demonstrate how to unload worlds in the case of the lobby level changer / select
			G_Printf("MAX_EXECS reached, not loading %s\n", nx);
			return;
		}
		G_Printf("mapCommand (%d): %s\n",num_target_execs,buf);
		//self->world=num_target_execs;
		num_target_execs++;
	}

	self->use = target_use_exec;
} 


void target_use_kamikaze( gentity_t *self, gentity_t *other, gentity_t *activator )  {
	self->activator = self;
	G_StartKamikaze(self);
}

void SP_target_kamikaze( gentity_t *self ) {
	self->use = target_use_kamikaze;
}


// entity
/*QUAKED target_earthquake (1 0 0) (-16 -16 -24) (16 16 32)
starts earthquake
"length" - length in  seconds (2-32, in steps of 2)
"intensity" - strength of earthquake (1-16)
*/

void target_earthquake( gentity_t *self, gentity_t *other, gentity_t *activator ) {
	G_AddEvent(self, EV_EARTHQUAKE, self->s.generic1);
}

void SP_target_earthquake( gentity_t *self ) {
	int param;
	float length;		// length in seconds (2 to 32)
	float intensity;	// intensity (1 to 16)
	int length_;
	int intensity_;
	// read parameters
	G_SpawnFloat( "length", "1000", &length);
	G_SpawnFloat( "intensity", "50", &intensity);
	if (length<2) length=2;
	if (length>32) length=32;
	if (intensity<1) intensity=1;
	if (intensity>16) intensity=16;
	// adjust parameters
	length_ =  ((int)(length) - 2)/2;
	intensity_ = (int)intensity-1;
	param = ( intensity_ | (length_<<4) );
	self->s.generic1=param;
	self->use = target_earthquake;
	self->s.eType = ET_EVENTS;
	trap_LinkEntity (self);
}

/*QUAKED target_player_stop (1 0 0) (-16 -16 -24) (16 16 32)
stops player for "wait"*2 seconds
*/

void target_player_stop( gentity_t *self, gentity_t *other, gentity_t *activator ) {
	activator->stop_event=level.time+((int)(self->wait) & 0x7F)*2000;
	G_AddEvent(activator, EV_PLAYERSTOP, self->wait);
}

void SP_target_player_stop( gentity_t *self ) {
	G_SpawnFloat( "wait", "1", &self->wait);
	if (self->spawnflags & 1)
	{
		if (self->wait>127)
			self->wait=127;
		self->wait  += 128;
	}
	self->use = target_player_stop;
}

#define MAX_SETTINGS 64
#define MAX_SETTING_TARGETS 64
#define PSOFS(x) ((intptr_t) & (((gclient_t *)0)->x))

typedef enum {
	F_NONE = 0,
	F_INT, 
	F_FLOAT,
	F_LSTRING,			// string on disk, pointer in memory, TAG_LEVEL
	F_GSTRING,			// string on disk, pointer in memory, TAG_GAME
	F_VECTOR,
	F_ANGLEHACK,
	F_ENTITY,			// index on disk, pointer in memory
	F_ITEM,				// index on disk, pointer in memory
	F_CLIENT,			// index on disk, pointer in memory
	F_IGNORE
} fieldtype_t;

typedef struct
{
	const char *name;
	int		ofs;
	fieldtype_t	type;
	byte value[12];
	//int		flags;
} playerSetting_t;

const playerSetting_t playerSettings[] = {
	{"altGravity", PSOFS(altGravity), F_FLOAT},
	{"ps.gravity", PSOFS(altGravity), F_FLOAT},
//	{"origin", PSOFS(s.origin), F_VECTOR},
//	{"model", PSOFS(model), F_LSTRING},
//	{"model2", PSOFS(model2), F_LSTRING},
//	{"spawnflags", PSOFS(spawnflags), F_INT},
};

static playerSetting_t player_targets[MAX_SETTING_TARGETS][MAX_SETTINGS];

static playerSetting_t old_player_targets[MAX_CLIENTS][MAX_SETTINGS];

static int numPlayerTargets = 0;


void target_player_setting( gentity_t *self, gentity_t *other, gentity_t *activator ) {
	playerSetting_t *settings;
	int i;
	//byte discard[12];
	byte	*b;
	byte	*o;
	//qboolean isReset;
	settings = player_targets[self->s.generic1];

	//isReset = Q_stricmpn(self->classname, "target_reset", 12) == 0;

	if(!activator->client) {
		return;
	}

	b = (byte *)activator->client;

	for(i = 0; i < MAX_SETTINGS; i++) {
		playerSetting_t *f;
		if(settings[i].type == F_NONE) break;

		// store the old values so they can be reset
		// TODO: this is going to work because triggers fire multiple times
		//   so the first time it's copied correctly, the second time it overwrites the reset values again
		//if(isReset) {
		//	o = (byte *)&discard;
		//	f = &old_player_targets[activator->s.number][i];
		//} else {
			o = (byte *)old_player_targets[activator->s.number][i].value;
			f = &settings[i];
		//}

		switch( settings[i].type ) {
		case F_LSTRING:
			*(char **)(o) = *(char **)(b+settings[i].ofs);
			*(char **)(b+settings[i].ofs) = *(char **)(f->value);
			break;
		case F_ANGLEHACK:
		case F_VECTOR:
			((float *)(o))[0] = ((float *)(b+settings[i].ofs))[0];
			((float *)(o))[1] = ((float *)(b+settings[i].ofs))[1];
			((float *)(o))[2] = ((float *)(b+settings[i].ofs))[2];
			((float *)(b+settings[i].ofs))[0] = ((float *)(f->value))[0];
			((float *)(b+settings[i].ofs))[1] = ((float *)(f->value))[1];
			((float *)(b+settings[i].ofs))[2] = ((float *)(f->value))[2];
			break;
		case F_INT:
			*(int *)(o) = *(int *)(b+settings[i].ofs);
			*(int *)(b+settings[i].ofs) = *(int *)(f->value);
			break;
		case F_FLOAT:
			*(float *)(o) = *(float *)(b+settings[i].ofs);
			*(float *)(b+settings[i].ofs) = *(float *)(f->value);
			break;
		default:
		case F_IGNORE:
			break;
		}

	}


	//G_Printf("Setting settings %i: %f\n", isReset, activator->client->altGravity);

}

void SP_target_setting( gentity_t *self ) {
	int numSettings;
	const playerSetting_t *f;
	byte	*b;
	float	v;
	vec3_t	vec;
	int i;
	const char *value;

	if(numPlayerTargets == MAX_SETTING_TARGETS) {
		G_FreeEntity(self);
		return;
	}
	numPlayerTargets++;


	G_SpawnFloat( "wait", "1", &self->wait);
	if (self->spawnflags & 1)
	{
		if (self->wait>127)
			self->wait=127;
		self->wait  += 128;
	}

	self->s.generic1 = numPlayerTargets;
	self->use = target_player_setting;

	numSettings = 0;
	for ( i = 0 ; i < level.numSpawnVars ; i++ ) {
		for ( f=playerSettings ; f->name ; f++ ) {
			if ( !Q_stricmp(f->name, level.spawnVars[i][0]) ) {
				// found it
				Com_Memcpy((void *)&player_targets[numPlayerTargets][numSettings], f, sizeof(playerSetting_t));
				b = (byte *)player_targets[numPlayerTargets][numSettings].value;
				value = level.spawnVars[i][1];

				switch( f->type ) {
				case F_LSTRING:
					*(char **)(b) = G_NewString (value);
					break;
				case F_VECTOR:
					Q_sscanf (value, "%f %f %f", &vec[0], &vec[1], &vec[2]);
					((float *)(b))[0] = vec[0];
					((float *)(b))[1] = vec[1];
					((float *)(b))[2] = vec[2];
					break;
				case F_INT:
					*(int *)(b) = atoi(value);
					break;
				case F_FLOAT:
					*(float *)(b) = atof(value);
					break;
				case F_ANGLEHACK:
					v = atof(value);
					((float *)(b))[0] = 0;
					((float *)(b))[1] = v;
					((float *)(b))[2] = 0;
					break;
				default:
				case F_IGNORE:
					break;
				}
				numSettings++;
				break;
			}
		}
	}
}


#endif
