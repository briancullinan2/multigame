#ifdef EXTERN_G_CVAR
	#define G_CVAR( vmCvar, cvarName, defaultString, cvarFlags, modificationCount, trackChange, teamShader ) extern vmCvar_t vmCvar;
#endif

#ifdef DECLARE_G_CVAR
	#define G_CVAR( vmCvar, cvarName, defaultString, cvarFlags, modificationCount, trackChange, teamShader ) vmCvar_t vmCvar;
#endif

#ifdef G_CVAR_LIST
	#define G_CVAR( vmCvar, cvarName, defaultString, cvarFlags, modificationCount, trackChange, teamShader ) { & vmCvar, cvarName, defaultString, cvarFlags, modificationCount, trackChange, teamShader },
#endif

// don't override the cheat state set by the system
G_CVAR( g_cheats, "sv_cheats", "", 0, 0, qfalse, qfalse )

//G_CVAR( g_restarted, "g_restarted", "0", CVAR_ROM, 0, qfalse, qfalse )
G_CVAR( g_mapname, "mapname", "", CVAR_SERVERINFO | CVAR_ROM, 0, qfalse, qfalse )
G_CVAR( g_fps, "sv_fps", "30", CVAR_ARCHIVE, 0, qfalse, qfalse )

// latched vars
G_CVAR( g_gametype, "g_gametype", "0", CVAR_SERVERINFO | CVAR_USERINFO | CVAR_LATCH, 0, qfalse, qfalse )

G_CVAR( g_maxclients, "sv_maxclients", "8", CVAR_SERVERINFO | CVAR_LATCH | CVAR_ARCHIVE, 0, qfalse, qfalse ) // allow this many total, including spectators
G_CVAR( g_maxGameClients, "g_maxGameClients", "0", CVAR_SERVERINFO | CVAR_LATCH | CVAR_ARCHIVE, 0, qfalse, qfalse ) // allow this many active

// change anytime vars
G_CVAR( g_dmflags, "dmflags", "0", CVAR_SERVERINFO | CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_fraglimit, "fraglimit", "20", CVAR_SERVERINFO | CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )
G_CVAR( g_timelimit, "timelimit", "0", CVAR_SERVERINFO | CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )
G_CVAR( g_capturelimit, "capturelimit", "8", CVAR_SERVERINFO | CVAR_ARCHIVE | CVAR_NORESTART, 0, qtrue, qfalse )

G_CVAR( g_synchronousClients, "g_synchronousClients", "0", CVAR_SYSTEMINFO, 0, qfalse, qfalse )

G_CVAR( g_friendlyFire, "g_friendlyFire", "0", CVAR_ARCHIVE, 0, qtrue, qfalse )

G_CVAR( g_autoJoin, "g_autoJoin", "1", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_teamForceBalance, "g_teamForceBalance", "0", CVAR_ARCHIVE, 0, qfalse, qfalse )

G_CVAR( g_warmup, "g_warmup", "20", CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_log, "g_log", "games.log", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_logSync, "g_logSync", "0", CVAR_ARCHIVE, 0, qfalse, qfalse )

G_CVAR( g_password, "g_password", "", CVAR_USERINFO, 0, qfalse, qfalse )

G_CVAR( g_banIPs, "g_banIPs", "", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_filterBan, "g_filterBan", "1", CVAR_ARCHIVE, 0, qfalse, qfalse )

G_CVAR( g_needpass, "g_needpass", "0", CVAR_SERVERINFO | CVAR_ROM, 0, qfalse, qfalse )

G_CVAR( g_dedicated, "dedicated", "0", 0, 0, qfalse, qfalse )

G_CVAR( g_speed, "g_speed", "320", 0, 0, qtrue, qfalse )
G_CVAR( g_gravity, "g_gravity", "800", 0, 0, qtrue, qfalse )
G_CVAR( g_knockback, "g_knockback", "1000", 0, 0, qtrue, qfalse )
G_CVAR( g_quadfactor, "g_quadfactor", "3", 0, 0, qtrue, qfalse )
G_CVAR( g_weaponRespawn, "g_weaponrespawn", "5", 0, 0, qtrue, qfalse )
G_CVAR( g_weaponTeamRespawn, "g_weaponTeamRespawn", "30", 0, 0, qtrue, qfalse )
G_CVAR( g_forcerespawn, "g_forcerespawn", "20", 0, 0, qtrue, qfalse )
G_CVAR( g_inactivity, "g_inactivity", "0", 0, 0, qtrue, qfalse )
G_CVAR( g_debugMove, "g_debugMove", "0", 0, 0, qfalse, qfalse )
G_CVAR( g_debugDamage, "g_debugDamage", "0", 0, 0, qfalse, qfalse )
G_CVAR( g_debugAlloc, "g_debugAlloc", "0", 0, 0, qfalse, qfalse )
G_CVAR( g_motd, "g_motd", "", 0, 0, qfalse, qfalse )
G_CVAR( g_blood, "com_blood", "1", 0, 0, qfalse, qfalse )

G_CVAR( g_podiumDist, "g_podiumDist", "80", 0, 0, qfalse, qfalse )
G_CVAR( g_podiumDrop, "g_podiumDrop", "70", 0, 0, qfalse, qfalse )

G_CVAR( g_allowVote, "g_allowVote", "1", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_listEntity, "g_listEntity", "0", 0, 0, qfalse, qfalse )

G_CVAR( g_unlagged, "g_unlagged", "1", CVAR_SERVERINFO | CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( g_predictPVS, "g_predictPVS", "0", CVAR_ARCHIVE, 0, qfalse, qfalse )

#ifdef MISSIONPACK
G_CVAR( g_obeliskHealth, "g_obeliskHealth", "2500", 0, 0, qfalse, qfalse )
G_CVAR( g_obeliskRegenPeriod, "g_obeliskRegenPeriod", "1", 0, 0, qfalse, qfalse )
G_CVAR( g_obeliskRegenAmount, "g_obeliskRegenAmount", "15", 0, 0, qfalse, qfalse )
G_CVAR( g_obeliskRespawnDelay, "g_obeliskRespawnDelay", "10", CVAR_SERVERINFO, 0, qfalse, qfalse )

G_CVAR( g_cubeTimeout, "g_cubeTimeout", "30", 0, 0, qfalse, qfalse )
G_CVAR( g_redteam, "g_redteam", "Stroggs", CVAR_ARCHIVE | CVAR_SERVERINFO | CVAR_USERINFO, 0, qtrue, qtrue )
G_CVAR( g_blueteam, "g_blueteam", "Pagans", CVAR_ARCHIVE | CVAR_SERVERINFO | CVAR_USERINFO, 0, qtrue, qtrue )
G_CVAR( g_singlePlayer, "ui_singlePlayerActive", "", 0, 0, qfalse, qfalse )

G_CVAR( g_enableDust, "g_enableDust", "0", CVAR_SERVERINFO, 0, qtrue, qfalse )
G_CVAR( g_enableBreath, "g_enableBreath", "0", CVAR_SERVERINFO, 0, qtrue, qfalse )
G_CVAR( g_proxMineTimeout, "g_proxMineTimeout", "20000", 0, 0, qfalse, qfalse )
#endif
G_CVAR( g_smoothClients, "g_smoothClients", "1", 0, 0, qfalse, qfalse )
G_CVAR( pmove_fixed, "pmove_fixed", "0", CVAR_SYSTEMINFO, 0, qfalse, qfalse )
G_CVAR( pmove_msec, "pmove_msec", "8", CVAR_SYSTEMINFO, 0, qfalse, qfalse )

G_CVAR( g_rotation, "g_rotation", "0", CVAR_ARCHIVE, 0, qfalse, qfalse )
#ifdef USE_PORTALS
G_CVAR( wp_portalEnable, "wp_portalEnable", "1", CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
#ifdef USE_ALT_FIRE
G_CVAR( g_altPortal, "g_altPortal", "0", CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
#endif
#endif


#ifdef USE_TRINITY
G_CVAR( g_unholyTrinity, "g_unholyTrinity", "0", 0, 0, qfalse, qfalse )
#endif
#ifdef USE_HOTRPG
G_CVAR( g_hotRockets, "g_hotRockets", "0", 0, 0, qfalse, qfalse )
#endif
#ifdef USE_HOTBFG
G_CVAR( g_hotBFG, "g_hotBFG", "0", 0, 0, qfalse, qfalse )
#endif

#ifdef USE_INSTAGIB
G_CVAR( g_instagib, "g_instagib", "0", 0, 0, qfalse, qfalse )
#endif
#ifdef USE_LOCAL_DMG
G_CVAR( g_locDamage, "g_locDamage", "1", CVAR_ARCHIVE, 0, qfalse, qfalse )
#endif

#ifdef USE_BIRDS_EYE
G_CVAR( g_birdsEye, "g_birdsEye", "0", CVAR_TEMP, 0, qfalse, qfalse )
G_CVAR( g_thirdPerson, "g_thirdPerson", "0", CVAR_TEMP, 0, qfalse, qfalse )
G_CVAR( g_sideview, "g_sideview", "0", CVAR_TEMP, 0, qfalse, qfalse )
#endif
#ifdef USE_AIW
G_CVAR( g_upsideDown, "g_upsideDown", "0", CVAR_TEMP, 0, qfalse, qfalse )
#endif

#if defined(USE_GAME_FREEZETAG) || defined(USE_REFEREE_CMDS)
G_CVAR( g_freezeTag, "g_freezeTag", "1", 0, 0, qfalse, qfalse )
G_CVAR( g_thawTime, "g_thawTime", "180", CVAR_ARCHIVE, 0, qfalse, qfalse )
#endif

#ifdef USE_VORTEX_GRENADES
G_CVAR( g_clusterGrenades, "g_clusterGrenades", "0", 0, 0, qfalse, qfalse )
#endif
#ifdef USE_VORTEX_GRENADES
G_CVAR( g_vortexGrenades, "g_vortexGrenades", "0", 0, 0, qfalse, qfalse )
#endif
#ifdef USE_INVULN_RAILS
G_CVAR( g_railThruWalls, "g_railThruWalls", "1", 0, 0, qfalse, qfalse )
#endif
#ifdef USE_BOUNCE_RAIL
G_CVAR( wp_railBounce, "wp_railBounce", "0", 0, 0, qfalse, qfalse )
#endif
#ifdef USE_HOMING_MISSILE
G_CVAR( wp_rocketHoming, "wp_rocketHoming", "0", 0, 0, qfalse, qfalse )
#endif
#ifdef USE_BOUNCE_RPG
G_CVAR( wp_bfgBounce, "wp_bfgBounce", "0", 0, 0, qfalse, qfalse )
G_CVAR( wp_plasmaBounce, "wp_plasmaBounce", "0", 0, 0, qfalse, qfalse )
G_CVAR( wp_rocketBounce, "wp_rocketBounce", "0", 0, 0, qfalse, qfalse )
#endif
#ifdef USE_VULN_RPG
G_CVAR( wp_rocketVuln, "wp_rocketVuln", "0", 0, 0, qfalse, qfalse )
#endif
#ifdef USE_ACCEL_RPG
G_CVAR( wp_rocketAccel, "wp_rocketAccel", "0", 0, 0, qfalse, qfalse )
#endif

#ifdef USE_PHYSICS_VARS
#ifdef MISSIONPACK
G_CVAR( g_scoutFactor, "g_scoutFactor", "1.5", CVAR_SERVERINFO | CVAR_ARCHIVE, 0, qtrue, qfalse )
#endif
G_CVAR( g_hasteFactor, "g_hasteFactor", "1.3", CVAR_SERVERINFO | CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_jumpVelocity, "g_jumpVelocity", "270", CVAR_SERVERINFO | CVAR_ARCHIVE, 0, qtrue, qfalse )
G_CVAR( g_wallWalk, "g_wallWalk", "0.7", CVAR_SERVERINFO | CVAR_ARCHIVE, 0, qtrue, qfalse )
#endif

#ifdef USE_WEAPON_DROP
G_CVAR( g_dropWeapon, "g_dropWeapon", "65535", CVAR_ARCHIVE, 0, qfalse, qfalse )
#endif
#undef G_CVAR
