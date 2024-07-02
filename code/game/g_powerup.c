

#include "g_local.h"


void UsePowerup( gentity_t *ent, powerup_t powerup ) {
	gitem_t *item;
	vec3_t	origin, angles;
	int		i, j;
	gentity_t *drop;
  int itemClass = floor(powerup / PW_MAX_POWERUPS);
  ent->client->inventory[itemClass][powerup % PW_MAX_POWERUPS] = 0;
  ent->client->inventoryModified[itemClass] = qtrue;

  switch(powerup) {
  case HI_TELEPORTER:		// teleporter
    // drop flags in CTF
    item = NULL;
    j = 0;

    if ( ent->client->ps.powerups[ PW_REDFLAG ] ) {
      item = BG_FindItemForPowerup( PW_REDFLAG );
      j = PW_REDFLAG;
    } else if ( ent->client->ps.powerups[ PW_BLUEFLAG ] ) {
      item = BG_FindItemForPowerup( PW_BLUEFLAG );
      j = PW_BLUEFLAG;
#if defined(USE_ADVANCED_GAMES) || defined(USE_ADVANCED_TEAMS)
    } else if ( ent->client->ps.powerups[ PW_GOLDFLAG ] ) {
      item = BG_FindItemForPowerup( PW_GOLDFLAG );
      j = PW_GOLDFLAG;
    } else if ( ent->client->ps.powerups[ PW_GREENFLAG ] ) {
      item = BG_FindItemForPowerup( PW_GREENFLAG );
      j = PW_GREENFLAG;
#endif
    } else if ( ent->client->ps.powerups[ PW_NEUTRALFLAG ] ) {
      item = BG_FindItemForPowerup( PW_NEUTRALFLAG );
      j = PW_NEUTRALFLAG;
    }

    if ( item ) {
      drop = Drop_Item( ent, item, 0 );
      // decide how many seconds it has left
      drop->count = ( ent->client->ps.powerups[ j ] - level.time ) / 1000;
      if ( drop->count < 1 ) {
        drop->count = 1;
      }
      // for pickup prediction
      drop->s.time2 = drop->count;

      ent->client->ps.powerups[ j ] = 0;
    }

#ifdef MISSIONPACK
    if ( g_gametype.integer == GT_HARVESTER ) {
      if ( ent->client->ps.generic1 > 0 ) {
        if ( ent->client->sess.sessionTeam == TEAM_RED ) {
          item = BG_FindItem( "Blue Cube" );
        } else {
          item = BG_FindItem( "Red Cube" );
        }
        if ( item ) {
          for ( j = 0; j < ent->client->ps.generic1; j++ ) {
            drop = Drop_Item( ent, item, 0 );
            if ( ent->client->sess.sessionTeam == TEAM_RED ) {
              drop->spawnflags = TEAM_BLUE;
            } else {
              drop->spawnflags = TEAM_RED;
            }
          }
        }
        ent->client->ps.generic1 = 0;
      }
    }
#endif
    SelectSpawnPoint( ent, ent->client->ps.origin, origin, angles );
    TeleportPlayer( ent, origin, angles );
    break;

  case HI_MEDKIT:		// medkit
    ent->health = ent->client->ps.stats[STAT_MAX_HEALTH] + 25;

    break;

  case HI_KAMIKAZE:		// kamikaze
    // make sure the invulnerability is off
    ent->client->invulnerabilityTime = 0;
    // start the kamikze
    G_StartKamikaze( ent );
    break;

  case HI_INVULNERABILITY:		// invulnerability
    ent->client->invulnerabilityTime = level.time + 10000;
    break;

#ifdef USE_PORTALS
  case HI_PORTAL:		// portal
    if( ent->client->portalID ) {
      DropPortalSource( ent, qfalse );
    }
    else {
      DropPortalDestination( ent, qfalse );
    }
    break;
#endif
  default:
    break;
  }
}

