
#ifdef USE_VORTEX_GRENADES
G_CVAR( wp_grenadeCluster, "wp_grenadeCluster", "0", 0, 0, qfalse, qfalse )
#endif
#ifdef USE_VORTEX_GRENADES
G_CVAR( wp_grenadeVortex, "wp_grenadeVortex", "0", 0, 0, qfalse, qfalse )
#endif
#ifdef USE_INVULN_RAILS
G_CVAR( wp_railThruWalls, "wp_railThruWalls", "0", 0, 0, qfalse, qfalse )
#endif
#ifdef USE_BOUNCE_RAIL
G_CVAR( wp_railBounce, "wp_railBounce", "0", 0, 0, qfalse, qfalse )
#endif
#ifdef USE_TELEFRAG_RAIL
G_CVAR( wp_railTelefrag, "wp_railTelefrag", "0", 0, 0, qfalse, qfalse )
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


#ifdef USE_WEAPON_VARS
G_CVAR( wp_gauntEnable,       "wp_gauntEnable",       "1",    CVAR_ARCHIVE, 0, qfalse, qfalse )
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


#endif // end USE_WEAPON_VARS

