// Copyright (C) 1999-2000 Id Software, Inc.
//
// bg_local.h -- local definitions for the bg (both games) files

#define	MIN_WALK_NORMAL	0.7f		// can't walk on very steep slopes

#define	JUMP_VELOCITY	270

#define	TIMER_LAND		130
#define	TIMER_GESTURE	(34*66+50)

#define	OVERCLIP		1.001f

// all of the locals will be zeroed before each
// pmove, just to make damn sure we don't have
// any differences when running on client or server
typedef struct {
	vec3_t		forward, right, up;
	float		frametime;

	int			msec;

	qboolean	walking;
	qboolean	groundPlane;
	trace_t		groundTrace;
#ifdef USE_LADDERS
  qboolean  ladder;
#endif

	float		impactSpeed;

	vec3_t		previous_origin;
	vec3_t		previous_velocity;
	int			previous_waterlevel;
#ifdef USE_VEHICLES
// STONELANCE
	int			physicsSplit;
// END
#endif
} pml_t;

extern	pmove_t		*pm;
extern	pml_t		pml;

// movement parameters
extern	float	pm_stopspeed;
extern	float	pm_duckScale;
extern	float	pm_swimScale;
extern	float	pm_wadeScale;

extern	float	pm_accelerate;
extern	float	pm_airaccelerate;
extern	float	pm_wateraccelerate;
extern	float	pm_flyaccelerate;

extern	float	pm_friction;
extern	float	pm_waterfriction;
extern	float	pm_flightfriction;

extern	int		c_pmove;

#ifdef USE_WEAPON_VARS

#ifdef CGAME

#ifdef USE_GRAPPLE
#define g_altGrapple cg_altGrapple
#define wp_grapplePull cgwp_grapplePull
#endif

#define wp_gauntCycle   cgwp_gauntCycle
#define wp_lightCycle   cgwp_lightCycle
#define wp_shotgunCycle cgwp_shotgunCycle
#define wp_machineCycle cgwp_machineCycle
#define wp_grenadeCycle cgwp_grenadeCycle
#define wp_rocketCycle  cgwp_rocketCycle
#define wp_plasmaCycle  cgwp_plasmaCycle
#define wp_railCycle    cgwp_railCycle
#define wp_bfgCycle     cgwp_bfgCycle
#define wp_grappleCycle cgwp_grappleCycle
#define wp_nailCycle    cgwp_nailCycle
#define wp_proxCycle    cgwp_proxCycle
#define wp_chainCycle   cgwp_chainCycle
#define wp_flameCycle   cgwp_flameCycle

extern vmCvar_t  cgwp_gauntCycle;
extern vmCvar_t  cgwp_lightCycle;
extern vmCvar_t  cgwp_shotgunCycle;
extern vmCvar_t  cgwp_machineCycle;
extern vmCvar_t  cgwp_grenadeCycle;
extern vmCvar_t  cgwp_rocketCycle;
extern vmCvar_t  cgwp_plasmaCycle;
extern vmCvar_t  cgwp_railCycle;
extern vmCvar_t  cgwp_bfgCycle;
extern vmCvar_t  cgwp_grappleCycle;
extern vmCvar_t  cgwp_nailCycle;
extern vmCvar_t  cgwp_proxCycle;
extern vmCvar_t  cgwp_chainCycle;
extern vmCvar_t  cgwp_flameCycle;

#else // end CGAME

extern vmCvar_t  wp_gauntCycle;
extern vmCvar_t  wp_lightCycle;
extern vmCvar_t  wp_shotgunCycle;
extern vmCvar_t  wp_machineCycle;
extern vmCvar_t  wp_grenadeCycle;
extern vmCvar_t  wp_rocketCycle;
extern vmCvar_t  wp_plasmaCycle;
extern vmCvar_t  wp_railCycle;
extern vmCvar_t  wp_bfgCycle;
extern vmCvar_t  wp_grappleCycle;
extern vmCvar_t  wp_nailCycle;
extern vmCvar_t  wp_proxCycle;
extern vmCvar_t  wp_chainCycle;
extern vmCvar_t  wp_flameCycle;

#endif

#endif // end USE_WEAPON_VARS

#ifdef USE_GRAPPLE
extern vmCvar_t  g_altGrapple;
extern vmCvar_t  wp_grapplePull;
#endif


#ifdef USE_PORTALS
#ifdef CGAME
#define wp_portalEnable cgwp_portalEnable
#define g_altPortal cg_altPortal
#endif
#endif
void PM_ClipVelocity( vec3_t in, vec3_t normal, vec3_t out, float overbounce );
void PM_AddTouchEnt( int entityNum );
void PM_AddEvent( int newEvent );

qboolean	PM_SlideMove( qboolean gravity );
void		PM_StepSlideMove( qboolean gravity );
