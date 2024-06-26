
#include "g_local.h"

void G_ExplodeMissile( gentity_t *ent );
#define	MISSILE_PRESTEP_TIME	50

#ifdef USE_WEAPON_SPREAD

static	float	s_quadFactor;
static	vec3_t	forward, right, up;
static	vec3_t	muzzle;
static	vec3_t	muzzle_origin; // for hitscan weapon trace

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
	if ( ent->client->ps.powerups[PW_QUAD] ) {
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
gentity_t *fire_special_grenade (gentity_t *self, vec3_t start, vec3_t dir, qboolean isCluster) 
{
	gentity_t	*bolt;

	VectorNormalize (dir);

	bolt = G_Spawn();
#ifdef USE_CLUSTER_GRENADES
	if(g_clusterGrenades.integer && isCluster) {
	  bolt->classname = "cgrenade";
	} else
#endif
	bolt->classname = "grenade";
#ifdef USE_VORTEX_GRENADES
  if(g_vortexGrenades.integer) {
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
#ifdef USE_CLUSTER_GRENADES
	if(isCluster) {
		VectorScale( dir, 400, bolt->s.pos.trDelta );
	} else
#endif
	VectorScale( dir, 700, bolt->s.pos.trDelta );
	SnapVector( bolt->s.pos.trDelta );			// save net bandwidth

	VectorCopy (start, bolt->r.currentOrigin);

	return bolt;
}

#ifdef USE_CLUSTER_GRENADES
gentity_t *fire_cluster_grenade (gentity_t *self, vec3_t start, vec3_t dir) {
	return fire_special_grenade(self, start, dir, g_clusterGrenades.integer);
}
#endif
