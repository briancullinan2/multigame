// Copyright (C) 1999-2000 Id Software, Inc.
//
#include "g_local.h"

#if defined(MISSIONPACK) || defined(USE_CLASSIC_HUD)
#include "../../ui/menudef.h"			// for the voice chats
#endif

/*
==================
DeathmatchScoreboardMessage

==================
*/
void DeathmatchScoreboardMessage( gentity_t *ent ) {
	char		entry[256]; // enough to hold 14 integers
	char		string[MAX_STRING_CHARS-1];
	int			stringlength;
	int			i, j, ping, prefix;
	gclient_t	*cl;
	int			numSorted, scoreFlags, accuracy, perfect;

	// send the latest information on all clients
	string[0] = '\0';
	stringlength = 0;
	scoreFlags = 0;

	numSorted = level.numConnectedClients;

	// estimate prefix length to avoid oversize of final string
	prefix = BG_sprintf( entry, "scores %i %i %i", level.teamScores[TEAM_RED], level.teamScores[TEAM_BLUE], numSorted );
	
	for ( i = 0 ; i < numSorted ; i++ ) {

		cl = &level.clients[level.sortedClients[i]];

		if ( cl->pers.connected == CON_CONNECTING ) {
			ping = -1;
		} else {
			ping = cl->ps.ping < 999 ? cl->ps.ping : 999;
		}

		if( cl->accuracy_shots ) {
			accuracy = cl->accuracy_hits * 100 / cl->accuracy_shots;
		} else {
			accuracy = 0;
		}

		perfect = ( cl->ps.persistant[PERS_RANK] == 0 && cl->ps.persistant[PERS_KILLED] == 0 ) ? 1 : 0;

		j = BG_sprintf( entry, " %i %i %i %i %i %i %i %i %i %i %i %i %i %i",
			level.sortedClients[i],
			cl->ps.persistant[PERS_SCORE],
			ping,
			(level.time - cl->pers.enterTime)/60000,
			scoreFlags,
			g_entities[level.sortedClients[i]].s.powerups,
			accuracy, 
			cl->ps.persistant[PERS_IMPRESSIVE_COUNT],
			cl->ps.persistant[PERS_EXCELLENT_COUNT],
			cl->ps.persistant[PERS_GAUNTLET_FRAG_COUNT], 
			cl->ps.persistant[PERS_DEFEND_COUNT], 
			cl->ps.persistant[PERS_ASSIST_COUNT], 
			perfect,
			cl->ps.persistant[PERS_CAPTURES]);

		if ( stringlength + j + prefix >= sizeof( string ) )
			break;

		strcpy( string + stringlength, entry );
		stringlength += j;
	}

	trap_SendServerCommand( ent-g_entities, va( "scores %i %i %i%s", i,
		level.teamScores[TEAM_RED], level.teamScores[TEAM_BLUE],
		string ) );
}


/*
==================
Cmd_Score_f

Request current scoreboard information
==================
*/
void Cmd_Score_f( gentity_t *ent ) {
	DeathmatchScoreboardMessage( ent );
}


/*
==================
CheatsOk
==================
*/
qboolean	CheatsOk( gentity_t *ent ) {
	if ( !g_cheats.integer ) {
		trap_SendServerCommand( ent-g_entities, "print \"Cheats are not enabled on this server.\n\"");
		return qfalse;
	}
	if ( ent->health <= 0 ) {
		trap_SendServerCommand( ent-g_entities, "print \"You must be alive to use this command.\n\"");
		return qfalse;
	}
	return qtrue;
}


/*
==================
ConcatArgs
==================
*/
char *ConcatArgs( int start ) {
	static char line[MAX_STRING_CHARS];
	char	arg[MAX_STRING_CHARS];
	int		i, c, tlen;
	int		len;

	len = 0;
	c = trap_Argc();
	for ( i = start ; i < c ; i++ ) {
		trap_Argv( i, arg, sizeof( arg ) );
		tlen = (int)strlen( arg );
		if ( len + tlen >= sizeof( line )-1 ) {
			break;
		}
		memcpy( line + len, arg, tlen );
		len += tlen;
		if ( i != c - 1 ) {
			line[len] = ' ';
			len++;
		}
	}

	line[len] = '\0';

	return line;
}


/*
==================
SanitizeString

Remove case and control characters
==================
*/
void SanitizeString( const char *in, char *out ) {
	while ( *in ) {
		if ( *in == 27 ) {
			in += 2;		// skip color code
			continue;
		}
		if ( *in < ' ' ) {
			in++;
			continue;
		}
		*out = tolower( *in );
		out++;
		in++;
	}

	*out = '\0';
}


/*
==================
ClientNumberFromString

Returns a player number for either a number or name string
Returns -1 if invalid
==================
*/
int ClientNumberFromString( gentity_t *to, char *s ) {
	gclient_t	*cl;
	int			idnum;
	char		s2[MAX_STRING_CHARS];
	char		n2[MAX_STRING_CHARS];

	// numeric values are just slot numbers
	if (s[0] >= '0' && s[0] <= '9') {
		idnum = atoi( s );
		if ( (unsigned) idnum >= (unsigned)level.maxclients ) {
			trap_SendServerCommand( to-g_entities, va("print \"Bad client slot: %i\n\"", idnum));
			return -1;
		}

		cl = &level.clients[idnum];
		if ( cl->pers.connected != CON_CONNECTED ) {
			trap_SendServerCommand( to-g_entities, va("print \"Client %i is not active\n\"", idnum));
			return -1;
		}
		return idnum;
	}

	// check for a name match
	SanitizeString( s, s2 );
	for ( idnum=0,cl=level.clients ; idnum < level.maxclients ; idnum++,cl++ ) {
		if ( cl->pers.connected != CON_CONNECTED ) {
			continue;
		}
		SanitizeString( cl->pers.netname, n2 );
		if ( !strcmp( n2, s2 ) ) {
			return idnum;
		}
	}

	trap_SendServerCommand( to-g_entities, va("print \"User %s is not on the server\n\"", s));
	return -1;
}


/*
==================
Cmd_Give_f

Give items to a client
==================
*/
void Cmd_Give_f( gentity_t *ent )
{
	char		*name;
	gitem_t		*it;
#ifndef USE_ADVANCED_WEAPONS
	int			i;
#endif
	qboolean	give_all;
	gentity_t	*it_ent;
	trace_t		trace;

	if ( !CheatsOk( ent ) ) {
		return;
	}

	name = ConcatArgs( 1 );

	if (Q_stricmp(name, "all") == 0)
		give_all = qtrue;
	else
		give_all = qfalse;

	if (give_all || Q_stricmp( name, "health") == 0)
	{
		ent->health = ent->client->ps.stats[STAT_MAX_HEALTH];
		if (!give_all)
			return;
	}

#ifdef USE_ADVANCED_WEAPONS

	if (give_all || Q_stricmp(name, "weapons") == 0)
	{
		int i, j;
		for(i = 0; i < WP_MAX_CLASSES; i++) {
			for(j = 0; j < WP_MAX_WEAPONS && i * WP_MAX_WEAPONS + j < WP_NUM_WEAPONS; j++) {
				gitem_t *it = BG_FindItemForWeapon(i * WP_MAX_WEAPONS + j);
				if(it) {
					ent->client->classWeapons[i * WP_MAX_WEAPONS + j]++;
					ent->client->weaponsModified[i] = qtrue;
				}
			}
		}
	}

	if (give_all || Q_stricmp(name, "ammo") == 0)
	{
		int i, j;
		for(i = 0; i < WP_MAX_CLASSES; i++) {
			for ( j = 0 ; j < WP_MAX_WEAPONS && i * WP_MAX_WEAPONS + j < WP_NUM_WEAPONS; j++ ) {
				gitem_t *it = BG_FindAmmoForWeapon(i * WP_MAX_WEAPONS + j);
				if(i * WP_MAX_WEAPONS + j == WP_GAUNTLET
					|| i * WP_MAX_WEAPONS + j == WP_GAUNTLET2
					|| i * WP_MAX_WEAPONS + j == WP_GRAPPLING_HOOK) {
					ent->client->classAmmo[i * WP_MAX_WEAPONS + j] = INFINITE;
				} else 
				if(it) {
					ent->client->classAmmo[i * WP_MAX_WEAPONS + j] = 999;
				}
			}
		}
	}
#else

	if (give_all || Q_stricmp(name, "weapons") == 0)
	{
#ifdef USE_GRAPPLE
		ent->client->ps.stats[STAT_WEAPONS] = (1 << WP_MAX_WEAPONS) - 1 - 
			( 1 << WP_GRAPPLING_HOOK ) - ( 1 << WP_NONE );
#else
		ent->client->ps.stats[STAT_WEAPONS] = (1 << WP_MAX_WEAPONS) - 1 - ( 1 << WP_NONE );
#endif
		if (!give_all)
			return;
	}

	if (give_all || Q_stricmp(name, "ammo") == 0)
	{
		for ( i = 0 ; i < WP_MAX_WEAPONS ; i++ ) {
			ent->client->ps.ammo[i] = 999;
		}
		if (!give_all)
			return;
	}

#endif

	if (give_all || Q_stricmp(name, "armor") == 0)
	{
		ent->client->ps.stats[STAT_ARMOR] = 200;

		if (!give_all)
			return;
	}

	if (Q_stricmp(name, "excellent") == 0) {
		ent->client->ps.persistant[PERS_EXCELLENT_COUNT]++;
		return;
	}
	if (Q_stricmp(name, "impressive") == 0) {
		ent->client->ps.persistant[PERS_IMPRESSIVE_COUNT]++;
		return;
	}
	if (Q_stricmp(name, "gauntletaward") == 0) {
		ent->client->ps.persistant[PERS_GAUNTLET_FRAG_COUNT]++;
		return;
	}
	if (Q_stricmp(name, "defend") == 0) {
		ent->client->ps.persistant[PERS_DEFEND_COUNT]++;
		return;
	}
	if (Q_stricmp(name, "assist") == 0) {
		ent->client->ps.persistant[PERS_ASSIST_COUNT]++;
		return;
	}

	// spawn a specific item right on the player
	if ( !give_all ) {
#ifdef USE_RUNES
    char	arg[MAX_TOKEN_CHARS];
    trap_Argv( 1, arg, sizeof( arg ) );
    if(	Q_stricmp(arg, "rune") == 0 ) {
      name = ConcatArgs(2);
      it = BG_FindItemForRune(atoi(name));
      if(!it) {
        Com_Printf("Unknown rune: %s\n", name);
        return;
      }
      //if(ent->rune)
      //  ent->client->inventory[ent->rune] = 0;
      //ent->rune = 0;
    } else
#endif
		it = BG_FindItem (name);
		if (!it) {
			return;
		}

		it_ent = G_Spawn();
		VectorCopy( ent->r.currentOrigin, it_ent->s.origin );
		it_ent->classname = it->classname;
		G_SpawnItem (it_ent, it);
		FinishSpawningItem(it_ent );
		memset( &trace, 0, sizeof( trace ) );
		Touch_Item (it_ent, ent, &trace);
		if (it_ent->inuse) {
			G_FreeEntity( it_ent );
		}
	}
}


/*
==================
Cmd_God_f

Sets client to godmode

argv(0) god
==================
*/
void Cmd_God_f( gentity_t *ent )
{
	const char *msg;

	if ( !CheatsOk( ent ) ) {
		return;
	}

	ent->flags ^= FL_GODMODE;
	if (!(ent->flags & FL_GODMODE) )
		msg = "godmode OFF\n";
	else
		msg = "godmode ON\n";

	trap_SendServerCommand( ent-g_entities, va( "print \"%s\"", msg ) );
}


/*
==================
Cmd_Notarget_f

Sets client to notarget

argv(0) notarget
==================
*/
void Cmd_Notarget_f( gentity_t *ent ) {
	const char *msg;

	if ( !CheatsOk( ent ) ) {
		return;
	}

	ent->flags ^= FL_NOTARGET;
	if (!(ent->flags & FL_NOTARGET) )
		msg = "notarget OFF\n";
	else
		msg = "notarget ON\n";

	trap_SendServerCommand( ent-g_entities, va( "print \"%s\"", msg ) );
}


/*
==================
Cmd_Noclip_f

argv(0) noclip
==================
*/
void Cmd_Noclip_f( gentity_t *ent ) {
	const char *msg;

	if ( !CheatsOk( ent ) ) {
		return;
	}

	if ( ent->client->noclip ) {
		msg = "noclip OFF\n";
	} else {
		msg = "noclip ON\n";
	}
	ent->client->noclip = !ent->client->noclip;

	trap_SendServerCommand( ent-g_entities, va("print \"%s\"", msg));
}


/*
==================
Cmd_LevelShot_f

This is just to help generate the level pictures
for the menus.  It goes to the intermission immediately
and sends over a command to the client to resize the view,
hide the scoreboard, and take a special screenshot
==================
*/
void Cmd_LevelShot_f( gentity_t *ent ) {
	if ( !CheatsOk( ent ) ) {
		return;
	}

	// doesn't work in single player
	if ( g_gametype.integer == GT_SINGLE_PLAYER ) {
		trap_SendServerCommand( ent-g_entities, 
			"print \"Must be in g_gametype 0 for levelshot\n\"" );
		return;
	}

	if ( !ent->client->pers.localClient )
	{
		trap_SendServerCommand( ent - g_entities,
			"print \"The levelshot command must be executed by a local client\n\"" );
		return;
	}

	BeginIntermission();
	trap_SendServerCommand( ent-g_entities, "clientLevelShot" );
}


/*
==================
Cmd_TeamTask_f
==================
*/
void Cmd_TeamTask_f( gentity_t *ent ) {
	char userinfo[MAX_INFO_STRING];
	char arg[MAX_TOKEN_CHARS];
	int task;
	int client = ent->client - level.clients;

	if ( trap_Argc() != 2 ) {
		return;
	}
	trap_Argv( 1, arg, sizeof( arg ) );
	task = atoi( arg );

	trap_GetUserinfo( client, userinfo, sizeof( userinfo ) );
	Info_SetValueForKey( userinfo, "teamtask", va( "%d", task ) );
	trap_SetUserinfo( client, userinfo );
	ClientUserinfoChanged( client );
}


/*
=================
Cmd_Kill_f
=================
*/
void Cmd_Kill_f( gentity_t *ent ) {
	if ( ent->client->sess.sessionTeam == TEAM_SPECTATOR ) {
		return;
	}
	if (ent->health <= 0) {
		return;
	}
	ent->flags &= ~FL_GODMODE;
	ent->client->ps.stats[STAT_HEALTH] = ent->health = -999;
	player_die (ent, ent, ent, 100000, MOD_SUICIDE);
}


/*
=================
BroadcastTeamChange

Let everyone know about a team change
=================
*/
void BroadcastTeamChange( gclient_t *client, team_t oldTeam )
{
	int clientNum = client - level.clients;

	if ( client->sess.sessionTeam == TEAM_RED ) {
		G_BroadcastServerCommand( clientNum, va("cp \"%s" S_COLOR_WHITE " joined the " S_COLOR_RED "red" S_COLOR_WHITE " team.\n\"",
			client->pers.netname) );
	} else if ( client->sess.sessionTeam == TEAM_BLUE ) {
		G_BroadcastServerCommand( clientNum, va("cp \"%s" S_COLOR_WHITE " joined the " S_COLOR_BLUE "blue" S_COLOR_WHITE " team.\n\"",
		client->pers.netname));
	} else if ( client->sess.sessionTeam == TEAM_SPECTATOR && oldTeam != TEAM_SPECTATOR ) {
		G_BroadcastServerCommand( clientNum, va("cp \"%s" S_COLOR_WHITE " joined the spectators.\n\"",
		client->pers.netname));
	} else if ( client->sess.sessionTeam == TEAM_FREE ) {
		G_BroadcastServerCommand( clientNum, va("cp \"%s" S_COLOR_WHITE " joined the battle.\n\"",
		client->pers.netname));
	}
}


static qboolean AllowTeamSwitch( int clientNum, team_t newTeam ) {

	if ( g_teamForceBalance.integer  ) {
		int		counts[TEAM_NUM_TEAMS];

		counts[TEAM_BLUE] = TeamCount( clientNum, TEAM_BLUE );
		counts[TEAM_RED] = TeamCount( clientNum, TEAM_RED );

		// We allow a spread of two
		if ( newTeam == TEAM_RED && counts[TEAM_RED] - counts[TEAM_BLUE] > 1 ) {
			trap_SendServerCommand( clientNum, "cp \"Red team has too many players.\n\"" );
			return qfalse; // ignore the request
		}

		if ( newTeam == TEAM_BLUE && counts[TEAM_BLUE] - counts[TEAM_RED] > 1 ) {
			trap_SendServerCommand( clientNum, "cp \"Blue team has too many players.\n\"" );
			return qfalse; // ignore the request
		}

		// It's ok, the team we are switching to has less or same number of players
	}

	return qtrue;
}


/*
=================
SetTeam
=================
*/
qboolean SetTeam( gentity_t *ent, const char *s ) {
	team_t				team, oldTeam;
	gclient_t			*client;
	int					clientNum;
	spectatorState_t	specState;
	int					specClient;
	int					teamLeader;
	qboolean			checkTeamLeader;

	//
	// see what change is requested
	//

	clientNum = ent - g_entities;
	client = level.clients + clientNum;

	// early team override
	if ( client->pers.connected == CON_CONNECTING && g_gametype.integer >= GT_TEAM ) {
		if ( !Q_stricmp( s, "red" ) || !Q_stricmp( s, "r" ) ) {
			team = TEAM_RED;
		} else if ( !Q_stricmp( s, "blue" ) || !Q_stricmp( s, "b" ) ) {
			team = TEAM_BLUE; 
#if defined(USE_ADVANCED_GAMES) || defined(USE_ADVANCED_TEAMS)
		} else if ( !Q_stricmp( s, "yellow" ) || !Q_stricmp( s, "y" ) || !Q_stricmp( s, "gold" ) || !Q_stricmp( s, "k" ) ) {
			team = TEAM_GOLD;
		} else if ( !Q_stricmp( s, "green" ) || !Q_stricmp( s, "g" ) ) {
			team = TEAM_GREEN; 
#endif
		} else {
			team = -1;
		}
		if ( team != -1 && AllowTeamSwitch( clientNum, team ) ) {
			client->sess.sessionTeam = team;
			client->pers.teamState.state = TEAM_BEGIN;
			G_WriteClientSessionData( client );
			// count current clients and rank for scoreboard
			CalculateRanks();
		}
		return qfalse; // bypass flood protection
	}

	specClient = clientNum;
	specState = SPECTATOR_NOT;
	if ( !Q_stricmp( s, "scoreboard" ) || !Q_stricmp( s, "score" )  ) {
		team = TEAM_SPECTATOR;
		specState = SPECTATOR_SCOREBOARD;
	} else if ( !Q_stricmp( s, "follow1" ) ) {
		team = TEAM_SPECTATOR;
		specState = SPECTATOR_FOLLOW;
		specClient = -1;
	} else if ( !Q_stricmp( s, "follow2" ) ) {
		team = TEAM_SPECTATOR;
		specState = SPECTATOR_FOLLOW;
		specClient = -2;
	} else if ( !Q_stricmp( s, "spectator" ) || !Q_stricmp( s, "s" ) ) {
		team = TEAM_SPECTATOR;
		specState = SPECTATOR_FREE;
	} else if ( g_gametype.integer >= GT_TEAM ) {
		// if running a team game, assign player to one of the teams
		specState = SPECTATOR_NOT;
		if ( !Q_stricmp( s, "red" ) || !Q_stricmp( s, "r" ) ) {
			team = TEAM_RED;
		} else if ( !Q_stricmp( s, "blue" ) || !Q_stricmp( s, "b" ) ) {
			team = TEAM_BLUE;
#if defined(USE_ADVANCED_GAMES) || defined(USE_ADVANCED_TEAMS)
		} else if ( !Q_stricmp( s, "yellow" ) || !Q_stricmp( s, "y" ) || !Q_stricmp( s, "gold" ) || !Q_stricmp( s, "k" ) ) {
			team = TEAM_GOLD;
		} else if ( !Q_stricmp( s, "green" ) || !Q_stricmp( s, "g" ) ) {
			team = TEAM_GREEN;

#endif
		} else {
			// pick the team with the least number of players
			team = PickTeam( clientNum );
		}

		if ( !AllowTeamSwitch( clientNum, team ) ) {
			return qtrue;
		}

	} else {
		// force them to spectators if there aren't any spots free
		team = TEAM_FREE;
	}

	// override decision if limiting the players
	if ( (g_gametype.integer == GT_TOURNAMENT)
		&& level.numNonSpectatorClients >= 2 ) {
		team = TEAM_SPECTATOR;
	} else if ( g_maxGameClients.integer > 0 && 
		level.numNonSpectatorClients >= g_maxGameClients.integer ) {
		team = TEAM_SPECTATOR;
	}

	//
	// decide if we will allow the change
	//
	oldTeam = client->sess.sessionTeam;
	if ( team == oldTeam ) {
		if ( team != TEAM_SPECTATOR )
			return qfalse;

		// do soft release if possible
		if ( ( client->ps.pm_flags & PMF_FOLLOW ) && client->sess.spectatorState == SPECTATOR_FOLLOW ) {
			StopFollowing( ent, qtrue );
			return qfalse;
		}

		// second spectator team request will move player to intermission point
		if ( client->ps.persistant[ PERS_TEAM ] == TEAM_SPECTATOR && !( client->ps.pm_flags & PMF_FOLLOW )
			&& client->sess.spectatorState == SPECTATOR_FREE ) {
			VectorCopy( level.intermission_origin, ent->s.origin );
			VectorCopy( level.intermission_origin, client->ps.origin );
			SetClientViewAngle( ent, level.intermission_angle );
			return qfalse;
		}
	}

	//
	// execute the team change
	//

	// if the player was dead leave the body
	if ( ent->health <= 0 ) {
		CopyToBodyQue( ent );
	}

	// he starts at 'base'
	client->pers.teamState.state = TEAM_BEGIN;

	if ( oldTeam != TEAM_SPECTATOR ) {
		
		// revert any casted votes
		if ( oldTeam != team )
			G_RevertVote( ent->client );

		// Kill him (makes sure he loses flags, etc)
		ent->flags &= ~FL_GODMODE;
		ent->client->ps.stats[STAT_HEALTH] = ent->health = 0;
#ifdef USE_MODES_DEATH
		player_die (ent, ent, ent, 100000, MOD_SPECTATE);
#else
		player_die (ent, ent, ent, 100000, MOD_SUICIDE);
#endif
	}

	// they go to the end of the line for tournements
	if ( team == TEAM_SPECTATOR ) {
		client->sess.spectatorTime = 0;
	}

	client->sess.sessionTeam = team;
	client->sess.spectatorState = specState;
	client->sess.spectatorClient = specClient;

	checkTeamLeader = client->sess.teamLeader;
	client->sess.teamLeader = qfalse;

	if ( team == TEAM_RED || team == TEAM_BLUE ) {
		teamLeader = TeamLeader( team );
		// if there is no team leader or the team leader is a bot and this client is not a bot
		if ( teamLeader == -1 || ( !(g_entities[clientNum].r.svFlags & SVF_BOT) && (g_entities[teamLeader].r.svFlags & SVF_BOT) ) ) {
			SetLeader( team, clientNum );
		}
	}

	// make sure there is a team leader on the team the player came from
	if ( oldTeam == TEAM_RED || oldTeam == TEAM_BLUE ) {
		if ( checkTeamLeader ) {
			CheckTeamLeader( oldTeam );
		}
	}

	G_WriteClientSessionData( client );

	BroadcastTeamChange( client, oldTeam );

	// get and distribute relevent paramters
	ClientUserinfoChanged( clientNum );

	ClientBegin( clientNum );

	return qtrue;
}


/*
=================
StopFollowing

If the client being followed leaves the game, or you just want to drop
to free floating spectator mode
=================
*/
void StopFollowing( gentity_t *ent, qboolean release ) {
	gclient_t *client;

	if ( ent->r.svFlags & SVF_BOT || !ent->inuse )
		return;

	client = ent->client;

	client->ps.persistant[ PERS_TEAM ] = TEAM_SPECTATOR;	
	client->sess.sessionTeam = TEAM_SPECTATOR;	
	if ( release ) {
		client->ps.stats[STAT_HEALTH] = ent->health = 1;
#ifdef USE_ADVANCED_WEAPONS
		memset( client->classAmmo, 0, sizeof( client->classAmmo ) );
		memset( client->classWeapons, 0, sizeof( client->classWeapons ) );
#endif
#ifdef USE_ADVANCED_ITEMS
		memset( client->inventory, 0, sizeof( client->inventory ) );
		memset( client->ps.powerTimes, 0, sizeof ( client->ps.powerTimes ) );
#else
		memset( client->ps.powerups, 0, sizeof ( client->ps.powerups ) );
#endif
	}
	SetClientViewAngle( ent, client->ps.viewangles );

	client->sess.spectatorState = SPECTATOR_FREE;
	client->ps.pm_flags &= ~PMF_FOLLOW;
	//ent->r.svFlags &= ~SVF_BOT;

	client->ps.clientNum = ent - g_entities;
}


/*
=================
Cmd_Team_f
=================
*/
static void Cmd_Team_f( gentity_t *ent ) {
	char		s[MAX_TOKEN_CHARS];

	if ( trap_Argc() != 2 ) {
		switch ( ent->client->sess.sessionTeam ) {
		case TEAM_BLUE:
			trap_SendServerCommand( ent-g_entities, "print \"Blue team\n\"" );
			break;
		case TEAM_RED:
			trap_SendServerCommand( ent-g_entities, "print \"Red team\n\"" );
			break;
#if defined(USE_ADVANCED_GAMES) || defined(USE_ADVANCED_TEAMS)
		case TEAM_GOLD:
			trap_SendServerCommand( ent-g_entities, "print \"Gold team\n\"" );
			break;
		case TEAM_GREEN:
			trap_SendServerCommand( ent-g_entities, "print \"Green team\n\"" );
			break;
#endif
		case TEAM_FREE:
			trap_SendServerCommand( ent-g_entities, "print \"Free team\n\"" );
			break;
		case TEAM_SPECTATOR:
			trap_SendServerCommand( ent-g_entities, "print \"Spectator team\n\"" );
			break;
		default:
			break;
		}
		return;
	}

	if ( ent->client->switchTeamTime > level.time ) {
		trap_SendServerCommand( ent-g_entities, "print \"May not switch teams more than once per 5 seconds.\n\"" );
		return;
	}

	// if they are playing a tournement game, count as a loss
	if ( (g_gametype.integer == GT_TOURNAMENT )
		&& ent->client->sess.sessionTeam == TEAM_FREE ) {
		ent->client->sess.losses++;
	}

	trap_Argv( 1, s, sizeof( s ) );

	if ( SetTeam( ent, s ) ) {
		ent->client->switchTeamTime = level.time + 5000;
	}
}


/*
=================
Cmd_Follow_f
=================
*/
static void Cmd_Follow_f( gentity_t *ent ) {
	int		i;
	char	arg[MAX_TOKEN_CHARS];

	if ( trap_Argc() != 2 ) {
		if ( ent->client->sess.spectatorState == SPECTATOR_FOLLOW ) {
			StopFollowing( ent, qtrue );
		}
		return;
	}

	trap_Argv( 1, arg, sizeof( arg ) );
	i = ClientNumberFromString( ent, arg );
	if ( i == -1 ) {
		return;
	}

	// can't follow self
	if ( &level.clients[ i ] == ent->client ) {
		return;
	}

	// can't follow another spectator
	if ( level.clients[ i ].sess.sessionTeam == TEAM_SPECTATOR ) {
		return;
	}

	// if they are playing a tournement game, count as a loss
	if ( (g_gametype.integer == GT_TOURNAMENT )
		&& ent->client->sess.sessionTeam == TEAM_FREE ) {
		ent->client->sess.losses++;
	}

	// first set them to spectator
	if ( ent->client->sess.sessionTeam != TEAM_SPECTATOR ) {
		SetTeam( ent, "spectator" );
	}

	ent->client->sess.spectatorState = SPECTATOR_FOLLOW;
	ent->client->sess.spectatorClient = i;
}


/*
=================
Cmd_FollowCycle_f
=================
*/
void Cmd_FollowCycle_f( gentity_t *ent, int dir ) {
	int		clientnum;
	int		original;
	gclient_t	*client;

	// if they are playing a tournement game, count as a loss
	if ( (g_gametype.integer == GT_TOURNAMENT )
		&& ent->client->sess.sessionTeam == TEAM_FREE ) {
		ent->client->sess.losses++;
	}

	client = ent->client;

	// first set them to spectator
	if ( client->sess.spectatorState == SPECTATOR_NOT ) {
		SetTeam( ent, "spectator" );
	}

	if ( dir != 1 && dir != -1 ) {
		G_Error( "Cmd_FollowCycle_f: bad dir %i", dir );
	}

	clientnum = client->sess.spectatorClient;
	original = clientnum;
	do {
		clientnum += dir;
		if ( clientnum >= level.maxclients ) {
			clientnum = 0;
		}
		if ( clientnum < 0 ) {
			clientnum = level.maxclients - 1;
		}

		// can only follow connected clients
		if ( level.clients[ clientnum ].pers.connected != CON_CONNECTED ) {
			continue;
		}

		// can't follow another spectator
		if ( level.clients[ clientnum ].sess.sessionTeam == TEAM_SPECTATOR ) {
			continue;
		}

		// this is good, we can use it
		ent->client->sess.spectatorClient = clientnum;
		ent->client->sess.spectatorState = SPECTATOR_FOLLOW;
		return;
	} while ( clientnum != original );

	// leave it where it was
}


/*
==================
G_Say
==================
*/
static void G_SayTo( gentity_t *ent, gentity_t *other, int mode, int color, const char *name, const char *message ) {
	if (!other) {
		return;
	}
	if (!other->inuse) {
		return;
	}
	if (!other->client) {
		return;
	}
	if ( other->client->pers.connected != CON_CONNECTED ) {
		return;
	}
	if ( mode == SAY_TEAM  && !OnSameTeam(ent, other) ) {
		return;
	}
	// no chatting to players in tournements
	if ( (g_gametype.integer == GT_TOURNAMENT )
		&& other->client->sess.sessionTeam == TEAM_FREE
		&& ent->client->sess.sessionTeam != TEAM_FREE ) {
		return;
	}

	trap_SendServerCommand( other-g_entities, va( "%s \"%s%c%c%s\" %i", mode == SAY_TEAM ? "tchat" : "chat", 
		name, Q_COLOR_ESCAPE, color, message, ent - g_entities ) );
}

#define EC		"\x19"

static void G_Say( gentity_t *ent, gentity_t *target, int mode, const char *chatText ) {
	int			j;
	gentity_t	*other;
	int			color;
	char		name[64 + 64 + 12]; // name + location + formatting
	// don't let text be too long for malicious reasons
	char		text[MAX_SAY_TEXT];
	char		location[64];

	if ( g_gametype.integer < GT_TEAM && mode == SAY_TEAM ) {
		mode = SAY_ALL;
	}

	switch ( mode ) {
	default:
	case SAY_ALL:
		G_LogPrintf( "say: %s: %s\n", ent->client->pers.netname, chatText );
		Com_sprintf (name, sizeof(name), "%s%c%c"EC": ", ent->client->pers.netname, Q_COLOR_ESCAPE, COLOR_WHITE );
		color = COLOR_GREEN;
		break;
	case SAY_TEAM:
		G_LogPrintf( "sayteam: %s: %s\n", ent->client->pers.netname, chatText );
		if (Team_GetLocationMsg(ent, location, sizeof(location)))
			Com_sprintf (name, sizeof(name), EC"(%s%c%c"EC") (%s)"EC": ", 
				ent->client->pers.netname, Q_COLOR_ESCAPE, COLOR_WHITE, location);
		else
			Com_sprintf (name, sizeof(name), EC"(%s%c%c"EC")"EC": ", 
				ent->client->pers.netname, Q_COLOR_ESCAPE, COLOR_WHITE );
		color = COLOR_CYAN;
		break;
	case SAY_TELL:
		if (target && target->inuse && target->client && g_gametype.integer >= GT_TEAM &&
			target->client->sess.sessionTeam == ent->client->sess.sessionTeam &&
			Team_GetLocationMsg(ent, location, sizeof(location)))
			Com_sprintf (name, sizeof(name), EC"[%s%c%c"EC"] (%s)"EC": ", ent->client->pers.netname, Q_COLOR_ESCAPE, COLOR_WHITE, location );
		else
			Com_sprintf (name, sizeof(name), EC"[%s%c%c"EC"]"EC": ", ent->client->pers.netname, Q_COLOR_ESCAPE, COLOR_WHITE );
		color = COLOR_MAGENTA;
		break;
	}

	Q_strncpyz( text, chatText, sizeof(text) );

	if ( target ) {
		G_SayTo( ent, target, mode, color, name, text );
		return;
	}

	// echo the text to the console
	if ( g_dedicated.integer ) {
		G_Printf( "%s%s\n", name, text);
	}

	// send it to all the apropriate clients
	for (j = 0; j < level.maxclients; j++) {
		other = &g_entities[j];
		G_SayTo( ent, other, mode, color, name, text );
	}
}


/*
==================
Cmd_Say_f
==================
*/
static void Cmd_Say_f( gentity_t *ent, int mode, qboolean arg0 ) {
	char		*p;

	if ( trap_Argc () < 2 && !arg0 ) {
		return;
	}

	if (arg0)
	{
		p = ConcatArgs( 0 );
	}
	else
	{
		p = ConcatArgs( 1 );
	}

	G_Say( ent, NULL, mode, p );
}


/*
==================
Cmd_Tell_f
==================
*/
static void Cmd_Tell_f( gentity_t *ent ) {
	int			targetNum;
	gentity_t	*target;
	char		*p;
	char		arg[MAX_TOKEN_CHARS];

	if ( trap_Argc () < 2 ) {
		return;
	}

	trap_Argv( 1, arg, sizeof( arg ) );
	targetNum = atoi( arg );
	if ( (unsigned)targetNum >= (unsigned)level.maxclients ) {
		return;
	}

	target = &g_entities[targetNum];
	if ( !target->inuse || !target->client ) {
		return;
	}

	p = ConcatArgs( 2 );

	G_LogPrintf( "tell: %s to %s: %s\n", ent->client->pers.netname, target->client->pers.netname, p );
	G_Say( ent, target, SAY_TELL, p );
	// don't tell to the player self if it was already directed to this player
	// also don't send the chat back to a bot
	if ( ent != target && !(ent->r.svFlags & SVF_BOT)) {
		G_Say( ent, ent, SAY_TELL, p );
	}
}

#ifdef MISSIONPACK

static void G_VoiceTo( gentity_t *ent, gentity_t *other, int mode, const char *id, qboolean voiceonly ) {
	int color;
	char *cmd;

	if (!other) {
		return;
	}
	if (!other->inuse) {
		return;
	}
	if (!other->client) {
		return;
	}
	if ( mode == SAY_TEAM && !OnSameTeam(ent, other) ) {
		return;
	}
	// no chatting to players in tournements
	if ( g_gametype.integer == GT_TOURNAMENT ) {
		return;
	}

	if (mode == SAY_TEAM) {
		color = COLOR_CYAN;
		cmd = "vtchat";
	}
	else if (mode == SAY_TELL) {
		color = COLOR_MAGENTA;
		cmd = "vtell";
	}
	else {
		color = COLOR_GREEN;
		cmd = "vchat";
	}

	trap_SendServerCommand( other-g_entities, va("%s %d %d %d %s", cmd, voiceonly, ent->s.number, color, id));
}

void G_Voice( gentity_t *ent, gentity_t *target, int mode, const char *id, qboolean voiceonly ) {
	int			j;
	gentity_t	*other;

	if ( g_gametype.integer < GT_TEAM && mode == SAY_TEAM ) {
		mode = SAY_ALL;
	}

	if ( target ) {
		G_VoiceTo( ent, target, mode, id, voiceonly );
		return;
	}

	// echo the text to the console
	if ( g_dedicated.integer ) {
		G_Printf( "voice: %s %s\n", ent->client->pers.netname, id);
	}

	// send it to all the apropriate clients
	for (j = 0; j < level.maxclients; j++) {
		other = &g_entities[j];
		G_VoiceTo( ent, other, mode, id, voiceonly );
	}
}

/*
==================
Cmd_Voice_f
==================
*/
static void Cmd_Voice_f( gentity_t *ent, int mode, qboolean arg0, qboolean voiceonly ) {
	char		*p;

	if ( trap_Argc () < 2 && !arg0 ) {
		return;
	}

	if (arg0)
	{
		p = ConcatArgs( 0 );
	}
	else
	{
		p = ConcatArgs( 1 );
	}

	G_Voice( ent, NULL, mode, p, voiceonly );
}

/*
==================
Cmd_VoiceTell_f
==================
*/
static void Cmd_VoiceTell_f( gentity_t *ent, qboolean voiceonly ) {
	int			targetNum;
	gentity_t	*target;
	char		*id;
	char		arg[MAX_TOKEN_CHARS];

	if ( trap_Argc () < 2 ) {
		return;
	}

	trap_Argv( 1, arg, sizeof( arg ) );
	targetNum = atoi( arg );
	if ( targetNum < 0 || targetNum >= level.maxclients ) {
		return;
	}

	target = &g_entities[targetNum];
	if ( !target->inuse || !target->client ) {
		return;
	}

	id = ConcatArgs( 2 );

	G_LogPrintf( "vtell: %s to %s: %s\n", ent->client->pers.netname, target->client->pers.netname, id );
	G_Voice( ent, target, SAY_TELL, id, voiceonly );
	// don't tell to the player self if it was already directed to this player
	// also don't send the chat back to a bot
	if ( ent != target && !(ent->r.svFlags & SVF_BOT)) {
		G_Voice( ent, ent, SAY_TELL, id, voiceonly );
	}
}


/*
==================
Cmd_VoiceTaunt_f
==================
*/
static void Cmd_VoiceTaunt_f( gentity_t *ent ) {
	gentity_t *who;
	int i;

	if (!ent->client) {
		return;
	}

	// insult someone who just killed you
	if (ent->enemy && ent->enemy->client && ent->enemy->client->lastkilled_client == ent->s.number) {
		// i am a dead corpse
		if (!(ent->enemy->r.svFlags & SVF_BOT)) {
			G_Voice( ent, ent->enemy, SAY_TELL, VOICECHAT_DEATHINSULT, qfalse );
		}
		if (!(ent->r.svFlags & SVF_BOT)) {
			G_Voice( ent, ent,        SAY_TELL, VOICECHAT_DEATHINSULT, qfalse );
		}
		ent->enemy = NULL;
		return;
	}
	// insult someone you just killed
	if (ent->client->lastkilled_client >= 0 && ent->client->lastkilled_client != ent->s.number) {
		who = g_entities + ent->client->lastkilled_client;
		if (who->client) {
			// who is the person I just killed
			if (who->client->lasthurt_mod == MOD_GAUNTLET) {
				if (!(who->r.svFlags & SVF_BOT)) {
					G_Voice( ent, who, SAY_TELL, VOICECHAT_KILLGAUNTLET, qfalse );	// and I killed them with a gauntlet
				}
				if (!(ent->r.svFlags & SVF_BOT)) {
					G_Voice( ent, ent, SAY_TELL, VOICECHAT_KILLGAUNTLET, qfalse );
				}
			} else {
				if (!(who->r.svFlags & SVF_BOT)) {
					G_Voice( ent, who, SAY_TELL, VOICECHAT_KILLINSULT, qfalse );	// and I killed them with something else
				}
				if (!(ent->r.svFlags & SVF_BOT)) {
					G_Voice( ent, ent, SAY_TELL, VOICECHAT_KILLINSULT, qfalse );
				}
			}
			ent->client->lastkilled_client = -1;
			return;
		}
	}

	if (g_gametype.integer >= GT_TEAM) {
		// praise a team mate who just got a reward
		for(i = 0; i < MAX_CLIENTS; i++) {
			who = g_entities + i;
			if (who->client && who != ent && who->client->sess.sessionTeam == ent->client->sess.sessionTeam) {
				if (who->client->rewardTime > level.time) {
					if (!(who->r.svFlags & SVF_BOT)) {
						G_Voice( ent, who, SAY_TELL, VOICECHAT_PRAISE, qfalse );
					}
					if (!(ent->r.svFlags & SVF_BOT)) {
						G_Voice( ent, ent, SAY_TELL, VOICECHAT_PRAISE, qfalse );
					}
					return;
				}
			}
		}
	}

	// just say something
	G_Voice( ent, NULL, SAY_ALL, VOICECHAT_TAUNT, qfalse );
}
#endif


static char	*gc_orders[] = {
	"hold your position",
	"hold this position",
	"come here",
	"cover me",
	"guard location",
	"search and destroy",
	"report"
};

void Cmd_GameCommand_f( gentity_t *ent ) {
	int		player;
	int		order;
	char	str[MAX_TOKEN_CHARS];

	trap_Argv( 1, str, sizeof( str ) );
	player = atoi( str );
	trap_Argv( 2, str, sizeof( str ) );
	order = atoi( str );

	if ( (unsigned)player >= MAX_CLIENTS ) {
		return;
	}
	if ( (unsigned) order > ARRAY_LEN( gc_orders ) ) {
		return;
	}
	G_Say( ent, &g_entities[player], SAY_TELL, gc_orders[order] );
	G_Say( ent, ent, SAY_TELL, gc_orders[order] );
}


/*
==================
Cmd_Where_f
==================
*/
void Cmd_Where_f( gentity_t *ent ) {
	trap_SendServerCommand( ent-g_entities, va("print \"%s\n\"", vtos( ent->s.origin ) ) );
}

static const char *voteCommands[] = {
	"map_restart",
	"map",
	"rotate",
	"nextmap",
	"kick",
	"clientkick",
	"g_gametype",
	"g_unlagged",
	"g_warmup",
	"timelimit",
	"fraglimit",
	"capturelimit"
};


/*
==================
ValidVoteCommand

Input string can be modified by overwriting gametype number instead of text value, for example
==================
*/
static qboolean ValidVoteCommand( int clientNum, char *command ) 
{
	char buf[ MAX_CVAR_VALUE_STRING ];
	char *base;
	char *s;
	int	i;

	if ( strchr( command, ';' ) || strchr( command, '\n' ) || strchr( command, '\r' ) )
	{
		trap_SendServerCommand( clientNum, "print \"Invalid vote command.\n\"" );
		return qfalse;
	}

	base = command;
	
	s = buf; // extract command name
	while ( *command != '\0' && *command != ' ' ) {
		*s = *command; s++; command++;
	}
	*s = '\0';
	// point cmd on first argument
	while ( *command == ' ' || *command == '\t' )
		command++;

	for ( i = 0; i < ARRAY_LEN( voteCommands ); i++ ) {
		if ( !Q_stricmp( buf, voteCommands[i] ) ) {
			break;
		}
	}

	if ( i == ARRAY_LEN( voteCommands ) ) {
		trap_SendServerCommand( clientNum, "print \"Invalid vote command.\nVote commands are: \n"
			" g_gametype <n|ffa|duel|tdm|ctf>\n"
			" map_restart, map <mapname>, rotate [round], nextmap\n"
			" kick <player>, clientkick <clientnum>\n"
			" g_unlagged <0|1>, g_warmup <-1|0|seconds>\n"
			" timelimit <time>, fraglimit <frags>, capturelimit <captures>.\n\"" );
		return qfalse;
	}

	if ( Q_stricmp( buf, "g_gametype" ) == 0 )
	{
		if ( !Q_stricmp( command, "ffa" ) ) i = GT_FFA;
		else if ( !Q_stricmp( command, "duel" ) ) i = GT_TOURNAMENT;
		else if ( !Q_stricmp( command, "tdm" ) ) i = GT_TEAM;
		else if ( !Q_stricmp( command, "ctf" ) ) i = GT_CTF;
		else 
		{
			i = atoi( command );
			if( i == GT_SINGLE_PLAYER || i < GT_FFA || i >= GT_MAX_GAME_TYPE ) {
				trap_SendServerCommand( clientNum, va( "print \"Invalid gametype %i.\n\"", i ) );
				return qfalse;
			}
			return qfalse;
		}

		// handle string values
		BG_sprintf( base, "g_gametype %i", i );

		return qtrue;
	}

	if ( Q_stricmp( buf, "map" ) == 0 ) {
		if ( !G_MapExist( command ) ) {
			trap_SendServerCommand( clientNum, va( "print \"No such map on server: %s.\n\"", command ) );
			return qfalse;
		} 
		return qtrue;
	}

	if ( Q_stricmp( buf, "nextmap" ) == 0 ) {
		strcpy( base, "rotate" );
	}

	return qtrue;
}


/*
==================
Cmd_CallVote_f
==================
*/
void Cmd_CallVote_f( gentity_t *ent ) {
	int		i, n;
	char	arg[MAX_STRING_TOKENS], *argn[4];
	char	cmd[MAX_STRING_TOKENS], *s;

	if ( !g_allowVote.integer ) {
		trap_SendServerCommand( ent-g_entities, "print \"Voting not allowed here.\n\"" );
		return;
	}

	if ( level.voteTime ) {
		trap_SendServerCommand( ent-g_entities, "print \"A vote is already in progress.\n\"" );
		return;
	}

	// if there is still a vote to be executed
	if ( level.voteExecuteTime || level.restarted ) {
		trap_SendServerCommand( ent-g_entities, "print \"Previous vote command is waiting execution^1.^7\n\"" );
		return;
	}

	if ( ent->client->pers.voteCount >= MAX_VOTE_COUNT ) {
		trap_SendServerCommand( ent-g_entities, "print \"You have called the maximum number of votes.\n\"" );
		return;
	}
	if ( ent->client->sess.sessionTeam == TEAM_SPECTATOR ) {
		trap_SendServerCommand( ent-g_entities, "print \"Not allowed to call a vote as spectator.\n\"" );
		return;
	}

	// build command buffer
	arg[ 0 ] = '\0'; s = arg;
	for ( i = 1; i < trap_Argc(); i++ ) {
		if ( arg[ 0 ] )
			s = Q_stradd( s, " " );
		trap_Argv( i, cmd, sizeof( cmd ) );
		s = Q_stradd( s, cmd );
	}

	// split by ';' seperators
	n = Com_Split( arg, argn, ARRAY_LEN( argn ), ';' );
	if ( n == 0 || *argn[0] == '\0' ) 
		return; // empty callvote command?

	// validate all split commands
	for ( i = 0; i < n; i++ ) {
		// make sure it is a valid command to vote on
		if ( !ValidVoteCommand( ent - g_entities, argn[i] ) )
			return;
	}

	// rebuild command buffer
	cmd[0] = '\0';
	for ( s = cmd, i = 0; i < n; i++ ) {
		if ( cmd[0] )
			s = Q_stradd( s, ";" );
		s = Q_stradd( s, argn[ i ] );
	}

	Com_sprintf( level.voteString, sizeof( level.voteString ), cmd );
	Com_sprintf( level.voteDisplayString, sizeof( level.voteDisplayString ), "%s", level.voteString );

	trap_SendServerCommand( -1, va( "print \"%s called a vote(%s).\n\"", ent->client->pers.netname, cmd ) );

	// start the voting, the caller automatically votes yes
	level.voteTime = level.time;
	level.voteYes = 1;
	level.voteNo = 0;

	for ( i = 0 ; i < level.maxclients ; i++ ) {
		level.clients[i].ps.eFlags &= ~EF_VOTED;
		level.clients[i].pers.voted = 0;
	}

	ent->client->ps.eFlags |= EF_VOTED;
	ent->client->pers.voted = 1;

	ent->client->pers.voteCount++;

	trap_SetConfigstring( CS_VOTE_TIME, va("%i", level.voteTime ) );
	trap_SetConfigstring( CS_VOTE_STRING, level.voteDisplayString );	
	trap_SetConfigstring( CS_VOTE_YES, va("%i", level.voteYes ) );
	trap_SetConfigstring( CS_VOTE_NO, va("%i", level.voteNo ) );	
}


/*
==================
Cmd_Vote_f
==================
*/
static void Cmd_Vote_f( gentity_t *ent ) {
	char		msg[64];

	if ( !level.voteTime ) {
		trap_SendServerCommand( ent-g_entities, "print \"No vote in progress.\n\"" );
		return;
	}

	if ( ent->client->pers.voted != 0 ) {
		trap_SendServerCommand( ent-g_entities, "print \"Vote already cast.\n\"" );
		return;
	}

	if ( ent->client->sess.sessionTeam == TEAM_SPECTATOR ) {
		trap_SendServerCommand( ent-g_entities, "print \"Not allowed to vote as spectator.\n\"" );
		return;
	}

	trap_SendServerCommand( ent-g_entities, "print \"Vote cast.\n\"" );

	ent->client->ps.eFlags |= EF_VOTED;

	trap_Argv( 1, msg, sizeof( msg ) );

	if ( msg[0] == 'y' || msg[0] == 'Y' || msg[0] == '1' ) {
		level.voteYes++;
		ent->client->pers.voted = 1;
		trap_SetConfigstring( CS_VOTE_YES, va( "%i", level.voteYes ) );
	} else {
		level.voteNo++;
		ent->client->pers.voted = -1;
		trap_SetConfigstring( CS_VOTE_NO, va( "%i", level.voteNo ) );	
	}

	// a majority will be determined in CheckVote, which will also account
	// for players entering or leaving
}


void G_RevertVote( gclient_t *client ) {
	if ( level.voteTime ) {
		if ( client->pers.voted == 1 ) {
			level.voteYes--;
			client->pers.voted = 0;
			client->ps.eFlags &= ~EF_VOTED;
			trap_SetConfigstring( CS_VOTE_YES, va( "%i", level.voteYes ) );
		} else if ( client->pers.voted == -1 ) {
			level.voteNo--;
			client->pers.voted = 0;
			client->ps.eFlags &= ~EF_VOTED;
			trap_SetConfigstring( CS_VOTE_NO, va( "%i", level.voteNo ) );
		}
	}
	if ( client->sess.sessionTeam == TEAM_RED || client->sess.sessionTeam == TEAM_BLUE ) {
		int cs_offset;
		if ( client->sess.sessionTeam == TEAM_RED )
			cs_offset = 0;
		else
			cs_offset = 1;
		if ( client->pers.teamVoted == 1 ) {
			level.teamVoteYes[cs_offset]--;
			client->pers.teamVoted = 0;
			client->ps.eFlags &= ~EF_TEAMVOTED;
			trap_SetConfigstring( CS_TEAMVOTE_YES + cs_offset, va("%i", level.teamVoteYes[cs_offset] ) );
		} else if ( client->pers.teamVoted == -1 ) {
			level.teamVoteNo[cs_offset]--;
			client->pers.teamVoted = 0;
			client->ps.eFlags &= ~EF_TEAMVOTED;
			trap_SetConfigstring( CS_TEAMVOTE_NO + cs_offset, va("%i", level.teamVoteNo[cs_offset] ) );
		}
	} 
}


/*
==================
Cmd_CallTeamVote_f
==================
*/
static void Cmd_CallTeamVote_f( gentity_t *ent ) {
	int		i, team, cs_offset;
	char	arg1[MAX_STRING_TOKENS];
	char	arg2[MAX_STRING_TOKENS];

	team = ent->client->sess.sessionTeam;
	if ( team == TEAM_RED )
		cs_offset = 0;
	else if ( team == TEAM_BLUE )
		cs_offset = 1;
	else
		return;

	if ( !g_allowVote.integer ) {
		trap_SendServerCommand( ent-g_entities, "print \"Voting not allowed here.\n\"" );
		return;
	}

	if ( level.teamVoteTime[cs_offset] ) {
		trap_SendServerCommand( ent-g_entities, "print \"A team vote is already in progress.\n\"" );
		return;
	}
	if ( ent->client->pers.teamVoteCount >= MAX_VOTE_COUNT ) {
		trap_SendServerCommand( ent-g_entities, "print \"You have called the maximum number of team votes.\n\"" );
		return;
	}

	if ( level.voteExecuteTime || level.restarted ) {
		return;
	}

	if ( ent->client->sess.sessionTeam == TEAM_SPECTATOR ) {
		trap_SendServerCommand( ent-g_entities, "print \"Not allowed to call a vote as spectator.\n\"" );
		return;
	}

	// make sure it is a valid command to vote on
	trap_Argv( 1, arg1, sizeof( arg1 ) );
	arg2[0] = '\0';
	for ( i = 2; i < trap_Argc(); i++ ) {
		if (i > 2)
			strcat(arg2, " ");
		trap_Argv( i, &arg2[strlen(arg2)], sizeof( arg2 ) - (int)strlen(arg2) );
	}

	if( strchr( arg1, ';' ) || strchr( arg2, ';' ) || strchr( arg2, '\n' ) || strchr( arg2, '\r' ) ) {
		trap_SendServerCommand( ent-g_entities, "print \"Invalid vote string.\n\"" );
		return;
	}

	if ( !Q_stricmp( arg1, "leader" ) ) {
		char netname[MAX_NETNAME], leader[MAX_NETNAME];

		if ( !arg2[0] ) {
			i = ent->client->ps.clientNum;
		}
		else {
			// numeric values are just slot numbers
			for (i = 0; i < 3; i++) {
				if ( !arg2[i] || arg2[i] < '0' || arg2[i] > '9' )
					break;
			}
			if ( i >= 3 || !arg2[i]) {
				i = atoi( arg2 );
				if ( i < 0 || i >= level.maxclients ) {
					trap_SendServerCommand( ent-g_entities, va("print \"Bad client slot: %i\n\"", i) );
					return;
				}

				if ( !g_entities[i].inuse ) {
					trap_SendServerCommand( ent-g_entities, va("print \"Client %i is not active\n\"", i) );
					return;
				}
			}
			else {
				Q_strncpyz(leader, arg2, sizeof(leader));
				Q_CleanStr(leader);
				for ( i = 0 ; i < level.maxclients ; i++ ) {
					if ( level.clients[i].pers.connected == CON_DISCONNECTED )
						continue;
					if (level.clients[i].sess.sessionTeam != team)
						continue;
					Q_strncpyz(netname, level.clients[i].pers.netname, sizeof(netname));
					Q_CleanStr(netname);
					if ( !Q_stricmp(netname, leader) ) {
						break;
					}
				}
				if ( i >= level.maxclients ) {
					trap_SendServerCommand( ent-g_entities, va("print \"%s is not a valid player on your team.\n\"", arg2) );
					return;
				}
			}
		}
		Com_sprintf(arg2, sizeof(arg2), "%d", i);
	} else {
		trap_SendServerCommand( ent-g_entities, "print \"Invalid vote string.\n\"" );
		trap_SendServerCommand( ent-g_entities, "print \"Team vote commands are: leader <player>.\n\"" );
		return;
	}

	Com_sprintf( level.teamVoteString[cs_offset], sizeof( level.teamVoteString[cs_offset] ), "%s %s", arg1, arg2 );

	for ( i = 0 ; i < level.maxclients ; i++ ) {
		if ( level.clients[i].pers.connected == CON_DISCONNECTED )
			continue;
		if (level.clients[i].sess.sessionTeam == team)
			trap_SendServerCommand( i, va("print \"%s called a team vote.\n\"", ent->client->pers.netname ) );
	}

	// start the voting, the caller automatically votes yes
	level.teamVoteTime[cs_offset] = level.time;
	level.teamVoteYes[cs_offset] = 1;
	level.teamVoteNo[cs_offset] = 0;

	for ( i = 0 ; i < level.maxclients ; i++ ) {
		if ( level.clients[i].sess.sessionTeam == team ) {
			level.clients[i].ps.eFlags &= ~EF_TEAMVOTED;
			level.clients[i].pers.teamVoted = 0;
		}
	}
	ent->client->ps.eFlags |= EF_TEAMVOTED;
	ent->client->pers.teamVoted = 1;

	ent->client->pers.teamVoteCount++;

	trap_SetConfigstring( CS_TEAMVOTE_TIME + cs_offset, va("%i", level.teamVoteTime[cs_offset] ) );
	trap_SetConfigstring( CS_TEAMVOTE_STRING + cs_offset, level.teamVoteString[cs_offset] );
	trap_SetConfigstring( CS_TEAMVOTE_YES + cs_offset, va("%i", level.teamVoteYes[cs_offset] ) );
	trap_SetConfigstring( CS_TEAMVOTE_NO + cs_offset, va("%i", level.teamVoteNo[cs_offset] ) );
}


/*
==================
Cmd_TeamVote_f
==================
*/
static void Cmd_TeamVote_f( gentity_t *ent ) {
	int			team, cs_offset;
	char		msg[64];

	team = ent->client->sess.sessionTeam;
	if ( team == TEAM_RED )
		cs_offset = 0;
	else if ( team == TEAM_BLUE )
		cs_offset = 1;
	else
		return;

	if ( !level.teamVoteTime[cs_offset] ) {
		trap_SendServerCommand( ent-g_entities, "print \"No team vote in progress.\n\"" );
		return;
	}
	if ( ent->client->pers.teamVoted != 0 ) {
		trap_SendServerCommand( ent-g_entities, "print \"Team vote already cast.\n\"" );
		return;
	}
	if ( ent->client->sess.sessionTeam == TEAM_SPECTATOR ) {
		trap_SendServerCommand( ent-g_entities, "print \"Not allowed to vote as spectator.\n\"" );
		return;
	}

	trap_SendServerCommand( ent-g_entities, "print \"Team vote cast.\n\"" );

	ent->client->ps.eFlags |= EF_TEAMVOTED;
	ent->client->pers.teamVoteCount++;

	trap_Argv( 1, msg, sizeof( msg ) );

	if ( msg[0] == 'y' || msg[0] == 'Y' || msg[0] == '1' ) {
		level.teamVoteYes[cs_offset]++;
		trap_SetConfigstring( CS_TEAMVOTE_YES + cs_offset, va("%i", level.teamVoteYes[cs_offset] ) );
	} else {
		level.teamVoteNo[cs_offset]++;
		trap_SetConfigstring( CS_TEAMVOTE_NO + cs_offset, va("%i", level.teamVoteNo[cs_offset] ) );	
	}

	// a majority will be determined in TeamCheckVote, which will also account
	// for players entering or leaving
}


/*
=================
Cmd_SetViewpos_f
=================
*/
static void Cmd_SetViewpos_f( gentity_t *ent ) {
	vec3_t		origin, angles;
	char		buffer[MAX_TOKEN_CHARS];
	int			i;

	if ( !g_cheats.integer ) {
		trap_SendServerCommand( ent-g_entities, "print \"Cheats are not enabled on this server.\n\"");
		return;
	}
	if ( trap_Argc() != 5 ) {
		trap_SendServerCommand( ent-g_entities, "print \"usage: setviewpos x y z yaw\n\"");
		return;
	}

	VectorClear( angles );
	for ( i = 0 ; i < 3 ; i++ ) {
		trap_Argv( i + 1, buffer, sizeof( buffer ) );
		origin[i] = atof( buffer );
	}

	trap_Argv( 4, buffer, sizeof( buffer ) );
	angles[YAW] = atof( buffer );

	TeleportPlayer( ent, origin, angles );
}


gentity_t *dropWeapon( gentity_t *ent, gitem_t *item, float angle, int xr_flags );
gitem_t	*BG_FindItemForHealth( int amount );
gitem_t	*BG_FindItemForAmmo( weapon_t weapon );
gentity_t *ThrowWeapon( gentity_t *ent );


#ifdef USE_FLAG_DROP
void Cmd_DropFlag_f(gentity_t *ent) {
#ifdef USE_ADVANCED_ITEMS
  if(ent->client->inventory[PW_REDFLAG]) {
    dropWeapon( ent, BG_FindItemForPowerup(PW_REDFLAG), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
  } else if (ent->client->inventory[PW_BLUEFLAG]) {
    dropWeapon( ent, BG_FindItemForPowerup(PW_BLUEFLAG), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
#if defined(USE_ADVANCED_GAMES) || defined(USE_ADVANCED_TEAMS)
  } else if(ent->client->inventory[PW_GOLDFLAG]) {
    dropWeapon( ent, BG_FindItemForPowerup(PW_GOLDFLAG), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
  } else if (ent->client->inventory[PW_GREENFLAG]) {
    dropWeapon( ent, BG_FindItemForPowerup(PW_GREENFLAG), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
#endif
  } else if (ent->client->inventory[PW_NEUTRALFLAG]) {
    dropWeapon( ent, BG_FindItemForPowerup(PW_NEUTRALFLAG), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
  }
#if defined(USE_ADVANCED_GAMES) || defined(USE_ADVANCED_TEAMS)
  ent->client->inventory[PW_GREENFLAG] =
  ent->client->inventory[PW_GOLDFLAG] =
#endif
  ent->client->inventory[PW_REDFLAG] =
  ent->client->inventory[PW_BLUEFLAG] =
  ent->client->inventory[PW_NEUTRALFLAG] = 0;

#else
  if(ent->client->ps.powerups[PW_REDFLAG]) {
    dropWeapon( ent, BG_FindItemForPowerup(PW_REDFLAG), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
  } else if (ent->client->ps.powerups[PW_BLUEFLAG]) {
    dropWeapon( ent, BG_FindItemForPowerup(PW_BLUEFLAG), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
#if defined(USE_ADVANCED_GAMES) || defined(USE_ADVANCED_TEAMS)
  } else if(ent->client->ps.powerups[PW_GOLDFLAG]) {
    dropWeapon( ent, BG_FindItemForPowerup(PW_GOLDFLAG), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
  } else if (ent->client->ps.powerups[PW_GREENFLAG]) {
    dropWeapon( ent, BG_FindItemForPowerup(PW_GREENFLAG), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
#endif
  } else if (ent->client->ps.powerups[PW_NEUTRALFLAG]) {
    dropWeapon( ent, BG_FindItemForPowerup(PW_NEUTRALFLAG), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
  }
#if defined(USE_ADVANCED_GAMES) || defined(USE_ADVANCED_TEAMS)
  ent->client->ps.powerups[PW_GREENFLAG] =
  ent->client->ps.powerups[PW_GOLDFLAG] =
#endif
  ent->client->ps.powerups[PW_REDFLAG] =
  ent->client->ps.powerups[PW_BLUEFLAG] =
  ent->client->ps.powerups[PW_NEUTRALFLAG] = 0;
#endif
}
#endif



#ifdef USE_RUNES
void Cmd_DropRune_f(gentity_t *ent) {
	int i;
  int contents;
  contents = trap_PointContents( ent->r.currentOrigin, -1 );
  if (contents & CONTENTS_NODROP)
    return;

	for(i = RUNE_STRENGTH; i <= RUNE_LITHIUM; i++) {
		if(ent->client->inventory[i]) {
			dropWeapon( ent, BG_FindItemForRune(i), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
			ent->client->inventory[i] = 0;
			ent->client->inventoryModified[(int)floor(i / PW_MAX_POWERUPS)] = qtrue;
			return;
		}
	}
}
#endif


#ifdef USE_POWERUP_DROP
void Cmd_DropPowerup_f(gentity_t *ent) {
#ifdef MISSIONPACK
  // if there are persistant power-ups drop those
  if(ent->client->persistantPowerup) {
    TossClientPersistantPowerups(ent);
    return;
  } else
#endif
  {
    gentity_t	*drop;
    int i;
#ifdef USE_ADVANCED_ITEMS
    for ( i = 1 ; i < PW_NUM_POWERUPS ; i++ ) {
      if ( ent->client->inventory[ i ] > level.time ) {
        drop = dropWeapon( ent, BG_FindItemForPowerup( i ), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
        // decide how many seconds it has left
        drop->count = ( ent->client->inventory[i] - level.time ) / 1000;
        if ( drop->count < 1 ) {
          drop->count = 1;
        }
        // for pickup prediction
        drop->s.time2 = drop->count;
        ent->client->inventory[i] = 0;
        return;
      }
    }
#else
    for ( i = 1 ; i < MAX_POWERUPS ; i++ ) {
      if ( ent->client->ps.powerups[ i ] > level.time ) {
        drop = dropWeapon( ent, BG_FindItemForPowerup( i ), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
        // decide how many seconds it has left
        drop->count = ( ent->client->ps.powerups[i] - level.time ) / 1000;
        if ( drop->count < 1 ) {
          drop->count = 1;
        }
        // for pickup prediction
        drop->s.time2 = drop->count;
        ent->client->ps.powerups[i] = 0;
        return;
      }
    }
#endif
  }
}
#endif



#ifdef USE_ITEM_DROP
void Cmd_DropItem_f(gentity_t *ent) {
  // check if there are some holdable items to toss
#ifdef USE_ADVANCED_ITEMS
	int i;
	for(i = HI_TELEPORTER; i < HI_NUM_HOLDABLE; i++) {
		if(ent->client->inventory[i]) {
			dropWeapon( ent, &bg_itemlist[ent->client->inventory[i]], 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
			ent->client->inventory[i] = 0;
			return;
		}
	}
#else
  if(ent->client->ps.stats[STAT_HOLDABLE_ITEM]) {
    dropWeapon( ent, &bg_itemlist[ent->client->ps.stats[STAT_HOLDABLE_ITEM]], 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
    ent->client->ps.stats[STAT_HOLDABLE_ITEM] = 0;
    return;
  }
#endif
}
#endif


#ifdef USE_AMMO_DROP
void Cmd_DropAmmo_f(gentity_t *ent) {
  // drop ammo for current weapon, total / default pack size
  gitem_t *item;
  int i = ent->s.weapon;
#ifdef USE_ADVANCED_WEAPONS
	if(ent->client->classAmmo[i] == INFINITE)
		return;
  item = BG_FindItemForAmmo(i);
  if(floor(ent->client->classAmmo[i] / item->quantity) > 1) {
    dropWeapon( ent, item, 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
    ent->client->classAmmo[i] -= item->quantity;
    return;
  }
#else
	if(ent->client->ps.ammo[i] == INFINITE)
		return;
  item = BG_FindItemForAmmo(i);
  if(floor(ent->client->ps.ammo[i] / item->quantity) > 1) {
    dropWeapon( ent, item, 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
    ent->client->ps.ammo[i] -= item->quantity;
    return;
  }
#endif
}
#endif


#ifdef USE_HEALTH_DROP
void Cmd_DropHealth_f(gentity_t *ent) {
  gitem_t *item;
	// TODO: infinite version of health 999 like DOOM?
	if(ent->health == INFINITE)
		return;
	item = BG_FindItemForHealth(25);
	if(floor(ent->health / item->quantity) > 1) {
		dropWeapon( ent, item, 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
		ent->health -= item->quantity;
		return;
	}
}
#endif



#ifdef USE_WEAPON_DROP

/*
=================
Cmd_Drop_f XRAY FMJ
=================
*/
void Cmd_Drop_f( gentity_t *ent ) {
  gentity_t	*drop;
  int contents;
  contents = trap_PointContents( ent->r.currentOrigin, -1 );
	if (contents & CONTENTS_NODROP)
    return;

  if(!g_dropWeapon.integer)
    return;

  if(g_dropWeapon.integer == 1)
    ThrowWeapon( ent );

#ifdef USE_FLAG_DROP
#ifdef USE_ADVANCED_ITEMS
  if((g_dropWeapon.integer & 2)
    && (ent->client->inventory[PW_REDFLAG]
      || ent->client->inventory[PW_BLUEFLAG]
      || ent->client->inventory[PW_NEUTRALFLAG])) {
    if(ent->client->inventory[PW_REDFLAG]) {
      dropWeapon( ent, BG_FindItemForPowerup(PW_REDFLAG), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
    } else if (ent->client->inventory[PW_BLUEFLAG]) {
      dropWeapon( ent, BG_FindItemForPowerup(PW_BLUEFLAG), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
    } else if (ent->client->inventory[PW_NEUTRALFLAG]) {
      dropWeapon( ent, BG_FindItemForPowerup(PW_NEUTRALFLAG), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
    }
#ifdef USE_ADVANCED_GAMES
		else if (ent->client->inventory[PW_GREENFLAG]) {
      dropWeapon( ent, BG_FindItemForPowerup(PW_GREENFLAG), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
    } else if (ent->client->inventory[PW_GOLDFLAG]) {
      dropWeapon( ent, BG_FindItemForPowerup(PW_GOLDFLAG), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
    }
    ent->client->inventory[PW_GREENFLAG] =
    ent->client->inventory[PW_GREENFLAG] =
#endif
    ent->client->inventory[PW_REDFLAG] =
    ent->client->inventory[PW_BLUEFLAG] =
    ent->client->inventory[PW_NEUTRALFLAG] = 0;
    return;
  }
#else
  if((g_dropWeapon.integer & 2)
    && (ent->client->ps.powerups[PW_REDFLAG]
      || ent->client->ps.powerups[PW_BLUEFLAG]
      || ent->client->ps.powerups[PW_NEUTRALFLAG])) {
    if(ent->client->ps.powerups[PW_REDFLAG]) {
      dropWeapon( ent, BG_FindItemForPowerup(PW_REDFLAG), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
    } else if (ent->client->ps.powerups[PW_BLUEFLAG]) {
      dropWeapon( ent, BG_FindItemForPowerup(PW_BLUEFLAG), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
    } else if (ent->client->ps.powerups[PW_NEUTRALFLAG]) {
      dropWeapon( ent, BG_FindItemForPowerup(PW_NEUTRALFLAG), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
    }
#ifdef USE_ADVANCED_GAMES
		else if (ent->client->ps.powerups[PW_GREENFLAG]) {
      dropWeapon( ent, BG_FindItemForPowerup(PW_GREENFLAG), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
    } else if (ent->client->ps.powerups[PW_GOLDFLAG]) {
      dropWeapon( ent, BG_FindItemForPowerup(PW_GOLDFLAG), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
    }
    ent->client->ps.powerups[PW_GREENFLAG] =
    ent->client->ps.powerups[PW_GREENFLAG] =
#endif
    ent->client->ps.powerups[PW_REDFLAG] =
    ent->client->ps.powerups[PW_BLUEFLAG] =
    ent->client->ps.powerups[PW_NEUTRALFLAG] = 0;
    return;
  }
#endif
#endif

#ifdef USE_RUNES
  if((g_dropWeapon.integer & 8)) {
		int i;
		for(i = RUNE_STRENGTH; i <= RUNE_LITHIUM; i++) {
			if(ent->client->inventory[i]) {
				dropWeapon( ent, BG_FindItemForRune(i), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
				ent->client->inventory[i] = 0;
				ent->client->inventoryModified[(int)floor(i / PW_MAX_POWERUPS)] = qtrue;
				return;
			}
		}
	}
#endif
#ifdef USE_POWERUP_DROP
  if(g_dropWeapon.integer & 4) {
#ifdef MISSIONPACK
    // if there are persistant power-ups drop those
    if(ent->client->persistantPowerup) {
      TossClientPersistantPowerups(ent);
      return;
    } else
#endif
    {
      int i;
#ifdef USE_ADVANCED_ITEMS
      for ( i = 1 ; i < PW_NUM_POWERUPS ; i++ ) {
        if ( ent->client->inventory[i ] > level.time ) {
          drop = dropWeapon( ent, BG_FindItemForPowerup( i ), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
          // decide how many seconds it has left
          drop->count = ( ent->client->inventory[i] - level.time ) / 1000;
          if ( drop->count < 1 ) {
            drop->count = 1;
          }
          // for pickup prediction
          drop->s.time2 = drop->count;
          ent->client->inventory[i] = 0;
          return;
        }
      }
#else
      for ( i = 1 ; i < MAX_POWERUPS ; i++ ) {
        if ( ent->client->ps.powerups[i ] > level.time ) {
          drop = dropWeapon( ent, BG_FindItemForPowerup( i ), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
          // decide how many seconds it has left
          drop->count = ( ent->client->ps.powerups[i] - level.time ) / 1000;
          if ( drop->count < 1 ) {
            drop->count = 1;
          }
          // for pickup prediction
          drop->s.time2 = drop->count;
          ent->client->ps.powerups[i] = 0;
          return;
        }
      }
#endif
    }
  }
#endif
#ifdef USE_ITEM_DROP
  // check if there are some holdable items to toss
#ifdef USE_ADVANCED_ITEMS
	if(g_dropWeapon.integer & 16) {
		int i;
		for(i = HI_TELEPORTER; i < HI_NUM_HOLDABLE; i++) {
			if(ent->client->inventory[i]) {
				dropWeapon(ent, BG_FindItemForPowerup(i), 0, FL_DROPPED_ITEM | FL_THROWN_ITEM);
				ent->client->inventory[i] = 0;
				return;
			}
		}
	}
#else
  if(g_dropWeapon.integer & 16
    && ent->client->ps.stats[STAT_HOLDABLE_ITEM]) {
    dropWeapon( ent, &bg_itemlist[ent->client->ps.stats[STAT_HOLDABLE_ITEM]], 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
    ent->client->ps.stats[STAT_HOLDABLE_ITEM] = 0;
    return;
  }
#endif
#endif
#ifdef USE_AMMO_DROP
  // drop ammo for current weapon, total / default pack size
  if(g_dropWeapon.integer & 32) {
    gitem_t *item;
    int i = ent->s.weapon;
#ifdef USE_ADVANCED_WEAPONS
		if(ent->client->classAmmo[i] != -1 && ent->client->classAmmo[i] != INFINITE) {
			item = BG_FindItemForAmmo(i);
			if(floor(ent->client->classAmmo[i] / item->quantity) > 0) {
				dropWeapon( ent, item, 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
				ent->client->classAmmo[i] -= item->quantity;
				if(ent->client->classAmmo[i] == 0) {
					G_AddEvent( ent, EV_NOAMMO, 0 );
					ent->client->ps.weaponTime += 500;
				}
				return;
			}
		}
#else
		if(ent->client->ps.ammo[i] != -1 && ent->client->ps.ammo[i] != INFINITE) {
			item = BG_FindItemForAmmo(i);
			if(floor(ent->client->ps.ammo[i] / item->quantity) > 0) {
				dropWeapon( ent, item, 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
				ent->client->ps.ammo[i] -= item->quantity;
				if(ent->client->ps.ammo[i] == 0) {
					G_AddEvent( ent, EV_NOAMMO, 0 );
					ent->client->ps.weaponTime += 500;
				}
				return;
			}
		}
#endif
  }
#endif
  // TODO: fix weapon switch animation
  drop = ThrowWeapon( ent );
#ifdef USE_HEALTH_DROP
  if(!drop && g_dropWeapon.integer & 64) {
    gitem_t *item;
    item = BG_FindItemForHealth(25);
    if(floor(ent->health / item->quantity) > 1) {
      dropWeapon( ent, item, 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
      ent->health -= item->quantity;
      return;
    }
  }
#endif
}
#endif


#ifdef USE_BOUNCE_CMD
/*
=================
Cmd_RBounce_f
=================
*/
void Cmd_RBounce_f( gentity_t *ent ) {

	char *msg; // message to player

	if (ent->flags & FL_ROCKETBOUNCE) {
		msg = "Rocket Bounce OFF\n";
    ent->flags &= ~FL_ROCKETBOUNCE;
	} else {
	  msg = "Rocket Bounce ON\n";
    ent->flags |= FL_ROCKETBOUNCE;
  }
	trap_SendServerCommand( ent-g_entities, va("print \"%s\"", msg));
}
#endif


#ifdef USE_CLOAK_CMD
/*
=================
Cmd_Cloak_f
=================
*/
void Cmd_Cloak_f( gentity_t *ent ) {

	char *msg; // message to player

  
  if(!g_enableCloak.integer) {
    msg = "Cloaking not enabled\n";
	} else if (ent->flags & FL_CLOAK) {
		msg = "Cloaking OFF\n";
    ent->flags &= ~FL_CLOAK;
#ifdef USE_ADVANCED_ITEMS
		ent->client->inventory[PW_INVIS] = level.time;
#else
		ent->client->ps.powerups[PW_INVIS] = level.time;
#endif
		// Removes the invisible powerup from the player
	}        
	else {
		msg = "Cloaking ON\n";
    ent->flags |= FL_CLOAK;
#ifdef USE_ADVANCED_ITEMS
		ent->client->inventory[PW_INVIS] = level.time + 1000000000;
#else
		ent->client->ps.powerups[PW_INVIS] = level.time + 1000000000;
#endif
		// Gives the invisible powerup to the player
	}

	trap_SendServerCommand( ent-g_entities, va("print \"%s\"", msg));
}
#endif


#ifdef USE_GRAVITY_BOOTS
/*
=================
Cmd_Boots_f          function for turning boots on/off
=================
*/
void Cmd_Boots_f( gentity_t *ent ) {
  char *msg; // message to player

  if(!g_enableBoots.integer) {
    msg = "Gravity boots not enabled\n";
  } else if (ent->flags & FL_BOOTS) {
    msg = "Anti Gravity boots OFF\n";
    ent->flags &= ~FL_BOOTS;
  } else {
    msg = "Anti Gravity boots ON\n";
    ent->flags |= FL_BOOTS;
  }

  trap_SendServerCommand( ent-g_entities, va("print \"%s\"", msg));
}
#endif


#ifdef USE_LASER_SIGHT
// in g_weapon.c
void Laser_Gen( gentity_t *ent, int type );
#endif


/*
=================
Cmd_Stats_f
=================
*/
static void Cmd_Stats_f( gentity_t *ent ) {
/*
	int max, n, i;

	max = trap_AAS_PointReachabilityAreaIndex( NULL );

	n = 0;
	for ( i = 0; i < max; i++ ) {
		if ( ent->client->areabits[i >> 3] & (1 << (i & 7)) )
			n++;
	}

	//trap_SendServerCommand( ent-g_entities, va("print \"visited %d of %d areas\n\"", n, max));
	trap_SendServerCommand( ent-g_entities, va("print \"%d%% level coverage\n\"", n * 100 / max));
*/
}


#ifdef USE_RUNES
gitem_t	*BG_FindItemForRune( int r );

static void Cmd_Rune_f( gentity_t *ent ) {
  char		buffer[MAX_TOKEN_CHARS];
  vec3_t		dir, delta;
  int i, r;
  int v = random() * 4;
  gentity_t	*e;
  gitem_t *item;
  float nearestDist = 100000;
  float dist;
  vec3_t nearest;

  // select the item location nearest the player
  for (i = 0; i < level.num_entities; i++) {
    e = &g_entities[i];
    if(!e->inuse || e->client || !e->item) {
      continue;
    }
    VectorSubtract( e->s.origin, ent->s.pos.trBase, delta );
    dist = VectorLength( delta );
    if(dist < nearestDist && dist > 0) {
      VectorCopy(e->s.origin, nearest);
      nearestDist = dist;
    }
  }
  if(nearestDist == 100000) {
    Com_Printf("Error: couldn't find good spawn location\n");
  } else {
    Com_Printf("Launching rune: %f: %f, %f, %f\n", 
      nearestDist, nearest[0], nearest[1], nearest[2]);
  }
  nearest[2] += 4;
  if(v == 0)
    VectorSet(dir, .5, .5, 2.0);
  else if(v == 1)
    VectorSet(dir, -.5, .5, 2.0);
  else if(v == 2)
    VectorSet(dir, .5, -.5, 2.0);
  else
    VectorSet(dir, -.5, -.5, 2.0);
  VectorMA( nearest, 10, dir, nearest );
  VectorNormalize( dir );

  trap_Argv( 1, buffer, sizeof( buffer ) );
	r = atof( buffer );
  item = BG_FindItemForRune( r );
  if(!r || !item) {
    Com_Printf("Unknown rune: \"%s\"\n", buffer);
    return;
  }

  // pop the rune out of that location
  RegisterItem( item );
  e = LaunchItem( item, nearest, dir, FL_DROPPED_ITEM | FL_THROWN_ITEM );
  G_AddEvent( e, EV_ITEM_RESPAWN, 0 );
}
#endif




void Cmd_Spawn_f( gentity_t *ent ) {
	vec3_t	angles;
	vec3_t velocity;
	char	str[MAX_TOKEN_CHARS];
	char *stripped[MAX_QPATH];
	gentity_t	*dropped;

	if ( trap_Argc() < 2 ) {
		return;
	}
	
	trap_Argv( 1, str, sizeof( str ) );

	VectorCopy( ent->s.apos.trBase, angles );
	//angles[YAW] += 45;
	angles[PITCH] = 0;	// always forward

	AngleVectors( angles, velocity, NULL, NULL );
	VectorScale( velocity, 400, velocity );
	velocity[2] += 100 + crandom() * 50;
	

	dropped = G_Spawn();

	//dropped->r.bmodel = qfalse;
	dropped->s.eType = ET_GENERAL;
	dropped->s.modelindex = G_ModelIndex(str);
	COM_StripExtension(str, (char *)stripped, MAX_QPATH);
	dropped->s.modelindex2 = G_SkinIndex(va("%s_default.skin", stripped));

	// item scale-down
	dropped->s.time = level.time;
	dropped->physicsObject = qtrue;
	dropped->s.generic1 = 8;
	dropped->classname = G_NewString(str);
	VectorSet (dropped->r.mins, -ITEM_RADIUS, -ITEM_RADIUS, -ITEM_RADIUS);
	VectorSet (dropped->r.maxs, ITEM_RADIUS, ITEM_RADIUS, ITEM_RADIUS);
	dropped->r.contents = CONTENTS_TRIGGER;
	dropped->clipmask = MASK_SHOT;

	//dropped->s.legsAnim = 0; // firstFrame
	//dropped->s.torsoAnim = 0; // numFrames
	//dropped->s.generic1 |= 16; // repeatFrames
	//dropped->s.generic1 |= 32; // 10 instead of 15
	//dropped->s.generic1 |= 64; 
	

	G_SetOrigin( dropped, ent->s.pos.trBase );
	dropped->s.pos.trType = TR_GRAVITY;
	VectorCopy( velocity, dropped->s.pos.trDelta );
	SnapVector( dropped->s.pos.trDelta );			// save net bandwidth

	dropped->r.bmodel = qfalse;
	dropped->s.eFlags = EF_BOUNCE_HALF;
	dropped->think = G_FreeEntity;
	dropped->nextthink = level.time + DROPPED_TIME;

	dropped->flags = FL_DROPPED_ITEM; // FL_DROPPED_ITEM; // XRAY FMJ FL_THROWN_ITEM
	dropped->s.solid = qtrue;

	dropped->clipmask = MASK_SHOT; // XRAY FMJ
	dropped->s.pos.trTime = level.time - 100;	// move a bit on the very first frame
	//VectorScale( velocity, 20, dropped->s.pos.trDelta ); // 700
	//SnapVector( dropped->s.pos.trDelta );		// save net bandwidth
	dropped->physicsBounce = 0.5;

	trap_LinkEntity (dropped);

}





/*
=================
ClientCommand
=================
*/
void ClientCommand( int clientNum ) {
	gentity_t *ent;
	char	cmd[MAX_TOKEN_CHARS];

	ent = g_entities + clientNum;
	if ( !ent->client )
		return;

	trap_Argv( 0, cmd, sizeof( cmd ) );

	if ( ent->client->pers.connected != CON_CONNECTED ) {
		if ( ent->client->pers.connected == CON_CONNECTING && g_gametype.integer >= GT_TEAM ) {
			if ( Q_stricmp( cmd, "team" ) == 0 && !level.restarted ) {
				Cmd_Team_f( ent ); // early team override
			}
		}
		return;	// not fully in game yet
	}

	if (Q_stricmp (cmd, "say") == 0) {
		Cmd_Say_f (ent, SAY_ALL, qfalse);
		return;
	}
	if (Q_stricmp (cmd, "say_team") == 0) {
		Cmd_Say_f (ent, SAY_TEAM, qfalse);
		return;
	}
	if (Q_stricmp (cmd, "tell") == 0) {
		Cmd_Tell_f ( ent );
		return;
	}
#ifdef MISSIONPACK
	if (Q_stricmp (cmd, "vsay") == 0) {
		Cmd_Voice_f (ent, SAY_ALL, qfalse, qfalse);
		return;
	}
	if (Q_stricmp (cmd, "vsay_team") == 0) {
		Cmd_Voice_f (ent, SAY_TEAM, qfalse, qfalse);
		return;
	}
	if (Q_stricmp (cmd, "vtell") == 0) {
		Cmd_VoiceTell_f ( ent, qfalse );
		return;
	}
	if (Q_stricmp (cmd, "vosay") == 0) {
		Cmd_Voice_f (ent, SAY_ALL, qfalse, qtrue);
		return;
	}
	if (Q_stricmp (cmd, "vosay_team") == 0) {
		Cmd_Voice_f (ent, SAY_TEAM, qfalse, qtrue);
		return;
	}
	if (Q_stricmp (cmd, "votell") == 0) {
		Cmd_VoiceTell_f ( ent, qtrue );
		return;
	}
	if (Q_stricmp (cmd, "vtaunt") == 0) {
		Cmd_VoiceTaunt_f ( ent );
		return;
	}
#endif
	if (Q_stricmp (cmd, "score") == 0) {
		Cmd_Score_f (ent);
		return;
	}

	// ignore all other commands when at intermission
	if (level.intermissiontime) {
		Cmd_Say_f (ent, qfalse, qtrue);
		return;
	}

#ifdef USE_ADVANCED_WEAPONS
	// cycle classes just like we do with weapons but server side
	if (Q_stricmp (cmd, "prevclass") == 0 || Q_stricmp (cmd, "nextclass") == 0) {
		char		arg[MAX_TOKEN_CHARS];

		if ( trap_Argc () < 2 ) {
			return;
		}

		trap_Argv( 1, arg, sizeof( arg ) );
		if(ent->client->weaponClass != atoi(arg)) {
			ent->client->classChange = qtrue;
			ent->client->weaponClass = atoi(arg);
		}
	} else

#if 0
	if (Q_stricmp (cmd, "prevclass") == 0) {
		int i, j;
		int prevClass = floor(ent->client->ps.weapon / WP_MAX_WEAPONS);
		for(i = 0; i < WP_MAX_CLASSES; i++) {
			prevClass--;
			if(prevClass < 0) {
				prevClass = WP_MAX_CLASSES - 1;
			}
			for(j = 0; j < WP_MAX_WEAPONS; j++) {
				if(ent->client->classWeapons[prevClass * WP_MAX_WEAPONS + j] > 0) {
					break;
				}
			}
			if(j < WP_MAX_WEAPONS) {
				break;
			}
		}
		if(ent->client->weaponClass != prevClass) {
			ent->client->classChange = qtrue;
			ent->client->weaponClass = prevClass;
		}
	}
	else if (Q_stricmp (cmd, "nextclass") == 0) {
		int i, j;
		int nextClass = floor(ent->client->ps.weapon / WP_MAX_WEAPONS);
		for(i = 0; i < WP_MAX_CLASSES; i++) {
			nextClass++;
			if(nextClass >= WP_MAX_CLASSES) {
				nextClass = 0;
			}
			for(j = 0; j < WP_MAX_WEAPONS; j++) {
				if(ent->client->classWeapons[nextClass * WP_MAX_WEAPONS + j] > 0) {
					break;
				}
			}
			if(j < WP_MAX_WEAPONS) {
				break;
			}
		}
		if(ent->client->weaponClass != nextClass) {
			ent->client->classChange = qtrue;
			ent->client->weaponClass = nextClass;
		}
	}
	else
#endif
#endif

	if (Q_stricmp (cmd, "give") == 0)
		Cmd_Give_f (ent);
	else if (Q_stricmp (cmd, "god") == 0)
		Cmd_God_f (ent);
	else if (Q_stricmp (cmd, "notarget") == 0)
		Cmd_Notarget_f (ent);
	else if (Q_stricmp (cmd, "noclip") == 0)
		Cmd_Noclip_f (ent);
	else if (Q_stricmp (cmd, "kill") == 0)
		Cmd_Kill_f (ent);
	else if (Q_stricmp (cmd, "teamtask") == 0)
		Cmd_TeamTask_f (ent);
	else if (Q_stricmp (cmd, "levelshot") == 0)
		Cmd_LevelShot_f (ent);
	else if (Q_stricmp (cmd, "follow") == 0)
		Cmd_Follow_f (ent);
	else if (Q_stricmp (cmd, "follownext") == 0)
		Cmd_FollowCycle_f (ent, 1);
	else if (Q_stricmp (cmd, "followprev") == 0)
		Cmd_FollowCycle_f (ent, -1);
	else if (Q_stricmp (cmd, "team") == 0)
		Cmd_Team_f (ent);
	else if (Q_stricmp (cmd, "where") == 0)
		Cmd_Where_f (ent);
	else if (Q_stricmp (cmd, "callvote") == 0)
		Cmd_CallVote_f (ent);
	else if (Q_stricmp (cmd, "vote") == 0)
		Cmd_Vote_f (ent);
	else if (Q_stricmp (cmd, "callteamvote") == 0)
		Cmd_CallTeamVote_f (ent);
	else if (Q_stricmp (cmd, "teamvote") == 0)
		Cmd_TeamVote_f (ent);
	else if (Q_stricmp (cmd, "gc") == 0)
		Cmd_GameCommand_f( ent );
	else if (Q_stricmp (cmd, "setviewpos") == 0)
		Cmd_SetViewpos_f( ent );
#ifdef USE_WEAPON_DROP
  else if (Q_stricmp (cmd, "drop") == 0)  // XRAY FMJ
    Cmd_Drop_f( ent );
#endif
#ifdef USE_POWERUP_DROP
  else if (Q_stricmp (cmd, "droppowerup") == 0)
    Cmd_DropPowerup_f( ent );
#endif
#ifdef USE_FLAG_DROP
  else if (Q_stricmp (cmd, "dropflag") == 0)
    Cmd_DropFlag_f( ent );
#endif
#ifdef USE_ITEM_DROP
  else if (Q_stricmp (cmd, "dropitem") == 0)
    Cmd_DropItem_f( ent );
#endif
#ifdef USE_AMMO_DROP // for heavys
  else if (Q_stricmp (cmd, "dropammo") == 0)
    Cmd_DropAmmo_f( ent );
#endif
#ifdef USE_HEALTH_DROP // for medics
	else if (Q_stricmp (cmd, "drophealth") == 0)
		Cmd_DropHealth_f( ent );
#endif

#ifdef USE_BOUNCE_CMD
  else if (Q_stricmp (cmd, "rbounce") == 0)
    Cmd_RBounce_f( ent );
#endif
#ifdef USE_CLOAK_CMD
  else if (Q_stricmp (cmd, "cloak") == 0)
  	Cmd_Cloak_f( ent );
#endif
#ifdef USE_GRAVITY_BOOTS
  else if (Q_stricmp (cmd, "boots") == 0)
     Cmd_Boots_f( ent );
#endif
#ifdef USE_LASER_SIGHT
  else if (Q_stricmp (cmd, "laser") == 0)
		Laser_Gen( ent, 1 );//1=Laser, 2=Flashlight
	else if (Q_stricmp (cmd, "flashlight") == 0)
		Laser_Gen( ent, 2 );
#endif

#ifdef USE_RUNES
  else if (Q_stricmp (cmd, "rune") == 0)
    Cmd_Rune_f( ent );
  else if (Q_stricmp (cmd, "droprune") == 0)
    Cmd_DropRune_f( ent );
#endif

	else if (Q_stricmp (cmd, "spawn") == 0)
		Cmd_Spawn_f( ent );

	else if (Q_stricmp (cmd, "stats") == 0)
		Cmd_Stats_f( ent );
	else
		trap_SendServerCommand( clientNum, va( "print \"unknown cmd %s\n\"", cmd ) );
}
