
{
  NULL,
  NULL,
  { NULL,
  NULL,
  0, 0} ,
/* icon */		NULL,
/* pickup */	NULL,
  0,
  0,
  0,
/* precache */ "",
/* sounds */ ""
},	// leave index 0 alone

#include "./bg_misc_armor.h"
#include "./bg_misc_health.h"
#include "./bg_misc_weapons.h"
#include "./bg_misc_ammo.h"
#include "./bg_misc_items.h"
#include "./bg_misc_powerups.h"

#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS)
#include "./bg_misc_mp.h"
#endif

#include "./bg_misc_weapons3.h"
//#include "./bg_misc_weapons4.h"
#include "./bg_misc_ammo2.h"

#ifdef USE_ADVANCED_ITEMS
#include "./bg_misc_items2.h"
#ifdef USE_RUNES
#include "./bg_misc_runes.h"
#endif
#endif

#ifdef USE_ADVANCED_CLASS
#include "./bg_misc_gen_earth.h"
#include "./bg_misc_gen_strogg.h"
#include "./bg_misc_gen_slip.h"
#include "./bg_misc_gen_doom.h"
#endif

