

#include "cg_local.h"

#ifdef USE_ADVANCED_WEAPONS

#define WEAPON_CLASS (cg.weaponClass * WP_MAX_WEAPONS)

#else

#define WEAPON_CLASS 

#endif

/*
==========================
CG_RailTrail
==========================
*/
void CG_OldRailTrail (clientInfo_t *ci, vec3_t start, vec3_t end)
{
	vec3_t axis[36], move, move2, vec, temp;
	float  len;
	int    i, j, skip;

	localEntity_t *le;
	refEntity_t   *re;

#define RADIUS   4
#define ROTATION 1
#define SPACING  5

	start[2] -= 4;

	le = CG_AllocLocalEntity();
	re = &le->refEntity;

	le->leType = LE_FADE_RGB;
	le->startTime = cg.time;
	le->endTime = cg.time + cg_railTrailTime.value;
	le->lifeRate = 1.0 / (le->endTime - le->startTime);

	re->u.shaderTime = cg.time / 1000.0f;
	re->reType = RT_RAIL_CORE;
	re->customShader = cgs.media.railCoreShader;

	VectorCopy(start, re->origin);
	VectorCopy(end, re->oldorigin);

	re->shaderRGBA[0] = ci->color1[0] * 255;
	re->shaderRGBA[1] = ci->color1[1] * 255;
	re->shaderRGBA[2] = ci->color1[2] * 255;
	re->shaderRGBA[3] = 255;

	le->color[0] = ci->color1[0] * 0.75;
	le->color[1] = ci->color1[1] * 0.75;
	le->color[2] = ci->color1[2] * 0.75;
	le->color[3] = 1.0f;

	AxisClear( re->axis );

	if (cg_oldRail.integer) {
		// nudge down a bit so it isn't exactly in center
		re->origin[2] -= 8;
		re->oldorigin[2] -= 8;

		// leilei - reimplementing the rail discs that were removed in 1.30
		if (cg_oldRail.integer > 1) {

			le = CG_AllocLocalEntity();
			re = &le->refEntity;

			VectorCopy(start, re->origin);
			VectorCopy(end, re->oldorigin);
			le->leType = LE_FADE_RGB;
			le->startTime = cg.time;
			le->endTime = cg.time + cg_railTrailTime.value;
			le->lifeRate = 1.0 / (le->endTime - le->startTime);

			re->u.shaderTime = cg.time / 1000.0f;
			re->reType = RT_RAIL_RINGS;
			re->customShader = cgs.media.railRingsShader;
			re->shaderRGBA[0] = ci->color1[0] * 255;
			re->shaderRGBA[1] = ci->color1[1] * 255;
			re->shaderRGBA[2] = ci->color1[2] * 255;
			re->shaderRGBA[3] = 255;

			le->color[0] = ci->color1[0] * 0.75;
			le->color[1] = ci->color1[1] * 0.75;
			le->color[2] = ci->color1[2] * 0.75;
			le->color[3] = 1.0f;

			re->origin[2] -= 8;
			re->oldorigin[2] -= 8;

			if (cg_oldRail.integer > 2) {		// use the secondary color instead
				re->shaderRGBA[0] = ci->color2[0] * 255;
				re->shaderRGBA[1] = ci->color2[1] * 255;
				re->shaderRGBA[2] = ci->color2[2] * 255;
				re->shaderRGBA[3] = 255;

				le->color[0] = ci->color2[0] * 0.75;
				le->color[1] = ci->color2[1] * 0.75;
				le->color[2] = ci->color2[2] * 0.75;
				le->color[3] = 1.0f;
			}

		}
		return;
	}

	VectorCopy (start, move);
	VectorSubtract (end, start, vec);
	len = VectorNormalize (vec);
	PerpendicularVector(temp, vec);
	for (i = 0 ; i < 36; i++) {
		RotatePointAroundVector(axis[i], vec, temp, i * 10);//banshee 2.4 was 10
	}

	VectorMA(move, 20, vec, move);
	VectorScale (vec, SPACING, vec);

	skip = -1;

	j = 18;
	for (i = 0; i < len; i += SPACING) {
		if (i != skip) {
			skip = i + SPACING;
			le = CG_AllocLocalEntity();
			re = &le->refEntity;
			le->leFlags = LEF_PUFF_DONT_SCALE;
			le->leType = LE_MOVE_SCALE_FADE;
			le->startTime = cg.time;
			le->endTime = cg.time + (i>>1) + 600;
			le->lifeRate = 1.0 / (le->endTime - le->startTime);

			re->u.shaderTime = cg.time / 1000.0f;
			re->reType = RT_SPRITE;
			re->radius = 1.1f;
			re->customShader = cgs.media.railRingsShader;

			re->shaderRGBA[0] = ci->color2[0] * 255;
			re->shaderRGBA[1] = ci->color2[1] * 255;
			re->shaderRGBA[2] = ci->color2[2] * 255;
			re->shaderRGBA[3] = 255;

			le->color[0] = ci->color2[0] * 0.75;
			le->color[1] = ci->color2[1] * 0.75;
			le->color[2] = ci->color2[2] * 0.75;
			le->color[3] = 1.0f;

			le->pos.trType = TR_LINEAR;
			le->pos.trTime = cg.time;

			VectorCopy( move, move2);
			VectorMA(move2, RADIUS , axis[j], move2);
			VectorCopy(move2, le->pos.trBase);

			le->pos.trDelta[0] = axis[j][0]*6;
			le->pos.trDelta[1] = axis[j][1]*6;
			le->pos.trDelta[2] = axis[j][2]*6;
		}

		VectorAdd (move, vec, move);

		j = (j + ROTATION) % 36;
	}
}


