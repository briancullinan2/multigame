#ifdef EXTERN_CG_CVAR
	#define CG_CVAR( vmCvar, cvarName, defaultString, cvarFlags ) extern vmCvar_t vmCvar;
#endif

#ifdef DECLARE_CG_CVAR
	#define CG_CVAR( vmCvar, cvarName, defaultString, cvarFlags ) vmCvar_t vmCvar;
#endif

#ifdef CG_CVAR_LIST
	#define CG_CVAR( vmCvar, cvarName, defaultString, cvarFlags ) { & vmCvar, cvarName, defaultString, cvarFlags },
#endif

CG_CVAR( cg_ignore, "cg_ignore", "0", 0 ) // used for debugging
CG_CVAR( cg_autoswitch, "cg_autoswitch", "1", CVAR_ARCHIVE )
CG_CVAR( cg_drawGun, "cg_drawGun", "1", CVAR_ARCHIVE )
CG_CVAR( cg_zoomFov, "cg_zoomfov", "22.5", CVAR_ARCHIVE )
CG_CVAR( cg_fov, "cg_fov", "90", CVAR_ARCHIVE )
CG_CVAR( cg_viewsize, "cg_viewsize", "100", CVAR_ARCHIVE )
CG_CVAR( cg_shadows, "cg_shadows", "1", CVAR_ARCHIVE )
CG_CVAR( cg_gibs, "cg_gibs", "1", CVAR_ARCHIVE )
CG_CVAR( cg_draw2D, "cg_draw2D", "1", CVAR_ARCHIVE )
CG_CVAR( cg_drawStatus, "cg_drawStatus", "1", CVAR_ARCHIVE )
CG_CVAR( cg_drawTimer, "cg_drawTimer", "0", CVAR_ARCHIVE )
#ifdef USE_MULTIWORLD
CG_CVAR( cg_drawFPS, "cg_drawFPS", "1", CVAR_ARCHIVE )
#else
CG_CVAR( cg_drawFPS, "cg_drawFPS", "0", CVAR_ARCHIVE )
#endif
CG_CVAR( cg_drawSnapshot, "cg_drawSnapshot", "0", CVAR_ARCHIVE  )
#ifdef USE_3D_WEAPONS
CG_CVAR( cg_draw3dIcons, "cg_draw3dIcons", "2", CVAR_ARCHIVE )
#else
CG_CVAR( cg_draw3dIcons, "cg_draw3dIcons", "1", CVAR_ARCHIVE )
#endif
CG_CVAR( cg_drawIcons, "cg_drawIcons", "1", CVAR_ARCHIVE )
CG_CVAR( cg_drawAmmoWarning, "cg_drawAmmoWarning", "1", CVAR_ARCHIVE )
CG_CVAR( cg_drawAttacker, "cg_drawAttacker", "1", CVAR_ARCHIVE )
CG_CVAR( cg_drawSpeed, "cg_drawSpeed", "0", CVAR_ARCHIVE )
CG_CVAR( cg_drawCrosshair, "cg_drawCrosshair", "4", CVAR_ARCHIVE | CVAR_USERINFO )
CG_CVAR( cg_drawCrosshairNames, "cg_drawCrosshairNames", "1", CVAR_ARCHIVE )
CG_CVAR( cg_drawRewards, "cg_drawRewards", "1", CVAR_ARCHIVE )
CG_CVAR( cg_drawWeaponSelect, "cg_drawWeaponSelect", "1", CVAR_ARCHIVE )
CG_CVAR( cg_crosshairSize, "cg_crosshairSize", "24", CVAR_ARCHIVE )
CG_CVAR( cg_crosshairHealth, "cg_crosshairHealth", "1", CVAR_ARCHIVE )
CG_CVAR( cg_crosshairX, "cg_crosshairX", "0", CVAR_ARCHIVE )
CG_CVAR( cg_crosshairY, "cg_crosshairY", "0", CVAR_ARCHIVE )
CG_CVAR( cg_brassTime, "cg_brassTime", "2500", CVAR_ARCHIVE )
CG_CVAR( cg_simpleItems, "cg_simpleItems", "0", CVAR_ARCHIVE )
CG_CVAR( cg_addMarks, "cg_marks", "1", CVAR_ARCHIVE )
CG_CVAR( cg_lagometer, "cg_lagometer", "1", CVAR_ARCHIVE )
CG_CVAR( cg_railTrailTime, "cg_railTrailTime", "400", CVAR_ARCHIVE  )
CG_CVAR( cg_railTrailRadius, "cg_railTrailRadius", "0", CVAR_ARCHIVE  )
CG_CVAR( cg_gun_frame, "cg_gun_frame", "", CVAR_ROM )
CG_CVAR( cg_gun_x, "cg_gunX", "0", CVAR_ARCHIVE )
CG_CVAR( cg_gun_y, "cg_gunY", "0", CVAR_ARCHIVE )
CG_CVAR( cg_gun_z, "cg_gunZ", "0", CVAR_ARCHIVE )
CG_CVAR( cg_centertime, "cg_centertime", "3", CVAR_CHEAT )
CG_CVAR( cg_runpitch, "cg_runpitch", "0.002", CVAR_ARCHIVE )
CG_CVAR( cg_runroll, "cg_runroll", "0.005", CVAR_ARCHIVE )
CG_CVAR( cg_bobup , "cg_bobup", "0.005", CVAR_ARCHIVE )
CG_CVAR( cg_bobpitch, "cg_bobpitch", "0.002", CVAR_ARCHIVE )
CG_CVAR( cg_bobroll, "cg_bobroll", "0.002", CVAR_ARCHIVE )
CG_CVAR( cg_swingSpeed, "cg_swingSpeed", "0.3", CVAR_CHEAT )
CG_CVAR( cg_animSpeed, "cg_animspeed", "1", CVAR_CHEAT )
CG_CVAR( cg_debugAnim, "cg_debuganim", "0", CVAR_CHEAT )
CG_CVAR( cg_debugPosition, "cg_debugposition", "0", CVAR_CHEAT )
CG_CVAR( cg_debugEvents, "cg_debugevents", "0", CVAR_CHEAT )
CG_CVAR( cg_errorDecay, "cg_errordecay", "100", 0 )
CG_CVAR( cg_nopredict, "cg_nopredict", "0", 0 )
CG_CVAR( cg_noPlayerAnims, "cg_noplayeranims", "0", CVAR_CHEAT )
CG_CVAR( cg_showmiss, "cg_showmiss", "0", 0 )
CG_CVAR( cg_footsteps, "cg_footsteps", "1", CVAR_CHEAT )
CG_CVAR( cg_tracerChance, "cg_tracerchance", "0.4", CVAR_CHEAT )
CG_CVAR( cg_tracerWidth, "cg_tracerwidth", "1", CVAR_CHEAT )
CG_CVAR( cg_tracerLength, "cg_tracerlength", "100", CVAR_CHEAT )
CG_CVAR( cg_thirdPersonRange, "cg_thirdPersonRange", "40", CVAR_CHEAT )
CG_CVAR( cg_thirdPersonAngle, "cg_thirdPersonAngle", "0", CVAR_CHEAT )
CG_CVAR( cg_thirdPerson, "cg_thirdPerson", "0", CVAR_USERINFO | CVAR_SERVERINFO )
CG_CVAR( cg_teamChatTime, "cg_teamChatTime", "3000", CVAR_ARCHIVE  )
CG_CVAR( cg_teamChatHeight, "cg_teamChatHeight", "0", CVAR_ARCHIVE  )
CG_CVAR( cg_forceModel, "cg_forceModel", "0", CVAR_ARCHIVE  )
CG_CVAR( cg_predictItems, "cg_predictItems", "1", CVAR_ARCHIVE )
#ifdef MISSIONPACK
CG_CVAR( cg_deferPlayers, "cg_deferPlayers", "0", CVAR_ARCHIVE )
#else
CG_CVAR( cg_deferPlayers, "cg_deferPlayers", "1", CVAR_ARCHIVE )
#endif
CG_CVAR( cg_drawTeamOverlay, "cg_drawTeamOverlay", "0", CVAR_ARCHIVE )
CG_CVAR( cg_teamOverlayUserinfo, "teamoverlay", "0", CVAR_ROM | CVAR_USERINFO )
CG_CVAR( cg_stats, "cg_stats", "0", 0 )
CG_CVAR( cg_drawFriend, "cg_drawFriend", "1", CVAR_ARCHIVE )
CG_CVAR( cg_teamChatsOnly, "cg_teamChatsOnly", "0", CVAR_ARCHIVE )
#ifdef MISSIONPACK
CG_CVAR( cg_noVoiceChats, "cg_noVoiceChats", "0", CVAR_ARCHIVE )
CG_CVAR( cg_noVoiceText, "cg_noVoiceText", "0", CVAR_ARCHIVE )
#endif
// the following variables are created in other parts of the system,
// but we also reference them here
CG_CVAR( cg_buildScript, "com_buildScript", "0", 0 )	// force loading of all possible data amd error on failures
CG_CVAR( cg_paused, "cl_paused", "0", CVAR_ROM )
CG_CVAR( cg_blood, "com_blood", "1", CVAR_ARCHIVE )
#if defined(MISSIONPACK) || defined(USE_CLASSIC_HUD)
CG_CVAR( cg_redTeamName, "g_redteam", DEFAULT_REDTEAM_NAME, CVAR_ARCHIVE | CVAR_SERVERINFO | CVAR_USERINFO )
CG_CVAR( cg_blueTeamName, "g_blueteam", DEFAULT_BLUETEAM_NAME, CVAR_ARCHIVE | CVAR_SERVERINFO | CVAR_USERINFO )
CG_CVAR( cg_currentSelectedPlayer, "cg_currentSelectedPlayer", "0", CVAR_ARCHIVE )
CG_CVAR( cg_currentSelectedPlayerName, "cg_currentSelectedPlayerName", "", CVAR_ARCHIVE )
CG_CVAR( cg_singlePlayer, "ui_singlePlayerActive", "0", CVAR_USERINFO )
CG_CVAR( cg_enableDust, "g_enableDust", "0", CVAR_SERVERINFO )
CG_CVAR( cg_enableBreath, "g_enableBreath", "0", CVAR_SERVERINFO )
CG_CVAR( cg_singlePlayerActive, "ui_singlePlayerActive", "0", CVAR_USERINFO )
CG_CVAR( cg_recordSPDemo, "ui_recordSPDemo", "0", CVAR_ARCHIVE )
CG_CVAR( cg_recordSPDemoName, "ui_recordSPDemoName", "", CVAR_ARCHIVE )
CG_CVAR( cg_obeliskRespawnDelay, "g_obeliskRespawnDelay", "10", CVAR_SERVERINFO )
#endif
#if defined(MISSIONPACK) || defined(USE_CLASSIC_HUD)
CG_CVAR( cg_hudFiles, "cg_hudFiles", "ui/hud.txt", CVAR_ARCHIVE )
#endif
CG_CVAR( cg_cameraOrbit, "cg_cameraOrbit", "0", CVAR_CHEAT )
CG_CVAR( cg_cameraOrbitDelay, "cg_cameraOrbitDelay", "50", CVAR_ARCHIVE )
CG_CVAR( cg_timescaleFadeEnd, "cg_timescaleFadeEnd", "1", 0 )
CG_CVAR( cg_timescaleFadeSpeed, "cg_timescaleFadeSpeed", "0", 0 )
CG_CVAR( cg_timescale, "timescale", "1", 0 )
CG_CVAR( cg_scorePlum, "cg_scorePlums", "1", CVAR_USERINFO | CVAR_ARCHIVE )
CG_CVAR( cg_smoothClients, "cg_smoothClients", "0", CVAR_USERINFO | CVAR_ARCHIVE )
CG_CVAR( cg_cameraMode, "com_cameraMode", "0", CVAR_CHEAT )
CG_CVAR( cg_noTaunt, "cg_noTaunt", "0", CVAR_ARCHIVE )
CG_CVAR( cg_noProjectileTrail, "cg_noProjectileTrail", "0", CVAR_ARCHIVE )
CG_CVAR( cg_smallFont, "ui_smallFont", "0.25", CVAR_ARCHIVE )
CG_CVAR( cg_bigFont, "ui_bigFont", "0.4", CVAR_ARCHIVE )
CG_CVAR( cg_oldRail, "cg_oldRail", "1", CVAR_ARCHIVE )
CG_CVAR( cg_oldRocket, "cg_oldRocket", "1", CVAR_ARCHIVE )
CG_CVAR( cg_oldPlasma, "cg_oldPlasma", "1", CVAR_ARCHIVE )
CG_CVAR( cg_trueLightning, "cg_trueLightning", "0.0", CVAR_ARCHIVE )
CG_CVAR( cg_hitSounds, "cg_hitSounds", "0", CVAR_ARCHIVE )
CG_CVAR( cg_enemyModel, "cg_enemyModel", "", CVAR_ARCHIVE )
CG_CVAR( cg_enemyColors, "cg_enemyColors", "", CVAR_ARCHIVE )
CG_CVAR( cg_teamModel, "cg_teamModel", "", CVAR_ARCHIVE )
CG_CVAR( cg_teamColors, "cg_teamColors", "", CVAR_ARCHIVE )
CG_CVAR( cg_deadBodyDarken, "cg_deadBodyDarken", "1", CVAR_ARCHIVE )
CG_CVAR( cg_fovAdjust, "cg_fovAdjust", "0", CVAR_ARCHIVE )
CG_CVAR( cg_followKiller, "cg_followKiller", "0", CVAR_ARCHIVE )

CG_CVAR( cg_gametype, "gametype", "0", CVAR_SERVERINFO ) // used for debugging

CG_CVAR( cg_mode, "r_mode", "-2", CVAR_ARCHIVE )
CG_CVAR( cg_aspect, "r_customAspect", "1", CVAR_ARCHIVE )
CG_CVAR( cg_height, "r_customHeight", "1024", CVAR_ARCHIVE )
CG_CVAR( cg_width, "r_customWidth", "1600", CVAR_ARCHIVE )
CG_CVAR( cg_fullscreen, "r_modeFullscreen", "-2", CVAR_ARCHIVE )


#ifdef USE_PORTALS
CG_CVAR( cgwp_portalEnable, "wp_portalEnable", "1", CVAR_SERVERINFO )
CG_CVAR( cg_altPortal, "g_altPortal", "1", CVAR_SERVERINFO )
#endif

CG_CVAR( cg_developer, "developer", "0", 0 )
#ifdef USE_ITEM_TIMERS
CG_CVAR( cg_itemTimer, "cg_itemTimers", "1", CVAR_USERINFO | CVAR_ARCHIVE)
#endif

#ifdef USE_BIRDS_EYE
CG_CVAR( cg_birdsEyeRange, "cg_birdsEyeRange", "300", CVAR_CHEAT )
CG_CVAR( cg_birdsEyeAngle, "cg_birdsEyeAngle", "0", CVAR_CHEAT )
CG_CVAR( cg_birdsEye, "cg_birdsEye", "0", CVAR_USERINFO )
CG_CVAR( cg_sideview, "cg_sideview", "0", CVAR_USERINFO )
#endif

#ifdef USE_AIW
CG_CVAR( cg_upsideDown, "cg_upsideDown", "0", CVAR_USERINFO )
CG_CVAR( cg_reverseControls, "cg_reverseControls", "0", CVAR_USERINFO )
#endif

#ifdef USE_DAMAGE_PLUMS
CG_CVAR( cg_damagePlum, "cg_damagePlums", "1", CVAR_USERINFO | CVAR_ARCHIVE)
#endif

#ifdef USE_RPG_STATS
CG_CVAR( cg_healthBar, "cg_healthBar", "1", CVAR_USERINFO | CVAR_TEMP )
#endif


#ifdef USE_PHYSICS_VARS
#if defined(MISSIONPACK) || defined(USE_ADVANCED_ITEMS)
CG_CVAR( cg_scoutFactor, "cg_scoutFactor", "1.5", CVAR_SERVERINFO)
#endif
CG_CVAR( cg_hasteFactor, "g_hasteFactor", "1.3", CVAR_SERVERINFO)
CG_CVAR( cg_jumpVelocity, "g_jumpVelocity", "270", CVAR_SERVERINFO)
CG_CVAR( cg_gravity, "g_gravity", "800", CVAR_SERVERINFO)
CG_CVAR( cg_wallWalk, "g_wallWalk", "0.7", CVAR_SERVERINFO)
#endif

CG_CVAR( cg_atmosphere, "g_atmosphere", "", CVAR_SERVERINFO | CVAR_TEMP )
CG_CVAR( cg_atmosphericEffects, "cg_atmosphericEffects", "1", CVAR_ARCHIVE )
#ifdef USE_WEAPON_VARS
CG_CVAR( cgwp_gauntCycle, "wp_gauntCycle", "400", CVAR_SERVERINFO )
CG_CVAR( cgwp_lightCycle, "wp_lightCycle", "50", CVAR_SERVERINFO )
CG_CVAR( cgwp_shotgunCycle, "wp_shotgunCycle", "1000", CVAR_SERVERINFO )
CG_CVAR( cgwp_machineCycle, "wp_machineCycle", "100", CVAR_SERVERINFO )
CG_CVAR( cgwp_grenadeCycle, "wp_grenadeCycle", "800", CVAR_SERVERINFO )
CG_CVAR( cgwp_rocketCycle, "wp_rocketCycle", "800", CVAR_SERVERINFO )
CG_CVAR( cgwp_plasmaCycle, "wp_plasmaCycle", "100", CVAR_SERVERINFO )
CG_CVAR( cgwp_railCycle, "wp_railCycle", "1500", CVAR_SERVERINFO )
CG_CVAR( cgwp_bfgCycle, "wp_bfgCycle", "200", CVAR_SERVERINFO )
#ifdef USE_GRAPPLE
CG_CVAR( cgwp_grappleCycle, "wp_grappleCycle", "400", CVAR_SERVERINFO )
#endif
#if defined(MISSIONPACK) || defined(USE_ADVANCED_WEAPONS)
CG_CVAR( cgwp_nailCycle, "wp_nailCycle", "1000", CVAR_SERVERINFO )
CG_CVAR( cgwp_proxCycle, "wp_proxCycle", "800", CVAR_SERVERINFO )
CG_CVAR( cgwp_chainCycle, "wp_chainCycle", "30", CVAR_SERVERINFO )
#endif
#endif

#ifdef USE_WEAPON_ORDER
CG_CVAR( cg_weaponOrder, "cg_weaponOrder", "1/2/3/4/6/8/5/7/9", CVAR_ARCHIVE ) //WarZone
#endif
#ifdef USE_WEAPON_CENTER
CG_CVAR( cg_gunCenter, "cg_gunCenter", "1", CVAR_ARCHIVE )
#endif

#ifdef USE_GRAPPLE
CG_CVAR( cgwp_grappleEnable, "wp_grappleEnable", "1", CVAR_SERVERINFO )
CG_CVAR( cgwp_grapplePull,  "wp_grapplePull", "700", CVAR_SERVERINFO )
CG_CVAR( cg_altGrapple,  "g_altGrapple", "1", CVAR_SERVERINFO )
#endif
#ifdef USE_FLAME_THROWER
CG_CVAR( cgwp_flameCycle, "wp_flameCycle", "40", CVAR_SERVERINFO )
#endif


#ifdef USE_MULTIWORLD
CG_CVAR( cg_worlds, "worlds", "0", CVAR_USERINFO | CVAR_ROM | CVAR_NORESTART )
#endif

#undef CG_CVAR
