


	//
	// ARMOR
	//

/*QUAKED item_earth_armor_shard (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_earth_armor_shard", 
		"sound/misc/ar1_pkup.wav",
		{ "models/powerups5/armor/shardearth.md3", 
		"models/powerups5/armor/shard_sphereearth.md3",
		0, 0} ,
/* icon */		"icons/iconr_shard",
/* pickup */	"Armor Shard",
		5,
		IT_ARMOR2,
		0,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED item_earth_armor_combat (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_earth_armor_combat", 
		"sound/misc/ar2_pkup.wav",
        { "models/powerups5/armor/armor_yellowearth.md3",
		0, 0, 0},
/* icon */		"icons/iconr_yellow",
/* pickup */	"Armor",
		50,
		IT_ARMOR2,
		0,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED item_earth_armor_body (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_earth_armor_body", 
		"sound/misc/ar2_pkup.wav",
        { "models/powerups5/armor/armor_redearth.md3",
		0, 0, 0},
/* icon */		"icons/iconr_red",
/* pickup */	"Heavy Armor",
		100,
		IT_ARMOR2,
		0,
/* precache */ "",
/* sounds */ "",
//		"models/powerups5/armor/armor_red.skin%rainbow"
	},

	//
	// health
	//
/*QUAKED item_earth_health_small (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_earth_health_small",
		"sound/items/s_health.wav",
        { "models/powerups5/health/small_crossearth.md3", 
		"models/powerups5/health/small_sphereearth.md3", 
		0, 0 },
/* icon */		"icons/iconh_green",
/* pickup */	"5 Health",
		5,
		IT_HEALTH2,
		0,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED item_earth_health (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_earth_health",
		"sound/items/n_health.wav",
        { "models/powerups5/health/medium_crossearth.md3", 
		"models/powerups5/health/medium_sphereearth.md3", 
		0, 0 },
/* icon */		"icons/iconh_yellow",
/* pickup */	"25 Health",
		25,
		IT_HEALTH2,
		0,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED item_earth_health_large (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_earth_health_large",
		"sound/items/l_health.wav",
        { "models/powerups5/health/large_crossearth.md3", 
		"models/powerups5/health/large_sphereearth.md3", 
		0, 0 },
/* icon */		"icons/iconh_red",
/* pickup */	"50 Health",
		50,
		IT_HEALTH2,
		0,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED item_earth_health_mega (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_earth_health_mega",
		"sound/items/m_health.wav",
        { "models/powerups5/health/mega_crossearth.md3", 
		"models/powerups5/health/mega_sphereearth.md3", 
		0, 0 },
/* icon */		"icons/iconh_mega",
/* pickup */	"Mega Health",
		100,
		IT_HEALTH2,
		0,
/* precache */ "",
/* sounds */ ""
	},


	//
	// WEAPONS 
	//

/*QUAKED weapon_earth_gauntlet (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_earth_gauntlet", 
		"sound/misc/w_pkup.wav",
        { "models/weapons5/gauntlet/gauntletearth.md3",
		0, 0, 0},
/* icon */		"icons/iconw_gauntlet",
/* pickup */	"Gauntlet",
		0,
		IT_WEAPON2,
		WP_GAUNTLET,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED weapon_earth_shotgun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_earth_shotgun", 
		"sound/misc/w_pkup.wav",
        { "models/weapons5/shotgun/shotgunearth.md3", 
		0, 0, 0},
/* icon */		"icons/iconw_shotgun",
/* pickup */	"Shotgun",
		10,
		IT_WEAPON2,
		WP_SHOTGUN,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED weapon_earth_machinegun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_earth_machinegun", 
		"sound/misc/w_pkup.wav",
        { "models/weapons5/machinegun/machinegunearth.md3", 
		0, 0, 0},
/* icon */		"icons/iconw_machinegun",
/* pickup */	"Machinegun",
		40,
		IT_WEAPON2,
		WP_MACHINEGUN,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED weapon_earth_grenadelauncher (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_earth_grenadelauncher",
		"sound/misc/w_pkup.wav",
        { "models/weapons5/grenadel/grenadelearth.md3", 
		0, 0, 0},
/* icon */		"icons/iconw_grenade",
/* pickup */	"Grenade Launcher",
		10,
		IT_WEAPON2,
		WP_GRENADE_LAUNCHER,
/* precache */ "",
/* sounds */ "sound/weapons/grenade/hgrenb1a.wav sound/weapons/grenade/hgrenb2a.wav"
	},

/*QUAKED weapon_earth_rocketlauncher (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_earth_rocketlauncher",
		"sound/misc/w_pkup.wav",
        { "models/weapons5/rocketl/rocketlearth.md3", 
		0, 0, 0},
/* icon */		"icons/iconw_rocket",
/* pickup */	"Rocket Launcher",
		10,
		IT_WEAPON2,
		WP_ROCKET_LAUNCHER,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED weapon_earth_lightning (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_earth_lightning", 
		"sound/misc/w_pkup.wav",
        { "models/weapons5/lightning/lightningearth.md3", 
		0, 0, 0},
/* icon */		"icons/iconw_lightning",
/* pickup */	"Lightning Gun",
		100,
		IT_WEAPON2,
		WP_LIGHTNING,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED weapon_earth_railgun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_earth_railgun", 
		"sound/misc/w_pkup.wav",
        { "models/weapons5/railgun/railgunearth.md3", 
		0, 0, 0},
/* icon */		"icons/iconw_railgun",
/* pickup */	"Railgun",
		10,
		IT_WEAPON2,
		WP_RAILGUN,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED weapon_earth_plasmagun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_earth_plasmagun", 
		"sound/misc/w_pkup.wav",
        { "models/weapons5/plasma/plasmaearth.md3", 
		0, 0, 0},
/* icon */		"icons/iconw_plasma",
/* pickup */	"Plasma Gun",
		50,
		IT_WEAPON2,
		WP_PLASMAGUN,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED weapon_earth_bfg (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_earth_bfg",
		"sound/misc/w_pkup.wav",
        { "models/weapons5/bfg/bfgearth.md3", 
		0, 0, 0},
/* icon */		"icons/iconw_bfg",
/* pickup */	"BFG10K",
		20,
		IT_WEAPON2,
		WP_BFG,
/* precache */ "",
/* sounds */ ""
	},

#ifdef USE_GRAPPLE
/*QUAKED weapon_earth_grapplinghook (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_earth_grapplinghook",
		"sound/misc/w_pkup.wav",
        { "models/weapons5/grapple/grappleearth.md3", 
		0, 0, 0},
/* icon */		"icons/iconw_grapple",
/* pickup */	"Grappling Hook",
		0,
		IT_WEAPON2,
		WP_GRAPPLING_HOOK,
/* precache */ "",
/* sounds */ ""
	},
#endif

	//
	// AMMO ITEMS
	//

/*QUAKED ammo_earth_shells (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"ammo_earth_shells",
		"sound/misc/am_pkup.wav",
        { "models/powerups5/ammo/shotgunamearth.md3", 
		0, 0, 0},
/* icon */		"icons/icona_shotgun",
/* pickup */	"Shells",
		10,
		IT_AMMO2,
		WP_SHOTGUN,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED ammo_earth_bullets (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"ammo_earth_bullets",
		"sound/misc/am_pkup.wav",
        { "models/powerups5/ammo/machinegunamearth.md3", 
		0, 0, 0},
/* icon */		"icons/icona_machinegun",
/* pickup */	"Bullets",
		50,
		IT_AMMO2,
		WP_MACHINEGUN,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED ammo_earth_grenades (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"ammo_earth_grenades",
		"sound/misc/am_pkup.wav",
        { "models/powerups5/ammo/grenadeamearth.md3", 
		0, 0, 0},
/* icon */		"icons/icona_grenade",
/* pickup */	"Grenades",
		5,
		IT_AMMO2,
		WP_GRENADE_LAUNCHER,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED ammo_earth_cells (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"ammo_earth_cells",
		"sound/misc/am_pkup.wav",
        { "models/powerups5/ammo/plasmaamearth.md3", 
		0, 0, 0},
/* icon */		"icons/icona_plasma",
/* pickup */	"Cells",
		30,
		IT_AMMO2,
		WP_PLASMAGUN,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED ammo_earth_lightning (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"ammo_earth_lightning",
		"sound/misc/am_pkup.wav",
        { "models/powerups5/ammo/lightningamearth.md3", 
		0, 0, 0},
/* icon */		"icons/icona_lightning",
/* pickup */	"Lightning",
		60,
		IT_AMMO2,
		WP_LIGHTNING,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED ammo_earth_rockets (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"ammo_earth_rockets",
		"sound/misc/am_pkup.wav",
        { "models/powerups5/ammo/rocketamearth.md3", 
		0, 0, 0},
/* icon */		"icons/icona_rocket",
/* pickup */	"Rockets",
		5,
		IT_AMMO2,
		WP_ROCKET_LAUNCHER,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED ammo_earth_slugs (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"ammo_earth_slugs",
		"sound/misc/am_pkup.wav",
        { "models/powerups5/ammo/railgunamearth.md3", 
		0, 0, 0},
/* icon */		"icons/icona_railgun",
/* pickup */	"Slugs",
		10,
		IT_AMMO2,
		WP_RAILGUN,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED ammo_earth_bfg (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"ammo_earth_bfg",
		"sound/misc/am_pkup.wav",
        { "models/powerups5/ammo/bfgamearth.md3", 
		0, 0, 0},
/* icon */		"icons/icona_bfg",
/* pickup */	"Bfg Ammo",
		15,
		IT_AMMO2,
		WP_BFG,
/* precache */ "",
/* sounds */ ""
	},

	//
	// HOLDABLE ITEMS
	//
/*QUAKED holdable_earth_teleporter (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"holdable_earth_teleporter", 
		"sound/items/holdable.wav",
        { "models/powerups5/holdable/teleporterearth.md3", 
		0, 0, 0},
/* icon */		"icons/teleporter",
/* pickup */	"Personal Teleporter",
		60,
		IT_HOLDABLE2,
		HI_TELEPORTER,
/* precache */ "",
/* sounds */ ""
	},
/*QUAKED holdable_earth_medkit (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"holdable_earth_medkit", 
		"sound/items/holdable.wav",
        { 
		"models/powerups5/holdable/medkitearth.md3", 
		"models/powerups5/holdable/medkit_sphereearth.md3",
		0, 0},
/* icon */		"icons/medkit",
/* pickup */	"Medkit",
		60,
		IT_HOLDABLE2,
		HI_MEDKIT,
/* precache */ "",
/* sounds */ "sound/items/use_medkit.wav"
	},

	//
	// POWERUP ITEMS
	//
/*QUAKED item_earth_quad (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_earth_quad", 
		"sound/items/quaddamage.wav",
        { "models/powerups5/instant/quad.md3", 
        "models/powerups5/instant/quad_ring.md3",
		0, 0 },
/* icon */		"icons/quad",
/* pickup */	"Quad Damage",
		30,
		IT_POWERUP2,
		PW_QUAD,
/* precache */ "",
/* sounds */ "sound/items/damage2.wav sound/items/damage3.wav"
	},

/*QUAKED item_earth_enviro (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_earth_enviro",
		"sound/items/protect.wav",
        { "models/powerups5/instant/enviroearth.md3", 
		"models/powerups5/instant/enviro_ringearth.md3", 
		0, 0 },
/* icon */		"icons/envirosuit",
/* pickup */	"Battle Suit",
		30,
		IT_POWERUP2,
		PW_BATTLESUIT,
/* precache */ "",
/* sounds */ "sound/items/airout.wav sound/items/protect3.wav"
	},

/*QUAKED item_earth_haste (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_earth_haste",
		"sound/items/haste.wav",
        { "models/powerups5/instant/hasteearth.md3", 
		"models/powerups5/instant/haste_ringearth.md3", 
		0, 0 },
/* icon */		"icons/haste",
/* pickup */	"Speed",
		30,
		IT_POWERUP2,
		PW_HASTE,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED item_earth_invis (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_earth_invis",
		"sound/items/invisibility.wav",
        { "models/powerups5/instant/invisearth.md3", 
		"models/powerups5/instant/invis_ringearth.md3", 
		0, 0 },
/* icon */		"icons/invis",
/* pickup */	"Invisibility",
		30,
		IT_POWERUP2,
		PW_INVIS,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED item_earth_regen (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_earth_regen",
		"sound/items/regeneration.wav",
        { "models/powerups5/instant/regenearth.md3", 
		"models/powerups5/instant/regen_ringearth.md3", 
		0, 0 },
/* icon */		"icons/regen",
/* pickup */	"Regeneration",
		30,
		IT_POWERUP2,
		PW_REGEN,
/* precache */ "",
/* sounds */ "sound/items/regen.wav"
	},

/*QUAKED item_earth_flight (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_earth_flight",
		"sound/items/flight.wav",
        { "models/powerups5/instant/flightearth.md3", 
		"models/powerups5/instant/flight_ringearth.md3", 
		0, 0 },
/* icon */		"icons/flight",
/* pickup */	"Flight",
		60,
		IT_POWERUP2,
		PW_FLIGHT,
/* precache */ "",
/* sounds */ "sound/items/flight.wav"
	},

/*QUAKED team_CTF_redflag (1 0 0) (-16 -16 -16) (16 16 16)
Only in CTF games
*/
	{
		"team_earth_CTF_redflag",
		NULL,
        { "models/flags/r_flagearth.md3",
		0, 0, 0 },
/* icon */		"icons/iconf_red1",
/* pickup */	"Red Flag",
		0,
		IT_TEAM2,
		PW_REDFLAG,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED team_CTF_blueflag (0 0 1) (-16 -16 -16) (16 16 16)
Only in CTF games
*/
	{
		"team_earth_CTF_blueflag",
		NULL,
        { "models/flags/b_flagearth.md3",
		0, 0, 0 },
/* icon */		"icons/iconf_blu1",
/* pickup */	"Blue Flag",
		0,
		IT_TEAM2,
		PW_BLUEFLAG,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED holdable_kamikaze (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "holdable_earth_vengeance", 
  "sound/items/holdable.wav",
      { "models/powerups5/holdable/vengeance.md3", 
  0, 0, 0},
/* icon */		"icons/kamikaze",
/* pickup */	"Vengeance",
  60,
  IT_HOLDABLE2,
  HI_KAMIKAZE,
/* precache */ "",
/* sounds */ "sound/items/kamikazerespawn.wav"
},

