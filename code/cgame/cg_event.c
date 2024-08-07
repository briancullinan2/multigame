// Copyright (C) 1999-2000 Id Software, Inc.
//
// cg_event.c -- handle entity events at snapshot or playerstate transitions

#include "cg_local.h"

// for the voice chats
#if defined(MISSIONPACK) || defined(USE_CLASSIC_HUD) // bk001205
#include "../../ui/menudef.h"
#endif
//==========================================================================

/*
===================
CG_PlaceString

Also called by scoreboard drawing
===================
*/
const char	*CG_PlaceString( int rank ) {
	static char	str[64];
	char	*s, *t;

	if ( rank & RANK_TIED_FLAG ) {
		rank &= ~RANK_TIED_FLAG;
		t = "Tied for ";
	} else {
		t = "";
	}

	if ( rank == 1 ) {
		s = S_COLOR_BLUE "1st" S_COLOR_WHITE;		// draw in blue
	} else if ( rank == 2 ) {
		s = S_COLOR_RED "2nd" S_COLOR_WHITE;		// draw in red
	} else if ( rank == 3 ) {
		s = S_COLOR_YELLOW "3rd" S_COLOR_WHITE;		// draw in yellow
	} else if ( rank == 11 ) {
		s = "11th";
	} else if ( rank == 12 ) {
		s = "12th";
	} else if ( rank == 13 ) {
		s = "13th";
	} else if ( rank % 10 == 1 ) {
		s = va("%ist", rank);
	} else if ( rank % 10 == 2 ) {
		s = va("%ind", rank);
	} else if ( rank % 10 == 3 ) {
		s = va("%ird", rank);
	} else {
		s = va("%ith", rank);
	}

	Com_sprintf( str, sizeof( str ), "%s%s", t, s );
	return str;
}


/*
=============
CG_Obituary
=============
*/
static void CG_Obituary( entityState_t *ent ) {
	int			mod;
	int			target, attacker;
	char		*message;
	char		*message2;
	const char	*targetInfo;
	const char	*attackerInfo;
	char		targetName[32];
	char		attackerName[32];
	gender_t	gender;
	clientInfo_t	*ci;
	qboolean	following;

	target = ent->otherEntityNum;
	attacker = ent->otherEntityNum2;
	mod = ent->eventParm;

	if ( target < 0 || target >= MAX_CLIENTS ) {
		CG_Error( "CG_Obituary: target out of range" );
	}
	ci = &cgs.clientinfo[target];

	if ( attacker < 0 || attacker >= MAX_CLIENTS ) {
		attacker = ENTITYNUM_WORLD;
		attackerInfo = NULL;
	} else {
		attackerInfo = CG_ConfigString( CS_PLAYERS + attacker );
	}

	targetInfo = CG_ConfigString( CS_PLAYERS + target );
	if ( !targetInfo[0] )
	{
		return;
	}
	Q_strncpyz( targetName, Info_ValueForKey( targetInfo, "n" ), sizeof(targetName) - 2);
	strcat( targetName, S_COLOR_WHITE );

	following = cg.snap->ps.pm_flags & PMF_FOLLOW;
#ifdef USE_RUNES
  cg_entities[target].rune = 0;
#endif

	message2 = "";

	// check for single client messages

	switch( mod ) {
	case MOD_SUICIDE:
		message = "suicides";
		break;
	case MOD_FALLING:
		message = "cratered";
		break;
	case MOD_CRUSH:
		message = "was squished";
		break;
	case MOD_WATER:
		message = "sank like a rock";
		break;
	case MOD_SLIME:
		message = "melted";
		break;
	case MOD_LAVA:
		message = "does a back flip into the lava";
		break;
	case MOD_TARGET_LASER:
		message = "saw the light";
		break;
#ifdef USE_MODES_DEATH
  case MOD_VOID:
    message = "fell into the void";
    break;
#endif
	case MOD_TRIGGER_HURT:
		message = "was in the wrong place";
		break;
	default:
		message = NULL;
		break;
	}

	if (attacker == target) {
		gender = ci->gender;
		switch (mod) {
#ifdef MISSIONPACK
		case MOD_KAMIKAZE:
			message = "goes out with a bang";
			break;
#endif
		case MOD_GRENADE_SPLASH:
			if ( gender == GENDER_FEMALE )
				message = "tripped on her own grenade";
			else if ( gender == GENDER_NEUTER )
				message = "tripped on its own grenade";
			else
				message = "tripped on his own grenade";
			break;
		case MOD_ROCKET_SPLASH:
			if ( gender == GENDER_FEMALE )
				message = "blew herself up";
			else if ( gender == GENDER_NEUTER )
				message = "blew itself up";
			else
				message = "blew himself up";
			break;
		case MOD_PLASMA_SPLASH:
			if ( gender == GENDER_FEMALE )
				message = "melted herself";
			else if ( gender == GENDER_NEUTER )
				message = "melted itself";
			else
				message = "melted himself";
			break;
		case MOD_BFG_SPLASH:
			message = "should have used a smaller gun";
			break;
#ifdef MISSIONPACK
		case MOD_PROXIMITY_MINE:
			if( gender == GENDER_FEMALE ) {
				message = "found her prox mine";
			} else if ( gender == GENDER_NEUTER ) {
				message = "found its prox mine";
			} else {
				message = "found his prox mine";
			}
			break;
#ifdef USE_FLAME_THROWER
    case MOD_FLAME_THROWER:
      message = "was fried by";
      break;
#endif
#endif
#ifdef USE_HEADSHOTS
    case MOD_HEADSHOT:
      gender = ci->gender;
      if(gender==GENDER_FEMALE)
      message = "got her head blown off by";
      else{
      if(gender==GENDER_NEUTER)
        message = "got its head blown off by";
      else
        message = "got his head blown off by";
      }
      break;
#endif
#ifdef USE_MODES_DEATH
		case MOD_SPECTATE:
			message = "left to spectate";
			break;
#endif

#ifdef USE_RUNES
		case MOD_RUNE_STRENGTH:
			if ( gender == GENDER_FEMALE )
				message = "was too strong for her own good";
			else if ( gender == GENDER_NEUTER )
				message = "was too strong for its own good";
			else
				message = "was too strong for his own good";
			break;
		case MOD_RUNE_BERSERK:
			if ( gender == GENDER_FEMALE )
				message = "berserked herself";
			else if ( gender == GENDER_NEUTER )
				message = "berserked itself";
			else
				message = "berserked himself";
			break;
		case MOD_RUNE_PIERCING:
			if ( gender == GENDER_FEMALE )
				message = "pierced herself";
			else if ( gender == GENDER_NEUTER )
				message = "pierced itself";
			else
				message = "pierced himself";
			break;
#endif
		default:
			if ( gender == GENDER_FEMALE )
				message = "killed herself";
			else if ( gender == GENDER_NEUTER )
				message = "killed itself";
			else
				message = "killed himself";
			break;
		}
	}

	if ( message ) {
		CG_Printf( "%s %s.\n", targetName, message);
		// switch to first killer if not following anyone
		if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR && cg_followKiller.integer ) {
			if ( !cg.followTime && attacker != cg.snap->ps.clientNum && attacker < MAX_CLIENTS ) {
				cg.followClient = attacker;
				cg.followTime = cg.time;
			}
		}
		return;
	}

	// check for kill messages from the current clientNum
	if ( attacker == cg.snap->ps.clientNum ) {
		char	*s;

#ifdef USE_HEADSHOTS
    if(mod == MOD_HEADSHOT) {
      if ( cgs.gametype < GT_TEAM ) {
        s = va("Headshot!\n\nYou fragged %s\n%s place with %i", targetName, 
		      CG_PlaceString( cg.snap->ps.persistant[PERS_RANK] + 1 ),
		      cg.snap->ps.persistant[PERS_SCORE] );
  		} else {
  			s = va("Headshot!\n\nYou fragged %s", targetName );
  		}
    } else
#endif
		if ( cgs.gametype < GT_TEAM ) {
			s = va("You fragged %s\n%s place with %i", targetName, 
				CG_PlaceString( cg.snap->ps.persistant[PERS_RANK] + 1 ),
				cg.snap->ps.persistant[PERS_SCORE] );
		} else {
			s = va("You fragged %s", targetName );
		}
#ifdef MISSIONPACK
		if (!(cg_singlePlayerActive.integer && cg_cameraOrbit.integer)) {
			CG_CenterPrint( s, SCREEN_HEIGHT * 0.30, BIGCHAR_WIDTH );
		} 
#else
		CG_CenterPrint( s, SCREEN_HEIGHT * 0.30, BIGCHAR_WIDTH );
#endif

		// print the text message as well
	}

	// check for double client messages
	if ( !attackerInfo ) {
		attacker = ENTITYNUM_WORLD;
		strcpy( attackerName, "noname" );
	} else {
		Q_strncpyz( attackerName, Info_ValueForKey( attackerInfo, "n" ), sizeof(attackerName) - 2);
		Q_CleanStr( attackerName );
		strcat( attackerName, S_COLOR_WHITE );
		// check for kill messages about the current clientNum
		if ( target == cg.snap->ps.clientNum ) {
			Q_strncpyz( cg.killerName, attackerName, sizeof( cg.killerName ) );
			// follow killer
			if ( following && cg_followKiller.integer ) {
				if ( !cg.followTime && attacker != cg.snap->ps.clientNum && attacker < MAX_CLIENTS ) {
					cg.followClient = attacker;
					cg.followTime = cg.time + 1100;
				}
			}
		}
	}

	if ( attacker != ENTITYNUM_WORLD ) {
		switch (mod) {
		case MOD_GRAPPLE:
			message = "was caught by";
			break;
		case MOD_GAUNTLET:
			message = "was pummeled by";
			break;
		case MOD_MACHINEGUN:
			message = "was machinegunned by";
			break;
		case MOD_SHOTGUN:
			message = "was gunned down by";
			break;
		case MOD_GRENADE:
			message = "ate";
			message2 = "'s grenade";
			break;
		case MOD_GRENADE_SPLASH:
			message = "was shredded by";
			message2 = "'s shrapnel";
			break;
		case MOD_ROCKET:
			message = "ate";
			message2 = "'s rocket";
			break;
		case MOD_ROCKET_SPLASH:
			message = "almost dodged";
			message2 = "'s rocket";
			break;
		case MOD_PLASMA:
			message = "was melted by";
			message2 = "'s plasmagun";
			break;
		case MOD_PLASMA_SPLASH:
			message = "was melted by";
			message2 = "'s plasmagun";
			break;
		case MOD_RAILGUN:
			message = "was railed by";
			break;
#ifdef USE_LV_DISCHARGE
// The SARACEN's Lightning Discharge - START
    // Classic Quake style obituary - the original and the best!!!
		case MOD_LIGHTNING:
			message = "was shafted by";
			break;
		case MOD_LV_DISCHARGE:
			message = "was discharged by";
			break;
// The SARACEN's Lightning Discharge - END
#else
		case MOD_LIGHTNING:
			message = "was electrocuted by";
			break;
#endif
		case MOD_BFG:
		case MOD_BFG_SPLASH:
			message = "was blasted by";
			message2 = "'s BFG";
			break;
#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS)
		case MOD_NAIL:
			message = "was nailed by";
			break;
		case MOD_CHAINGUN:
			message = "got lead poisoning from";
			message2 = "'s Chaingun";
			break;
		case MOD_PROXIMITY_MINE:
			message = "was too close to";
			message2 = "'s Prox Mine";
			break;
		case MOD_KAMIKAZE:
			message = "falls to";
			message2 = "'s Kamikaze blast";
			break;
		case MOD_JUICED:
			message = "was juiced by";
			break;
#endif
#ifdef USE_MODES_DEATH
    case MOD_FROM_GRAVE:
      message = "was killed by";
      message2 = " from the grave";
      break;
    case MOD_RING_OUT:
      message = "was forced out of the ring by";
      break;
#endif
		case MOD_TELEFRAG:
			message = "tried to invade";
			message2 = "'s personal space";
			break;
#ifdef USE_RUNES
		case MOD_RUNE_PIERCING:
			message = "was pierced by";
			break;
		case MOD_RUNE_DIVINITY:
			message = "was struck by divinity from";
			break;
#endif
		default:
			message = "was killed by";
			break;
		}

		if ( message ) {
			CG_Printf( "%s %s %s%s\n", targetName, message, attackerName, message2 );
			// switch to first killer if not following anyone
			if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR && cg_followKiller.integer ) {
				if ( !cg.followTime && attacker != cg.snap->ps.clientNum && attacker < MAX_CLIENTS ) {
					cg.followClient = attacker;
					cg.followTime = cg.time;
				}
			}
			return;
		}
	}

	// we don't know what it was
	CG_Printf( "%s "S_COLOR_STRIP"died.\n", targetName );
}
//==========================================================================


/*
===============
CG_UseItem
===============
*/
#ifdef USE_ADVANCED_ITEMS
static void CG_UseItem( centity_t *cent, int itemNum ) 
#else
static void CG_UseItem( centity_t *cent ) 
#endif
{
	clientInfo_t *ci;
#ifdef USE_ADVANCED_ITEMS
	int			clientNum;
#else
	int			itemNum, clientNum;
#endif
	gitem_t		*item;
	entityState_t *es;

	es = &cent->currentState;
	
#ifndef USE_ADVANCED_ITEMS
	itemNum = (es->event & ~EV_EVENT_BITS) - EV_USE_ITEM0;
	if ( itemNum < 0 || itemNum > HI_NUM_HOLDABLE ) {
		itemNum = 0;
	}
#else
	itemNum = es->eventParm;
#endif

	// print a message if the local player
	if ( es->number == cg.snap->ps.clientNum ) {
		if ( !itemNum ) {
			CG_CenterPrint( "No item to use", SCREEN_HEIGHT * 0.30, BIGCHAR_WIDTH );
		} else {
#ifdef USE_ADVANCED_ITEMS
			item = BG_FindItemForPowerup( itemNum );
#else
			item = BG_FindItemForHoldable( itemNum );
#endif
			if(!item) {
				CG_CenterPrint( va("Use %i", itemNum), SCREEN_HEIGHT * 0.30, BIGCHAR_WIDTH );
			} else
			CG_CenterPrint( va("Use %s", item->pickup_name), SCREEN_HEIGHT * 0.30, BIGCHAR_WIDTH );
		}
	}

	switch ( itemNum ) {
	default:
#ifndef USE_ADVANCED_ITEMS
	case HI_NONE:
#endif
		trap_S_StartSound (NULL, es->number, CHAN_BODY, cgs.media.useNothingSound );
		break;

	case HI_TELEPORTER:
		break;

	case HI_MEDKIT:
		clientNum = cent->currentState.clientNum;
		if ( clientNum >= 0 && clientNum < MAX_CLIENTS ) {
			ci = &cgs.clientinfo[ clientNum ];
			ci->medkitUsageTime = cg.time;
		}
		trap_S_StartSound (NULL, es->number, CHAN_BODY, cgs.media.medkitSound );
		break;

#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS)
	case HI_KAMIKAZE:
		break;

	case HI_PORTAL:
		break;
	case HI_INVULNERABILITY:
		trap_S_StartSound (NULL, es->number, CHAN_BODY, cgs.media.useInvulnerabilitySound );
		break;
#endif
#if defined(USE_ADVANCED_ITEMS) || defined(USE_RUNES)
	case PW_SPECIAL_ABILITY:
		if((es->powerups & 0xFF) == RUNE_SHIELD || (es->powerups >> 8) == RUNE_SHIELD) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY, cgs.media.useInvulnerabilitySound );
		}
		break;
#endif
	}
}


/*
================
CG_ItemPickup

A new item was picked up this frame
================
*/
#ifdef USE_WEAPON_ORDER
int RateWeapon (int weapon);
static void CG_ItemPickup( int itemNum, qboolean alreadyHad )
#else
static void CG_ItemPickup( int itemNum ) 
#endif
{
	static int oldItem = -1;
	
	cg.itemPickup = itemNum;
	cg.itemPickupTime = cg.time;
	cg.itemPickupBlendTime = cg.time;

	if ( oldItem != itemNum )
		cg.itemPickupCount = 1;
	else
		cg.itemPickupCount++;

	oldItem = itemNum;
	
	// see if it should be the grabbed weapon
	if ( bg_itemlist[itemNum].giType == IT_WEAPON ) {
		// select it immediately
		if ( cg_autoswitch.integer && bg_itemlist[itemNum].giTag != WP_MACHINEGUN ) {
#ifdef USE_WEAPON_ORDER
      if(cg_autoswitch.integer == 2 && alreadyHad) {
        if(RateWeapon( bg_itemlist[itemNum].giTag) < RateWeapon( cg.weaponSelect ))
          return;
      }
#endif
			cg.weaponSelectTime = cg.time;
#ifdef USE_ADVANCED_WEAPONS
			cg.weaponClass = floor(bg_itemlist[itemNum].giTag / WP_MAX_WEAPONS);
#endif
			cg.weaponSelect = bg_itemlist[itemNum].giTag;

		}
	}

}


/*
================
CG_WaterLevel

Returns waterlevel for entity origin
================
*/
int CG_WaterLevel(centity_t *cent) {
	vec3_t point;
	int contents, sample1, sample2, anim, waterlevel;
	int viewheight;

	anim = cent->currentState.legsAnim & ~ANIM_TOGGLEBIT;

	if ( anim == LEGS_WALKCR || anim == LEGS_IDLECR ) {
		viewheight = CROUCH_VIEWHEIGHT;
	} else {
		viewheight = DEFAULT_VIEWHEIGHT;
	}

	//
	// get waterlevel, accounting for ducking
	//
	waterlevel = 0;

	point[0] = cent->lerpOrigin[0];
	point[1] = cent->lerpOrigin[1];
	point[2] = cent->lerpOrigin[2] + MINS_Z + 1;
	contents = CG_PointContents(point, -1);

	if ( contents & MASK_WATER ) {
		sample2 = viewheight - MINS_Z;
		sample1 = sample2 / 2;
		waterlevel = 1;
		point[2] = cent->lerpOrigin[2] + MINS_Z + sample1;
		contents = CG_PointContents(point, -1);

		if (contents & MASK_WATER) {
			waterlevel = 2;
			point[2] = cent->lerpOrigin[2] + MINS_Z + sample2;
			contents = CG_PointContents(point, -1);

			if (contents & MASK_WATER) {
				waterlevel = 3;
			}
		}
	}

	return waterlevel;
}

void CG_OldRailTrail (clientInfo_t *ci, vec3_t start, vec3_t end);



/*
================
CG_PainEvent

Also called by playerstate transition
================
*/
void CG_PainEvent( centity_t *cent, int health ) {
	const char *snd;

	// don't do more than two pain sounds a second
	if ( cg.time - cent->pe.painTime < 500 ) {
		cent->pe.painIgnore = qfalse;
		return;
	}

	if ( cent->pe.painIgnore ) {
		cent->pe.painIgnore = qfalse;
		return;
	}

	if ( health < 25 ) {
		snd = "*pain25_1.wav";
	} else if ( health < 50 ) {
		snd = "*pain50_1.wav";
	} else if ( health < 75 ) {
		snd = "*pain75_1.wav";
	} else {
		snd = "*pain100_1.wav";
	}

	// play a gurp sound instead of a normal pain sound
	if (CG_WaterLevel(cent) == 3) {
		if (rand()&1) {
			trap_S_StartSound(NULL, cent->currentState.number, CHAN_VOICE, CG_CustomSound(cent->currentState.number, "sound/player/gurp1.wav"));
		} else {
			trap_S_StartSound(NULL, cent->currentState.number, CHAN_VOICE, CG_CustomSound(cent->currentState.number, "sound/player/gurp2.wav"));
		}
	} else {
		trap_S_StartSound(NULL, cent->currentState.number, CHAN_VOICE, CG_CustomSound(cent->currentState.number, snd));
	}

	// save pain time for programitic twitch animation
	cent->pe.painTime = cg.time;
	cent->pe.painDirection ^= 1;
}


#ifdef USE_HEADSHOTS
void CG_GibPlayerHeadshot( vec3_t playerOrigin );
#endif
#ifdef USE_LV_DISCHARGE
void CG_Lightning_Discharge (vec3_t origin, int msec);
#endif

/*
==============
CG_EntityEvent

An entity has an event value
also called by CG_CheckPlayerstateEvents
==============
*/
void CG_EntityEvent( centity_t *cent, vec3_t position, int entityNum ) {
	entityState_t	*es;
	entity_event_t	event;
	vec3_t			dir;
	const char		*s;
	int				clientNum;
	clientInfo_t	*ci;
	vec3_t			vec;
	float			fovOffset;
	centity_t		*ce;

	es = &cent->currentState;
	event = es->event & ~EV_EVENT_BITS;

	if ( (unsigned) event >= EV_MAX ) {
		CG_Error( "Unknown event 2: %i > %i", event, EV_MAX );
		return;
	}

	if ( cg_debugEvents.integer ) {
		CG_Printf( "ent:%3i  event:%3i %s", es->number, event, eventnames[ event ] );
	}

	if ( !event ) {
		return;
	}

	clientNum = es->clientNum;
	if ( (unsigned) clientNum >= MAX_CLIENTS ) {
		clientNum = 0;
	}
	ci = &cgs.clientinfo[ clientNum ];

	switch ( event ) {
	//
	// movement generated events
	//
	case EV_FOOTSTEP:
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY, 
				cgs.media.footsteps[ ci->footsteps ][rand()&3] );
		}
		break;

	case EV_FOOTSTEP_METAL:
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY, 
				cgs.media.footsteps[ FOOTSTEP_METAL ][rand()&3] );
		}
		break;

	case EV_FOOTSPLASH:
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY, 
				cgs.media.footsteps[ FOOTSTEP_SPLASH ][rand()&3] );
		}
		break;

	case EV_FOOTWADE:
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY, 
				cgs.media.footsteps[ FOOTSTEP_SPLASH ][rand()&3] );
		}
		break;

	case EV_SWIM:
		if (cg_footsteps.integer) {
			trap_S_StartSound (NULL, es->number, CHAN_BODY, 
				cgs.media.footsteps[ FOOTSTEP_SPLASH ][rand()&3] );
		}
		break;

	case EV_FALL_SHORT:
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.landSound );
		if ( clientNum == cg.predictedPlayerState.clientNum ) {
			// smooth landing z changes
			cg.landChange = -8;
			cg.landTime = cg.time;
		}
		break;

	case EV_FALL_MEDIUM:
		// use normal pain sound
		trap_S_StartSound( NULL, es->number, CHAN_VOICE, CG_CustomSound( es->number, "*pain100_1.wav" ) );
		cent->pe.painIgnore = qtrue;
		cent->pe.painTime = cg.time;	// don't play a pain sound right after this
		if ( clientNum == cg.predictedPlayerState.clientNum ) {
			// smooth landing z changes
			cg.landChange = -16;
			cg.landTime = cg.time;
		}
		break;

	case EV_FALL_FAR:
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, CG_CustomSound( es->number, "*fall1.wav" ) );
		cent->pe.painIgnore = qtrue;
		cent->pe.painTime = cg.time;	// don't play a pain sound right after this
		if ( clientNum == cg.predictedPlayerState.clientNum ) {
			// smooth landing z changes
			cg.landChange = -24;
			cg.landTime = cg.time;
		}
		break;

	case EV_STEP_4:
	case EV_STEP_8:
	case EV_STEP_12:
	case EV_STEP_16:		// smooth out step up transitions
	{
		float	oldStep;
		int		delta;
		int		step;

		if ( clientNum != cg.predictedPlayerState.clientNum ) {
			break;
		}
		// if we are interpolating, we don't need to smooth steps
		if ( cg.demoPlayback || (cg.snap->ps.pm_flags & PMF_FOLLOW) ||
			cg_nopredict.integer || cgs.synchronousClients ) {
			break;
		}
		// check for stepping up before a previous step is completed
		delta = cg.time - cg.stepTime;
		if (delta < STEP_TIME) {
			oldStep = cg.stepChange * (STEP_TIME - delta) / STEP_TIME;
		} else {
			oldStep = 0;
		}

		// add this amount
		step = 4 * (event - EV_STEP_4 + 1 );
		cg.stepChange = oldStep + step;
		if ( cg.stepChange > MAX_STEP_CHANGE ) {
			cg.stepChange = MAX_STEP_CHANGE;
		}
		cg.stepTime = cg.time;
		break;
	}

	case EV_JUMP_PAD:
//		CG_Printf( "EV_JUMP_PAD w/effect #%i\n", es->eventParm );
		{
			vec3_t			up = {0, 0, 1};


			CG_SmokePuff( cent->lerpOrigin, up, 
						  32, 
						  1, 1, 1, 0.33f,
						  1000, 
						  cg.time, 0,
						  LEF_PUFF_DONT_SCALE, 
						  cgs.media.smokePuffShader );
		}

		// boing sound at origin, jump sound on player
		trap_S_StartSound ( cent->lerpOrigin, -1, CHAN_VOICE, cgs.media.jumpPadSound );
		trap_S_StartSound (NULL, es->number, CHAN_VOICE, CG_CustomSound( es->number, "*jump1.wav" ) );
		break;

	case EV_JUMP:
		// pain event with fast sequential jump just creates sound distortion
		if ( cg.time - cent->pe.painTime > 50 )
			trap_S_StartSound (NULL, es->number, CHAN_VOICE, CG_CustomSound( es->number, "*jump1.wav" ) );
		break;

	case EV_TAUNT:
		trap_S_StartSound (NULL, es->number, CHAN_VOICE, CG_CustomSound( es->number, "*taunt.wav" ) );
		break;

#ifdef MISSIONPACK
	case EV_TAUNT_YES:
		CG_VoiceChatLocal(SAY_TEAM, qfalse, es->number, COLOR_CYAN, VOICECHAT_YES);
		break;

	case EV_TAUNT_NO:
		CG_VoiceChatLocal(SAY_TEAM, qfalse, es->number, COLOR_CYAN, VOICECHAT_NO);
		break;

	case EV_TAUNT_FOLLOWME:
		CG_VoiceChatLocal(SAY_TEAM, qfalse, es->number, COLOR_CYAN, VOICECHAT_FOLLOWME);
		break;

	case EV_TAUNT_GETFLAG:
		CG_VoiceChatLocal(SAY_TEAM, qfalse, es->number, COLOR_CYAN, VOICECHAT_ONGETFLAG);
		break;

	case EV_TAUNT_GUARDBASE:
		CG_VoiceChatLocal(SAY_TEAM, qfalse, es->number, COLOR_CYAN, VOICECHAT_ONDEFENSE);
		break;

	case EV_TAUNT_PATROL:
		CG_VoiceChatLocal(SAY_TEAM, qfalse, es->number, COLOR_CYAN, VOICECHAT_ONPATROL);
		break;
#endif
	case EV_WATER_TOUCH:
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.watrInSound );
		break;

	case EV_WATER_LEAVE:
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.watrOutSound );
		break;

	case EV_WATER_UNDER:
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.watrUnSound );
		break;

	case EV_WATER_CLEAR:
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, CG_CustomSound( es->number, "*gasp.wav" ) );
		break;

#ifdef USE_WEAPON_ORDER
  case EV_ITEM_PICKUP2:
#endif
	case EV_ITEM_PICKUP:
		{
			gitem_t	*item;
			int		index;

			index = es->eventParm;		// player predicted

			if ( index < 1 || index >= bg_numItems ) {
				break;
			}

			if ( entityNum >= 0 ) {
				// our predicted entity
				ce = cg_entities + entityNum;
				if ( ce->delaySpawn > cg.time && ce->delaySpawnPlayed ) {
					break; // delay item pickup
				}
			} else {
				ce = NULL;
			}

			item = &bg_itemlist[ index ];

			// powerups and team items will have a separate global sound, this one
			// will be played at prediction time
			if ( item->giType == IT_POWERUP || item->giType == IT_TEAM) {
				trap_S_StartSound (NULL, es->number, CHAN_AUTO,	cgs.media.n_healthSound );
			} else if (item->giType == IT_PERSISTANT_POWERUP) {
#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS)
				switch (item->giTag ) {
					case PW_SCOUT:
						trap_S_StartSound (NULL, es->number, CHAN_AUTO,	cgs.media.scoutSound );
					break;
					case PW_GUARD:
						trap_S_StartSound (NULL, es->number, CHAN_AUTO,	cgs.media.guardSound );
					break;
					case PW_DOUBLER:
						trap_S_StartSound (NULL, es->number, CHAN_AUTO,	cgs.media.doublerSound );
					break;
					case PW_AMMOREGEN:
						trap_S_StartSound (NULL, es->number, CHAN_AUTO,	cgs.media.ammoregenSound );
					break;
				}
#endif
			} else {
				trap_S_StartSound (NULL, es->number, CHAN_AUTO,	trap_S_RegisterSound( item->pickup_sound, qfalse ) );
			}

#ifdef USE_RUNES
        if(item->giTag >= RUNE_STRENGTH && item->giTag <= RUNE_LITHIUM) {
          cg_entities[es->number].rune = item->giTag;
        }
#endif
			// show icon and name on status bar
			if ( es->number == cg.snap->ps.clientNum ) {
#ifdef USE_WEAPON_ORDER
				CG_ItemPickup( index, event == EV_ITEM_PICKUP2 );
#else
        CG_ItemPickup( index );
#endif
			}

			if ( ce ) {
				ce->delaySpawnPlayed = qtrue;
			}
		}
		break;

	case EV_GLOBAL_ITEM_PICKUP:
		{
			gitem_t	*item;
			int		index;

			index = es->eventParm;		// player predicted

			if ( index < 1 || index >= bg_numItems ) {
				break;
			}

			if ( entityNum >= 0 ) {
				// our predicted entity
				ce = cg_entities + entityNum;
				if ( ce->delaySpawn > cg.time && ce->delaySpawnPlayed ) {
					break;
				}
			} else {
				ce = NULL;
			}

			item = &bg_itemlist[ index ];
			// powerup pickups are global
			if( item->pickup_sound ) {
				trap_S_StartSound (NULL, cg.snap->ps.clientNum, CHAN_AUTO, trap_S_RegisterSound( item->pickup_sound, qfalse ) );
			}

			// show icon and name on status bar
			if ( es->number == cg.snap->ps.clientNum ) {
        if(item->giTag == PW_HASTE
#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS)
					|| item->giTag == PW_SCOUT
#endif
#ifdef USE_RUNES
          || item->giTag == RUNE_HASTE
#endif
        ) {
#ifdef USE_PHYSICS_VARS
          cg.predictedPlayerState.speed *= cg_hasteFactor.value;
#else
          cg.predictedPlayerState.speed *= 1.3f;
#endif
        }
#ifdef USE_ADVANCED_ITEMS
				if(item->giTag == PW_FLASH) {
          cg.predictedPlayerState.speed *= 2.6f;
				}
#endif

#ifdef USE_WEAPON_ORDER
				CG_ItemPickup( index, qfalse );
#else
        CG_ItemPickup( index );
#endif
			}

			if ( ce ) {
				ce->delaySpawnPlayed = qtrue;
			}
		}
		break;

	//
	// weapon events
	//
	case EV_NOAMMO:
//		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.noAmmoSound );
		if ( es->number == cg.snap->ps.clientNum ) {
			CG_OutOfAmmoChange();
		}
		break;

	case EV_CHANGE_WEAPON:
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.selectSound );
		break;

#ifdef USE_ALT_FIRE
  case EV_ALTFIRE_WEAPON:
#ifdef USE_GRAPPLE
    if(cg_altGrapple.integer) {
      // don't play firing animation
		break;
	}
#endif
#ifdef USE_PORTALS
    if(cg_altPortal.integer) {
      break;
    }
#endif
#endif
	case EV_FIRE_WEAPON:
		CG_FireWeapon( cent );
		break;

	case EV_USE_ITEM0:
	case EV_USE_ITEM1:
	case EV_USE_ITEM2:
	case EV_USE_ITEM3:
	case EV_USE_ITEM4:
	case EV_USE_ITEM5:
	case EV_USE_ITEM6:
	case EV_USE_ITEM7:
	case EV_USE_ITEM8:
	case EV_USE_ITEM9:
	case EV_USE_ITEM10:
	case EV_USE_ITEM11:
	case EV_USE_ITEM12:
	case EV_USE_ITEM13:
	case EV_USE_ITEM14:
	case EV_USE_ITEM15:
#ifdef USE_ADVANCED_ITEMS
		CG_UseItem( cent, es->eventParm );
#else
		CG_UseItem( cent );
#endif
		break;

	//=================================================================

#ifdef USE_SINGLEPLAYER // entity
	case EV_PLAYERSTOP:
		player_stop = cg.time + (es->eventParm & 0x7F) * 2000;
		if (es->eventParm & 0x80) black_bars = 1;
		break;
#endif

	//
	// other events
	//
	case EV_PLAYER_TELEPORT_IN:
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.teleInSound );
		CG_SpawnEffect( position);
		break;

	case EV_PLAYER_TELEPORT_OUT:
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.teleOutSound );
		CG_SpawnEffect(  position);
		break;

	case EV_ITEM_POP:
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.respawnSound );
		break;

	case EV_ITEM_RESPAWN:
		cent->miscTime = cg.time;	// scale up from this
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.respawnSound );
		break;

	case EV_GRENADE_BOUNCE:
		if ( rand() & 1 ) {
			trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.hgrenb1aSound );
		} else {
			trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.hgrenb2aSound );
		}
		break;

#ifdef MISSIONPACK
	case EV_PROXIMITY_MINE_STICK:
		if( es->eventParm & SURF_FLESH ) {
			trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.wstbimplSound );
		} else 	if( es->eventParm & SURF_METALSTEPS ) {
			trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.wstbimpmSound );
		} else {
			trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.wstbimpdSound );
		}
		break;

	case EV_PROXIMITY_MINE_TRIGGER:
		trap_S_StartSound (NULL, es->number, CHAN_AUTO, cgs.media.wstbactvSound );
		break;

#endif
#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS) || defined(USE_ADVANCED_ITEMS) || defined(USE_RUNES)

	case EV_KAMIKAZE:
		CG_KamikazeEffect( cent->lerpOrigin );
		break;

	case EV_OBELISKEXPLODE:
		CG_ObeliskExplode( cent->lerpOrigin, es->eventParm );
		break;

	case EV_OBELISKPAIN:
		CG_ObeliskPain( cent->lerpOrigin );
		break;

	case EV_INVUL_IMPACT:
		CG_InvulnerabilityImpact( cent->lerpOrigin, cent->currentState.angles );
		break;

	case EV_JUICED:
		CG_InvulnerabilityJuiced( cent->lerpOrigin );
		break;

	case EV_LIGHTNINGBOLT:
		CG_LightningBoltBeam(es->origin2, es->pos.trBase);
		break;
#endif

	case EV_SCOREPLUM:
		CG_ScorePlum( cent->currentState.otherEntityNum, cent->lerpOrigin, cent->currentState.time );
		break;

#ifdef USE_RPG_STATS
	case EV_HEALTHPLUM:
		if(cent->currentState.time) {
			cgs.clientinfo[cent->currentState.otherEntityNum].health = cent->currentState.time;
			cgs.clientinfo[cent->currentState.otherEntityNum].powerups = cent->currentState.powerups;
			cg_entities[cent->currentState.otherEntityNum].currentState.powerups = cent->currentState.powerups;
			if(cent->currentState.otherEntityNum == cg.snap->ps.clientNum) {
				cg.snap->entities[cg.snap->ps.clientNum].powerups = cent->currentState.powerups;
			}
		}
		break;
#endif


#ifdef USE_DAMAGE_PLUMS
	case EV_DAMAGEPLUM:
#ifdef USE_RUNES
		if((cg_entities[cent->currentState.otherEntityNum].currentState.powerups & 0xFF) == RUNE_CLOAK
			|| (cg_entities[cent->currentState.otherEntityNum].currentState.powerups >> 8) == RUNE_CLOAK) {
			cg_entities[cent->currentState.otherEntityNum].cloakBlinkTime = cg.time;
		}

		// don't actually show the plum on invisible players
		if(cent->currentState.otherEntityNum != cg.snap->ps.clientNum)
#endif
		if(cent->currentState.time && cent->currentState.otherEntityNum2 == cg.snap->ps.clientNum) {
			CG_DamagePlum( cent->currentState.otherEntityNum, cent->lerpOrigin, cent->currentState.time );
		}
		break;
#endif

	//
	// missile impacts
	//
	case EV_MISSILE_HIT:
		ByteToDir( es->eventParm, dir );
		CG_MissileHitPlayer( es->weapon, position, dir, es->otherEntityNum );
		break;

	case EV_MISSILE_MISS:
		ByteToDir( es->eventParm, dir );
		CG_MissileHitWall( es->weapon, 0, position, dir, IMPACTSOUND_DEFAULT );
		break;

	case EV_MISSILE_MISS_METAL:
		ByteToDir( es->eventParm, dir );
		CG_MissileHitWall( es->weapon, 0, position, dir, IMPACTSOUND_METAL );
		break;

	case EV_RAILTRAIL:
		cent->currentState.weapon = WP_RAILGUN;

		if ( cent->currentState.clientNum == cg.snap->ps.clientNum && !cg_thirdPerson.integer ) 
		{
			VectorCopy( cg.refdef.vieworg, vec );
			fovOffset = -0.2f * ( cgs.fov - 90.0f );

			// 13.5, -5.5, -6.0
#ifdef USE_WEAPON_CENTER
      if(cg_gunCenter.integer) {
        VectorMA( vec, cg_gun_x.value + 13.5f, cg.refdef.viewaxis[0], vec );
  			VectorMA( vec, (cg_gun_y.value + 5*cg_gunCenter.value) - 5.5f, cg.refdef.viewaxis[1], vec );
  			VectorMA( vec, cg_gun_z.value + fovOffset - 6.0f, cg.refdef.viewaxis[2], vec );
      } else
#endif
      {
        VectorMA( vec, cg_gun_x.value + 13.5f, cg.refdef.viewaxis[0], vec );
  			VectorMA( vec, cg_gun_y.value - 5.5f, cg.refdef.viewaxis[1], vec );
  			VectorMA( vec, cg_gun_z.value + fovOffset - 6.0f, cg.refdef.viewaxis[2], vec );
      }
		}
		else
			VectorCopy( es->origin2, vec );

		// if the end was on a nomark surface, don't make an explosion
		if(cg_oldRail.integer > 0) {
			CG_OldRailTrail( ci, vec, es->pos.trBase );
		} else {
			CG_RailTrail( ci, vec, es->pos.trBase );
		}

		if ( es->eventParm != 255 ) {
			ByteToDir( es->eventParm, dir );
			CG_MissileHitWall( es->weapon, es->clientNum, position, dir, IMPACTSOUND_DEFAULT );
		}
		break;

	case EV_BULLET_HIT_WALL:
		ByteToDir( es->eventParm, dir );
		CG_Bullet( es->pos.trBase, es->otherEntityNum, dir, qfalse, ENTITYNUM_WORLD );
		break;

	case EV_BULLET_HIT_FLESH:
		CG_Bullet( es->pos.trBase, es->otherEntityNum, dir, qtrue, es->eventParm );
		break;

	case EV_SHOTGUN:
		CG_ShotgunFire( es );
		break;

#ifdef USE_LV_DISCHARGE
// The SARACEN's Lightning Discharge - START
	case EV_LV_DISCHARGE:
		CG_Lightning_Discharge (position, es->eventParm);	// eventParm is duration/size
		break;
// The SARACEN's Lightning Discharge - END
#endif

	case EV_GENERAL_SOUND:
		if ( cgs.gameSounds[ es->eventParm ] ) {
			trap_S_StartSound (NULL, es->number, CHAN_VOICE, cgs.gameSounds[ es->eventParm ] );
		} else {
			s = CG_ConfigString( CS_SOUNDS + es->eventParm );
			trap_S_StartSound (NULL, es->number, CHAN_VOICE, CG_CustomSound( es->number, s ) );
		}
		break;

	case EV_GLOBAL_SOUND:	// play from the player's head so it never diminishes
		if ( cgs.gameSounds[ es->eventParm ] ) {
			trap_S_StartSound (NULL, cg.snap->ps.clientNum, CHAN_AUTO, cgs.gameSounds[ es->eventParm ] );
		} else {
			s = CG_ConfigString( CS_SOUNDS + es->eventParm );
			trap_S_StartSound (NULL, cg.snap->ps.clientNum, CHAN_AUTO, CG_CustomSound( es->number, s ) );
		}
		break;

	case EV_GLOBAL_TEAM_SOUND:	// play from the player's head so it never diminishes
		{
			switch( es->eventParm ) {
				case GTS_RED_CAPTURE: // CTF: red team captured the blue flag, 1FCTF: red team captured the neutral flag
					if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_RED )
						CG_AddBufferedSound( cgs.media.captureYourTeamSound );
					else
						CG_AddBufferedSound( cgs.media.captureOpponentSound );
					break;
				case GTS_BLUE_CAPTURE: // CTF: blue team captured the red flag, 1FCTF: blue team captured the neutral flag
					if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_BLUE )
						CG_AddBufferedSound( cgs.media.captureYourTeamSound );
					else
						CG_AddBufferedSound( cgs.media.captureOpponentSound );
					break;
				case GTS_RED_RETURN: // CTF: blue flag returned, 1FCTF: never used
					if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_RED )
						CG_AddBufferedSound( cgs.media.returnYourTeamSound );
					else
						CG_AddBufferedSound( cgs.media.returnOpponentSound );
					//
					CG_AddBufferedSound( cgs.media.blueFlagReturnedSound );
					break;
				case GTS_BLUE_RETURN: // CTF red flag returned, 1FCTF: neutral flag returned
					if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_BLUE )
						CG_AddBufferedSound( cgs.media.returnYourTeamSound );
					else
						CG_AddBufferedSound( cgs.media.returnOpponentSound );
					//
					CG_AddBufferedSound( cgs.media.redFlagReturnedSound );
					break;

				case GTS_RED_TAKEN: // CTF: red team took blue flag, 1FCTF: blue team took the neutral flag
					// if this player picked up the flag then a sound is played in CG_CheckLocalSounds
#ifdef USE_ADVANCED_ITEMS
					if (cg.inventory[PW_BLUEFLAG] || cg.inventory[PW_NEUTRALFLAG]) {
					}
#else
					if (cg.snap->ps.powerups[PW_BLUEFLAG] || cg.snap->ps.powerups[PW_NEUTRALFLAG]) {
					}
#endif
					else {
						if (cg.snap->ps.persistant[PERS_TEAM] == TEAM_BLUE) {
#ifdef MISSIONPACK
							if (cgs.gametype == GT_1FCTF) 
								CG_AddBufferedSound( cgs.media.yourTeamTookTheFlagSound );
							else
#endif
						 	CG_AddBufferedSound( cgs.media.enemyTookYourFlagSound );
						}
						else if (cg.snap->ps.persistant[PERS_TEAM] == TEAM_RED) {
#ifdef MISSIONPACK
							if (cgs.gametype == GT_1FCTF)
								CG_AddBufferedSound( cgs.media.enemyTookTheFlagSound );
							else
#endif
 							CG_AddBufferedSound( cgs.media.yourTeamTookEnemyFlagSound );
						}
					}
					break;
				case GTS_BLUE_TAKEN: // CTF: blue team took the red flag, 1FCTF red team took the neutral flag
					// if this player picked up the flag then a sound is played in CG_CheckLocalSounds
#ifdef USE_ADVANCED_ITEMS
					if (cg.inventory[PW_REDFLAG] || cg.inventory[PW_NEUTRALFLAG]) {
					}
#else
					if (cg.snap->ps.powerups[PW_REDFLAG] || cg.snap->ps.powerups[PW_NEUTRALFLAG]) {
					}
#endif
					else {
						if (cg.snap->ps.persistant[PERS_TEAM] == TEAM_RED) {
#ifdef MISSIONPACK
							if (cgs.gametype == GT_1FCTF)
								CG_AddBufferedSound( cgs.media.yourTeamTookTheFlagSound );
							else
#endif
							CG_AddBufferedSound( cgs.media.enemyTookYourFlagSound );
						}
						else if (cg.snap->ps.persistant[PERS_TEAM] == TEAM_BLUE) {
#ifdef MISSIONPACK
							if (cgs.gametype == GT_1FCTF)
								CG_AddBufferedSound( cgs.media.enemyTookTheFlagSound );
							else
#endif
							CG_AddBufferedSound( cgs.media.yourTeamTookEnemyFlagSound );
						}
					}
					break;
#ifdef MISSIONPACK
				case GTS_REDOBELISK_ATTACKED: // Overload: red obelisk is being attacked
					if (cg.snap->ps.persistant[PERS_TEAM] == TEAM_RED) {
						CG_AddBufferedSound( cgs.media.yourBaseIsUnderAttackSound );
					}
					break;
				case GTS_BLUEOBELISK_ATTACKED: // Overload: blue obelisk is being attacked
					if (cg.snap->ps.persistant[PERS_TEAM] == TEAM_BLUE) {
						CG_AddBufferedSound( cgs.media.yourBaseIsUnderAttackSound );
					}
					break;
#endif

				case GTS_REDTEAM_SCORED:
					CG_AddBufferedSound(cgs.media.redScoredSound);
					break;
				case GTS_BLUETEAM_SCORED:
					CG_AddBufferedSound(cgs.media.blueScoredSound);
					break;
				case GTS_REDTEAM_TOOK_LEAD:
					CG_AddBufferedSound(cgs.media.redLeadsSound);
					break;
				case GTS_BLUETEAM_TOOK_LEAD:
					CG_AddBufferedSound(cgs.media.blueLeadsSound);
					break;
				case GTS_TEAMS_ARE_TIED:
					CG_AddBufferedSound( cgs.media.teamsTiedSound );
					break;
#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS)
				case GTS_KAMIKAZE:
					trap_S_StartLocalSound(cgs.media.kamikazeFarSound, CHAN_ANNOUNCER);
					break;
#endif
				default:
					break;
			}
			break;
		}

	case EV_PAIN:
		// local player sounds are triggered in CG_CheckLocalSounds,
		// so ignore events on the player
		if ( cent->currentState.number != cg.snap->ps.clientNum ) {
			CG_PainEvent( cent, es->eventParm );
		}
		break;

	case EV_DEATH1:
	case EV_DEATH2:
	case EV_DEATH3:
		if ( CG_WaterLevel(cent) == 3 ) {
			trap_S_StartSound( NULL, es->number, CHAN_VOICE, CG_CustomSound(es->number, "*drown.wav") );
		} else {
			trap_S_StartSound( NULL, es->number, CHAN_VOICE, CG_CustomSound(es->number, va("*death%i.wav", event - EV_DEATH1 + 1)) );
		}

		break;

	case EV_OBITUARY:
		CG_Obituary( es );
		break;

	//
	// powerup events
	//
	case EV_POWERUP_QUAD:
		if ( es->number == cg.snap->ps.clientNum ) {
			cg.powerupActive = PW_QUAD;
			cg.powerupTime = cg.time;
		}
		trap_S_StartSound (NULL, es->number, CHAN_ITEM, cgs.media.quadSound );
		break;

	case EV_POWERUP_BATTLESUIT:
		if ( es->number == cg.snap->ps.clientNum ) {
			cg.powerupActive = PW_BATTLESUIT;
			cg.powerupTime = cg.time;
		}
		trap_S_StartSound (NULL, es->number, CHAN_ITEM, cgs.media.protectSound );
#ifdef USE_RUNES
//Com_Printf("powerup: %i -> %i -> %i\n", es->eventParm, es->otherEntityNum, es->time);
    if(es->eventParm >= RUNE_STRENGTH && es->eventParm <= RUNE_LITHIUM
      && cg_entities[es->otherEntityNum].rune != es->eventParm) {
      gitem_t *item;
      item = BG_FindItemForRune(es->eventParm);
      CG_RegisterItemVisuals( ITEM_INDEX(item) );
      cg_entities[es->otherEntityNum].rune = es->eventParm;
    }
    /*
      if(cg.snap->ps.powerups[index] == 0) {
        cg_entities[cent->currentState.otherEntityNum].rune = 0
      } else {
        
      }
      cg_entities[cent->currentState.otherEntityNum].rune = item->giTag;
    }
    */
#endif
		break;

	case EV_POWERUP_REGEN:
		if ( es->number == cg.snap->ps.clientNum ) {
			cg.powerupActive = PW_REGEN;
			cg.powerupTime = cg.time;
		}
		trap_S_StartSound (NULL, es->number, CHAN_ITEM, cgs.media.regenSound );
		break;

#if defined(USE_GAME_FREEZETAG) || defined(USE_REFEREE_CMDS)
  case EV_FROZEN:
		if ( es->number == cg.snap->ps.clientNum ) {
			cg.powerupActive = PW_FROZEN;
			cg.powerupTime = cg.time;
		}
		cgs.clientinfo[es->number].health = 0;
		cg_entities[es->number].currentState.powerups |= (1 << PW_FROZEN);
		trap_S_StartSound (NULL, es->number, CHAN_ITEM, cgs.media.frozenSound );
		break;
  case EV_UNFROZEN:
    // TODO: play unfreeze sound
    //cg_entities[es->number].items[PW_FROZEN] = 0;
		cg_entities[es->number].currentState.powerups &= ~(1 << PW_FROZEN);
    trap_S_StartSound (NULL, es->number, CHAN_ITEM, cgs.media.unfrozenSound );
    break;
#endif

	case EV_GIB_PLAYER:
		// don't play gib sound when using the kamikaze because it interferes
		// with the kamikaze sound, downside is that the gib sound will also
		// not be played when someone is gibbed while just carrying the kamikaze
#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS)
		if ( !(es->eFlags & EF_KAMIKAZE) ) {
			trap_S_StartSound( NULL, es->number, CHAN_BODY, cgs.media.gibSound );
		}
#else
		trap_S_StartSound( NULL, es->number, CHAN_BODY, cgs.media.gibSound );
#endif
		CG_GibPlayer( cent->lerpOrigin );
		break;

#ifdef USE_HEADSHOTS
  case EV_GIB_PLAYER_HEADSHOT:
    trap_S_StartSound( NULL, es->number, CHAN_BODY, cgs.media.gibSound );
    cent->pe.noHead = qtrue;
    CG_GibPlayerHeadshot( cent->lerpOrigin );
    break;
  case EV_BODY_NOHEAD:
    cent->pe.noHead = qtrue;
    break;
#endif

	case EV_STOPLOOPINGSOUND:
		trap_S_StopLoopingSound( es->number );
		es->loopSound = 0;
		break;

	case EV_DEBUG_LINE:
		CG_Beam( cent );
		break;


	case EV_CURSORSTART:
		CG_Printf("Start cursor\n");
		break;

	default:
		CG_Error( "Unknown event: %i", event );
		break;
	}
}


/*
==============
CG_CheckEvents

==============
*/
void CG_CheckEvents( centity_t *cent ) {
	// check for event-only entities
	if ( cent->currentState.eType > ET_EVENTS ) {
		if ( cent->previousEvent ) {
			return;	// already fired
		}
		// if this is a player event set the entity number of the client entity number
		if ( cent->currentState.eFlags & EF_PLAYER_EVENT ) {
			cent->currentState.number = cent->currentState.otherEntityNum;
		}

		cent->previousEvent = 1;

		cent->currentState.event = cent->currentState.eType - ET_EVENTS;
	} else {
		// check for events riding with another entity
		if ( cent->currentState.event == cent->previousEvent ) {
			return;
		}
		cent->previousEvent = cent->currentState.event;
		if ( ( cent->currentState.event & ~EV_EVENT_BITS ) == 0 ) {
			return;
		}
	}

	// calculate the position at exactly the frame time
	BG_EvaluateTrajectory( &cent->currentState.pos, cg.snap->serverTime, cent->lerpOrigin );
	CG_SetEntitySoundPosition( cent );

	CG_EntityEvent( cent, cent->lerpOrigin, -1 );
}
