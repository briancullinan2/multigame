
#include "cg_local.h"

#ifdef USE_ITEM_TIMERS
//#define USE_GUNNM_TIMER 1
#define TIMER_SIZE 24
/*
==================
CG_ItemTimer
==================
*/
#ifdef USE_GUNNM_TIMER
static void CG_ItemTimer( entityState_t	*es, const vec3_t origin ) {
	refEntity_t		re;
	vec3_t			angles;
	float			c, len;
	int				i, numsegs, totalsegs;
	qhandle_t		lengthShader;
	vec3_t			vec = { 0, 0, 1 };

	int startTime, respawnTime;

	startTime = es->time;
	respawnTime = es->frame * 1000; // save bandwidth

	if (!cg_itemTimer.integer) {
		return;
	}

	VectorSubtract(cg.refdef.vieworg, origin, re.origin);
	len = VectorLength(re.origin);
	VectorNormalize(re.origin);

	re.shaderRGBA[0] = re.shaderRGBA[1] = re.shaderRGBA[2] = 0xff; // where rgb are set in megamind's code?

	// if the view would be "inside" the sprite, kill the sprite
	// so it doesn't add too much overdraw
	// TODO: count up and count down
	// TODO: modifiable distance
	if (len <= 20) {
		//Com_Printf("Too close:\n");
		return;
	}
	else if (len > 20 && len <= 300) {
		re.shaderRGBA[3] = 0xff;
	}
	else if (len > 300 && len <= 500) {
		float scale = (500 - len) / 200;
		re.shaderRGBA[3] = 0xff * scale;
	}
	else {
		//Com_Printf("Too far away:\n");
		return; // too far away, don't add to scene
	}

	// Add powerup icon at center
	re.reType = RT_SPRITE;
	re.renderfx = /*RF_DEPTHHACK |*/ RF_FIRST_PERSON; // with RF_DEPTHHACK counter is visible behind wall

	re.radius = 3;
	VectorCopy(origin, re.origin);
	re.origin[2] += (TIMER_SIZE * 0.5f);

	VectorClear(angles);
	AnglesToAxis(angles, re.axis);

	re.rotation = 0;

	re.customShader = cg_items[es->modelindex].icon_df;
	trap_R_AddRefEntityToScene(&re);

	// Choose the slice type
	numsegs = respawnTime / 5000;
	if (numsegs < 7) {
		lengthShader = cgs.media.timerSlices[0];
		totalsegs = 5;
	}
	else if (numsegs < 12) {
		lengthShader = cgs.media.timerSlices[1];
		totalsegs = 7;
	}
	else if (numsegs < 24) {
		lengthShader = cgs.media.timerSlices[2];
		totalsegs = 12;
	}
	else {
		lengthShader = cgs.media.timerSlices[3];
		totalsegs = 24;
	}

	c = ((startTime + respawnTime) - cg.time) * (1.0 / respawnTime);
	re.radius = TIMER_SIZE * 0.5f;

	// calculate segments
	numsegs = ceil((1.0f - c) * totalsegs);
	for (i = 0; i < numsegs; i++) {
		re.rotation = 180.0f - (360.0f / (totalsegs * 2)) - (360.0f / totalsegs) * i;
		VectorMA(origin, (float)(0.5 - 1) * TIMER_SIZE, vec, re.origin);
		re.origin[2] += TIMER_SIZE;
		re.customShader = lengthShader;

		// fade the last segment in gradually
		if (i == numsegs - 1) {

			/* fadding
			float fade = ((1.0f - c) - i * (1.0f / totalsegs) + 0.01f) / (1.0f / totalsegs);
			if (fade > 1.0f) fade = 1.0f;
			re.shaderRGBA[3] = (int)(fade * (float)re.shaderRGBA[3]);
			*/

			// Blinking
			if ((cg.time >> 9) & 1) {
				re.shaderRGBA[3] = 0xff;// (int)(fade * (float)re.shaderRGBA[3]);
			}
			else {
				re.shaderRGBA[3] = 0x33;
			}

			/* TODO better blinking, something like this:
			if (((startTime ) - cg.time) < POWERUP_BLINKS * POWERUP_BLINK_TIME) {
				re.shaderRGBA[3] = 0xff;
			}
			else {
				re.shaderRGBA[3] = 0x33;
			}*/
		}//last segment
		trap_R_AddRefEntityToScene(&re);
	}
}
#else

void CG_ItemTimer(int client, const vec3_t origin, int startTime, int respawnTime) {
  refEntity_t		re;
  vec3_t			angles;
  vec3_t		  vec = {0, 0, 1};
	float		    c, len;
  int         i, numsegs, totalsegs;
  qhandle_t   lengthShader;

  if(!cg_itemTimer.integer) {
    return;
  }

  re.reType = RT_SPRITE;
  re.renderfx = RF_DEPTHHACK | RF_FIRST_PERSON;
  re.radius = 16;

  VectorClear(angles);
  AnglesToAxis( angles, re.axis );

  c = ( (startTime + respawnTime) - cg.time ) * (1.0 / respawnTime);

	re.radius = TIMER_SIZE / 2;

  VectorSubtract( cg.refdef.vieworg, origin, re.origin );
  len = VectorLength( re.origin );
	VectorNormalize(re.origin);

	// if the view would be "inside" the sprite, kill the sprite
	// so it doesn't add too much overdraw
  // TODO: count up and count down
  // TODO: modifiable distance
	if ( len <= 20 ) {
    //Com_Printf("Too close:\n");
		return;
	} else if (len > 20 && len <= 300) {
    re.shaderRGBA[3] = 0xff;
  } else if (len > 300 && len <= 500) {
    float scale = (500 - len)/200;
    re.shaderRGBA[3] = 0xff * scale;
  } else {
    //Com_Printf("Too far away:\n");
    return; // too far away, don't add to scene
  }
  
  numsegs = respawnTime / 5000;
  if(numsegs < 7) {
    lengthShader = cgs.media.timerSlices[0];
    totalsegs = 5;
  } else if (numsegs < 12) {
    lengthShader = cgs.media.timerSlices[1];
    totalsegs = 7;
  } else if (numsegs < 24) {
    lengthShader = cgs.media.timerSlices[2];
    totalsegs = 12;
  } else {
    lengthShader = cgs.media.timerSlices[3];
    totalsegs = 24;
  }
  

  // calculate segments
  numsegs = ceil((1.0f-c) * totalsegs);
  for (i = 0; i < numsegs; i++) {
    re.rotation = 180.0f - (360.0f / (totalsegs * 2)) - (360.0f / totalsegs) * i;
    VectorMA(origin, (float) (0.5 - 1) * TIMER_SIZE, vec, re.origin);
		re.origin[2] += TIMER_SIZE;
    re.customShader = lengthShader;
    // fade the last segment in gradually
    if(i == numsegs - 1) {
      float fade = ((1.0f - c) - i * (1.0f / totalsegs) + 0.01f) / (1.0f / totalsegs);
      if(fade > 1.0f) fade = 1.0f;
      re.shaderRGBA[3] = (int)(fade * (float)re.shaderRGBA[3]);
    }
    trap_R_AddRefEntityToScene( &re );
  }
}
#endif
#endif