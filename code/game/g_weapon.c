// Copyright (C) 1999-2000 Id Software, Inc.
//
// g_weapon.c 
// perform the server side effects of a weapon firing

#include "g_local.h"

static	float	s_quadFactor;
static	vec3_t	forward, right, up;
static	vec3_t	muzzle;
static	vec3_t	muzzle_origin; // for hitscan weapon trace

#define NUM_NAILSHOTS 15

#ifdef USE_LV_DISCHARGE
qboolean G_WaterRadiusDamage (vec3_t origin, gentity_t *attacker, 
  float damage, float radius, gentity_t *ignore, int mod);
#endif

#ifdef USE_VULN_RPG
#define IsSelf(x, y) i == 0 \
  && !(x.surfaceFlags & SURF_NOIMPACT) \
  && x.entityNum == ent->s.number
#endif

/*
===============
CalcMuzzlePointOrigin
===============
*/
void CalcMuzzlePointOrigin( const gentity_t *ent, vec3_t origin, const vec3_t forward, const vec3_t right, const vec3_t up, vec3_t muzzlePoint ) {
	VectorCopy( ent->client->ps.origin, origin );
	origin[2] += ent->client->ps.viewheight;
	VectorMA( origin, 14.0, forward, muzzlePoint );
	// snap to integer coordinates for more efficient network bandwidth usage
	//SnapVector( muzzlePoint );
}


/*
================
G_BounceProjectile
================
*/
void G_BounceProjectile( vec3_t start, vec3_t impact, vec3_t dir, vec3_t endout ) {
	vec3_t v, newv;
	float dot;

	VectorSubtract( impact, start, v );
	dot = DotProduct( v, dir );
	VectorMA( v, -2*dot, dir, newv );

	VectorNormalize(newv);
	VectorMA(impact, 8192, newv, endout);
}


/*
======================================================================

GAUNTLET

======================================================================
*/

void Weapon_Gauntlet( gentity_t *ent ) {

}

/*
===============
CheckGauntletAttack
===============
*/
qboolean CheckGauntletAttack( gentity_t *ent ) {
	trace_t		tr;
	vec3_t		end;
	gentity_t	*tent;
	gentity_t	*traceEnt;
	int			damage;
	
	// set aiming directions
	AngleVectors( ent->client->ps.viewangles, forward, right, up );

	CalcMuzzlePointOrigin( ent, muzzle_origin, forward, right, up, muzzle );

	VectorMA( muzzle_origin, ( 32.0 + 14.0 ), forward, end );

	trap_Trace( &tr, muzzle_origin, NULL, NULL, end, ent->s.number, MASK_SHOT );
	if ( tr.surfaceFlags & SURF_NOIMPACT ) {
		return qfalse;
	}

	if ( ent->client->noclip ) {
		return qfalse;
	}

	traceEnt = &g_entities[ tr.entityNum ];

	// send blood impact
	if ( traceEnt->takedamage && traceEnt->client ) {
		tent = G_TempEntity( tr.endpos, EV_MISSILE_HIT );
		tent->s.otherEntityNum = traceEnt->s.number;
		tent->s.eventParm = DirToByte( tr.plane.normal );
		tent->s.weapon = ent->s.weapon;
	}

	if ( !traceEnt->takedamage ) {
		return qfalse;
	}

#ifdef USE_ADVANCED_ITEMS
	if (ent->client->inventory[PW_QUAD] ) 
#else
	if (ent->client->ps.powerups[PW_QUAD] )
#endif
	{
		G_AddEvent( ent, EV_POWERUP_QUAD, 0 );
#ifdef USE_RUNES
  if(ent->client->inventory[RUNE_BERSERK]) {
    s_quadFactor = 6.0;
  } else
  if(ent->client->inventory[RUNE_STRENGTH]) {
    s_quadFactor = 2.0;
  } else
#endif
		s_quadFactor = g_quadfactor.value;
	} else {
		s_quadFactor = 1.0;
	}
#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS)
	if( ent->client->persistantPowerup && ent->client->persistantPowerup->item && ent->client->persistantPowerup->item->giTag == PW_DOUBLER ) {
		s_quadFactor *= 2;
	}
#endif

#ifdef USE_WEAPON_VARS
	damage = wp_gauntDamage.integer * s_quadFactor;
#else
  damage = 50 * s_quadFactor;
#endif
	G_Damage( traceEnt, ent, ent, forward, tr.endpos, damage, 0, MOD_GAUNTLET );

	return qtrue;
}


/*
======================================================================

MACHINEGUN

======================================================================
*/

/*
======================
SnapVectorTowards

Round a vector to integers for more efficient network
transmission, but make sure that it rounds towards a given point
rather than blindly truncating.  This prevents it from truncating 
into a wall.
======================
*/
void SnapVectorTowards( vec3_t v, vec3_t to ) {
	int		i;

	for ( i = 0 ; i < 3 ; i++ ) {
		if ( v[i] < 0 ) {
			if ( to[i] >= v[i])
			v[i] = (int)v[i];
			else
				v[i] = (int)v[i] - 1;
		} else {
			if ( to[i] <= v[i] )
				v[i] = (int)v[i];
			else
			v[i] = (int)v[i] + 1;
		}
	}
}

#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS) || defined(USE_ADVANCED_CLASS)
#define CHAINGUN_SPREAD		600
#endif
#define MACHINEGUN_SPREAD	200
#define	MACHINEGUN_DAMAGE	7
#define	MACHINEGUN_TEAM_DAMAGE	5		// wimpier MG in teamplay

static void Bullet_Fire( gentity_t *ent, float spread, int damage ) {
	trace_t		tr;
	vec3_t		end;
#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS) || defined(USE_ADVANCED_ITEMS)
	vec3_t		impactpoint, bouncedir;
#endif
	float		r;
	float		u;
	gentity_t	*tent;
	gentity_t	*traceEnt;
	int			i, passent;

	damage *= s_quadFactor;

	r = random() * M_PI * 2.0f;
	u = sin(r) * crandom() * spread * 16;
	r = cos(r) * crandom() * spread * 16;

	VectorMA( muzzle_origin, ( 8192.0 * 16.0 ), forward, end );
	VectorMA( end, r, right, end );
	VectorMA( end, u, up, end );

	passent = ent->s.number;
	for ( i = 0; i < 10; i++ ) {

		// unlagged
		G_DoTimeShiftFor( ent );

#ifdef USE_VULN_RPG
    if(wp_rocketVuln.integer) {
      trap_Trace( &tr, muzzle_origin, NULL, NULL, end, ENTITYNUM_NONE, MASK_SHOT );
      // double check we aren't hitting ourselves on the first pass
      if(IsSelf(tr, ent)) {
        // do another trace that skips ourselves
        trap_Trace( &tr, muzzle_origin, NULL, NULL, end, ent->s.number, MASK_SHOT );
      }
    } else
#endif
		trap_Trace( &tr, muzzle_origin, NULL, NULL, end, passent, MASK_SHOT );

		// unlagged
		G_UndoTimeShiftFor( ent );

		if ( tr.surfaceFlags & SURF_NOIMPACT )
			return;

		traceEnt = &g_entities[ tr.entityNum ];

		// snap the endpos to integers, but nudged towards the line
		SnapVectorTowards( tr.endpos, muzzle_origin );

		// send bullet impact
		if ( traceEnt->takedamage && traceEnt->client ) {
			tent = G_TempEntity( tr.endpos, EV_BULLET_HIT_FLESH );
			tent->s.eventParm = traceEnt->s.number;

			// unlagged
			tent->s.clientNum = ent->s.clientNum;

			if( LogAccuracyHit( traceEnt, ent ) ) {
				ent->client->accuracy_hits++;
			}
		} else {
			tent = G_TempEntity( tr.endpos, EV_BULLET_HIT_WALL );
			tent->s.eventParm = DirToByte( tr.plane.normal );
		}
		tent->s.otherEntityNum = ent->s.number;

		if ( traceEnt->takedamage ) {
#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS) || defined(USE_ADVANCED_ITEMS) || defined(USE_RUNES)
			if ( traceEnt->client && traceEnt->client->invulnerabilityTime > level.time ) {
				if (G_InvulnerabilityEffect( traceEnt, forward, tr.endpos, impactpoint, bouncedir )) {
					G_BounceProjectile( muzzle, impactpoint, bouncedir, end );
					VectorCopy( impactpoint, muzzle );
					// the player can hit him/herself with the bounced rail
					passent = ENTITYNUM_NONE;
				}
				else {
					VectorCopy( tr.endpos, muzzle );
					passent = traceEnt->s.number;
				}
				continue;
			}
			else {
#endif
				G_Damage( traceEnt, ent, ent, forward, tr.endpos, damage, 0, MOD_MACHINEGUN );
#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS) || defined(USE_ADVANCED_ITEMS)
			}
#endif
		}
		break;
	}
}


/*
======================================================================

BFG

======================================================================
*/

void BFG_Fire( gentity_t *ent ) {
	gentity_t *m;

	m = fire_bfg( ent, muzzle, forward );
#ifdef USE_HOTBFG
  if(g_hotBFG.integer) {
    m->damage *= 1.5;
  	m->splashRadius *= 2;
  } else 
#endif
  {
  	m->damage *= s_quadFactor;
  	m->splashDamage *= s_quadFactor;
  }
//	VectorAdd( m->s.pos.trDelta, ent->client->ps.velocity, m->s.pos.trDelta );	// "real" physics
}


/*
======================================================================

SHOTGUN

======================================================================
*/

// DEFAULT_SHOTGUN_SPREAD and DEFAULT_SHOTGUN_COUNT	are in bg_public.h, because
// client predicts same spreads
#define	DEFAULT_SHOTGUN_DAMAGE	10

static qboolean ShotgunPellet( const vec3_t start, const vec3_t end, gentity_t *ent ) {
	trace_t		tr;
	int			damage, i, passent;
	gentity_t	*traceEnt;
#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS) || defined(USE_ADVANCED_ITEMS)
	vec3_t		impactpoint, bouncedir;
#endif
	vec3_t		tr_start, tr_end;
	qboolean	hitClient = qfalse;

	passent = ent->s.number;
	VectorCopy( start, tr_start );
	VectorCopy( end, tr_end );

	for ( i = 0; i < 10; i++ ) {
		trap_Trace( &tr, tr_start, NULL, NULL, tr_end, passent, MASK_SHOT );
		traceEnt = &g_entities[ tr.entityNum ];

		// send bullet impact
		if (  tr.surfaceFlags & SURF_NOIMPACT ) {
			return qfalse;
		}

		if ( traceEnt->takedamage ) {
#ifdef USE_WEAPON_VARS
      damage = wp_shotgunDamage.integer * s_quadFactor;
#else
			damage = DEFAULT_SHOTGUN_DAMAGE * s_quadFactor;
#endif
#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS) || defined(USE_ADVANCED_ITEMS) || defined(USE_RUNES)
			if ( traceEnt->client && traceEnt->client->invulnerabilityTime > level.time ) {
				if (G_InvulnerabilityEffect( traceEnt, forward, tr.endpos, impactpoint, bouncedir )) {
					G_BounceProjectile( tr_start, impactpoint, bouncedir, tr_end );
					VectorCopy( impactpoint, tr_start );
					// the player can hit him/herself with the bounced rail
					passent = ENTITYNUM_NONE;
				}
				else {
					VectorCopy( tr.endpos, tr_start );
					passent = traceEnt->s.number;
				}
				continue;
			}
#endif
			if ( LogAccuracyHit( traceEnt, ent ) ) {
				hitClient = qtrue;
			}
			G_Damage( traceEnt, ent, ent, forward, tr.endpos, damage, 0, MOD_SHOTGUN );
			return hitClient;
		}
		return qfalse;
	}
	return qfalse;
}


// this should match CG_ShotgunPattern
static void ShotgunPattern( const vec3_t origin, const vec3_t origin2, int seed, gentity_t *ent ) {
	int			i;
	float		r, u;
	vec3_t		end;
	vec3_t		forward, right, up;
	qboolean	hitClient = qfalse;

	// derive the right and up vectors from the forward vector, because
	// the client won't have any other information
	VectorNormalize2( origin2, forward );
	PerpendicularVector( right, forward );
	CrossProduct( forward, right, up );

	// unlagged
	G_DoTimeShiftFor( ent );

	// generate the "random" spread pattern
	for ( i = 0 ; i < DEFAULT_SHOTGUN_COUNT ; i++ ) {
		r = Q_crandom( &seed ) * DEFAULT_SHOTGUN_SPREAD * 16;
		u = Q_crandom( &seed ) * DEFAULT_SHOTGUN_SPREAD * 16;
		VectorMA( origin, ( 8192.0 * 16.0 ), forward, end );
		VectorMA( end, r, right, end );
		VectorMA( end, u, up, end );
		if ( ShotgunPellet( origin, end, ent ) && !hitClient ) {
			hitClient = qtrue;
			ent->client->accuracy_hits++;
		}
	}

	// unlagged
	G_UndoTimeShiftFor( ent );
}


static void weapon_supershotgun_fire( gentity_t *ent ) {
	gentity_t		*tent;

	// send shotgun blast
	tent = G_TempEntity( muzzle, EV_SHOTGUN );
	VectorScale( forward, 4096.0, tent->s.origin2 );

	SnapVector( tent->s.origin2 );
	tent->s.eventParm = rand() & 255;		// seed for spread pattern
	tent->s.otherEntityNum = ent->s.number;

	ShotgunPattern( muzzle_origin, tent->s.origin2, tent->s.eventParm, ent );
}

#if defined(USE_CLUSTER_GRENADES) || defined(USE_RUNES)
gentity_t *fire_special_grenade (gentity_t *self, vec3_t start, vec3_t dir, qboolean isCluster, qboolean isVortex);
#endif

/*
======================================================================

GRENADE LAUNCHER

======================================================================
*/

void weapon_grenadelauncher_fire (gentity_t *ent) {
	gentity_t	*m;

	// extra vertical velocity
	forward[2] += 0.2f;
	VectorNormalize( forward );

#if defined(USE_CLUSTER_GRENADES) || defined(USE_RUNES)
#ifdef USE_RUNES
	if(ent->client->inventory[RUNE_CLUSTER]) {
		m = fire_special_grenade (ent, muzzle, forward, qtrue, wp_grenadeVortex.integer);
	} else
#endif
	if(wp_grenadeCluster.integer || wp_grenadeVortex.integer) {
		m = fire_special_grenade (ent, muzzle, forward, wp_grenadeCluster.integer, wp_grenadeVortex.integer);
	} else
#endif
	m = fire_grenade (ent, muzzle, forward);
	m->damage *= s_quadFactor;
	m->splashDamage *= s_quadFactor;

//	VectorAdd( m->s.pos.trDelta, ent->client->ps.velocity, m->s.pos.trDelta );	// "real" physics
}


#if defined(USE_BOUNCE_RPG) || defined(USE_HOMING_MISSILE) || defined(USE_VULN_RPG) || defined(USE_ACCEL_RPG)
gentity_t *fire_special_rocket (gentity_t *self, vec3_t start, vec3_t dir,
qboolean bounce, qboolean homing, qboolean vulnerable, qboolean accelerate);
#endif

/*
======================================================================

ROCKET

======================================================================
*/

#if defined(USE_ADVANCED_WEAPONS) || defined(USE_ADVANCED_ITEMS) || defined(USE_ADVANCED_CLASS) || defined(USE_HOMING_MISSILE)
void Weapon_RocketLauncher_Fire (gentity_t *ent, qboolean isHoming)
#else
void Weapon_RocketLauncher_Fire (gentity_t *ent)
#endif
{
	gentity_t	*m;

#ifdef USE_BOUNCE_RPG
	if(wp_rocketBounce.integer) {
		m = fire_special_rocket(ent, muzzle, forward, qtrue, isHoming, qfalse, qfalse);
	} else
#endif
#ifdef USE_HOMING_MISSILE
  if(wp_rocketHoming.integer || isHoming) {
		m = fire_special_rocket(ent, muzzle, forward, qfalse, isHoming, qfalse, qfalse);
	} else
#endif
#ifdef USE_VULN_RPG
  if(wp_rocketVuln.integer) {
		m = fire_special_rocket(ent, muzzle, forward, qfalse, isHoming, qtrue, qfalse);
	} else
#endif
#ifdef USE_ACCEL_RPG
  if(wp_rocketAccel.integer) {
		m = fire_special_rocket(ent, muzzle, forward, qfalse, isHoming, qfalse, qtrue);
	} else
#endif

	m = fire_rocket (ent, muzzle, forward);

#ifdef USE_HOTRPG
  if(g_hotRockets.integer) {
    m->damage *= g_quadfactor.value;
  	m->splashDamage *= g_quadfactor.value;
  } else 
#endif
#ifdef USE_TRINITY
  if(g_unholyTrinity.integer) {
    m->damage *= g_quadfactor.value;
  	m->splashDamage *= g_quadfactor.value;
  } else 
#endif
  {
	m->damage *= s_quadFactor;
	m->splashDamage *= s_quadFactor;
  }
//	VectorAdd( m->s.pos.trDelta, ent->client->ps.velocity, m->s.pos.trDelta );	// "real" physics
}


/*
======================================================================

PLASMA GUN

======================================================================
*/

void Weapon_Plasmagun_Fire (gentity_t *ent) {
	gentity_t	*m;

	m = fire_plasma (ent, muzzle, forward);
	m->damage *= s_quadFactor;
	m->splashDamage *= s_quadFactor;

//	VectorAdd( m->s.pos.trDelta, ent->client->ps.velocity, m->s.pos.trDelta );	// "real" physics
}

/*
======================================================================

RAILGUN

======================================================================
*/


/*
=================
weapon_railgun_fire
=================
*/
#define	MAX_RAIL_HITS	4
void weapon_railgun_fire( gentity_t *ent ) {
	vec3_t		end;
#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS) || defined(USE_ADVANCED_ITEMS)
	vec3_t impactpoint, bouncedir;
#endif
	trace_t		trace;
	gentity_t	*tent;
	gentity_t	*traceEnt;
	int			damage;
	int			i;
	int			hits;
	int			unlinked;
	int			passent;
	gentity_t	*unlinkedEntities[MAX_RAIL_HITS];

#ifdef USE_TRINITY
  if(g_unholyTrinity.integer) {
    damage = 500 * s_quadFactor;
  } else 
#endif
#ifdef USE_INSTAGIB
  if(g_instagib.integer) {
    damage = 500 * s_quadFactor;
  } else
#endif
#ifdef USE_WEAPON_VARS
	damage = wp_railDamage.integer * s_quadFactor;
#else
	damage = 100 * s_quadFactor;
#endif

	VectorMA( muzzle_origin, 8192.0, forward, end );

	// unlagged
	G_DoTimeShiftFor( ent );

	// trace only against the solids, so the railgun will go through people
	unlinked = 0;
	hits = 0;
	passent = ent->s.number;
	do {
#ifdef USE_VULN_RPG
    if(wp_rocketVuln.integer) {
      passent = ENTITYNUM_NONE;
    }
#endif
		trap_Trace( &trace, muzzle_origin, NULL, NULL, end, passent, MASK_SHOT );
		if ( trace.entityNum >= ENTITYNUM_MAX_NORMAL ) {
			break;
		}
		traceEnt = &g_entities[ trace.entityNum ];
		if ( traceEnt->takedamage ) {
#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS) || defined(USE_ADVANCED_ITEMS) || defined(USE_RUNES)
			if ( traceEnt->client && traceEnt->client->invulnerabilityTime > level.time ) {
				if ( G_InvulnerabilityEffect( traceEnt, forward, trace.endpos, impactpoint, bouncedir ) ) {
					G_BounceProjectile( muzzle, impactpoint, bouncedir, end );
					// snap the endpos to integers to save net bandwidth, but nudged towards the line
					SnapVectorTowards( trace.endpos, muzzle );
					// send railgun beam effect
					tent = G_TempEntity( trace.endpos, EV_RAILTRAIL );
					// set player number for custom colors on the railtrail
					tent->s.clientNum = ent->s.clientNum;
					VectorCopy( muzzle, tent->s.origin2 );
					// move origin a bit to come closer to the drawn gun muzzle
					VectorMA( tent->s.origin2, 4, right, tent->s.origin2 );
					VectorMA( tent->s.origin2, -1, up, tent->s.origin2 );
					tent->s.eventParm = 255;	// don't make the explosion at the end
					//
					VectorCopy( impactpoint, muzzle );
					// the player can hit him/herself with the bounced rail
					passent = ENTITYNUM_NONE;
				}
			} else
#endif
			{
				if ( LogAccuracyHit( traceEnt, ent ) ) {
					hits++;
				}
				G_Damage( traceEnt, ent, ent, forward, trace.endpos, damage, 0, MOD_RAILGUN );
			}
		}
		if ( trace.contents & CONTENTS_SOLID ) {
			break;		// we hit something solid enough to stop the beam
		}
		// unlink this entity, so the next trace will go past it
		trap_UnlinkEntity( traceEnt );
		unlinkedEntities[unlinked] = traceEnt;
		unlinked++;
	} while ( unlinked < MAX_RAIL_HITS );

	// unlagged
	G_UndoTimeShiftFor( ent );


	// link back in any entities we unlinked
	for ( i = 0 ; i < unlinked ; i++ ) {
		trap_LinkEntity( unlinkedEntities[i] );
	}

	// the final trace endpos will be the terminal point of the rail trail

	// snap the endpos to integers to save net bandwidth, but nudged towards the line
	SnapVectorTowards( trace.endpos, muzzle_origin );

	// send railgun beam effect
	tent = G_TempEntity( trace.endpos, EV_RAILTRAIL );

	// set player number for custom colors on the railtrail
	tent->s.clientNum = ent->s.clientNum;

	VectorCopy( muzzle, tent->s.origin2 );
	// move origin a bit to come closer to the drawn gun muzzle
	VectorMA( tent->s.origin2, 4, right, tent->s.origin2 );
	VectorMA( tent->s.origin2, -1, up, tent->s.origin2 );

	SnapVector( tent->s.origin2 );

	// no explosion at end if SURF_NOIMPACT, but still make the trail
	if ( trace.surfaceFlags & SURF_NOIMPACT ) {
		tent->s.eventParm = 255;	// don't make the explosion at the end
	} else {
		tent->s.eventParm = DirToByte( trace.plane.normal );
	}
	tent->s.clientNum = ent->s.clientNum;

	// give the shooter a reward sound if they have made two railgun hits in a row
	if ( hits == 0 ) {
		// complete miss
		ent->client->accurateCount = 0;
	} else {
		// check for "impressive" reward sound
		ent->client->accurateCount += hits;
		if ( ent->client->accurateCount >= 2 ) {
			ent->client->accurateCount -= 2;
			ent->client->ps.persistant[PERS_IMPRESSIVE_COUNT]++;
			// add the sprite over the player's head
			ent->client->ps.eFlags &= ~EF_AWARDS;
			ent->client->ps.eFlags |= EF_AWARD_IMPRESSIVE;
			ent->client->rewardTime = level.time + REWARD_SPRITE_TIME;
		}
		ent->client->accuracy_hits++;
	}

}


#ifdef USE_GRAPPLE

/*
======================================================================

GRAPPLING HOOK

======================================================================
*/

void Weapon_GrapplingHook_Fire (gentity_t *ent)
{
	if (!ent->client->fireHeld && !ent->client->hook)
		fire_grapple (ent, muzzle, forward);

	ent->client->fireHeld = qtrue;
}


void Weapon_HookFree (gentity_t *ent)
{
	ent->parent->client->hook = NULL;
	ent->parent->client->ps.pm_flags &= ~PMF_GRAPPLE_PULL;
	G_FreeEntity( ent );
}


void Weapon_HookThink (gentity_t *ent)
{
	if (ent->enemy) {
		vec3_t v, oldorigin;

		VectorCopy(ent->r.currentOrigin, oldorigin);
		v[0] = ent->enemy->r.currentOrigin[0] + (ent->enemy->r.mins[0] + ent->enemy->r.maxs[0]) * 0.5;
		v[1] = ent->enemy->r.currentOrigin[1] + (ent->enemy->r.mins[1] + ent->enemy->r.maxs[1]) * 0.5;
		v[2] = ent->enemy->r.currentOrigin[2] + (ent->enemy->r.mins[2] + ent->enemy->r.maxs[2]) * 0.5;
		SnapVectorTowards( v, oldorigin );	// save net bandwidth

		G_SetOrigin( ent, v );
	}

	VectorCopy( ent->r.currentOrigin, ent->parent->client->ps.grapplePoint);
}


#endif

/*
======================================================================

LIGHTNING GUN

======================================================================
*/

void Weapon_LightningFire( gentity_t *ent ) {
	trace_t		tr;
	vec3_t		end;
#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS) || defined(USE_ADVANCED_ITEMS)
	vec3_t impactpoint, bouncedir;
#endif
	gentity_t	*traceEnt, *tent;
	int			damage, i, passent;


#ifdef USE_WEAPON_VARS
  damage = wp_lightDamage.integer * s_quadFactor;
#else
	damage = 8 * s_quadFactor;
#endif

#ifdef USE_TRINITY
  if(g_unholyTrinity.integer) {
    damage *= g_quadfactor.value;
  } else 
#endif

	passent = ent->s.number;

#ifdef USE_LV_DISCHARGE
  VectorMA( muzzle_origin, LIGHTNING_RANGE, forward, end );
  // The SARACEN's Lightning Discharge - START
	if (trap_PointContents (muzzle_origin, -1) & MASK_WATER)
	{
		int zaps;
		gentity_t *tent;

#ifdef USE_ADVANCED_WEAPONS
		zaps = ent->client->classAmmo[WP_LIGHTNING];	// determines size/power of discharge
#else
		zaps = ent->client->ps.ammo[WP_LIGHTNING];	// determines size/power of discharge
#endif
		if (!zaps) return;	// prevents any subsequent frames causing second discharge + error
		zaps++;		// pmove does an ammo[gun]--, so we must compensate
		SnapVectorTowards (muzzle_origin, ent->s.origin);	// save bandwidth

		tent = G_TempEntity (muzzle_origin, EV_LV_DISCHARGE);
		tent->s.eventParm = zaps;				// duration / size of explosion graphic

#ifdef USE_ADVANCED_WEAPONS
		ent->client->classAmmo[WP_LIGHTNING] = 0;		// drain ent's lightning count
#else
		ent->client->ps.ammo[WP_LIGHTNING] = 0;		// drain ent's lightning count
#endif
		if (G_WaterRadiusDamage (muzzle_origin, ent, damage * zaps,
					(damage * zaps) + 16, NULL, MOD_LV_DISCHARGE))
			g_entities[ent->r.ownerNum].client->accuracy_hits++;
		
		return;
	}
  // The SARACEN's Lightning Discharge - END
#endif

	for (i = 0; i < 10; i++) {
		VectorMA( muzzle_origin, LIGHTNING_RANGE, forward, end );

		// unlagged
		G_DoTimeShiftFor( ent );

#ifdef USE_VULN_RPG
    if(wp_rocketVuln.integer) {
      trap_Trace( &tr, muzzle_origin, NULL, NULL, end, ENTITYNUM_NONE, MASK_SHOT );
      // double check we aren't hitting ourselves on the first pass
      if(IsSelf(tr, ent)) {
        // do another trace that skips ourselves
        trap_Trace( &tr, muzzle_origin, NULL, NULL, end, ent->s.number, MASK_SHOT );
      }
    } else
#endif
		trap_Trace( &tr, muzzle_origin, NULL, NULL, end, passent, MASK_SHOT );

		// unlagged
		G_UndoTimeShiftFor( ent );

#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS) || defined(USE_ADVANCED_ITEMS) || defined(USE_RUNES)
		// if not the first trace (the lightning bounced of an invulnerability sphere)
		if (i) {
			// add bounced off lightning bolt temp entity
			// the first lightning bolt is a cgame only visual
			//
			tent = G_TempEntity( muzzle, EV_LIGHTNINGBOLT );
			VectorCopy( tr.endpos, end );
			SnapVector( end );
			VectorCopy( end, tent->s.origin2 );
		}
#endif
		if ( tr.entityNum == ENTITYNUM_NONE ) {
			return;
		}

		traceEnt = &g_entities[ tr.entityNum ];

		if ( traceEnt->takedamage ) {
#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS) || defined(USE_ADVANCED_ITEMS) || defined(USE_RUNES)
			if ( traceEnt->client && traceEnt->client->invulnerabilityTime > level.time ) {
				if (G_InvulnerabilityEffect( traceEnt, forward, tr.endpos, impactpoint, bouncedir )) {
					G_BounceProjectile( muzzle, impactpoint, bouncedir, end );
					VectorCopy( impactpoint, muzzle );
					VectorSubtract( end, impactpoint, forward );
					VectorNormalize(forward);
					// the player can hit him/herself with the bounced lightning
					passent = ENTITYNUM_NONE;
				}
				else {
					VectorCopy( tr.endpos, muzzle );
					passent = traceEnt->s.number;
				}
				continue;
			}
#endif
			if ( LogAccuracyHit( traceEnt, ent ) ) {
				ent->client->accuracy_hits++;
			}
			G_Damage( traceEnt, ent, ent, forward, tr.endpos, damage, 0, MOD_LIGHTNING );
		}

		if ( traceEnt->takedamage && traceEnt->client ) {
			tent = G_TempEntity( tr.endpos, EV_MISSILE_HIT );
			tent->s.otherEntityNum = traceEnt->s.number;
			tent->s.eventParm = DirToByte( tr.plane.normal );
			tent->s.weapon = ent->s.weapon;
		} else if ( !( tr.surfaceFlags & SURF_NOIMPACT ) ) {
			tent = G_TempEntity( tr.endpos, EV_MISSILE_MISS );
			tent->s.eventParm = DirToByte( tr.plane.normal );
			tent->s.weapon = ent->s.weapon;
		}

		break;
	}
}

#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS) || defined(USE_ADVANCED_CLASS)
/*
======================================================================

NAILGUN

======================================================================
*/

void Weapon_Nailgun_Fire (gentity_t *ent) {
	gentity_t	*m;
	int			count;

	for( count = 0; count < NUM_NAILSHOTS; count++ ) {
		m = fire_nail (ent, muzzle, forward, right, up );
		m->damage *= s_quadFactor;
		m->splashDamage *= s_quadFactor;
	}

//	VectorAdd( m->s.pos.trDelta, ent->client->ps.velocity, m->s.pos.trDelta );	// "real" physics
}


/*
======================================================================

PROXIMITY MINE LAUNCHER

======================================================================
*/

void weapon_proxlauncher_fire (gentity_t *ent) {
	gentity_t	*m;

	// extra vertical velocity
	forward[2] += 0.2f;
	VectorNormalize( forward );

	m = fire_prox (ent, muzzle, forward);
	m->damage *= s_quadFactor;
	m->splashDamage *= s_quadFactor;

//	VectorAdd( m->s.pos.trDelta, ent->client->ps.velocity, m->s.pos.trDelta );	// "real" physics
}

#endif

//======================================================================


#ifdef USE_WEAPON_DROP
/*
================
dropWeapon XRAY FMJ
================
*/
gentity_t *dropWeapon( gentity_t *ent, gitem_t *item, float angle, int xr_flags ) { // XRAY FMJ
	vec3_t	velocity;
	vec3_t	origin;

	VectorCopy( ent->s.pos.trBase, origin );

	// set aiming directions
	AngleVectors (ent->client->ps.viewangles, velocity, NULL, NULL);

	origin[2] += ent->client->ps.viewheight;
	VectorMA( origin, 34, velocity, origin ); // 14
	// snap to integer coordinates for more efficient network bandwidth usage
	SnapVector( origin);

	// extra vertical velocity
	velocity[2] += 0.3;
	VectorNormalize( velocity );
	return LaunchItem( item, origin, velocity, xr_flags );
}


/*
=============
ThrowWeapon

XRAY FMJ
=============
*/

gentity_t *ThrowWeapon( gentity_t *ent ) {
	gclient_t	*client;
	usercmd_t	*ucmd;
	gitem_t		*xr_item;
	gentity_t	*xr_drop;
	byte i;
	int amount;

	client = ent->client;
	ucmd = &ent->client->pers.cmd;

	if( client->ps.weapon == WP_GAUNTLET
		|| client->ps.weapon == WP_MACHINEGUN
#ifdef USE_GRAPPLE
		|| client->ps.weapon == WP_GRAPPLING_HOOK
#endif
		|| ( ucmd->buttons & BUTTON_ATTACK )
		// TODO: just make it disappear in mode where it affects speed
#ifdef USE_ADVANCED_WEAPONS
		|| client->classAmmo[client->ps.weapon] == INFINITE
#else
		|| client->ps.ammo[client->ps.weapon] == INFINITE
#endif
		|| client->ps.weapon == WP_NONE)
		return NULL;


	xr_item = BG_FindItemForWeapon( client->ps.weapon );

#ifdef USE_ADVANCED_WEAPONS
	amount = client->classAmmo[ client->ps.weapon ]; // XRAY save amount
	client->ps.classAmmo[ client->ps.weapon % WP_MAX_WEAPONS ] = 0; // assume we're showing the same class currently?
#else
	amount = client->ps.ammo[ client->ps.weapon ]; // XRAY save amount
	client->ps.ammo[ client->ps.weapon ] = 0;
#endif

#ifdef USE_ADVANCED_WEAPONS
	client->classWeapons[client->ps.weapon] = 0;
	client->weaponsModified[client->weaponClass] = qtrue;
#else
	client->ps.stats[STAT_WEAPONS] &= ~( 1 << client->ps.weapon );
#endif
	client->ps.weapon = WP_MACHINEGUN;
	for ( i = WP_NUM_WEAPONS - 1 ; i > 0 ; i-- ) {
#ifdef USE_ADVANCED_WEAPONS
		if ( client->classWeapons[i] ) {
			client->ps.weapon = i;
			break;
		}
#else
		if ( client->ps.stats[STAT_WEAPONS] & ( 1 << i ) ) {
			client->ps.weapon = i;
			break;
		}
#endif
	}

	xr_drop = dropWeapon( ent, xr_item, 0, FL_DROPPED_ITEM | FL_THROWN_ITEM );
	if( amount != 0)
		xr_drop->count= amount;
	else
		xr_drop->count= -1; // XRAY FMJ 0 is already taken, -1 means no ammo
  return xr_drop;
}
#endif

#ifdef USE_LASER_SIGHT
#define LASER_THINK_TIME 50
/*
============
Laser Sight Stuff

	Laser Sight / Flash Light Functions
============
*/

void Laser_Think( gentity_t *self )	{
	vec3_t		end, start, forward, up;
	trace_t		tr;

	//If Player Dies, You Die -> now thanks to Camouflage!
	if (self->parent->client->ps.pm_type == PM_DEAD)  {
		G_FreeEntity(self);
		return;
	}

	//Set Aiming Directions
	AngleVectors(self->parent->client->ps.viewangles, forward, right, up);
	CalcMuzzlePointOrigin(self->parent, muzzle_origin, forward, right, up, start);
	VectorMA (start, 8192, forward, end);

	//Trace Position
	trap_Trace (&tr, start, NULL, NULL, end, self->parent->s.number, MASK_SHOT );

	//Did you not hit anything?
	if (tr.surfaceFlags & SURF_NOIMPACT || tr.surfaceFlags & SURF_SKY)	{
		self->nextthink = level.time + 50;
		trap_UnlinkEntity(self);
		return;
	}

	//Move you forward to keep you visible
	if (tr.fraction != 1)	VectorMA(tr.endpos,-8,forward,tr.endpos);

	//Set Your position
	VectorCopy( tr.endpos, self->r.currentOrigin );
	VectorCopy( tr.endpos, self->s.pos.trBase );

	vectoangles(tr.plane.normal, self->s.angles);

	trap_LinkEntity(self);

	//Prep next move
	self->nextthink = level.time + LASER_THINK_TIME;
}

void Laser_Gen( gentity_t *ent, int type )	{
	gentity_t	*las;
	int oldtype;

	//Get rid of you?
	if ( ent->client->lasersight) {
		  oldtype = ent->client->lasersight->s.eventParm;
		  G_FreeEntity( ent->client->lasersight );
		  ent->client->lasersight = NULL;
		  if (oldtype == type)
			  return;
	}

	las = G_Spawn();

	las->nextthink = level.time + LASER_THINK_TIME;
	las->think = Laser_Think;
	las->r.ownerNum = ent->s.number;
	las->parent = ent;
	las->s.eType = ET_LASER;

	//Lets tell it if flashlight or laser
	if (type == 2)	{
		las->s.eventParm = 2; //tells CG that it is a flashlight
		las->classname = "flashlight";
	}
	else {
		las->s.eventParm = 1; //tells CG that it is a laser sight
		las->classname = "lasersight";
	}

	ent->client->lasersight = las;
}

#endif


/*
===============
LogAccuracyHit
===============
*/
qboolean LogAccuracyHit( gentity_t *target, gentity_t *attacker ) {
	if( !target->takedamage ) {
		return qfalse;
	}

	if ( target == attacker ) {
		return qfalse;
	}

	if( !target->client ) {
		return qfalse;
	}

	if( !attacker->client ) {
		return qfalse;
	}

	if( target->client->ps.stats[STAT_HEALTH] <= 0 ) {
		return qfalse;
	}

	if ( OnSameTeam( target, attacker ) ) {
		return qfalse;
	}

	return qtrue;
}


#ifdef USE_PORTALS
gentity_t *fire_portal (gentity_t *self, vec3_t start, vec3_t dir, qboolean altFire);
#endif
#if defined(USE_WEAPON_SPREAD) || defined(USE_RUNES)
void SpreadFire_Powerup(gentity_t* ent, gentity_t* (*fireFunc)(gentity_t*, vec3_t, vec3_t) );
#endif
#if defined(USE_CLUSTER_GRENADES) || defined(USE_RUNES)
gentity_t *fire_cluster_grenade (gentity_t *self, vec3_t start, vec3_t dir);
#endif
#ifdef USE_FLAME_THROWER
void Weapon_fire_flame (gentity_t *ent );
#endif
#if defined(USE_BOUNCE_RAIL) || defined(USE_INVULN_RAILS) || defined(USE_RUNES)
void fire_special_railgun( gentity_t *ent, qboolean isBounce, qboolean invulnerable );
#endif

#ifdef USE_TELEFRAG_RAIL
void weapon_telefrag_fire (gentity_t *ent,vec3_t muzzle,vec3_t forward,vec3_t right,vec3_t up);
#endif

/*
===============
FireWeapon
===============
*/
#ifdef USE_ALT_FIRE
void FireWeapon( gentity_t *ent, qboolean altFire ) 
#else
void FireWeapon( gentity_t *ent ) 
#endif
{
#ifdef USE_RUNES
  if ( ent->client->inventory[RUNE_STRENGTH] ) {
		s_quadFactor = g_quadfactor.value;
  } else
#endif
#ifdef USE_ADVANCED_ITEMS
	if ( ent->client->inventory[PW_QUAD] || ent->client->inventory[PW_SUPERMAN])
#else
	if ( ent->client->ps.powerups[PW_QUAD] ) 
#endif
	{
		s_quadFactor = g_quadfactor.value;
	} else {
		s_quadFactor = 1.0;
	}
#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS)
	if( ent->client->persistantPowerup && ent->client->persistantPowerup->item && ent->client->persistantPowerup->item->giTag == PW_DOUBLER ) {
		s_quadFactor *= 2;
	}
#endif

	// track shots taken for accuracy tracking.  Grapple is not a weapon and gauntet is just not tracked
#ifdef USE_GRAPPLE
	if( ent->s.weapon != WP_GRAPPLING_HOOK )
#endif
	if( ent->s.weapon != WP_GAUNTLET ) {
#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS)
		if( ent->s.weapon == WP_NAILGUN ) {
			ent->client->accuracy_shots += NUM_NAILSHOTS;
		} else {
			ent->client->accuracy_shots++;
		}
#else
		ent->client->accuracy_shots++;
#endif
	}

	// set aiming directions
#ifdef USE_BIRDS_EYE
	if(ent->client->ps.pm_type == PM_BIRDSEYE || ent->client->ps.pm_type == PM_FOLLOWCURSOR) {
		ent->client->ps.viewangles[PITCH] = 0;
	}
#endif

	AngleVectors( ent->client->ps.viewangles, forward, right, up );

	CalcMuzzlePointOrigin( ent, muzzle_origin, forward, right, up, muzzle );

	// fire the specific weapon
	switch( ent->s.weapon ) {
	case WP_GAUNTLET:
		Weapon_Gauntlet( ent );
		break;
	case WP_LIGHTNING:
		Weapon_LightningFire( ent );
		break;
	case WP_SHOTGUN:
		weapon_supershotgun_fire( ent );
		break;
	case WP_MACHINEGUN:
#ifdef USE_WEAPON_VARS
    if ( g_gametype.integer != GT_TEAM ) {
      Bullet_Fire( ent, MACHINEGUN_SPREAD, wp_machineDamage.integer );
    } else {
      Bullet_Fire( ent, MACHINEGUN_SPREAD, wp_machineDamageTeam.integer );
    }
#else
		if ( g_gametype.integer != GT_TEAM ) {
			Bullet_Fire( ent, MACHINEGUN_SPREAD, MACHINEGUN_DAMAGE );
		} else {
			Bullet_Fire( ent, MACHINEGUN_SPREAD, MACHINEGUN_TEAM_DAMAGE );
		}
#endif
		break;
	case WP_GRENADE_LAUNCHER:
#if defined(USE_WEAPON_SPREAD) || defined(USE_RUNES)
  //Hal9000 spreadfire
#ifdef USE_ADVANCED_ITEMS
  if ( ent->client->inventory[PW_SPREAD] ) 
#else
  if ( ent->client->ps.powerups[PW_SPREAD] ) 
#endif
	{
#if defined(USE_CLUSTER_GRENADES) || defined(USE_RUNES)
		if(wp_grenadeCluster.integer) {
			SpreadFire_Powerup(ent, fire_cluster_grenade);
		} else
#endif
		SpreadFire_Powerup(ent, fire_grenade);
	} else
#endif
		weapon_grenadelauncher_fire( ent );
		break;
	case WP_ROCKET_LAUNCHER:
#if defined(USE_ADVANCED_WEAPONS) || defined(USE_ADVANCED_ITEMS) || defined(USE_ADVANCED_CLASS) || defined(USE_HOMING_MISSILE)
	case WP_HOMING_ROCKET:
#ifdef USE_ADVANCED_CLASS
		if(ent->client->pers.playerclass == PCLASS_VORE) {
			Weapon_RocketLauncher_Fire( ent, qtrue ); // always fires homing rockets, so f-ing annoying
		} else
#endif
		Weapon_RocketLauncher_Fire( ent, ent->s.weapon == WP_HOMING_ROCKET );
#else
		Weapon_RocketLauncher_Fire( ent );
#endif
		break;
	case WP_PLASMAGUN:
		Weapon_Plasmagun_Fire( ent );
		break;
	case WP_RAILGUN:
#ifdef USE_RUNES
		if(ent->client->inventory[RUNE_PIERCING]) {
#ifdef USE_BOUNCE_RAIL
			fire_special_railgun(ent, wp_railBounce.integer, qtrue);
#else
			fire_special_railgun(ent, qfalse, qtrue);
#endif
		} else
#endif
#ifdef USE_INVULN_RAILS
    if(wp_railThruWalls.integer)
			fire_special_railgun( ent, qfalse, qtrue );
		else
#endif
#ifdef USE_BOUNCE_RAIL
		if(wp_railBounce.integer) {
			fire_special_railgun( ent, qtrue, qfalse );
		} else
#endif
#ifdef USE_TELEFRAG_RAIL
		if(wp_railTelefrag.integer) {
			weapon_telefrag_fire( ent,muzzle,forward,right,up );
		} else
#endif
		weapon_railgun_fire( ent );
		break;
	case WP_BFG:
#ifdef USE_PORTALS
    if(wp_portalEnable.integer
#ifdef USE_ALT_FIRE
      && !g_altPortal.integer // do both ends with right click, reset each time
#endif
    ) {
#ifdef USE_ALT_FIRE
			fire_portal( ent, muzzle, forward, altFire );
#else
			fire_portal( ent, muzzle, forward, ent->client->portalSource != NULL );
#endif
    } else
#endif
		BFG_Fire( ent );
		break;
#ifdef USE_GRAPPLE
	case WP_GRAPPLING_HOOK:
		Weapon_GrapplingHook_Fire( ent );
		break;
#endif
#ifdef USE_FLAME_THROWER
  case WP_FLAME_THROWER :
    Weapon_fire_flame( ent );
    break;
#endif
#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS) || defined(USE_ADVANCED_CLASS)
	case WP_NAILGUN:
		Weapon_Nailgun_Fire( ent );
		break;
	case WP_PROX_LAUNCHER:
		weapon_proxlauncher_fire( ent );
		break;
	case WP_CHAINGUN:
#ifdef USE_WEAPON_VARS
		Bullet_Fire( ent, CHAINGUN_SPREAD, wp_chainDamage.integer );
#else
    Bullet_Fire( ent, CHAINGUN_SPREAD, MACHINEGUN_DAMAGE );
#endif
		break;
#endif
	default:
// FIXME		G_Error( "Bad ent->s.weapon" );
		break;
	}
}


#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS) || defined(USE_SINGLEPLAYER)

/*
===============
KamikazeRadiusDamage
===============
*/
static void KamikazeRadiusDamage( vec3_t origin, gentity_t *attacker, float damage, float radius ) {
	float		dist;
	gentity_t	*ent;
	int			entityList[MAX_GENTITIES];
	int			numListedEntities;
	vec3_t		mins, maxs;
	vec3_t		v;
	vec3_t		dir;
	int			i, e;

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

		if (!ent->takedamage) {
			continue;
		}

		// dont hit things we have already hit
		if( ent->kamikazeTime > level.time ) {
			continue;
		}

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

//		if( CanDamage (ent, origin) ) {
			VectorSubtract (ent->r.currentOrigin, origin, dir);
			// push the center of mass higher than the origin so players
			// get knocked into the air more
			dir[2] += 24;
			G_Damage( ent, NULL, attacker, dir, origin, damage, DAMAGE_RADIUS|DAMAGE_NO_TEAM_PROTECTION, MOD_KAMIKAZE );
			ent->kamikazeTime = level.time + 3000;
//		}
	}
}

/*
===============
KamikazeShockWave
===============
*/
static void KamikazeShockWave( vec3_t origin, gentity_t *attacker, float damage, float push, float radius ) {
	float		dist;
	gentity_t	*ent;
	int			entityList[MAX_GENTITIES];
	int			numListedEntities;
	vec3_t		mins, maxs;
	vec3_t		v;
	vec3_t		dir;
	int			i, e;

	if ( radius < 1 )
		radius = 1;

	for ( i = 0 ; i < 3 ; i++ ) {
		mins[i] = origin[i] - radius;
		maxs[i] = origin[i] + radius;
	}

	numListedEntities = trap_EntitiesInBox( mins, maxs, entityList, MAX_GENTITIES );

	for ( e = 0 ; e < numListedEntities ; e++ ) {
		ent = &g_entities[entityList[ e ]];

		// dont hit things we have already hit
		if( ent->kamikazeShockTime > level.time ) {
			continue;
		}

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

//		if( CanDamage (ent, origin) ) {
			VectorSubtract (ent->r.currentOrigin, origin, dir);
			dir[2] += 24;
			G_Damage( ent, NULL, attacker, dir, origin, damage, DAMAGE_RADIUS|DAMAGE_NO_TEAM_PROTECTION, MOD_KAMIKAZE );
			//
			dir[2] = 0;
			VectorNormalize(dir);
			if ( ent->client ) {
				ent->client->ps.velocity[0] = dir[0] * push;
				ent->client->ps.velocity[1] = dir[1] * push;
				ent->client->ps.velocity[2] = 100;
			}
			ent->kamikazeShockTime = level.time + 3000;
//		}
	}
}

/*
===============
KamikazeDamage
===============
*/
static void KamikazeDamage( gentity_t *self ) {
	int i;
	float t;
	gentity_t *ent;
	vec3_t newangles;

	self->count += 100;

	if (self->count >= KAMI_SHOCKWAVE_STARTTIME) {
		// shockwave push back
		t = self->count - KAMI_SHOCKWAVE_STARTTIME;
		KamikazeShockWave(self->s.pos.trBase, self->activator, 25, 400,	(int) (float) t * KAMI_SHOCKWAVE_MAXRADIUS / (KAMI_SHOCKWAVE_ENDTIME - KAMI_SHOCKWAVE_STARTTIME) );
	}
	//
	if (self->count >= KAMI_EXPLODE_STARTTIME) {
		// do our damage
		t = self->count - KAMI_EXPLODE_STARTTIME;
		KamikazeRadiusDamage( self->s.pos.trBase, self->activator, 400,	(int) (float) t * KAMI_BOOMSPHERE_MAXRADIUS / (KAMI_IMPLODE_STARTTIME - KAMI_EXPLODE_STARTTIME) );
	}

	// either cycle or kill self
	if( self->count >= KAMI_SHOCKWAVE_ENDTIME ) {
		G_FreeEntity( self );
		return;
	}
	self->nextthink = level.time + 100;

	// add earth quake effect
	newangles[0] = crandom() * 2;
	newangles[1] = crandom() * 2;
	newangles[2] = 0;
	for (i = 0; i < MAX_CLIENTS; i++)
	{
		ent = &g_entities[i];
		if (!ent->inuse)
			continue;
		if (!ent->client)
			continue;

		if (ent->client->ps.groundEntityNum != ENTITYNUM_NONE) {
			ent->client->ps.velocity[0] += crandom() * 120;
			ent->client->ps.velocity[1] += crandom() * 120;
			ent->client->ps.velocity[2] = 30 + random() * 25;
		}

		ent->client->ps.delta_angles[0] += ANGLE2SHORT(newangles[0] - self->movedir[0]);
		ent->client->ps.delta_angles[1] += ANGLE2SHORT(newangles[1] - self->movedir[1]);
		ent->client->ps.delta_angles[2] += ANGLE2SHORT(newangles[2] - self->movedir[2]);
	}
	VectorCopy(newangles, self->movedir);
}

/*
===============
G_StartKamikaze
===============
*/
void G_StartKamikaze( gentity_t *ent ) {
	gentity_t	*explosion;
	gentity_t	*te;
	vec3_t		snapped;

	// start up the explosion logic
	explosion = G_Spawn();

	explosion->s.eType = ET_EVENTS + EV_KAMIKAZE;
	explosion->eventTime = level.time;

	if ( ent->client ) {
		VectorCopy( ent->s.pos.trBase, snapped );
	}
	else {
		VectorCopy( ent->activator->s.pos.trBase, snapped );
	}
	SnapVector( snapped );		// save network bandwidth
	G_SetOrigin( explosion, snapped );

	explosion->classname = "kamikaze";
	explosion->s.pos.trType = TR_STATIONARY;

	explosion->kamikazeTime = level.time;

	explosion->think = KamikazeDamage;
	explosion->nextthink = level.time + 100;
	explosion->count = 0;
	VectorClear(explosion->movedir);

	trap_LinkEntity( explosion );

	if (ent->client) {
		//
		explosion->activator = ent;
		//
		ent->s.eFlags &= ~EF_KAMIKAZE;
		// nuke the guy that used it
		G_Damage( ent, ent, ent, NULL, NULL, 100000, DAMAGE_NO_PROTECTION, MOD_KAMIKAZE );
	}
	else {
		if ( !strcmp(ent->activator->classname, "bodyque") ) {
			explosion->activator = &g_entities[ent->activator->r.ownerNum];
		}
		else {
			explosion->activator = ent->activator;
		}
	}

	// play global sound at all clients
	te = G_TempEntity(snapped, EV_GLOBAL_TEAM_SOUND );
	te->r.svFlags |= SVF_BROADCAST;
	te->s.eventParm = GTS_KAMIKAZE;
}
#endif
