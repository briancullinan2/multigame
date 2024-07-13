// Copyright (C) 1999-2000 Id Software, Inc.
//
// cg_snapshot.c -- things that happen on snapshot transition,
// not necessarily every single rendered frame

#include "cg_local.h"



/*
==================
CG_ResetEntity
==================
*/
void CG_ResetEntity( centity_t *cent ) {
	// if the previous snapshot this entity was updated in is at least
	// an event window back in time then we can reset the previous event
	if ( cent->snapShotTime < cg.time - EVENT_VALID_MSEC ) {
		cent->previousEvent = 0;
	}

	cent->trailTime = cg.snap->serverTime;

	VectorCopy (cent->currentState.origin, cent->lerpOrigin);
	VectorCopy (cent->currentState.angles, cent->lerpAngles);
	if ( cent->currentState.eType == ET_PLAYER ) {
		CG_ResetPlayerEntity( cent );
	}
}

/*
===============
CG_TransitionEntity

cent->nextState is moved to cent->currentState and events are fired
===============
*/
static void CG_TransitionEntity( centity_t *cent ) {
	cent->currentState = cent->nextState;
	cent->currentValid = qtrue;

	// reset if the entity wasn't in the last frame or was teleported
	if ( !cent->interpolate ) {
		CG_ResetEntity( cent );
	}

	// clear the next state.  if will be set by the next CG_SetNextSnap
	cent->interpolate = qfalse;

	// check for events
	CG_CheckEvents( cent );
}


/*
==================
CG_SetInitialSnapshot

This will only happen on the very first snapshot, or
on tourney restarts.  All other times will use 
CG_TransitionSnapshot instead.

FIXME: Also called by map_restart?
==================
*/
void CG_SetInitialSnapshot( snapshot_t *snap ) {
	int				i;
	centity_t		*cent;
	entityState_t	*state;

	cg.snap = snap;

	BG_PlayerStateToEntityState( &snap->ps, &cg_entities[ snap->ps.clientNum ].currentState, qfalse );

	// sort out solid entities
	CG_BuildSolidList();

	CG_ExecuteNewServerCommands( snap->serverCommandSequence );

	// set our local weapon selection pointer to
	// what the server has indicated the current weapon is
	CG_Respawn();

	for ( i = 0 ; i < cg.snap->numEntities ; i++ ) {
		state = &cg.snap->entities[ i ];
		cent = &cg_entities[ state->number ];

		memcpy(&cent->currentState, state, sizeof(entityState_t));
		//cent->currentState = *state;
		cent->interpolate = qfalse;
		cent->currentValid = qtrue;

		CG_ResetEntity( cent );

		// check for events
		CG_CheckEvents( cent );
	}
}


/*
===================
CG_TransitionSnapshot

The transition point from snap to nextSnap has passed
===================
*/
static void CG_TransitionSnapshot( void ) {
	centity_t			*cent;
	snapshot_t			*oldFrame;
	int					i;

	if ( !cg.snap ) {
		CG_Error( "CG_TransitionSnapshot: NULL cg.snap" );
	}
	if ( !cg.nextSnap ) {
		CG_Error( "CG_TransitionSnapshot: NULL cg.nextSnap" );
	}

	// execute any server string commands before transitioning entities
	CG_ExecuteNewServerCommands( cg.nextSnap->serverCommandSequence );

	// if we had a map_restart, set everthing with initial
	if ( !cg.snap ) {
		return;
	}

	// clear the currentValid flag for all entities in the existing snapshot
	for ( i = 0 ; i < cg.snap->numEntities ; i++ ) {
		cent = &cg_entities[ cg.snap->entities[ i ].number ];
		cent->currentValid = qfalse;
	}

	// move nextSnap to snap and do the transitions
	oldFrame = cg.snap;
	cg.snap = cg.nextSnap;

	BG_PlayerStateToEntityState( &cg.snap->ps, &cg_entities[ cg.snap->ps.clientNum ].currentState, qfalse );
	cg_entities[ cg.snap->ps.clientNum ].interpolate = qfalse;

	for ( i = 0 ; i < cg.snap->numEntities ; i++ ) {
		cent = &cg_entities[ cg.snap->entities[ i ].number ];
		CG_TransitionEntity( cent );

		// remember time of snapshot this entity was last updated in
		cent->snapShotTime = cg.snap->serverTime;
	}

	cg.nextSnap = NULL;

	// check for playerstate transition events
	if ( oldFrame ) {
		playerState_t	*ops, *ps;

		ops = &oldFrame->ps;
		ps = &cg.snap->ps;
		// teleporting checks are irrespective of prediction
		if ( ( ps->eFlags ^ ops->eFlags ) & EF_TELEPORT_BIT ) {
			cg.thisFrameTeleport = qtrue;	// will be cleared by prediction code
		}

		// if we are not doing client side movement prediction for any
		// reason, then the client events and view changes will be issued now
		if ( cg.demoPlayback || (cg.snap->ps.pm_flags & PMF_FOLLOW)
			|| cg_nopredict.integer || cgs.synchronousClients ) {
			CG_TransitionPlayerState( ps, ops );
		}



#ifdef USE_ADVANCED_WEAPONS
	{
		//cg.weaponClass = cg.snap->ps.stats[STAT_WEAPONS] >> 9;
		int newClass = floor(cg.snap->ps.weapon / WP_MAX_WEAPONS);
		if(newClass < 0) {
			newClass = WP_MAX_CLASSES + newClass;
		}

		if(newClass != cg.weaponClass || cg.weaponChange
			|| cg.snap->ps.stats[STAT_WEAPONS] != oldFrame->ps.stats[STAT_WEAPONS]) {
			cg.weaponClass = newClass;
			if(cg.weaponChange < 0 && !CG_WeaponSelectable( cg.weaponSelect )) {
				PrevClass();
				//CG_PrevWeapon_f();
				cg.weaponChange = 0;
			}
			if(cg.weaponChange > 0 && !CG_WeaponSelectable( cg.weaponSelect )) {
				NextClass();
				//CG_NextWeapon_f();
				cg.weaponChange = 0;
			}
		}

		if(cg.snap->ps.stats[STAT_WEAPONS] != oldFrame->ps.stats[STAT_WEAPONS]
			//oldFrame->ps.weapon != cg.snap->ps.weapon || cg.weaponClass != newClass
			) {
			
			/*CG_Printf("weapons %i: %i %i %i %i %i %i %i %i %i %i\n%i %i %i %i %i %i %i %i %i %i\n", 
				cg.weaponClass,
				cg.snap->ps.ammo[0],
				cg.snap->ps.ammo[1],
				cg.snap->ps.ammo[2],
				cg.snap->ps.ammo[3],
				cg.snap->ps.ammo[4],
				cg.snap->ps.ammo[5],
				cg.snap->ps.ammo[6],
				cg.snap->ps.ammo[7],
				cg.snap->ps.ammo[8],
				cg.snap->ps.ammo[9],
				(cg.snap->ps.stats[STAT_WEAPONS] & (1 << 0)) >> 0,
				(cg.snap->ps.stats[STAT_WEAPONS] & (1 << 1)) >> 1,
				(cg.snap->ps.stats[STAT_WEAPONS] & (1 << 2)) >> 2,
				(cg.snap->ps.stats[STAT_WEAPONS] & (1 << 3)) >> 3,
				(cg.snap->ps.stats[STAT_WEAPONS] & (1 << 4)) >> 4,
				(cg.snap->ps.stats[STAT_WEAPONS] & (1 << 5)) >> 5,
				(cg.snap->ps.stats[STAT_WEAPONS] & (1 << 6)) >> 6,
				(cg.snap->ps.stats[STAT_WEAPONS] & (1 << 7)) >> 7,
				(cg.snap->ps.stats[STAT_WEAPONS] & (1 << 8)) >> 8,
				(cg.snap->ps.stats[STAT_WEAPONS] & (1 << 9)) >> 9
			);*/
		}
	}
	if(cg.weaponClass >= WP_MAX_CLASSES) {
		CG_Error("CG_TransitionSnapshot: out of range weapon class %d", cg.weaponClass);
	}
#endif


#ifdef USE_ADVANCED_ITEMS
		if(ps->stats[STAT_HOLDABLE_UPDATE] != ops->stats[STAT_HOLDABLE_UPDATE]
			|| ps->stats[STAT_HOLDABLE_AVAILABLE] != ops->stats[STAT_HOLDABLE_AVAILABLE]) {
			int j;
			int prevItemClass = ps->stats[STAT_HOLDABLE_UPDATE];
			CG_Printf("items %i: ", ps->stats[STAT_HOLDABLE_UPDATE]);
			for(j = 0; j < PW_MAX_POWERUPS; j++) {
				if(ps->stats[STAT_HOLDABLE_AVAILABLE] & (1 << j)) {
					CG_Printf("1");
					cg.inventory[prevItemClass * PW_MAX_POWERUPS + j] = 1;
				} else {
					CG_Printf("0");
					cg.inventory[prevItemClass * PW_MAX_POWERUPS + j] = 0;
				}
			}
			CG_Printf("\n");
		}

#endif


	}
}


/*
===================
CG_SetNextSnap

A new snapshot has just been read in from the client system.
===================
*/
static void CG_SetNextSnap( snapshot_t *snap ) {
	int					num;
	int					esNum;
	entityState_t		*es;
	centity_t			*cent;

	cg.nextSnap = snap;

	BG_PlayerStateToEntityState( &snap->ps, &cg_entities[ snap->ps.clientNum ].nextState, qfalse );
	cg_entities[ cg.snap->ps.clientNum ].interpolate = qtrue;

	// check for extrapolation errors
	for ( num = 0 ; num < snap->numEntities ; num++ ) {
		es = &snap->entities[num];
		cent = &cg_entities[ es->number ];

		memcpy(&cent->nextState, es, sizeof(entityState_t));
		//cent->nextState = *es;

		if ( cgs.ospEnc && ( esNum = cent->nextState.number ) <= MAX_CLIENTS-1 ) {
			cent->nextState.pos.trBase[0] += (677 - 7 * esNum);
			cent->nextState.pos.trBase[1] += (411 - 12 * esNum);
			cent->nextState.pos.trBase[2] += (243 - 2 * esNum);
		}

		// if this frame is a teleport, or the entity wasn't in the
		// previous frame, don't interpolate
		if ( !cent->currentValid || ( ( cent->currentState.eFlags ^ es->eFlags ) & EF_TELEPORT_BIT )  ) {
			cent->interpolate = qfalse;
		} else {
			cent->interpolate = qtrue;
		}
	}

	// if the next frame is a teleport for the playerstate, we
	// can't interpolate during demos
	if ( cg.snap && ( ( snap->ps.eFlags ^ cg.snap->ps.eFlags ) & EF_TELEPORT_BIT ) ) {
		cg.nextFrameTeleport = qtrue;
	} else {
		cg.nextFrameTeleport = qfalse;
	}

	// if changing follow mode, don't interpolate
	if ( cg.nextSnap->ps.clientNum != cg.snap->ps.clientNum ) {
		cg.nextFrameTeleport = qtrue;
	}

	// if changing server restarts, don't interpolate
	if ( ( cg.nextSnap->snapFlags ^ cg.snap->snapFlags ) & SNAPFLAG_SERVERCOUNT ) {
		cg.nextFrameTeleport = qtrue;
	}

	// sort out solid entities
	CG_BuildSolidList();
}


/*
========================
CG_ReadNextSnapshot

This is the only place new snapshots are requested
This may increment cgs.processedSnapshotNum multiple
times if the client system fails to return a
valid snapshot.
========================
*/
static snapshot_t *CG_ReadNextSnapshot( void ) {
	qboolean	r;
	snapshot_t	*dest;

	if ( cg.latestSnapshotNum > cgs.processedSnapshotNum + 1000 ) {
		CG_Printf( "WARNING: CG_ReadNextSnapshot: way out of range, %i > %i\n", 
			cg.latestSnapshotNum, cgs.processedSnapshotNum );
	}

	while ( cgs.processedSnapshotNum < cg.latestSnapshotNum ) {
		// decide which of the two slots to load it into
		if ( cg.snap == &cg.activeSnapshots[0] ) {
			dest = &cg.activeSnapshots[1];
		} else {
			dest = &cg.activeSnapshots[0];
		}

		// try to read the snapshot from the client system
		cgs.processedSnapshotNum++;
		r = trap_GetSnapshot( cgs.processedSnapshotNum, dest );

		// FIXME: why would trap_GetSnapshot return a snapshot with the same server time
		if ( cg.snap && r && dest->serverTime == cg.snap->serverTime ) {
			//continue;
		}

		// if it succeeded, return
		if ( r ) {
			CG_AddLagometerSnapshotInfo( dest );
			return dest;
		}

		// a GetSnapshot will return failure if the snapshot
		// never arrived, or  is so old that its entities
		// have been shoved off the end of the circular
		// buffer in the client system.

		// record as a dropped packet
		if ( cg.snap ) {
			CG_AddLagometerSnapshotInfo( NULL );
		}

		// If there are additional snapshots, continue trying to
		// read them.
	}

	// nothing left to read
	return NULL;
}


/*
============
CG_ProcessSnapshots

We are trying to set up a renderable view, so determine
what the simulated time is, and try to get snapshots
both before and after that time if available.

If we don't have a valid cg.snap after exiting this function,
then a 3D game view cannot be rendered.  This should only happen
right after the initial connection.  After cg.snap has been valid
once, it will never turn invalid.

Even if cg.snap is valid, cg.nextSnap may not be, if the snapshot
hasn't arrived yet (it becomes an extrapolating situation instead
of an interpolating one)

============
*/
void CG_ProcessSnapshots( void ) {
	snapshot_t		*snap;
	int				n;

	// see what the latest snapshot the client system has is
	trap_GetCurrentSnapshotNumber( &n, &cg.latestSnapshotTime );
	if ( n != cg.latestSnapshotNum ) {
		if ( n < cg.latestSnapshotNum ) {
			// this should never happen
			CG_Error( "CG_ProcessSnapshots: n < cg.latestSnapshotNum" );
		}
		cg.latestSnapshotNum = n;
	}

	// If we have yet to receive a snapshot, check for it.
	// Once we have gotten the first snapshot, cg.snap will
	// always have valid data for the rest of the game
	while ( !cg.snap ) {
		snap = CG_ReadNextSnapshot();
		if ( !snap ) {
			// we can't continue until we get a snapshot
			return;
		}

		// set our weapon selection to what
		// the playerstate is currently using
		if ( !( snap->snapFlags & SNAPFLAG_NOT_ACTIVE ) ) {
			CG_SetInitialSnapshot( snap );
		}
	}

	// loop until we either have a valid nextSnap with a serverTime
	// greater than cg.time to interpolate towards, or we run
	// out of available snapshots
	do {
		// if we don't have a nextframe, try and read a new one in
		if ( !cg.nextSnap ) {
			snap = CG_ReadNextSnapshot();

			// if we still don't have a nextframe, we will just have to
			// extrapolate
			if ( !snap ) {
				break;
			}

			CG_SetNextSnap( snap );

			// if time went backwards, we have a level restart
			if ( cg.nextSnap->serverTime < cg.snap->serverTime ) {
				CG_Error( "CG_ProcessSnapshots: Server time went backwards" );
			}
		}

		// if our time is < nextFrame's, we have a nice interpolating state
		if ( cg.time >= cg.snap->serverTime && cg.time < cg.nextSnap->serverTime ) {
			break;
		}

		// we have passed the transition from nextFrame to frame
		CG_TransitionSnapshot();
	} while ( 1 );


	//CG_Printf("worlds: %i\n", cgs.clientinfo[cg.snap->ps.clientNum].worlds);

#ifdef USE_MULTIWORLD
// TODO: use this same method serverside to spy on and modify entity trajectories, like rockets and moving players
	// spy on snapshots from other CGVMs
	if(cg.multiworld) {
		int i;
		for(i = 0; i < MAX_WORLDS; i++) {
			int latest, latestTime;
			trap_R_SwitchWorld(i);
			trap_GetCurrentSnapshotNumber( &latest, &latestTime );
			if(cg.snapshotNumWorlds[i] < latest) {
				cg.snapshotNumWorlds[i] = latest;
				trap_GetSnapshot( latest, &cg.snapshotWorlds[i] );
			}
		}
		trap_R_SwitchWorld(cgs.selectedWorld);

	}
#endif





	// assert our valid conditions upon exiting
	if ( cg.snap == NULL ) {
		CG_Error( "CG_ProcessSnapshots: cg.snap == NULL" );
	}
	if ( cg.time < cg.snap->serverTime ) {
		// this can happen right after a vid_restart
		cg.time = cg.snap->serverTime;
	}
	if ( cg.nextSnap != NULL && cg.nextSnap->serverTime <= cg.time ) {
		CG_Error( "CG_ProcessSnapshots: cg.nextSnap->serverTime <= cg.time" );
	}
}
