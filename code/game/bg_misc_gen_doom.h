

//
// ARMOR
//

/*QUAKED item_doom_armor_shard (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
 */
{
		"item_doom_armor_shard",
		"sound/misc/ar1_pkup.wav",
		{"models/powerups5/armor/sharddoom.md3",
		 "models/powerups5/armor/shard_spheredoom.md3",
		 0, 0},
		/* icon */ "icons/iconr_shard",
		/* pickup */ "Armor Shard",
		5,
		IT_ARMOR2,
		0,
		/* precache */ "",
		/* sounds */ ""},

		/*QUAKED item_doom_armor_combat (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"item_doom_armor_combat",
				"sound/misc/ar2_pkup.wav",
				{"models/powerups5/armor/armor_yellowdoom.md3",
				 0, 0, 0},
				/* icon */ "icons/iconr_yellow",
				/* pickup */ "Armor",
				50,
				IT_ARMOR2,
				0,
				/* precache */ "",
				/* sounds */ ""},

		/*QUAKED item_doom_armor_body (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"item_doom_armor_body",
				"sound/misc/ar2_pkup.wav",
				{"models/powerups5/armor/armor_reddoom.md3",
				 0, 0, 0},
				/* icon */ "icons/iconr_red",
				/* pickup */ "Mega Armor",
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
		/*QUAKED item_doom_health_small (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"item_doom_health_small",
				"sound/items/s_health.wav",
				{"models/powerups5/health/small_crossdoom.md3",
				 "models/powerups5/health/small_spheredoom.md3",
				 0, 0},
				/* icon */ "icons/iconh_green",
				/* pickup */ "Health",
				5,
				IT_HEALTH2,
				0,
				/* precache */ "",
				/* sounds */ ""},

		/*QUAKED item_doom_health (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"item_doom_health",
				"sound/items/n_health.wav",
				{"models/powerups5/health/medium_crossdoom.md3",
				 "models/powerups5/health/medium_spheredoom.md3",
				 0, 0},
				/* icon */ "icons/iconh_yellow",
				/* pickup */ "Stimpack",
				25,
				IT_HEALTH2,
				0,
				/* precache */ "",
				/* sounds */ ""},

		/*QUAKED item_doom_health_large (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"item_doom_health_large",
				"sound/items/l_health.wav",
				{"models/powerups5/health/large_crossdoom.md3",
				 "models/powerups5/health/large_spheredoom.md3",
				 0, 0},
				/* icon */ "icons/iconh_red",
				/* pickup */ "Medkit",
				50,
				IT_HEALTH2,
				0,
				/* precache */ "",
				/* sounds */ ""},

		/*QUAKED item_doom_health_mega (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"item_doom_health_mega",
				"sound/items/m_health.wav",
				{"models/powerups5/health/mega_crossdoom.md3",
				 "models/powerups5/health/mega_spheredoom.md3",
				 0, 0},
				/* icon */ "icons/iconh_mega",
				/* pickup */ "Supercharge",
				100,
				IT_HEALTH2,
				0,
				/* precache */ "",
				/* sounds */ ""},

		//
		// WEAPONS
		//

		/*QUAKED weapon_doom_gauntlet (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"weapon_doom_pistol",
				"sound/misc/w_pkup.wav",
				{"models/weapons5/pistol/pistoldoom.md3",
				 0, 0, 0},
				/* icon */ "icons/iconw_gauntlet",
				/* pickup */ "Pistol",
				0,
				IT_WEAPON2,
				WP_PISTOL,
				/* precache */ "",
				/* sounds */ ""},

		/*QUAKED weapon_doom_shotgun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"weapon_doom_shotgun",
				"sound/misc/w_pkup.wav",
				{"models/weapons5/shotgun/shotgundoom.md3",
				 0, 0, 0},
				/* icon */ "icons/iconw_shotgun",
				/* pickup */ "Shotgun",
				10,
				IT_WEAPON2,
				WP_SHOTGUN3,
				/* precache */ "",
				/* sounds */ ""},

		/*QUAKED weapon_doom_machinegun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"weapon_doom_chainsaw",
				"sound/misc/w_pkup.wav",
				{"models/weapons5/machinegun/machinegundoom.md3",
				 0, 0, 0},
				/* icon */ "icons/iconw_machinegun",
				/* pickup */ "Chainsaw",
				40,
				IT_WEAPON2,
				WP_CHAINSAW3,
				/* precache */ "",
				/* sounds */ ""},

		/*QUAKED weapon_doom_rocketlauncher (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"weapon_doom_rocketlauncher",
				"sound/misc/w_pkup.wav",
				{"models/weapons5/rocketl/rocketldoom.md3",
				 0, 0, 0},
				/* icon */ "icons/iconw_rocket",
				/* pickup */ "Rocket Launcher",
				10,
				IT_WEAPON2,
				WP_ORIGINAL3,
				/* precache */ "",
				/* sounds */ ""},

		/*QUAKED weapon_doom_railgun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"weapon_doom_chaingun",
				"sound/misc/w_pkup.wav",
				{"models/weapons5/lightning/lightningdoom.md3",
				 0, 0, 0},
				/* icon */ "icons/iconw_railgun",
				/* pickup */ "Chaingun",
				10,
				IT_WEAPON2,
				WP_CHAINGUN3,
				/* precache */ "",
				/* sounds */ ""},

		/*QUAKED weapon_doom_plasmagun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"weapon_doom_plasmagun",
				"sound/misc/w_pkup.wav",
				{"models/weapons5/plasma/plasmadoom.md3",
				 0, 0, 0},
				/* icon */ "icons/iconw_plasma",
				/* pickup */ "Plasma Gun",
				50,
				IT_WEAPON2,
				WP_PLASMAGUN3,
				/* precache */ "",
				/* sounds */ ""},

		/*QUAKED weapon_doom_bfg (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"weapon_doom_bfg",
				"sound/misc/w_pkup.wav",
				{"models/weapons5/bfg/bfgdoom.md3",
				 0, 0, 0},
				/* icon */ "icons/iconw_bfg",
				/* pickup */ "BFG9000",
				20,
				IT_WEAPON2,
				WP_BFG9000,
				/* precache */ "",
				/* sounds */ ""},

		//
		// AMMO ITEMS
		//

		/*QUAKED ammo_doom_shells (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"ammo_doom_shells",
				"sound/misc/am_pkup.wav",
				{"models/powerups5/ammo/shotgunamdoom.md3",
				 0, 0, 0},
				/* icon */ "icons/icona_shotgun",
				/* pickup */ "Shells",
				10,
				IT_AMMO2,
				WP_SHOTGUN3,
				/* precache */ "",
				/* sounds */ ""},

		/*QUAKED ammo_doom_bullets (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"ammo_doom_bullets",
				"sound/misc/am_pkup.wav",
				{"models/powerups5/ammo/machinegunamdoom.md3",
				 0, 0, 0},
				/* icon */ "icons/icona_machinegun",
				/* pickup */ "Bullets",
				50,
				IT_AMMO2,
				WP_PISTOL,
				/* precache */ "",
				/* sounds */ ""},

		/*QUAKED ammo_doom_cells (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"ammo_doom_cells",
				"sound/misc/am_pkup.wav",
				{"models/powerups5/ammo/plasmaamdoom.md3",
				 0, 0, 0},
				/* icon */ "icons/icona_plasma",
				/* pickup */ "Cells",
				30,
				IT_AMMO2,
				WP_PLASMAGUN3,
				/* precache */ "",
				/* sounds */ ""},

		/*QUAKED ammo_doom_rockets (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"ammo_doom_rockets",
				"sound/misc/am_pkup.wav",
				{"models/powerups5/ammo/rocketamdoom.md3",
				 0, 0, 0},
				/* icon */ "icons/icona_rocket",
				/* pickup */ "Rockets",
				5,
				IT_AMMO2,
				WP_ORIGINAL3,
				/* precache */ "",
				/* sounds */ ""},

		/*QUAKED ammo_doom_slugs (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"ammo_doom_slugs",
				"sound/misc/am_pkup.wav",
				{"models/powerups5/ammo/railgunamdoom.md3",
				 0, 0, 0},
				/* icon */ "icons/icona_railgun",
				/* pickup */ "Slugs",
				10,
				IT_AMMO2,
				WP_CHAINGUN3,
				/* precache */ "",
				/* sounds */ ""},

		/*QUAKED ammo_doom_bfg (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"ammo_doom_bfg",
				"sound/misc/am_pkup.wav",
				{"models/powerups5/ammo/bfgamdoom.md3",
				 0, 0, 0},
				/* icon */ "icons/icona_bfg",
				/* pickup */ "Bfg Ammo",
				15,
				IT_AMMO2,
				WP_BFG9000,
				/* precache */ "",
				/* sounds */ ""},

		//
		// HOLDABLE ITEMS
		//
		/*QUAKED holdable_doom_teleporter (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"holdable_doom_teleporter",
				"sound/items/holdable.wav",
				{"models/powerups5/holdable/teleporterdoom.md3",
				 0, 0, 0},
				/* icon */ "icons/teleporter",
				/* pickup */ "Personal Teleporter",
				60,
				IT_HOLDABLE2,
				HI_TELEPORTER,
				/* precache */ "",
				/* sounds */ ""},
		/*QUAKED holdable_doom_medkit (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"holdable_doom_medkit",
				"sound/items/holdable.wav",
				{"models/powerups5/holdable/medkitdoom.md3",
				 "models/powerups5/holdable/medkit_spheredoom.md3",
				 0, 0},
				/* icon */ "icons/medkit",
				/* pickup */ "Medkit",
				60,
				IT_HOLDABLE2,
				HI_MEDKIT,
				/* precache */ "",
				/* sounds */ "sound/items/use_medkit.wav"},

		//
		// POWERUP ITEMS
		//
		/*QUAKED item_doom_quad (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"item_doom_quad",
				"sound/items/quaddamage.wav",
				{"models/powerups5/holdable/medkitdoom.md3",
				 0, 0, 0},
				/* icon */ "icons/quad",
				/* pickup */ "Quad Damage",
				30,
				IT_POWERUP2,
				PW_BERSERKER,
				/* precache */ "",
				/* sounds */ "sound/items/damage2.wav sound/items/damage3.wav"},

		/*QUAKED item_doom_enviro (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"item_doom_enviro",
				"sound/items/protect.wav",
				{"models/powerups5/instant/envirodoom.md3",
				 0, 0, 0},
				/* icon */ "icons/envirosuit",
				/* pickup */ "Invulnerability",
				30,
				IT_POWERUP2,
				PW_BATTLESUIT,
				/* precache */ "",
				/* sounds */ "sound/items/airout.wav sound/items/protect3.wav"},

		/*QUAKED item_doom_haste (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"item_doom_haste",
				"sound/items/haste.wav",
				{"models/powerups5/instant/hastedoom.md3",
				 "models/powerups5/instant/haste_ringdoom.md3",
				 0, 0},
				/* icon */ "icons/haste",
				/* pickup */ "Speed",
				30,
				IT_POWERUP2,
				PW_HASTE,
				/* precache */ "",
				/* sounds */ "",
				{NULL, NULL, NULL, NULL},
				{1, 14, 14, 1000/15, 1000/15, 0, 0},
				RF_BILLBOARD},

		/*QUAKED item_doom_invis (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"item_doom_invis",
				"sound/items/invisibility.wav",
				{"models/powerups5/instant/invisdoom.md3",
				 "models/powerups5/instant/invis_ringdoom.md3",
				 0, 0},
				/* icon */ "icons/invis",
				/* pickup */ "Invisibility",
				30,
				IT_POWERUP2,
				PW_INVIS,
				/* precache */ "",
				/* sounds */ ""},

		/*QUAKED item_doom_regen (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"item_doom_regen",
				"sound/items/regeneration.wav",
				{"models/powerups5/instant/regendoom.md3",
				 "models/powerups5/instant/regen_ringdoom.md3",
				 0, 0},
				/* icon */ "icons/regen",
				/* pickup */ "Regeneration",
				30,
				IT_POWERUP2,
				PW_REGEN,
				/* precache */ "",
				/* sounds */ "sound/items/regen.wav"},

		/*QUAKED item_doom_flight (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"item_doom_flight",
				"sound/items/flight.wav",
				{"models/powerups5/instant/flightdoom.md3",
				 "models/powerups5/instant/flight_ringdoom.md3",
				 0, 0},
				/* icon */ "icons/flight",
				/* pickup */ "Flight",
				60,
				IT_POWERUP2,
				PW_FLIGHT,
				/* precache */ "",
				/* sounds */ "sound/items/flight.wav"},

		/*QUAKED team_CTF_redflag (1 0 0) (-16 -16 -16) (16 16 16)
		Only in CTF games
		*/
		{
				"team_doom_CTF_redflag",
				NULL,
				{"models/flags/r_flagdoom.md3",
				 0, 0, 0},
				/* icon */ "icons/iconf_red1",
				/* pickup */ "Red Flag",
				0,
				IT_TEAM2,
				PW_REDFLAG,
				/* precache */ "",
				/* sounds */ ""},

		/*QUAKED team_CTF_blueflag (0 0 1) (-16 -16 -16) (16 16 16)
		Only in CTF games
		*/
		{
				"team_doom_CTF_blueflag",
				NULL,
				{"models/flags/b_flagdoom.md3",
				 0, 0, 0},
				/* icon */ "icons/iconf_blu1",
				/* pickup */ "Blue Flag",
				0,
				IT_TEAM2,
				PW_BLUEFLAG,
				/* precache */ "",
				/* sounds */ ""},

		/*QUAKED holdable_kamikaze (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
		 */
		{
				"holdable_doom_vengeance",
				"sound/items/holdable.wav",
				{"models/powerups5/holdable/vengeance.md3",
				 0, 0, 0},
				/* icon */ "icons/kamikaze",
				/* pickup */ "Vengeance",
				60,
				IT_HOLDABLE2,
				HI_KAMIKAZE,
				/* precache */ "",
				/* sounds */ "sound/items/kamikazerespawn.wav"},
