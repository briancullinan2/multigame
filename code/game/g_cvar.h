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

#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS)
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

#ifdef USE_WEAPON_VARS
G_CVAR( wp_gauntCycle,        "wp_gauntCycle",        "400",  CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
G_CVAR( wp_gauntDamage,       "wp_gauntDamage",       "50",   CVAR_ARCHIVE, 0, qfalse, qfalse )

G_CVAR( wp_lightCycle,        "wp_lightCycle",        "50",   CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
G_CVAR( wp_lightDamage,       "wp_lightDamage",       "8",    CVAR_ARCHIVE, 0, qfalse, qfalse )

G_CVAR( wp_shotgunCycle,      "wp_shotgunCycle",      "1000", CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
G_CVAR( wp_shotgunDamage,     "wp_shotgunDamage",     "10",   CVAR_ARCHIVE, 0, qfalse, qfalse )

G_CVAR( wp_machineCycle,      "wp_machineCycle",      "100",  CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
G_CVAR( wp_machineDamage,     "wp_machineDamage",     "7",    CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_machineDamageTeam, "wp_machineDamageTeam", "5",    CVAR_ARCHIVE, 0, qfalse, qfalse )

G_CVAR( wp_grenadeCycle,      "wp_grenadeCycle",      "800",  CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
G_CVAR( wp_grenadeDamage,     "wp_grenadeDamage",     "100",  CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_grenadeSplash,     "wp_grenadeSplash",     "100",  CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_grenadeRadius,     "wp_grenadeRadius",     "150",  CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_grenadeSpeed,      "wp_grenadeSpeed",      "700",  CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_grenadeTime,       "wp_grenadeTime",       "2.5",  CVAR_ARCHIVE, 0, qfalse, qfalse )

G_CVAR( wp_rocketCycle,       "wp_rocketCycle",       "800",  CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
G_CVAR( wp_rocketDamage,      "wp_rocketDamage",      "100",  CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_rocketSplash,      "wp_rocketSplash",      "100",  CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_rocketRadius,      "wp_rocketRadius",      "120",  CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_rocketSpeed,       "wp_rocketSpeed",       "900",  CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_rocketTime,        "wp_rocketTime",        "15",   CVAR_ARCHIVE, 0, qfalse, qfalse )

G_CVAR( wp_plasmaCycle,       "wp_plasmaCycle",       "100",  CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
G_CVAR( wp_plasmaDamage,      "wp_plasmaDamage",      "20",   CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_plasmaSplash,      "wp_plasmaSplash",      "15",   CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_plasmaRadius,      "wp_plasmaRadius",      "20",   CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_plasmaSpeed,       "wp_plasmaSpeed",       "2000", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_plasmaTime,        "wp_plasmaTime",        "10.0", CVAR_ARCHIVE, 0, qfalse, qfalse )

G_CVAR( wp_railCycle,         "wp_railCycle",         "1500", CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
G_CVAR( wp_railDamage,        "wp_railDamage",        "100",  CVAR_ARCHIVE, 0, qfalse, qfalse )

G_CVAR( wp_bfgCycle,          "wp_bfgCycle",          "200",  CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
G_CVAR( wp_bfgDamage,         "wp_bfgDamage",         "100",  CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_bfgSplash,         "wp_bfgSplash",         "100",  CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_bfgRadius,         "wp_bfgRadius",         "120",  CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_bfgSpeed,          "wp_bfgSpeed",          "2000", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_bfgTime,           "wp_bfgTime",           "10",   CVAR_ARCHIVE, 0, qfalse, qfalse )

#ifdef USE_GRAPPLE
G_CVAR( wp_grappleEnable,     "wp_grappleEnable", "0",    CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_grapplePull,       "wp_grapplePull",   "700",  CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
G_CVAR( wp_grappleCycle,      "wp_grappleCycle",  "400",  CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
G_CVAR( wp_grappleDamage,     "wp_grappleDamage", "300",  CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_grappleSpeed,      "wp_grappleSpeed",  "2000", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_grappleTime,       "wp_grappleDamage", "10.0",   CVAR_ARCHIVE, 0, qfalse, qfalse )

#ifdef USE_ALT_FIRE
G_CVAR( g_altGrapple,         "g_altGrapple",     "0",  CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
#endif
#endif

#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS)

G_CVAR( wp_nailCycle,         "wp_nailCycle",         "1000", CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
G_CVAR( wp_nailDamage,        "wp_nailDamage",        "20",   CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_nailSpeed,         "wp_nailSpeed",         "555",  CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_nailTime,          "wp_nailTime",          "10.0", CVAR_ARCHIVE, 0, qfalse, qfalse )
// doesn't have a hit damage, only sticks and splashes
G_CVAR( wp_proxCycle,         "wp_proxCycle",         "800",  CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
G_CVAR( wp_proxDamage,        "wp_proxDamage",        "0",    CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_proxSplash,        "wp_proxSplash",        "100",  CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_proxRadius,        "wp_proxRadius",        "150",  CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_proxSpeed,         "wp_proxSpeed",         "700",  CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_proxTime,          "wp_proxTime",          "3.0",  CVAR_ARCHIVE, 0, qfalse, qfalse )

G_CVAR( wp_chainCycle,        "wp_chainCycle",        "30",   CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
G_CVAR( wp_chainDamage,       "wp_chainDamage",       "7",    CVAR_ARCHIVE, 0, qfalse, qfalse )
#endif

#ifdef USE_FLAME_THROWER
G_CVAR( wp_flameCycle,        "wp_flameCycle",        "40",   CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
G_CVAR( wp_flameDamage,       "wp_flameDamage",       "30",   CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_flameSplash,       "wp_flameSplash",       "25",   CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_flameRadius,       "wp_flameRadius",       "45",   CVAR_ARCHIVE, 0, qfalse, qfalse )
#endif

#endif // end USE_WEAPON_VARS

#ifdef USE_BOUNCE_RPG
G_CVAR( wp_bfgBounce, "wp_bfgBounce", "1", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_plasmaBounce, "wp_plasmaBounce", "1", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_rocketBounce, "wp_rocketBounce", "1", CVAR_ARCHIVE, 0, qfalse, qfalse )
#endif
#ifdef USE_CLOAK_CMD
G_CVAR( g_enableCloak, "g_enableCloak", "1", CVAR_ARCHIVE, 0, qfalse, qfalse )
#endif

#ifdef USE_GRAVITY_BOOTS
G_CVAR( g_enableBoots, "g_enableBoots", "1", CVAR_ARCHIVE, 0, qfalse, qfalse )
#endif

#ifdef USE_WEAPON_ORDER
G_CVAR( g_supportsWeaponOrder, "g_supportsWeaponOrder", "1", CVAR_SERVERINFO | CVAR_ROM, 0, qfalse, qfalse ) //WarZone
#endif

#undef G_CVAR
