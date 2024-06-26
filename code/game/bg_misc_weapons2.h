
	//
	// WEAPONS 
	//

	/*QUAKED weapon_gauntlet (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
	 */
	{
		"weapon_gauntlet",
		"sound/misc3/w_pkup.wav",
		{ "models/weapons3/gauntlet/gauntlet.md3",
			NULL, NULL, NULL},
		/* icon */ "icons3/iconw_gauntlet",
		/* pickup */ "Gauntlet",
		0,
		IT_WEAPON,
		WP_GAUNTLET2,
		/* precache */ "",
		/* sounds */ ""
	},

	/*QUAKED weapon_shotgun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
	 */
	{
		"weapon_shotgun",
		"sound/misc3/w_pkup.wav",
		{ "models/weapons3/shotgun/shotgun.md3",
			NULL, NULL, NULL},
		/* icon */ "icons3/iconw_shotgun",
		/* pickup */ "Shotgun",
		10,
		IT_WEAPON,
		WP_SHOTGUN2,
		/* precache */ "",
		/* sounds */ ""
	},

	/*QUAKED weapon_machinegun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
	 */
	{
		"weapon_machinegun",
		"sound/misc3/w_pkup.wav",
		{ "models/weapons3/machinegun/machinegun.md3",
			NULL, NULL, NULL},
		/* icon */ "icons3/iconw_machinegun",
		/* pickup */ "Machinegun",
		40,
		IT_WEAPON,
		WP_MACHINEGUN2,
		/* precache */ "",
		/* sounds */ ""
	},

	/*QUAKED weapon_grenadelauncher (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
	 */
	{
		"weapon_grenadelauncher",
		"sound/misc3/w_pkup.wav",
		{ "models/weapons3/grenadel/grenadel.md3",
			NULL, NULL, NULL},
		/* icon */ "icons3/iconw_grenade",
		/* pickup */ "Grenade Launcher",
		10,
		IT_WEAPON,
		WP_GRENADE_LAUNCHER2,
		/* precache */ "",
		/* sounds */ "sound/weapons/grenade/hgrenb1a.wav sound/weapons/grenade/hgrenb2a.wav"
	},

	/*QUAKED weapon_rocketlauncher (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
	 */
	{
		"weapon_rocketlauncher",
		"sound/misc3/w_pkup.wav",
		{ "models/weapons3/rocketl/rocketl.md3",
			NULL, NULL, NULL},
		/* icon */ "icons3/iconw_rocket",
		/* pickup */ "Rocket Launcher",
		10,
		IT_WEAPON,
		WP_ROCKET_LAUNCHER2,
		/* precache */ "",
		/* sounds */ ""
	},

	/*QUAKED weapon_lightning (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
	 */
	{
		"weapon_lightning",
		"sound/misc3/w_pkup.wav",
		{ "models/weapons3/lightning/lightning.md3",
			NULL, NULL, NULL},
		/* icon */ "icons3/iconw_lightning",
		/* pickup */ "Lightning Gun",
		100,
		IT_WEAPON,
		WP_LIGHTNING2,
		/* precache */ "",
		/* sounds */ ""
	},

	/*QUAKED weapon_railgun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
	 */
	{
		"weapon_railgun",
		"sound/misc3/w_pkup.wav",
		{ "models/weapons3/railgun/railgun.md3",
			NULL, NULL, NULL},
		/* icon */ "icons3/iconw_railgun",
		/* pickup */ "Railgun",
		10,
		IT_WEAPON,
		WP_RAILGUN2,
		/* precache */ "",
		/* sounds */ ""
	},

	/*QUAKED weapon_plasmagun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
	 */
	{
		"weapon_plasmagun",
		"sound/misc3/w_pkup.wav",
		{ "models/weapons3/plasma/plasma.md3",
			NULL, NULL, NULL},
		/* icon */ "icons3/iconw_plasma",
		/* pickup */ "Plasma Gun",
		50,
		IT_WEAPON,
		WP_PLASMAGUN2,
		/* precache */ "",
		/* sounds */ ""
	},

	/*QUAKED weapon_bfg (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
	 */
	{
		"weapon_bfg",
		"sound/misc3/w_pkup.wav",
		{ "models/weapons3/bfg/bfg.md3",
			NULL, NULL, NULL},
		/* icon */ "icons3/iconw_bfg",
		/* pickup */ "BFG10K",
		20,
		IT_WEAPON,
		WP_BFG2,
		/* precache */ "",
		/* sounds */ ""
	},

#if 0

#ifdef USE_GRAPPLE
	/*QUAKED weapon_grapplinghook (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
	 */
	{
		"weapon_grapplinghook",
		"sound/misc3/w_pkup.wav",
		{ "models/weapons3/grapple/grapple.md3",
			NULL, NULL, NULL},
		/* icon */ "icons3/iconw_grapple",
		/* pickup */ "Grappling Hook",
		0,
		IT_WEAPON,
		WP_GRAPPLING_HOOK,
		/* precache */ "",
		/* sounds */ ""
	},
#endif

  /*QUAKED weapon_nailgun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
	 */
  {
		"weapon_nailgun",
		"sound/misc3/w_pkup.wav",
		{ "models/weapons/nailgun/nailgun.md3",
			NULL, NULL, NULL},
		/* icon */ "icons3/iconw_nailgun",
		/* pickup */ "Nailgun",
		10,
		IT_WEAPON,
		WP_NAILGUN,
		/* precache */ "",
		/* sounds */ ""
	},

	/*QUAKED weapon_prox_launcher (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
	 */
	{
		"weapon_prox_launcher",
		"sound/misc3/w_pkup.wav",
		{ "models/weapons/proxmine/proxmine.md3",
			NULL, NULL, NULL},
		/* icon */ "icons3/iconw_proxlauncher",
		/* pickup */ "Prox Launcher",
		5,
		IT_WEAPON,
		WP_PROX_LAUNCHER,
		/* precache */ "",
		/* sounds */ "sound/weapons/proxmine/wstbtick.wav "
		"sound/weapons/proxmine/wstbactv.wav "
		"sound/weapons/proxmine/wstbimpl.wav "
		"sound/weapons/proxmine/wstbimpm.wav "
		"sound/weapons/proxmine/wstbimpd.wav "
		"sound/weapons/proxmine/wstbactv.wav"
	},

	/*QUAKED weapon_chaingun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
	 */
	{
		"weapon_chaingun",
		"sound/misc3/w_pkup.wav",
		{ "models/weapons/vulcan/vulcan.md3",
			NULL, NULL, NULL},
		/* icon */ "icons3/iconw_chaingun",
		/* pickup */ "Chaingun",
		80,
		IT_WEAPON,
		WP_CHAINGUN,
		/* precache */ "",
		/* sounds */ "sound/weapons/vulcan/wvulwind.wav"
	},
#endif
