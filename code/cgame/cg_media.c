#include "cg_local.h"

void CG_RegisterExtraSounds( void ) {

#if defined(USE_GAME_FREEZETAG) || defined(USE_REFEREE_CMDS)
  cgs.media.frozenSound = trap_S_RegisterSound("sound/teamplay/freezing.wav", qfalse);
#endif

}