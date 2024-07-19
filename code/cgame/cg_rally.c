#include "cg_local.h"

void CG_Sparks( const vec3_t origin, const vec3_t normal, const vec3_t direction, const float speed )
{
	vec3_t			velocity;
	localEntity_t	*le;
	refEntity_t		*re;

	VectorCopy( direction, velocity );
	velocity[0] += crandom() * 0.5f;
	velocity[1] += crandom() * 0.5f;
	velocity[2] += random() * 0.5f;
	VectorNormalize( velocity );
	VectorScale( velocity, speed + crandom() * 10.0f, velocity );

	le = CG_AllocLocalEntity();
	re = &le->refEntity;

	le->leType = LE_FRAGMENT;
	le->leFlags = LEF_SCALE_FADE_OUT;
	le->startTime = cg.time;
	le->endTime = le->startTime + 600 + random() * 200;
	le->fadeInTime = le->startTime + ( le->endTime - le->startTime ) * 0.4f;
	le->radius = 2.0f;

	VectorCopy( origin, re->origin );
	re->u.shaderTime = cg.time / 1000.0f;
	re->reType = RT_SPRITE;
	re->rotation = 0;
	re->radius = 2.0f;
	re->customShader = cgs.media.sparkShader;
	re->shaderRGBA[0] = 0xff;
	re->shaderRGBA[1] = 0xff;
	re->shaderRGBA[2] = 0xff;
	re->shaderRGBA[3] = 0x7f;
	le->color[0] = 1.0f;
	le->color[1] = 1.0f;
	le->color[2] = 1.0f;
	le->color[3] = 0.5f;

	le->pos.trType = TR_GRAVITY;
	VectorCopy( origin, le->pos.trBase );
	VectorCopy( velocity, le->pos.trDelta );
	le->pos.trTime = cg.time;

	le->bounceFactor = 0.4f;

	le->leBounceSoundType = LEBS_BRASS;
	le->leMarkType = LEMT_NONE;
}
