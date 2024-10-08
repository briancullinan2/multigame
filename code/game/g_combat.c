// Copyright (C) 1999-2000 Id Software, Inc.
//
// g_combat.c

#include "g_local.h"


/*
============
ScorePlum
============
*/
void ScorePlum( gentity_t *ent, vec3_t origin, int score ) {
	gentity_t *plum;

	plum = G_TempEntity( origin, EV_SCOREPLUM );
	// only send this temp entity to a single client
	plum->r.svFlags |= SVF_SINGLECLIENT;
	plum->r.singleClient = ent->s.number;
	//
	plum->s.otherEntityNum = ent->s.number;
	plum->s.time = score;
}

/*
============
AddScore

Adds score to both the client and his team
============
*/
void AddScore( gentity_t *ent, vec3_t origin, int score ) {
	if ( !ent->client ) {
		return;
	}
	// no scoring during pre-match warmup
	if ( level.warmupTime ) {
		return;
	}
	// show score plum
	ScorePlum(ent, origin, score);
	//
	ent->client->ps.persistant[PERS_SCORE] += score;
	if ( g_gametype.integer == GT_TEAM ) {
		AddTeamScore( origin, ent->client->ps.persistant[PERS_TEAM], score );
	}
	CalculateRanks();
}

gentity_t *dropWeapon( gentity_t *ent, gitem_t *item, float angle, int xr_flags );


/*
=================
TossClientItems

Toss the weapon and powerups for the killed player
=================
*/
void TossClientItems( gentity_t *self ) {
	gitem_t		*item;
	int			weapon;
	float		angle;
	int			i;
	gentity_t	*drop;

	// drop the weapon if not a gauntlet or machinegun
	weapon = self->s.weapon;

#ifdef USE_CLOAK_CMD
  if (self->flags & FL_CLOAK) {
  	// remove the invisible powerup if the player is cloaked.
#ifdef USE_ADVANCED_ITEMS
  	self->client->inventory[PW_INVIS] = level.time;
#else
  	self->client->ps.powerups[PW_INVIS] = level.time;
#endif
  } 
#endif

	// make a special check to see if they are changing to a new
	// weapon that isn't the mg or gauntlet.  Without this, a client
	// can pick up a weapon, be killed, and not drop the weapon because
	// their weapon change hasn't completed yet and they are still holding the MG.
	if ( weapon == WP_MACHINEGUN 
#ifdef USE_GRAPPLE
		|| weapon == WP_GRAPPLING_HOOK 
#endif
#ifdef USE_FLAME_THROWER
		|| weapon == WP_FLAME_THROWER
#endif
  ) {
		if ( self->client->ps.weaponstate == WEAPON_DROPPING ) {
			weapon = self->client->pers.cmd.weapon;
		}
#ifdef USE_ADVANCED_WEAPONS
		if ( !( self->client->classWeapons[weapon] ) ) {
			weapon = WP_NONE;
		}
#else
		if ( !( self->client->ps.stats[STAT_WEAPONS] & ( 1 << (weapon % WP_MAX_WEAPONS) ) ) ) {
			weapon = WP_NONE;
		}
#endif
	}

	if ( weapon > WP_MACHINEGUN && weapon != WP_GRAPPLING_HOOK && 
#ifdef USE_ADVANCED_WEAPONS
		self->client->classAmmo[ weapon ]
#ifdef USE_WEAPON_VARS
		&& self->client->classAmmo[ weapon ] != INFINITE
#endif
#else
		self->client->ps.ammo[ weapon ]
#ifdef USE_WEAPON_VARS
		&& self->client->ps.ammo[ weapon ] != INFINITE
#endif
#endif
#ifdef USE_TRINITY
    // don't drop anything in instagib mode
    && !g_unholyTrinity.integer
#endif
#ifdef USE_HOTRPG
    // don't drop anything in hot-rockets mode
    && !g_hotRockets.integer
#endif
#ifdef USE_HOTBFG
    // don't drop anything in hot-rockets mode
    && !g_hotBFG.integer
#endif
#ifdef USE_INSTAGIB
    // don't drop anything in instagib mode
    && !g_instagib.integer
#endif
#ifdef USE_PORTALS
		// don't drop portal guns
		&& (!wp_portalEnable.integer || weapon != WP_BFG)
#endif
#ifdef USE_GRAPPLE
		&& weapon != WP_GRAPPLING_HOOK 
#endif
#ifdef USE_FLAME_THROWER
		// don't drop flame thrower power-up
    && weapon != WP_FLAME_THROWER
#endif
	) {
		// find the item type for this weapon
		item = BG_FindItemForWeapon( weapon );

		// spawn the item
		drop = Drop_Item( self, item, 0 );

		// for pickup prediction
		drop->s.time2 = item->quantity;
	}

#ifdef USE_RUNES

	for(i = RUNE_STRENGTH; i <= RUNE_LITHIUM; i++) {
		if(self->client->inventory[i]) {
			gitem_t *item = BG_FindItemForRune(i - RUNE_STRENGTH);
			if(!item) continue;
			dropWeapon( self, item, 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
			self->client->inventory[i] = 0;
			self->client->inventoryModified[(int)floor(i / PW_MAX_POWERUPS)] = qtrue;
		}
	}

#endif

	// drop all the powerups if not in teamplay
	if ( g_gametype.integer != GT_TEAM ) {
		angle = 45;
		for ( i = 1 ; i < MAX_POWERUPS ; i++ ) {
			if ( 
#ifdef USE_ADVANCED_ITEMS
				self->client->inventory[ i ] > level.time 
#else
				self->client->ps.powerups[ i ] > level.time 
#endif
			) {
				item = BG_FindItemForPowerup( i );
				if ( !item ) {
					continue;
				}
				drop = Drop_Item( self, item, angle );
				// decide how many seconds it has left
#ifdef USE_ADVANCED_ITEMS
				drop->count = ( self->client->inventory[ i ] - level.time ) / 1000;
#else
				drop->count = ( self->client->ps.powerups[ i ] - level.time ) / 1000;
#endif
				if ( drop->count < 1 ) {
					drop->count = 1;
				}
				// for pickup prediction
				drop->s.time2 = drop->count;
				angle += 45;
			}
		}
	}
}


#ifdef MISSIONPACK
/*
=================
TossClientCubes
=================
*/
extern gentity_t	*neutralObelisk;

void TossClientCubes( gentity_t *self ) {
	gitem_t		*item;
	gentity_t	*drop;
	vec3_t		velocity;
	vec3_t		angles;
	vec3_t		origin;

	self->client->ps.generic1 = 0;

	// this should never happen but we should never
	// get the server to crash due to skull being spawned in
	if (!G_EntitiesFree()) {
		return;
	}

	if( self->client->sess.sessionTeam == TEAM_RED ) {
		item = BG_FindItem( "Red Cube" );
	}
	else {
		item = BG_FindItem( "Blue Cube" );
	}

	angles[YAW] = (float)(level.time % 360);
	angles[PITCH] = 0;	// always forward
	angles[ROLL] = 0;

	AngleVectors( angles, velocity, NULL, NULL );
	VectorScale( velocity, 150, velocity );
	velocity[2] += 200 + crandom() * 50;

	if( neutralObelisk ) {
		VectorCopy( neutralObelisk->s.pos.trBase, origin );
		origin[2] += 44;
	} else {
		VectorClear( origin ) ;
	}

#ifdef USE_WEAPON_DROP
  drop = LaunchItem( item, origin, velocity, FL_DROPPED_ITEM );
#else
	drop = LaunchItem( item, origin, velocity );
#endif

	drop->nextthink = level.time + g_cubeTimeout.integer * 1000;
	drop->think = G_FreeEntity;
	drop->spawnflags = self->client->sess.sessionTeam;
}

#endif



#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS)


/*
=================
TossClientPersistantPowerups
=================
*/
void TossClientPersistantPowerups( gentity_t *ent ) {
	gentity_t	*powerup;

	if( !ent->client ) {
		return;
	}

	if( !ent->client->persistantPowerup ) {
		return;
	}

	powerup = ent->client->persistantPowerup;

	powerup->r.svFlags &= ~SVF_NOCLIENT;
	powerup->s.eFlags &= ~EF_NODRAW;
	powerup->r.contents = CONTENTS_TRIGGER;
	trap_LinkEntity( powerup );

#ifdef USE_ADVANCED_ITEMS
	ent->client->inventory[powerup->item->giTag] = 0;
#else
	ent->client->ps.stats[STAT_PERSISTANT_POWERUP] = 0;
#endif
	ent->client->persistantPowerup = NULL;
}
#endif


/*
==================
LookAtKiller
==================
*/
void LookAtKiller( gentity_t *self, gentity_t *inflictor, gentity_t *attacker ) {
	vec3_t		dir;

	if ( attacker && attacker != self ) {
		VectorSubtract (attacker->s.pos.trBase, self->s.pos.trBase, dir);
	} else if ( inflictor && inflictor != self ) {
		VectorSubtract (inflictor->s.pos.trBase, self->s.pos.trBase, dir);
	} else {
		self->client->ps.stats[STAT_DEAD_YAW] = self->s.angles[YAW];
		return;
	}

	self->client->ps.stats[STAT_DEAD_YAW] = vectoyaw ( dir );
}

/*
==================
GibEntity
==================
*/
void GibEntity( gentity_t *self, int killer ) {
#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS) || defined(USE_RUNES)
	gentity_t *ent;
	int i;

	//if this entity still has kamikaze
	if (self->s.eFlags & EF_KAMIKAZE) {
		// check if there is a kamikaze timer around for this owner
		for (i = 0; i < level.num_entities; i++) {
			ent = &g_entities[i];
			if (!ent->inuse)
				continue;
			if (ent->activator != self)
				continue;
			if (strcmp(ent->classname, "kamikaze timer"))
				continue;
			G_FreeEntity(ent);
			break;
		}
	}
#endif

	G_AddEvent( self, EV_GIB_PLAYER, killer );
	self->takedamage = qfalse;
	self->s.eType = ET_INVISIBLE;
	self->r.contents = 0;
}

/*
==================
body_die
==================
*/
void body_die( gentity_t *self, gentity_t *inflictor, gentity_t *attacker, int damage, int meansOfDeath ) {
	if ( self->health > GIB_HEALTH ) {
		return;
	}
	if ( !g_blood.integer ) {
		self->health = GIB_HEALTH+1;
		return;
	}

	GibEntity( self, 0 );
}


// these are just for logging, the client prints its own messages
char	*modNames[] = {
	"MOD_UNKNOWN",
	"MOD_SHOTGUN",
	"MOD_GAUNTLET",
	"MOD_MACHINEGUN",
	"MOD_GRENADE",
	"MOD_GRENADE_SPLASH",
	"MOD_ROCKET",
	"MOD_ROCKET_SPLASH",
	"MOD_PLASMA",
	"MOD_PLASMA_SPLASH",
	"MOD_RAILGUN",
	"MOD_LIGHTNING",
	"MOD_BFG",
	"MOD_BFG_SPLASH",
	"MOD_WATER",
	"MOD_SLIME",
	"MOD_LAVA",
	"MOD_CRUSH",
	"MOD_TELEFRAG",
	"MOD_FALLING",
	"MOD_SUICIDE",
	"MOD_TARGET_LASER",
	"MOD_TRIGGER_HURT",
#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS)
	"MOD_NAIL",
	"MOD_CHAINGUN",
	"MOD_PROXIMITY_MINE",
	"MOD_KAMIKAZE",
	"MOD_JUICED",
#ifdef USE_FLAME_THROWER
  "MOD_FLAME_THROWER",
#endif
#endif
#ifdef USE_LV_DISCHARGE
  "MOD_LV_DISCHARGE",
#endif
#ifdef USE_HEADSHOTS
  "MOD_HEADSHOT",
#endif
#ifdef USE_HEADSHOTS
  "MOD_HEADSHOT",
#endif
	"MOD_GRAPPLE"
#ifdef USE_VEHICLES
	"MOD_HIGH_FORCES",
	"MOD_BO_SHOCKS",
	"MOD_WORLD_COLLISION",
#endif
#ifdef USE_RUNES
	"MOD_RUNE_STRENGTH",
	"MOD_RUNE_BERSERK",
	"MOD_RUNE_PIERCING",
	"MOD_RUNE_DIVINITY",
#endif
};

#ifdef USE_PORTALS
void PortalDestroy( gentity_t *self );
#endif
#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS) || defined(USE_RUNES)
/*
==================
Kamikaze_DeathActivate
==================
*/
void Kamikaze_DeathActivate( gentity_t *ent ) {
	G_StartKamikaze(ent);
	G_FreeEntity(ent);
}

/*
==================
Kamikaze_DeathTimer
==================
*/
void Kamikaze_DeathTimer( gentity_t *self ) {
	gentity_t *ent;

	ent = G_Spawn();
	ent->classname = "kamikaze timer";
	VectorCopy(self->s.pos.trBase, ent->s.pos.trBase);
	ent->r.svFlags |= SVF_NOCLIENT;
	ent->think = Kamikaze_DeathActivate;
	ent->nextthink = level.time + 5 * 1000;

	ent->activator = self;
}

#endif

/*
==================
CheckAlmostCapture
==================
*/
void CheckAlmostCapture( gentity_t *self, gentity_t *attacker ) {
	gentity_t	*ent;
	vec3_t		dir;
	char		*classname;

	// if this player was carrying a flag
	if ( 
#ifdef USE_ADVANCED_ITEMS
		self->client->inventory[PW_REDFLAG] ||
		self->client->inventory[PW_BLUEFLAG] ||
		self->client->inventory[PW_NEUTRALFLAG] 
#else
		self->client->ps.powerups[PW_REDFLAG] ||
		self->client->ps.powerups[PW_BLUEFLAG] ||
		self->client->ps.powerups[PW_NEUTRALFLAG] 
#endif
	) {
		// get the goal flag this player should have been going for
		if ( g_gametype.integer == GT_CTF ) {
			if ( self->client->sess.sessionTeam == TEAM_BLUE ) {
				classname = "team_CTF_blueflag";
			}
			else {
				classname = "team_CTF_redflag";
			}
		}
		else {
			if ( self->client->sess.sessionTeam == TEAM_BLUE ) {
				classname = "team_CTF_redflag";
			}
			else {
				classname = "team_CTF_blueflag";
			}
		}
		ent = NULL;
		do
		{
			ent = G_Find(ent, FOFS(classname), classname);
		} while (ent && (ent->flags & FL_DROPPED_ITEM));
		// if we found the destination flag and it's not picked up
		if (ent && !(ent->r.svFlags & SVF_NOCLIENT) ) {
			// if the player was *very* close
			VectorSubtract( self->client->ps.origin, ent->s.origin, dir );
			if ( VectorLength(dir) < 200 ) {
				self->client->ps.persistant[PERS_PLAYEREVENTS] ^= PLAYEREVENT_HOLYSHIT;
				if ( attacker->client ) {
					attacker->client->ps.persistant[PERS_PLAYEREVENTS] ^= PLAYEREVENT_HOLYSHIT;
				}
			}
		}
	}
}

/*
==================
CheckAlmostScored
==================
*/
void CheckAlmostScored( gentity_t *self, gentity_t *attacker ) {
	gentity_t	*ent;
	vec3_t		dir;
	char		*classname;

	// if the player was carrying cubes
	if ( self->client->ps.generic1 ) {
		if ( self->client->sess.sessionTeam == TEAM_BLUE ) {
			classname = "team_redobelisk";
		}
		else {
			classname = "team_blueobelisk";
		}
		ent = G_Find(NULL, FOFS(classname), classname);
		// if we found the destination obelisk
		if ( ent ) {
			// if the player was *very* close
			VectorSubtract( self->client->ps.origin, ent->s.origin, dir );
			if ( VectorLength(dir) < 200 ) {
				self->client->ps.persistant[PERS_PLAYEREVENTS] ^= PLAYEREVENT_HOLYSHIT;
				if ( attacker->client ) {
					attacker->client->ps.persistant[PERS_PLAYEREVENTS] ^= PLAYEREVENT_HOLYSHIT;
				}
			}
		}
	}
}



#if defined(USE_DAMAGE_PLUMS) || defined(USE_RUNES)
void player_pain(gentity_t *self, gentity_t *attacker, int damage) {
  gentity_t *plum;

  if ( self->client->ps.pm_type == PM_DEAD ) {
		return;
	}

#ifdef USE_RUNES
  if ( !attacker || !attacker->client || (self->client == attacker->client && !self->client->inventory[RUNE_CLOAK]) ) {
    return;
  }
#else
  if ( !attacker || !attacker->client || self->client == attacker->client ) {
    return;
  }
#endif


  plum = G_TempEntity( self->r.currentOrigin, EV_DAMAGEPLUM );
  // only send this temp entity to a single client
#ifdef USE_RUNES
	if(self->client->inventory[RUNE_CLOAK]) {
		// ironically, broadcast to make them blink uninvisible
		plum->r.svFlags |= SVF_BROADCAST;
		plum->r.singleClient = 0;
	} else {
#endif
  plum->r.svFlags |= SVF_SINGLECLIENT;
  plum->r.singleClient = attacker->s.number;
#ifdef USE_RUNES
	}
#endif
  //
  plum->s.otherEntityNum2 = attacker->s.number;
  plum->s.otherEntityNum = self->s.number;
  plum->s.time = damage;
}
#endif



#ifdef USE_GAME_FREEZETAG

void CheckFrozen( void ) {
	int redCount = 0, blueCount = 0, frozenCount = 0, clientCount = 0;
	int redTeam = 0, blueTeam = 0;
	gentity_t	*lastAlive;
	gentity_t	*ent;
	int i;
	qboolean unfreezeAll = qfalse;

	ent = &g_entities[0];
	for (i=0 ; i<MAX_CLIENTS ; i++, ent++) {
		if ( !ent->inuse ) {
			continue;
		}
		if ( !ent->r.linked ) {
			continue;
		}
		if( ent->client->pers.connected == CON_CONNECTED ) {
			clientCount++;
			if (ent->client->sess.sessionTeam == TEAM_RED) {
				redTeam++;
#ifdef USE_ADVANCED_ITEMS
				if(ent->client->inventory[PW_FROZEN]) 
#else
				if(ent->client->ps.powerups[PW_FROZEN]) 
#endif
				{
					redCount++;
				}
			} 
			if (ent->client->sess.sessionTeam == TEAM_BLUE) {
				blueTeam++;
#ifdef USE_ADVANCED_ITEMS
				if(ent->client->inventory[PW_FROZEN]) 
#else
				if(ent->client->ps.powerups[PW_FROZEN]) 
#endif
				{
					blueCount++;
				}
			}
#ifdef USE_ADVANCED_ITEMS
			if (ent->client->inventory[PW_FROZEN] ) 
#else
			if (ent->client->ps.powerups[PW_FROZEN] ) 
#endif
			{
				frozenCount++;
			} else {
				lastAlive = ent;
			}
		}
	}

	if(frozenCount > 0 && frozenCount == clientCount - 1) {
		AddScore(lastAlive, lastAlive->r.currentOrigin, frozenCount);
		unfreezeAll = qtrue;
	}
	if(!(redTeam == 0 || blueTeam == 0)) {
		if(redCount == clientCount || redCount == redTeam ) {
			AddScore(lastAlive, lastAlive->r.currentOrigin, redCount);
			unfreezeAll = qtrue;
		}
		if(blueCount == clientCount || blueCount == blueTeam) {
			AddScore(lastAlive, lastAlive->r.currentOrigin, blueCount);
			unfreezeAll = qtrue;
		}
	}

	if(unfreezeAll) {
		ent = &g_entities[0];
		for (i=0 ; i<MAX_CLIENTS ; i++, ent++) {
			if(ent->inuse && ent->client && (
#ifdef USE_ADVANCED_ITEMS
				ent->client->inventory[PW_FROZEN]
#else
				ent->client->ps.powerups[PW_FROZEN]
#endif
				|| ent->client->ps.pm_type == PM_FROZEN)) {
				G_AddEvent( ent, EV_UNFROZEN, 0 );
				// TODO: decide if they die or gib or come back to life
				ent->client->ps.pm_type = PM_DEAD;
				ent->client->ps.stats[STAT_HEALTH] = 0;
#ifdef USE_ADVANCED_ITEMS
				ent->client->inventory[PW_FROZEN] = 0;
#else
				ent->client->ps.powerups[PW_FROZEN] = 0;
#endif
				ent->health = 0;
				//SetClientViewAngle(ent, ent->client->frozen_angles);
			}
		}
	}


}


void player_frozen(gentity_t *self, int killer) {
  gentity_t *plum;

	if(!g_freezeTag.integer) {
		return;
	}

  if ( self->client->ps.pm_type != PM_DEAD
		&& self->client->ps.pm_type != PM_FROZEN ) {
		return;
	}

	plum = G_TempEntity( self->r.currentOrigin, EV_DAMAGEPLUM );
#ifdef USE_ADVANCED_ITEMS
	plum->s.time2 = g_thawTime.integer - (level.time - self->client->inventory[PW_FROZEN]) / 1000.0f;
#else
	plum->s.time2 = g_thawTime.integer - (level.time - self->client->ps.powerups[PW_FROZEN]) / 1000.0f;
#endif
  plum->s.otherEntityNum = self->s.number;
	plum->r.svFlags |= SVF_BROADCAST;
	self->client->lastFreezeTime = level.time;

	CheckFrozen();

  if ( self->client->ps.pm_type == PM_FROZEN ) {
		return;
	}

	self->client->ps.pm_type = PM_FROZEN;
	self->client->ps.torsoAnim = TORSO_STAND;
	self->client->ps.legsAnim = LEGS_IDLE;

#ifdef USE_ADVANCED_ITEMS
	self->client->inventory[PW_FROZEN] = level.time + g_thawTime.integer * 1000;
#else
	self->client->ps.powerups[PW_FROZEN] = level.time + g_thawTime.integer * 1000;
#endif

	self->takedamage = qfalse;	// can still be gibbed
	self->health = INFINITE;
	self->client->ps.stats[STAT_HEALTH] = INFINITE;

	G_AddEvent( self, EV_FROZEN, killer );

}
#endif



/*
==================
player_die
==================
*/
void player_die( gentity_t *self, gentity_t *inflictor, gentity_t *attacker, int damage, int meansOfDeath ) {
	gentity_t	*ent;
	int			anim;
	int			contents;
	int			killer;
	int			i;
	char		*killerName, *obit;

	if ( self->client->ps.pm_type == PM_DEAD ) {
		return;
	}

	if ( level.intermissiontime ) {
		return;
	}

#ifdef USE_BIRDS_EYE
	if(self->client->cursorEnt) {
		trap_UnlinkEntity(self->client->cursorEnt);
		G_FreeEntity(self->client->cursorEnt);
		self->client->cursorEnt = NULL;
	}
#endif

	//unlag the client
	G_UnTimeShiftClient( self );

	// check for an almost capture
	CheckAlmostCapture( self, attacker );
	// check for a player that almost brought in cubes
	CheckAlmostScored( self, attacker );

#ifdef USE_GRAPPLE
	if (self->client && self->client->hook) {
		Weapon_HookFree(self->client->hook);
	}
#endif
#ifdef MISSIONPACK
	if ((self->client->ps.eFlags & EF_TICKING) && self->activator) {
		self->client->ps.eFlags &= ~EF_TICKING;
		self->activator->think = G_FreeEntity;
		self->activator->nextthink = level.time;
	}
#endif

	self->client->ps.pm_type = PM_DEAD;

	if ( attacker ) {
		killer = attacker->s.number;
		if ( attacker->client ) {
			killerName = attacker->client->pers.netname;
		} else {
			killerName = "<non-client>";
		}
	} else {
		killer = ENTITYNUM_WORLD;
		killerName = "<world>";
	}
#ifdef USE_MODES_DEATH
  if (attacker && attacker->health < 0 ) {
    meansOfDeath = MOD_FROM_GRAVE;
  }
  if (level.time - self->splashTime < 4000
    && meansOfDeath == MOD_VOID) {
    attacker = self->splashAttacker;
    killer = self->splashAttacker->s.number;
    killerName = self->splashAttacker->client->pers.netname;
    meansOfDeath = MOD_RING_OUT;
	}
#endif

	if ( killer < 0 || killer >= MAX_CLIENTS ) {
		killer = ENTITYNUM_WORLD;
		killerName = "<world>";
	}

	if ( (unsigned)meansOfDeath >= ARRAY_LEN( modNames ) ) {
		obit = "<bad obituary>";
	} else {
		obit = modNames[ meansOfDeath ];
	}

	G_LogPrintf("Kill: %i %i %i: %s killed %s by %s\n", 
		killer, self->s.number, meansOfDeath, killerName, 
		self->client->pers.netname, obit );

	// broadcast the death event to everyone
	ent = G_TempEntity( self->r.currentOrigin, EV_OBITUARY );
	ent->s.eventParm = meansOfDeath;
	ent->s.otherEntityNum = self - g_entities;
	ent->s.otherEntityNum2 = killer;
	ent->r.svFlags = SVF_BROADCAST;	// send to everyone

	self->enemy = attacker;

	self->client->ps.persistant[PERS_KILLED]++;

	if (attacker && attacker->client) {
		attacker->client->lastkilled_client = self->s.number;

		if ( attacker == self || OnSameTeam (self, attacker ) ) {
			AddScore( attacker, self->r.currentOrigin, -1 );
		} else {
#ifdef USE_MODES_DEATH
      if(meansOfDeath == MOD_RING_OUT) {
        AddScore( self, self->r.currentOrigin, -1 );
      }
#endif
			AddScore( attacker, self->r.currentOrigin, 1 );

			if( meansOfDeath == MOD_GAUNTLET ) {
				
				// play humiliation on player
				attacker->client->ps.persistant[PERS_GAUNTLET_FRAG_COUNT]++;

				// add the sprite over the player's head
				attacker->client->ps.eFlags &= ~(EF_AWARD_IMPRESSIVE | EF_AWARD_EXCELLENT | EF_AWARD_GAUNTLET | EF_AWARD_ASSIST | EF_AWARD_DEFEND | EF_AWARD_CAP );
				attacker->client->ps.eFlags |= EF_AWARD_GAUNTLET;
				attacker->client->rewardTime = level.time + REWARD_SPRITE_TIME;

				// also play humiliation on target
				self->client->ps.persistant[PERS_PLAYEREVENTS] ^= PLAYEREVENT_GAUNTLETREWARD;
			}

			// check for two kills in a short amount of time
			// if this is close enough to the last kill, give a reward sound
			if ( level.time - attacker->client->lastKillTime < CARNAGE_REWARD_TIME ) {
				// play excellent on player
				attacker->client->ps.persistant[PERS_EXCELLENT_COUNT]++;

				// add the sprite over the player's head
				attacker->client->ps.eFlags &= ~(EF_AWARD_IMPRESSIVE | EF_AWARD_EXCELLENT | EF_AWARD_GAUNTLET | EF_AWARD_ASSIST | EF_AWARD_DEFEND | EF_AWARD_CAP );
				attacker->client->ps.eFlags |= EF_AWARD_EXCELLENT;
				attacker->client->rewardTime = level.time + REWARD_SPRITE_TIME;
			}
			attacker->client->lastKillTime = level.time;

		}
	} else {
		AddScore( self, self->r.currentOrigin, -1 );
	}

	// Add team bonuses
	Team_FragBonuses(self, inflictor, attacker);

	// if I committed suicide, the flag does not fall, it returns.
	if (meansOfDeath == MOD_SUICIDE
#ifdef USE_MODES_DEATH
		|| meansOfDeath == MOD_SPECTATE
#endif
	) {
#ifdef MISSIONPACK
#ifdef USE_ADVANCED_ITEMS
		if ( self->client->inventory[PW_NEUTRALFLAG] ) {		// only happens in One Flag CTF
			Team_ReturnFlag( TEAM_FREE );
			self->client->inventory[PW_NEUTRALFLAG] = 0;
			self->client->inventoryModified[(int)floor(PW_NEUTRALFLAG / PW_MAX_POWERUPS)] = 0;
		} else 
#else
		if ( self->client->ps.powerups[PW_NEUTRALFLAG] ) {		// only happens in One Flag CTF
			Team_ReturnFlag( TEAM_FREE );
			self->client->ps.powerups[PW_NEUTRALFLAG] = 0;
		} else 
#endif
#endif
#ifdef USE_ADVANCED_ITEMS
		if ( self->client->inventory[PW_REDFLAG] ) {		// only happens in standard CTF
			Team_ReturnFlag( TEAM_RED );
			self->client->inventory[PW_REDFLAG] = 0;
		}
		else if ( self->client->inventory[PW_BLUEFLAG] ) {	// only happens in standard CTF
			Team_ReturnFlag( TEAM_BLUE );
			self->client->inventory[PW_BLUEFLAG] = 0;
		}
#if defined(USE_ADVANCED_GAMES) || defined(USE_ADVANCED_TEAMS)
		else if ( self->client->inventory[PW_GOLDFLAG] ) {		// only happens in standard CTF
			Team_ReturnFlag( TEAM_GOLD );
			self->client->inventory[PW_GOLDFLAG] = 0;
		}
		else if ( self->client->inventory[PW_GREENFLAG] ) {	// only happens in standard CTF
			Team_ReturnFlag( TEAM_GREEN );
			self->client->inventory[PW_GREENFLAG] = 0;
		}
#endif
#else
		if ( self->client->ps.powerups[PW_REDFLAG] ) {		// only happens in standard CTF
			Team_ReturnFlag( TEAM_RED );
			self->client->ps.powerups[PW_REDFLAG] = 0;
		}
		else if ( self->client->ps.powerups[PW_BLUEFLAG] ) {	// only happens in standard CTF
			Team_ReturnFlag( TEAM_BLUE );
			self->client->ps.powerups[PW_BLUEFLAG] = 0;
		}
#if defined(USE_ADVANCED_GAMES) || defined(USE_ADVANCED_TEAMS)
		else if ( self->client->ps.powerups[PW_GOLDFLAG] ) {		// only happens in standard CTF
			Team_ReturnFlag( TEAM_GOLD );
			self->client->ps.powerups[PW_GOLDFLAG] = 0;
		}
		else if ( self->client->ps.powerups[PW_GREENFLAG] ) {	// only happens in standard CTF
			Team_ReturnFlag( TEAM_GREEN );
			self->client->ps.powerups[PW_GREENFLAG] = 0;
		}
#endif
#endif
	}

	// if client is in a nodrop area, don't drop anything (but return CTF flags!)
	contents = trap_PointContents( self->r.currentOrigin, -1 );
	if ( !( contents & CONTENTS_NODROP )) {
		TossClientItems( self );
	}
	else {
#ifdef USE_ADVANCED_ITEMS
		if ( self->client->inventory[PW_NEUTRALFLAG] ) {		// only happens in One Flag CTF
			Team_ReturnFlag( TEAM_FREE );
		}
		else if ( self->client->inventory[PW_REDFLAG] ) {		// only happens in standard CTF
			Team_ReturnFlag( TEAM_RED );
		}
		else if ( self->client->inventory[PW_BLUEFLAG] ) {	// only happens in standard CTF
			Team_ReturnFlag( TEAM_BLUE );
		}
#if defined(USE_ADVANCED_GAMES) || defined(USE_ADVANCED_TEAMS)
		else if ( self->client->inventory[PW_GOLDFLAG] ) {		// only happens in standard CTF
			Team_ReturnFlag( TEAM_GOLD );
		}
		else if ( self->client->inventory[PW_GREENFLAG] ) {	// only happens in standard CTF
			Team_ReturnFlag( TEAM_GREEN );
		}
#endif
#else
		if ( self->client->ps.powerups[PW_NEUTRALFLAG] ) {		// only happens in One Flag CTF
			Team_ReturnFlag( TEAM_FREE );
		}
		else if ( self->client->ps.powerups[PW_REDFLAG] ) {		// only happens in standard CTF
			Team_ReturnFlag( TEAM_RED );
		}
		else if ( self->client->ps.powerups[PW_BLUEFLAG] ) {	// only happens in standard CTF
			Team_ReturnFlag( TEAM_BLUE );
		}
#if defined(USE_ADVANCED_GAMES) || defined(USE_ADVANCED_TEAMS)
		else if ( self->client->ps.powerups[PW_GOLDFLAG] ) {		// only happens in standard CTF
			Team_ReturnFlag( TEAM_GOLD );
		}
		else if ( self->client->ps.powerups[PW_GREENFLAG] ) {	// only happens in standard CTF
			Team_ReturnFlag( TEAM_GREEN );
		}
#endif
#endif
	}
#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS)
	TossClientPersistantPowerups( self );
#ifdef MISSIONPACK // TODO || USE_ADVANCED_GAMES
	if( g_gametype.integer == GT_HARVESTER ) {
		TossClientCubes( self );
	}
#endif
#endif

	Cmd_Score_f( self );		// show scores
	// send updated scores to any clients that are following this one,
	// or they would get stale scoreboards
	for ( i = 0 ; i < level.maxclients ; i++ ) {
		gclient_t	*client;

		client = &level.clients[i];
		if ( client->pers.connected != CON_CONNECTED ) {
			continue;
		}
		if ( client->sess.sessionTeam != TEAM_SPECTATOR ) {
			continue;
		}
		if ( client->sess.spectatorClient == self->s.number ) {
			Cmd_Score_f( g_entities + i );
		}
	}

#ifdef USE_GAME_FREEZETAG
	if(!g_freezeTag.integer || meansOfDeath == MOD_TRIGGER_HURT || meansOfDeath == MOD_VOID) {
#endif

	self->takedamage = qtrue;	// can still be gibbed

	self->s.weapon = WP_NONE;
	self->s.powerups = 0;
	self->r.contents = CONTENTS_CORPSE;

	self->s.angles[0] = 0;
	self->s.angles[2] = 0;
	LookAtKiller (self, inflictor, attacker);

	VectorCopy( self->s.angles, self->client->ps.viewangles );

	self->s.loopSound = 0;

	self->r.maxs[2] = -8;

	// don't allow respawn until the death anim is done
	// g_forcerespawn may force spawning at some later time
	self->client->respawnTime = level.time + 1700;

	// remove powerups
#ifdef USE_ADVANCED_ITEMS
	memset( self->client->inventory, 0, sizeof( self->client->inventory ) );
	memset( self->client->inventoryModified, 1, sizeof( self->client->inventoryModified ) );
	memset( self->client->ps.powerTimes, 0, sizeof(self->client->ps.powerTimes) );
#else
	memset( self->client->ps.powerups, 0, sizeof(self->client->ps.powerups) );
#endif

#ifdef USE_PORTALS
  if(self->client->portalDestination) {
    PortalDestroy(self->client->portalDestination);
  }
#endif

	// never gib in a nodrop
	if ( (self->health <= GIB_HEALTH && !(contents & CONTENTS_NODROP)
    && g_blood.integer
#ifdef USE_HEADSHOTS
    && meansOfDeath != MOD_HEADSHOT
#endif
    ) || meansOfDeath == MOD_SUICIDE
#ifdef USE_MODES_DEATH
		|| meansOfDeath == MOD_SPECTATE
#endif
  ) {
		// gib death
		GibEntity( self, killer );
	} else {
		// normal death
		static int i;

		switch ( i ) {
		case 0:
			anim = BOTH_DEATH1;
			break;
		case 1:
			anim = BOTH_DEATH2;
			break;
		case 2:
		default:
			anim = BOTH_DEATH3;
			break;
		}

		// for the no-blood option, we need to prevent the health
		// from going to gib level
		if ( self->health <= GIB_HEALTH ) {
			self->health = GIB_HEALTH+1;
		}

		self->client->ps.legsAnim = 
			( ( self->client->ps.legsAnim & ANIM_TOGGLEBIT ) ^ ANIM_TOGGLEBIT ) | anim;
		self->client->ps.torsoAnim = 
			( ( self->client->ps.torsoAnim & ANIM_TOGGLEBIT ) ^ ANIM_TOGGLEBIT ) | anim;

#ifdef USE_HEADSHOTS
    if(meansOfDeath == MOD_HEADSHOT) {
      G_AddEvent( self, EV_GIB_PLAYER_HEADSHOT, killer );
    } else
#endif
		G_AddEvent( self, EV_DEATH1 + i, killer );

		// the body can still be gibbed
		self->die = body_die;

		// globally cycle through the different death animations
		i = ( i + 1 ) % 3;

#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS) || defined(USE_RUNES)
		if (self->s.eFlags & EF_KAMIKAZE) {
			Kamikaze_DeathTimer( self );
		}
#endif
	}

#ifdef USE_GAME_FREEZETAG
	} else {
		player_frozen(self, killer);
	}
#endif

	trap_LinkEntity (self);

}


/*
================
CheckArmor
================
*/
int CheckArmor (gentity_t *ent, int damage, int dflags)
{
	gclient_t	*client;
	int			save;
	int			count;

	if (!damage)
		return 0;

	client = ent->client;

	if (!client)
		return 0;

	if (dflags & DAMAGE_NO_ARMOR)
		return 0;

	// armor
	count = client->ps.stats[STAT_ARMOR];
	save = ceil( damage * ARMOR_PROTECTION );
	if (save >= count)
		save = count;

	if (!save)
		return 0;

	client->ps.stats[STAT_ARMOR] -= save;

	return save;
}

/*
================
RaySphereIntersections
================
*/
int RaySphereIntersections( vec3_t origin, float radius, vec3_t point, vec3_t dir, vec3_t intersections[2] ) {
	float b, c, d, t;

	//	| origin - (point + t * dir) | = radius
	//	a = dir[0]^2 + dir[1]^2 + dir[2]^2;
	//	b = 2 * (dir[0] * (point[0] - origin[0]) + dir[1] * (point[1] - origin[1]) + dir[2] * (point[2] - origin[2]));
	//	c = (point[0] - origin[0])^2 + (point[1] - origin[1])^2 + (point[2] - origin[2])^2 - radius^2;

	// normalize dir so a = 1
	VectorNormalize(dir);
	b = 2 * (dir[0] * (point[0] - origin[0]) + dir[1] * (point[1] - origin[1]) + dir[2] * (point[2] - origin[2]));
	c = (point[0] - origin[0]) * (point[0] - origin[0]) +
		(point[1] - origin[1]) * (point[1] - origin[1]) +
		(point[2] - origin[2]) * (point[2] - origin[2]) -
		radius * radius;

	d = b * b - 4 * c;
	if (d > 0) {
		t = (- b + sqrt(d)) / 2;
		VectorMA(point, t, dir, intersections[0]);
		t = (- b - sqrt(d)) / 2;
		VectorMA(point, t, dir, intersections[1]);
		return 2;
	}
	else if (d == 0) {
		t = (- b ) / 2;
		VectorMA(point, t, dir, intersections[0]);
		return 1;
	}
	return 0;
}

#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS) || defined(USE_ADVANCED_ITEMS) || defined(USE_RUNES)
/*
================
G_InvulnerabilityEffect
================
*/
int G_InvulnerabilityEffect( gentity_t *targ, vec3_t dir, vec3_t point, vec3_t impactpoint, vec3_t bouncedir ) {
	gentity_t	*impact;
	vec3_t		intersections[2], vec;
	int			n;

	if ( !targ->client ) {
		return qfalse;
	}
	VectorCopy(dir, vec);
	VectorInverse(vec);
	// sphere model radius = 42 units
	n = RaySphereIntersections( targ->client->ps.origin, 42, point, vec, intersections);
	if (n > 0) {
		impact = G_TempEntity( targ->client->ps.origin, EV_INVUL_IMPACT );
		VectorSubtract(intersections[0], targ->client->ps.origin, vec);
		vectoangles(vec, impact->s.angles);
		impact->s.angles[0] += 90;
		if (impact->s.angles[0] > 360)
			impact->s.angles[0] -= 360;
		if ( impactpoint ) {
			VectorCopy( intersections[0], impactpoint );
		}
		if ( bouncedir ) {
			VectorCopy( vec, bouncedir );
			VectorNormalize( bouncedir );
		}
		return qtrue;
	}
	else {
		return qfalse;
	}
}
#endif


#ifdef USE_LOCAL_DMG
/* 
============
G_LocationDamage
============
*/
int G_LocationDamage(vec3_t point, gentity_t* targ, gentity_t* attacker, int take) {
	vec3_t bulletPath;
	vec3_t bulletAngle;

	int clientHeight;
	int clientFeetZ;
	int clientRotation;
	int bulletHeight;
	int bulletRotation;	// Degrees rotation around client.
				// used to check Back of head vs. Face
	int impactRotation;


	// First things first.  If we're not damaging them, why are we here? 
	if (!take) 
		return 0;
    
	// Point[2] is the REAL world Z. We want Z relative to the clients feet
	
	// Where the feet are at [real Z]
	clientFeetZ  = targ->r.currentOrigin[2] + targ->r.mins[2];	
	// How tall the client is [Relative Z]
	clientHeight = targ->r.maxs[2] - targ->r.mins[2];
	// Where the bullet struck [Relative Z]
	bulletHeight = point[2] - clientFeetZ;

	// Get a vector aiming from the client to the bullet hit 
	VectorSubtract(targ->r.currentOrigin, point, bulletPath); 
	// Convert it into PITCH, ROLL, YAW
	vectoangles(bulletPath, bulletAngle);

	clientRotation = targ->client->ps.viewangles[YAW];
	bulletRotation = bulletAngle[YAW];

	impactRotation = abs(clientRotation-bulletRotation);
	
	impactRotation += 45; // just to make it easier to work with
	impactRotation = impactRotation % 360; // Keep it in the 0-359 range

	if (impactRotation < 90)
		targ->client->lasthurt_location = LOCATION_BACK;
	else if (impactRotation < 180)
		targ->client->lasthurt_location = LOCATION_RIGHT;
	else if (impactRotation < 270)
		targ->client->lasthurt_location = LOCATION_FRONT;
	else if (impactRotation < 360)
		targ->client->lasthurt_location = LOCATION_LEFT;
	else
		targ->client->lasthurt_location = LOCATION_NONE;

	// The upper body never changes height, just distance from the feet
		if (bulletHeight > clientHeight - 2)
			targ->client->lasthurt_location |= LOCATION_HEAD;
		else if (bulletHeight > clientHeight - 8)
			targ->client->lasthurt_location |= LOCATION_FACE;
		else if (bulletHeight > clientHeight - 10)
			targ->client->lasthurt_location |= LOCATION_SHOULDER;
		else if (bulletHeight > clientHeight - 16)
			targ->client->lasthurt_location |= LOCATION_CHEST;
		else if (bulletHeight > clientHeight - 26)
			targ->client->lasthurt_location |= LOCATION_STOMACH;
		else if (bulletHeight > clientHeight - 29)
			targ->client->lasthurt_location |= LOCATION_GROIN;
		else if (bulletHeight < 4)
			targ->client->lasthurt_location |= LOCATION_FOOT;
		else
			// The leg is the only thing that changes size when you duck,
			// so we check for every other parts RELATIVE location, and
			// whats left over must be the leg. 
			targ->client->lasthurt_location |= LOCATION_LEG; 


		
		// Check the location ignoring the rotation info
		switch ( targ->client->lasthurt_location & 
				~(LOCATION_BACK | LOCATION_LEFT | LOCATION_RIGHT | LOCATION_FRONT) )
		{
		case LOCATION_HEAD:
			take *= 1.8;
			break;
		case LOCATION_FACE:
			if (targ->client->lasthurt_location & LOCATION_FRONT)
				take *= 5.0; // Faceshots REALLY suck
			else
				take *= 1.8;
			break;
		case LOCATION_SHOULDER:
			if (targ->client->lasthurt_location & (LOCATION_FRONT | LOCATION_BACK))
				take *= 1.4; // Throat or nape of neck
			else
				take *= 1.1; // Shoulders
			break;
		case LOCATION_CHEST:
			if (targ->client->lasthurt_location & (LOCATION_FRONT | LOCATION_BACK))
				take *= 1.3; // Belly or back
			else
				take *= 0.8; // Arms
			break;
		case LOCATION_STOMACH:
			take *= 1.2;
			break;
		case LOCATION_GROIN:
			if (targ->client->lasthurt_location & LOCATION_FRONT)
				take *= 1.3; // Groin shot
			break;
		case LOCATION_LEG:
			take *= 0.7;
			break;
		case LOCATION_FOOT:
			take *= 0.5;
			break;

		}
	return take;

}
#endif


/*
============
G_Damage

targ		entity that is being damaged
inflictor	entity that is causing the damage
attacker	entity that caused the inflictor to damage targ
	example: targ=monster, inflictor=rocket, attacker=player

dir			direction of the attack for knockback
point		point at which the damage is being inflicted, used for headshots
damage		amount of damage being inflicted
knockback	force to be applied against targ as a result of the damage

inflictor, attacker, dir, and point can be NULL for environmental effects

dflags		these flags are used to control how T_Damage works
	DAMAGE_RADIUS			damage was indirect (from a nearby explosion)
	DAMAGE_NO_ARMOR			armor does not protect from this damage
	DAMAGE_NO_KNOCKBACK		do not affect velocity, just view angles
	DAMAGE_NO_PROTECTION	kills godmode, armor, everything
============
*/

void G_Damage( gentity_t *targ, gentity_t *inflictor, gentity_t *attacker,
			   vec3_t dir, vec3_t point, int damage, int dflags, int mod ) {
	gclient_t	*client;
	int			take;
	int			asave;
	int			knockback;
	int			max;
#ifdef USE_RUNES
	vec3_t tempdir;
#endif
#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS) || defined(USE_ADVANCED_ITEMS) || defined(USE_RUNES)
	vec3_t		bouncedir, impactpoint;
#endif

	if (!targ->takedamage) {
		return;
	}

	// the intermission has allready been qualified for, so don't
	// allow any extra scoring
	if ( level.intermissionQueued ) {
		return;
	}
#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS) || defined(USE_ADVANCED_ITEMS) || defined(USE_RUNES)
	if ( targ->client && mod != MOD_JUICED) {
		if ( targ->client->invulnerabilityTime > level.time) {
			if ( dir && point ) {
				G_InvulnerabilityEffect( targ, dir, point, impactpoint, bouncedir );
			}
			return;
		}
	}
#endif
	if ( !inflictor ) {
		inflictor = &g_entities[ENTITYNUM_WORLD];
	}
	if ( !attacker ) {
		attacker = &g_entities[ENTITYNUM_WORLD];
	}

#ifdef USE_RUNES
	if(attacker->client) {

		if(attacker->client->inventory[RUNE_DIVINE]) {
			mod = MOD_RUNE_DIVINITY;
		}

		if(attacker->client->inventory[RUNE_PIERCING]) {
			mod = MOD_RUNE_PIERCING;
		}

		if(targ == attacker) {
			if(attacker->client->inventory[RUNE_STRENGTH]) {
				mod = MOD_RUNE_STRENGTH;
			}
			if(attacker->client->inventory[RUNE_BERSERK]) {
				mod = MOD_RUNE_BERSERK;
			}
		} else {
			// do armor damage discount on self, but not on enemies
			if(attacker->client->inventory[RUNE_PIERCING]) {
				dflags |= DAMAGE_NO_ARMOR;
			}
		}

	}

#endif



	// shootable doors / buttons don't actually have any health
	if ( targ->s.eType == ET_MOVER ) {
		if ( targ->use && (targ->moverState == MOVER_POS1 
#ifdef USE_ROTATING_DOOR
			|| targ->moverState == ROTATOR_POS1
#endif
    )) {
			targ->use( targ, inflictor, attacker );
		}
		return;
	}
#ifdef MISSIONPACK
	if( g_gametype.integer == GT_OBELISK && CheckObeliskAttack( targ, attacker ) ) {
		return;
	}
#endif
	// reduce damage by the attacker's handicap value
	// unless they are rocket jumping
	if ( attacker->client && attacker != targ ) {
		max = attacker->client->ps.stats[STAT_MAX_HEALTH];
#ifdef USE_ADVANCED_ITEMS
		if( attacker->client->inventory[PW_GUARD] ) {
			max /= 2;
		}
#else
#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS)
		if( bg_itemlist[attacker->client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_GUARD ) {
			max /= 2;
		}
#endif
#endif
		damage = damage * max / 100;
	}

	client = targ->client;

	if ( client ) {
		if ( client->noclip ) {
			return;
		}
	}

#ifdef USE_RUNES
	if(attacker->client->inventory[RUNE_IMPACT] && !dir) {
		dir = tempdir;
		VectorCopy(attacker->s.origin, dir);
		VectorSubtract(dir, targ->s.origin, dir);
		VectorNormalize(dir);
	}
#endif
	if ( !dir ) {
		dflags |= DAMAGE_NO_KNOCKBACK;
	} else {
		VectorNormalize(dir);
	}

	knockback = damage;
#ifdef USE_RUNES
	if(attacker->client->inventory[RUNE_IMPACT]) {
		knockback *= 2;
	}
#endif
	if ( knockback > 200 ) {
		knockback = 200;
	}
	if ( targ->flags & FL_NO_KNOCKBACK ) {
		knockback = 0;
	}
	if ( dflags & DAMAGE_NO_KNOCKBACK ) {
		knockback = 0;
	}

#ifdef USE_ADVANCED_ITEMS
	if(targ->client->inventory[PW_GRAVITYSUIT]) {
		knockback *= 0.5f;
	}
#endif

#ifdef USE_GRAVITY_BOOTS
	// TODO: targ->flags & FL_BOOTS?
	// half the knockback with boots on
	if(targ->client->ps.gravity && targ->client->ps.gravity != g_gravity.value) {
		knockback *= 0.5f;
	}
#endif

	// figure momentum add, even if the damage won't be taken
	if ( knockback && targ->client ) {
		vec3_t	kvel;
		float	mass;

		mass = 200;

		VectorScale (dir, g_knockback.value * (float)knockback / mass, kvel);
		VectorAdd (targ->client->ps.velocity, kvel, targ->client->ps.velocity);

#ifdef USE_MODES_DEATH
    targ->splashAttacker = attacker;
    targ->splashTime = level.time;
#endif

		// set the timer so that the other client can't cancel
		// out the movement immediately
		if ( !targ->client->ps.pm_time ) {
			int		t;

			t = knockback * 2;
			if ( t < 50 ) {
				t = 50;
			}
			if ( t > 200 ) {
				t = 200;
			}
			targ->client->ps.pm_time = t;
			targ->client->ps.pm_flags |= PMF_TIME_KNOCKBACK;
		}
	}

	// check for completely getting out of the damage
	if ( !(dflags & DAMAGE_NO_PROTECTION) ) {

		// if TF_NO_FRIENDLY_FIRE is set, don't do damage to the target
		// if the attacker was on the same team
#ifdef MISSIONPACK
		if ( mod != MOD_JUICED && targ != attacker && !(dflags & DAMAGE_NO_TEAM_PROTECTION) && OnSameTeam (targ, attacker)  ) {
#else	
		if ( targ != attacker && OnSameTeam (targ, attacker)  ) {
#endif
			if ( !g_friendlyFire.integer ) {
				return;
			}
		}
#ifdef MISSIONPACK
		if (mod == MOD_PROXIMITY_MINE) {
			if (inflictor && inflictor->parent && OnSameTeam(targ, inflictor->parent)) {
				return;
			}
			if (targ == attacker) {
				return;
			}
		}
#endif

		// check for godmode
		if ( targ->flags & FL_GODMODE ) {
			return;
		}
	}

	// battlesuit protects from all radius damage (but takes knockback)
	// and protects 50% against all damage
	if ( client && 
#ifdef USE_ADVANCED_ITEMS
	(client->inventory[PW_BATTLESUIT] || client->inventory[PW_GRAVITYSUIT] )
#else
	client->ps.powerups[PW_BATTLESUIT] 
#endif	
	) {
		G_AddEvent( targ, EV_POWERUP_BATTLESUIT, 0 );
		if ( ( dflags & DAMAGE_RADIUS ) || ( mod == MOD_FALLING ) ) {
			return;
		}
		damage *= 0.5;
	}
#ifdef USE_ADVANCED_ITEMS
	// don't play sounds like above
	else if(client && client->inventory[PW_SUPERMAN]) {
		if ( ( dflags & DAMAGE_RADIUS ) || ( mod == MOD_FALLING ) ) {
			return;
		}
		damage *= 0.5;
	}
#endif

#ifdef USE_RUNES
	if(client->inventory[RUNE_STRENGTH]) {
		damage *= 2.0;
	}
	if(client->inventory[RUNE_BERSERK]) {
		damage *= 6.0;
	}
	if(client->inventory[RUNE_RESIST] || client->inventory[RUNE_ENVIRO]) {
		G_AddEvent( targ, EV_POWERUP_BATTLESUIT, 0 );
		if ( ( dflags & DAMAGE_RADIUS ) || ( mod == MOD_FALLING ) ) {
			return;
		}
		if ( targ == attacker) {
			damage *= 0.5;
		}
	}
#endif

	// always give half damage if hurting self
	// calculated after knockback, so rocket jumping works
	if ( targ == attacker) {
		damage *= 0.5;
#ifdef USE_TRINITY
    if(g_unholyTrinity.integer && targ == attacker) {
      return;
    }
#endif
#ifdef USE_HOTRPG
    if(g_hotRockets.integer && targ == attacker) {
      return;
    }
#endif
#ifdef USE_HOTBFG
    if(g_hotBFG.integer && targ == attacker) {
      return;
    }
#endif
	}

	if ( damage < 1 ) {
		damage = 1;
	}
	take = damage;

	// save some from armor
	asave = CheckArmor( targ, take, dflags );

	take -= asave;

	if ( g_debugDamage.integer ) {
		G_Printf( "%i: client:%i health:%i damage:%i armor:%i\n", level.time, targ->s.number,
			targ->health, take, asave );
	}

	// add to the attacker's hit counter (if the target isn't a general entity like a prox mine)
	if ( attacker->client && client && targ != attacker && targ->health > 0
			&& targ->s.eType != ET_MISSILE
			&& targ->s.eType != ET_GENERAL) {
#ifdef MISSIONPACK
		if ( OnSameTeam( targ, attacker ) ) {
			attacker->client->ps.persistant[PERS_HITS]--;
		} else {
			attacker->client->ps.persistant[PERS_HITS]++;
		}
		attacker->client->ps.persistant[PERS_ATTACKEE_ARMOR] = (targ->health<<8)|(client->ps.stats[STAT_ARMOR]);
#else
		// we may hit multiple targets from different teams
		// so usual PERS_HITS increments/decrements could result in ZERO delta
		if ( OnSameTeam( targ, attacker ) ) {
			attacker->client->damage.team++;
		} else {
			attacker->client->damage.enemy++;
			// accumulate damage during server frame
			attacker->client->damage.amount += take + asave;
		}
#endif
	}

	// add to the damage inflicted on a player this frame
	// the total will be turned into screen blends and view angle kicks
	// at the end of the frame
	if ( client ) {
		if ( attacker ) { // FIXME: always true?
			client->ps.persistant[PERS_ATTACKER] = attacker->s.number;
		} else {
			client->ps.persistant[PERS_ATTACKER] = ENTITYNUM_WORLD;
		}
		client->damage_armor += asave;
		client->damage_blood += take;
		client->damage_knockback += knockback;
		if ( dir ) {
			VectorCopy ( dir, client->damage_from );
			client->damage_fromWorld = qfalse;
		} else {
			VectorCopy ( targ->r.currentOrigin, client->damage_from );
			client->damage_fromWorld = qtrue;
		}
	}

	// See if it's the player hurting the emeny flag carrier
#ifdef MISSIONPACK
	if( g_gametype.integer == GT_CTF || g_gametype.integer == GT_1FCTF ) {
#else	
	if( g_gametype.integer == GT_CTF) {
#endif
		Team_CheckHurtCarrier(targ, attacker);
	}

	if (targ->client) {
		// set the last client who damaged the target
		targ->client->lasthurt_client = attacker->s.number;
		targ->client->lasthurt_mod = mod;

#ifdef USE_LOCAL_DMG
    if(g_locDamage.integer) {
  		// Modify the damage for location damage
  		if (point && targ && targ->health > 0 && attacker && take)
  			take = G_LocationDamage(point, targ, attacker, take);
  		if (targ && targ->health > 0 && mod == MOD_FALLING && take) {
        if(take >= 15)
          targ->client->lasthurt_location = LOCATION_FOOT | LOCATION_LEG;
        else if (take >= 10)
          targ->client->lasthurt_location = LOCATION_FOOT;
        else if (take >= 5)
          targ->client->lasthurt_location = LOCATION_LEG;
      }
      if(targ && (!point || !attacker || targ->health <= 0 || !take))
  			targ->client->lasthurt_location = LOCATION_NONE;
    }
#endif

#ifdef USE_HEADSHOTS
    if (attacker->client && targ && targ->health > 0
      && inflictor && inflictor->s.weapon == WP_RAILGUN) {
    	// let's say only railgun can do head shots
    	if((targ->client->lasthurt_location & LOCATION_HEAD)
        || (targ->client->lasthurt_location & LOCATION_FACE)) {
        /*
        float	z_ratio;
        float	z_rel;
        int	height;
        float	targ_maxs2;
        targ_maxs2 = targ->r.maxs[2];
    	
    		// handling crouching
    		if(targ->client->ps.pm_flags & PMF_DUCKED){
    			height = (abs(targ->r.mins[2]) + targ_maxs2)*(0.75);
    		}
    		else
    			height = abs(targ->r.mins[2]) + targ_maxs2; 
    			
    		// project the z component of point 
    		// onto the z component of the model's origin
    		// this results in the z component from the origin at 0
    		z_rel = point[2] - targ->r.currentOrigin[2] + abs(targ->r.mins[2]);
    		z_ratio = z_rel / height;
    	
    		if (z_ratio > 0.90) {
        */
  			take = 9999; // head shot is a sure kill
  			targ->client->lasthurt_mod = mod = MOD_HEADSHOT;
        // }
    	}
    }
#endif
	}

	// do the damage
	if (take) {
		targ->health = targ->health - take;
		if ( targ->client ) {
			targ->client->ps.stats[STAT_HEALTH] = targ->health;
		}
			
		if ( targ->health <= 0 ) {
			if ( client )
				targ->flags |= FL_NO_KNOCKBACK;

			if (targ->health < -999)
				targ->health = -999;

			targ->enemy = attacker;
			targ->die (targ, inflictor, attacker, take, mod);
			return;
		} else if ( targ->pain ) {
			targ->pain (targ, attacker, take);
		}
	}

}


/*
============
CanDamage

Returns qtrue if the inflictor can directly damage the target.  Used for
explosions and melee attacks.
============
*/
qboolean CanDamage( gentity_t *targ, vec3_t origin )
{
	//we check if the attacker can damage the target, return qtrue if yes, qfalse if no
	vec3_t	dest;
	trace_t	tr;
	vec3_t	midpoint;
	vec3_t				size;

	// use the midpoint of the bounds instead of the origin, because bmodels may have their origin 0,0,0
	VectorAdd (targ->r.absmin, targ->r.absmax, midpoint);
	VectorScale( midpoint, 0.5, dest );

	trap_Trace ( &tr, origin, vec3_origin, vec3_origin, dest, ENTITYNUM_NONE, MASK_SOLID);
	if (tr.fraction == 1.0 || tr.entityNum == targ->s.number)
		return qtrue;

	VectorSubtract( targ->r.absmax, targ->r.absmin, size );
	
	// top quad

	// - +
	// - -
	VectorCopy( targ->r.absmax, dest );
	trap_Trace ( &tr, origin, vec3_origin, vec3_origin, dest, ENTITYNUM_NONE, MASK_SOLID);
	if (tr.fraction == 1.0)
		return qtrue;

	// + -
	// - -
	dest[0] -= size[0];
	trap_Trace( &tr, origin, vec3_origin, vec3_origin, dest, ENTITYNUM_NONE, MASK_SOLID );
	if ( tr.fraction == 1.0 )
		return qtrue;

	// - -
	// + -
	dest[1] -= size[1];
	trap_Trace( &tr, origin, vec3_origin, vec3_origin, dest, ENTITYNUM_NONE, MASK_SOLID );
	if ( tr.fraction == 1.0 )
		return qtrue;

	// - -
	// - +
	dest[0] += size[0];
	trap_Trace( &tr, origin, vec3_origin, vec3_origin, dest, ENTITYNUM_NONE, MASK_SOLID );
	if ( tr.fraction == 1.0 )
		return qtrue;

	// bottom quad

	// - -
	// + -
	VectorCopy( targ->r.absmin, dest );
	trap_Trace ( &tr, origin, vec3_origin, vec3_origin, dest, ENTITYNUM_NONE, MASK_SOLID);
	if (tr.fraction == 1.0)
		return qtrue;

	// - -
	// - +
	dest[0] += size[0];
	trap_Trace ( &tr, origin, vec3_origin, vec3_origin, dest, ENTITYNUM_NONE, MASK_SOLID);
	if (tr.fraction == 1.0)
		return qtrue;

	// - +
	// - -
	dest[1] += size[1];
	trap_Trace ( &tr, origin, vec3_origin, vec3_origin, dest, ENTITYNUM_NONE, MASK_SOLID);
	if (tr.fraction == 1.0)
		return qtrue;

	// + -
	// - -
	dest[0] -= size[0];
	trap_Trace( &tr, origin, vec3_origin, vec3_origin, dest, ENTITYNUM_NONE, MASK_SOLID );
	if ( tr.fraction == 1.0 )
		return qtrue;

	return qfalse;
}


/*
============
G_RadiusDamage
============
*/
qboolean G_RadiusDamage ( vec3_t origin, gentity_t *attacker, float damage, float radius,
					 gentity_t *ignore, int mod) {
	float		points, dist;
	gentity_t	*ent;
	int			entityList[MAX_GENTITIES];
	int			numListedEntities;
	vec3_t		mins, maxs;
	vec3_t		v;
	vec3_t		dir;
	int			i, e;
	qboolean	hitClient = qfalse;

	if ( radius < 1 ) {
		radius = 1;
	}

	for ( i = 0 ; i < 3 ; i++ ) {
		mins[i] = origin[i] - radius;
		maxs[i] = origin[i] + radius;
	}

	numListedEntities = trap_EntitiesInBox( mins, maxs, entityList, MAX_GENTITIES );

	for ( e = 0 ; e < numListedEntities ; e++ ) {
		ent = &g_entities[entityList[ e ]];

#ifdef USE_GAME_FREEZETAG
		if(g_freezeTag.integer) {
			// don't do radius damage to frozen players, like they turned into a brick of ice
			if(ent->client->ps.pm_type == PM_FROZEN) {
				continue;
			}
		}
#endif

		if (ent == ignore)
			continue;
		if (!ent->takedamage)
			continue;

		// find the distance from the edge of the bounding box
		for ( i = 0 ; i < 3 ; i++ ) {
			if ( origin[i] < ent->r.absmin[i] ) {
				v[i] = ent->r.absmin[i] - origin[i];
			} else if ( origin[i] > ent->r.absmax[i] ) {
				v[i] = origin[i] - ent->r.absmax[i];
			} else {
				v[i] = 0;
			}
		}

		dist = VectorLength( v );
		if ( dist >= radius ) {
			continue;
		}

		points = damage * ( 1.0 - dist / radius );

		if( CanDamage (ent, origin) ) {
			if( LogAccuracyHit( ent, attacker ) ) {
				hitClient = qtrue;
			}
			VectorSubtract (ent->r.currentOrigin, origin, dir);
			// push the center of mass higher than the origin so players
			// get knocked into the air more
			dir[2] += 24;
			G_Damage (ent, NULL, attacker, dir, origin, (int)points, DAMAGE_RADIUS, mod);
		}
	}

	return hitClient;
}


#ifdef USE_LV_DISCHARGE
/*
============
G_WaterRadiusDamage for The SARACEN's Lightning Discharge
============
*/
qboolean G_WaterRadiusDamage (vec3_t origin, gentity_t *attacker, float damage, float radius,
					 gentity_t *ignore, int mod)
{
	float		points, dist;
	gentity_t	*ent;
	int		entityList[MAX_GENTITIES];
	int		numListedEntities;
	vec3_t		mins, maxs;
	vec3_t		v;
	vec3_t		dir;
	int		i, e;
	qboolean	hitClient = qfalse;

	if (!(trap_PointContents (origin, -1) & MASK_WATER)) return qfalse;
		// if we're not underwater, forget it!

	if (radius < 1) radius = 1;

	for (i = 0 ; i < 3 ; i++)
	{
		mins[i] = origin[i] - radius;
		maxs[i] = origin[i] + radius;
	}

	numListedEntities = trap_EntitiesInBox (mins, maxs, entityList, MAX_GENTITIES);

	for (e = 0 ; e < numListedEntities ; e++)
	{
		ent = &g_entities[entityList[e]];

		if (ent == ignore)			continue;
		if (!ent->takedamage)		continue;

		// find the distance from the edge of the bounding box
		for (i = 0 ; i < 3 ; i++)
		{
			     if (origin[i] < ent->r.absmin[i]) v[i] = ent->r.absmin[i] - origin[i];
			else if (origin[i] > ent->r.absmax[i]) v[i] = origin[i] - ent->r.absmax[i];
			else v[i] = 0;
		}

		dist = VectorLength(v);
		if (dist >= radius)			continue;

		points = damage * (1.0 - dist / radius);

		if (CanDamage (ent, origin) && ent->waterlevel) 	// must be in the water, somehow!
		{
			if (LogAccuracyHit (ent, attacker)) hitClient = qtrue;
			VectorSubtract (ent->r.currentOrigin, origin, dir);
			// push the center of mass higher than the origin so players
			// get knocked into the air more
			dir[2] += 24;
			G_Damage (ent, NULL, attacker, dir, origin, (int)points, DAMAGE_RADIUS, mod);
		}
	}

	return hitClient;
}
#endif
