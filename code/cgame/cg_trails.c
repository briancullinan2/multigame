
#include "cg_local.h"
#include "../ui/ui_shared.h"

#define VectorSet4(v,x,y,z,w)	((v)[0]=(x),(v)[1]=(y),(v)[2]=(z),(v)[3]=(w))

void CG_AddPolyToPool( qhandle_t shader, const polyVert_t *verts );

#define TRAIL_SPACING 4
#define TRAIL_LENGTH 64
#define TRAIL_WIDTH 12
#define TRAIL_SPEED 20

static void CG_TrailParticleRender( vec3_t pos, vec3_t deltaNormalized, float length, qhandle_t shader ) {
	// Draw a raindrop

	vec3_t		forward, right, viewAxis;
	polyVert_t	verts[3];
	//vec2_t		line;
	float		len, /*frac,*/ dist;
	vec3_t		start, finish;
	//float		groundHeight;
	//int			msec = trap_Milliseconds();
	float height = TRAIL_WIDTH; // + random() * 3;
	float weight = TRAIL_WIDTH; //height * 0.5f;
	vec3_t colour;
	colour[0] = 0xFF; //0.8 + 0.2 * random() * 0xFF;
	colour[1] = 0xFF; //0.8 + 0.2 * random() * 0xFF;
	colour[2] = 0xFF; //0.8 + 0.2 * random() * 0xFF;

	if( CG_CullPoint( pos ) ) {
		return;
	}

	VectorCopy( pos, start );

	dist = DistanceSquared( pos, cg.refdef.vieworg );

	// Make sure it doesn't clip through surfaces
	len = height;

	if( len <= 0 ) {
		return;
	}

	if(dist < Square( 32.f )) {
		return;
	}

	// fade nearby rain particles
	if ( dist < Square( 128.f ) ) {
		dist = .25f + .75f * ( dist / Square( 128.f ) );
	} else {
		dist = 1.0f;
	}

#if 0
	//AngleVectors(cg.refdefViewAngles, forward, NULL, NULL);
	VectorClear(forward);
	forward[1] = 1.0f;
	//VectorCopy( deltaNormalized, forward );
	VectorMA( start, -len, forward, finish );

	line[0] = DotProduct( forward, cg.refdef.viewaxis[1] );
	line[1] = DotProduct( forward, cg.refdef.viewaxis[2] );

	VectorScale( cg.refdef.viewaxis[1], line[1], right );
	VectorMA( right, -line[0], cg.refdef.viewaxis[2], right );
	VectorNormalize( right );
#else
  VectorCopy( deltaNormalized, forward );

	VectorCopy( pos, start );
	VectorMA( start, len, forward, finish );

  VectorSubtract( cg.refdef.vieworg, pos, viewAxis );
  CrossProduct( viewAxis, forward, right );
  VectorNormalize( right );
#endif
	
	dist = length; //length / 256.0f;

	//CG_Printf("value: %f\n", dist);

	VectorCopy( finish, verts[0].xyz );	
	verts[0].st[0] = 0.5f;
	verts[0].st[1] = 0;
	verts[0].modulate[0] = colour[0];
	verts[0].modulate[1] = colour[1];
	verts[0].modulate[2] = colour[2];
	verts[0].modulate[3] = 100 * dist;

	VectorMA( start, -weight, right, verts[1].xyz );
	verts[1].st[0] = 0;
	verts[1].st[1] = 1;
	verts[1].modulate[0] = colour[0];
	verts[1].modulate[1] = colour[1];
	verts[2].modulate[2] = colour[2];
	verts[1].modulate[3] = 200 * dist;

	VectorMA( start, weight, right, verts[2].xyz );
	verts[2].st[0] = 1;
	verts[2].st[1] = 1;
	verts[2].modulate[0] = colour[0];
	verts[2].modulate[1] = colour[1];
	verts[2].modulate[2] = colour[2];
	verts[2].modulate[3] = 200 * dist;

	CG_AddPolyToPool( shader, verts );

}

static int trailTime[MAX_CLIENTS];
static int trailLength[MAX_CLIENTS];
static int trailHead[MAX_CLIENTS];
static vec3_t trailPos[MAX_CLIENTS][TRAIL_LENGTH];

void CG_AddTrailEffects( void ) {
	int i, j;
	for(j = 0; j < MAX_CLIENTS; j++) {
		vec3_t prev;
		VectorCopy(trailPos[j][trailHead[j]], prev);

		if(cg_entities[j].currentState.eType != ET_PLAYER) {
			continue;
		}

		for ( i = 0 ; i < trailLength[j] ; i++ ) {
			vec3_t temp;
			//float length;
			int trailI = trailHead[j] - i;
			if(trailI < 0) {
				trailI += TRAIL_LENGTH;
			}
			VectorSubtract(trailPos[j][trailI], prev, temp);
			/*length =*/ VectorNormalize(temp);
			//CG_Printf("pos: %f %f %f\n", trailPos[i][0], trailPos[i][1], trailPos[i][2]);
			CG_TrailParticleRender(trailPos[j][trailI], temp, 1.0f - (1.0f * i) / trailLength[j], cgs.media.dustPuffShader);
			VectorCopy(trailPos[j][i], prev);
		}
	}
	
}

void CG_RecordKi(centity_t *cent, qboolean moving, qboolean isAdding);


void CG_RecordPosition(centity_t *cent, qboolean moving, qboolean isAdding) {
	int j;
	vec3_t temp;
	float length;
	
	if(cent->currentState.clientNum > MAX_CLIENTS) {
		return;
	}

  if(cg_kiTrail.integer) {
    CG_RecordKi(cent, moving, isAdding);
    return;
  }

  if(!isAdding) {
    return; // ours removed automatically based on time
  }

	j = cent->currentState.clientNum;
	
	VectorSubtract(cent->lerpOrigin, trailPos[j][trailHead[j]], temp);
	length = VectorNormalize(temp);

	// reduce the trail when the player stops moving so fast
	if(cg.time - trailTime[j] > TRAIL_SPEED) {
		if(trailLength[j] > 0) {
			trailLength[j]--;
		}
		trailTime[j] = cg.time;
	}

	if(fabs(length) < TRAIL_SPACING) {
		return;
	}

	if(trailLength[j] + 1 < TRAIL_LENGTH) {
		trailLength[j]++;
	}

	// record position
	trailHead[j]++;
	if(trailHead[j] >= TRAIL_LENGTH) {
		trailHead[j] = 0;
	}
	VectorCopy(cent->lerpOrigin, trailPos[j][trailHead[j]]);
}


// kiTrails from LegendaryGuard


#define KI_TRAIL_SEGMENTS		99
#define KI_TRAIL_WIDTH			15

typedef struct {
	vec3_t segments[KI_TRAIL_SEGMENTS];
	int numSegments;
} kiTrail_t;

static kiTrail_t cg_kiTrails[MAX_GENTITIES];

/*
===============
CG_InitKiTrails
Initializes the array of trails for all centities.
Should be called from CG_Init in cg_main.c
===============
*/
void CG_InitKiTrails( void ) {
	memset( &cg_kiTrails, 0, sizeof(cg_kiTrails) );
}

/*
===============
CG_ResetKiTrail
Reset entity's ki trail.
Should be called whenever an entity that has to use a trail, wasn't in the PVS the previous frame.
entityNum: Valid entity number
origin:    Point from where the trail should start.
           (This should be equal to the entity's current position.)
=====================
*/
void CG_ResetKiTrail( int entityNum, vec3_t origin ) {
	int i;

	for ( i = 0; i < KI_TRAIL_SEGMENTS; i++ ) {
		VectorCopy( origin, cg_kiTrails[entityNum].segments[i] );
	}
	cg_kiTrails[entityNum].numSegments = 0;
}

/*
====================
CG_UpdateKiTrail
Updates the head of the trail with a new position.
Should be called whenever an entity that has to use a trail, is in the PVS.
entityNum: Valid entity number
origin:    Point where the trail's head should go to.
           (This should be equal to the entity's current position.)
remove:    If true, every segment is removed.
====================
*/
void CG_UpdateKiTrail( int entityNum, vec3_t origin, qboolean remove ) {
	int i;

	if ( entityNum < 0 || entityNum >= MAX_GENTITIES ) {
		return;
	}

	if ( remove ) { // removes every segment
		cg_kiTrails[entityNum].numSegments--;
	} else {
		if ( cg_kiTrails[entityNum].numSegments < KI_TRAIL_SEGMENTS ) {
			cg_kiTrails[entityNum].numSegments++;
		}
	}

	// shift points down the buffer
	for ( i = cg_kiTrails[entityNum].numSegments - 1; i > 0; i-- ) {
		VectorCopy( cg_kiTrails[entityNum].segments[i - 1], cg_kiTrails[entityNum].segments[i] );
	}

	// add the current position at the start
	VectorCopy( origin, cg_kiTrails[entityNum].segments[0] );
}

/*
=====================
CG_KiTrail
Adds ki trail segments
=====================
*/
void CG_KiTrail( int entityNum, qhandle_t hShader ) {
	int i, j;
	polyVert_t verts[4];

	if ( entityNum < 0 || entityNum >= MAX_GENTITIES ) {
		return;
	}

	for ( i = 0; i < cg_kiTrails[entityNum].numSegments - 1; i++ ) {
		// loop to render the segment 3 times
		for ( j = 0; j < 3; j++ ) {
			vec3_t start, end, forward, right;
			vec3_t viewAxis[3];
			int kiTrailLength = cg_kiTrail.integer;

			if ( kiTrailLength > KI_TRAIL_SEGMENTS ) {
				kiTrailLength = KI_TRAIL_SEGMENTS;
			}

			if ( i > kiTrailLength ) {
				return;
			}

			if ( i + j >= cg_kiTrails[entityNum].numSegments - 1 ) {
				return;
			}

			VectorCopy( cg_kiTrails[entityNum].segments[i + j], start );
			VectorCopy( cg_kiTrails[entityNum].segments[i + j + 1], end );

			VectorSubtract( end, start, forward );
			VectorNormalize( forward );

			VectorSubtract( cg.refdef.vieworg, start, viewAxis[0] );
			CrossProduct( viewAxis[0], forward, right );
			VectorNormalize( right );

			VectorMA( end, KI_TRAIL_WIDTH, right, verts[0].xyz );
			verts[0].st[0] = 0;
			verts[0].st[1] = 1;
			VectorSet4( verts[0].modulate, 255, 255, 255, 255 );

			VectorMA( end, -KI_TRAIL_WIDTH, right, verts[1].xyz );
			verts[1].st[0] = 1;
			verts[1].st[1] = 0;
			VectorSet4( verts[1].modulate, 255, 255, 255, 255 );

			VectorMA( start, -KI_TRAIL_WIDTH, right, verts[2].xyz );
			verts[2].st[0] = 1;
			verts[2].st[1] = 0;
			VectorSet4( verts[2].modulate, 255, 255, 255, 255 );

			VectorMA( start, KI_TRAIL_WIDTH, right, verts[3].xyz );
			verts[3].st[0] = 0;
			verts[3].st[1] = 1;
			VectorSet4( verts[3].modulate, 255, 255, 255, 255 );

			trap_R_AddPolyToScene( hShader, 4, verts );
		}
	}
}

#define KI_TRAIL_ZPOS 5

#define REMOVING_KI_TRAILS(clientNum, kiTrailOrigin, kiTrailShader, fastRemove) \
	if ( cg.time > cent->pe.kiTrailTime ) { /* reset ki trail position avoid being zeroed */ \
		CG_ResetKiTrail( clientNum, kiTrailOrigin ); \
	} else { /* ki trails keep running in that moment, but their segments are being removed */ \
		CG_UpdateKiTrail( clientNum, kiTrailOrigin, fastRemove ); \
		CG_KiTrail( clientNum, kiTrailShader ); \
	}

void CG_RecordKi(centity_t *cent, qboolean moving, qboolean isAdding) {
	clientInfo_t	*ci;
	int				clientNum;
  vec3_t			kiTrailOrigin;
  qhandle_t		kiTrailShader;

  clientNum = cent->currentState.clientNum;
  ci = &cgs.clientinfo[ clientNum ];

  kiTrailShader = cgs.media.kiTrailRedShader;
  // BFP - TODO: Add yellow ki trail only when the player is transformed, but don't override when playing a team gamemode
  // kiTrailShader = cgs.media.kiTrailYellowShader;
  if ( ci->team == TEAM_BLUE ) {
    kiTrailShader = cgs.media.kiTrailBlueShader;
  }

  // apply time for using ki trail
  cent->pe.kiTrailTime = cg.time + cg_kiTrail.integer*5;
  VectorCopy( cent->currentState.pos.trBase, kiTrailOrigin );
  kiTrailOrigin[2] += KI_TRAIL_ZPOS;

  // BFP - Ki trail
  if ( isAdding
    //( cent->currentState.legsAnim & ~ANIM_TOGGLEBIT ) != LEGS_CHARGE 
    //( cent->currentState.legsAnim & ~ANIM_TOGGLEBIT ) != LEGS_IDLE
    //&&  ( cent->currentState.legsAnim & ~ANIM_TOGGLEBIT ) != LEGS_IDLECR
    && cg_kiTrail.integer >= 10 ) {
    CG_UpdateKiTrail( clientNum, kiTrailOrigin, qfalse );
    CG_KiTrail( clientNum, kiTrailShader );
  } else { // handle when the ki trail was being used previously
    REMOVING_KI_TRAILS( clientNum, kiTrailOrigin, kiTrailShader, qtrue )
  }

}


