
#ifdef USE_PORTALS
#ifndef MISSIONPACK

/*QUAKED holdable_portal (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "holdable_portal", 
  "sound/items/holdable.wav",
      { "models/powerups/holdable/porter.md3",
  0, 0, 0},
/* icon */		"icons/portal",
/* pickup */	"Portal",
  60,
  IT_HOLDABLE,
  HI_PORTAL,
/* precache */ "",
/* sounds */ ""
},

#endif
#endif


#if defined(MISSIONPACK)

/*QUAKED holdable_kamikaze (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "holdable_kamikaze", 
  "sound/items/holdable.wav",
      { "models/powerups/kamikazi.md3", 
  0, 0, 0},
/* icon */		"icons/kamikaze",
/* pickup */	"Kamikaze",
  60,
  IT_HOLDABLE,
  HI_KAMIKAZE,
/* precache */ "",
/* sounds */ "sound/items/kamikazerespawn.wav"
},

/*QUAKED holdable_portal (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "holdable_portal", 
  "sound/items/holdable.wav",
      { "models/powerups/holdable/porter.md3",
  0, 0, 0},
/* icon */		"icons/portal",
/* pickup */	"Portal",
  60,
  IT_HOLDABLE,
  HI_PORTAL,
/* precache */ "",
/* sounds */ ""
},

/*QUAKED holdable_invulnerability (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "holdable_invulnerability", 
  "sound/items/holdable.wav",
      { "models/powerups/holdable/invulnerability.md3", 
  0, 0, 0},
/* icon */		"icons/invulnerability",
/* pickup */	"Invulnerability",
  60,
  IT_HOLDABLE,
  HI_INVULNERABILITY,
/* precache */ "",
/* sounds */ ""
},

//
// PERSISTANT POWERUP ITEMS
//
/*QUAKED item_scout (.3 .3 1) (-16 -16 -16) (16 16 16) suspended redTeam blueTeam
*/
{
  "item_scout",
  "sound/items/scout.wav",
      { "models/powerups/scout.md3", 
  0, 0, 0 },
/* icon */		"icons/scout",
/* pickup */	"Scout",
  30,
  IT_PERSISTANT_POWERUP,
  PW_SCOUT,
/* precache */ "",
/* sounds */ ""
},

/*QUAKED item_guard (.3 .3 1) (-16 -16 -16) (16 16 16) suspended redTeam blueTeam
*/
{
  "item_guard",
  "sound/items/guard.wav",
      { "models/powerups/guard.md3", 
  0, 0, 0 },
/* icon */		"icons/guard",
/* pickup */	"Guard",
  30,
  IT_PERSISTANT_POWERUP,
  PW_GUARD,
/* precache */ "",
/* sounds */ ""
},

/*QUAKED item_doubler (.3 .3 1) (-16 -16 -16) (16 16 16) suspended redTeam blueTeam
*/
{
  "item_doubler",
  "sound/items/doubler.wav",
      { "models/powerups/doubler.md3", 
  0, 0, 0 },
/* icon */		"icons/doubler",
/* pickup */	"Doubler",
  30,
  IT_PERSISTANT_POWERUP,
  PW_DOUBLER,
/* precache */ "",
/* sounds */ ""
},

/*QUAKED item_doubler (.3 .3 1) (-16 -16 -16) (16 16 16) suspended redTeam blueTeam
*/
{
  "item_ammoregen",
  "sound/items/ammoregen.wav",
      { "models/powerups/ammo.md3",
  0, 0, 0 },
/* icon */		"icons/ammo_regen",
/* pickup */	"Ammo Regen",
  30,
  IT_PERSISTANT_POWERUP,
  PW_AMMOREGEN,
/* precache */ "",
/* sounds */ ""
},

/*QUAKED team_CTF_neutralflag (0 0 1) (-16 -16 -16) (16 16 16)
Only in One Flag CTF games
*/
{
  "team_CTF_neutralflag",
  NULL,
      { "models/flags/n_flag.md3",
  0, 0, 0 },
/* icon */		"icons/iconf_neutral1",
/* pickup */	"Neutral Flag",
  0,
  IT_TEAM,
  PW_NEUTRALFLAG,
/* precache */ "",
/* sounds */ ""
},

{
  "item_redcube",
  "sound/misc/am_pkup.wav",
      { "models/powerups/orb/r_orb.md3",
  0, 0, 0 },
/* icon */		"icons/iconh_rorb",
/* pickup */	"Red Cube",
  0,
  IT_TEAM,
  0,
/* precache */ "",
/* sounds */ ""
},

{
  "item_bluecube",
  "sound/misc/am_pkup.wav",
      { "models/powerups/orb/b_orb.md3",
  0, 0, 0 },
/* icon */		"icons/iconh_borb",
/* pickup */	"Blue Cube",
  0,
  IT_TEAM,
  0,
/* precache */ "",
/* sounds */ ""
},

#endif

#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS)

/*QUAKED ammo_nails (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "ammo_nails",
  "sound/misc/am_pkup.wav",
      { "models/powerups/ammo/nailgunam.md3", 
  0, 0, 0},
/* icon */		"icons/icona_nailgun",
/* pickup */	"Nails",
  20,
  IT_AMMO,
  WP_NAILGUN,
/* precache */ "",
/* sounds */ ""
},

/*QUAKED ammo_mines (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "ammo_mines",
  "sound/misc/am_pkup.wav",
      { "models/powerups/ammo/proxmineam.md3", 
  0, 0, 0},
/* icon */		"icons/icona_proxlauncher",
/* pickup */	"Proximity Mines",
  10,
  IT_AMMO,
  WP_PROX_LAUNCHER,
/* precache */ "",
/* sounds */ ""
},

/*QUAKED ammo_belt (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "ammo_belt",
  "sound/misc/am_pkup.wav",
      { "models/powerups/ammo/chaingunam.md3", 
  0, 0, 0},
/* icon */		"icons/icona_chaingun",
/* pickup */	"Chaingun Belt",
  100,
  IT_AMMO,
  WP_CHAINGUN,
/* precache */ "",
/* sounds */ ""
},


/*QUAKED weapon_nailgun (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "weapon_nailgun", 
  "sound/misc/w_pkup.wav",
      { "models/weapons/nailgun/nailgun.md3", 
  0, 0, 0},
/* icon */		"icons/iconw_nailgun",
/* pickup */	"Nailgun",
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
  "sound/misc/w_pkup.wav",
      { "models/weapons/proxmine/proxmine.md3", 
  0, 0, 0},
/* icon */		"icons/iconw_proxlauncher",
/* pickup */	"Prox Launcher",
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
  "sound/misc/w_pkup.wav",
      { "models/weapons/vulcan/vulcan.md3", 
  0, 0, 0},
/* icon */		"icons/iconw_chaingun",
/* pickup */	"Chaingun",
  80,
  IT_WEAPON,
  WP_CHAINGUN,
/* precache */ "",
/* sounds */ "sound/weapons/vulcan/wvulwind.wav"
},

#endif
