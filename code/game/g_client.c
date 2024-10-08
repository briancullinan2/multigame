// Copyright (C) 1999-2000 Id Software, Inc.
//
#include "g_local.h"

// g_client.c -- client functions that don't happen every frame

void Add_Weapon_Ammo( gentity_t *ent, int weapon, int count );
void Remove_Weapon_Ammo( gentity_t *ent, int weapon, int count );
void Add_Ammo( gentity_t *ent, int weapon, int count );

const vec3_t	playerMins = {-15, -15, -24};
const vec3_t	playerMaxs = { 15,  15,  32};

static char	ban_reason[MAX_CVAR_VALUE_STRING];

/*QUAKED info_player_deathmatch (1 0 1) (-16 -16 -24) (16 16 32) initial
potential spawning position for deathmatch games.
The first time a player enters the game, they will be at an 'initial' spot.
Targets will be fired when someone spawns in on them.
"nobots" will prevent bots from using this spot.
"nohumans" will prevent non-bots from using this spot.
*/
void SP_info_player_deathmatch( gentity_t *ent ) {
	int		i;

	G_SpawnInt( "nobots", "0", &i);
	if ( i ) {
		ent->flags |= FL_NO_BOTS;
	}
	G_SpawnInt( "nohumans", "0", &i );
	if ( i ) {
		ent->flags |= FL_NO_HUMANS;
	}
}

/*QUAKED info_player_start (1 0 0) (-16 -16 -24) (16 16 32)
equivelant to info_player_deathmatch
*/
void SP_info_player_start(gentity_t *ent) {
	ent->classname = "info_player_deathmatch";
	SP_info_player_deathmatch( ent );
}

/*QUAKED info_player_intermission (1 0 1) (-16 -16 -24) (16 16 32)
The intermission will be viewed from this point.  Target an info_notnull for the view direction.
*/
void SP_info_player_intermission( gentity_t *ent ) {

}



/*
=======================================================================

  SelectSpawnPoint

=======================================================================
*/

/*
================
SpotWouldTelefrag

================
*/
qboolean SpotWouldTelefrag( gentity_t *spot ) {
	int			i, num;
	int			touch[MAX_GENTITIES];
	gentity_t	*hit;
	vec3_t		mins, maxs;

	VectorAdd( spot->s.origin, playerMins, mins );
	VectorAdd( spot->s.origin, playerMaxs, maxs );
	num = trap_EntitiesInBox( mins, maxs, touch, MAX_GENTITIES );

	for (i=0 ; i<num ; i++) {
		hit = &g_entities[touch[i]];
		//if ( hit->client && hit->client->ps.stats[STAT_HEALTH] > 0 ) {
		if ( hit->client) {
			return qtrue;
		}

	}

	return qfalse;
}


/*
===========
SelectRandomFurthestSpawnPoint

Chooses a player start, deathmatch start, etc
============
*/
#define	MAX_SPAWN_POINTS 64
static gentity_t *SelectRandomFurthestSpawnPoint( const gentity_t *ent, vec3_t avoidPoint, vec3_t origin, vec3_t angles ) {
	gentity_t	*spot;
	vec3_t		delta;
	float		dist;
	float		list_dist[MAX_SPAWN_POINTS];
	gentity_t	*list_spot[MAX_SPAWN_POINTS];
	int			numSpots, i, j, n;
	int			selection;
	int			checkTelefrag;
	int			checkType;
	int			checkMask;
	qboolean	isBot;

	checkType = qtrue;
	checkTelefrag = qtrue;

	if ( ent )
		isBot = ((ent->r.svFlags & SVF_BOT) == SVF_BOT); 
	else
		isBot = qfalse;

	checkMask = 3;

__search:

	checkTelefrag = checkMask & 1;
	checkType = checkMask & 2;

	numSpots = 0;
	for ( n = 0 ; n < level.numSpawnSpots ; n++ ) {
		spot = level.spawnSpots[n];

		if ( spot->fteam != TEAM_FREE && level.numSpawnSpotsFFA > 0 )
			continue;

		if ( checkTelefrag && SpotWouldTelefrag( spot ) )
			continue;

		if ( checkType ) 
		{
			if ( (spot->flags & FL_NO_BOTS) && isBot )
				continue;
			if ( (spot->flags & FL_NO_HUMANS) && !isBot )
				continue;
		}

		VectorSubtract( spot->s.origin, avoidPoint, delta );
		dist = VectorLength( delta );

		for ( i = 0; i < numSpots; i++ )
		{
			if( dist > list_dist[i] )
			{
				if (numSpots >= MAX_SPAWN_POINTS)
					numSpots = MAX_SPAWN_POINTS - 1;

				for( j = numSpots; j > i; j-- )
				{
					list_dist[j] = list_dist[j-1];
					list_spot[j] = list_spot[j-1];
				}

				list_dist[i] = dist;
				list_spot[i] = spot;

				numSpots++;
				break;
			}
		}

		if(i >= numSpots && numSpots < MAX_SPAWN_POINTS)
		{
			list_dist[numSpots] = dist;
			list_spot[numSpots] = spot;
			numSpots++;
		}
	}

	if ( !numSpots ) {
		if ( checkMask <= 0 ) {
			G_Error( "Couldn't find a spawn point" );
			return NULL;
		}
		checkMask--;
		goto __search; // next attempt with different flags
	}

	// select a random spot from the spawn points furthest away
	selection = random() * (numSpots / 2);
	spot = list_spot[ selection ];

	VectorCopy( spot->s.angles, angles );
	VectorCopy( spot->s.origin, origin );
	origin[2] += 9.0f;

	return spot;
}


/*
===========
SelectSpawnPoint

Chooses a player start, deathmatch start, etc
============
*/
gentity_t *SelectSpawnPoint( gentity_t *ent, vec3_t avoidPoint, vec3_t origin, vec3_t angles ) {
	return SelectRandomFurthestSpawnPoint( ent, avoidPoint, origin, angles );
}


/*
===========
SelectInitialSpawnPoint

Try to find a spawn point marked 'initial', otherwise
use normal spawn selection.
============
*/
gentity_t *SelectInitialSpawnPoint( gentity_t *ent, vec3_t origin, vec3_t angles ) {
	gentity_t	*spot;
	int n;

	spot = NULL;

	for ( n = 0; n < level.numSpawnSpotsFFA; n++ ) {
		spot = level.spawnSpots[ n ];
		if ( spot->fteam != TEAM_FREE )
			continue;
		if ( spot->spawnflags & 1 )
			break;
		else
			spot = NULL;
	}

	if ( !spot || SpotWouldTelefrag( spot ) ) {
		return SelectSpawnPoint( ent, vec3_origin, origin, angles );
	}

	VectorCopy( spot->s.angles, angles );
	VectorCopy( spot->s.origin, origin );
	origin[2] += 9.0f;

	return spot;
}


/*
===========
SelectSpectatorSpawnPoint

============
*/
gentity_t *SelectSpectatorSpawnPoint( vec3_t origin, vec3_t angles ) {
	FindIntermissionPoint();

	VectorCopy( level.intermission_origin, origin );
	VectorCopy( level.intermission_angle, angles );

	return level.spawnSpots[ SPAWN_SPOT_INTERMISSION ]; // was NULL
}


/*
=======================================================================

BODYQUE

=======================================================================
*/

/*
===============
InitBodyQue
===============
*/
void InitBodyQue (void) {
	int		i;
	gentity_t	*ent;

	level.bodyQueIndex = 0;
	for (i=0; i<BODY_QUEUE_SIZE ; i++) {
		ent = G_Spawn();
		ent->classname = "bodyque";
		ent->neverFree = qtrue;
		level.bodyQue[i] = ent;
	}
}

/*
=============
BodySink

After sitting around for five seconds, fall into the ground and dissapear
=============
*/
void BodySink( gentity_t *ent ) {
	if ( level.time - ent->timestamp > 6500 ) {
		// the body ques are never actually freed, they are just unlinked
		trap_UnlinkEntity( ent );
		ent->physicsObject = qfalse;
		return;	
	}
	ent->nextthink = level.time + FRAMETIME;
	ent->s.pos.trBase[2] -= 1;
}


/*
=============
CopyToBodyQue

A player is respawning, so make an entity that looks
just like the existing corpse to leave behind.
=============
*/
void CopyToBodyQue( gentity_t *ent ) {
#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS) || defined(USE_RUNES)
	gentity_t	*e;
	int i;
#endif
	gentity_t		*body;
	int			contents;

	trap_UnlinkEntity (ent);

	// if client is in a nodrop area, don't leave the body
	contents = trap_PointContents( ent->s.origin, -1 );
	if ( contents & CONTENTS_NODROP ) {
		return;
	}

	// grab a body que and cycle to the next one
	body = level.bodyQue[ level.bodyQueIndex ];
	level.bodyQueIndex = (level.bodyQueIndex + 1) % BODY_QUEUE_SIZE;

	trap_UnlinkEntity (body);

	body->s = ent->s;
	body->s.eFlags = EF_DEAD;		// clear EF_TALK, etc
#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS) || defined(USE_RUNES)
	if ( ent->s.eFlags & EF_KAMIKAZE ) {
		body->s.eFlags |= EF_KAMIKAZE;

		// check if there is a kamikaze timer around for this owner
		for (i = 0; i < level.num_entities; i++) {
			e = &g_entities[i];
			if (!e->inuse)
				continue;
			if (e->activator != ent)
				continue;
			if (strcmp(e->classname, "kamikaze timer"))
				continue;
			e->activator = body;
			break;
		}
	}
#endif
	body->s.powerups = 0;	// clear powerups
	body->s.loopSound = 0;	// clear lava burning
	body->s.number = body - g_entities;
	body->timestamp = level.time;
	body->physicsObject = qtrue;
	body->physicsBounce = 0;		// don't bounce
	if ( body->s.groundEntityNum == ENTITYNUM_NONE ) {
		body->s.pos.trType = TR_GRAVITY;
		body->s.pos.trTime = level.time;
		VectorCopy( ent->client->ps.velocity, body->s.pos.trDelta );
	} else {
		body->s.pos.trType = TR_STATIONARY;
	}
	body->s.event = 0;

	// change the animation to the last-frame only, so the sequence
	// doesn't repeat anew for the body
	switch ( body->s.legsAnim & ~ANIM_TOGGLEBIT ) {
	case BOTH_DEATH1:
	case BOTH_DEAD1:
		body->s.torsoAnim = body->s.legsAnim = BOTH_DEAD1;
		break;
	case BOTH_DEATH2:
	case BOTH_DEAD2:
		body->s.torsoAnim = body->s.legsAnim = BOTH_DEAD2;
		break;
	case BOTH_DEATH3:
	case BOTH_DEAD3:
	default:
		body->s.torsoAnim = body->s.legsAnim = BOTH_DEAD3;
		break;
	}

	body->r.svFlags = ent->r.svFlags;
	VectorCopy (ent->r.mins, body->r.mins);
	VectorCopy (ent->r.maxs, body->r.maxs);
	VectorCopy (ent->r.absmin, body->r.absmin);
	VectorCopy (ent->r.absmax, body->r.absmax);

	body->clipmask = CONTENTS_SOLID | CONTENTS_PLAYERCLIP;
	body->r.contents = CONTENTS_CORPSE;
	body->r.ownerNum = ent->s.number;

#ifdef USE_HORDES
	if(g_hordeBodies.integer) {

	} else {
#endif

	body->nextthink = level.time + 5000;
	body->think = BodySink;

#ifdef USE_HORDES
	}
#endif


	body->die = body_die;

	// don't take more damage if already gibbed
	if ( ent->health <= GIB_HEALTH ) {
		body->takedamage = qfalse;
	} else {
		body->takedamage = qtrue;
	}

#ifdef USE_HEADSHOTS
  if(ent->client->lasthurt_mod == MOD_HEADSHOT)
	  G_AddEvent( body, EV_BODY_NOHEAD, 0 );
#endif


	VectorCopy ( body->s.pos.trBase, body->r.currentOrigin );
	trap_LinkEntity( body );
}


//======================================================================

/*
==================
SetClientViewAngle
==================
*/
void SetClientViewAngle( gentity_t *ent, vec3_t angle ) {
	int	i, cmdAngle;
	gclient_t	*client;

	client = ent->client;

	// set the delta angle
	for (i = 0 ; i < 3 ; i++) {
		cmdAngle = ANGLE2SHORT(angle[i]);
		client->ps.delta_angles[i] = cmdAngle - client->pers.cmd.angles[i];
	}
	VectorCopy( angle, ent->s.angles );
	VectorCopy( ent->s.angles, client->ps.viewangles );
}


/*
================
respawn
================
*/
void respawn( gentity_t *ent ) {
	gentity_t	*tent;

	if ( ent->health <= 0 )
		CopyToBodyQue( ent );

	ClientSpawn( ent );

	// bots doesn't need to see any effects
	if ( level.intermissiontime && ent->r.svFlags & SVF_BOT )
		return;

	// add a teleportation effect
	tent = G_TempEntity( ent->client->ps.origin, EV_PLAYER_TELEPORT_IN );
	tent->s.clientNum = ent->s.clientNum;

	// optimize bandwidth
	if ( level.intermissiontime ) {
		tent->r.svFlags = SVF_SINGLECLIENT;
		tent->r.singleClient = ent->s.clientNum;
	}
}


/*
================
TeamCount

Returns number of players on a team
================
*/
int TeamCount( int ignoreClientNum, team_t team ) {
	int		i;
	int		count = 0;

	for ( i = 0 ; i < level.maxclients ; i++ ) {
		if ( i == ignoreClientNum ) {
			continue;
		}
		if ( level.clients[i].pers.connected == CON_DISCONNECTED ) {
			continue;
		}
		if ( level.clients[i].sess.sessionTeam == team ) {
			count++;
		}
	}

	return count;
}


/*
================
TeamConnectedCount

Returns number of active players on a team
================
*/
int TeamConnectedCount( int ignoreClientNum, team_t team ) {
	int		i;
	int		count = 0;

	for ( i = 0 ; i < level.maxclients ; i++ ) {
		if ( i == ignoreClientNum ) {
			continue;
		}
		if ( level.clients[i].pers.connected != CON_CONNECTED ) {
			continue;
		}
		if ( level.clients[i].sess.sessionTeam == team ) {
			count++;
		}
	}

	return count;
}


/*
================
TeamLeader

Returns the client number of the team leader
================
*/
int TeamLeader( team_t team ) {
	int		i;

	for ( i = 0 ; i < level.maxclients ; i++ ) {
		if ( level.clients[i].pers.connected == CON_DISCONNECTED ) {
			continue;
		}
		if ( level.clients[i].sess.sessionTeam == team ) {
			if ( level.clients[i].sess.teamLeader )
				return i;
		}
	}

	return -1;
}


/*
================
PickTeam
================
*/
team_t PickTeam( int ignoreClientNum ) {
	int		counts[TEAM_NUM_TEAMS];

	counts[TEAM_BLUE] = TeamCount( ignoreClientNum, TEAM_BLUE );
	counts[TEAM_RED] = TeamCount( ignoreClientNum, TEAM_RED );

	if ( counts[TEAM_BLUE] > counts[TEAM_RED] ) {
		return TEAM_RED;
	}
	if ( counts[TEAM_RED] > counts[TEAM_BLUE] ) {
		return TEAM_BLUE;
	}
	// equal team count, so join the team with the lowest score
	if ( level.teamScores[TEAM_BLUE] > level.teamScores[TEAM_RED] ) {
		return TEAM_RED;
	}
	return TEAM_BLUE;
}


/*
===========
ClientUserInfoChanged

Called from ClientConnect when the player first connects and
directly by the server system when the player updates a userinfo variable.

The game can override any of the settings and call trap_SetUserinfo
if desired.

returns qfalse in case of invalid userinfo
============
*/
qboolean ClientUserinfoChanged( int clientNum ) {
	gentity_t *ent;
	int		teamTask, teamLeader, health;
	char	*s;
	char	model[MAX_QPATH];
	char	headModel[MAX_QPATH];
	char	oldname[MAX_NETNAME];
	gclient_t	*client;
	char	c1[8];
	char	c2[8];
	char	userinfo[MAX_INFO_STRING];

	ent = g_entities + clientNum;
	client = ent->client;

	trap_GetUserinfo( clientNum, userinfo, sizeof( userinfo ) );

	// check for malformed or illegal info strings
	if ( !Info_Validate( userinfo ) ) {
		Q_strcpy( ban_reason, "bad userinfo" );
		if ( client && client->pers.connected != CON_DISCONNECTED )
			trap_DropClient( clientNum, ban_reason );
		return qfalse;
	}

	if ( client->pers.connected == CON_DISCONNECTED ) {
		// we just checked if connecting player can join server
		// so quit now as some important data like player team is still not set
		return qtrue;
	}

	// check for local client
	s = Info_ValueForKey( userinfo, "ip" );
	if ( !strcmp( s, "localhost" ) ) {
		client->pers.localClient = qtrue;
	} else {
		client->pers.localClient = qfalse;
	}

	// check the item prediction
	s = Info_ValueForKey( userinfo, "cg_predictItems" );
	if ( !atoi( s ) ) {
		client->pers.predictItemPickup = qfalse;
	} else {
		client->pers.predictItemPickup = qtrue;
	}

	// set name
	Q_strncpyz( oldname, client->pers.netname, sizeof( oldname ) );
	s = Info_ValueForKey( userinfo, "name" );
	BG_CleanName( s, client->pers.netname, sizeof( client->pers.netname ), "UnnamedPlayer" );

	if ( client->sess.sessionTeam == TEAM_SPECTATOR ) {
		if ( client->sess.spectatorState == SPECTATOR_SCOREBOARD ) {
			Q_strncpyz( client->pers.netname, "scoreboard", sizeof(client->pers.netname) );
		}
	}

	if ( client->pers.connected == CON_CONNECTED ) {
		if ( strcmp( oldname, client->pers.netname ) ) {
			G_BroadcastServerCommand( -1, va("print \"%s" S_COLOR_WHITE " renamed to %s\n\"", oldname, client->pers.netname) );
		}
	}

	// set max health
#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS)
#ifdef USE_ADVANCED_ITEMS
	if (client->inventory[PW_GUARD])
#else
	if (client->ps.powerups[PW_GUARD])
#endif
	{
		client->pers.maxHealth = HEALTH_SOFT_LIMIT*2;
	} else {
		health = atoi( Info_ValueForKey( userinfo, "handicap" ) );
		client->pers.maxHealth = health;
		if ( client->pers.maxHealth < 1 || client->pers.maxHealth > HEALTH_SOFT_LIMIT ) {
			client->pers.maxHealth = HEALTH_SOFT_LIMIT;
		}
	}
#else
	health = atoi( Info_ValueForKey( userinfo, "handicap" ) );
	client->pers.maxHealth = health;
	if ( client->pers.maxHealth < 1 || client->pers.maxHealth > HEALTH_SOFT_LIMIT ) {
		client->pers.maxHealth = HEALTH_SOFT_LIMIT;
	}
#endif

#ifdef USE_RUNES
	if(client->inventory[RUNE_HEALTH]) {
		client->ps.stats[STAT_MAX_HEALTH] = rune_healthMax.integer;
	} else
#endif
	client->ps.stats[STAT_MAX_HEALTH] = client->pers.maxHealth;

#if defined(MISSIONPACK) || defined(USE_ADVANCED_TEAMS)
	if (g_gametype.integer >= GT_TEAM) {
		client->pers.teamInfo = qtrue;
	} else {
		s = Info_ValueForKey( userinfo, "teamoverlay" );
		if ( ! *s || atoi( s ) != 0 ) {
			client->pers.teamInfo = qtrue;
		} else {
			client->pers.teamInfo = qfalse;
		}
	}
#else
	// teamInfo
	s = Info_ValueForKey( userinfo, "teamoverlay" );
	if ( ! *s || atoi( s ) != 0 ) {
		client->pers.teamInfo = qtrue;
	} else {
		client->pers.teamInfo = qfalse;
	}
#endif


#ifdef USE_BIRDS_EYE
	s = Info_ValueForKey( userinfo, "cg_thirdperson" );
	if ( *s && atoi( s ) != 0 ) {
		// TODO: AIM towards the surface it would hit, through portals
		client->ps.pm_type = PM_THIRDPERSON;
		client->pers.thirdPerson = qtrue;
	} else {
		client->pers.thirdPerson = qfalse;
	}
	s = Info_ValueForKey( userinfo, "cg_birdsEye" );
	if ( *s && atoi( s ) != 0 ) {
	G_Printf("setting birds eye\n");
		client->ps.pm_type = PM_BIRDSEYE;
		client->pers.birdsEye = qtrue;
	} else {
		client->pers.birdsEye = qfalse;
	}


	s = Info_ValueForKey( userinfo, "cg_drawCrosshair" );
	if ( *s && atoi( s ) != 0 ) {
		client->ps.pm_type = PM_FOLLOWCURSOR;
		client->pers.showCursor = qtrue;
	} else {
		client->pers.showCursor = qfalse;
	}


	s = Info_ValueForKey( userinfo, "cg_sideview" );
	if ( *s && atoi( s ) != 0 ) {
		client->ps.pm_type = PM_PLATFORM;
		client->pers.sideView = qtrue;
	} else {
		client->pers.sideView = qfalse;
	}
#endif

#ifdef USE_AIW
	s = Info_ValueForKey( userinfo, "cg_reverseControls" );
	if ( *s && atoi( s ) != 0 ) {
		client->ps.pm_type = PM_REVERSED;
		client->pers.reverseControls = qtrue;
	} else {
		client->pers.reverseControls = qfalse;
	}

	s = Info_ValueForKey( userinfo, "cg_upsideDown" );
	if ( *s && atoi( s ) != 0 ) {
		client->ps.pm_type = PM_UPSIDEDOWN;
		client->pers.upsidedown = qtrue;
	} else {
		client->pers.upsidedown = qfalse;
	}

	if(client->pers.upsidedown && client->pers.reverseControls) {
		client->ps.pm_type = PM_REVERSEDUPSIDEDOWN;
	}
#endif


	// set model
	Q_strncpyz( model, Info_ValueForKey( userinfo, "model" ), sizeof( model ) );
	Q_strncpyz( headModel, Info_ValueForKey( userinfo, "headmodel" ), sizeof( headModel ) );

#ifdef USE_MULTIWORLD
	s = Info_ValueForKey( userinfo, "worlds" );
	if(*s) {
		client->pers.allWorlds = atoi(s) | (1 << level.world); // add this game instance to occupying worlds to let the client know about
	} else {
		client->pers.allWorlds |= (1 << level.world);
	}
//Com_Printf("Adding world to server client: %i in %i\n", client - level.clients, client->pers.allWorlds);
#endif


#ifdef USE_ADVANCED_CLASS
  client->pers.newplayerclass = BG_PlayerClassFromModel(model);
  client->pers.playerclass = client->pers.newplayerclass;
#endif

	// team task (0 = none, 1 = offence, 2 = defence)
	teamTask = atoi(Info_ValueForKey(userinfo, "teamtask"));
	// team Leader (1 = leader, 0 is normal player)
	teamLeader = client->sess.teamLeader;

	// colors
	Q_strncpyz( c1, Info_ValueForKey( userinfo, "color1" ), sizeof( c1 ) );
	Q_strncpyz( c2, Info_ValueForKey( userinfo, "color2" ), sizeof( c2 ) );

	// send over a subset of the userinfo keys so other clients can
	// print scoreboards, display models, and play custom sounds
#ifdef USE_MULTIWORLD
	if ( ent->r.svFlags & SVF_BOT ) {
		s = va("n\\%s\\t\\%i\\model\\%s\\hmodel\\%s\\c1\\%s\\c2\\%s\\hc\\%i\\w\\%i\\l\\%i\\skill\\%s\\tt\\%d\\tl\\%d\\worlds\\%i",
			client->pers.netname, client->sess.sessionTeam, model, headModel, c1, c2,
			client->pers.maxHealth, client->sess.wins, client->sess.losses,
			Info_ValueForKey( userinfo, "skill" ), teamTask, teamLeader, client->pers.allWorlds );
	} else {
		s = va("n\\%s\\t\\%i\\model\\%s\\hmodel\\%s\\c1\\%s\\c2\\%s\\hc\\%i\\w\\%i\\l\\%i\\tt\\%d\\tl\\%d\\worlds\\%i",
			client->pers.netname, client->sess.sessionTeam, model, headModel, c1, c2, 
			client->pers.maxHealth, client->sess.wins, client->sess.losses, teamTask, teamLeader, client->pers.allWorlds );
	}
#else
	if ( ent->r.svFlags & SVF_BOT ) {
		s = va("n\\%s\\t\\%i\\model\\%s\\hmodel\\%s\\c1\\%s\\c2\\%s\\hc\\%i\\w\\%i\\l\\%i\\skill\\%s\\tt\\%d\\tl\\%d",
			client->pers.netname, client->sess.sessionTeam, model, headModel, c1, c2,
			client->pers.maxHealth, client->sess.wins, client->sess.losses,
			Info_ValueForKey( userinfo, "skill" ), teamTask, teamLeader );
	} else {
		s = va("n\\%s\\t\\%i\\model\\%s\\hmodel\\%s\\c1\\%s\\c2\\%s\\hc\\%i\\w\\%i\\l\\%i\\tt\\%d\\tl\\%d",
			client->pers.netname, client->sess.sessionTeam, model, headModel, c1, c2, 
			client->pers.maxHealth, client->sess.wins, client->sess.losses, teamTask, teamLeader );
	}
#endif

G_Printf("somethings wrong %s\n", s);

	trap_SetConfigstring( CS_PLAYERS+clientNum, s );

	// this is not the userinfo, more like the configstring actually
	G_LogPrintf( "ClientUserinfoChanged: %i %s\n", clientNum, s );

	return qtrue;
}


/*
===========
ClientConnect

Called when a player begins connecting to the server.
Called again for every map change or tournement restart.

The session information will be valid after exit.

Return NULL if the client should be allowed, otherwise return
a string with the reason for denial.

Otherwise, the client will be sent the current gamestate
and will eventually get to ClientBegin.

firstTime will be qtrue the very first time a client connects
to the server machine, but qfalse on map changes and tournement
restarts.
============
*/
const char *ClientConnect( int clientNum, qboolean firstTime, qboolean isBot ) {
	char		*value;
//	char		*areabits;
	gclient_t	*client;
	char		userinfo[MAX_INFO_STRING];
	gentity_t	*ent;
	qboolean	isAdmin;

	if ( clientNum >= level.maxclients ) {
		return "Bad connection slot.";
	}

	ent = &g_entities[ clientNum ];
	ent->client = level.clients + clientNum;

	if ( firstTime ) {
		// cleanup previous data manually
		// because client may silently (re)connect without ClientDisconnect in case of crash for example
		if ( level.clients[ clientNum ].pers.connected != CON_DISCONNECTED )
			ClientDisconnect( clientNum );

		// remove old entity from the world
		trap_UnlinkEntity( ent );
		ent->r.contents = 0;
		ent->s.eType = ET_INVISIBLE;
		ent->s.eFlags = 0;
		ent->s.modelindex = 0;
		ent->s.clientNum = clientNum;
		ent->s.number = clientNum;
		ent->takedamage = qfalse;
	}

	ent->r.svFlags &= ~SVF_BOT;
	ent->inuse = qfalse;

	trap_GetUserinfo( clientNum, userinfo, sizeof( userinfo ) );

 	// IP filtering
 	// https://zerowing.idsoftware.com/bugzilla/show_bug.cgi?id=500
 	// recommanding PB based IP / GUID banning, the builtin system is pretty limited
 	// check to see if they are on the banned IP list
	value = Info_ValueForKey( userinfo, "ip" );

	if ( !strcmp( value, "localhost" ) && !isBot )
		isAdmin = qtrue;
	else
		isAdmin = qfalse;

	if ( !isAdmin && G_FilterPacket( value ) ) {
		return "You are banned from this server.";
	}

	// we don't check password for bots and local client
	// NOTE: local client <-> "ip" "localhost"
	// this means this client is not running in our current process
	if ( !isBot && !isAdmin ) {
		// check for a password
		if ( g_password.string[0] && Q_stricmp( g_password.string, "none" ) ) {
			value = Info_ValueForKey( userinfo, "password" );
			if ( strcmp( g_password.string, value ) )
				return "Invalid password";
		}
	}

	// they can connect
	ent->client = level.clients + clientNum;
	client = ent->client;

//	areabits = client->areabits;
	memset( client, 0, sizeof( *client ) );

	client->ps.clientNum = clientNum;

	if ( !ClientUserinfoChanged( clientNum ) ) {
		return ban_reason;
	}

	// read or initialize the session data
	if ( firstTime || level.newSession ) {
		value = Info_ValueForKey( userinfo, "team" );
		G_InitSessionData( client, value, isBot );
		G_WriteClientSessionData( client );
	}

	G_ReadClientSessionData( client );

	if( isBot ) {
		if( !G_BotConnect( clientNum, !firstTime ) ) {
			return "BotConnectfailed";
		}
		ent->r.svFlags |= SVF_BOT;
		ent->r.svFlags |= SVF_BROADCAST;
		client->sess.spectatorClient = clientNum;
	}
	ent->inuse = qtrue;

	// get and distribute relevant paramters
	G_LogPrintf( "ClientConnect: %i\n", clientNum );

	client->pers.connected = CON_CONNECTING;

	ClientUserinfoChanged( clientNum );

	// don't do the "xxx connected" messages if they were caried over from previous level
	if ( firstTime ) {
		G_BroadcastServerCommand( -1, va( "print \"%s" S_COLOR_WHITE " connected\n\"", client->pers.netname ) );

		// mute all prints until completely in game
		client->pers.inGame = qfalse;
	} else {
		client->pers.inGame = qtrue; // FIXME: read from session data?
	}

	// count current clients and rank for scoreboard
	CalculateRanks();

	// for statistics
//	client->areabits = areabits;
//	if ( !client->areabits )
//		client->areabits = G_Alloc( (trap_AAS_PointReachabilityAreaIndex( NULL ) + 7) / 8 );

	return NULL;
}


/*
===========
ClientBegin

called when a client has finished connecting, and is ready
to be placed into the level.  This will happen every level load,
and on transition between teams, but doesn't happen on respawns
============
*/
void ClientBegin( int clientNum ) {
	gentity_t	*ent;
	gclient_t	*client;
	gentity_t	*tent;
	int			flags;
	int			spawns;

	ent = g_entities + clientNum;

	client = level.clients + clientNum;

	if ( ent->r.linked ) {
		trap_UnlinkEntity( ent );
	}

	G_InitGentity( ent );
	ent->touch = 0;
	ent->pain = 0;
	ent->client = client;

	if ( client->pers.connected == CON_DISCONNECTED )
		return;

	client->pers.connected = CON_CONNECTED;
	client->pers.enterTime = level.time;
	client->pers.teamState.state = TEAM_BEGIN;
	spawns = client->ps.persistant[PERS_SPAWN_COUNT];

	// save eflags around this, because changing teams will
	// cause this to happen with a valid entity, and we
	// want to make sure the teleport bit is set right
	// so the viewpoint doesn't interpolate through the
	// world to the new position
	flags = client->ps.eFlags;
	memset( &client->ps, 0, sizeof( client->ps ) );
	client->ps.eFlags = flags;
	client->ps.persistant[PERS_SPAWN_COUNT] = spawns;

	// locate ent at a spawn point
	ClientSpawn( ent );

	if ( !client->pers.inGame ) {
		BroadcastTeamChange( client, -1 );
		if ( client->sess.sessionTeam == TEAM_RED || client->sess.sessionTeam == TEAM_BLUE )
			CheckTeamLeader( client->sess.sessionTeam );
	}

	if ( client->sess.sessionTeam != TEAM_SPECTATOR ) {
		// send event
		tent = G_TempEntity( client->ps.origin, EV_PLAYER_TELEPORT_IN );
		tent->s.clientNum = ent->s.clientNum;

		client->sess.spectatorTime = 0;

		if ( g_gametype.integer != GT_TOURNAMENT && !client->pers.inGame ) {
			G_BroadcastServerCommand( -1, va("print \"%s" S_COLOR_WHITE " entered the game\n\"", client->pers.netname) );
		}
	}
	
	client->pers.inGame = qtrue;

	G_LogPrintf( "ClientBegin: %i\n", clientNum );

	// count current clients and rank for scoreboard
	CalculateRanks();
}


/*
===========
ClientSpawn

Called every time a client is placed fresh in the world:
after the first ClientBegin, and after each respawn
Initializes all non-persistant parts of playerState
============
*/
void ClientSpawn(gentity_t *ent) {
	int		index;
	vec3_t	spawn_origin, spawn_angles;
	gclient_t	*client;
	int		i;
	clientPersistant_t	saved;
	clientSession_t		savedSess;
	int		persistant[MAX_PERSISTANT];
	gentity_t	*spawnPoint;
	int		flags;
	int		savedPing;
//	char	*savedAreaBits;
	int		accuracy_hits, accuracy_shots;
	int		eventSequence;
	char	userinfo[MAX_INFO_STRING];
	qboolean isSpectator;

	index = ent - g_entities;
	client = ent->client;

	trap_UnlinkEntity( ent );

	isSpectator = client->sess.sessionTeam == TEAM_SPECTATOR;
	// find a spawn point
	// do it before setting health back up, so farthest
	// ranging doesn't count this client
	if ( isSpectator ) {
		spawnPoint = SelectSpectatorSpawnPoint( spawn_origin, spawn_angles );
	} else if (g_gametype.integer >= GT_CTF ) {
		// all base oriented team games use the CTF spawn points
		spawnPoint = SelectCTFSpawnPoint( ent, client->sess.sessionTeam, client->pers.teamState.state, spawn_origin, spawn_angles );
	} else {
		do {
			// the first spawn should be at a good looking spot
			if ( !client->pers.initialSpawn && client->pers.localClient ) {
				client->pers.initialSpawn = qtrue;
				spawnPoint = SelectInitialSpawnPoint( ent, spawn_origin, spawn_angles );
			} else {
				// don't spawn near existing origin if possible
				spawnPoint = SelectSpawnPoint( ent, client->ps.origin, spawn_origin, spawn_angles );
			}

			// Tim needs to prevent bots from spawning at the initial point
			// on q3dm0...
			if ( ( spawnPoint->flags & FL_NO_BOTS ) && ( ent->r.svFlags & SVF_BOT ) ) {
				continue;	// try again
			}
			// just to be symetric, we have a nohumans option...
			if ( ( spawnPoint->flags & FL_NO_HUMANS ) && !( ent->r.svFlags & SVF_BOT ) ) {
				continue;	// try again
			}

			break;

		} while ( 1 );
	}
	client->pers.teamState.state = TEAM_ACTIVE;

#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS) || defined(USE_RUNES)
	// always clear the kamikaze flag
	ent->s.eFlags &= ~EF_KAMIKAZE;
#endif

	// toggle the teleport bit so the client knows to not lerp
	// and never clear the voted flag
	flags = client->ps.eFlags & (EF_TELEPORT_BIT | EF_VOTED | EF_TEAMVOTED);
	flags ^= EF_TELEPORT_BIT;

	// unlagged
	G_ResetHistory( ent );
	client->saved.leveltime = 0;

	// clear everything but the persistant data

	saved = client->pers;
	savedSess = client->sess;
	savedPing = client->ps.ping;
//	savedAreaBits = client->areabits;
	accuracy_hits = client->accuracy_hits;
	accuracy_shots = client->accuracy_shots;
	for ( i = 0 ; i < MAX_PERSISTANT ; i++ ) {
		persistant[i] = client->ps.persistant[i];
	}
	eventSequence = client->ps.eventSequence;

	Com_Memset (client, 0, sizeof(*client));

	client->pers = saved;
	client->sess = savedSess;
	client->ps.ping = savedPing;
//	client->areabits = savedAreaBits;
	client->accuracy_hits = accuracy_hits;
	client->accuracy_shots = accuracy_shots;
	client->lastkilled_client = -1;

#ifdef USE_ADVANCED_WEAPONS
	memset( client->weaponsModified, 1, sizeof( client->weaponsModified ) );
#endif
#ifdef USE_ADVANCED_ITEMS
	ent->s.powerups = 0;
	memset( client->inventory, 0, sizeof( client->inventory ) );
	memset( client->inventoryModified, 1, sizeof( client->inventoryModified ) );
#endif

	for ( i = 0 ; i < MAX_PERSISTANT ; i++ ) {
		client->ps.persistant[i] = persistant[i];
	}
	client->ps.eventSequence = eventSequence;
	// increment the spawncount so the client will detect the respawn
	client->ps.persistant[PERS_SPAWN_COUNT]++;
	client->ps.persistant[PERS_TEAM] = client->sess.sessionTeam;

	client->airOutTime = level.time + 12000;

	trap_GetUserinfo( index, userinfo, sizeof(userinfo) );
	// set max health
	client->pers.maxHealth = atoi( Info_ValueForKey( userinfo, "handicap" ) );
	if ( client->pers.maxHealth < 1 || client->pers.maxHealth > HEALTH_SOFT_LIMIT ) {
		client->pers.maxHealth = HEALTH_SOFT_LIMIT;
	}
	// clear entity values
	client->ps.stats[STAT_MAX_HEALTH] = client->pers.maxHealth;
	client->ps.eFlags = flags;

	ent->r.svFlags |= SVF_BROADCAST;
	ent->s.groundEntityNum = ENTITYNUM_NONE;
	ent->client = &level.clients[index];
	ent->inuse = qtrue;
	ent->classname = "player";
	if ( isSpectator ) {
		ent->takedamage = qfalse;
		ent->r.contents = 0;
		ent->clipmask = MASK_PLAYERSOLID & ~CONTENTS_BODY;
		client->ps.pm_type = PM_SPECTATOR;
	} else {
		ent->takedamage = qtrue;
		ent->r.contents = CONTENTS_BODY;
		ent->clipmask = MASK_PLAYERSOLID;
	}
#ifdef USE_DAMAGE_PLUMS
  ent->pain = player_pain;
#endif
	ent->die = player_die;
	ent->waterlevel = 0;
	ent->watertype = 0;
	ent->flags = 0;
	

#ifdef USE_ADVANCED_CLASS
  client->pers.playerclass = client->pers.newplayerclass;  
#endif

	//VectorCopy (playerMins, ent->r.mins);
	//VectorCopy (playerMaxs, ent->r.maxs);
	VectorScale(playerMins, g_playerScale.value, ent->r.mins);
	VectorScale(playerMaxs, g_playerScale.value, ent->r.maxs);

	client->ps.clientNum = index;


#ifdef USE_ADVANCED_WEAPONS
	// TODO: make these templates somehow where a conditional evaluates to this if else code
	if ( g_gametype.integer == GT_TEAM ) {
		Add_Weapon_Ammo(ent, WP_MACHINEGUN, 50);
	} else {
		Add_Weapon_Ammo(ent, WP_MACHINEGUN, 100);
	}
#else
	client->ps.stats[STAT_WEAPONS] = ( 1 << WP_MACHINEGUN );
	if ( g_gametype.integer == GT_TEAM ) {
		client->ps.ammo[WP_MACHINEGUN] = 50;
	} else {
		client->ps.ammo[WP_MACHINEGUN] = 100;
	}
#endif

#ifdef USE_ADVANCED_CLASS
  //assign weapons according to class
  switch (client->pers.playerclass) {
	case PCLASS_VORE:
		G_ModelIndex("models/runes/icetrap.md3");
		Remove_Weapon_Ammo(ent, WP_MACHINEGUN, INFINITE);
		Add_Weapon_Ammo(ent, WP_ROCKET_LAUNCHER, 30);
		break;
	case PCLASS_GUNNER:
		Remove_Weapon_Ammo(ent, WP_MACHINEGUN, INFINITE);
		Add_Weapon_Ammo(ent, WP_CHAINGUN, 100);
		break;
	case PCLASS_BERSERKER:
		Remove_Weapon_Ammo(ent, WP_MACHINEGUN, INFINITE);
		break;
  case PCLASS_DRAGON:
		Remove_Weapon_Ammo(ent, WP_MACHINEGUN, INFINITE);
#ifdef USE_FLAME_THROWER
		Add_Weapon_Ammo(ent, WP_FLAME_THROWER, 40);
#endif
    break;
  case PCLASS_BFG:
		Add_Weapon_Ammo(ent, WP_BFG, 20);
    break;
  case PCLASS_SHAMBLER:
		Remove_Weapon_Ammo(ent, WP_MACHINEGUN, INFINITE);
  case PCLASS_LIGHTNING:
		Add_Weapon_Ammo(ent, WP_LIGHTNING, 60);
    break;
  case PCLASS_RAILGUN:
		Add_Weapon_Ammo(ent, WP_RAILGUN, 20);
    break;
	case PCLASS_RANGER:
		Add_Weapon_Ammo(ent, WP_SHOTGUN, 10);
		break;
  default:
		break;
  }
#endif

	if(!( 
#ifdef USE_ADVANCED_WEAPONS
		!wp_gauntEnable.integer
#else
		qtrue
#endif
#ifdef USE_HOTRPG
		|| g_hotRockets.integer
#endif
#ifdef USE_HOTBFG
		|| g_hotRockets.integer
#endif
#ifdef USE_TRINITY
		|| g_unholyTrinity.integer
#endif
#ifdef USE_INSTAGIB
		|| g_instagib.integer
#endif
	)) {

#ifdef USE_ADVANCED_WEAPONS
	Add_Weapon_Ammo(ent, WP_GAUNTLET, INFINITE);
#else
	client->ps.stats[STAT_WEAPONS] |= ( 1 << WP_GAUNTLET );
	client->ps.ammo[WP_GAUNTLET] = -1;
#endif

	}

#ifdef USE_INSTAGIB
  if(g_instagib.integer) {
    // bots don't seem to like -1 as ammo amount, maybe this can be fixed
    //   during advanced grapple hook tutorial.
		Add_Weapon_Ammo(ent, WP_RAILGUN, INFINITE);
  }
#endif

#ifdef USE_GRAPPLE
	if(wp_grappleEnable.integer) {
#ifdef USE_ADVANCED_WEAPONS
		Add_Ammo(ent, WP_GAUNTLET, INFINITE);
#else
		client->ps.ammo[WP_GRAPPLING_HOOK] = -1;
#endif
	}
#endif

#ifdef USE_PORTALS
  if(wp_portalEnable.integer) {
    // in alt-fire mode, both ends reset with right click
    // otherwise, use BFG left and right click for both ends
		Add_Weapon_Ammo(ent, WP_BFG, INFINITE);
  }
#endif

#ifdef USE_TRINITY
if(g_unholyTrinity.integer) {
	Add_Weapon_Ammo(ent, WP_RAILGUN, INFINITE);
	Add_Weapon_Ammo(ent, WP_LIGHTNING, INFINITE);
	Add_Weapon_Ammo(ent, WP_ROCKET_LAUNCHER, INFINITE);
}
#endif

#ifdef USE_HOTRPG
if(g_hotRockets.integer) {
	Add_Weapon_Ammo(ent, WP_ROCKET_LAUNCHER, INFINITE);
}
#endif

#ifdef USE_HOTBFG
	if(g_hotBFG.integer) {
		int handicap, max;
		Add_Weapon_Ammo(ent, WP_BFG, INFINITE);
		trap_GetUserinfo( client - level.clients, userinfo, sizeof(userinfo) );
		handicap = atof( Info_ValueForKey( userinfo, "handicap" ) );
		if( handicap<=0.0f || handicap>100.0f) {
			handicap = 100.0f;
		}
		max = (int)(2 *  handicap);
		ent->health = max;
		client->ps.stats[STAT_HEALTH] = max;
		client->ps.stats[STAT_MAX_HEALTH] = max;
	}
#endif

#if defined(USE_GRAPPLE)
  if(wp_grappleEnable.integer 
#ifdef USE_ALT_FIRE
    && !g_altGrapple.integer
#endif
  ) {
		Add_Weapon_Ammo(ent, WP_GRAPPLING_HOOK, INFINITE);
  }
#endif

#ifdef USE_FLAME_THROWER
	if(wp_flameEnable.integer) {
		//Spawn player with flame thrower
		Add_Weapon_Ammo(ent, WP_FLAME_THROWER, INFINITE);
	}
#endif



#if 0
#ifdef USE_ADVANCED_WEAPONS
	weaponClass = floor(client->ps.weapon / WP_MAX_WEAPONS);
	for(i = 0; i < WP_MAX_WEAPONS; i++) {
		if(client->ps.stats[STAT_WEAPONS] & (1 << i)) {
			if(client->classWeapons[weaponClass * WP_MAX_WEAPONS + i] < 1) {
				client->classWeapons[weaponClass * WP_MAX_WEAPONS + i]++;
			}
		} else {
			client->classWeapons[weaponClass * WP_MAX_WEAPONS + i] = 0;
		}
		client->classAmmo[weaponClass * WP_MAX_WEAPONS + i] = client->ps.ammo[i];
	}


	// give the zero weapon (empty/hands) and malee weapon to all the classes
	for(i = 1; i < WP_MAX_CLASSES; i++) {
		if(i * WP_MAX_WEAPONS >= WP_NUM_WEAPONS) {
			break;
		}

#ifdef USE_INSTAGIB
		if(g_instagib.integer) {
			Add_Weapon_Ammo(ent, WP_RAILGUN, INFINITE);
		}
#endif
#ifdef USE_TRINITY
		if(g_unholyTrinity.integer) {
			Add_Weapon_Ammo(ent, WP_RAILGUN, INFINITE);
			Add_Weapon_Ammo(ent, WP_LIGHTNING, INFINITE);
			Add_Weapon_Ammo(ent, WP_ROCKET_LAUNCHER, INFINITE);
		}
		#endif
#ifdef USE_HOTRPG
		if(g_hotRockets.integer) {
			Add_Weapon_Ammo(ent, WP_ROCKET_LAUNCHER, INFINITE);
		}
#endif
#ifdef USE_HOTBFG
		if(g_hotBFG.integer) {
			Add_Weapon_Ammo(ent, WP_BFG, INFINITE);
		}
#endif

		if(!( !wp_gauntEnable.integer
#ifdef USE_HOTRPG
			|| g_hotRockets.integer
#endif
#ifdef USE_HOTBFG
			|| g_hotRockets.integer
#endif
#ifdef USE_TRINITY
			|| g_unholyTrinity.integer
#endif
#ifdef USE_INSTAGIB
			|| g_instagib.integer
#endif
		)) {


		Add_Weapon_Ammo(ent, i * WP_MAX_WEAPONS + WP_NONE, INFINITE);
		Add_Weapon_Ammo(ent, i * WP_MAX_WEAPONS + WP_GAUNTLET, INFINITE);

		}
	}
#endif


#endif

	// health will count down towards max_health
	ent->health = client->ps.stats[STAT_HEALTH] = client->ps.stats[STAT_MAX_HEALTH] + 25;

#if defined(USE_RPG_STATS) || defined(USE_ADVANCED_CLASS) || defined(USE_RUNES)
	client->ps.stats[STAT_STAMINA] = g_stamina.integer;
	// start with ability powerup
	client->ps.stats[STAT_ABILITY] = g_ability.integer;
#endif

#ifdef USE_LOCAL_DMG
  // return to normal speed, McBain
  client->ps.speed = g_speed.value;
  client->lasthurt_location = LOCATION_NONE;
#endif

	G_SetOrigin( ent, spawn_origin );
	VectorCopy( spawn_origin, client->ps.origin );

	// the respawned flag will be cleared after the attack and jump keys come up
	client->ps.pm_flags |= PMF_RESPAWNED;

	trap_GetUsercmd( client - level.clients, &ent->client->pers.cmd );
	SetClientViewAngle( ent, spawn_angles );

#ifdef USE_VEHICLES
	ent->client->pers.cmd.buttons = 0;
	//client->frameNum = 0;
	//client->pmoveTime = 0;
	client->car.initializeOnNextMove = qtrue;
	client->car.onGroundTime = level.time;
	client->car.offGroundTime = level.time;

#endif

	// entity should be unlinked before calling G_KillBox()	
	if ( !isSpectator )
		G_KillBox( ent );

	// force the base weapon up
	client->ps.weapon = WP_MACHINEGUN;
	client->ps.weaponstate = WEAPON_READY;

	// don't allow full run speed for a bit
	client->ps.pm_flags |= PMF_TIME_KNOCKBACK;
	client->ps.pm_time = 100;

	client->respawnTime = level.time;
	client->inactivityTime = level.time + g_inactivity.integer * 1000;
	client->latched_buttons = 0;

	// set default animations
	client->ps.torsoAnim = TORSO_STAND;
	client->ps.legsAnim = LEGS_IDLE;

	if ( level.intermissiontime ) {
		MoveClientToIntermission( ent );
	} else {
		if ( !isSpectator )
			trap_LinkEntity( ent );
		// fire the targets of the spawn point
		G_UseTargets( spawnPoint, ent );

		// select the highest weapon number available, after any
		// spawn given items have fired
		client->ps.weapon = 1;
#ifdef USE_ADVANCED_WEAPONS
		for ( i = WP_NUM_WEAPONS - 1 ; i > 0 ; i-- ) {
			if ( client->classWeapons[i] ) {
				client->ps.weapon = i;
				client->weaponClass = floor(i / WP_MAX_WEAPONS);
				break;
			}
		}
#else
		for ( i = WP_MAX_WEAPONS - 1 ; i > 0 ; i-- ) {
			if ( client->ps.stats[STAT_WEAPONS] & ( 1 << i ) ) {
				client->ps.weapon = i;
				break;
			}
		}
#endif
	}

	// run a client frame to drop exactly to the floor,
	// initialize animations and other things
	client->ps.commandTime = level.time - 100;
	client->pers.cmd.serverTime = level.time;
	ClientThink( ent-g_entities );

	BG_PlayerStateToEntityState( &client->ps, &ent->s, qtrue );
	VectorCopy( client->ps.origin, ent->r.currentOrigin );

	// run the presend to set anything else
	ClientEndFrame( ent );

	// clear entity state values
	BG_PlayerStateToEntityState( &client->ps, &ent->s, qtrue );
}


/*
===========
ClientDisconnect

Called when a player drops from the server.
Will not be called between levels.

This should NOT be called directly by any game logic,
call trap_DropClient(), which will call this and do
server system housekeeping.
============
*/
void ClientDisconnect( int clientNum ) {
	gentity_t	*ent;
	gentity_t	*tent;
	int			i;

	// cleanup if we are kicking a bot that
	// hasn't spawned yet
	G_RemoveQueuedBotBegin( clientNum );

	ent = g_entities + clientNum;
	if (!ent->client || ent->client->pers.connected == CON_DISCONNECTED) {
		return;
	}

	// stop any following clients
	for ( i = 0 ; i < level.maxclients ; i++ ) {
		if ( level.clients[i].sess.sessionTeam == TEAM_SPECTATOR
			&& level.clients[i].sess.spectatorState == SPECTATOR_FOLLOW
			&& level.clients[i].sess.spectatorClient == clientNum ) {
			StopFollowing( &g_entities[i], qtrue );
		}
	}

	// send effect if they were completely connected
	if ( ent->client->pers.connected == CON_CONNECTED 
		&& ent->client->sess.sessionTeam != TEAM_SPECTATOR ) {
		tent = G_TempEntity( ent->client->ps.origin, EV_PLAYER_TELEPORT_OUT );
		tent->s.clientNum = ent->s.clientNum;

		// They don't get to take powerups with them!
		// Especially important for stuff like CTF flags
		TossClientItems( ent );
#ifdef MISSIONPACK
		TossClientPersistantPowerups( ent );
		if( g_gametype.integer == GT_HARVESTER ) {
			TossClientCubes( ent );
		}
#endif

	}

	G_RevertVote( ent->client );

	G_LogPrintf( "ClientDisconnect: %i\n", clientNum );

	// if we are playing in tourney mode and losing, give a win to the other player
	if ( (g_gametype.integer == GT_TOURNAMENT )
		&& !level.intermissiontime
		&& !level.warmupTime && level.sortedClients[1] == clientNum ) {
		level.clients[ level.sortedClients[0] ].sess.wins++;
		ClientUserinfoChanged( level.sortedClients[0] );
	}

	trap_UnlinkEntity( ent );
	ent->s.modelindex = 0;
	ent->inuse = qfalse;
	ent->classname = "disconnected";
	ent->client->pers.connected = CON_DISCONNECTED;
	ent->client->ps.persistant[PERS_TEAM] = TEAM_FREE;
	ent->client->sess.sessionTeam = TEAM_FREE;

	trap_SetConfigstring( CS_PLAYERS + clientNum, "" );

	G_ClearClientSessionData( ent->client );

	CalculateRanks();

	if ( ent->r.svFlags & SVF_BOT ) {
		BotAIShutdownClient( clientNum, qfalse );
	}
}
