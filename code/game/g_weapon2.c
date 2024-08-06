
#include "g_local.h"

void CalcMuzzlePointOrigin( const gentity_t *ent, vec3_t origin, const vec3_t forward, const vec3_t right, const vec3_t up, vec3_t muzzlePoint );
void G_ExplodeMissile( gentity_t *ent );
void G_BounceProjectile( vec3_t start, vec3_t impact, vec3_t dir, vec3_t endout );

#define	MISSILE_PRESTEP_TIME	50

static	float	s_quadFactor;
static	vec3_t	forward, right, up;
static	vec3_t	muzzle;
static	vec3_t	muzzle_origin; // for hitscan weapon trace

#ifdef USE_WEAPON_SPREAD

/*
===============
SpreadFire_Powerup

HypoThermia: fan bolts at any view pitch
===============
*/
void SpreadFire_Powerup(gentity_t* ent, gentity_t* (*fireFunc)(gentity_t*, vec3_t, vec3_t) )
{
	gentity_t	*m;
	gclient_t	*client;
	vec3_t		newforward;
	vec3_t		angles;
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

	// set aiming directions
	AngleVectors( ent->client->ps.viewangles, forward, right, up );

	CalcMuzzlePointOrigin( ent, muzzle_origin, forward, right, up, muzzle );

	client = ent->client; 

	//First shot, slightly to the right
	AngleVectors( client->ps.viewangles, forward, right, 0);
	VectorMA(forward, 0.1, right, newforward);
	VectorNormalize(newforward);
	vectoangles(newforward, angles);

	AngleVectors( angles, forward, right, up );
	CalcMuzzlePointOrigin( ent, muzzle_origin, forward, right, up, muzzle );

	m = fireFunc (ent, muzzle, forward);
	m->damage *= s_quadFactor;
	m->splashDamage *= s_quadFactor;

	//Second shot, slightly to the left
	AngleVectors( client->ps.viewangles, forward, right, 0);
	VectorMA(forward, -0.1, right, newforward);
	VectorNormalize(newforward);
	vectoangles(newforward, angles);

	AngleVectors( angles, forward, right, up );
	CalcMuzzlePointOrigin( ent, muzzle_origin, forward, right, up, muzzle );

	m = fireFunc(ent, muzzle, forward);
	m->damage *= s_quadFactor;
	m->splashDamage *= s_quadFactor;
}
#endif


#ifdef USE_VORTEX_GRENADES
/*
================
findradius
================
*/
gentity_t *findradius (gentity_t *ent, vec3_t org, float rad) {

	vec3_t eorg;
	int j;

	if (!ent)
		ent = g_entities;
	else
		ent++;

	for (; ent < &g_entities[level.num_entities]; ent++)
		{
		if (!ent->inuse)
			continue;

		for (j=0; j<3; j++)
			eorg[j] = org[j] - (ent->r.currentOrigin[j] + 
			(ent->r.mins[j] + ent->r.maxs[j])*0.5);
		if (VectorLength(eorg) > rad)
			continue;
		return ent;
	}
	return NULL;
}


#define GSUCK_TIMING	  50			  // the think time interval of G_Suck
#define GSUCK_VELOCITY	2000			// the amount of kick each second gets
#define GSUCK_RADIUS    500
#define GSUCK_TRIGGER	  32

/*
=================
G_Suck
=================
*/
static void G_Suck( gentity_t *self ) {
	gentity_t *target;
	vec3_t start,dir,end,kvel,mins,maxs;
  int targNum[MAX_GENTITIES],num;

	target = NULL;

  //check if there are any entity's within a radius of 500 units.
  mins[0] = -GSUCK_RADIUS * 1.42;
  mins[1] = -GSUCK_RADIUS * 1.42;
  mins[2] = -GSUCK_RADIUS * 1.42;
  maxs[0] = GSUCK_RADIUS * 1.42;
  maxs[1] = GSUCK_RADIUS * 1.42;
  maxs[2] = GSUCK_RADIUS * 1.42;

  VectorAdd( self->r.currentOrigin, mins, mins );
  VectorAdd( self->r.currentOrigin, maxs, maxs );

  num = trap_EntitiesInBox(mins,maxs,targNum,MAX_GENTITIES);
  for(num--; num > 0; num--) {    // count from num-1 down to 0
  	target = &g_entities[targNum[num]];

    // target must not be vortex grenade
  	if (target == self) 
  		continue;

    // target must be a client
  	if (!target->client) 
  		continue;

    // target must not be the player who fired the vortex grenade 
  	//if (target == self->parent) 
  	//	continue;

    // target must be able to take damage
  	if (!target->takedamage) 
  		continue;
      
    // target must actually be in GSUCK_RADIUS
    if ( Distance(self->r.currentOrigin, target->r.currentOrigin) > GSUCK_RADIUS )
    	continue;

    // put target position in start
  	VectorCopy(target->r.currentOrigin, start); 
    // put grenade position in end
  	VectorCopy(self->r.currentOrigin, end); 
    // subtract start from end to get directional vector
  	VectorSubtract(end, start, dir); 
  	VectorNormalize(dir); 
    // scale directional vector by 200 and add to the targets velocity
  	VectorScale(dir, GSUCK_VELOCITY / GSUCK_TIMING, kvel);
    // make targets move direction = to directional vector.
  	//VectorCopy(dir, target->movedir); 
    // add the kick velocity to the player's velocity
    VectorAdd (target->client->ps.velocity,kvel, target->client->ps.velocity);

    // set the timer so that the other client can't cancel
    // out the movement immediately
    if ( !target->client->ps.pm_time ) {
    	target->client->ps.pm_time = GSUCK_TIMING - 1;

    	/* the next G_Suck that works here will
    	probably be the one that worked before */

    	target->client->ps.pm_flags |= PMF_TIME_KNOCKBACK;
    }
       
	}

	self->nextthink = level.time + GSUCK_TIMING; 

  // check if vortext grenade is older than 20 seconds.
	if (level.time > self->wait) 
		G_ExplodeMissile( self);

  mins[0] = -GSUCK_TRIGGER * 1.42;
  mins[1] = -GSUCK_TRIGGER * 1.42;
  mins[2] = -GSUCK_TRIGGER * 1.42;
  maxs[0] = GSUCK_TRIGGER * 1.42;
  maxs[1] = GSUCK_TRIGGER * 1.42;
  maxs[2] = GSUCK_TRIGGER * 1.42;

  VectorAdd( self->r.currentOrigin, mins, mins );
  VectorAdd( self->r.currentOrigin, maxs, maxs );

  num = trap_EntitiesInBox(mins,maxs,targNum,MAX_GENTITIES);
  for(num--; num > 0; num--) {    // count from num-1 down to 0
  	target = &g_entities[targNum[num]];

  	// target must be a client
  	if (!target->client) 
  		continue;

  	// target must not be the player who fired the vortex grenade 
  	if (target == self->parent)		// makes sense here
  		continue;

  	// target must be able to take damage
  	if (!target->takedamage)
  		continue;

  	G_ExplodeMissile( self);			// EXPLODE goes the weasel!
  }
}
#endif


/*
=================
fire_grenade
=================
*/

#define GRENADE_DAMAGE	100		// bolt->damage for grenade
#define GRENADE_RADIUS	150		// bolt->splashRadius for grenade
/*
=================
CCH: fire_grenade_real

38: 62. They will also say, `Our Lord, whosoever prepared this for us,
do thou multiply manifold his punishment in the Fire.'
--Holy Quran, translated by Maulvi Sher Ali  
=================
*/
gentity_t *fire_special_grenade (gentity_t *self, vec3_t start, vec3_t dir, qboolean isCluster, qboolean isVortex) 
{
	gentity_t	*bolt;

	VectorNormalize (dir);

	bolt = G_Spawn();
#if defined(USE_CLUSTER_GRENADES) || defined(USE_RUNES)
	if(isCluster) {
	  bolt->classname = "cgrenade";
	} else
#endif
	bolt->classname = "grenade";
#ifdef USE_VORTEX_GRENADES
  if(isVortex) {
    bolt->nextthink = level.time + 1000; // call G_Suck in 1 second
    bolt->think = G_Suck;
    bolt->wait = level.time + 20000; // vortext grenade lifetime.
  } else
#endif
  {
  	bolt->nextthink = level.time + 2500;
  	bolt->think = G_ExplodeMissile;
  }
	bolt->s.eType = ET_MISSILE;
	bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	bolt->s.weapon = WP_GRENADE_LAUNCHER;
	bolt->s.eFlags = EF_BOUNCE_HALF;
	bolt->r.ownerNum = self->s.number;
	bolt->parent = self;
	bolt->damage = 100;
	bolt->splashDamage = 100;
	bolt->splashRadius = 150;
	bolt->methodOfDeath = MOD_GRENADE;
	bolt->splashMethodOfDeath = MOD_GRENADE_SPLASH;
	bolt->clipmask = MASK_SHOT;
	bolt->target_ent = NULL;

	if ( self->s.powerups & (1 << PW_QUAD) )
		bolt->s.powerups |= (1 << PW_QUAD);

	// missile owner
	bolt->s.clientNum = self->s.clientNum;
	// unlagged
	bolt->s.otherEntityNum = self->s.number;

	bolt->s.pos.trType = TR_GRAVITY;
	bolt->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;		// move a bit on the very first frame
	VectorCopy( start, bolt->s.pos.trBase );
#if defined(USE_CLUSTER_GRENADES) || defined(USE_RUNES)
	if(isCluster) {
		VectorScale( dir, 400, bolt->s.pos.trDelta );
	} else
#endif
	VectorScale( dir, 700, bolt->s.pos.trDelta );
	SnapVector( bolt->s.pos.trDelta );			// save net bandwidth

	VectorCopy (start, bolt->r.currentOrigin);

	return bolt;
}

#if defined(USE_CLUSTER_GRENADES) || defined(USE_RUNES)
gentity_t *fire_cluster_grenade (gentity_t *self, vec3_t start, vec3_t dir) {
	return fire_special_grenade(self, start, dir, qtrue, wp_grenadeVortex.integer);
}
#endif

#ifdef USE_BOUNCE_RAIL
#define MAX_RAIL_BOUNCE 4 //Luc: Defines the maximum number of bounces
#endif

/*
=================
weapon_railgun_fire
=================
*/
#define	MAX_RAIL_HITS	4
void fire_special_railgun( gentity_t *ent, qboolean isBounce, qboolean invulnerable ) {
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
#ifdef USE_BOUNCE_RAIL
  int bounce; //Luc: Bounce count
#endif
	gentity_t	*unlinkedEntities[MAX_RAIL_HITS];
#ifdef USE_INVULN_RAILS
  vec3_t		tracefrom;	// SUM
  vec3_t		lastend;	// SUM
#endif
#ifdef USE_RUNES
  if ( ent->client->inventory[RUNE_STRENGTH] ) {
		s_quadFactor = g_quadfactor.value;
  } else
	// berserk only on melee attack
  //if ( ent->client->inventory[RUNE_BERSERK] ) {
	//	s_quadFactor = g_quadfactor.value * 3;
  //} else
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

	// set aiming directions
	AngleVectors( ent->client->ps.viewangles, forward, right, up );

	CalcMuzzlePointOrigin( ent, muzzle_origin, forward, right, up, muzzle );

	damage = 100 * s_quadFactor;

	VectorMA( muzzle_origin, 8192.0, forward, end );
#ifdef USE_INVULN_RAILS
  VectorCopy (muzzle_origin, tracefrom);
#endif

	// unlagged
	G_DoTimeShiftFor( ent );

	// trace only against the solids, so the railgun will go through people
	unlinked = 0;
	hits = 0;
	passent = ent->s.number;
  i = 0;

#ifdef USE_BOUNCE_RAIL
  bounce = 0; //Luc: start off with no bounces
  //Luc:
  do {
    if (bounce) {
			// This sets the new angles for the bounce
      G_BounceProjectile( muzzle , trace.endpos , trace.plane.normal, end);
			// copy the end position as the new muzzle
      VectorCopy (trace.endpos , muzzle);
    }
#endif
	do {
#ifdef USE_INVULN_RAILS
    if(invulnerable)
      trap_Trace (&trace, tracefrom, NULL, NULL, end, passent, MASK_SHOT );
    else
#endif
		trap_Trace( &trace, muzzle_origin, NULL, NULL, end, passent, MASK_SHOT );
#ifdef USE_INVULN_RAILS
    // double check we aren't hitting ourselves on the first pass
    if(IsSelf(trace, ent)) {
      // do another trace that skips ourselves
      trap_Trace( &trace, muzzle_origin, NULL, NULL, end, ent->s.number, MASK_SHOT );
    }
    i++;
#endif

		if ( trace.entityNum >= ENTITYNUM_MAX_NORMAL ) {
#ifdef USE_INVULN_RAILS
      if(invulnerable) {
        // SUM break if we hit the sky
  			if (trace.surfaceFlags & SURF_SKY)
  				break;

  			// Hypo: break if we traversed length of vector tracefrom
  			if (trace.fraction == 1.0)
  				break;

        // save last solid for explosion mark
        if ( trace.contents & CONTENTS_SOLID ) {
          VectorCopy (trace.endpos, lastend);
        }
        
  			// otherwise continue tracing thru walls
  			VectorMA (trace.endpos,1,forward,tracefrom);
      } else
#endif
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
#ifdef USE_INVULN_RAILS
    if(!invulnerable)
#endif
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
#ifdef USE_INVULN_RAILS
  if(invulnerable)
    VectorCopy (lastend, trace.endpos);
#endif

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
#ifdef USE_BOUNCE_RAIL
   bounce = MAX_RAIL_BOUNCE; //Luc: If hit sky, max out bounces so wont bounce again
#endif
		tent->s.eventParm = 255;	// don't make the explosion at the end
	} else {
		tent->s.eventParm = DirToByte( trace.plane.normal );
	}
	tent->s.clientNum = ent->s.clientNum;

#ifdef USE_INVULN_RAILS
  //send the effect to everyone since it tunnels through walls
	if(invulnerable) {
		tent->r.svFlags |= SVF_BROADCAST;
	}
#endif

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

#ifdef USE_BOUNCE_RAIL//Luc: Add a bounce, so it'll bounce only 4 times
	tent->s.powerups = bounce;
	bounce++;
} while (isBounce && bounce <= MAX_RAIL_BOUNCE);
#endif
}


#ifdef USE_VULN_RPG
/*
================
G_MissileDie

Lancer - Destroy a missile
================
*/
void G_MissileDie( gentity_t *self, gentity_t *inflictor,
  gentity_t *attacker, int damage, int mod ) {
  if (inflictor == self)
    return;
  self->takedamage = qfalse;
  self->think = G_ExplodeMissile;
  self->nextthink = level.time + 10;
}
#endif


#ifdef USE_HOMING_MISSILE



/*
================
CCH: rocket_think

Fly like an eagle...
--"Fly Like an Eagle", Steve Miller Band
================
*/
#define ROCKET_SPEED	   600
#define ROCKET_VIS_CONE  0.90
//#define ROCKET_TURNING   0.08
#define ROCKET_TURNING   0.04
// 

gentity_t *RedirectTarget(gentity_t *ent, gentity_t *tent, vec4_t forward, vec3_t targetdir) {
	vec3_t		tentdir, midbody;
	float		/* targetlength,*/ tentlength;
	trace_t		tr;

	// Aim for the body, not the feet
	midbody[0] = tent->r.currentOrigin[0] + 
		(tent->r.mins[0] + tent->r.maxs[0]) * 0.5;
	midbody[1] = tent->r.currentOrigin[1] + 
		(tent->r.mins[1] + tent->r.maxs[1]) * 0.5;
	midbody[2] = tent->r.currentOrigin[2] + 
		(tent->r.mins[2] + tent->r.maxs[2]) * 0.5;

	VectorSubtract(midbody, ent->r.currentOrigin, tentdir);
	tentlength = VectorLength(tentdir);
	if ( tentlength > LIGHTNING_RANGE ) return NULL;

	// Quick normalization of tentdir since 
	// we already have the length
	tentdir[0] /= tentlength;
	tentdir[1] /= tentlength;
	tentdir[2] /= tentlength;

	// this value determines how wide from it's direction it can search for 
	//   players to target
	if ( DotProduct(forward, tentdir) < ROCKET_VIS_CONE ) return NULL;

	trap_Trace( &tr, ent->r.currentOrigin, NULL, NULL, 
		tent->r.currentOrigin, ENTITYNUM_NONE, MASK_SHOT );

	if ( tent != &g_entities[tr.entityNum] ) return NULL;

	//targetlength = tentlength;
	VectorCopy(tentdir, targetdir);
	return tent;
}

gentity_t *RedirectEntity(gentity_t *ent, gentity_t *tent, vec4_t forward, vec3_t targetdir) {
	vec3_t		tentdir; //, midbody;
	float		/* targetlength,*/ tentlength;
	//trace_t		tr;

	// Aim for the body, not the feet
	// midbody[0] = tent->r.currentOrigin[0] + 
	// 	(tent->r.mins[0] + tent->r.maxs[0]) * 0.5;
	// midbody[1] = tent->r.currentOrigin[1] + 
	// 	(tent->r.mins[1] + tent->r.maxs[1]) * 0.5;
	// midbody[2] = tent->r.currentOrigin[2] + 
	// 	(tent->r.mins[2] + tent->r.maxs[2]) * 0.5;

	VectorSubtract(tent->r.currentOrigin, ent->r.currentOrigin, tentdir);
	tentlength = VectorLength(tentdir);
	if ( tentlength > LIGHTNING_RANGE ) return qfalse;

	// Quick normalization of tentdir since 
	// we already have the length
	tentdir[0] /= tentlength;
	tentdir[1] /= tentlength;
	tentdir[2] /= tentlength;

	// this value determines how wide from it's direction it can search for 
	//   players to target
	 if ( DotProduct(forward, tentdir) < ROCKET_VIS_CONE ) return qfalse;

	// trap_Trace( &tr, ent->r.currentOrigin, NULL, NULL, 
	// 	tent->r.currentOrigin, ENTITYNUM_NONE, MASK_SHOT );

	// if ( tent != &g_entities[tr.entityNum] ) return qfalse;

	//targetlength = tentlength;
	VectorCopy(tentdir, targetdir);
	return tent;
}


void rocket_think( gentity_t *ent ) {
	gentity_t	*target, *tent;
	int		i;
	vec3_t		targetdir, forward;

	target = NULL;
	// Best way to get forward vector for this rocket?
	VectorCopy(ent->s.pos.trDelta, forward);
	VectorNormalize(forward);
	for (i = 0; i < level.maxclients; i++) {
		// Here we use tent to point to potential targets
		tent = &g_entities[i];

		if (!tent->inuse) continue;
		if (tent == ent->parent) continue;
		if ( OnSameTeam( tent, ent->parent ) ) continue;
		if (tent->health <= 0) continue;

		target = RedirectTarget(ent, tent, forward, targetdir);
		if(!target) {
			continue;
		} else {
			//break; ?
		}
	}

	ent->nextthink += 20;

	if (!target) {
		for (i = 0; i < level.numSpawnSpots; i++) {
			// Here we use tent to point to potential targets
			tent = level.spawnSpots[i];

			//if ( OnSameTeam( tent, ent->parent ) ) continue;
			target = RedirectEntity(ent, tent, forward, targetdir);
			if(!target) {
				continue;
			}
		}
		if (!target) {
		//G_Printf("no target!\n");
			return;
		}
	}

  // this variable determines how quickly it can change direction
	VectorMA(forward, ROCKET_TURNING, targetdir, targetdir);
	VectorNormalize(targetdir);
	VectorScale(targetdir, ROCKET_SPEED, ent->s.pos.trDelta);
}
#endif



/*
=================
fire_rocket
=================
*/
gentity_t *fire_special_rocket (gentity_t *self, vec3_t start, vec3_t dir, 
	qboolean bounce, qboolean homing, qboolean vulnerable, qboolean accelerate) {
	gentity_t	*bolt;

	VectorNormalize (dir);

	bolt = G_Spawn();
	bolt->classname = "rocket";
#ifdef USE_ADVANCED_CLASS
	if(self->client->pers.playerclass == PCLASS_VORE) {
		bolt->s.modelindex = G_ModelIndex("models/runes/icetrap.md3");
	}
#endif
#ifdef USE_BOUNCE_RPG
  if (self->flags & FL_ROCKETBOUNCE || wp_rocketBounce.integer || bounce) {
  	bolt->s.eFlags = EF_BOUNCE;
		// shorter explosion time because of the extra bouncing chaos
    bolt->nextthink = level.time + 2500;
	} else
#endif
#ifdef USE_HOMING_MISSILE
  if(wp_rocketHoming.integer || homing) {
    bolt->nextthink = level.time + 20;	// CCH
    bolt->think = rocket_think;		// CCH
  } else
#endif
  bolt->think = G_ExplodeMissile;
	bolt->s.eType = ET_MISSILE;
	bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	bolt->s.weapon = WP_ROCKET_LAUNCHER;
#ifdef USE_VULN_RPG
  // Lancer
  if(wp_rocketVuln.integer || vulnerable) {
    bolt->health = 5;
    bolt->takedamage = qtrue;
    bolt->die = G_MissileDie;
    bolt->r.contents = CONTENTS_BODY;
    VectorSet(bolt->r.mins, -10, -3, 0);
    VectorCopy(bolt->r.mins, bolt->r.absmin);
    VectorSet(bolt->r.maxs, 10, 3, 6);
    VectorCopy(bolt->r.maxs, bolt->r.absmax);
  }
#endif
	bolt->r.ownerNum = self->s.number;
	bolt->parent = self;
	bolt->damage = 100;
	bolt->splashDamage = 100;
	bolt->splashRadius = 120;
	bolt->methodOfDeath = MOD_ROCKET;
	bolt->splashMethodOfDeath = MOD_ROCKET_SPLASH;
	bolt->clipmask = MASK_SHOT;
	bolt->target_ent = NULL;

	if ( self->s.powerups & (1 << PW_QUAD) )
		bolt->s.powerups |= (1 << PW_QUAD);

	// missile owner
	bolt->s.clientNum = self->s.clientNum;
	// unlagged
	bolt->s.otherEntityNum = self->s.number;

#ifdef USE_ACCEL_RPG
  if(wp_rocketAccel.integer || accelerate) {
    bolt->s.pos.trType = TR_ACCEL;
  	bolt->s.pos.trDuration = 500;
  } else
#endif
	bolt->s.pos.trType = TR_LINEAR;
	bolt->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;		// move a bit on the very first frame
	VectorCopy( start, bolt->s.pos.trBase );
	SnapVector( bolt->s.pos.trBase );			// save net bandwidth
#ifdef USE_HOMING_MISSILE
  if(wp_rocketHoming.integer || homing)
    VectorScale( dir, ROCKET_SPEED, bolt->s.pos.trDelta );	// CCH
  else
#endif
#ifdef USE_ACCEL_RPG
  if(wp_rocketAccel.integer || accelerate)
    VectorScale( dir, 50, bolt->s.pos.trDelta );
  else
#endif
#ifdef USE_WEAPON_VARS
	VectorScale( dir, wp_rocketSpeed.integer, bolt->s.pos.trDelta );
#else
	VectorScale( dir, 900, bolt->s.pos.trDelta );
#endif
	SnapVector( bolt->s.pos.trDelta );			// save net bandwidth
	VectorCopy (start, bolt->r.currentOrigin);

	return bolt;
}


#ifdef USE_FLAME_THROWER
/*
=================
fire_flame
=================
*/
gentity_t *fire_flame (gentity_t *self, vec3_t start, vec3_t dir) {
  gentity_t*bolt;

  VectorNormalize (dir);

  bolt = G_Spawn();
  bolt->classname = "flame";
  bolt->nextthink = level.time + 1500;
  bolt->think = G_ExplodeMissile;
  bolt->s.eType = ET_MISSILE;
  bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
  bolt->s.weapon = WP_FLAME_THROWER;
  bolt->r.ownerNum = self->s.number;
  bolt->parent = self;
#ifdef USE_WEAPON_VARS
  bolt->damage = wp_flameDamage.integer;
  bolt->splashDamage = wp_flameSplash.integer;
  bolt->splashRadius = wp_flameRadius.integer;
#else
  bolt->damage = 30;
  bolt->splashDamage = 25;
  bolt->splashRadius = 45;
#endif
  bolt->methodOfDeath = MOD_FLAME_THROWER;
  bolt->splashMethodOfDeath = MOD_PLASMA_SPLASH;
  bolt->clipmask = MASK_SHOT;

  bolt->s.pos.trType = TR_LINEAR;
  bolt->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;// move a bit on the very first frame
  VectorCopy( start, bolt->s.pos.trBase );
  VectorScale( dir, 300, bolt->s.pos.trDelta );
  SnapVector( bolt->s.pos.trDelta );// save net bandwidth

  VectorCopy (start, bolt->r.currentOrigin);

  return bolt;
}


/*
=======================================================================
FLAME_THROWER
=======================================================================
*/
void Weapon_fire_flame (gentity_t *ent ) {
	gentity_t *m;
	// because this is set in another file, i have to copy here
	AngleVectors( ent->client->ps.viewangles, forward, right, up );

	CalcMuzzlePointOrigin( ent, muzzle_origin, forward, right, up, muzzle );

	m = fire_flame(ent, muzzle, forward);
	m->damage *= s_quadFactor;
	m->splashDamage *= s_quadFactor;
}
#endif
