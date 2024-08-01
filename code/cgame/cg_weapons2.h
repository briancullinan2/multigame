/*
{
  WP_NONE, // weapon_t  giTag; // for matching up with items
	NULL, // char *readyFile;
	NULL, // char *firingFile;
	0, // int		loopFireSound;
	{NULL, NULL, NULL, NULL}, // char *flashSoundFile[4];
	0.0f, // float			flashDlight;
	{0.0f, 0.0f, 0.0f}, // vec3_t			flashDlightColor;
	NULL, // char *missileFile;
	NULL, // char *missleModelFile;
	NULL, // void			(*missileTrailFunc)( centity_t *, const struct weaponInfo_s *wi );
	0.0f, // float			missileDlight;
	{0.0f, 0.0f, 0.0f}, // vec3_t			missileDlightColor;
	0, // int				missileRenderfx;
	NULL, // void			(*ejectBrassFunc)( centity_t * );
	0.0f, // float			trailRadius;
	0.0f, // float			wiTrailTime;
	NULL, // char *handsFile;
	NULL, // char *weaponFile;
	NULL, // char *barrelFile;
	{NULL, NULL, NULL, NULL}, // char *flashShaders[4];
	{NULL, NULL, NULL, NULL}, // char *flashModels[4];
	{NULL, NULL, NULL, NULL}, // char *flashShaders[4];
  0 // int explosionRadius
},
*/

#if 0 //def USE_GRAPPLE
{
  WP_GRAPPLING_HOOK2,
  "sound/weapons3/melee/fsthum.wav",
  "sound/weapons3/melee/fstrun.wav",
  0,
  {"sound/weapons3/grapple/grapfire.wav", NULL, NULL, NULL},
  0,
  {0.6f, 0.6f, 1.0f},
  "baseoa/sound/weapons3/grapple/grappull.wav", // missile sound file
  "models/ammo/rocket/rocket.md3",
  CG_GrappleTrail,
  HOOK_GLOW_RADIUS, // dlight
  {1, 0.75f, 0},
  0, // missile effects
  NULL, // eject brass
  64,
  2000,
  NULL,
  NULL,
  NULL,
  {NULL, "lightningBoltNew2", NULL, NULL},
  {NULL, NULL, NULL, NULL}
},
#endif

{
  WP_GAUNTLET2,
  NULL,
  "sound/weapons3/melee/fsthum.wav",
  0,
  {"sound/weapons3/melee/fstatck.wav", NULL, NULL, NULL},
  0,
  {0.0f, 0.0f, 0.0f},
  NULL, // missile sound file
  NULL,
  NULL,
  0, // dlight
  {0.6f, 0.6f, 1.0f},
  0,
  NULL,
  0, 
  0, 
  NULL,
  NULL,
  NULL,
  {"gfx/damage/hole_lg_mrk", "lightningBoltNew2", NULL, NULL},
},

{
  WP_LIGHTNING2,
  "sound/weapons3/melee/fsthum.wav",
  "sound/weapons3/lightning/lg_hum.wav",
  0,
  {"sound/weapons3/lightning/lg_fire.wav", NULL, NULL, NULL},
  0,
  {0.6f, 0.6f, 1.0f},
  NULL,
  NULL,
  NULL,
  0,
  {0.0f, 0.0f, 0.0f},
  0,
  NULL,
  0, 
  0, 
  NULL,
  NULL,
  NULL,
  {"gfx/damage/hole_lg_mrk", "lightningBoltNew2", NULL, NULL},
  {"models/weaphits/crackle.md3", NULL, NULL, NULL},
  {"sound/weapons3/lightning/lg_hit.wav", "sound/weapons3/lightning/lg_hit2.wav",
  "sound/weapons3/lightning/lg_hit3.wav", NULL},
  12 // int explosionRadius
},

#if 0 //defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS)
{
  WP_CHAINGUN2, // weapon_t  giTag; // for matching up with items
	NULL, // char *readyFile;
	"sound/weapons3/vulcan/wvulfire.wav", // char *firingFile;
	qtrue, // int		loopFireSound;
	{"sound/weapons3/vulcan/vulcanf1b.wav", "sound/weapons3/vulcan/vulcanf2b.wav", 
  "sound/weapons3/vulcan/vulcanf3b.wav", "sound/weapons3/vulcan/vulcanf4b.wav"}, // char *flashSoundFile[4];
	0.0f, // float			flashDlight;
	{1.0f, 1.0f, 0.0f}, // vec3_t			flashDlightColor;
	NULL, // char *missileFile;
	NULL, // char *missleModelFile;
	NULL, // void			(*missileTrailFunc)( centity_t *, const struct weaponInfo_s *wi );
	0.0f, // float			missileDlight;
	{0.0f, 0.0f, 0.0f}, // vec3_t			missileDlightColor;
	0, // int				missileRenderfx;
	CG_MachineGunEjectBrass, // void			(*ejectBrassFunc)( centity_t * );
	0.0f, // float			trailRadius;
	0.0f, // float			wiTrailTime;
	NULL, // char *handsFile;
	NULL, // char *weaponFile;
	NULL, // char *barrelFile;
	{"gfx/damage/bullet_mrk", "bulletExplosion", NULL, NULL}, // char *flashModels[4];
	{"models/weaphits/bullet.md3", NULL, NULL, NULL}, // char *flashShaders[4];
  {"sound/weapons3/vulcan/wvulimpd.wav", "sound/weapons3/vulcan/wvulimpm.wav", 
  "sound/weapons3/vulcan/wvulimpl.wav", NULL},
  8 // int explosionRadius
},

#endif

{
  WP_MACHINEGUN2,
	NULL, // char *readyFile;
	NULL, // char *firingFile;
	0, // int		loopFireSound;
	{"sound/weapons3/machinegun/machgf1b.wav", "sound/weapons3/machinegun/machgf2b.wav", 
  "sound/weapons3/machinegun/machgf3b.wav", "sound/weapons3/machinegun/machgf4b.wav"}, // char *flashSoundFile[4];
	0.0f, // float			flashDlight;
	{0.0f, 0.0f, 0.0f}, // vec3_t			flashDlightColor;
	NULL, // char *missileFile;
	NULL, // char *missleModelFile;
	NULL, // void			(*missileTrailFunc)( centity_t *, const struct weaponInfo_s *wi );
	0.0f, // float			missileDlight;
	{0.0f, 0.0f, 0.0f}, // vec3_t			missileDlightColor;
	0, // int				missileRenderfx;
	CG_MachineGunEjectBrass, // void			(*ejectBrassFunc)( centity_t * );
	0.0f, // float			trailRadius;
	0.0f, // float			wiTrailTime;
	NULL, // char *handsFile;
	NULL, // char *weaponFile;
	NULL, // char *barrelFile;
	{"gfx/damage/bullet_mrk", "bulletExplosion2", NULL, NULL}, // char *flashModels[4];
	{"models/weaphits/bullet.md3", NULL, NULL, NULL}, // char *flashShaders[4];
  {"sound/weapons3/machinegun/ric1.wav", "sound/weapons3/machinegun/ric2.wav"
  "sound/weapons3/machinegun/ric3.wav", NULL},
  8 // int explosionRadius
},

{
  WP_SHOTGUN2,
  NULL, // char *readyFile;
	NULL, // char *firingFile;
	0, // int		loopFireSound;
	{"sound/weapons3/shotgun/sshotf1b.wav", NULL, NULL, NULL}, // char *flashSoundFile[4];
	0.0f, // float			flashDlight;
	{1.0f, 1.0f, 0.0f}, // vec3_t			flashDlightColor;
	NULL, // char *missileFile;
	NULL, // char *missleModelFile;
	NULL, // void			(*missileTrailFunc)( centity_t *, const struct weaponInfo_s *wi );
	0.0f, // float			missileDlight;
	{0.0f, 0.0f, 0.0f}, // vec3_t			missileDlightColor;
	0, // int				missileRenderfx;
	CG_ShotgunEjectBrass, // void			(*ejectBrassFunc)( centity_t * );
  0.0f, // float			trailRadius;
	0.0f, // float			wiTrailTime;
	NULL, // char *handsFile;
	NULL, // char *weaponFile;
	NULL, // char *barrelFile;
	{"gfx/damage/bullet_mrk", "bulletExplosion2", NULL, NULL}, // char *flashModels[4];
  {"models/weaphits/bullet.md3", NULL, NULL, NULL},
  {NULL, NULL, NULL, NULL},
  4 // int explosionRadius
},

{
  WP_ROCKET_LAUNCHER2,
	NULL, // char *readyFile;
	NULL, // char *firingFile;
	0, // int		loopFireSound;
	{"sound/weapons3/rocket/rocklf1a.wav", NULL, NULL, NULL}, // char *flashSoundFile[4];
	0.0f, // float			flashDlight;
	{1.0f, 0.75f, 0.0f}, // vec3_t			flashDlightColor;
	"sound/weapons3/rocket/rockfly.wav", // char *missileFile;
	"models/ammo/rocket/rocket.md3", // char *missleModelFile;
	CG_RocketTrail, // void			(*missileTrailFunc)( centity_t *, const struct weaponInfo_s *wi );
	MISSILE_GLOW_RADIUS, // float			missileDlight;
	{1.0f, 0.75f, 0.0f}, // vec3_t			missileDlightColor;
	0, // int				missileRenderfx;
	NULL, // void			(*ejectBrassFunc)( centity_t * );
	64.0f, // float			trailRadius;
	2000.0f, // float			wiTrailTime;
	NULL, // char *handsFile;
	NULL, // char *weaponFile;
	NULL, // char *barrelFile;
	{"gfx/damage/burn_med_mrk", "rocketExplosion2", NULL, NULL}, // char *flashModels[4];
	{"models/weaphits/boom01.md3", NULL, NULL, NULL}, // char *flashShaders[4];
  {"sound/weapons3/rocket/rocklx1a.wav", NULL, NULL, NULL},
  64, // int explosionRadius
  RL_EXPLOSION_RADIUS,
  {1.0f, 0.75f, 0.0f}
},

#if 0 //defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS)
{
  WP_PROX_LAUNCHER,
  NULL, // char *readyFile;
	NULL, // char *firingFile;
	0, // int		loopFireSound;
	{"sound/weapons3/proxmine/wstbfire.wav", NULL, NULL, NULL}, // char *flashSoundFile[4];
	0.0f, // float			flashDlight;
	{1.0f, 0.70f, 0.0f}, // vec3_t			flashDlightColor;
	NULL, // char *missileFile;
	"models/weaphits/proxmine.md3", // char *missleModelFile;
	CG_GrenadeTrail, // void			(*missileTrailFunc)( centity_t *, const struct weaponInfo_s *wi );
	0.0f, // float			missileDlight;
	{0.0f, 0.0f, 0.0f}, // vec3_t			missileDlightColor;
	0, // int				missileRenderfx;
	NULL, // void			(*ejectBrassFunc)( centity_t * );
	32.0f, // float			trailRadius;
	700.0f, // float			wiTrailTime;
  NULL,
  NULL,
  NULL,
  {"gfx/damage/burn_med_mrk", "grenadeExplosion2", NULL, NULL},
  {"models/weaphits/boom01.md3", NULL, NULL, NULL},
  { "sound/weapons3/proxmine/wstbexpl.wav", NULL, NULL, NULL},
  64, // int explosionRadius
  300
},

#endif

{
  WP_GRENADE_LAUNCHER2, // weapon_t  giTag; // for matching up with items
	NULL, // char *readyFile;
	NULL, // char *firingFile;
	0, // int		loopFireSound;
	{"sound/weapons3/grenade/grenlf1a.wav", NULL, NULL, NULL}, // char *flashSoundFile[4];
	0.0f, // float			flashDlight;
	{1.0f, 0.70f, 0.0f}, // vec3_t			flashDlightColor;
	NULL, // char *missileFile;
	"models/ammo/grenade1.md3", // char *missleModelFile;
	CG_GrenadeTrail, // void			(*missileTrailFunc)( centity_t *, const struct weaponInfo_s *wi );
	0.0f, // float			missileDlight;
	{0.0f, 0.0f, 0.0f}, // vec3_t			missileDlightColor;
	0, // int				missileRenderfx;
	NULL, // void			(*ejectBrassFunc)( centity_t * );
	32.0f, // float			trailRadius;
	700.0f, // float			wiTrailTime;
	NULL, // char *handsFile;
	NULL, // char *weaponFile;
	NULL, // char *barrelFile;
	{"gfx/damage/burn_med_mrk", "grenadeExplosion2", NULL, NULL}, // char *flashModels[4];
	{"models/weaphits/boom01.md3", NULL, NULL, NULL}, // char *flashShaders[4];
  {"sound/weapons3/rocket/rocklx1a.wav", NULL, NULL, NULL},
  64, // int explosionRadius
  GL_EXPLOSION_RADIUS
},

#if 0 //defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS)
{
  WP_NAILGUN, // weapon_t  giTag; // for matching up with items
	NULL, // char *readyFile;
	NULL, // char *firingFile;
	0, // int		loopFireSound;
	{"sound/weapons3/nailgun/wnalfire.wav", NULL, NULL, NULL}, // char *flashSoundFile[4];
	0.0f, // float			flashDlight;
	{1.0f, 0.75f, 0.0f}, // vec3_t			flashDlightColor;
	NULL, // char *missileFile;
	"models/weaphits/nail.md3", // char *missleModelFile;
	CG_NailTrail, // void			(*missileTrailFunc)( centity_t *, const struct weaponInfo_s *wi );
	0.0f, // float			missileDlight;
	{0.0f, 0.0f, 0.0f}, // vec3_t			missileDlightColor;
	0, // int				missileRenderfx;
	CG_NailgunEjectBrass, // void			(*ejectBrassFunc)( centity_t * );
	16.0f, // float			trailRadius;
	250.0f, // float			wiTrailTime;
	NULL, // char *handsFile;
	NULL, // char *weaponFile;
	NULL, // char *barrelFile;
	{"gfx/damage/hole_lg_mrk", NULL, NULL, NULL}, // char *flashModels[4];
	{NULL, NULL, NULL, NULL}, // char *flashShaders[4];
  {"sound/weapons3/nailgun/wnalimpd.wav", "sound/weapons3/nailgun/wnalimpm.wav",  
  "sound/weapons3/nailgun/wnalimpl.wav", NULL},
  12 // int explosionRadius
},

#endif

{
  WP_PLASMAGUN2, // weapon_t  giTag; // for matching up with items
	NULL, // char *readyFile;
	NULL, // char *firingFile;
	0, // int		loopFireSound;
	{"sound/weapons3/plasma/hyprbf1a.wav", NULL, NULL, NULL}, // char *flashSoundFile[4];
	0.0f, // float			flashDlight;
	{0.6f, 0.6f, 1.0f}, // vec3_t			flashDlightColor;
	"sound/weapons3/plasma/lasfly.wav", // char *missileFile;
	NULL, // char *missleModelFile;
	CG_PlasmaTrail, // void			(*missileTrailFunc)( centity_t *, const struct weaponInfo_s *wi );
	MISSILE_GLOW_RADIUS, // float			missileDlight;
	{0.2f, 0.2f, 1.0f}, // vec3_t			missileDlightColor;
	0, // int				missileRenderfx;
	NULL, // void			(*ejectBrassFunc)( centity_t * );
	0.0f, // float			trailRadius;
	0.0f, // float			wiTrailTime;
	NULL, // char *handsFile;
	NULL, // char *weaponFile;
	NULL, // char *barrelFile;
	{"gfx/damage/plasma_mrk", "plasmaExplosion2", "railDisc2", NULL}, // char *flashModels[4];
	{"models/weaphits/ring02.md3", NULL, NULL, NULL}, // char *flashShaders[4];
  {"sound/weapons3/plasma/plasmx1a.wav", NULL, NULL, NULL},
  16
},

{
  WP_RAILGUN2, // weapon_t  giTag; // for matching up with items
	"sound/weapons3/railgun/rg_hum.wav", // char *readyFile;
	NULL, // char *firingFile;
	0, // int		loopFireSound;
	{"sound/weapons3/railgun/railgf1a.wav", NULL, NULL, NULL}, // char *flashSoundFile[4];
	0.0f, // float			flashDlight;
	{1.0f, 0.5f, 0.0f}, // vec3_t			flashDlightColor;
	NULL, // char *missileFile;
	NULL, // char *missleModelFile;
	NULL, // void			(*missileTrailFunc)( centity_t *, const struct weaponInfo_s *wi );
	0.0f, // float			missileDlight;
	{0.0f, 0.0f, 0.0f}, // vec3_t			missileDlightColor;
	0, // int				missileRenderfx;
	NULL, // void			(*ejectBrassFunc)( centity_t * );
	0.0f, // float			trailRadius;
	0.0f, // float			wiTrailTime;
	NULL, // char *handsFile;
	NULL, // char *weaponFile;
	NULL, // char *barrelFile;
	{"gfx/damage/plasma_mrk", "railExplosion2", "railDisc2", "railCore"}, // char *flashModels[4];
	{"models/weaphits/ring02.md3", NULL, NULL, NULL}, // char *flashShaders[4];
  {"sound/weapons3/plasma/plasmx1a.wav", NULL, NULL, NULL},
  24
},

{
  WP_BFG2, // weapon_t  giTag; // for matching up with items
	"sound/weapons3/bfg/bfg_hum.wav", // char *readyFile;
	NULL, // char *firingFile;
	0, // int		loopFireSound;
	{"sound/weapons3/bfg/bfg_fire.wav", NULL, NULL, NULL}, // char *flashSoundFile[4];
	0.0f, // float			flashDlight;
	{1.0f, 0.7f, 1.0f}, // vec3_t			flashDlightColor;
	"sound/weapons3/rocket/rockfly.wav", // char *missileFile;
	"models/weaphits/bfg.md3", // char *missleModelFile;
	NULL, // void			(*missileTrailFunc)( centity_t *, const struct weaponInfo_s *wi );
	MISSILE_GLOW_RADIUS, // float			missileDlight;
	{0.2f, 1.0f, 0.2f}, // vec3_t			missileDlightColor;
	0, // int				missileRenderfx;
	NULL, // void			(*ejectBrassFunc)( centity_t * );
	0.0f, // float			trailRadius;
	0.0f, // float			wiTrailTime;
	NULL, // char *handsFile;
	NULL, // char *weaponFile;
	NULL, // char *barrelFile;
	{"gfx/damage/burn_med_mrk", "bfgExplosion2", NULL, NULL}, // char *flashModels[4];
	{"models/weaphits/boom01.md3", NULL, NULL, NULL}, // char *flashShaders[4];
  {"sound/weapons3/rocket/rocklx1a.wav", NULL, NULL, NULL},
  32,
  BFG_EXPLOSION_RADIUS,
  {0.2f, 1.0f, 0.2f}
},




