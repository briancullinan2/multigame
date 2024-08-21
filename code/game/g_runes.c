
#include "g_local.h"

void Add_Weapon_Ammo( gentity_t *ent, int weapon, int count );
void Remove_Weapon_Ammo( gentity_t *ent, int weapon, int count );
void Add_Ammo( gentity_t *ent, int weapon, int count );
void Remove_Ammo( gentity_t *ent, int weapon, int count );

#ifdef USE_RUNES

void RuneTimerActions( gentity_t *ent, int msec ) {
	gclient_t	*client;
	client = ent->client;

  if((client->inventory[RUNE_ELECTRIC] 
    && client->ps.ammo[WP_LIGHTNING] < 50
  )) {
    Add_Ammo(ent, WP_LIGHTNING, 1);
  }

  if (client->ps.stats[STAT_ABILITY] < rune_ability.value) {
    if((client->inventory[RUNE_HEALTH] && !client->inventory[HI_MEDKIT])
      || (client->inventory[RUNE_DIVINE] && !client->inventory[HI_KAMIKAZE])) {
      client->ps.stats[STAT_ABILITY]++;
    }
  }

  if(client->ps.stats[STAT_ABILITY] >= rune_ability.value) {
    if(client->inventory[RUNE_HEALTH] && !client->inventory[HI_MEDKIT]) {
      G_GiveItem(ent, HI_MEDKIT);
    }
    if(client->inventory[RUNE_DIVINE] && !client->inventory[HI_KAMIKAZE]) {
      G_GiveItem(ent, HI_KAMIKAZE);
    }
  }

  if (client->ps.stats[STAT_ABILITY] < rune_abilityMin.value) {
    if((client->inventory[RUNE_SHIELD] && !client->inventory[HI_INVULNERABILITY])
      || (client->inventory[RUNE_RECALL] && !client->inventory[HI_TELEPORTER])
      || (client->inventory[RUNE_GRAPPLE] 
      && client->ps.ammo[WP_GRAPPLING_HOOK] < 100
      ) || (client->inventory[RUNE_TORNADO])
    ) {
      client->ps.stats[STAT_ABILITY]++;
    }
  }

  if(client->ps.stats[STAT_ABILITY] >= rune_abilityMin.value) {
    if(client->inventory[RUNE_SHIELD] && !client->inventory[HI_INVULNERABILITY]) {
      G_GiveItem(ent, HI_INVULNERABILITY);
    } else 
    if(client->inventory[RUNE_RECALL] && !client->inventory[HI_PORTAL]) {
      G_GiveItem(ent, HI_PORTAL);
    }
    if(client->inventory[RUNE_GRAPPLE] 
      && client->ps.ammo[WP_GRAPPLING_HOOK] < 100
    ) {
      Add_Ammo(ent, WP_GRAPPLING_HOOK, 100);
    }
  }

  if(ent->client->inventory[RUNE_IMPACT]) {
    gentity_t	*other;
    int			entityList[MAX_GENTITIES];
    int			numListedEntities, e;
    vec3_t		mins, maxs, dir, origin;
    vec3_t bounding = {50, 50, 50};
    Remove_Ammo(ent, WP_LIGHTNING, 5);
    VectorCopy(ent->s.origin, mins);
    VectorCopy(ent->s.origin, maxs);
    VectorSubtract(mins, bounding, mins);
    VectorAdd(maxs, bounding, maxs);
    numListedEntities = trap_EntitiesInBox( mins, maxs, entityList, MAX_GENTITIES );
    for ( e = 0 ; e < numListedEntities ; e++ ) {
      other = &g_entities[entityList[ e ]];

      if (!ent->takedamage) {
        continue;
      }

      VectorSubtract (other->r.currentOrigin, ent->s.origin, dir);
      dir[2] += 24;
      G_Damage( other, NULL, ent, dir, origin, 10000, DAMAGE_RADIUS|DAMAGE_NO_TEAM_PROTECTION, MOD_LV_DISCHARGE );
    }
    // TODO: add event that makes a radius of random lighting bolts like the hammer weapon
  }
}


#endif


