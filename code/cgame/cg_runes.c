
#include "cg_local.h"

#ifdef USE_RUNES
qboolean	CG_CalcMuzzlePoint( int entityNum, vec3_t muzzle );


void CG_TellRune_f( void ) {
	//vec3_t		forward;
	//vec3_t		start;
	//vec3_t		reach;
	//trace_t trace;
	centity_t *other = NULL;

	cg.tellRune = qtrue;

	//AngleVectors( cg.snap->ps.viewangles, forward, NULL, NULL );
	//CG_CalcMuzzlePoint( cg.snap->ps.clientNum, start );
	//VectorMA(start, 64, forward, reach);

	//trap_CM_BoxTrace( &trace, reach, start, NULL, NULL, 0,  MASK_SHOT | CONTENTS_TRIGGER );
	//other = &cg_entities[ trace.entityNum ];
	if(cg.snap->ps.stats[STAT_ENTITY_POINTED]) {
		other = &cg_entities[ cg.snap->ps.stats[STAT_ENTITY_POINTED] ];
	}
	if(other && other->currentState.eType == ET_ITEM) {
		const gitem_t	*item;
		item = &bg_itemlist[ other->currentState.modelindex | (other->currentState.modelindex2 << 8) ];
		CG_CenterPrint( item->pickup_name, SCREEN_HEIGHT * 0.30, BIGCHAR_WIDTH );
	}
}


void CG_UntellRune_f( void ) {
	if ( cgs.filterKeyUpEvent ) {
		cgs.filterKeyUpEvent = qfalse;
		return;
	}

	cg.tellRune = qfalse;
}

void CG_RunesDown_f( void ) {
	cg.showRunes = qtrue;

	//CG_SetScoreCatcher( cg.showScores );
}


void CG_RunesUp_f( void ) {
	if ( cgs.filterKeyUpEvent ) {
		cgs.filterKeyUpEvent = qfalse;
		return;
	}

	if ( cg.showRunes ) {
		cg.showRunes = qfalse;
		cg.runesFadeTime = cg.time;
	}

	//CG_SetScoreCatcher( cg.showScores );
}


void hud_runes(float x, float y, float w, float h, gitem_t *rune)
{
	vec3_t angles;
	vec3_t origin;
	float rotation;
	refdef_t refdef;
	// refEntity_t		hand;
	refEntity_t ent;
	float dx = x, dy = y, dw = w, dh = h;
	float *color;
	itemInfo_t *itemInfo;
	int len;
	char firstPart[256];
	int s;
	char *split;

	itemInfo = &cg_items[ITEM_INDEX(rune)];

	VectorClear(angles);
	origin[0] = 90;
	origin[1] = 0;
	origin[2] = -10;
	rotation = (cg.time & 4095) * 120 / 4096.0;
	if (rotation <= 60)
	{
		angles[YAW] = 270 + rotation;
	}
	else
	{
		angles[YAW] = 270 + (120 - rotation);
	}

	// dont draw world if model is missing
	if (!itemInfo->models[0])
	{
		return;
	}

	memset(&ent, 0, sizeof(ent));
	AnglesToAxis(angles, ent.axis);
	// VectorSubtract(origin, weapon->weaponMidpoint, ent.origin);
	VectorCopy(origin, ent.origin);
	ent.hModel = itemInfo->models[0];
	ent.customSkin = 0;
	ent.renderfx = RF_NOSHADOW; // no stencil shadows

	CG_AdjustFrom640(&dx, &dy, &dw, &dh);
	memset(&refdef, 0, sizeof(refdef));
	refdef.rdflags = RDF_NOWORLDMODEL;
	AxisClear(refdef.viewaxis);
	refdef.fov_x = 30;
	refdef.fov_y = 30;
	refdef.x = dx;
	refdef.y = dy;
	refdef.width = dw;
	refdef.height = dh;
	refdef.time = cg.time;

	trap_R_ClearScene();

	if (cg.showRunes)
		color = colorWhite;
	else
		color = CG_FadeColor(cg.runesFadeTime, FADE_TIME);
	trap_R_SetColor(color);

	ent.customShader = itemInfo->altShader1;
	trap_R_AddRefEntityToScene(&ent);
	if (itemInfo->models[1])
	{
		ent.customShader = itemInfo->altShader2;
		trap_R_AddRefEntityToScene(&ent);
	}
	trap_R_RenderScene(&refdef);

	// draw icon just below and next to the rune
	CG_DrawString(x + 4, y + 4, va("%i", rune->giTag - RUNE_STRENGTH + 1), color, SMALLCHAR_WIDTH / 2, SMALLCHAR_HEIGHT / 2, 0, DS_SHADOW);

	CG_DrawPic(x + w - 20, y + h - 20, 16, 16, itemInfo->icon);

	len = strlen(rune->pickup_name);
	if (len >= 12)
	{
		split = Q_strrchr(rune->pickup_name, ' ');
		if (!split)
		{
			s = len;
		}
		else
		{
			s = len - strlen(split) + 1;
		}
		if (s > 12)
		{
			s = 11;
			Q_strncpyz(firstPart, rune->pickup_name, s + 1);
			firstPart[s + 1] = '\0';
		}
		else
		{
			Q_strncpyz(firstPart, rune->pickup_name, s);
			firstPart[s] = '\0';
		}
		CG_DrawString(x + 4, y + h - 20, firstPart, color, SMALLCHAR_WIDTH / 2, SMALLCHAR_HEIGHT / 2, 0, DS_SHADOW);
		CG_DrawString(x + 4, y + h - 12, &rune->pickup_name[s], color, SMALLCHAR_WIDTH / 2, SMALLCHAR_HEIGHT / 2, 0, DS_SHADOW);
	}
	else
	{
		CG_DrawString(x + 4, y + h - 12, rune->pickup_name, color, SMALLCHAR_WIDTH / 2, SMALLCHAR_HEIGHT / 2, 0, DS_SHADOW);
	}
}

qboolean CG_DrawRunesboard(void)
{
	gitem_t *item;
	float *fadeColor;
	int x, y, w, h, ix, iy;
	int n;

	if (cg.showRunes)
	{
		fadeColor = colorWhite;
	}
	else
	{
		fadeColor = CG_FadeColor(cg.runesFadeTime, FADE_TIME);
		if (!fadeColor)
		{
			return qfalse;
		}
	}

	trap_R_SetColor(fadeColor);

	w = cgs.screenXmax / 9;
	h = cgs.screenYmax / 9;
	y = (cgs.screenYmax / 2) - 4 * h - 10;

	for (iy = 0; iy < 8; iy++)
	{
		x = (cgs.screenXmax / 2) - 4 * w;
		for (ix = 0; ix < 8; ix++)
		{

			n = iy * 8 + ix;
			if (n > PW_NUM_RUNES) {
				break;
			}

			item = BG_FindItemForRune(n);
			CG_RegisterItemVisuals(ITEM_INDEX(item));

			hud_runes(x, y, w, h, item);

			// TODO: draw selection marker
			// if ( i == cg.weaponSelect ) {
			// CG_DrawPic( x-4, y-4, w+8, h+8, cgs.media.selectShader );
			//}

			x += w;
		}
		y += h;
	}

	trap_R_SetColor(NULL);
	return qtrue;
}

#endif

