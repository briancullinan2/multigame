
//
// HOLDABLE ITEMS
//
/*QUAKED holdable_teleporter (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "holdable_teleporter", 
  "sound/items/holdable.wav",
      { "models/powerups/holdable/teleporter.md3", 
  0, 0, 0},
/* icon */		"icons/teleporter",
/* pickup */	"Personal Teleporter",
  60,
  IT_HOLDABLE,
  HI_TELEPORTER,
/* precache */ "",
/* sounds */ ""
},
/*QUAKED holdable_medkit (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "holdable_medkit", 
  "sound/items/holdable.wav",
      { 
  "models/powerups/holdable/medkit.md3", 
  "models/powerups/holdable/medkit_sphere.md3",
  0, 0},
/* icon */		"icons/medkit",
/* pickup */	"Medkit",
  60,
  IT_HOLDABLE,
  HI_MEDKIT,
/* precache */ "",
/* sounds */ "sound/items/use_medkit.wav"
},
