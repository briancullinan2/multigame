


	//
	// ARMOR
	//

/*QUAKED item_slip_armor_shard (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_slip_armor_shard", 
		"sound/misc/ar1_pkup.wav",
		{ "models/powerups5/armor/shardslip.md3", 
		"models/powerups5/armor/shard_sphereslip.md3",
		0, 0} ,
/* icon */		"icons/iconr_shard",
/* pickup */	"Armor Shard",
		5,
		IT_ARMOR,
		0,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED item_slip_armor_combat (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_slip_armor", 
		"sound/misc/ar2_pkup.wav",
        { "models/powerups5/armor/armor_yellowslip.md3",
		0, 0, 0},
/* icon */		"icons/iconr_yellow",
/* pickup */	"Green Armor",
		100,
		IT_ARMOR,
		0,
/* precache */ "",
/* sounds */ "",
		{"models/powerups5/armor/armor_yellowslip.skin%hue0.15", 0, 0, 0}
	},

/*QUAKED item_slip_armor_combat (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_slip_armor_combat", 
		"sound/misc/ar2_pkup.wav",
        { "models/powerups5/armor/armor_yellowslip.md3",
		0, 0, 0},
/* icon */		"icons/iconr_yellow",
/* pickup */	"Yellow Armor",
		150,
		IT_ARMOR,
		0,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED item_slip_armor_body (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_slip_armor_body", 
		"sound/misc/ar2_pkup.wav",
        { "models/powerups5/armor/armor_redslip.md3",
		0, 0, 0},
/* icon */		"icons/iconr_red",
/* pickup */	"Red Armor",
		200,
		IT_ARMOR,
		0,
/* precache */ "",
/* sounds */ "",
//		"models/powerups5/armor/armor_red.skin%rainbow"
	},

	//
	// health
	//
/*QUAKED item_slip_health_small (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_slip_health_small",
		"sound/items/s_health.wav",
        { "models/powerups5/health/small_crossslip.md3", 
		"models/powerups5/health/small_sphereslip.md3", 
		0, 0 },
/* icon */		"icons/iconh_green",
/* pickup */	"5 Health",
		5,
		IT_HEALTH,
		0,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED item_slip_health (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_slip_health",
		"sound/items/n_health.wav",
        { "models/powerups5/health/medium_crossslip.md3", 
		"models/powerups5/health/medium_sphereslip.md3", 
		0, 0 },
/* icon */		"icons/iconh_yellow",
/* pickup */	"25 Health",
		25,
		IT_HEALTH,
		0,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED item_slip_health_large (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_slip_health_large",
		"sound/items/l_health.wav",
        { "models/powerups5/health/large_crossslip.md3", 
		"models/powerups5/health/large_sphereslip.md3", 
		0, 0 },
/* icon */		"icons/iconh_red",
/* pickup */	"50 Health",
		50,
		IT_HEALTH,
		0,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED item_slip_health_mega (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_slip_health_mega",
		"sound/items/m_health.wav",
        { "models/powerups5/health/mega_crossslip.md3", 
		"models/powerups5/health/mega_sphereslip.md3", 
		0, 0 },
/* icon */		"icons/iconh_mega",
/* pickup */	"Mega Health",
		100,
		IT_HEALTH,
		0,
/* precache */ "",
/* sounds */ ""
	},


	//
	// WEAPONS 
	//

/*QUAKED weapon_slip_gauntlet (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_slip_axe", 
		"sound/misc/w_pkup.wav",
        { "models/weapons5/gauntlet/gauntletslip.md3",
		0, 0, 0},
/* icon */		"icons/iconw_gauntlet",
/* pickup */	"Axe",
		0,
		IT_WEAPON,
		WP_AXE,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED weapon_slip_shotgun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_slip_shotgun", 
		"sound/misc/w_pkup.wav",
        { "models/weapons5/shotgun/shotgunslip.md3", 
		0, 0, 0},
/* icon */		"icons/iconw_shotgun",
/* pickup */	"Double Barrel",
		10,
		IT_WEAPON,
		WP_MARAUDER,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED weapon_slip_machinegun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_slip_machinegun", 
		"sound/misc/w_pkup.wav",
        { "models/weapons5/machinegun/machinegunslip.md3", 
		0, 0, 0},
/* icon */		"icons/iconw_machinegun",
/* pickup */	"Oscillator",
		40,
		IT_WEAPON,
		WP_OSCILLATOR,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED weapon_slip_grenadelauncher (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_slip_grenadelauncher",
		"sound/misc/w_pkup.wav",
        { "models/weapons5/grenadel/grenadelslip.md3", 
		0, 0, 0},
/* icon */		"icons/iconw_grenade",
/* pickup */	"Trailblazer",
		10,
		IT_WEAPON,
		WP_TRAILBLAZER,
/* precache */ "",
/* sounds */ "sound/weapons/grenade/hgrenb1a.wav sound/weapons/grenade/hgrenb2a.wav"
	},

/*QUAKED weapon_slip_rocketlauncher (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_slip_rocketlauncher",
		"sound/misc/w_pkup.wav",
        { "models/weapons5/rocketl/rocketlslip.md3", 
		0, 0, 0},
/* icon */		"icons/iconw_rocket",
/* pickup */	"Rocket Launcher",
		10,
		IT_WEAPON,
		WP_ORIGINAL,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED weapon_slip_lightning (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_slip_lightning", 
		"sound/misc/w_pkup.wav",
        { "models/weapons5/lightning/lightningslip.md3", 
		0, 0, 0},
/* icon */		"icons/iconw_lightning",
/* pickup */	"Thunderbolt",
		100,
		IT_WEAPON,
		WP_THUNDERBOLT,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED weapon_slip_plasmagun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"weapon_slip_nailgun", 
		"sound/misc/w_pkup.wav",
        { "models/weapons5/plasma/plasmaslip.md3", 
		0, 0, 0},
/* icon */		"icons/iconw_plasma",
/* pickup */	"Super Nailgun",
		50,
		IT_WEAPON,
		WP_NAILGUN4,
/* precache */ "",
/* sounds */ ""
	},

	//
	// AMMO ITEMS
	//

/*QUAKED ammo_slip_shells (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"ammo_slip_shells",
		"sound/misc/am_pkup.wav",
        { "models/powerups5/ammo/shotgunamslip.md3", 
		0, 0, 0},
/* icon */		"icons/icona_shotgun",
/* pickup */	"Shells",
		10,
		IT_AMMO,
		WP_MARAUDER,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED ammo_slip_bullets (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"ammo_slip_bullets",
		"sound/misc/am_pkup.wav",
        { "models/powerups5/ammo/machinegunamslip.md3", 
		0, 0, 0},
/* icon */		"icons/icona_machinegun",
/* pickup */	"Bullets",
		50,
		IT_AMMO,
		WP_OSCILLATOR,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED ammo_slip_cells (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"ammo_slip_nails",
		"sound/misc/am_pkup.wav",
        { "models/powerups5/ammo/plasmaamslip.md3", 
		0, 0, 0},
/* icon */		"icons/icona_plasma",
/* pickup */	"Nails",
		30,
		IT_AMMO,
		WP_NAILGUN4,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED ammo_slip_lightning (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"ammo_slip_lightning",
		"sound/misc/am_pkup.wav",
        { "models/powerups5/ammo/lightningamslip.md3", 
		0, 0, 0},
/* icon */		"icons/icona_lightning",
/* pickup */	"Lightning",
		60,
		IT_AMMO,
		WP_THUNDERBOLT,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED ammo_slip_rockets (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"ammo_slip_rockets",
		"sound/misc/am_pkup.wav",
        { "models/powerups5/ammo/rocketamslip.md3", 
		0, 0, 0},
/* icon */		"icons/icona_rocket",
/* pickup */	"Rockets",
		5,
		IT_AMMO,
		WP_ORIGINAL,
/* precache */ "",
/* sounds */ ""
	},

	//
	// HOLDABLE ITEMS
	//

/*QUAKED holdable_slip_medkit (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"holdable_slip_medkit", 
		"sound/items/holdable.wav",
        { 
		"models/powerups5/holdable/medkitslip.md3", 
		"models/powerups5/holdable/medkit_sphereslip.md3",
		0, 0},
/* icon */		"icons/medkit",
/* pickup */	"Medkit",
		60,
		IT_HOLDABLE,
		HI_MEDKIT,
/* precache */ "",
/* sounds */ "sound/items/use_medkit.wav"
	},

	//
	// POWERUP ITEMS
	//
/*QUAKED item_slip_quad (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_slip_quad", 
		"sound/items/quaddamage.wav",
        { "models/powerups5/instant/quad.md3", 
        "models/powerups5/instant/quad_ring.md3",
		0, 0 },
/* icon */		"icons/quad",
/* pickup */	"Quad Damage",
		30,
		IT_POWERUP,
		PW_QUAD,
/* precache */ "",
/* sounds */ "sound/items/damage2.wav sound/items/damage3.wav"
	},

/*QUAKED item_slip_enviro (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_slip_enviro",
		"sound/items/protect.wav",
        { "models/powerups5/instant/enviroslip.md3", 
		"models/powerups5/instant/enviro_ringslip.md3", 
		0, 0 },
/* icon */		"icons/envirosuit",
/* pickup */	"Battle Suit",
		30,
		IT_POWERUP,
		PW_BATTLESUIT,
/* precache */ "",
/* sounds */ "sound/items/airout.wav sound/items/protect3.wav"
	},

/*QUAKED item_slip_haste (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_slip_haste",
		"sound/items/haste.wav",
        { "models/powerups5/instant/hasteslip.md3", 
		"models/powerups5/instant/haste_ringslip.md3", 
		0, 0 },
/* icon */		"icons/haste",
/* pickup */	"Speed",
		30,
		IT_POWERUP,
		PW_HASTE,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED item_slip_invis (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_slip_invis",
		"sound/items/invisibility.wav",
        { "models/powerups5/instant/invisslip.md3", 
		"models/powerups5/instant/invis_ringslip.md3", 
		0, 0 },
/* icon */		"icons/invis",
/* pickup */	"Invisibility",
		30,
		IT_POWERUP,
		PW_INVIS,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED item_slip_regen (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_slip_regen",
		"sound/items/regeneration.wav",
        { "models/powerups5/instant/regenslip.md3", 
		"models/powerups5/instant/regen_ringslip.md3", 
		0, 0 },
/* icon */		"icons/regen",
/* pickup */	"Regeneration",
		30,
		IT_POWERUP,
		PW_REGEN,
/* precache */ "",
/* sounds */ "sound/items/regen.wav"
	},

/*QUAKED item_slip_flight (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
	{
		"item_slip_flight",
		"sound/items/flight.wav",
        { "models/powerups5/instant/flightslip.md3", 
		"models/powerups5/instant/flight_ringslip.md3", 
		0, 0 },
/* icon */		"icons/flight",
/* pickup */	"Flight",
		60,
		IT_POWERUP,
		PW_FLIGHT,
/* precache */ "",
/* sounds */ "sound/items/flight.wav"
	},

/*QUAKED team_CTF_redflag (1 0 0) (-16 -16 -16) (16 16 16)
Only in CTF games
*/
	{
		"team_slip_CTF_redflag",
		NULL,
        { "models/flags/r_flagslip.md3",
		0, 0, 0 },
/* icon */		"icons/iconf_red1",
/* pickup */	"Red Flag",
		0,
		IT_TEAM,
		PW_REDFLAG,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED team_CTF_blueflag (0 0 1) (-16 -16 -16) (16 16 16)
Only in CTF games
*/
	{
		"team_slip_CTF_blueflag",
		NULL,
        { "models/flags/b_flagslip.md3",
		0, 0, 0 },
/* icon */		"icons/iconf_blu1",
/* pickup */	"Blue Flag",
		0,
		IT_TEAM,
		PW_BLUEFLAG,
/* precache */ "",
/* sounds */ ""
	},

/*QUAKED holdable_kamikaze (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "holdable_slip_vengeance", 
  "sound/items/holdable.wav",
      { "models/powerups5/holdable/vengeance.md3", 
  0, 0, 0},
/* icon */		"icons/kamikaze",
/* pickup */	"Vengeance",
  60,
  IT_HOLDABLE,
  HI_KAMIKAZE,
/* precache */ "",
/* sounds */ "sound/items/kamikazerespawn.wav"
},

