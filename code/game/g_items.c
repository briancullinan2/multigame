// Copyright (C) 1999-2000 Id Software, Inc.
//
#include "g_local.h"

/*

  Items are any object that a player can touch to gain some effect.

  Pickup will return the number of seconds until they should respawn.

  all items should pop when dropped in lava or slime

  Respawnable items don't actually go away when picked up, they are
  just made invisible and untouchable.  This allows them to ride
  movers and respawn apropriately.
*/

// initial spawn times after warmup
// in vq3 most of the items appears in one frame but we will delay that a bit
// to reduce peak bandwidth and get some nice transition effects
#define	SPAWN_WEAPONS		333
#define	SPAWN_ARMOR			1200
#define	SPAWN_HEALTH		900
#define	SPAWN_AMMO			600
#define	SPAWN_HOLDABLE		2500
#define	SPAWN_MEGAHEALTH	10000
#define	SPAWN_POWERUP		45000

// periodic respawn times
// g_weaponRespawn.integer || g_weaponTeamRespawn.integer
#define	RESPAWN_ARMOR		25000
#define	RESPAWN_HEALTH		35000
#define	RESPAWN_AMMO		40000
#define	RESPAWN_HOLDABLE	60000
#define	RESPAWN_MEGAHEALTH	35000 //120000
#define	RESPAWN_POWERUP		120000


void Add_Weapon_Ammo( gentity_t *ent, int weapon, int count );
void Add_Ammo( gentity_t *ent, int weapon, int count );

//======================================================================

int SpawnTime( gentity_t *ent, qboolean firstSpawn ) 
{
	if ( !ent->item )
		return 0;

	switch( ent->item->giType ) {
#ifdef USE_ADVANCED_ITEMS
	case IT_WEAPON2:
#endif
	case IT_WEAPON:
		if ( firstSpawn )
			return SPAWN_WEAPONS;
		if ( g_gametype.integer == GT_TEAM )
			return g_weaponTeamRespawn.value * 1000;
		else
			return g_weaponRespawn.value * 1000 ;

#ifdef USE_ADVANCED_ITEMS
	case IT_AMMO2:
#endif
	case IT_AMMO:
		return firstSpawn ? SPAWN_AMMO : RESPAWN_AMMO;

#ifdef USE_ADVANCED_ITEMS
	case IT_ARMOR2:
#endif
	case IT_ARMOR:
		return firstSpawn ? SPAWN_ARMOR : RESPAWN_ARMOR;

#ifdef USE_ADVANCED_ITEMS
	case IT_HEALTH2:
#endif
	case IT_HEALTH:
		if ( ent->item->quantity == 100 ) // mega health respawns slow
			return firstSpawn ? SPAWN_MEGAHEALTH : RESPAWN_MEGAHEALTH;
		else
			return firstSpawn ? SPAWN_HEALTH : RESPAWN_HEALTH;

#ifdef USE_ADVANCED_ITEMS
	case IT_POWERUP2:
#endif
	case IT_POWERUP:
		return firstSpawn ? SPAWN_POWERUP : RESPAWN_POWERUP;

#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS)
#ifdef USE_ADVANCED_ITEMS
	case IT_PERSISTANT_POWERUP2:
#endif
	case IT_PERSISTANT_POWERUP:
		return -1;
		break;
#endif

#ifdef USE_ADVANCED_ITEMS
	case IT_HOLDABLE2:
#endif
	case IT_HOLDABLE:
		return firstSpawn ? SPAWN_HOLDABLE : RESPAWN_HOLDABLE;

	default: // IT_BAD and others
		return 0;
	}
} 

#ifdef USE_ADVANCED_ITEMS
int BG_FindPriorityShaderForInventory(int powerup, int inventory[PW_NUM_POWERUPS], int team);
#endif

void G_GiveItem(gentity_t *ent, powerup_t pw);


int Pickup_Powerup( gentity_t *ent, gentity_t *other ) {
	int			quantity;
	int			i;
	gclient_t	*client;

#ifndef USE_ADVANCED_ITEMS
	if ( !other->client->ps.powerups[ent->item->giTag] ) {
		// round timing to seconds to make multiple powerup timers count in sync
		other->client->ps.powerups[ent->item->giTag] = level.time - ( level.time % 1000 );
	}

	if ( ent->count ) {
		quantity = ent->count;
	} else {
		quantity = ent->item->quantity;
	}

	other->client->ps.powerups[ent->item->giTag] += quantity * 1000;

#else
	{
		other->client->inventory[ent->item->giTag] = level.time + (1000 - ( level.time % 1000 )); // round up?

		if ( ent->count ) {
			quantity = ent->count;
		} else {
			quantity = ent->item->quantity;
		}

		other->client->inventory[ent->item->giTag] += quantity * 1000;
		other->client->inventoryModified[(int)floor(ent->item->giTag / PW_MAX_POWERUPS)] = qtrue;
		//G_Printf("powerup: %i = %i\n", ent->item->giTag,  other->client->ps.powerups[ent->item->giTag]);
		other->s.powerups = BG_FindPriorityShaderForInventory(ent->item->giTag, other->client->inventory, other->client->sess.sessionTeam);
	}
#endif

#ifdef USE_RUNES
  if(ent->item->giTag >= RUNE_STRENGTH && ent->item->giTag <= RUNE_LITHIUM) {
    other->client->inventory[ent->item->giTag] += 999 * 1000; // rune for a really long time
  }
  if(ent->item->giTag == RUNE_HEALTH) {
		other->client->ps.stats[STAT_MAX_HEALTH] = rune_healthMax.integer;
		other->health = rune_health.integer;
  } else
	if(ent->item->giTag == RUNE_RECALL) {
		G_GiveItem(other, HI_PORTAL);
	} else
	if(ent->item->giTag == RUNE_SHIELD) {
		G_GiveItem(other, HI_INVULNERABILITY);
	} else
	if(ent->item->giTag == RUNE_DIVINE) {
		G_GiveItem(other, HI_KAMIKAZE);
	} else
	if(ent->item->giTag == RUNE_GRAPPLE) {
		Add_Weapon_Ammo(other, WP_GRAPPLING_HOOK, 100);
	} else
	if(ent->item->giTag == RUNE_LITHIUM) {
		Add_Weapon_Ammo(other, WP_GRAPPLING_HOOK, INFINITE);
	} else
	if(ent->item->giTag == RUNE_CLUSTER) {
		Add_Weapon_Ammo(other, WP_GRENADE_LAUNCHER, 10);
	}

#endif

	// give any nearby players a "denied" anti-reward
	for ( i = 0 ; i < level.maxclients ; i++ ) {
		vec3_t		delta;
		float		len;
		vec3_t		forward;
		trace_t		tr;

		client = &level.clients[i];
		if ( client == other->client ) {
			continue;
		}
		if ( client->pers.connected != CON_CONNECTED ) {
			continue;
		}
		if ( client->ps.stats[STAT_HEALTH] <= 0 ) {
			continue;
		}

		// if same team in team game, no sound
		// cannot use OnSameTeam as it expects to g_entities, not clients
		if ( g_gametype.integer >= GT_TEAM && other->client->sess.sessionTeam == client->sess.sessionTeam  ) {
			continue;
		}

		// if too far away, no sound
		VectorSubtract( ent->s.pos.trBase, client->ps.origin, delta );
		len = VectorNormalize( delta );
		if ( len > 192 ) {
			continue;
		}

		// if not facing, no sound
		AngleVectors( client->ps.viewangles, forward, NULL, NULL );
		if ( DotProduct( delta, forward ) < 0.4 ) {
			continue;
		}

		// if not line of sight, no sound
		trap_Trace( &tr, client->ps.origin, NULL, NULL, ent->s.pos.trBase, ENTITYNUM_NONE, CONTENTS_SOLID );
		if ( tr.fraction != 1.0 ) {
			continue;
		}

		// anti-reward
		client->ps.persistant[PERS_PLAYEREVENTS] ^= PLAYEREVENT_DENIEDREWARD;
	}

	return SpawnTime( ent, qfalse ); // return RESPAWN_POWERUP;
}


//======================================================================

#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS)
int Pickup_PersistantPowerup( gentity_t *ent, gentity_t *other ) {
	int		clientNum;
	char	userinfo[MAX_INFO_STRING];
	float	handicap;
	int		max;

#ifdef USE_ADVANCED_ITEMS
	other->s.powerups = ent->item->giTag;
	other->client->inventory[ent->item->giTag] = 1;
	other->client->inventoryModified[(int)floor(ent->item->giTag / PW_MAX_POWERUPS)] = qtrue;
#else
	other->client->ps.stats[STAT_PERSISTANT_POWERUP] = ent->item - bg_itemlist;
#endif

	other->client->persistantPowerup = ent;

	switch( ent->item->giTag ) {
	case PW_GUARD:
		clientNum = other->client->ps.clientNum;
		trap_GetUserinfo( clientNum, userinfo, sizeof(userinfo) );
		handicap = atof( Info_ValueForKey( userinfo, "handicap" ) );
		if( handicap<=0.0f || handicap>100.0f) {
			handicap = 100.0f;
		}
		max = (int)(2 *  handicap);

		other->health = max;
		other->client->ps.stats[STAT_HEALTH] = max;
		other->client->ps.stats[STAT_MAX_HEALTH] = max;
		other->client->ps.stats[STAT_ARMOR] = max;
		other->client->pers.maxHealth = max;

		break;

	case PW_SCOUT:
		clientNum = other->client->ps.clientNum;
		trap_GetUserinfo( clientNum, userinfo, sizeof(userinfo) );
		handicap = atof( Info_ValueForKey( userinfo, "handicap" ) );
		if( handicap<=0.0f || handicap>100.0f) {
			handicap = 100.0f;
		}
		other->client->pers.maxHealth = handicap;
		other->client->ps.stats[STAT_ARMOR] = 0;
		break;

	case PW_DOUBLER:
		clientNum = other->client->ps.clientNum;
		trap_GetUserinfo( clientNum, userinfo, sizeof(userinfo) );
		handicap = atof( Info_ValueForKey( userinfo, "handicap" ) );
		if( handicap<=0.0f || handicap>100.0f) {
			handicap = 100.0f;
		}
		other->client->pers.maxHealth = handicap;
		break;
	case PW_AMMOREGEN:
		clientNum = other->client->ps.clientNum;
		trap_GetUserinfo( clientNum, userinfo, sizeof(userinfo) );
		handicap = atof( Info_ValueForKey( userinfo, "handicap" ) );
		if( handicap<=0.0f || handicap>100.0f) {
			handicap = 100.0f;
		}
		other->client->pers.maxHealth = handicap;
		memset(other->client->ammoTimes, 0, sizeof(other->client->ammoTimes));
		break;
	default:
		clientNum = other->client->ps.clientNum;
		trap_GetUserinfo( clientNum, userinfo, sizeof(userinfo) );
		handicap = atof( Info_ValueForKey( userinfo, "handicap" ) );
		if( handicap<=0.0f || handicap>100.0f) {
			handicap = 100.0f;
		}
		other->client->pers.maxHealth = handicap;
		break;
	}

	return SpawnTime( ent, qfalse ); // return -1;
}

//======================================================================
#endif

int Pickup_Holdable( gentity_t *ent, gentity_t *other ) {

#ifdef USE_ADVANCED_ITEMS
	{
		other->client->inventory[ent->item->giTag] = level.time;
		other->client->inventoryModified[(int)floor(ent->item->giTag / PW_MAX_POWERUPS)] = qtrue;
		//G_Printf("powerup: %i = %i\n", ent->item->giTag,  other->client->ps.powerups[ent->item->giTag]);
	}
#else
	other->client->ps.stats[STAT_HOLDABLE_ITEM] = ent->item - bg_itemlist;
#endif



#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS) || defined(USE_RUNES)
	if( ent->item->giTag == HI_KAMIKAZE ) {
		other->client->ps.eFlags |= EF_KAMIKAZE;
	}
#endif

	return SpawnTime( ent, qfalse ); // return RESPAWN_HOLDABLE;
}


//======================================================================

void Remove_Weapon_Ammo( gentity_t *ent, int weapon, int count )
{
#ifdef USE_ADVANCED_WEAPONS
	ent->client->classWeapons[weapon] = 0;
	ent->client->weaponsModified[(int)floor(weapon / WP_MAX_WEAPONS)] = qtrue;
	ent->client->classAmmo[weapon] -= count;
	if ( ent->client->classAmmo[weapon] < 0 ) {
		ent->client->classAmmo[weapon] = 0;
	}
#else
	ent->client->ps.stats[STAT_WEAPONS] &= ~(1 << weapon);
	ent->client->ps.ammo[weapon] -= count;
	if ( ent->client->ps.ammo[weapon] < 0 ) {
		ent->client->ps.ammo[weapon] = 0;
	}
#endif
}

void Add_Weapon_Ammo( gentity_t *ent, int weapon, int count )
{
#ifdef USE_ADVANCED_WEAPONS
	ent->client->classWeapons[weapon]++;
	ent->client->weaponsModified[(int)floor(weapon / WP_MAX_WEAPONS)] = qtrue;
	ent->client->classAmmo[weapon] += count;
	if ( ent->client->classAmmo[weapon] > AMMO_HARD_LIMIT ) {
		ent->client->classAmmo[weapon] = AMMO_HARD_LIMIT;
	}
#else
	ent->client->ps.stats[STAT_WEAPONS] |= (1 << weapon);
	ent->client->ps.ammo[weapon] += count;
	if ( ent->client->ps.ammo[weapon] > AMMO_HARD_LIMIT ) {
		ent->client->ps.ammo[weapon] = AMMO_HARD_LIMIT;
	}
#endif
}

void Remove_Ammo( gentity_t *ent, int weapon, int count )
{
#ifdef USE_ADVANCED_WEAPONS
	ent->client->classAmmo[weapon] -= count;
	if ( ent->client->classAmmo[weapon] < 0 ) {
		ent->client->classAmmo[weapon] = 0;
	}
#else
	ent->client->ps.ammo[weapon] -= count;
	if ( ent->client->ps.ammo[weapon] < 0 ) {
		ent->client->ps.ammo[weapon] = 0;
	}
#endif
}

void Add_Ammo( gentity_t *ent, int weapon, int count )
{
#ifdef USE_ADVANCED_WEAPONS
	ent->client->classAmmo[weapon] += count;
	if ( ent->client->classAmmo[weapon] > AMMO_HARD_LIMIT ) {
		ent->client->classAmmo[weapon] = AMMO_HARD_LIMIT;
	}
#else
	ent->client->ps.ammo[weapon] += count;
	if ( ent->client->ps.ammo[weapon] > AMMO_HARD_LIMIT ) {
		ent->client->ps.ammo[weapon] = AMMO_HARD_LIMIT;
	}
#endif
}


static int Pickup_Ammo( gentity_t *ent, gentity_t *other )
{
	int		quantity;

	if ( ent->count ) {
		quantity = ent->count;
	} else {
		quantity = ent->item->quantity;
	}

	Add_Ammo( other, ent->item->giTag, quantity );

	return SpawnTime( ent, qfalse ); // return RESPAWN_AMMO;
}

//======================================================================


static int Pickup_Weapon( gentity_t *ent, gentity_t *other ) {
	int		quantity;

	if ( ent->count < 0 ) {
		quantity = 0; // None for you, sir!
	} else {
		if ( ent->count ) {
			quantity = ent->count;
		} else {
			quantity = ent->item->quantity;
		}

		// dropped items and teamplay weapons always have full ammo
		if ( ! (ent->flags & FL_DROPPED_ITEM) && g_gametype.integer != GT_TEAM ) {
			// respawning rules
			// drop the quantity if the already have over the minimum
#ifdef USE_ADVANCED_WEAPONS
			if ( other->client->classAmmo[ ent->item->giTag ] < quantity ) {
				quantity = quantity - other->client->classAmmo[ ent->item->giTag ];
#else
			if ( other->client->ps.ammo[ ent->item->giTag ] < quantity ) {
				quantity = quantity - other->client->ps.ammo[ ent->item->giTag ];
#endif
			} else {
				quantity = 1;		// only add a single shot
			}
		}
	}

	// add the weapon
#ifdef USE_ADVANCED_WEAPONS
	other->client->classWeapons[ent->item->giTag]++;
	other->client->weaponsModified[(int)floor(ent->item->giTag / WP_MAX_WEAPONS)] = qtrue;
#else
	other->client->ps.stats[STAT_WEAPONS] |= ( 1 << ent->item->giTag );
#endif

	Add_Ammo( other, ent->item->giTag, quantity );

#ifdef USE_GRAPPLE
	if (ent->item->giTag == WP_GRAPPLING_HOOK)
#ifdef USE_ADVANCED_WEAPONS
		other->client->classAmmo[ent->item->giTag] = INFINITE; // unlimited ammo
#else
		other->client->ps.ammo[ent->item->giTag] = -1; // unlimited ammo
#endif
#endif

	// team deathmatch has slow weapon respawns
	//if ( g_gametype.integer == GT_TEAM ) {
	//	return g_weaponTeamRespawn.integer;
	//} else {
	//	return g_weaponRespawn.integer;
	//}
	return SpawnTime( ent, qfalse );
}


//======================================================================

static int Pickup_Health( gentity_t *ent, gentity_t *other ) {
	int			max;
	int			quantity;

	// small and mega healths will go over the max
#ifdef USE_ADVANCED_ITEMS
	if( other->client && other->client->inventory[PW_GUARD] ) {
		max = other->client->ps.stats[STAT_MAX_HEALTH];
	}
	else
#else
#ifdef MISSIONPACK
	if( other->client && bg_itemlist[other->client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_GUARD ) {
		max = other->client->ps.stats[STAT_MAX_HEALTH];
	}
	else
#endif
#endif
	if ( ent->item->quantity != 5 && ent->item->quantity != 100
#ifdef USE_ADVANCED_ITEMS
	&& ent->item->quantity != 200 
#endif
	) {
		max = other->client->ps.stats[STAT_MAX_HEALTH];
	} else {
		max = other->client->ps.stats[STAT_MAX_HEALTH] * 2;
	}

	if ( ent->count ) {
		quantity = ent->count;
	} else {
		quantity = ent->item->quantity;
	}

	other->health += quantity;

#ifdef USE_LOCAL_DMG
  if(g_locDamage.integer) {
    // return speed upon health pickup or more than maximum health, McBain
    other->client->lasthurt_location = LOCATION_NONE;
  	other->client->ps.speed += quantity;
  	if (other->client->ps.speed > g_speed.value) {
  		other->client->ps.speed = g_speed.value;
  	}

  	if (other->health >= other->client->ps.stats[STAT_MAX_HEALTH]) {
  		other->client->ps.speed = g_speed.value;
  	}

#ifdef USE_ADVANCED_ITEMS
  	if( other->client->inventory[PW_SCOUT] ) {
  		other->client->ps.speed *= 1.5;
  	}
  	else
#else
#if defined(MISSIONPACK)
  	if( bg_itemlist[other->client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_SCOUT ) {
  		other->client->ps.speed *= 1.5;
  	}
  	else
#endif
#endif
    if (
#ifdef USE_ADVANCED_ITEMS
			 other->client->inventory[PW_HASTE] 
#else
			 other->client->ps.powerups[PW_HASTE] 
#endif
#ifdef USE_RUNES
      || other->client->inventory[RUNE_HASTE]
#endif
    ) {
      other->client->ps.speed *= 1.3;
    }

  	// end McBain
  }
#endif

	if (other->health > max ) {
		other->health = max;
	}
	other->client->ps.stats[STAT_HEALTH] = other->health;

	//if ( ent->item->quantity == 100 ) { // mega health respawns slow
	//	return RESPAWN_MEGAHEALTH;
	//} else {
	//	return RESPAWN_HEALTH;
	//}
	return SpawnTime( ent, qfalse );
}


//======================================================================

int Pickup_Armor( gentity_t *ent, gentity_t *other ) {
#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS)
	int		upperBound;

	other->client->ps.stats[STAT_ARMOR] += ent->item->quantity;

#ifdef USE_ADVANCED_ITEMS
	if( other->client && other->client->inventory[PW_GUARD] ) {
		upperBound = other->client->ps.stats[STAT_MAX_HEALTH];
	}
#else
	if( other->client && bg_itemlist[other->client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_GUARD ) {
		upperBound = other->client->ps.stats[STAT_MAX_HEALTH];
	}
#endif
	else {
		upperBound = other->client->ps.stats[STAT_MAX_HEALTH] * 2;
	}

	if ( other->client->ps.stats[STAT_ARMOR] > upperBound ) {
		other->client->ps.stats[STAT_ARMOR] = upperBound;
	}
#else
	other->client->ps.stats[STAT_ARMOR] += ent->item->quantity;
	if ( other->client->ps.stats[STAT_ARMOR] > other->client->ps.stats[STAT_MAX_HEALTH] * 2 ) {
		other->client->ps.stats[STAT_ARMOR] = other->client->ps.stats[STAT_MAX_HEALTH] * 2;
	}
#endif

	return SpawnTime( ent, qfalse ); // return RESPAWN_ARMOR;
}

//======================================================================

/*
===============
RespawnItem
===============
*/
void RespawnItem( gentity_t *ent ) {
	
	if ( !ent ) {
		return;
	}
	
	// randomly select from teamed entities
	if ( ent->team ) {
		gentity_t *master;
		int	count;
		int choice;

		if ( !ent->teammaster ) {
			G_Error( "RespawnItem: bad teammaster" );
		}

		master = ent->teammaster;

		for ( count = 0, ent = master; ent; ent = ent->teamchain, count++ ) {
			// reset spawn timers on all teamed entities
			ent->nextthink = 0;
		}

		choice = rand() % count;

		for ( count = 0, ent = master; ent && count < choice; ent = ent->teamchain, count++ )
			;
	}

	if ( !ent ) {
		return;
	}

	ent->r.contents = CONTENTS_TRIGGER;
	ent->s.eFlags &= ~EF_NODRAW;
#ifdef USE_ITEM_TIMERS
  ent->s.eFlags &= ~EF_TIMER;
#endif
	ent->r.svFlags &= ~SVF_NOCLIENT;
	trap_LinkEntity( ent );

	if ( ent->item->giType == IT_POWERUP ) {
		// play powerup spawn sound to all clients
		gentity_t	*te;

		// if the powerup respawn sound should Not be global
		if ( ent->speed ) {
			te = G_TempEntity( ent->s.pos.trBase, EV_GENERAL_SOUND );
		} else {
			te = G_TempEntity( ent->s.pos.trBase, EV_GLOBAL_SOUND );
		}
		te->s.eventParm = G_SoundIndex( "sound/items/poweruprespawn.wav" );
		te->r.svFlags |= SVF_BROADCAST;
	}

#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS) || defined(USE_RUNES)
	if ( ent->item->giType == IT_HOLDABLE && ent->item->giTag == HI_KAMIKAZE ) {
		// play powerup spawn sound to all clients
		gentity_t	*te;

		// if the powerup respawn sound should Not be global
		if (ent->speed) {
			te = G_TempEntity( ent->s.pos.trBase, EV_GENERAL_SOUND );
		}
		else {
			te = G_TempEntity( ent->s.pos.trBase, EV_GLOBAL_SOUND );
		}
		te->s.eventParm = G_SoundIndex( "sound/items/kamikazerespawn.wav" );
		te->r.svFlags |= SVF_BROADCAST;
	}
#endif

	// play the normal respawn sound only to nearby clients
	G_AddEvent( ent, EV_ITEM_RESPAWN, 0 );

	ent->nextthink = 0;
}


/*
===============
Touch_Item
===============
*/
void Touch_Item (gentity_t *ent, gentity_t *other, trace_t *trace) {
	int			respawn;
	qboolean	predict;
#ifdef USE_WEAPON_ORDER
  qboolean alreadyHad = qfalse;
#endif

#ifdef USE_INSTAGIB
	//SCO if ent-item is some sort of team item.
	if (g_instagib.integer && ent->item->giType != IT_TEAM)
		return;
#endif

#ifdef USE_TRINITY
	if (g_unholyTrinity.integer && ent->item->giType != IT_TEAM)
		return;
#endif
#ifdef USE_HOTRPG
	if (g_hotRockets.integer && ent->item->giType != IT_TEAM)
		return;
#endif
#ifdef USE_HOTBFG
	if (g_hotBFG.integer && ent->item->giType != IT_TEAM)
		return;
#endif

	if (!other->client)
		return;
	if (other->health < 1)
		return;		// dead people can't pickup

	// the same pickup rules are used for client side and server side
	if ( !BG_CanItemBeGrabbed( g_gametype.integer, &ent->s, 
#ifdef USE_ADVANCED_ITEMS
		other->client->inventory, 
#endif
#ifdef USE_ADVANCED_CLASS
		other->client->pers.playerclass,
#endif
#ifdef USE_ADVANCED_WEAPONS
		other->client->classWeapons,
		other->client->classAmmo,
#endif
		&other->client->ps ) ) {
		return;
	}

#ifdef USE_ADVANCED_ITEMS
{
	if(ent->item->giType == IT_HOLDABLE && 
		other->client->inventory[ent->item->giTag]) {
		return;
	}
}

#endif

#ifdef USE_RUNES
  // can only pickup one rune at a time
  if(ent->item->giType == IT_POWERUP
    && ent->item->giTag >= RUNE_STRENGTH && ent->item->giTag <= RUNE_LITHIUM) {
		int i;
		for(i = RUNE_STRENGTH; i <= RUNE_LITHIUM; i++) {
			if(other->client->inventory[i]) {
				return; // one at a time?
			}
		}
  }

	if(other->client->inventory[RUNE_REQUIEM]
		&& (ent->item->giType == IT_HEALTH || ent->item->giType == IT_ARMOR || ent->item->giType == IT_AMMO
#ifdef USE_ADVANCED_ITEMS
		|| ent->item->giType == IT_HEALTH2 || ent->item->giType == IT_ARMOR2 || ent->item->giType == IT_AMMO2
#endif
	)) {
		other->client->requiemGrab = ent->item->giType;
		other->client->requiemTime = level.time;
		// instead handle this in clienttimeractions
		return;
	}

#endif

	G_LogPrintf( "Item: %i %s\n", other->s.number, ent->item->classname );

	predict = other->client->pers.predictItemPickup;

	// call the item-specific pickup function
	switch( ent->item->giType ) {
#ifdef USE_ADVANCED_ITEMS
	case IT_WEAPON2:
#endif
	case IT_WEAPON:
#ifdef USE_WEAPON_ORDER
#ifdef USE_ADVANCED_WEAPONS
    alreadyHad = other->client->classWeapons[ent->item->giTag];
#else
    alreadyHad = other->client->ps.stats[STAT_WEAPONS] & (1 << ent->item->giTag);
#endif
#endif
		respawn = Pickup_Weapon(ent, other);
		break;
#ifdef USE_ADVANCED_ITEMS
	case IT_AMMO2:
#endif
	case IT_AMMO:
		respawn = Pickup_Ammo(ent, other);
		break;

#ifdef USE_ADVANCED_ITEMS
	case IT_ARMOR2:
#endif
	case IT_ARMOR:
		respawn = Pickup_Armor(ent, other);
		break;
#ifdef USE_ADVANCED_ITEMS
	case IT_HEALTH2:
#endif
	case IT_HEALTH:
		respawn = Pickup_Health(ent, other);
		break;
#ifdef USE_ADVANCED_ITEMS
	case IT_POWERUP2:
#endif
	case IT_POWERUP:
		respawn = Pickup_Powerup(ent, other);
		// brian cullinan - why?
		// allow prediction for some powerups
#ifdef USE_RUNES
    if(ent->item->giTag >= RUNE_STRENGTH && ent->item->giTag <= RUNE_LITHIUM)
      predict = qtrue;
#endif
		if ( ent->item->giTag >= PW_QUAD && ent->item->giTag <= PW_FLIGHT )
			predict = qtrue;
		else
			predict = qfalse;
#ifdef USE_ADVANCED_ITEMS
			predict = qtrue;
#endif
		break;
#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS)
#ifdef USE_ADVANCED_ITEMS
	case IT_PERSISTANT_POWERUP2:
#endif
	case IT_PERSISTANT_POWERUP:
		respawn = Pickup_PersistantPowerup(ent, other);
		break;
#endif
#ifdef USE_ADVANCED_ITEMS
	case IT_TEAM2:
#endif

	case IT_TEAM:
		respawn = Pickup_Team(ent, other);
		break;
#ifdef USE_ADVANCED_ITEMS
	case IT_HOLDABLE2:
#endif
	case IT_HOLDABLE:
		respawn = Pickup_Holdable(ent, other);
		break;
	default:
		return;
	}

	if ( !respawn ) {
		return;
	}

	// play the normal pickup sound
#ifdef USE_WEAPON_ORDER
#ifdef USE_ADVANCED_ITEMS
  if ( predict ) {
		
		G_AddPredictableEvent( other, 
			alreadyHad ? EV_ITEM_PICKUP + (ent->s.modelindex2 * 2)
								: EV_ITEM_PICKUP + (ent->s.modelindex2 * 2) + 1,
			ent->s.modelindex );
	} else {
		G_AddEvent( other, 
			alreadyHad ? EV_ITEM_PICKUP + (ent->s.modelindex2 * 2)
								: EV_ITEM_PICKUP + (ent->s.modelindex2 * 2) + 1,
			ent->s.modelindex );
	}
#else
  if ( predict ) {
		G_AddPredictableEvent( other, 
			alreadyHad ? EV_ITEM_PICKUP2 : EV_ITEM_PICKUP, 
			ent->s.modelindex );
	} else {
		G_AddEvent( other, 
			alreadyHad ? EV_ITEM_PICKUP2 : EV_ITEM_PICKUP, 
			ent->s.modelindex );
	}
#endif
#else
#ifdef USE_ADVANCED_ITEMS
  if ( predict ) {
		G_AddPredictableEvent( other, EV_ITEM_PICKUP + ent->s.modelindex2,
			ent->s.modelindex );
	} else {
		G_AddEvent( other, EV_ITEM_PICKUP + ent->s.modelindex2,
			ent->s.modelindex );
	}
#else
	if ( predict ) {
		G_AddPredictableEvent( other, EV_ITEM_PICKUP, ent->s.modelindex );
	} else {
		G_AddEvent( other, EV_ITEM_PICKUP, ent->s.modelindex );
	}
#endif
#endif

	// powerup pickups are global broadcasts
	if ( ent->item->giType == IT_POWERUP || ent->item->giType == IT_TEAM) {
		// if we want the global sound to play
		if (!ent->speed) {
			gentity_t	*te;

			te = G_TempEntity( ent->s.pos.trBase, EV_GLOBAL_ITEM_PICKUP + ent->s.modelindex2 );
			te->s.eventParm = ent->s.modelindex;
			te->r.svFlags |= SVF_BROADCAST;
		} else {
			gentity_t	*te;

			te = G_TempEntity( ent->s.pos.trBase, EV_GLOBAL_ITEM_PICKUP + ent->s.modelindex2 );
			te->s.eventParm = ent->s.modelindex;
			// only send this temp entity to a single client
			te->r.svFlags |= SVF_SINGLECLIENT;
			te->r.singleClient = other->s.number;
		}
	}

	// fire item targets
	G_UseTargets (ent, other);

	// wait of -1 will not respawn
	if ( ent->wait == -1 ) {
		ent->r.svFlags |= SVF_NOCLIENT;
		ent->s.eFlags |= EF_NODRAW;
		ent->r.contents = 0;
		ent->unlinkAfterEvent = qtrue;
		return;
	}

	// non zero wait overrides respawn time
	if ( ent->wait ) {
		respawn = ent->wait;
		respawn *= 1000;
	}

	// random can be used to vary the respawn time
	if ( ent->random ) {
		respawn += (crandom() * ent->random) * 1000;
		if ( respawn < 1000 ) {
			respawn = 1000;
		}
	}

	// dropped items will not respawn
	if ( ent->flags & FL_DROPPED_ITEM ) {
		ent->freeAfterEvent = qtrue;
	}

	// picked up items still stay around, they just don't
	// draw anything.  This allows respawnable items
	// to be placed on movers.
#ifdef USE_ITEM_TIMERS
	if(ent->item->giType != IT_TEAM && respawn != -1) {
		ent->r.svFlags |= SVF_BROADCAST;
	} else
#endif
	ent->r.svFlags |= SVF_NOCLIENT;
	ent->s.eFlags |= EF_NODRAW;
	ent->r.contents = 0;

	// ZOID
	// A negative respawn times means to never respawn this item (but don't 
	// delete it).  This is used by items that are respawned by third party 
	// events such as ctf flags
	if ( respawn <= 0 ) {
		ent->nextthink = 0;
		ent->think = 0;
#ifdef USE_ITEM_TIMERS
    ent->s.eFlags &= ~EF_TIMER;
#endif
	} else {
		ent->nextthink = level.time + respawn;
		ent->think = RespawnItem;
#ifdef USE_ITEM_TIMERS
		/* 
		if ( cg_itemTimer->integer && (
			(ent->item->giType == IT_ARMOR) ||
			(ent->item->giType == IT_POWERUP) ||
			(ent->item->giType == IT_HOLDABLE) ||
			(ent->item->giType == IT_PERSISTANT_POWERUP))) {
		*/
		//}
    ent->s.eFlags |= EF_TIMER;
    ent->s.time = level.time;
    ent->s.frame = respawn / 1000; // save bandwidth
#endif
	}

	trap_LinkEntity( ent );
}



/**
 * Pickup_Item
 *
 * Pickup an item but do a few checks before to see whether this is indeed valid
 */
void Pickup_Item (gentity_t *ent, gentity_t *other, trace_t *trace, int autoPickup)
{
	int respawn;

	// need a client and dead people can't pickup
	if (!other->client || other->health < 1)
	{
		return;
	}

	if(ent->s.eFlags & EF_NOPICKUP)
	{
		return;
	}

#if 0 // TODO
	// owner can't pickup his own items straight away
	if((ent->lastOwner == other) && (ent->lastOwnerThink > level.time))
	{
		return;
	}
#endif

	// not allowed to pick up weapons while reloading

	if ((ent->item->giType == IT_WEAPON) && (other->client->ps.weaponstate = WEAPON_DROPPING))
	{
		return;
	}

	if (!BG_CanItemBeGrabbed( g_gametype.integer, &ent->s, 
#ifdef USE_ADVANCED_ITEMS
		other->client->inventory,
#endif
#ifdef USE_ADVANCED_CLASS
		other->client->pers.playerclass,
#endif
#ifdef USE_ADVANCED_WEAPONS
		other->client->classWeapons,
		other->client->classAmmo,
#endif
		&other->client->ps ))
	{
		return;
	}

#if 0
	if(g_gametype.integer == GT_BOMB &&
		(other->client->sess.sessionTeam != TEAM_RED) && (ent->item->giTag == WP_BOMB))
	{
		return;
	}

	//Somebodys grabbed the bomb
	if (ent->item->giTag == WP_BOMB)
	{
		level.BombHolderLastRound = other->client->ps.clientNum;
		G_LogPrintf("Bomb has been collected by %i\n", other->client->ps.clientNum);
		level.UseLastRoundBomber  = qtrue;

		//@Barbatos: be sure we are playing bomb mode
		if(g_gametype.integer == GT_BOMB)
			G_AutoRadio(3, other);

		// we have to pickup bombs when we walk over
		autoPickup = -1;
	}
#endif

	// call the item-specific pickup function
	switch(ent->item->giType)
	{
		case IT_WEAPON:
			if (autoPickup & (1 << (ent->item - bg_itemlist)))
			{
				respawn = Pickup_Weapon(ent, other);
			}
			else
			{
				return;
			}
			break;

		case IT_TEAM:
			respawn = Pickup_Team(ent, other);
			break;

		case IT_HOLDABLE:
			// No picking up an item twice.
			if ((autoPickup & (1 << (ent->item - bg_itemlist))) 
#ifdef USE_ADVANCED_ITEMS
				&& !other->client->inventory[ent->item->giTag]
#else
				&& !other->client->ps.stats[STAT_HOLDABLE_ITEM]
#endif
			) {
				respawn = Pickup_Holdable(ent, other);
			}
			else
			{
				return;
			}

			break;

		default:
			return;
	}

	if (!respawn)
	{
		return;
	}

	G_LogPrintf( "Item: %i %s\n", other->s.number, ent->item->classname );

	// play the normal pickup sound
	G_AddPredictableEvent( other, EV_ITEM_PICKUP, ent->s.modelindex | (ent->s.modelindex2 << 8) );

	// powerup pickups are global broadcasts
	if ((ent->item->giType == IT_POWERUP) || (ent->item->giType == IT_TEAM))
	{
		char powerupcmd[32];

		// if we want the global sound to play
		if (!ent->speed)
		{
			gentity_t  *te;

			te		= G_TempEntity( ent->s.pos.trBase, EV_GLOBAL_ITEM_PICKUP );
			te->s.eventParm = ent->s.modelindex | (ent->s.modelindex2 << 8);
			te->r.svFlags  |= SVF_BROADCAST;
		}
		else
		{
			gentity_t  *te;

			te		   = G_TempEntity( ent->s.pos.trBase, EV_GLOBAL_ITEM_PICKUP );
			te->s.eventParm    = ent->s.modelindex | (ent->s.modelindex2 << 8);
			// only send this temp entity to a single client
			te->r.svFlags	  |= SVF_SINGLECLIENT;
			te->r.singleClient = other->s.number;
		}
	/***
		s.e.t.i. : Use global broadast to generate a cg_followpowerup command
			Gametypes:
				* CTF : Flag has been grabbed by other->client->ps.clientNum
				* Bomb : Bomb has been picked up by other->client->ps.clientNum
	***/
		Com_sprintf(powerupcmd, 32, "followpowerup %i", other->client->ps.clientNum);

		//trap_Argv(1, clientnum, sizeof(char)*2);
		// Send to client -1, which broadcasts to all clients
		trap_SendServerCommand(-1, powerupcmd);
	}

	// fire item targets
	G_UseTargets (ent, other);

	// wait of -1 will not respawn
	if (ent->wait == -1)
	{
		ent->r.svFlags		 	 |= SVF_NOCLIENT;
		ent->s.eFlags		 		 |= EF_NODRAW | EF_NOPICKUP;
		ent->r.contents 	    = 0;
		ent->unlinkAfterEvent = qtrue;
		return;
	}

	// non zero wait overrides respawn time
	if (ent->wait)
	{
		respawn = ent->wait;
	}

	// random can be used to vary the respawn time
	if (ent->random)
	{
		respawn += crandom() * ent->random;

		if (respawn < 1)
		{
			respawn = 1;
		}
	}

	// dropped items will not respawn
	if (ent->flags & FL_DROPPED_ITEM)
	{
		ent->freeAfterEvent = qtrue;
	}

	// picked up items still stay around, they just don't
	// draw anything.  This allows respawnable items
	// to be placed on movers.
	ent->r.svFlags |= SVF_NOCLIENT;
	ent->s.eFlags  |= EF_NODRAW | EF_NOPICKUP;
	ent->r.contents = 0;

	// ZOID
	// A negative respawn times means to never respawn this item (but don't
	// delete it).	This is used by items that are respawned by third party
	// events such as ctf flags
	if (respawn <= 0)
	{
		ent->nextthink = 0;
		ent->think	   = 0;
	}
	else
	{
		ent->nextthink = level.time + respawn * 1000;
		ent->think	   = RespawnItem;
	}
	trap_LinkEntity( ent );
}



//======================================================================

/*
================
LaunchItem

Spawns an item and tosses it forward
================
*/
#ifdef USE_WEAPON_DROP
gentity_t *LaunchItem( gitem_t *item, vec3_t origin, vec3_t velocity, int xr_flags )
#else
gentity_t *LaunchItem( gitem_t *item, vec3_t origin, vec3_t velocity )
#endif
{
	gentity_t	*dropped;

	dropped = G_Spawn();

	dropped->s.eType = ET_ITEM;
	dropped->s.modelindex = (item - bg_itemlist) & 0xFF;	// store item number in modelindex
	dropped->s.modelindex2 = (item - bg_itemlist) >> 8;	// store item number in modelindex
	//dropped->s.modelindex2 = 1; // This is non-zero is it's a dropped item

	// item scale-down
	dropped->s.time = level.time;

	dropped->classname = item->classname;
	dropped->item = item;
	VectorSet (dropped->r.mins, -ITEM_RADIUS, -ITEM_RADIUS, -ITEM_RADIUS);
	VectorSet (dropped->r.maxs, ITEM_RADIUS, ITEM_RADIUS, ITEM_RADIUS);
	dropped->r.contents = CONTENTS_TRIGGER;

	dropped->touch = Touch_Item;

	G_SetOrigin( dropped, origin );
	dropped->s.pos.trType = TR_GRAVITY;
	dropped->s.pos.trTime = level.time;
	VectorCopy( velocity, dropped->s.pos.trDelta );

	dropped->s.eFlags |= EF_BOUNCE_HALF;
	if ((g_gametype.integer == GT_CTF 
#ifdef MISSIONPACK
    || g_gametype.integer == GT_1FCTF
#endif
  ) && item->giType == IT_TEAM) {// Special case for CTF flags
		dropped->think = Team_DroppedFlagThink;
#ifdef USE_TEAM_VARS
    dropped->nextthink = level.time + g_flagReturn.integer;
#else
    dropped->nextthink = level.time + DROPPED_TIME;
#endif
		Team_CheckDroppedItem( dropped );
	} else { // auto-remove after 30 seconds
		dropped->think = G_FreeEntity;
    dropped->nextthink = level.time + DROPPED_TIME;
	}

#ifdef USE_WEAPON_DROP
	dropped->flags = xr_flags; // FL_DROPPED_ITEM; // XRAY FMJ FL_THROWN_ITEM

  if( xr_flags & FL_THROWN_ITEM) {
    dropped->clipmask = MASK_SHOT; // XRAY FMJ
    dropped->s.pos.trTime = level.time - 100;	// move a bit on the very first frame
    VectorScale( velocity, 200, dropped->s.pos.trDelta ); // 700
    SnapVector( dropped->s.pos.trDelta );		// save net bandwidth
    dropped->physicsBounce = 0.5;
  }
#else
	dropped->flags = FL_DROPPED_ITEM;
#endif

	trap_LinkEntity (dropped);

	return dropped;
}

/*
================
Drop_Item

Spawns an item and tosses it forward
================
*/
gentity_t *Drop_Item( gentity_t *ent, gitem_t *item, float angle ) {
	vec3_t	velocity;
	vec3_t	angles;

	VectorCopy( ent->s.apos.trBase, angles );
	angles[YAW] += angle;
	angles[PITCH] = 0;	// always forward

	AngleVectors( angles, velocity, NULL, NULL );
	VectorScale( velocity, 150, velocity );
	velocity[2] += 200 + crandom() * 50;
	

#ifdef USE_WEAPON_DROP
  return LaunchItem( item, ent->s.pos.trBase, velocity, FL_DROPPED_ITEM );
#else
	return LaunchItem( item, ent->s.pos.trBase, velocity );
#endif
}


/*
================
Use_Item

Respawn the item
================
*/
void Use_Item( gentity_t *ent, gentity_t *other, gentity_t *activator ) {
	RespawnItem( ent );
}

//======================================================================

/*
================
FinishSpawningItem

Traces down to find where an item should rest, instead of letting them
free fall from their spawn points
================
*/
void FinishSpawningItem( gentity_t *ent ) {
	trace_t		tr;
	vec3_t		dest;

	VectorSet( ent->r.mins, -ITEM_RADIUS, -ITEM_RADIUS, -ITEM_RADIUS );
	VectorSet( ent->r.maxs, ITEM_RADIUS, ITEM_RADIUS, ITEM_RADIUS );

	ent->s.eType = ET_ITEM;
	ent->s.modelindex = (ent->item - bg_itemlist) & 0xFF;	// store item number in modelindex
	ent->s.modelindex2 = (ent->item - bg_itemlist) >> 8;	// store item number in modelindex
	//ent->s.modelindex = ent->item - bg_itemlist;		// store item number in modelindex
	//ent->s.modelindex2 = 0; // zero indicates this isn't a dropped item

	ent->r.contents = CONTENTS_TRIGGER;
	ent->touch = Touch_Item;
	// using an item causes it to respawn
	ent->use = Use_Item;

	// for pickup prediction
	if ( ent->count ) {
		ent->s.time2 = ent->count;
	} else if ( ent->item ) {
		ent->s.time2 = ent->item->quantity;	
	}

	if ( ent->spawnflags & 1 ) {
		// suspended
		G_SetOrigin( ent, ent->s.origin );
	} else {
		// drop to floor
		VectorSet( dest, ent->s.origin[0], ent->s.origin[1], ent->s.origin[2] - 4096 );
		trap_Trace( &tr, ent->s.origin, ent->r.mins, ent->r.maxs, dest, ent->s.number, MASK_SOLID );
		if ( tr.startsolid ) {
			G_Printf ("FinishSpawningItem: %s startsolid at %s\n", ent->classname, vtos(ent->s.origin));
			G_FreeEntity( ent );
			return;
		}

		// allow to ride movers
		ent->s.groundEntityNum = tr.entityNum;

		G_SetOrigin( ent, tr.endpos );
	}

	// team slaves and targeted items aren't present at start
	if ( ( ent->flags & FL_TEAMSLAVE ) || ent->targetname ) {
		ent->s.eFlags |= EF_NODRAW;
		ent->r.contents = 0;
		return;
	}

	trap_LinkEntity( ent );
}


qboolean	itemRegistered[MAX_ITEMS];

/*
==================
G_CheckTeamItems
==================
*/
void G_CheckTeamItems( void ) {

	// Set up team stuff
	Team_InitGame();

	if( g_gametype.integer == GT_CTF ) {
		gitem_t	*item;

		// check for the two flags
		item = BG_FindItem( "Red Flag" );
		if ( !item || !itemRegistered[ item - bg_itemlist ] ) {
			G_Printf( S_COLOR_YELLOW "WARNING: No team_CTF_redflag in map\n" );
		}
		item = BG_FindItem( "Blue Flag" );
		if ( !item || !itemRegistered[ item - bg_itemlist ] ) {
			G_Printf( S_COLOR_YELLOW "WARNING: No team_CTF_blueflag in map\n" );
		}
	}
#ifdef MISSIONPACK
	if( g_gametype.integer == GT_1FCTF ) {
		gitem_t	*item;

		// check for all three flags
		item = BG_FindItem( "Red Flag" );
		if ( !item || !itemRegistered[ item - bg_itemlist ] ) {
			G_Printf( S_COLOR_YELLOW "WARNING: No team_CTF_redflag in map\n" );
		}
		item = BG_FindItem( "Blue Flag" );
		if ( !item || !itemRegistered[ item - bg_itemlist ] ) {
			G_Printf( S_COLOR_YELLOW "WARNING: No team_CTF_blueflag in map\n" );
		}
		item = BG_FindItem( "Neutral Flag" );
		if ( !item || !itemRegistered[ item - bg_itemlist ] ) {
			G_Printf( S_COLOR_YELLOW "WARNING: No team_CTF_neutralflag in map\n" );
		}
	}

	if( g_gametype.integer == GT_OBELISK ) {
		gentity_t	*ent;

		// check for the two obelisks
		ent = NULL;
		ent = G_Find( ent, FOFS(classname), "team_redobelisk" );
		if( !ent ) {
			G_Printf( S_COLOR_YELLOW "WARNING: No team_redobelisk in map\n" );
		}

		ent = NULL;
		ent = G_Find( ent, FOFS(classname), "team_blueobelisk" );
		if( !ent ) {
			G_Printf( S_COLOR_YELLOW "WARNING: No team_blueobelisk in map\n" );
		}
	}

	if( g_gametype.integer == GT_HARVESTER ) {
		gentity_t	*ent;

		// check for all three obelisks
		ent = NULL;
		ent = G_Find( ent, FOFS(classname), "team_redobelisk" );
		if( !ent ) {
			G_Printf( S_COLOR_YELLOW "WARNING: No team_redobelisk in map\n" );
		}

		ent = NULL;
		ent = G_Find( ent, FOFS(classname), "team_blueobelisk" );
		if( !ent ) {
			G_Printf( S_COLOR_YELLOW "WARNING: No team_blueobelisk in map\n" );
		}

		ent = NULL;
		ent = G_Find( ent, FOFS(classname), "team_neutralobelisk" );
		if( !ent ) {
			G_Printf( S_COLOR_YELLOW "WARNING: No team_neutralobelisk in map\n" );
		}
	}
#endif
}

/*
==============
ClearRegisteredItems
==============
*/
void ClearRegisteredItems( void ) {
	memset( itemRegistered, 0, sizeof( itemRegistered ) );

	// players always start with the base weapon
	RegisterItem( BG_FindItemForWeapon( WP_MACHINEGUN ) );
	RegisterItem( BG_FindItemForWeapon( WP_GAUNTLET ) );
#ifdef USE_FLAME_THROWER
  RegisterItem( BG_FindItemForWeapon( WP_FLAME_THROWER) );
#endif
#ifdef MISSIONPACK
	if( g_gametype.integer == GT_HARVESTER ) {
		RegisterItem( BG_FindItem( "Red Cube" ) );
		RegisterItem( BG_FindItem( "Blue Cube" ) );
	}
#endif
#ifdef USE_TRINITY
  if(g_unholyTrinity.integer) {
	  RegisterItem( BG_FindItemForWeapon( WP_RAILGUN ) );
    RegisterItem( BG_FindItemForWeapon( WP_LIGHTNING ) );
    RegisterItem( BG_FindItemForWeapon( WP_ROCKET_LAUNCHER ) );
  }
#endif
#ifdef USE_ROTRPG
  if(g_hotRockets.integer) {
    RegisterItem( BG_FindItemForWeapon( WP_ROCKET_LAUNCHER ) );
  }
#endif
#ifdef USE_INSTAGIB
  if(g_instagib.integer)
  //register that rail gun
	  RegisterItem( BG_FindItemForWeapon( WP_RAILGUN ) );
#endif
}

/*
===============
RegisterItem

The item will be added to the precache list
===============
*/
void RegisterItem( gitem_t *item ) {
	if ( !item ) {
		G_Error( "RegisterItem: NULL" );
	}
	itemRegistered[ item - bg_itemlist ] = qtrue;
}


/*
===============
SaveRegisteredItems

Write the needed items to a config string
so the client will know which ones to precache
===============
*/
void SaveRegisteredItems( void ) {
	char	string[MAX_ITEMS+1];
	int		i;
	int		count;

	count = 0;
	for ( i = 0 ; i < bg_numItems ; i++ ) {
		if ( itemRegistered[i] ) {
			count++;
			string[i] = '1';
		} else {
			string[i] = '0';
		}
	}
	string[ bg_numItems ] = 0;

	G_Printf( "%i items registered\n", count );
	trap_SetConfigstring(CS_ITEMS, string);
}

/*
============
G_ItemDisabled
============
*/
int G_ItemDisabled( gitem_t *item ) {

	char name[128];

	Com_sprintf(name, sizeof(name), "disable_%s", item->classname);
	return trap_Cvar_VariableIntegerValue( name );
}


void G_GiveItem(gentity_t *ent, powerup_t pw) {
	gitem_t		*it;
	gentity_t *it_ent;
	trace_t		trace;
	it = BG_FindItemForPowerup (pw);
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


/*
============
G_SpawnItem

Sets the clipping size and plants the object on the floor.

Items can't be immediately dropped to floor, because they might
be on an entity that hasn't spawned yet.
============
*/
void G_SpawnItem( gentity_t *ent, gitem_t *item ) {

	G_SpawnFloat( "random", "0", &ent->random );
	G_SpawnFloat( "wait", "0", &ent->wait );

	if(item->giType != IT_TEAM) {
		ent->nothot = qtrue;
	}

  if(item->giType != IT_TEAM && (qfalse
#ifdef USE_INSTAGIB
		|| g_instagib.integer 
#endif
#ifdef USE_HOTRPG
		|| g_hotRockets.integer
#endif
#ifdef USE_HOTBFG
		|| g_hotBFG.integer
#endif
#ifdef USE_TRINITY
		|| g_unholyTrinity.integer
#endif
	)) {
		// don't send items to clients
		ent->r.svFlags = SVF_NOCLIENT;
		ent->s.eFlags |= EF_NODRAW;
    ent->tag = TAG_DONTSPAWN;
	} else {
		RegisterItem( item );

		if ( G_ItemDisabled( item ) ) {
			ent->tag = TAG_DONTSPAWN;
			return;
		}
  }

	ent->item = item;
	// some movers spawn on the second frame, so delay item
	// spawns until the third frame so they can ride trains
	ent->nextthink = level.time + FRAMETIME * 2;
	ent->think = FinishSpawningItem;

	ent->physicsBounce = 0.50;		// items are bouncy

	if ( item->giType == IT_POWERUP ) {
		G_SoundIndex( "sound/items/poweruprespawn.wav" );
		G_SpawnFloat( "noglobalsound", "0", &ent->speed);
	}

#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS)
	if ( item->giType == IT_PERSISTANT_POWERUP ) {
		ent->s.generic1 = ent->spawnflags;
	}
#endif
}


/*
================
G_BounceItem

================
*/
void G_BounceItem( gentity_t *ent, trace_t *trace ) {
	vec3_t	velocity;
	float	dot;
	int		hitTime;

	// reflect the velocity on the trace plane
	hitTime = level.previousTime + ( level.time - level.previousTime ) * trace->fraction;
	BG_EvaluateTrajectoryDelta( &ent->s.pos, hitTime, velocity );
	dot = DotProduct( velocity, trace->plane.normal );
	VectorMA( velocity, -2*dot, trace->plane.normal, ent->s.pos.trDelta );

	// cut the velocity to keep from bouncing forever
	VectorScale( ent->s.pos.trDelta, ent->physicsBounce, ent->s.pos.trDelta );

	// check for stop
	if ( trace->plane.normal[2] > 0 && ent->s.pos.trDelta[2] < 40 ) {
		trace->endpos[2] += 1.0;	// make sure it is off ground
		SnapVector( trace->endpos );
		G_SetOrigin( ent, trace->endpos );
		ent->s.groundEntityNum = trace->entityNum;
		return;
	}

	VectorAdd( ent->r.currentOrigin, trace->plane.normal, ent->r.currentOrigin);
	VectorCopy( ent->r.currentOrigin, ent->s.pos.trBase );
	ent->s.pos.trTime = level.time;
}


/*
================
G_RunItem

================
*/
void G_RunItem( gentity_t *ent ) {
	vec3_t		origin;
	trace_t		tr;
	int			contents;
	int			mask;

	// if its groundentity has been set to ENTITYNUM_NONE, it may have been pushed off an edge
	if ( ent->s.groundEntityNum == ENTITYNUM_NONE ) {
		if ( ent->s.pos.trType != TR_GRAVITY ) {
			ent->s.pos.trType = TR_GRAVITY;
			ent->s.pos.trTime = level.time;
		}
	}

	if ( ent->s.pos.trType == TR_STATIONARY ) {
		// check think function
		G_RunThink( ent );
		return;
	}

	// get current position
	BG_EvaluateTrajectory( &ent->s.pos, level.time, origin );

	// trace a line from the previous position to the current position
	if ( ent->clipmask ) {
		mask = ent->clipmask;
	} else {
		mask = MASK_PLAYERSOLID & ~CONTENTS_BODY;//MASK_SOLID;
	}
	trap_Trace( &tr, ent->r.currentOrigin, ent->r.mins, ent->r.maxs, origin, 
		ent->r.ownerNum, mask );

	VectorCopy( tr.endpos, ent->r.currentOrigin );

	if ( tr.startsolid ) {
		tr.fraction = 0;
	}

	trap_LinkEntity( ent );	// FIXME: avoid this for stationary?

	// check think function
	G_RunThink( ent );

	if ( tr.fraction == 1 ) {
		return;
	}

	// if it is in a nodrop volume, remove it
	contents = trap_PointContents( ent->r.currentOrigin, -1 );
	if ( contents & CONTENTS_NODROP ) {
		if (ent->item && ent->item->giType == IT_TEAM) {
			Team_FreeEntity(ent);
		} else {
			G_FreeEntity( ent );
		}
		return;
	}

	G_BounceItem( ent, &tr );
}
