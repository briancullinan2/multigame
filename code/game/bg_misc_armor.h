
//
// ARMOR
//

/*QUAKED item_armor_shard (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "item_armor_shard", 
  "sound/misc/ar1_pkup.wav",
  { "models/powerups/armor/shard.md3", 
  "models/powerups/armor/shard_sphere.md3",
  0, 0} ,
/* icon */		"icons/iconr_shard",
/* pickup */	"Armor Shard",
  5,
  IT_ARMOR,
  0,
/* precache */ "",
/* sounds */ ""
},

/*QUAKED item_armor_combat (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "item_armor_combat", 
  "sound/misc/ar2_pkup.wav",
      { "models/powerups/armor/armor_yel.md3",
  0, 0, 0},
/* icon */		"icons/iconr_yellow",
/* pickup */	"Armor",
  50,
  IT_ARMOR,
  0,
/* precache */ "",
/* sounds */ ""
},

/*QUAKED item_armor_body (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "item_armor_body", 
  "sound/misc/ar2_pkup.wav",
      { "models/powerups/armor/armor_red.md3",
  0, 0, 0},
/* icon */		"icons/iconr_red",
/* pickup */	"Heavy Armor",
  100,
  IT_ARMOR,
  0,
/* precache */ "",
/* sounds */ ""
},
