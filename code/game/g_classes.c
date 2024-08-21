
#include "g_local.h"

void Add_Weapon_Ammo( gentity_t *ent, int weapon, int count );
void Remove_Weapon_Ammo( gentity_t *ent, int weapon, int count );
void Add_Ammo( gentity_t *ent, int weapon, int count );
void Remove_Ammo( gentity_t *ent, int weapon, int count );
void G_GiveItem(gentity_t *ent, powerup_t pw);

#if defined(USE_RPG_STATS) || defined(USE_ADVANCED_CLASS) || defined(USE_RUNES)

void ClassTimerActions( gentity_t *ent, int msec ) {
	gclient_t	*client;
	client = ent->client;

  if(!( client->pers.cmd.buttons & BUTTON_WALKING )
    && (client->pers.cmd.forwardmove != 0 || client->pers.cmd.rightmove != 0 || client->pers.cmd.upmove > 0)
    && client->ps.stats[STAT_STAMINA] > 0) {
    client->ps.stats[STAT_STAMINA] -= 10;
  } else if (client->ps.stats[STAT_STAMINA] < 100) {
    client->ps.stats[STAT_STAMINA] += 10;
  }

#if defined(USE_ADVANCED_CLASS)
  if(g_ability.integer > 0) {
      
    if (client->ps.stats[STAT_ABILITY] < g_ability.value) {
      if(client->pers.playerclass == PCLASS_RANGER
        && client->ps.stats[STAT_HOLDABLE_ITEM] != HI_TELEPORTER
      ) {
        client->ps.stats[STAT_ABILITY]++;
      }
      if(client->pers.playerclass == PCLASS_VISOR) {
        client->ps.stats[STAT_ABILITY]++;
      }
    }

    if(client->ps.stats[STAT_ABILITY] >= g_ability.value) {
      if(client->pers.playerclass == PCLASS_RANGER 
        && client->ps.stats[STAT_HOLDABLE_ITEM] != HI_TELEPORTER
      ) {
        G_GiveItem(ent, HI_TELEPORTER);
        client->ps.stats[STAT_ABILITY] = 0;
      }
    }
  }
#endif

}


#endif


