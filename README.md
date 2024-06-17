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
 * many many weapons from every other mod, need a handy way to do this with data
 * walking on walls. possible way to implement, load the world in 6 orientations along each axis, then estimate the intersections of each corner
 * puzzles like the one in myst to solve, add EngineOfCreation



# Documentation

See /docs/

# Compilation and installation

Look in /build/
