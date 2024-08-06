// Copyright (C) 1999-2000 Id Software, Inc.
//

#include "g_local.h"


/*
===============
G_DamageFeedback

Called just before a snapshot is sent to the given player.
Totals up all damage and generates both the player_state_t
damage values to that client for pain blends and kicks, and
global pain sound events for all clients.
===============
*/
void P_DamageFeedback( gentity_t *player ) {
	gclient_t	*client;
	float	count;
	vec3_t	angles;

	client = player->client;
	if ( client->ps.pm_type == PM_DEAD ) {
		return;
	}

	// total points of damage shot at the player this frame
	count = client->damage_blood + client->damage_armor;
	if ( count == 0 ) {
		return;		// didn't take any damage
	}

	if ( count > 255 ) {
		count = 255;
	}

	// send the information to the client

	// world damage (falling, slime, etc) uses a special code
	// to make the blend blob centered instead of positional
	if ( client->damage_fromWorld ) {
		client->ps.damagePitch = 255;
		client->ps.damageYaw = 255;

		client->damage_fromWorld = qfalse;
	} else {
		vectoangles( client->damage_from, angles );
		client->ps.damagePitch = angles[PITCH]/360.0 * 256;
		client->ps.damageYaw = angles[YAW]/360.0 * 256;
	}

	// play an apropriate pain sound
	if ( (level.time > player->pain_debounce_time) && !(player->flags & FL_GODMODE) ) {
		player->pain_debounce_time = level.time + 700;
		G_AddEvent( player, EV_PAIN, player->health );
		client->ps.damageEvent++;
	}


	client->ps.damageCount = count;

	//
	// clear totals
	//
	client->damage_blood = 0;
	client->damage_armor = 0;
	client->damage_knockback = 0;
}



/*
=============
P_WorldEffects

Check for lava / slime contents and drowning
=============
*/
void P_WorldEffects( gentity_t *ent ) {
	qboolean	envirosuit;
	int			waterlevel;

	if ( ent->client->noclip ) {
		ent->client->airOutTime = level.time + 12000;	// don't need air
		return;
	}

	waterlevel = ent->waterlevel;

#ifdef USE_ADVANCED_ITEMS
	envirosuit = (ent->client->inventory[PW_BATTLESUIT] || ent->client->inventory[PW_GRAVITYSUIT] || ent->client->inventory[PW_SUPERMAN]);
#else
	envirosuit = ent->client->ps.powerups[PW_BATTLESUIT] > level.time;
#endif
#ifdef USE_RUNES
  envirosuit |= ent->client->inventory[RUNE_RESIST] || ent->client->inventory[RUNE_ENVIRO];
#endif

	//
	// check for drowning
	//
	if ( waterlevel == 3 ) {
		// envirosuit give air
		if ( envirosuit ) {
			ent->client->airOutTime = level.time + 10000;
		}

		// if out of air, start drowning
		if ( ent->client->airOutTime < level.time) {
			// drown!
			ent->client->airOutTime += 1000;
			if ( ent->health > 0 ) {
				// take more damage the longer underwater
				ent->damage += 2;
				if (ent->damage > 15)
					ent->damage = 15;

				// don't play a normal pain sound
				ent->pain_debounce_time = level.time + 200;

				G_Damage (ent, NULL, NULL, NULL, NULL, 
					ent->damage, DAMAGE_NO_ARMOR, MOD_WATER);
			}
		}
	} else {
		ent->client->airOutTime = level.time + 12000;
		ent->damage = 2;
	}

	//
	// check for sizzle damage (move to pmove?)
	//
	if (waterlevel && 
		(ent->watertype&(CONTENTS_LAVA|CONTENTS_SLIME)) ) {
		if (ent->health > 0
			&& ent->pain_debounce_time <= level.time	) {

			if ( envirosuit ) {
				G_AddEvent( ent, EV_POWERUP_BATTLESUIT, 0 );
			} else {
				if (ent->watertype & CONTENTS_LAVA) {
					G_Damage (ent, NULL, NULL, NULL, NULL, 
						30*waterlevel, 0, MOD_LAVA);
				}

				if (ent->watertype & CONTENTS_SLIME) {
					G_Damage (ent, NULL, NULL, NULL, NULL, 
						10*waterlevel, 0, MOD_SLIME);
				}
			}
		}
	}
}

void Pickup_Item (gentity_t *ent, gentity_t *other, trace_t *trace, int autoPickup);
void CalcMuzzlePointOrigin( const gentity_t *ent, vec3_t origin, const vec3_t forward, const vec3_t right, const vec3_t up, vec3_t muzzlePoint );

void G_SetEntityPointed(gentity_t *ent) {
	static vec3_t  range = { 40, 40, 52 };
	int i;
	int 	   num;
	int 	   touch[MAX_GENTITIES];
	gentity_t	   *hit;
	vec3_t		   mins;
	vec3_t		   maxs;
	trace_t 	   tr;
	vec3_t		   reach;
	vec3_t		   forward;
	vec3_t		   right;
	vec3_t		   up;
	vec3_t		   muzzle;
	vec3_t		   origin;

	AngleVectors (ent->client->ps.viewangles, forward, right, up);
	CalcMuzzlePointOrigin( ent, origin, forward, right, up, muzzle );

	VectorMA(muzzle, 128, forward, reach);

	trap_Trace(&tr, muzzle, NULL, NULL, reach, ent->s.number, MASK_SHOT | CONTENTS_TRIGGER);

	if (tr.entityNum != ENTITYNUM_NONE && tr.entityNum != ENTITYNUM_WORLD) {
		ent->client->ps.stats[STAT_ENTITY_POINTED] = tr.entityNum;
	} else {
		ent->client->ps.stats[STAT_ENTITY_POINTED] = 0;
	}

	VectorSubtract(reach, range, mins);
	VectorAdd(reach, range, maxs);

	num = trap_EntitiesInBox(mins, maxs, touch, MAX_GENTITIES);

	for (i = 0; i < num; i++) {

		hit = &g_entities[touch[i]];

		if (!hit->classname || !hit->use) {
			continue;
		}

		ent->client->ps.stats[STAT_ENTITY_POINTED] = touch[i];
		break;
	}
}

/**
 * G_Use
 *
 * Uses something
 */
void G_Use(gentity_t *ent) {

	static vec3_t  range = { 40, 40, 52 };

	int 	   i;
	int 	   num;
	int 	   touch[MAX_GENTITIES];
	gentity_t	   *hit;
	gentity_t	   *interfaceEnt;
	vec3_t		   mins;
	vec3_t		   maxs;
	qboolean	   anim  = qfalse;
	qboolean	   doingDoor = qfalse;
	trace_t 	   tr;
	vec3_t		   reach;
	gentity_t	   *other;
	vec3_t		   forward;
	vec3_t		   right;
	vec3_t		   up;
	vec3_t		   muzzle;
	vec3_t		   origin;

	// dokta8 - work out where player is and where they are facing
	AngleVectors (ent->client->ps.viewangles, forward, right, up);
	CalcMuzzlePointOrigin( ent, origin, forward, right, up, muzzle );

	// has to be a meter away from the dude
	VectorMA(muzzle, 64, forward, reach);

	// dokta8 - Do a trace from player's muzzle to the object they are in front of
	trap_Trace(&tr, muzzle, NULL, NULL, reach, ent->s.number, MASK_SHOT | CONTENTS_TRIGGER);
	other = &g_entities[ tr.entityNum ];	//	dokta8 - get the first object in front of the player

	if (other) {

		if (other->item && (other->item->giType == IT_WEAPON || other->item->giType == IT_TEAM || other->item->giType == IT_HOLDABLE)) {
			//@Fenix - Fix cg_autoPickup 0 bug #392
			Pickup_Item(other, ent, &tr, -1);
			return;
		}

		if (other->classname) {
			if (!Q_stricmp(other->classname, "func_door")) {
				doingDoor = qtrue;
			}
		}
	}

	VectorSubtract(ent->client->ps.origin, range, mins);
	VectorAdd(ent->client->ps.origin, range, maxs);

	num = trap_EntitiesInBox(mins, maxs, touch, MAX_GENTITIES);

	for (i = 0; i < num; i++) {

		hit = &g_entities[touch[i]];

		if (!hit->classname || !hit->use) {
			continue;
		}

		if (!Q_stricmp(hit->classname, "func_button")) {
			//Press a button
			hit->use(hit, hit, ent);
		}
		else if (!Q_stricmp(hit->classname, "func_door")) {
			//Trigger_only is a flag set by the mapper
			//it prevents doors being opened directly by a player
			//ie: they have to use a button or another trigger
			if ((hit->mover->moverState != MOVER_1TO2) && (!hit->mover->trigger_only)) {
				hit->use(hit, hit, ent);
				anim = qtrue;
			}
		}
		else if (!Q_stricmp(hit->classname, "func_rotating_door") || !Q_stricmp(hit->classname, "func_door_rotating")) {
			if (!hit->mover->trigger_only) {
				hit->use(hit, hit, ent);
				anim = qtrue;
			}
		}
		else if (!Q_stricmp(hit->classname, "func_keyboard_interface") && !doingDoor) {
			hit->use(hit, hit, ent);
		}
		else if (!Q_stricmp(hit->classname, "func_train") && !doingDoor && hit->interfaceEnt) {
			if(hit->interfaceEnt){
				if ((interfaceEnt = G_Find (NULL, FOFS(targetname), hit->interfaceEnt)) != NULL
				 && interfaceEnt->use) {
					interfaceEnt->use(interfaceEnt, interfaceEnt, ent);
				}
			}
		}
	}

	//Run "use" animation but only if a high priority anim is not already running
	if (anim && (ent->client->ps.torsoTimer <= 0)) {
		ent->client->ps.torsoAnim  = TORSO_GESTURE; // TODO: TORSO_USE
		ent->client->ps.torsoTimer = 1500;
	}
}

/*
===============
G_SetClientSound
===============
*/
void G_SetClientSound( gentity_t *ent ) {
#ifdef MISSIONPACK
	if( ent->s.eFlags & EF_TICKING ) {
		ent->client->ps.loopSound = G_SoundIndex( "sound/weapons/proxmine/wstbtick.wav");
	}
	else
#endif
	if (ent->waterlevel && (ent->watertype&(CONTENTS_LAVA|CONTENTS_SLIME)) ) {
		ent->client->ps.loopSound = level.snd_fry;
	} else {
		ent->client->ps.loopSound = 0;
	}
}



//==============================================================

/*
==============
ClientImpacts
==============
*/
void ClientImpacts( gentity_t *ent, pmove_t *pm ) {
	int		i, j;
	trace_t	trace;
	gentity_t	*other;

	memset( &trace, 0, sizeof( trace ) );
	for (i=0 ; i<pm->numtouch ; i++) {
		for (j=0 ; j<i ; j++) {
			if (pm->touchents[j] == pm->touchents[i] ) {
				break;
			}
		}
		if (j != i) {
			continue;	// duplicated
		}
		other = &g_entities[ pm->touchents[i] ];

		if ( ( ent->r.svFlags & SVF_BOT ) && ( ent->touch ) ) {
			ent->touch( ent, other, &trace );
		}

		if ( !other->touch ) {
			continue;
		}

		other->touch( other, ent, &trace );
	}

}

#ifdef USE_PORTALS
/*
============
G_ListPortals

Find all personal portals so they don't affect Pmove physics negatively
============
*/
void	G_ListPortals( gentity_t *ent, vec3_t *sources, vec3_t *destinations
	, vec3_t *sourcesAngles, vec3_t *destinationsAngles ) {
	int			i, num;
	int			touch[MAX_GENTITIES];
	gentity_t	*hit;
	vec3_t		mins, maxs;
	int         count = 0;
  //vec3_t    velocity;
	static vec3_t	range = { 80, 80, 104 };

	if ( !ent->client ) {
		return;
	}

	// dead clients don't activate triggers!
	if ( ent->client->ps.stats[STAT_HEALTH] <= 0 ) {
		return;
	}

	VectorSubtract( ent->client->ps.origin, range, mins );
	VectorAdd( ent->client->ps.origin, range, maxs );
  //VectorCopy(ent->client->ps.velocity, velocity);
  //VectorScale( velocity, 52, velocity );
  //VectorSubtract( mins, velocity, mins );
  //VectorSubtract( maxs, velocity, maxs );

	num = trap_EntitiesInBox( mins, maxs, touch, MAX_GENTITIES );

	// can't use ent->absmin, because that has a one unit pad
	VectorAdd( ent->client->ps.origin, ent->r.mins, mins );
	VectorAdd( ent->client->ps.origin, ent->r.maxs, maxs );

	for ( i=0 ; i<num ; i++ ) {
		hit = &g_entities[touch[i]];

		if ( !hit->touch && !ent->touch ) {
			continue;
		}
		if ( !( hit->r.contents & CONTENTS_TRIGGER ) ) {
			continue;
		}

		if ( hit->s.eType != ET_TELEPORT_TRIGGER ) {
			continue;
		}

		if ( !trap_EntityContact( mins, maxs, hit ) ) {
			continue;
		}

		//pm->
		if( hit->pos1[0] || hit->pos1[1] || hit->pos1[2] ) {
			gentity_t *destination;
			gclient_t *client = &level.clients[hit->r.ownerNum];
			if(hit == client->portalSource) {
				destination = client->portalDestination;
			} else {
				destination = client->portalSource;
			}

			if(destination->s.eventParm) {
				vec3_t angles;
				ByteToDir( destination->s.eventParm, angles );
				vectoangles( angles, angles );
				if(hit->s.eventParm) {
					vec3_t angles2;
					ByteToDir( hit->s.eventParm, angles2 );
					vectoangles( angles2, angles2 );
					VectorCopy(hit->r.currentOrigin, sources[count]);
					VectorCopy(angles2, sourcesAngles[count]);
					VectorCopy(hit->pos1, destinations[count]);
					VectorCopy(angles, destinationsAngles[count]);
				} else {
					VectorCopy(hit->r.currentOrigin, sources[count]);
					VectorCopy(vec3_origin, sourcesAngles[count]);
					VectorCopy(hit->pos1, destinations[count]);
					VectorCopy(angles, destinationsAngles[count]);
				}
			} else {
				if(hit->s.eventParm) {
					vec3_t angles2;
					ByteToDir( hit->s.eventParm, angles2 );
					vectoangles( angles2, angles2 );
					VectorCopy(hit->r.currentOrigin, sources[count]);
					VectorCopy(angles2, sourcesAngles[count]);
					VectorCopy(hit->pos1, destinations[count]);
					VectorCopy(vec3_origin, destinationsAngles[count]);
				} else {
					VectorCopy(hit->r.currentOrigin, sources[count]);
					VectorCopy(vec3_origin, sourcesAngles[count]);
					VectorCopy(hit->pos1, destinations[count]);
					VectorCopy(vec3_origin, destinationsAngles[count]);
				}
			}

			count++;
		}
	}
	VectorCopy(vec3_origin, sources[count]);
	VectorCopy(vec3_origin, destinations[count]);
	VectorCopy(vec3_origin, sourcesAngles[count]);
	VectorCopy(vec3_origin, destinationsAngles[count]);
	//Com_Printf("%i portals detected\n", count);
}
#endif

/*
============
G_TouchTriggers

Find all trigger entities that ent's current position touches.
Spectators will only interact with teleporters.
============
*/
void	G_TouchTriggers( gentity_t *ent ) {
	int			i, num;
	int			touch[MAX_GENTITIES];
	gentity_t	*hit;
	trace_t		trace;
	vec3_t		mins, maxs;
	static vec3_t	range = { 40, 40, 52 };

	if ( !ent->client ) {
		return;
	}

	// dead clients don't activate triggers!
	if ( ent->client->ps.stats[STAT_HEALTH] <= 0 ) {
		return;
	}

	VectorSubtract( ent->client->ps.origin, range, mins );
	VectorAdd( ent->client->ps.origin, range, maxs );

	num = trap_EntitiesInBox( mins, maxs, touch, MAX_GENTITIES );

	// can't use ent->absmin, because that has a one unit pad
	VectorAdd( ent->client->ps.origin, ent->r.mins, mins );
	VectorAdd( ent->client->ps.origin, ent->r.maxs, maxs );

	for ( i=0 ; i<num ; i++ ) {
		hit = &g_entities[touch[i]];

		if ( !hit->touch && !ent->touch ) {
			continue;
		}
		if ( !( hit->r.contents & CONTENTS_TRIGGER ) ) {
			continue;
		}

		// ignore most entities if a spectator
		if ( ent->client->sess.sessionTeam == TEAM_SPECTATOR ) {
			if ( hit->s.eType != ET_TELEPORT_TRIGGER &&
				// this is ugly but adding a new ET_? type will
				// most likely cause network incompatibilities
				hit->touch != Touch_DoorTrigger) {
				continue;
			}
		}

		// use seperate code for determining if an item is picked up
		// so you don't have to actually contact its bounding box
		if ( hit->s.eType == ET_ITEM ) {
			if ( !BG_PlayerTouchesItem( &ent->client->ps, &hit->s, level.time ) ) {
				continue;
			}
		} else {
			if ( !trap_EntityContact( mins, maxs, hit ) ) {
				continue;
			}
		}

		memset( &trace, 0, sizeof(trace) );

		if ( hit->touch ) {
			hit->touch (hit, ent, &trace);
		}

		if ( ( ent->r.svFlags & SVF_BOT ) && ( ent->touch ) ) {
			ent->touch( ent, hit, &trace );
		}
	}

	// if we didn't touch a jump pad this pmove frame
	if ( ent->client->ps.jumppad_frame != ent->client->ps.pmove_framecount ) {
		ent->client->ps.jumppad_frame = 0;
		ent->client->ps.jumppad_ent = 0;
	}
}

/*
=================
SpectatorThink
=================
*/
void SpectatorThink( gentity_t *ent, usercmd_t *ucmd ) {
	pmove_t	pm;
	gclient_t	*client;

	client = ent->client;

	if ( client->sess.spectatorState != SPECTATOR_FOLLOW ) {
#ifdef USE_BIRDS_EYE
		if (client->pers.thirdPerson || g_thirdPerson.integer) {
			client->ps.pm_type = PM_THIRDPERSON;
		} else if (client->pers.birdsEye || g_birdsEye.integer) {
			if(client->pers.showCursor) {
				client->ps.pm_type = PM_FOLLOWCURSOR;
			} else {
				client->ps.pm_type = PM_BIRDSEYE;
			}
		} else if (client->pers.sideView || g_sideview.integer) {
			client->ps.pm_type = PM_PLATFORM;
		} else
#endif
#ifdef USE_AIW
		if(client->pers.reverseControls) {
			client->ps.pm_type = PM_REVERSED;
		} else
		if(client->pers.upsidedown || g_upsideDown.integer) {
			client->ps.pm_type = PM_UPSIDEDOWN;
		} else
		if(client->pers.reverseControls && (client->pers.upsidedown || g_upsideDown.integer)) {
			client->ps.pm_type = PM_REVERSEDUPSIDEDOWN;
		} else
#endif
		client->ps.pm_type = PM_SPECTATOR;
		client->ps.speed = g_speed.value * 1.25f; // faster than normal

		// set up for pmove
		memset( &pm, 0, sizeof( pm ) );
		pm.ps = &client->ps;
#ifdef USE_ADVANCED_ITEMS
		// spectators don't have inventory?
		//memcpy(pm.inventory, client->inventory, sizeof(client->inventory));
#endif
		pm.cmd = *ucmd;
		if ( client->noclip )
			pm.tracemask = 0;
		else
			pm.tracemask = MASK_PLAYERSOLID & ~CONTENTS_BODY;	// spectators can fly through bodies
		pm.trace = trap_Trace;
		pm.pointcontents = trap_PointContents;

		// perform a pmove
		Pmove( &pm );
		// save results of pmove
		VectorCopy( client->ps.origin, ent->s.origin );

		G_TouchTriggers( ent );
		trap_UnlinkEntity( ent );
	}

	client->oldbuttons = client->buttons;
	client->buttons = ucmd->buttons;

	// attack button cycles through spectators
	if ( ( client->buttons & BUTTON_ATTACK ) && ! ( client->oldbuttons & BUTTON_ATTACK ) ) {
		Cmd_FollowCycle_f( ent, 1 );
	}
}



/*
=================
ClientInactivityTimer

Returns qfalse if the client is dropped
=================
*/
qboolean ClientInactivityTimer( gclient_t *client ) {
	if ( ! g_inactivity.integer ) {
		// give everyone some time, so if the operator sets g_inactivity during
		// gameplay, everyone isn't kicked
		client->inactivityTime = level.time + 60 * 1000;
		client->inactivityWarning = qfalse;
	} else if ( client->pers.cmd.forwardmove || 
		client->pers.cmd.rightmove || 
		client->pers.cmd.upmove ||
		(client->pers.cmd.buttons & BUTTON_ATTACK) ) {
		client->inactivityTime = level.time + g_inactivity.integer * 1000;
		client->inactivityWarning = qfalse;
	} else if ( !client->pers.localClient ) {
		if ( level.time > client->inactivityTime ) {
			trap_DropClient( client - level.clients, "Dropped due to inactivity" );
			return qfalse;
		}
		if ( level.time > client->inactivityTime - 10000 && !client->inactivityWarning ) {
			client->inactivityWarning = qtrue;
			trap_SendServerCommand( client - level.clients, "cp \"Ten seconds until inactivity drop!\n\"" );
		}
	}
	return qtrue;
}


void G_GiveItem(gentity_t *ent, powerup_t pw);


/*
==================
ClientTimerActions

Actions that happen once a second
==================
*/
void ClientTimerActions( gentity_t *ent, int msec ) {
	gclient_t	*client;
#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS)
	int			maxHealth;
#endif

	client = ent->client;
	client->timeResidual += msec;

	while ( client->timeResidual >= 1000 ) {
		client->timeResidual -= 1000;

		// regenerate
#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS)
		if( bg_itemlist[client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_GUARD ) {
			maxHealth = client->ps.stats[STAT_MAX_HEALTH] / 2;
		}
#ifdef USE_RUNES
    else if ( ent->client->inventory[RUNE_REGEN] || ent->client->inventory[RUNE_HEALTH] 
				|| (ent->client->inventory[RUNE_REQUIEM] && ent->client->requiemGrab == IT_HEALTH && level.time - ent->client->requiemTime <= 1500)
		) {
      maxHealth = client->ps.stats[STAT_MAX_HEALTH];
    }
#endif
#ifdef USE_ADVANCED_ITEMS
		else if ( client->inventory[PW_REGEN]
			|| client->inventory[PW_SUPERMAN] // obviously because he's healed by sun
		){
			maxHealth = client->ps.stats[STAT_MAX_HEALTH];
		}
#else
		else if ( client->ps.powerups[PW_REGEN] ) {
			maxHealth = client->ps.stats[STAT_MAX_HEALTH];
		}
#endif
		else {
			maxHealth = 0;
		}
		if( maxHealth ) {
			if ( ent->health < maxHealth ) {
				ent->health += 15;
				if ( ent->health > maxHealth * 1.1 ) {
					ent->health = maxHealth * 1.1;
				}
				G_AddEvent( ent, EV_POWERUP_REGEN, 0 );
			} else 
			if ( ent->health < maxHealth * 2
#ifdef USE_RUNES
				// don't over maximize health, but do regenerate
				&& !ent->client->inventory[RUNE_HEALTH]
#endif
			) {
				ent->health += 5;
				if ( ent->health > maxHealth * 2 ) {
					ent->health = maxHealth * 2;
				}
				G_AddEvent( ent, EV_POWERUP_REGEN, 0 );
			}
#else
		if ( ent->client->ps.powerups[PW_REGEN] ) {
			if ( ent->health < client->ps.stats[STAT_MAX_HEALTH]) {
				ent->health += 15;
				if ( ent->health > client->ps.stats[STAT_MAX_HEALTH] * 1.1 ) {
					ent->health = client->ps.stats[STAT_MAX_HEALTH] * 1.1;
				}
				G_AddEvent( ent, EV_POWERUP_REGEN, 0 );
			} else if ( ent->health < client->ps.stats[STAT_MAX_HEALTH] * 2) {
				ent->health += 5;
				if ( ent->health > client->ps.stats[STAT_MAX_HEALTH] * 2 ) {
					ent->health = client->ps.stats[STAT_MAX_HEALTH] * 2;
				}
				G_AddEvent( ent, EV_POWERUP_REGEN, 0 );
			}
#endif
		} else {
			// count down health when over max
#ifdef USE_GAME_FREEZETAG
			if(!g_freezeTag.integer || ent->health != INFINITE) {
#endif
#ifdef USE_CLOAK_CMD
      if (ent->flags & FL_CLOAK) {
        // count down health when cloaked.
      	ent->health--;
      	if ( ent->health < 11) {
      		ent->flags ^= FL_CLOAK;
#ifdef USE_ADVANCED_ITEMS
      		ent->client->inventory[PW_INVIS] = level.time;
#else
      		ent->client->ps.powerups[PW_INVIS] = level.time;
#endif
      	}
      } else
#endif
			if ( ent->health > client->ps.stats[STAT_MAX_HEALTH] ) {
				ent->health--;
			}
#ifdef USE_GAME_FREEZETAG
			}
#endif
		}

// i had a friend Dan in college that added this feature to the half life 2 engine, our plan was to compile target for playstation leaked sdk
#if defined(USE_RPG_STATS) || defined(USE_ADVANCED_CLASS) || defined(USE_RUNES)
		if(!( client->pers.cmd.buttons & BUTTON_WALKING )
			&& (client->pers.cmd.forwardmove != 0 || client->pers.cmd.rightmove != 0 || client->pers.cmd.upmove > 0)
			&& client->ps.stats[STAT_STAMINA] > 0) {
			client->ps.stats[STAT_STAMINA] -= 10;
		} else if (client->ps.stats[STAT_STAMINA] < 100) {
			client->ps.stats[STAT_STAMINA] += 10;
		}

		if(g_ability.integer > 0) {
				
			if (client->ps.stats[STAT_ABILITY] < g_ability.value) {
				if(client->pers.playerclass == PCLASS_RANGER && !client->inventory[HI_TELEPORTER]) {
					client->ps.stats[STAT_ABILITY]++;
				}
				if(client->pers.playerclass == PCLASS_VISOR) {
					client->ps.stats[STAT_ABILITY]++;
				}
			}

			if(client->ps.stats[STAT_ABILITY] >= g_ability.value) {
				if(client->pers.playerclass == PCLASS_RANGER && !client->inventory[HI_TELEPORTER]) {
					G_GiveItem(ent, HI_TELEPORTER);
					client->ps.stats[STAT_ABILITY] = 0;
				}
			}
		}
#endif

#ifdef USE_RUNES

		if((client->inventory[RUNE_ELECTRIC] && client->ps.ammo[WP_LIGHTNING] < 50)) {
			client->ps.ammo[WP_LIGHTNING]++;
		}

		if (client->ps.stats[STAT_ABILITY] < rune_ability.value) {
			if((client->inventory[RUNE_HEALTH] && !client->inventory[HI_MEDKIT])
				|| (client->inventory[RUNE_DIVINE] && !client->inventory[HI_KAMIKAZE])) {
				client->ps.stats[STAT_ABILITY]++;
			}
		}

		if(client->ps.stats[STAT_ABILITY] >= rune_ability.value) {
			if(client->inventory[RUNE_HEALTH] && !client->inventory[HI_MEDKIT]) {
				G_GiveItem(ent, HI_MEDKIT);
			}
			if(client->inventory[RUNE_DIVINE] && !client->inventory[HI_KAMIKAZE]) {
				G_GiveItem(ent, HI_KAMIKAZE);
			}
		}

		if (client->ps.stats[STAT_ABILITY] < rune_abilityMin.value) {
			if((client->inventory[RUNE_SHIELD] && !client->inventory[HI_INVULNERABILITY])
				|| (client->inventory[RUNE_RECALL] && !client->inventory[HI_TELEPORTER])
				|| (client->inventory[RUNE_GRAPPLE] && client->ps.ammo[WP_GRAPPLING_HOOK] < 100)
				|| (client->inventory[RUNE_TORNADO])
			) {
				client->ps.stats[STAT_ABILITY]++;
			}
		}

		if(client->ps.stats[STAT_ABILITY] >= rune_abilityMin.value) {
			if(client->inventory[RUNE_SHIELD] && !client->inventory[HI_INVULNERABILITY]) {
				G_GiveItem(ent, HI_INVULNERABILITY);
			} else 
			if(client->inventory[RUNE_RECALL] && !client->inventory[HI_PORTAL]) {
				G_GiveItem(ent, HI_PORTAL);
			}
			if(client->inventory[RUNE_GRAPPLE] && client->ps.ammo[WP_GRAPPLING_HOOK] < 100) {
				client->ps.ammo[WP_GRAPPLING_HOOK] = 100;
			}
		}

    if(ent->client->inventory[RUNE_IMPACT]) {
      gentity_t	*other;
	    int			entityList[MAX_GENTITIES];
    	int			numListedEntities, e;
      vec3_t		mins, maxs, dir, origin;
      vec3_t bounding = {50, 50, 50};
      ent->client->ps.ammo[WP_LIGHTNING] -= 5;
      VectorCopy(ent->s.origin, mins);
      VectorCopy(ent->s.origin, maxs);
      VectorSubtract(mins, bounding, mins);
      VectorAdd(maxs, bounding, maxs);
      numListedEntities = trap_EntitiesInBox( mins, maxs, entityList, MAX_GENTITIES );
      for ( e = 0 ; e < numListedEntities ; e++ ) {
        other = &g_entities[entityList[ e ]];

        if (!ent->takedamage) {
          continue;
        }

        VectorSubtract (other->r.currentOrigin, ent->s.origin, dir);
        dir[2] += 24;
        G_Damage( other, NULL, ent, dir, origin, 10000, DAMAGE_RADIUS|DAMAGE_NO_TEAM_PROTECTION, MOD_LV_DISCHARGE );
      }
      // TODO: add event that makes a radius of random lighting bolts like the hammer weapon
    }
#endif

		// count down armor when over max
		if ( client->ps.stats[STAT_ARMOR] > client->ps.stats[STAT_MAX_HEALTH] ) {
			client->ps.stats[STAT_ARMOR]--;
		}
	
#ifdef USE_RUNES
		else if ( ent->client->inventory[RUNE_ARMOR] || ent->client->inventory[RUNE_REGEN]
			|| (ent->client->inventory[RUNE_REQUIEM] && ent->client->requiemGrab == IT_ARMOR && level.time - ent->client->requiemTime <= 1500) 
		) {
			if ( client->ps.stats[STAT_ARMOR] + 5 <= client->ps.stats[STAT_MAX_HEALTH] ) {
				client->ps.stats[STAT_ARMOR] += 5;
				G_AddEvent( ent, EV_POWERUP_REGEN, 0 );
			}
		}
#endif

	}



#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS) || defined(USE_ADVANCED_CLASS) || defined(USE_RUNES)
	if( bg_itemlist[client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_AMMOREGEN 
#ifdef USE_RUNES
		|| ent->client->inventory[RUNE_ACTION] 
		|| (ent->client->inventory[RUNE_REQUIEM] && ent->client->requiemGrab == IT_AMMO && level.time - ent->client->requiemTime <= 1500) 
#endif
	) {
		int w, max, inc, t, i;
    int weapList[]={WP_MACHINEGUN,WP_SHOTGUN,WP_GRENADE_LAUNCHER,WP_ROCKET_LAUNCHER,WP_LIGHTNING,WP_RAILGUN,WP_PLASMAGUN,WP_BFG,WP_NAILGUN,WP_PROX_LAUNCHER,WP_CHAINGUN};
    int weapCount = ARRAY_LEN( weapList );
		//
    for (i = 0; i < weapCount; i++) {
		  w = weapList[i];

		  switch(w) {
			  case WP_MACHINEGUN: max = 50; inc = 4; t = 1000; break;
			  case WP_SHOTGUN: max = 10; inc = 1; t = 1500; break;
			  case WP_GRENADE_LAUNCHER: max = 10; inc = 1; t = 2000; break;
			  case WP_ROCKET_LAUNCHER: max = 10; inc = 1; t = 1750; break;
			  case WP_LIGHTNING: max = 50; inc = 5; t = 1500; break;
			  case WP_RAILGUN: max = 10; inc = 1; t = 1750; break;
			  case WP_PLASMAGUN: max = 50; inc = 5; t = 1500; break;
			  case WP_BFG: max = 10; inc = 1; t = 4000; break;
			  case WP_NAILGUN: max = 10; inc = 1; t = 1250; break;
			  case WP_PROX_LAUNCHER: max = 5; inc = 1; t = 2000; break;
			  case WP_CHAINGUN: max = 100; inc = 5; t = 1000; break;
			  default: max = 0; inc = 0; t = 1000; break;
		  }
		  client->ammoTimes[w] += msec;
		  if ( client->ps.ammo[w] >= max ) {
			  client->ammoTimes[w] = 0;
#ifdef USE_RUNES
				if(ent->client->inventory[RUNE_ACTION]) {
					ent->client->ps.stats[STAT_WEAPONS] |= (1 << w);
				}
#endif
		  }
		  if ( client->ammoTimes[w] >= t ) {
			  while ( client->ammoTimes[w] >= t )
				  client->ammoTimes[w] -= t;
			  client->ps.ammo[w] += inc;
			  if ( client->ps.ammo[w] > max ) {
				  client->ps.ammo[w] = max;
			  }
		  }
    }
	}
#endif
}

/*
====================
ClientIntermissionThink
====================
*/
void ClientIntermissionThink( gclient_t *client ) {
	client->ps.eFlags &= ~EF_TALK;
	client->ps.eFlags &= ~EF_FIRING;

	// the level will exit when everyone wants to or after timeouts
#ifdef USE_BIRDS_EYE
	if (client->pers.thirdPerson || g_thirdPerson.integer) {
		client->ps.pm_type = PM_THIRDPERSON;
	} else if (client->pers.birdsEye || g_birdsEye.integer) {
			if(client->pers.showCursor) {
				client->ps.pm_type = PM_FOLLOWCURSOR;
			} else {
				client->ps.pm_type = PM_BIRDSEYE;
			}
	} else if (client->pers.sideView || g_sideview.integer) {
		client->ps.pm_type = PM_PLATFORM;
	}
#endif
#ifdef USE_AIW
	if(client->pers.reverseControls) {
		client->ps.pm_type = PM_REVERSED;
	}
	if(client->pers.upsidedown || g_upsideDown.integer) {
		client->ps.pm_type = PM_UPSIDEDOWN;
	}
	if(client->pers.reverseControls && (client->pers.upsidedown || g_upsideDown.integer)) {
		client->ps.pm_type = PM_REVERSEDUPSIDEDOWN;
	}
#endif

	// swap and latch button actions
	client->oldbuttons = client->buttons;
	client->buttons = client->pers.cmd.buttons;
	if ( client->buttons & ( BUTTON_ATTACK | BUTTON_USE_HOLDABLE ) & ( client->oldbuttons ^ client->buttons ) ) {
		// this used to be an ^1 but once a player says ready, it should stick
		client->readyToExit = 1;
	}
}


#ifdef USE_ADVANCED_ITEMS
void UsePowerup( gentity_t *ent, powerup_t powerup );
#endif


/*
================
ClientEvents

Events will be passed on to the clients for presentation,
but any server game effects are handled here
================
*/
void ClientEvents( gentity_t *ent, int oldEventSequence ) {
#ifdef USE_ADVANCED_ITEMS
	int		i;
#else
	int		i, j;
#endif
	int		event;
	gclient_t *client;
	int		damage;
#ifndef USE_ADVANCED_ITEMS
	vec3_t	origin, angles;
//	qboolean	fired;
	gitem_t *item;
	gentity_t *drop;
#endif

	client = ent->client;

	if ( oldEventSequence < client->ps.eventSequence - MAX_PS_EVENTS ) {
		oldEventSequence = client->ps.eventSequence - MAX_PS_EVENTS;
	}
	for ( i = oldEventSequence ; i < client->ps.eventSequence ; i++ ) {
		event = client->ps.events[ i & (MAX_PS_EVENTS-1) ];

		switch ( event ) {
		case EV_FALL_MEDIUM:
		case EV_FALL_FAR:
			if ( ent->s.eType != ET_PLAYER ) {
				break;		// not in the player model
			}
			if ( g_dmflags.integer & DF_NO_FALLING ) {
				break;
			}
			if ( event == EV_FALL_FAR ) {
				damage = 10;
			} else {
				damage = 5;
			}
			ent->pain_debounce_time = level.time + 200;	// no normal pain sound
			G_Damage (ent, NULL, NULL, NULL, NULL, damage, 0, MOD_FALLING);
			break;

#ifdef USE_ALT_FIRE
    case EV_ALTFIRE_BOTH:
    case EV_ALTFIRE_WEAPON:
#ifdef USE_PORTALS
      if(g_altPortal.integer) {
        int oldWeapon = ent->s.weapon;
        ent->s.weapon = WP_BFG;
				FireWeapon( ent, qtrue );
        ent->s.weapon = oldWeapon;
      } else
#endif
#ifdef USE_GRAPPLE
      if(g_altGrapple.integer) {
        int oldWeapon = ent->s.weapon;
        ent->s.weapon = WP_GRAPPLING_HOOK;
        FireWeapon( ent, qtrue );
        ent->s.weapon = oldWeapon;
      } else
#endif
      FireWeapon( ent, qtrue );

		if(event != EV_ALTFIRE_BOTH)
      break;        
#endif
		case EV_FIRE_WEAPON:
#ifdef USE_ALT_FIRE
			FireWeapon( ent, qfalse );
#else
			FireWeapon( ent );
#endif
			break;

#ifdef USE_SINGLEPLAYER
		case EV_USE:
			G_Use(ent);
			break;
#endif


#ifdef USE_ADVANCED_ITEMS
		case EV_USE_ITEM5:
		case EV_USE_ITEM4:
		case EV_USE_ITEM3:
		case EV_USE_ITEM2:
		case EV_USE_ITEM1:
		case EV_USE_ITEM0:
			UsePowerup(ent, client->ps.eventParms[ i & (MAX_PS_EVENTS-1) ]);
			break;
#else
		case EV_USE_ITEM1:		// teleporter
			// drop flags in CTF
			item = NULL;
			j = 0;

			if ( ent->client->ps.powerups[ PW_REDFLAG ] ) {
				item = BG_FindItemForPowerup( PW_REDFLAG );
				j = PW_REDFLAG;
			} else if ( ent->client->ps.powerups[ PW_BLUEFLAG ] ) {
				item = BG_FindItemForPowerup( PW_BLUEFLAG );
				j = PW_BLUEFLAG;
#if defined(USE_ADVANCED_GAMES) || defined(USE_ADVANCED_TEAMS)
			} else if ( ent->client->ps.powerups[ PW_GOLDFLAG ] ) {
				item = BG_FindItemForPowerup( PW_GOLDFLAG );
				j = PW_GOLDFLAG;
			} else if ( ent->client->ps.powerups[ PW_GREENFLAG ] ) {
				item = BG_FindItemForPowerup( PW_GREENFLAG );
				j = PW_GREENFLAG;
#endif
			} else if ( ent->client->ps.powerups[ PW_NEUTRALFLAG ] ) {
				item = BG_FindItemForPowerup( PW_NEUTRALFLAG );
				j = PW_NEUTRALFLAG;
			}

			if ( item ) {
				drop = Drop_Item( ent, item, 0 );
				// decide how many seconds it has left
				drop->count = ( ent->client->ps.powerups[ j ] - level.time ) / 1000;
				if ( drop->count < 1 ) {
					drop->count = 1;
				}
				// for pickup prediction
				drop->s.time2 = drop->count;

				ent->client->ps.powerups[ j ] = 0;
			}

#ifdef MISSIONPACK
			if ( g_gametype.integer == GT_HARVESTER ) {
				if ( ent->client->ps.generic1 > 0 ) {
					if ( ent->client->sess.sessionTeam == TEAM_RED ) {
						item = BG_FindItem( "Blue Cube" );
					} else {
						item = BG_FindItem( "Red Cube" );
					}
					if ( item ) {
						for ( j = 0; j < ent->client->ps.generic1; j++ ) {
							drop = Drop_Item( ent, item, 0 );
							if ( ent->client->sess.sessionTeam == TEAM_RED ) {
								drop->spawnflags = TEAM_BLUE;
							} else {
								drop->spawnflags = TEAM_RED;
							}
						}
					}
					ent->client->ps.generic1 = 0;
				}
			}
#endif
			SelectSpawnPoint( ent, ent->client->ps.origin, origin, angles );
			TeleportPlayer( ent, origin, angles );
			break;

		case EV_USE_ITEM2:		// medkit
			ent->health = ent->client->ps.stats[STAT_MAX_HEALTH] + 25;

			break;

#ifdef MISSIONPACK
		case EV_USE_ITEM3:		// kamikaze
			// make sure the invulnerability is off
			ent->client->invulnerabilityTime = 0;
			// start the kamikze
			G_StartKamikaze( ent );
			break;
		case EV_USE_ITEM5:		// invulnerability
			ent->client->invulnerabilityTime = level.time + 10000;
			break;
#endif

#ifdef USE_PORTALS
		case EV_USE_ITEM4:		// portal
			if( ent->client->portalID ) {
				DropPortalSource( ent );
			}
			else {
				DropPortalDestination( ent );
			}
			break;
#endif

#endif

		default:
			break;
		}
	}

}

#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS)
/*
==============
StuckInOtherClient
==============
*/
static int StuckInOtherClient(gentity_t *ent) {
	int i;
	gentity_t	*ent2;

	ent2 = &g_entities[0];
	for ( i = 0; i < MAX_CLIENTS; i++, ent2++ ) {
		if ( ent2 == ent ) {
			continue;
		}
		if ( !ent2->inuse ) {
			continue;
		}
		if ( !ent2->client ) {
			continue;
		}
		if ( ent2->health <= 0 ) {
			continue;
		}
		//
		if (ent2->r.absmin[0] > ent->r.absmax[0])
			continue;
		if (ent2->r.absmin[1] > ent->r.absmax[1])
			continue;
		if (ent2->r.absmin[2] > ent->r.absmax[2])
			continue;
		if (ent2->r.absmax[0] < ent->r.absmin[0])
			continue;
		if (ent2->r.absmax[1] < ent->r.absmin[1])
			continue;
		if (ent2->r.absmax[2] < ent->r.absmin[2])
			continue;
		return qtrue;
	}
	return qfalse;
}
#endif

void BotTestSolid(vec3_t origin);

/*
==============
SendPendingPredictableEvents
==============
*/
void SendPendingPredictableEvents( playerState_t *ps ) {
	gentity_t *t;
	int event, seq;
	int extEvent, number;

	// if there are still events pending
	if ( ps->entityEventSequence < ps->eventSequence ) {
		// create a temporary entity for this event which is sent to everyone
		// except the client who generated the event
		seq = ps->entityEventSequence & (MAX_PS_EVENTS-1);
		event = ps->events[ seq ] | ( ( ps->entityEventSequence & 3 ) << 8 );
		// set external event to zero before calling BG_PlayerStateToEntityState
		extEvent = ps->externalEvent;
		ps->externalEvent = 0;
		// create temporary entity for event
		t = G_TempEntity( ps->origin, event );
		number = t->s.number;
		BG_PlayerStateToEntityState( ps, &t->s, qtrue );
		t->s.number = number;
		t->s.eType = ET_EVENTS + event;
		t->s.eFlags |= EF_PLAYER_EVENT;
		t->s.otherEntityNum = ps->clientNum;
		// send to everyone except the client who generated the event
		t->r.svFlags |= SVF_NOTSINGLECLIENT;
		t->r.singleClient = ps->clientNum;
		// set back external event
		ps->externalEvent = extEvent;
	}
}


#ifdef USE_GAME_FREEZETAG
void player_frozen(gentity_t *self, int killer);
#endif


/*
==============
ClientThink

This will be called once for each client frame, which will
usually be a couple times for each server frame on fast clients.

If "g_synchronousClients 1" is set, this will be called exactly
once for each server frame, which makes for smooth demo recording.
==============
*/
void ClientThink_real( gentity_t *ent ) {
	gclient_t	*client;
	pmove_t		pm;
	int			oldEventSequence;
	int			msec;
	usercmd_t	*ucmd;
#ifdef USE_PORTALS
	vec3_t sources[32], destinations[32], sourcesAngles[32], destinationsAngles[32];
#endif
#ifdef USE_ADVANCED_WEAPONS
	int i;
#endif

	client = ent->client;

	// don't think if the client is not yet connected (and thus not yet spawned in)
	if (client->pers.connected != CON_CONNECTED) {
		return;
	}
	// mark the time, so the connection sprite can be removed
	ucmd = &ent->client->pers.cmd;

#ifdef USE_ADVANCED_WEAPONS
	//G_Printf("game class: %i\n", weaponClass);
	client->ps.weapon = ent->s.weapon = client->weaponClass * WP_MAX_WEAPONS + (ent->client->ps.weapon % WP_MAX_WEAPONS);
	client->ps.stats[STAT_WEAPONS] = client->weapons[client->weaponClass];
	for(i = 0; i < WP_MAX_WEAPONS; i++) {
		client->ps.ammo[i] = client->ammo[client->weaponClass][i];
	}
		/*G_Printf("weapons %i: %i %i %i %i %i %i %i %i %i %i\n", 
		client->weaponClass,
		(client->ps.stats[STAT_WEAPONS] & (1 << 0)) >> 0,
		(client->ps.stats[STAT_WEAPONS] & (1 << 1)) >> 1,
		(client->ps.stats[STAT_WEAPONS] & (1 << 2)) >> 2,
		(client->ps.stats[STAT_WEAPONS] & (1 << 3)) >> 3,
		(client->ps.stats[STAT_WEAPONS] & (1 << 4)) >> 4,
		(client->ps.stats[STAT_WEAPONS] & (1 << 5)) >> 5,
		(client->ps.stats[STAT_WEAPONS] & (1 << 6)) >> 6,
		(client->ps.stats[STAT_WEAPONS] & (1 << 7)) >> 7,
		(client->ps.stats[STAT_WEAPONS] & (1 << 8)) >> 8,
		(client->ps.stats[STAT_WEAPONS] & (1 << 9)) >> 9
		);*/

#endif

#ifdef USE_ADVANCED_ITEMS
	// update item classes but actually store them on the client
	// TODO: use these techniques to improve weapon switching without delay
	if(client->lastItemTime + 30 < level.time) {
		int i, j;
		int itemBits;
		qboolean hasItems = qfalse;
		// TODO: find the next item in inventory and switch to that class for updates
		int prevItemClass = client->ps.stats[STAT_HOLDABLE_UPDATE];
		for(i = 0; i < 2 * PW_NUM_POWERUPS; i++) {
			prevItemClass++;
			if(prevItemClass == PW_MAX_ITEMGROUPS) {
				prevItemClass = 0;
			}
			if(!client->inventoryModified[prevItemClass]) {
				continue;
			}
			itemBits = 0;
			hasItems = qfalse;
			for(j = 0; j < PW_MAX_POWERUPS; j++) {
				//gitem_t *item = BG_FindItemForPowerup(prevItemClass * PW_MAX_POWERUPS + j);
				//if(!item || !item->giTag) {
				//	continue;
				//}
				if(prevItemClass * PW_MAX_POWERUPS + j >= PW_NUM_POWERUPS) {
					continue;
				}
				hasItems = qtrue;
				if(client->inventory[prevItemClass * PW_MAX_POWERUPS + j] > 0) {
					itemBits |= (1 << j);
				}
			}
			if(hasItems) {
				break;
			}
		}

		if(i < 2 * PW_NUM_POWERUPS) {
			client->ps.stats[STAT_HOLDABLE_UPDATE] = prevItemClass;
			client->ps.stats[STAT_HOLDABLE_AVAILABLE] = itemBits;
			client->inventoryModified[prevItemClass] = qfalse;
		}
		client->lastItemTime = level.time;
	}
#endif

#ifdef USE_RPG_STATS
	if(client->lastHealthTime + 1000 < level.time) {
		gentity_t *plum;
		plum = G_TempEntity( ent->r.currentOrigin, EV_HEALTHPLUM );
		// only send this temp entity to a single client
		plum->r.svFlags |= SVF_BROADCAST;
		ent->s.eFlags |= EF_NODRAW;
		plum->s.otherEntityNum = ent->s.number;
		plum->s.time = ent->health;
		plum->s.powerups = ent->s.powerups;
		client->lastHealthTime = level.time;
	}
#endif

	// sanity check the command time to prevent speedup cheating
	if ( ucmd->serverTime > level.time + 200 ) {
		ucmd->serverTime = level.time + 200;
//		G_Printf("serverTime <<<<<\n" );
	} else
	if ( ucmd->serverTime < level.time - 1000 ) {
		ucmd->serverTime = level.time - 1000;
//		G_Printf("serverTime >>>>>\n" );
	}

	// unlagged
	client->frameOffset = trap_Milliseconds() - level.frameStartTime;
	client->lastCmdTime = ucmd->serverTime;
	client->lastUpdateFrame = level.framenum;

	msec = ucmd->serverTime - client->ps.commandTime;
	// following others may result in bad times, but we still want
	// to check for follow toggles
	if ( msec < 1 && client->sess.spectatorState != SPECTATOR_FOLLOW ) {
		return;
	}
	if ( msec > 200 ) {
		msec = 200;
	}

	if ( pmove_msec.integer < 8 ) {
		trap_Cvar_Set( "pmove_msec", "8" );
		trap_Cvar_Update( &pmove_msec );
	} else if ( pmove_msec.integer > 33 ) {
		trap_Cvar_Set( "pmove_msec", "33" );
		trap_Cvar_Update( &pmove_msec );
	}

	if ( pmove_fixed.integer ) {
		ucmd->serverTime = ((ucmd->serverTime + pmove_msec.integer-1) / pmove_msec.integer) * pmove_msec.integer;
		//if (ucmd->serverTime - client->ps.commandTime <= 0)
		//	return;
	}

	//
	// check for exiting intermission
	//
	if ( level.intermissiontime ) {
		ClientIntermissionThink( client );
		return;
	}

	// spectators don't do much
	if ( client->sess.sessionTeam == TEAM_SPECTATOR ) {
		if ( client->sess.spectatorState == SPECTATOR_SCOREBOARD ) {
			return;
		}
		SpectatorThink( ent, ucmd );
		return;
	}

	// check for inactivity timer, but never drop the local client of a non-dedicated server
	if ( !ClientInactivityTimer( client ) ) {
		return;
	}

	// clear the rewards if time
	if ( level.time > client->rewardTime ) {
		client->ps.eFlags &= ~EF_AWARDS;
	}

	if ( client->noclip ) {
		client->ps.pm_type = PM_NOCLIP;
  } else
#if defined(USE_GAME_FREEZETAG) || defined(USE_REFEREE_CMDS)
#ifdef USE_ADVANCED_ITEMS
  if ( g_freezeTag.integer && client->inventory[PW_FROZEN] ) 
#else
  if ( g_freezeTag.integer && client->ps.powerups[PW_FROZEN] ) 
#endif
	{
    client->ps.pm_type = PM_FROZEN;
		//client->ps.powerups[PW_FROZEN] = level.time + g_thawTime.integer * 1000;
  } else
#endif
  if ( client->ps.stats[STAT_HEALTH] <= 0 ) {
		client->ps.pm_type = PM_DEAD;
	} else 
#ifdef USE_VEHICLES
	if(client->inventory[HI_VEHICLE]) {
		if(client->pers.showCursor) {
			client->ps.pm_type = PM_VEHICLEMOUSE;
		} else {
			client->ps.pm_type = PM_VEHICLE;
		}
	} else
#endif
#ifdef USE_BIRDS_EYE
	if (client->pers.thirdPerson || g_thirdPerson.integer) {
		client->ps.pm_type = PM_THIRDPERSON;
	} else if (client->pers.birdsEye || g_birdsEye.integer) {
		if(client->pers.showCursor) {
			client->ps.pm_type = PM_FOLLOWCURSOR;
		} else {
			client->ps.pm_type = PM_BIRDSEYE;
		}
	} else if (client->pers.sideView || g_sideview.integer) {
		client->ps.pm_type = PM_PLATFORM;
	} else
#endif
#ifdef USE_AIW
	if(client->pers.reverseControls && (client->pers.upsidedown || g_upsideDown.integer)) {
		client->ps.pm_type = PM_REVERSEDUPSIDEDOWN;
	} else
	if(client->pers.reverseControls) {
		client->ps.pm_type = PM_REVERSED;
	} else 
	if(client->pers.upsidedown || g_upsideDown.integer) {
		client->ps.pm_type = PM_UPSIDEDOWN;
	} else 
#endif
	{
		client->ps.pm_type = PM_NORMAL;
	}

#ifdef USE_ADVANCED_ITEMS
	if(client->inventory[PW_GRAVITYSUIT]) {
		client->ps.gravity = g_gravity.value * 0.5f;        //  yeah... this too
	} else
#endif
#ifdef USE_GRAVITY_BOOTS
  if (g_enableBoots.integer && ent->flags & FL_BOOTS) {                  //  umm and this,
		client->ps.gravity = g_gravity.value * g_bootsGravity.value;        //  yeah... this too
	} else
#endif
	if(client->altGravity) {
		client->ps.gravity = client->altGravity;
	} else
	client->ps.gravity = g_gravity.value;

	// set speed
	client->ps.speed = g_speed.value;

#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS)
	if( bg_itemlist[client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_SCOUT ) {
#ifdef USE_PHYSICS_VARS
    client->ps.speed *= g_scoutFactor.value;
#else
		client->ps.speed *= 1.5;
#endif
	} else
#endif

#ifdef USE_ADVANCED_ITEMS
	if(client->inventory[PW_FLASH] || client->inventory[PW_SUPERMAN]) {
		client->ps.speed *= 2.6;
	} else
	if(client->inventory[PW_HASTE]) {
#ifdef USE_PHYSICS_VARS
    client->ps.speed *= g_hasteFactor.value;
#else
		client->ps.speed *= 1.3;
#endif
	} else

#else

	if ( client->ps.powerups[PW_HASTE] 
#ifdef USE_RUNES
    || ent->client->inventory[RUNE_HASTE]
#endif
	) {
#ifdef USE_PHYSICS_VARS
    client->ps.speed *= g_hasteFactor.value;
#else
		client->ps.speed *= 1.3;
#endif
	}

#endif

#ifdef USE_LOCAL_DMG
  if(g_locDamage.integer) {
    if(client->lasthurt_location == LOCATION_LEG) {
      client->ps.speed *= 0.7;
    }
    if(client->lasthurt_location == LOCATION_FOOT) {
      client->ps.speed *= 0.5;
    }
  }
#endif

client->ps.speed *= g_playerScale.value;

#if defined(USE_GAME_FREEZETAG) || defined(USE_REFEREE_CMDS)
  if(g_freezeTag.integer && g_thawTime.integer
#ifdef USE_ADVANCED_ITEMS
    && ent->client->inventory[PW_FROZEN]
    && level.time >= ent->client->inventory[PW_FROZEN]
#else
    && ent->client->ps.powerups[PW_FROZEN]
    && level.time >= ent->client->ps.powerups[PW_FROZEN]
#endif
  ) {
    G_AddEvent( ent, EV_UNFROZEN, 0 );
#ifdef USE_ADVANCED_ITEMS
    ent->client->inventory[PW_FROZEN] = 0;
#else
    ent->client->ps.powerups[PW_FROZEN] = 0;
#endif
    SetClientViewAngle(ent, client->frozen_angles);
  }
#endif
#ifdef USE_GRAPPLE
	// Let go of the hook if we aren't firing
#ifdef USE_ALT_FIRE
  if ( g_altGrapple.integer 
    && client->hook && !( ucmd->buttons & BUTTON_ALT_ATTACK ) ) {
    Weapon_HookFree(client->hook);
  } else
#endif
	if ( client->ps.weapon == WP_GRAPPLING_HOOK &&
		client->hook && !( ucmd->buttons & BUTTON_ATTACK ) ) {
		Weapon_HookFree(client->hook);
	}
#endif

	// set up for pmove
	oldEventSequence = client->ps.eventSequence;

	memset (&pm, 0, sizeof(pm));

	// check for the hit-scan gauntlet, don't let the action
	// go through as an attack unless it actually hits something
	if ( client->ps.weapon == WP_GAUNTLET && !( ucmd->buttons & BUTTON_TALK ) &&
		( ucmd->buttons & BUTTON_ATTACK ) && client->ps.weaponTime <= 0 ) {
		pm.gauntletHit = CheckGauntletAttack( ent );
	}

	if ( ent->flags & FL_FORCE_GESTURE ) {
		ent->flags &= ~FL_FORCE_GESTURE;
		ent->client->pers.cmd.buttons |= BUTTON_GESTURE;
	}

#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS) || defined(USE_RUNES)
	// check for invulnerability expansion before doing the Pmove
#ifdef USE_ADVANCED_ITEMS
	if (client->inventory[PW_INVULNERABILITY] ) 
#else
	if (client->ps.powerups[PW_INVULNERABILITY] ) 
#endif
	{
		if ( !(client->ps.pm_flags & PMF_INVULEXPAND) ) {
			vec3_t mins = { -42, -42, -42 };
			vec3_t maxs = { 42, 42, 42 };
			vec3_t oldmins, oldmaxs;

			VectorCopy (ent->r.mins, oldmins);
			VectorCopy (ent->r.maxs, oldmaxs);
			// expand
			VectorCopy (mins, ent->r.mins);
			VectorCopy (maxs, ent->r.maxs);
			trap_LinkEntity(ent);
			// check if this would get anyone stuck in this player
			if ( !StuckInOtherClient(ent) ) {
				// set flag so the expanded size will be set in PM_CheckDuck
				client->ps.pm_flags |= PMF_INVULEXPAND;
			}
			// set back
			VectorCopy (oldmins, ent->r.mins);
			VectorCopy (oldmaxs, ent->r.maxs);
			trap_LinkEntity(ent);
		}
	}
#endif

	pm.ps = &client->ps;
#ifdef USE_ADVANCED_CLASS
	pm.playerClass = client->pers.newplayerclass; // possible for bgmove to change a player class using a powerup?
#endif
#ifdef USE_ADVANCED_ITEMS
	memcpy(pm.inventory, client->inventory, sizeof(client->inventory));
#endif
	pm.cmd = *ucmd;
	if ( pm.ps->pm_type == PM_DEAD ) {
		pm.tracemask = MASK_PLAYERSOLID & ~CONTENTS_BODY;
	}
	else if ( ent->r.svFlags & SVF_BOT ) {
		pm.tracemask = MASK_PLAYERSOLID | CONTENTS_BOTCLIP;
	}
	else {
		pm.tracemask = MASK_PLAYERSOLID;
	}
	pm.trace = trap_Trace;
	pm.pointcontents = trap_PointContents;
	pm.debugLevel = g_debugMove.integer;

	pm.pmove_fixed = pmove_fixed.integer;
	pm.pmove_msec = pmove_msec.integer;

#ifdef USE_VEHICLES
// STONELANCE
	// TEMP used to move car around
/*
	client->car.sBody.r[2] += 3.0f * (pm.cmd.upmove * msec / 1000.0f);
	client->car.sBody.CoM[2] += 3.0f * (pm.cmd.upmove * msec / 1000.0f);
	for (i = 0; i < 8; i++){
		client->car.sPoints[i].r[2] += 3.0f * (pm.cmd.upmove * msec / 1000.0f);
	}
*/
	// END TEMP

	// load car position etc into pmove
	level.cars[ent->s.clientNum] = &client->car;

	pm.car = &client->car;
	pm.cars = level.cars;
	//pm.pDebug = ent->pDebug;

	//pm.controlMode = client->pers.controlMode;
	//pm.manualShift = client->pers.manualShift;
	pm.client = qfalse;

	//if (ent->pDebug > 0){
	//	Com_LogPrintf("Server Time: %i\n", pm.cmd.serverTime);
	//	Com_LogPrintf("Source: Debug %d\n", ent->pDebug);
	//	G_DebugForces(&pm.car->sBody, pm.car->sPoints, ent->pDebug-1);
	//	G_DebugDynamics(&pm.car->sBody, pm.car->sPoints, ent->pDebug-1);
	//}

	//start = trap_Milliseconds();

	//oldTime = client->ps.commandTime;
	//VectorCopy( client->ps.viewangles, oldAngles );

	pm.car_spring = car_spring.value;
	pm.car_shock_up = car_shock_up.value;
	pm.car_shock_down = car_shock_down.value;
	pm.car_swaybar = car_swaybar.value;
	pm.car_wheel = car_wheel.value;
	pm.car_wheel_damp = car_wheel_damp.value;

	pm.car_frontweight_dist = car_frontweight_dist.value;
	pm.car_IT_xScale = car_IT_xScale.value;
	pm.car_IT_yScale = car_IT_yScale.value;
	pm.car_IT_zScale = car_IT_zScale.value;
	pm.car_body_elasticity = car_body_elasticity.value;

	pm.car_air_cof = car_air_cof.value;
	pm.car_air_frac_to_df = car_air_frac_to_df.value;
	pm.car_friction_scale = car_friction_scale.value;
// END
#endif

	VectorCopy( client->ps.origin, client->oldOrigin );


#ifdef USE_PORTALS
	G_ListPortals( ent, sources, destinations, sourcesAngles, destinationsAngles );
#endif
#ifdef MISSIONPACK
		if (level.intermissionQueued != 0 && g_singlePlayer.integer) {
			if ( level.time - level.intermissionQueued >= 1000  ) {
				pm.cmd.buttons = 0;
				pm.cmd.forwardmove = 0;
				pm.cmd.rightmove = 0;
				pm.cmd.upmove = 0;
				if ( level.time - level.intermissionQueued >= 2000 && level.time - level.intermissionQueued <= 2500 ) {
					trap_SendConsoleCommand( EXEC_APPEND, "centerview\n");
				}
				ent->client->ps.pm_type = PM_SPINTERMISSION;
			}
		}
		Pmove (&pm);
#else
		Pmove (&pm);
#endif

#ifdef USE_BIRDS_EYE
	if(pm.ps->pm_type == PM_FOLLOWCURSOR
		|| pm.ps->pm_type == PM_PLATFORM) {
		if(!ent->client->cursorEnt || ent->client->cursorEnt->r.ownerNum != ent->client->ps.clientNum 
			|| level.time - ent->client->cursorEnt->eventTime > 1000) {
			gentity_t *pent;
			if(ent->client->cursorEnt && ent->client->cursorEnt->r.ownerNum == ent->client->ps.clientNum) {
				G_FreeEntity(ent->client->cursorEnt);
			}
			ent->client->cursorEnt = pent = G_TempEntity( client->ps.origin, EV_CURSORSTART );
			pent->s.clientNum = client - level.clients;
			pent->r.singleClient = client - level.clients;
			pent->r.svFlags |= SVF_SINGLECLIENT;
			pent->freeAfterEvent = qfalse;
			pent->s.eType = ET_CURSOR;
			pent->eventTime = level.time;
			pent->freetime = level.time + 1000;
			pent->r.ownerNum = ent->client->ps.clientNum;
		} else {
			gentity_t *pent;
			pent = ent->client->cursorEnt;
			//pent->eventTime = level.time;
			//pent->s.event++;
			//G_AddEvent(pent, EV_EVENT_BITS, 0);
			pent->s.pos.trBase[0] = SHORT2ANGLE(ucmd->angles[YAW]);
			pent->s.pos.trBase[1] = SHORT2ANGLE(ucmd->angles[PITCH]);
			
			
			VectorCopy(pent->s.pos.trBase, pent->s.origin);
		}
	}




	if(pm.ps->pm_type == PM_FOLLOWCURSOR && !(ent->r.svFlags & SVF_BOT)) {
		ent->client->ps.delta_angles[PITCH] = 0;
		ent->s.angles[PITCH] = SHORT2ANGLE(1);
	} else
	if(pm.ps->pm_type == PM_BIRDSEYE && !(ent->r.svFlags & SVF_BOT)) {
		ent->client->ps.delta_angles[PITCH] = 0;
		ent->s.angles[PITCH] = SHORT2ANGLE(1);
	} else
	if(pm.ps->pm_type == PM_PLATFORM && !(ent->r.svFlags & SVF_BOT)) {
		// ZYGOTE START
		// (Human) NOT A BOT
		short		temp;

		// Setup temp
		temp = ent->client->pers.cmd.angles[YAW]; // + ent->client->ps.delta_angles[YAW];		
		
		// Some ugly shit, but it works :)
		if ( (temp > -30000) && (temp < 0) ) {
			ent->client->ps.delta_angles[YAW] = -1000 - ent->client->pers.cmd.angles[YAW];
			temp = 0; // RIGHT
		}
		if ( (temp < 30000) && (temp > 0) ) {
			ent->client->ps.delta_angles[YAW] = 1000 - ent->client->pers.cmd.angles[YAW];
			temp = 32000; // LEFT
		}	

		// Copy modified YAW into viewangles
		//G_Printf("view: %f\n", SHORT2ANGLE(temp));
		ent->client->ps.delta_angles[YAW] = 0;
		//ent->client->ps.viewangles[YAW] = SHORT2ANGLE(temp) < 0 ? 270 : 90;
		ent->client->ps.viewangles[YAW] = SHORT2ANGLE(temp);
		// ZYGOTE FINISH
	}
#endif
#ifdef USE_AIW
	if(pm.ps->pm_type == PM_UPSIDEDOWN && !(ent->r.svFlags & SVF_BOT)) {
		// Copy modified YAW into viewangles
		ent->client->ps.delta_angles[ROLL] = 180;
		ent->client->ps.viewangles[ROLL] = SHORT2ANGLE(180);
	}
#endif

	// save results of pmove
	if ( ent->client->ps.eventSequence != oldEventSequence ) {
		ent->eventTime = level.time;
	}

	BG_PlayerStateToEntityState( &ent->client->ps, &ent->s, qtrue );

#ifdef USE_ADVANCED_WEAPONS
	client->ps.weapon = ent->s.weapon = client->weaponClass * WP_MAX_WEAPONS + (ent->client->ps.weapon % WP_MAX_WEAPONS);
	//G_Printf("weapon: %i\n", ent->client->ps.weapon);
	client->ammo[client->weaponClass][ client->ps.weapon % WP_MAX_WEAPONS ] = client->ps.ammo[client->ps.weapon % WP_MAX_WEAPONS];
#endif

	SendPendingPredictableEvents( &ent->client->ps );

#ifdef USE_GRAPPLE
	if ( !( ent->client->ps.eFlags & EF_FIRING ) 
#ifdef USE_ALT_FIRE
    || (g_altGrapple.integer && !(pm.cmd.buttons & BUTTON_ALT_ATTACK))
#endif
  ) {
		client->fireHeld = qfalse;		// for grapple
	}
#endif

	// use the snapped origin for linking so it matches client predicted versions
	VectorCopy( ent->s.pos.trBase, ent->r.currentOrigin );

	VectorCopy (pm.mins, ent->r.mins);
	VectorCopy (pm.maxs, ent->r.maxs);

#ifdef USE_ADVANCED_CLASS
	ent->client->ps.stats[STAT_PLAYERCLASS] = pm.playerClass;
#endif

	ent->waterlevel = pm.waterlevel;
	ent->watertype = pm.watertype;

	// execute client events
	ClientEvents( ent, oldEventSequence );

	// link entity now, after any personal teleporters have been used
	trap_LinkEntity (ent);
	if ( !ent->client->noclip ) {
		G_TouchTriggers( ent );
	}

	// NOTE: now copy the exact origin over otherwise clients can be snapped into solid
	VectorCopy( ent->client->ps.origin, ent->r.currentOrigin );

	//test for solid areas in the AAS file
	BotTestAAS(ent->r.currentOrigin);

	// touch other objects
	ClientImpacts( ent, &pm );

	// save results of triggers and client events
	if (ent->client->ps.eventSequence != oldEventSequence) {
		ent->eventTime = level.time;
	}

	// swap and latch button actions
	client->oldbuttons = client->buttons;
	client->buttons = ucmd->buttons;
	client->latched_buttons |= client->buttons & ~client->oldbuttons;

	// check for respawning
#ifdef USE_GAME_FREEZETAG
	if(!g_freezeTag.integer
		 || client->ps.stats[STAT_HEALTH] != INFINITE
		 || client->ps.pm_type != PM_FROZEN
	) {
#endif

	if ( client->ps.stats[STAT_HEALTH] <= 0 ) {
		// wait for the attack button to be pressed
		if ( level.time > client->respawnTime ) {
			// forcerespawn is to prevent users from waiting out powerups
			if ( g_forcerespawn.value > 0 && 
				( level.time - client->respawnTime ) > g_forcerespawn.value * 1000 ) {
				respawn( ent );
				return;
			}
		
			// pressing attack or use is the normal respawn method
			if ( ucmd->buttons & ( BUTTON_ATTACK | BUTTON_USE_HOLDABLE ) ) {
				respawn( ent );
			}
		}
		return;
	}

#ifdef USE_GAME_FREEZETAG
	} else {
		//if(level.time - client->ps.powerups[PW_FROZEN] >= 0) {
		//	client->ps.pm_type = PM_DEAD;
		//	respawn( ent );
		//}
		//if(level.time - client->lastFreezeTime >= 1000) {
		//	player_frozen(ent, 0);
		//}
	}
#endif


	G_SetEntityPointed(ent);

	// perform once-a-second actions
	ClientTimerActions( ent, msec );
}


/*
==================
ClientThink

A new command has arrived from the client
==================
*/
void ClientThink( int clientNum ) {
	gentity_t *ent;

	ent = g_entities + clientNum;

#ifdef USE_GAME_FREEZETAG
	if(ent->client->pers.connected == CON_CONNECTED) {
		if(g_freezeTag.integer &&
			(ent->client->ps.stats[STAT_HEALTH] == INFINITE
#ifdef USE_ADVANCED_ITEMS
			|| ent->client->inventory[PW_FROZEN]
#else
			|| ent->client->ps.powerups[PW_FROZEN]
#endif
		)) {
#ifdef USE_ADVANCED_ITEMS
			if(level.time - ent->client->inventory[PW_FROZEN] >= 0) 
#else
			if(level.time - ent->client->ps.powerups[PW_FROZEN] >= 0) 
#endif
			{
				ent->client->ps.pm_type = PM_DEAD;
				respawn( ent );
			}
			if(level.time - ent->client->lastFreezeTime >= 1000) {
				player_frozen(ent, 0);
			}
		}
	}
#endif


	trap_GetUsercmd( clientNum, &ent->client->pers.cmd );

	// mark the time we got info, so we can display the
	// phone jack if they don't get any for a while
#if 0 // unlagged
	ent->client->lastCmdTime = level.time;
#endif

	if ( !(ent->r.svFlags & SVF_BOT) && !g_synchronousClients.integer ) {
		ClientThink_real( ent );
	}
}


void G_RunClient( gentity_t *ent ) {

	if ( !(ent->r.svFlags & SVF_BOT) && !g_synchronousClients.integer ) {
		return;
	}
	ent->client->pers.cmd.serverTime = level.time;
	ClientThink_real( ent );
}


/*
==================
SpectatorClientEndFrame

==================
*/
void SpectatorClientEndFrame( gentity_t *ent ) {
	gclient_t	*cl;

	// if we are doing a chase cam or a remote view, grab the latest info
	if ( ent->client->sess.spectatorState == SPECTATOR_FOLLOW ) {
		int		clientNum, flags;

		clientNum = ent->client->sess.spectatorClient;

		// team follow1 and team follow2 go to whatever clients are playing
		if ( clientNum == -1 ) {
			clientNum = level.follow1;
		} else if ( clientNum == -2 ) {
			clientNum = level.follow2;
		}
		if ( (unsigned)clientNum < MAX_CLIENTS ) {
			cl = &level.clients[ clientNum ];
			if ( cl->pers.connected == CON_CONNECTED && cl->sess.sessionTeam != TEAM_SPECTATOR ) {
				flags = (cl->ps.eFlags & ~(EF_VOTED | EF_TEAMVOTED)) | (ent->client->ps.eFlags & (EF_VOTED | EF_TEAMVOTED));
				ent->client->ps = cl->ps;
				ent->client->ps.pm_flags |= PMF_FOLLOW;
				ent->client->ps.eFlags = flags;
				return;
			} else {
				// drop them to free spectators unless they are dedicated camera followers
				if ( ent->client->sess.spectatorClient >= 0 ) {
					ent->client->sess.spectatorState = SPECTATOR_FREE;
					ClientBegin( ent->client - level.clients );
				}
			}
		}
	}

	if ( ent->client->sess.spectatorState == SPECTATOR_SCOREBOARD ) {
		ent->client->ps.pm_flags |= PMF_SCOREBOARD;
	} else {
		ent->client->ps.pm_flags &= ~PMF_SCOREBOARD;
	}
}


#ifdef USE_ADVANCED_ITEMS
int BG_FindPriorityShaderForInventory(int powerup, int inventory[PW_NUM_POWERUPS], int team);
#endif

/*
==============
ClientEndFrame

Called at the end of each server frame for each connected client
A fast client will have multiple ClientThink for each ClientEdFrame,
while a slow client may have multiple ClientEndFrame between ClientThink.
==============
*/
void ClientEndFrame( gentity_t *ent ) {
	static gentity_t sent;
	int			i;
	gclient_t	*client;
	// unlagged
	int			frames;
#ifdef USE_ADVANCED_WEAPONS
	int weaponClass;
#endif

	if ( !ent->client )
		return;

	ent->r.svFlags &= ~svf_self_portal2;

	if ( ent->client->sess.sessionTeam == TEAM_SPECTATOR ) {
		SpectatorClientEndFrame( ent );
		return;
	}

	client = ent->client;

	// turn off any expired powerups
	for ( i = 0 ; i < MAX_POWERUPS ; i++ ) {
		if ( client->ps.powerups[ i ] < client->pers.cmd.serverTime ) {
			client->ps.powerups[ i ] = 0;
		}
	}

#ifdef USE_RUNES
  // keep rune switch on?
  //if(ent->client->inventory[ent->rune]) {
  //  ent->client->inventory[ent->rune] = level.time + 100000;
  //}
#endif
#ifdef USE_ADVANCED_CLASS
	//client->pers.newplayerclass = pm.playerClass; // possible for bgmove to change a player class using a powerup?
#endif
#ifdef USE_ADVANCED_ITEMS
	//memcpy(client->inventory, pm.inventory, sizeof(client->inventory));
	for ( i = 0 ; i < PW_NUM_POWERUPS ; i++ ) {
		gitem_t *item = BG_FindItemForPowerup(i);
		if(item->giType != IT_HOLDABLE &&
			item->giType != IT_PERSISTANT_POWERUP &&
			client->inventory[i] && 
			client->inventory[i] < client->pers.cmd.serverTime) {

			client->inventory[i] = 0;
			client->inventoryModified[(int)floor(i / PW_MAX_POWERUPS)] = qtrue;
			ent->s.powerups = 0;
		}
	}

	if( bg_itemlist[ent->client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_GUARD ) {
		ent->client->inventory[PW_GUARD] = level.time;
		ent->client->inventoryModified[(int)floor(PW_GUARD / PW_MAX_POWERUPS)] = qtrue;
	}
	if( bg_itemlist[ent->client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_SCOUT ) {
		ent->client->inventory[PW_SCOUT] = level.time;
		ent->client->inventoryModified[(int)floor(PW_SCOUT / PW_MAX_POWERUPS)] = qtrue;
	}
	if( bg_itemlist[ent->client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_DOUBLER ) {
		ent->client->inventory[PW_DOUBLER] = level.time;
		ent->client->inventoryModified[(int)floor(PW_DOUBLER / PW_MAX_POWERUPS)] = qtrue;
	}
	if( bg_itemlist[ent->client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_AMMOREGEN ) {
		ent->client->inventory[PW_AMMOREGEN] = level.time;
		ent->client->inventoryModified[(int)floor(PW_AMMOREGEN / PW_MAX_POWERUPS)] = qtrue;
	}
	if ( ent->client->invulnerabilityTime > level.time ) {
		ent->client->inventory[PW_INVULNERABILITY] = 1;
		ent->client->inventoryModified[(int)floor(PW_INVULNERABILITY / PW_MAX_POWERUPS)] = qtrue;
	}

	ent->s.powerups = BG_FindPriorityShaderForInventory(0, ent->client->inventory, ent->client->sess.sessionTeam);

#else
#ifdef MISSIONPACK
	// set powerup for player animation
	if( bg_itemlist[ent->client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_GUARD ) {
		ent->client->ps.powerups[PW_GUARD] = level.time;
	}
	if( bg_itemlist[ent->client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_SCOUT ) {
		ent->client->ps.powerups[PW_SCOUT] = level.time;
	}
	if( bg_itemlist[ent->client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_DOUBLER ) {
		ent->client->ps.powerups[PW_DOUBLER] = level.time;
	}
	if( bg_itemlist[ent->client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_AMMOREGEN ) {
		ent->client->ps.powerups[PW_AMMOREGEN] = level.time;
	}
	if ( ent->client->invulnerabilityTime > level.time ) {
		ent->client->ps.powerups[PW_INVULNERABILITY] = level.time;
	}
#endif
#endif

	// save network bandwidth
#if 0
	if ( !g_synchronousClients->integer && ent->client->ps.pm_type == PM_NORMAL ) {
		// FIXME: this must change eventually for non-sync demo recording
		VectorClear( ent->client->ps.viewangles );
	}
#endif

	//
	// If the end of unit layout is displayed, don't give
	// the player any normal movement attributes
	//
	if ( level.intermissiontime ) {
		client->ps.commandTime = client->pers.cmd.serverTime;
		return;
	}

	// burn from lava, etc
	P_WorldEffects (ent);

	// apply all the damage taken this frame
	P_DamageFeedback (ent);

	client->ps.stats[STAT_HEALTH] = ent->health;	// FIXME: get rid of ent->health...

	G_SetClientSound( ent );

	// set the latest info
	BG_PlayerStateToEntityState( &client->ps, &ent->s, qtrue );

	SendPendingPredictableEvents( &client->ps );

	client->ps.eFlags &= ~EF_CONNECTION;
	ent->s.eFlags &= ~EF_CONNECTION;

	frames = level.framenum - client->lastUpdateFrame - 1;

	// PVS prediction
	if ( g_predictPVS.integer && svf_self_portal2 ) {
		int lag;
		sent.s = ent->s;
		sent.r = ent->r;
		sent.clipmask = ent->clipmask;
		//VectorCopy( client->ps.origin, sent.s.pos.trBase );
		//VectorCopy( client->ps.velocity, sent.s.pos.trDelta );
		lag = level.time - client->ps.commandTime + 50;
		if ( lag > 500 )
			lag = 500;
		G_PredictPlayerMove( &sent, (float)lag * 0.001f );
		VectorCopy( sent.s.pos.trBase, ent->r.unused.origin2 );
		ent->r.unused.origin2[2] += client->ps.viewheight;
		ent->r.svFlags |= svf_self_portal2;
	}

	if ( frames > 2 ) {
		// limit lagged player prediction to 2 server frames
		frames = 2;
		// and add the EF_CONNECTION flag if we haven't gotten commands recently
		if ( !( ent->r.svFlags & SVF_BOT ) ) {
			client->ps.eFlags |= EF_CONNECTION;
			ent->s.eFlags |= EF_CONNECTION;
		}
	}

	if ( frames > 0 && g_smoothClients.integer ) {
		G_PredictPlayerMove( ent, (float)frames / g_fps.value );
		SnapVector( ent->s.pos.trBase );
	}

	// unlagged
	G_StoreHistory( ent );

	// hitsounds
	if ( client->damage.enemy && client->damage.amount ) {
		client->ps.persistant[PERS_HITS] += client->damage.enemy;
		client->damage.enemy = 0;
		// scale damage by max.health
		i = client->damage.amount * 100 / client->ps.stats[STAT_MAX_HEALTH];
		// avoid high-byte setup
		if ( i > 255 )
			i = 255;
		client->ps.persistant[PERS_ATTACKEE_ARMOR] = i;
		client->damage.amount = 0;
	} else if ( client->damage.team ) {
		client->ps.persistant[PERS_HITS] -= client->damage.team;
		client->damage.team = 0;
	}

	// set the bit for the reachability area the client is currently in
//	i = trap_AAS_PointReachabilityAreaIndex( ent->client->ps.origin );
//	ent->client->areabits[i >> 3] |= 1 << (i & 7);
}
