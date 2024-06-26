
//
// health
//
/*QUAKED item_health_small (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "item_health_small",
  "sound/items/s_health.wav",
      { "models/powerups/health/small_cross.md3", 
  "models/powerups/health/small_sphere.md3", 
  0, 0 },
/* icon */		"icons/iconh_green",
/* pickup */	"5 Health",
  5,
  IT_HEALTH,
  0,
/* precache */ "",
/* sounds */ ""
},

/*QUAKED item_health (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "item_health",
  "sound/items/n_health.wav",
      { "models/powerups/health/medium_cross.md3", 
  "models/powerups/health/medium_sphere.md3", 
  0, 0 },
/* icon */		"icons/iconh_yellow",
/* pickup */	"25 Health",
  25,
  IT_HEALTH,
  0,
/* precache */ "",
/* sounds */ ""
},

/*QUAKED item_health_large (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "item_health_large",
  "sound/items/l_health.wav",
      { "models/powerups/health/large_cross.md3", 
  "models/powerups/health/large_sphere.md3", 
  0, 0 },
/* icon */		"icons/iconh_red",
/* pickup */	"50 Health",
  50,
  IT_HEALTH,
  0,
/* precache */ "",
/* sounds */ ""
},

/*QUAKED item_health_mega (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "item_health_mega",
  "sound/items/m_health.wav",
      { "models/powerups/health/mega_cross.md3", 
  "models/powerups/health/mega_sphere.md3", 
  0, 0 },
/* icon */		"icons/iconh_mega",
/* pickup */	"Mega Health",
  100,
  IT_HEALTH,
  0,
/* precache */ "",
/* sounds */ ""
},
