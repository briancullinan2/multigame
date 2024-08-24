
#include "g_local.h"

void Add_Weapon_Ammo( gentity_t *ent, int weapon, int count );
void Remove_Weapon_Ammo( gentity_t *ent, int weapon, int count );
void Add_Ammo( gentity_t *ent, int weapon, int count );
void Remove_Ammo( gentity_t *ent, int weapon, int count );
void G_GiveHoldable(gentity_t *ent, holdable_t pw);

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
      client->ps.stats[STAT_ABILITY]++;
    }

    if(client->ps.stats[STAT_ABILITY] >= g_ability.value) {
      if((client->pers.playerclass == PCLASS_RANGER
        || (client->pers.playerclass >= PCLASS_MONSTER
        && client->pers.playerclass <= PCLASS_MONSTER_COUNT)) 
        && client->ps.stats[STAT_HOLDABLE_ITEM] != HI_TELEPORTER
      ) {
        G_GiveHoldable(ent, HI_TELEPORTER);
        client->ps.stats[STAT_ABILITY] = 0;
      }

      if(client->pers.playerclass == PCLASS_SHAMBLER
        && client->ps.ammo[WP_LIGHTNING] < 40) {
        Add_Ammo(ent, WP_LIGHTNING, 50);
      }
    }
  }
#endif

}


#endif

