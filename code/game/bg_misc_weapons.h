
//
// WEAPONS 
//

/*QUAKED weapon_gauntlet (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "weapon_gauntlet", 
  "sound/misc/w_pkup.wav",
      { "models/weapons2/gauntlet/gauntlet.md3",
  0, 0, 0},
/* icon */		"icons/iconw_gauntlet",
/* pickup */	"Gauntlet",
  0,
  IT_WEAPON,
  WP_GAUNTLET,
/* precache */ "",
/* sounds */ ""
},

/*QUAKED weapon_shotgun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "weapon_shotgun", 
  "sound/misc/w_pkup.wav",
      { "models/weapons2/shotgun/shotgun.md3", 
  0, 0, 0},
/* icon */		"icons/iconw_shotgun",
/* pickup */	"Shotgun",
  10,
  IT_WEAPON,
  WP_SHOTGUN,
/* precache */ "",
/* sounds */ ""
},

/*QUAKED weapon_machinegun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "weapon_machinegun", 
  "sound/misc/w_pkup.wav",
      { "models/weapons2/machinegun/machinegun.md3", 
  0, 0, 0},
/* icon */		"icons/iconw_machinegun",
/* pickup */	"Machinegun",
  40,
  IT_WEAPON,
  WP_MACHINEGUN,
/* precache */ "",
/* sounds */ ""
},

/*QUAKED weapon_grenadelauncher (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "weapon_grenadelauncher",
  "sound/misc/w_pkup.wav",
      { "models/weapons2/grenadel/grenadel.md3", 
  0, 0, 0},
/* icon */		"icons/iconw_grenade",
/* pickup */	"Grenade Launcher",
  10,
  IT_WEAPON,
  WP_GRENADE_LAUNCHER,
/* precache */ "",
/* sounds */ "sound/weapons/grenade/hgrenb1a.wav sound/weapons/grenade/hgrenb2a.wav"
},

/*QUAKED weapon_rocketlauncher (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "weapon_rocketlauncher",
  "sound/misc/w_pkup.wav",
      { "models/weapons2/rocketl/rocketl.md3", 
  0, 0, 0},
/* icon */		"icons/iconw_rocket",
/* pickup */	"Rocket Launcher",
  10,
  IT_WEAPON,
  WP_ROCKET_LAUNCHER,
/* precache */ "",
/* sounds */ ""
},

/*QUAKED weapon_lightning (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "weapon_lightning", 
  "sound/misc/w_pkup.wav",
      { "models/weapons2/lightning/lightning.md3", 
  0, 0, 0},
/* icon */		"icons/iconw_lightning",
/* pickup */	"Lightning Gun",
  100,
  IT_WEAPON,
  WP_LIGHTNING,
/* precache */ "",
/* sounds */ ""
},

/*QUAKED weapon_railgun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "weapon_railgun", 
  "sound/misc/w_pkup.wav",
      { "models/weapons2/railgun/railgun.md3", 
  0, 0, 0},
/* icon */		"icons/iconw_railgun",
/* pickup */	"Railgun",
  10,
  IT_WEAPON,
  WP_RAILGUN,
/* precache */ "",
/* sounds */ ""
},

/*QUAKED weapon_plasmagun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "weapon_plasmagun", 
  "sound/misc/w_pkup.wav",
      { "models/weapons2/plasma/plasma.md3", 
  0, 0, 0},
/* icon */		"icons/iconw_plasma",
/* pickup */	"Plasma Gun",
  50,
  IT_WEAPON,
  WP_PLASMAGUN,
/* precache */ "",
/* sounds */ ""
},

/*QUAKED weapon_bfg (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "weapon_bfg",
  "sound/misc/w_pkup.wav",
      { "models/weapons2/bfg/bfg.md3", 
  0, 0, 0},
/* icon */		"icons/iconw_bfg",
/* pickup */	"BFG10K",
  20,
  IT_WEAPON,
  WP_BFG,
/* precache */ "",
/* sounds */ ""
},

#ifdef USE_GRAPPLE

/*QUAKED weapon_grapplinghook (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "weapon_grapplinghook",
  "sound/misc/w_pkup.wav",
      { "models/weapons2/grapple/grapple.md3", 
  0, 0, 0},
/* icon */		"icons/iconw_grapple",
/* pickup */	"Grappling Hook",
  0,
  IT_WEAPON,
  WP_GRAPPLING_HOOK,
/* precache */ "",
/* sounds */ ""
},

#endif

#ifdef USE_FLAME_THROWER
  /*QUAKED weapon_flamethrower (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
  */
  {
  	"weapon_flamethrower",
  	"sound/misc/w_pkup.wav",
  	{ "models/weapons2/flamethrower/flamethrower.md3",
  	0, 0, 0},
  /* icon */	"icons/iconw_flamethrower",
  /* pickup */	"Flame Thrower",
  	20,
  	IT_WEAPON,
  	WP_FLAME_THROWER,
  /* precache */ "",
  /* sounds */ ""
  },


  /*QUAKED ammo_flame (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
  */
  {
  	"ammo_flame",
  	"sound/misc/am_pkup.wav",
  	{ "models/powerups/ammo/flameaam.md3", 
  	0, 0, 0},
  /* icon */"	icons/icona_flamethrower",
  /* pickup */	"Flame Ammo",
  	50,
  	IT_AMMO,
  	WP_FLAME_THROWER,
  /* precache */ "",
  /* sounds */ ""
  },
#endif

