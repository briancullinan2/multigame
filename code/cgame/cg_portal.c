
#include "cg_local.h"

#ifdef USE_PORTALS
#define AWAY_FROM_WALL 8.0f

void CG_PersonalPortal(const centity_t *cent) {
  vec3_t		    angles, angles2, vec, velocity;
	//vec3_t		    origin;
  refEntity_t			ent;
  qboolean        isMirror;
  centity_t       *target;
  //refdef_t		    refdef;
	float           len;
  //float           x = 0, y = 0, w = 640, h = 480;

  // always face portal towards player
  VectorSubtract( cg.refdef.vieworg, cent->lerpOrigin, vec );
  len = VectorNormalize( vec );
  VectorClear(angles);
	VectorClear(angles2);

  // add portal model
  memset (&ent, 0, sizeof(ent));

  // angles used below for camera direction
  if( cent->currentState.eventParm ) {
    // is wall portal
    ByteToDir( cent->currentState.eventParm == 1 ? 0 : cent->currentState.eventParm, angles );
    vectoangles( angles, angles );
		angles[ROLL] = 0;
    AnglesToAxis( angles, ent.axis );
    AngleVectors ( angles, velocity, NULL, NULL );
    VectorNormalize( velocity );
    VectorScale( velocity, AWAY_FROM_WALL, velocity );
    VectorSubtract( cent->lerpOrigin, velocity, ent.origin );
  } else {
		// is standalone portal
		// tracks player position on 2 axis to make it always look like someone can fit through it
		angles[YAW] = -180;
		angles[YAW] += cg.refdefViewAngles[YAW];
		angles[PITCH] -= cg.refdefViewAngles[PITCH];
		angles[ROLL] = 0;
		SnapVector( angles );
		AxisClear( ent.axis );
    AnglesToAxis( angles, ent.axis );
    VectorCopy( cent->lerpOrigin, ent.origin);
  }

  ent.hModel = cgs.gameModels[cent->currentState.modelindex];
	//VectorScale( ent.axis[0], 1.5, ent.axis[0] );
	//VectorScale( ent.axis[1], 1.5, ent.axis[1] );
	//VectorScale( ent.axis[2], 1.5, ent.axis[2] );
	//ent.nonNormalizedAxes = qtrue;
  if(!ent.hModel) {
    return;
  }
  ent.reType = RT_MODEL;
	//ent.reType = RT_SPRITE;
  ent.renderfx = RF_NOSHADOW | RF_FIRST_PERSON;
  ent.frame = cent->currentState.number;
  ent.oldframe = cent->currentState.otherEntityNum;
  trap_R_AddRefEntityToScene (&ent);



  // add portal camera view
  memset (&ent, 0, sizeof(ent));
	VectorCopy( cent->lerpOrigin, ent.origin );
  VectorCopy( cent->currentState.origin2, ent.oldorigin );
	//PerpendicularVector( vec, angles );
	//VectorScale( vec, AWAY_FROM_WALL, vec );
	//VectorSubtract( cent->lerpOrigin, vec, ent.origin );
	//VectorSubtract( cent->currentState.origin2, vec, ent.oldorigin );
  // TODO: size of portal model cached somewhere else like itemInfo_t?
  // TODO: change cg_weapons to match, it also uses midpoint of weapon models?
  //if(cent->currentState.powerups)
  //Com_Printf("origin: %f, %f, %f == %f, %f, %f\n", 
  //  ent.origin[0], ent.origin[1], ent.origin[2],
  //  ent.oldorigin[0], ent.oldorigin[1], ent.oldorigin[2]);
  if(ent.origin[0] == ent.oldorigin[0]
    && ent.origin[1] == ent.oldorigin[1]
    && ent.origin[2] == ent.oldorigin[2]
  ) {
    // is mirror
		isMirror = qtrue;
		target = &cg_entities[cent->currentState.otherEntityNum];
		if(target->currentState.eventParm) {
			AxisClear( ent.axis );
		} else {
			angles2[PITCH] = angles[PITCH];
			AnglesToAxis( angles2, ent.axis );
		}
		/*
		if( target->currentState.eventParm
			|| cent->currentState.eventParm ) {
			ByteToDir( target->currentState.eventParm, angles2 );
			vectoangles( angles2, angles2 );
			AnglesToAxis( angles2, ent.axis );
		}
		*/
  } else {
		isMirror = qfalse;
		target = &cg_entities[cent->currentState.otherEntityNum];
		if( target->currentState.eventParm ) {
			// if it is a wall portal
			ByteToDir( target->currentState.eventParm == 1 ? 0 : cent->currentState.eventParm, angles2 );
			vectoangles( angles2, angles2 );
			angles2[PITCH] = cg.refdefViewAngles[PITCH];
			angles2[YAW] += angles[YAW];
			angles2[ROLL] = -180;
			AnglesToAxis( angles2, ent.axis );
		} else {
			// TODO: camera bobbing might actually be cool for free standing portals
			// 180 from portal is same as continuing the view angle but from another position
			angles2[PITCH] = cg.refdefViewAngles[PITCH];
			angles2[YAW] = cg.refdefViewAngles[YAW];
			angles2[ROLL] = -90;
			SnapVector( angles2 );
			AnglesToAxis( angles2, ent.axis );
		}
	}
  ent.reType = RT_PORTALSURFACE;
  //ent.renderfx = RF_FIRST_PERSON;
	//ent.radius = 12;
	ent.skinNum = 0;
  ent.frame = cent->currentState.number;
  ent.oldframe = (cent->currentState.powerups & 0xF0) | 12;
  trap_R_AddRefEntityToScene(&ent);
}


void CG_DrawPortals( void ) {
	centity_t			*cent;
	int num;
	for ( num = 0 ; num < cg.snap->numEntities ; num++ ) {
		cent = &cg_entities[ cg.snap->entities[ num ].number ];
#ifdef USE_PORTALS
    if(cent->currentState.eType == ET_TELEPORT_TRIGGER
			&& cent->currentState.modelindex
			//&& cent->currentState.clientNum
			&& (cent->currentState.powerups & ((1 << 4) | (1 << 5)))
		) {
      CG_PersonalPortal( cent );
		}
#endif
	}
}

#endif
