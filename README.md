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

# TODO:

 * bugfixes
 * add shrinking and growing effects through a limited number of red and blue pill commands
 * ant-man style shrinking where the player doesn't get slower as they get smaller, larger players move slower because of larger metabolisms
 * king of the hill with portals. instead of rounds, levels run continuously, each time a player makes it to first place or hits the score limit, only they are teleported to the next map and the other players remain, the game is won by rotating through all the maps hitting the score limit in each one. kings can move because worlds using interdimensional portals, non-kings get blended.
 * DONE: many many weapons from every other mod, need a handy way to do this with data
 * walking on walls. possible way to implement, load the world in 6 orientations along each axis, then estimate the intersections of each corner
 * puzzles like the one in myst to solve, add EngineOfCreation


## TODO

  * Real auto-sprite for models using portal code but put in renderer and apply with RF_* name. 
  * Use srand() or seeded-random for random looking but synchronized effects.
  * Add radius damage to lighting bolt only in the rain.
  * Add atmospheric effects, smoke and sparks over lava, dust, worldly fog, to old maps.
  * Multiworld camera features
  * Add stray rounds to projectiles
  * Finish portal interpolation, and seeing one portal surface through another portal, projectiles (distance from origin). Share entities between multiple server qagame QVMs, possibly through the engine itself or a new API call for game/g_*.c
  * Finish multiworld TODOs like not crashing after 10 maps and cvars. 
  * Rocket Arena maps. Place white return teleporters for arena 0 on player_start positions and going through a portal counts as a vote to white arena to play in. Or use drop command to drop portal connects and in RA mode return to arena 0. Always spawn in arena 0 during intermission until voted, or remove guns from arena 0 and repawn in voted arena.
  * Add autosprite flag to misc_model for rotating like portal always facing camera
  * Shoot portal gun twice in the same place to fill a specific area of space on the wall for the portal, generating a new portal model to fit the surface. The portal stretches to cover an entire wall. 3 kinds of portals. Shoot again and the portal goes back to small and round. Maximize at an optional 50 x 50 = 2500 area. Somehow visualize morphing from sphere to whole wall. Need to learn how to make meshes.
  * Use geometric content from previous campaigns Q1, Q2, but ruin the ability to speed run (smarter bots, more enemies, team based, disrupting events and puzzles, long missions like Q2 Ground Zero Research Hangar) then create a new mode called shortcuts, where alternate puzzles can be solved to jump through maps quickly.
  * Free standing portals should use gravity for like half a second, to land on the ground correctly, then figure out where the bounding box puts it and maybe add a stand.
  * Make a Doom style Prawler amygdala that you have to kill for in a boss fight to get teleportation abilities.
  * Temporal goggles to see where other players portals are created. Add temporal paths using botlib to show a stream like donny darko where portals lead. Other worlds lead out into space somewhere. Also show the rendering between portals should stretch the world around for a second.
  * Fix portals on walls, possibly using bounce for half a second? Then check for a flat/even surface on at least 4 corners, if it is not on the same plane show the little "portal failure" bubbles where the explosion would have been. At least player movement must be able to handle points, how is it possible to detect holes and other geometry? Disregard irregular vertices completely and hide every vertex within a 100u radius by moving them to 10000 * AngleVectors() to hide an protrusions. Holes will just get covered up or the portal would go through it.
  * Reportedly, Portal the game it is a developer responsibility to specify where portals can be placed, this seems incredibly difficult to me or it was much more linear than I thought (i.e. only one way to solve the puzzle). https://www.youtube.com/watch?v=eNKntZzwnAw
  * Portal has view-axis ROLL turning towards the pull of gravity. Splitgate uses roll, but it is much faster than Portal 1.
  * Add Splitgate style if you go through someone else's portal it is black and unknown, might make for good traps, HAHA!
  * Trigger earthquake from kamikaze.
  * Optional for portals to be for 1 individual player, or any player can go through any players portal. NODRAW and SINGLECLIENT flags to be set.
  * Add auto-regen health shield thing?
  * Fix portal gun.  Use teleporter location to draw entities in relative locations on the other side of the jump.  Use a special flag on teleport to tell it where to interpolate for other players even though EF_TELEPORT_BIT is used, just follow velocity backwards one frame on personal teleporters. Looking through a standing portal has a weird repetitive effect because of depth write or sorting or something. Turn off depth in shader or skip entity in tr_main.c? Measure/cache midpoint of portal model and use on floor and wall alignment. Fix corners by tracing in server for edges. Add NOPORTAL surfaceParm. Still take falling damage for landing on a portal. Projectiles through portals. Face wall portals like 5 degrees towards player away from original angle. No falling damage while holding the portal gun.
  * Teach bots to use portals.
  * Add features to support other map types like Xonotic (warp zones are just automatically centered cameras with some fancy distortion shaders, Quake 1 did not normally have the camera feature) and QueToo (map format?) and Smokin' Guns probably added a surface parm.
  * Add tracer rounds, ammo clip sized packs for reloading, etc.
  * Infinite haste, how is this different than g_speed? Applies to only one player.
  * Boots that can climb steep slopes. 
  * Jump velocity as a part of anti-gravity boots. 
  * Power-ups cover entire body or just the gun setting from server and client setting. 
  * Add player state to UI QVM so multiple cursors can be shared, and players can see map and game configuration.
  * Add walk on walls, better movement than Trem.
  * Live-action minimap, using procedurally generated mini maps, draw small players top-down and glowing like quad damage.
  * Ricochet mode where damage only applies after projectile bounces/splash damage
  * Showing enemy health and armor above their head like an RPG
  * Extra UI menus with multiQVM, for voting on maps and bitcoin setup, Instant replay, consolidate all VM UIs scoreboard/postgame/HUD/menus in to 1 UI system, replace the menu address with an API call.
  * Many mod support, compiling and playing lots of different game types, capture the flag with 3+ teams
  * Campaign mode, playing older engine content and playing as enemy characters, new AI for old enemies
  * Keep away, where one team has to kill the flag carrier and return the flag to score.
  * Add light coming from player to flashlight command so even if you're pointing at the sky it looks like a flashlight is on.
  * Make "tech-demo" as an example of some game dynamic. 
  * DONE: Make a Matrix mod that loads the white loading program 
  * TODO: and jump simulation and UrT subway. Make a space to planet landing sequence with death modes. https://www.youtube.com/watch?v=sLqXFF8mlEU
  * Quake 5 play on the home-worlds of each species, but in a mistakenly massive defeat of stop the Arenas on Vadrigas, they've expanded to each home world.
  * 2001 Space Odyssey to meet VEGA aka HAL aka SKYNET
  * quake team racing, like crash team racing with a car power up
  * add level loading lobbies poke the old crash bandicoot gamea
  * use it as a game bowrd for dungeons and drangons and model scenese and entities for dnd players
  * model the entire city of flagstaff as a metaverse proof of concept
  * remove weapons from 0 and replace with hand base melee attack, good for matcbing tremulous
  * vehicle power ups with origin in model for cockpit
  * finish seamless portals between worlds
  * turn maze generator into a proper dungeon generator now with working geometries included as models entiee rooms can be referenced by shape, calculated and aligned automatically
  * make a simpsons spin off but include and entire neighborhood of portals into even bigger spaces
  * make a portal in this tree woolands area
  * use camera based portals for a 4 person map but make it clever
  * add scene lights to portals
  * grab some alice and star wars content to test with multiworld portals particularly for teleports
 

  
  * Playing split screen across the network for team based games where you might've been playing next to each other so you can watch your teammate.
  * automatically generate the rest of team assets like colors players using dynamic skins
  * LookAtKiller and LookAheadOf for aimbot powerup
  * DONE: Add spawn point as a target for homing missiles if there are no other players, 
  * TODO: add homing plasma, homing bullets, homing bfg, etc
  * TODO: zombies can't be killed again, immortal, but also walk very slowly, half speed
  * TODO: in the spirit of lame bot code, all the cyborgs should get depth hack powerup after their stamina recharges
  * DONE: add stamina that forces the player to walk instead of run, 
  * TODO: and double stamina, or double the charge time they get a special class based powerup to use, "HOLDABLE_GIVE"ETC
  * TODO: make multiplayer monsters like the new Doom game where you can play as the monster with special powers instead of weapons.
  * TODO: add special ability powerups like Sarge can teleport in Quake Champions after waiting for a minute
  * TODO: dragon with quad damage has blue/purple flame like Gozilla
  * TODO: vampire mode where all life forms that "die" respawn exactly as they were before the attack in the same place, temporary ghost shader for respawn timeout time, then popping back in, they can move as a ghost, just like spectators. i think world of warcraft had this feature but you lose equipment in the process and there might have been specific areas you must return to in order to respawn from the spirit realm.


# Documentation

See /docs/

# Compilation and installation

Look in /build/



## Game Features:

  * Automatically skip to multiplayer menu TODO: and that connects to first available command server that we can request a map command. TODO: Remove the auto-connect code from javascript.
  * Opening a web page from a map trigger.
  * Bots can spawn-camp, where they use spawn points as objectives for moving around. This was necessary for insta-gib because items are removed from the map.

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

