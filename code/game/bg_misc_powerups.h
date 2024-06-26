
//
// POWERUP ITEMS
//
/*QUAKED item_quad (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "item_quad", 
  "sound/items/quaddamage.wav",
      { "models/powerups/instant/quad.md3", 
      "models/powerups/instant/quad_ring.md3",
  0, 0 },
/* icon */		"icons/quad",
/* pickup */	"Quad Damage",
  30,
  IT_POWERUP,
  PW_QUAD,
/* precache */ "",
/* sounds */ "sound/items/damage2.wav sound/items/damage3.wav"
},

/*QUAKED item_enviro (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "item_enviro",
  "sound/items/protect.wav",
      { "models/powerups/instant/enviro.md3", 
  "models/powerups/instant/enviro_ring.md3", 
  0, 0 },
/* icon */		"icons/envirosuit",
/* pickup */	"Battle Suit",
  30,
  IT_POWERUP,
  PW_BATTLESUIT,
/* precache */ "",
/* sounds */ "sound/items/airout.wav sound/items/protect3.wav"
},

/*QUAKED item_haste (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "item_haste",
  "sound/items/haste.wav",
      { "models/powerups/instant/haste.md3", 
  "models/powerups/instant/haste_ring.md3", 
  0, 0 },
/* icon */		"icons/haste",
/* pickup */	"Speed",
  30,
  IT_POWERUP,
  PW_HASTE,
/* precache */ "",
/* sounds */ ""
},

/*QUAKED item_invis (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "item_invis",
  "sound/items/invisibility.wav",
      { "models/powerups/instant/invis.md3", 
  "models/powerups/instant/invis_ring.md3", 
  0, 0 },
/* icon */		"icons/invis",
/* pickup */	"Invisibility",
  30,
  IT_POWERUP,
  PW_INVIS,
/* precache */ "",
/* sounds */ ""
},

/*QUAKED item_regen (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "item_regen",
  "sound/items/regeneration.wav",
      { "models/powerups/instant/regen.md3", 
  "models/powerups/instant/regen_ring.md3", 
  0, 0 },
/* icon */		"icons/regen",
/* pickup */	"Regeneration",
  30,
  IT_POWERUP,
  PW_REGEN,
/* precache */ "",
/* sounds */ "sound/items/regen.wav"
},

/*QUAKED item_flight (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "item_flight",
  "sound/items/flight.wav",
      { "models/powerups/instant/flight.md3", 
  "models/powerups/instant/flight_ring.md3", 
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
  "team_CTF_redflag",
  NULL,
      { "models/flags/r_flag.md3",
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
  "team_CTF_blueflag",
  NULL,
      { "models/flags/b_flag.md3",
  0, 0, 0 },
/* icon */		"icons/iconf_blu1",
/* pickup */	"Blue Flag",
  0,
  IT_TEAM,
  PW_BLUEFLAG,
/* precache */ "",
/* sounds */ ""
},
