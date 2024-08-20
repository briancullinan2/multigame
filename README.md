# baseq3a

Unofficial Quake III Arena gamecode patch

# What is done:

 * new toolchain used (optimized q3lcc and q3asm)
 * upstream security fixes
 * floatfix
 * fixed vote system
 * fixed spawn system
 * fixed in-game crosshair proportions
 * fixed UI mouse sensitivity for high-resolution
 * fixed server browser + faster scanning
 * new demo UI (subfolders,filtering,sorting)
 * updated serverinfo UI
 * map rotation system
 * unlagged weapons
 * improved prediction
 * damage-based hitsounds
 * colored skins
 * high-quality proportional font renderer
 * single-line cvar declaration, improved cvar code readability and development efficiency

# Documentation

See /docs/

# Compilation and installation

Look in /build/


## Project TODO List:


https://docs.google.com/spreadsheets/d/1oMz7VVQWSyFlkWFYRP3DpU5hqCbojCZBCZCQwq1uOUI/edit?usp=sharing


## Game Features:


A lot of these features can be turned on/off and are marked in code with pre-compiler tags, just like the engine features listed here, [server.md](../docs/server.md) and here, [client.md](../docs/client.md).
These features are included in the games/multigame folder as a fork on baseq3a.
Use `USE_FEATURE=1` with make to enable.

### BUILD_EXPERIMENTAL
Enable experimental features (enabled by default)

### USE_DAMAGE_PLUMS
Damage plums, every time you hit another player, a little floating number appears from the spot you hit them.

![F1](../docs/plums.png?raw=true)

### USE_ITEM_TIMERS
Power-up item timers. Shows how long until power-up respawns.

![F1](../docs/timers.png?raw=true)

### USE_TEAM_VARS
Advanced team-play variables, currently only supports `g_flagReturn`, the number of milliseconds before a flag returns to base after being dropped.

### USE_PHYSICS_VARS
Configurable physics variables, usually transfered from server to client

### USE_SERVER_ROLES
Configurable vote options based on roles.

### USE_REFEREE_CMDS
Allow referees to freeze players/TODO: rebalance teams

### USE_GAME_FREEZETAG
Freezing a player like freeze tag with `\freeze` in the console. TODO: freeze when player dies, optional unfreeze with partial health or gib/respawn when unfrozen.  TODO: referee only, add freezing to game dynamics. TODO: add map triggers to freeze. TODO: treat frozen player like spectator.

![F1](../docs/freeze.png?raw=true)

### USE_CLASSIC_HUD
Loads the standard Q3 hud if the mod is missing a huds.txt file.

### USE_CLASSIC_MENU
Loads the standard Q3 menu if the mod is missing a menus.txt file.

### USE_3D_WEAPONS
Draw 3D weapons that rotate back and forth slightly while your switching weapons.

![F1](../docs/hud.png?raw=true)

### USE_WEAPON_VARS
Weapon vars have the same basic format. `Enable`, `Cycle`, `Damage`, `Splash`, `Radius`, `Speed`, `Time`. The explaination for each setting is below.

Weapons are named as `gaunt`, `machine`, `shotgun`, `grenade`, `rocket`, `plasma`, `rail`, `light`, `bfg`, `grapple`, `nail`, `prox`, `chain`, `flame`.

Combine the weapon words above like `\set wp_bfgEnable 0` to set each combination.

  * Enable - Disable the weapon on the map if the item appears and in the players arsenal.
  * Cycle - How quickly the weapon reloads in between firing each shot.
  * Damage - How much damage the weapon does to the players health with a direct hit.
  * Splash - How much splash damage the explosion does on impact.
  * Radius - The size radius around the impact to diffuse the splash damage.
  * Speed - The projectile speed.
  * Time - Time before the projectile triggers/reacts/auto-explodes.

### USE_WEAPON_ORDER
Advanced weapon switching order for clients to set which weapons upgrade when they pick up.

### USE_WEAPON_CENTER
Allow clients to center the weapon in the middle of the hud instead of using the hand aligned position. TODO: turn off LERPTAG for this and just draw the weapon centered in the middle using weapon->mins/maxs.

### USE_LOCAL_DMG
Advanced Location Damage, hitting a player on specific body parts changes damage amount. Also, slows and breaks legs if you fall too far like UrT.

### USE_GRAVITY_BOOTS
Anti-gravity boots with `\boots` command.

### USE_LADDERS
Ladders surface shader for mapping and loading UrT maps.

### USE_ADVANCED_CLASS
Advanced Player classes, changing starting weapon based on selected character model. TODO: change speed, and how much ammo can be carried.

### USE_LASER_SIGHT
Flashlight and laser commands. TODO: add visual for laser sight like battlefield when you are being targeted right in the eye.

### USE_ADVANCED_ZOOM
Advanced Progressive Zoom stops zooming when the key is up at any zoom level and returns to no zoom the second press.

### USE_ROTATING_DOOR
Rotating doors in maps for UrT support, Quake 2 map support.

### USE_HEADSHOTS
Beheading with headshot detection for Railgun only. Shows a special message and head only big animation.

### USE_ALT_FIRE
Alternate weapon fire, twice as fast POC. Set `\bind mouse2 +button13`.

### USE_CLUSTER_GRENADES
Cluster grenades explodes with grenades in 4 directions after they hit the ground.

### USE_HOMING_MISSILE
Homing rockets look for other player to track and change direction until they explode on impact. They are hard to dodge, but sometimes can get trapped in corridors.

### USE_WEAPON_SPREAD
Spreadfire weapon and powerup mod, sends lots of fire in every direction.

### USE_TRINITY
Unholy Trinity Mode, only starts the player with rocket, rails, lightning and unlimited ammo.

### USE_INSTAGIB
Server-side insta-gib gameplay. Weapons do 1000 times damage only on a direct hit.

### USE_GRAPPLE
Working Grappling Hook. TODO: add bot support. TODO: add to character class like Major only. Anyone can pick up if she drops it.

### USE_ACCEL_RPG
RPG accelerating missiles start slow and then speed up as they fly.

### USE_WEAPON_DROP
### USE_ITEM_DROP
### USE_POWERUP_DROP
### USE_FLAG_DROP
### USE_AMMO_DROP
### USE_ARMOR_DROP
### USE_HEALTH_DROP
Weapon dropping, using the `\drop` command will eject current weapon, eject picked-up items, eject ammo, eject active power-up, eject runes, eject persistent power-ups like guard and returns to their podium at the team base, ejects health orbs in a medic situation.

### USE_BOUNCE_CMD
Allow clients to specify bouncing rockets with the `\bounce` command.

### USE_BOUNCE_RPG
Bouncing rockets bounce off of walls. Can be enabled from map item's SPAWNFLAGS or server enabled.

### USE_BOUNCE_RAIL
Railgun fire bounces off of walls instead of going through them or hitting stopping after the first impact.

### USE_CLOAK_CMD
Infinite invisibility cloak with `\cloak` command.

### USE_LV_DISCHARGE
Lightening-gun discharge that kills players in radius when used in water like Quake 1.

### USE_FLAME_THROWER
Flame thrower. TODO: add model from web like Elon Musks invention

### USE_VORTEX_GRENADES
Vortex Grenades that suck players in when they are tossed. TODO: add vortex visual like warping BFG from Quake 4

### USE_VULN_RPG
Vulnerable missiles, rockets can be shot down mid air.

### USE_INVULN_RAILS
Armor piercing rails, rails that go through walls.

### USE_RUNES
60 different runes with colors, icons, and abilities from the original Rune Quake. TODO: [implement runes](../docs/runes.md).

### USE_MODES_DEATH
More modes of death - ring out takes a point away from the person who falls into the void and gives a point to the last person that did knock-back damage to the player that died (MOD_RING_OUT). "Void death" detection if someone fall a distance and then was killed by a world trigger (MOD_VOID). "from the grave" mode of death - when a grenade goes off and kills another player, after the grenade owner already died (MOD_FROM_GRAVE).

### USE_HOTRPG
Hot rockets do no self-splash damage, infinite rockets, intagib on direct hits.

### USE_HOTBFG
Hot BFG better balance for damage dealt, infinite ammo.

### USE_PORTALS
Portals! Portal power-up can be placed anywhere, ground, mid-air, under water. Portal gun can replace the BFG with left and right click to place a portal on walls. Portal power-up `\give portal` is a free standing portal it will set 2 ends of a portal with the `\use` command. Both ends of free standing portals rotate to always face the camera in the same orientation. Shader portals can specify "world" key in the .map entities and can be used on any mod with the new engine and renderer. ![Portals](../docs/portals.png?raw=true)

### USE_SINGLEPLAYER
Add single player features like earthquakes, player stopping, and animated models.

### USE_MULTIWORLD
Special multiworld features like cameras and portals. See [multiworld](../docs/multiworld.md) for more information.

