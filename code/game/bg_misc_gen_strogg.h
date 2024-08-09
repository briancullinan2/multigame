


	//
	// ARMOR
	//

/*QUAKED item_strogg_armor_shard (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_strogg_armor_shard", 
		"sound/misc/ar1_pkup.wav",
		{ "models/powerups5/armor/shardstrogg.md3", 
		"models/powerups5/armor/shard_spherestrogg.md3",
		0, 0} ,
/* icon */		"icons/iconr_shard",
/* pickup */	"Armor Shard",
		5,
		IT_ARMOR2,
		0,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED item_strogg_armor_combat (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_strogg_armor_combat", 
		"sound/misc/ar2_pkup.wav",
        { "models/powerups5/armor/armor_yellowstrogg.md3",
		0, 0, 0},
/* icon */		"icons/iconr_yellow",
/* pickup */	"Combat Armor",
		50,
		IT_ARMOR2,
		0,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED item_strogg_armor_body (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_strogg_armor_body", 
		"sound/misc/ar2_pkup.wav",
        { "models/powerups5/armor/armor_redstrogg.md3",
		0, 0, 0},
/* icon */		"icons/iconr_red",
/* pickup */	"Body Armor",
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
/*QUAKED item_strogg_health_small (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_strogg_health_small",
		"sound/items/s_health.wav",
        { "models/powerups5/health/small_crossstrogg.md3", 
		"models/powerups5/health/small_spherestrogg.md3", 
		0, 0 },
/* icon */		"icons/iconh_green",
/* pickup */	"Health",
		5,
		IT_HEALTH2,
		0,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED item_strogg_health (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_strogg_health",
		"sound/items/n_health.wav",
        { "models/powerups5/health/medium_crossstrogg.md3", 
		"models/powerups5/health/medium_spherestrogg.md3", 
		0, 0 },
/* icon */		"icons/iconh_yellow",
/* pickup */	"Stimpack",
		25,
		IT_HEALTH2,
		0,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED item_strogg_health_large (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_strogg_health_large",
		"sound/items/l_health.wav",
        { "models/powerups5/health/large_crossstrogg.md3", 
		"models/powerups5/health/large_spherestrogg.md3", 
		0, 0 },
/* icon */		"icons/iconh_red",
/* pickup */	"Medkit",
		50,
		IT_HEALTH2,
		0,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED item_strogg_health_mega (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_strogg_health_mega",
		"sound/items/m_health.wav",
        { "models/powerups5/health/mega_crossstrogg.md3", 
		"models/powerups5/health/mega_spherestrogg.md3", 
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

/*QUAKED weapon_strogg_gauntlet (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_strogg_blaster", 
		"sound/misc/w_pkup.wav",
        { "models/weapons5/pistol/pistolstrogg.md3",
		0, 0, 0},
/* icon */		"icons/iconw_gauntlet",
/* pickup */	"Blaster",
		0,
		IT_WEAPON2,
		WP_BLASTER,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED weapon_strogg_shotgun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_strogg_shotgun", 
		"sound/misc/w_pkup.wav",
        { "models/weapons5/shotgun/shotgunstrogg.md3", 
		0, 0, 0},
/* icon */		"icons/iconw_shotgun",
/* pickup */	"Super Shotgun",
		10,
		IT_WEAPON2,
		WP_TRESPASSER2,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED weapon_strogg_machinegun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_strogg_machinegun", 
		"sound/misc/w_pkup.wav",
        { "models/weapons5/machinegun/machinegunstrogg.md3", 
		0, 0, 0},
/* icon */		"icons/iconw_machinegun",
/* pickup */	"Stepchild",
		40,
		IT_WEAPON2,
		WP_STEPCHILD2,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED weapon_strogg_grenadelauncher (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_strogg_grenadelauncher",
		"sound/misc/w_pkup.wav",
        { "models/weapons5/grenadel/grenadelstrogg.md3", 
		0, 0, 0},
/* icon */		"icons/iconw_grenade",
/* pickup */	"Joker",
		10,
		IT_WEAPON2,
		WP_JOKER2,
/* precache */ "",
/* sounds */ "sound/weapons/grenade/hgrenb1a.wav sound/weapons/grenade/hgrenb2a.wav"
	},

/*QUAKED weapon_strogg_rocketlauncher (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_strogg_rocketlauncher",
		"sound/misc/w_pkup.wav",
        { "models/weapons5/rocketl/rocketlstrogg.md3", 
		0, 0, 0},
/* icon */		"icons/iconw_rocket",
/* pickup */	"Peacemaker",
		10,
		IT_WEAPON2,
		WP_PEACEMAKER2,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED weapon_strogg_lightning (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_strogg_lightning", 
		"sound/misc/w_pkup.wav",
        { "models/weapons5/lightning/lightningstrogg.md3", 
		0, 0, 0},
/* icon */		"icons/iconw_lightning",
/* pickup */	"Chaingun",
		100,
		IT_WEAPON2,
		WP_CHAINGUN2,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED weapon_strogg_railgun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_strogg_railgun", 
		"sound/misc/w_pkup.wav",
        { "models/weapons5/railgun/railgunstrogg.md3", 
		0, 0, 0},
/* icon */		"icons/iconw_railgun",
/* pickup */	"Rail Gun",
		10,
		IT_WEAPON2,
		WP_MALEDICTION2,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED weapon_strogg_plasmagun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_strogg_plasmagun", 
		"sound/misc/w_pkup.wav",
        { "models/weapons5/plasma/plasmastrogg.md3", 
		0, 0, 0},
/* icon */		"icons/iconw_plasma",
/* pickup */	"Hyper Blaster",
		50,
		IT_WEAPON2,
		WP_EXECUTIONER2,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED weapon_strogg_bfg (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_strogg_bfg",
		"sound/misc/w_pkup.wav",
        { "models/weapons5/bfg/bfgstrogg.md3", 
		0, 0, 0},
/* icon */		"icons/iconw_bfg",
/* pickup */	"BFG10K",
		20,
		IT_WEAPON2,
		WP_BFG10K,
/* precache */ "",
/* sounds */ ""
	},

#ifdef USE_GRAPPLE
/*QUAKED weapon_strogg_grapplinghook (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_strogg_grapple",
		"sound/misc/w_pkup.wav",
        { "models/weapons5/grapple/grapple.md3", 
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

/*QUAKED ammo_strogg_shells (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"ammo_strogg_shells",
		"sound/misc/am_pkup.wav",
        { "models/powerups5/ammo/shotgunamstrogg.md3", 
		0, 0, 0},
/* icon */		"icons/icona_shotgun",
/* pickup */	"Shells",
		10,
		IT_AMMO2,
		WP_TRESPASSER2,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED ammo_strogg_bullets (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"ammo_strogg_bullets",
		"sound/misc/am_pkup.wav",
        { "models/powerups5/ammo/machinegunamstrogg.md3", 
		0, 0, 0},
/* icon */		"icons/icona_machinegun",
/* pickup */	"Bullets",
		50,
		IT_AMMO2,
		WP_STEPCHILD2,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED ammo_strogg_grenades (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"ammo_strogg_grenades",
		"sound/misc/am_pkup.wav",
        { "models/powerups5/ammo/grenadeamstrogg.md3", 
		0, 0, 0},
/* icon */		"icons/icona_grenade",
/* pickup */	"Grenades",
		5,
		IT_AMMO2,
		WP_JOKER2,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED ammo_strogg_cells (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"ammo_strogg_cells",
		"sound/misc/am_pkup.wav",
        { "models/powerups5/ammo/plasmaamstrogg.md3", 
		0, 0, 0},
/* icon */		"icons/icona_plasma",
/* pickup */	"Cells",
		30,
		IT_AMMO2,
		WP_EXECUTIONER2,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED ammo_strogg_rockets (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"ammo_strogg_rockets",
		"sound/misc/am_pkup.wav",
        { "models/powerups5/ammo/rocketamstrogg.md3", 
		0, 0, 0},
/* icon */		"icons/icona_rocket",
/* pickup */	"Rockets",
		5,
		IT_AMMO2,
		WP_PEACEMAKER2,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED ammo_strogg_slugs (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"ammo_strogg_slugs",
		"sound/misc/am_pkup.wav",
        { "models/powerups5/ammo/railgunamstrogg.md3", 
		0, 0, 0},
/* icon */		"icons/icona_railgun",
/* pickup */	"Slugs",
		10,
		IT_AMMO2,
		WP_MALEDICTION2,
/* precache */ "",
/* sounds */ ""
	},

	//
	// HOLDABLE ITEMS
	//
/*QUAKED holdable_strogg_teleporter (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"holdable_strogg_teleporter", 
		"sound/items/holdable.wav",
        { "models/powerups5/holdable/teleporterstrogg.md3", 
		0, 0, 0},
/* icon */		"icons/teleporter",
/* pickup */	"Personal Teleporter",
		60,
		IT_HOLDABLE2,
		HI_TELEPORTER,
/* precache */ "",
/* sounds */ ""
	},
/*QUAKED holdable_strogg_medkit (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"holdable_strogg_medkit", 
		"sound/items/holdable.wav",
        { 
		"models/powerups5/holdable/medkitstrogg.md3", 
		"models/powerups5/holdable/medkit_spherestrogg.md3",
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
/*QUAKED item_strogg_quad (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_strogg_quad", 
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

/*QUAKED item_strogg_enviro (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_strogg_enviro",
		"sound/items/protect.wav",
        { "models/powerups5/instant/envirostrogg.md3", 
		"models/powerups5/instant/enviro_ringstrogg.md3", 
		0, 0 },
/* icon */		"icons/envirosuit",
/* pickup */	"Invulnerability",
		30,
		IT_POWERUP2,
		PW_BATTLESUIT,
/* precache */ "",
/* sounds */ "sound/items/airout.wav sound/items/protect3.wav"
	},

/*QUAKED item_strogg_haste (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_strogg_haste",
		"sound/items/haste.wav",
        { "models/powerups5/instant/hastestrogg.md3", 
		"models/powerups5/instant/haste_ringstrogg.md3", 
		0, 0 },
/* icon */		"icons/haste",
/* pickup */	"Speed",
		30,
		IT_POWERUP2,
		PW_HASTE,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED item_strogg_invis (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_strogg_invis",
		"sound/items/invisibility.wav",
        { "models/powerups5/instant/invisstrogg.md3", 
		"models/powerups5/instant/invis_ringstrogg.md3", 
		0, 0 },
/* icon */		"icons/invis",
/* pickup */	"Invisibility",
		30,
		IT_POWERUP2,
		PW_INVIS,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED item_strogg_regen (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_strogg_regen",
		"sound/items/regeneration.wav",
        { "models/powerups5/instant/regenstrogg.md3", 
		"models/powerups5/instant/regen_ringstrogg.md3", 
		0, 0 },
/* icon */		"icons/regen",
/* pickup */	"Regeneration",
		30,
		IT_POWERUP2,
		PW_REGEN,
/* precache */ "",
/* sounds */ "sound/items/regen.wav"
	},

/*QUAKED item_strogg_flight (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_strogg_flight",
		"sound/items/flight.wav",
        { "models/powerups5/instant/flightstrogg.md3", 
		"models/powerups5/instant/flight_ringstrogg.md3", 
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
		"team_strogg_CTF_redflag",
		NULL,
        { "models/flags/r_flagstrogg.md3",
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
		"team_strogg_CTF_blueflag",
		NULL,
        { "models/flags/b_flagstrogg.md3",
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
  "holdable_strogg_vengeance", 
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

