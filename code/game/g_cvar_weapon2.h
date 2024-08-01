

#ifdef USE_ADVANCED_WEAPONS
G_CVAR( wp_classOriginal,       "wp_classOriginal",       "1",    CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_classMission,        "wp_classMission",        "1",    CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_classOA,             "wp_classOA",             "1",    CVAR_ARCHIVE, 0, qfalse, qfalse )
#endif

#ifdef USE_PORTALS
G_CVAR( wp_portalEnable, "wp_portalEnable", "1", CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
#ifdef USE_ALT_FIRE
G_CVAR( g_altPortal, "g_altPortal", "0", CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
#endif
#endif

#ifdef USE_GRAPPLE
G_CVAR( wp_grappleEnable,     "wp_grappleEnable", "0",    CVAR_ARCHIVE, 0, qfalse, qfalse )
#ifdef USE_ALT_FIRE
G_CVAR( g_altGrapple,         "g_altGrapple",     "0",  CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
#endif
#endif

#ifdef USE_FLAME_THROWER
G_CVAR( wp_flameEnable,       "wp_flameEnable",       "0",    CVAR_ARCHIVE, 0, qfalse, qfalse )
#endif


#ifdef USE_WEAPON_VARS

#ifdef USE_PORTALS
G_CVAR( wp_portalCycle,          "wp_portalCycle",          "200",  CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
G_CVAR( wp_portalDamage,         "wp_portalDamage",         "100",  CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_portalSplash,         "wp_portalSplash",         "100",  CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_portalRadius,         "wp_portalRadius",         "120",  CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_portalSpeed,          "wp_portalSpeed",          "2000", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_portalTime,           "wp_portalTime",           "10",   CVAR_ARCHIVE, 0, qfalse, qfalse )
#endif


#ifdef USE_GRAPPLE
G_CVAR( wp_grapplePull,       "wp_grapplePull",   "700",  CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
G_CVAR( wp_grappleCycle,      "wp_grappleCycle",  "400",  CVAR_ARCHIVE | CVAR_SERVERINFO, 0, qfalse, qfalse )
G_CVAR( wp_grappleDamage,     "wp_grappleDamage", "300",  CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_grappleSpeed,      "wp_grappleSpeed",  "2000", CVAR_ARCHIVE, 0, qfalse, qfalse )
G_CVAR( wp_grappleTime,       "wp_grappleDamage", "10.0",   CVAR_ARCHIVE, 0, qfalse, qfalse )
#endif


#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS) || defined(USE_ADVANCED_CLASS)
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

#endif




