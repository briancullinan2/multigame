
/*QUAKED item_armor_body (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
 */
{
    "item_armor_amazing",
    "sound/misc/ar2_pkup.wav",
    {"models/powerups/armor/armor_red.md3",
     0, 0, 0},
    /* icon */ "icons/iconr_red",
    /* pickup */ "Amazing Armor",
    1000,
    IT_ARMOR,
    0,
    /* precache */ "",
    /* sounds */ "",
    {"models/powerups/armor/armor_red.skin%rainbow",
     0, 0, 0}},
    {"item_armor_strong",
     "sound/misc/ar2_pkup.wav",
     {"models/powerups/armor/armor_red.md3",
      0, 0, 0},
     /* icon */ "icons/iconr_red",
     /* pickup */ "Strong Armor",
     200,
     IT_ARMOR,
     0,
     /* precache */ "",
     /* sounds */ "",
     {"models/powerups/armor/armor_red.skin%hue0.25",
      0, 0, 0}},
    {"item_armor_weak",
     "sound/misc/ar2_pkup.wav",
     {"models/powerups/armor/armor_red.md3",
      0, 0, 0},
     /* icon */ "icons/iconr_red%hue0.65",
     /* pickup */ "Weak Armor",
     25,
     IT_ARMOR,
     0,
     /* precache */ "",
     /* sounds */ "",
     {"models/powerups/armor/armor_red.skin%hue0.85",
      0, 0, 0}},
    {"weapon_homingrocket",
     "sound/misc/w_pkup.wav",
     {"models/weapons2/rocketl/rocketl.md3",
      0, 0, 0},
     /* icon */ "icons/iconw_rocket",
     /* pickup */ "Homing Rocket Launcher",
     10,
     IT_WEAPON,
     WP_HOMING_ROCKET,
     /* precache */ "",
     /* sounds */ "",
     {"models/weapons2/rocketl/rocketl.skin%invert4",
      0, 0, 0}},

    /*QUAKED item_health_ultra (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "item_health_ultra",
        "sound/items/m_health.wav",
        {"models/powerups/health/mega_cross.md3",
         "models/powerups/health/mega_sphere.md3",
         0, 0},
        /* icon */ "icons/iconh_mega%hue0.30",
        /* pickup */ "Ultra Health",
        200,
        IT_HEALTH,
        0,
        /* precache */ "",
        /* sounds */ "",
        {"models/powerups/health/mega_cross.skin%hue0.30",
         "models/powerups/health/mega_sphere.skin%hue0.30",
         0, 0}},

    /*QUAKED item_enviro (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "item_enviro_multi",
        "sound/items/protect.wav",
        {"models/powerups/instant/enviro.md3",
         "models/powerups/instant/enviro_ring.md3",
         0, 0},
        /* icon */ "icons/envirosuit%hue0.30",
        /* pickup */ "Gravity Suit",
        30,
        IT_POWERUP,
        PW_GRAVITYSUIT,
        /* precache */ "",
        /* sounds */ "sound/items/airout.wav sound/items/protect3.wav",
        {"models/powerups/instant/enviro.skin%hue0.30",
         "models/powerups/instant/enviro_ring.skin%hue0.30",
         0, 0}},

    /*QUAKED item_flight (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "item_flight_long",
        "sound/items/flight.wav",
        {"models/powerups/instant/flight.md3",
         "models/powerups/instant/flight_ring.md3",
         0, 0},
        /* icon */ "icons/flight%hue0.75",
        /* pickup */ "Super Flight",
        240,
        IT_POWERUP,
        PW_SUPERMAN,
        /* precache */ "",
        /* sounds */ "sound/items/flight.wav",
        {"models/powerups/instant/flight.skin%hue0.75",
         "models/powerups/instant/flight_ring.skin%hue0.75",
         0, 0}},
    /*QUAKED item_haste (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "item_haste_flash",
        "sound/items/haste.wav",
        {"models/powerups/instant/haste.md3",
         "models/powerups/instant/haste_ring.md3",
         0, 0},
        /* icon */ "icons/haste%lum0.50%sat-0.8",
        /* pickup */ "Flash Speed",
        30,
        IT_POWERUP,
        PW_FLASH,
        /* precache */ "",
        /* sounds */ "",
        {"models/powerups/instant/haste.skin%lum0.50%sat-0.8",
         "models/powerups/instant/haste_ring.skin%lum0.50%sat-0.8",
         0, 0}},

#if !defined(USE_ADVANCED_WEAPONS)

    /*QUAKED holdable_kamikaze (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "holdable_kamikaze",
        "sound/items/holdable.wav",
        {"models/powerups/kamikazi.md3",
         0, 0, 0},
        /* icon */ "icons/kamikaze",
        /* pickup */ "Kamikaze",
        60,
        IT_HOLDABLE,
        HI_KAMIKAZE,
        /* precache */ "",
        /* sounds */ "sound/items/kamikazerespawn.wav"},

    /*QUAKED holdable_portal (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "holdable_portal",
        "sound/items/holdable.wav",
        {"models/powerups/holdable/porter.md3",
         0, 0, 0},
        /* icon */ "icons/portal",
        /* pickup */ "Portal",
        60,
        IT_HOLDABLE,
        HI_PORTAL,
        /* precache */ "",
        /* sounds */ ""},

    /*QUAKED holdable_invulnerability (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "holdable_invulnerability",
        "sound/items/holdable.wav",
        {"models/powerups/holdable/invulnerability.md3",
         0, 0, 0},
        /* icon */ "icons/invulnerability",
        /* pickup */ "Invulnerability",
        60,
        IT_HOLDABLE,
        HI_INVULNERABILITY,
        /* precache */ "",
        /* sounds */ ""},

    //
    // PERSISTANT POWERUP ITEMS
    //
    /*QUAKED item_scout (.3 .3 1) (-16 -16 -16) (16 16 16) suspended redTeam blueTeam
     */
    {
        "item_scout",
        "sound/items/scout.wav",
        {"models/powerups/scout.md3",
         0, 0, 0},
        /* icon */ "icons/scout",
        /* pickup */ "Scout",
        30,
        IT_PERSISTANT_POWERUP,
        PW_SCOUT,
        /* precache */ "",
        /* sounds */ ""},

    /*QUAKED item_guard (.3 .3 1) (-16 -16 -16) (16 16 16) suspended redTeam blueTeam
     */
    {
        "item_guard",
        "sound/items/guard.wav",
        {"models/powerups/guard.md3",
         0, 0, 0},
        /* icon */ "icons/guard",
        /* pickup */ "Guard",
        30,
        IT_PERSISTANT_POWERUP,
        PW_GUARD,
        /* precache */ "",
        /* sounds */ ""},

    /*QUAKED item_doubler (.3 .3 1) (-16 -16 -16) (16 16 16) suspended redTeam blueTeam
     */
    {
        "item_doubler",
        "sound/items/doubler.wav",
        {"models/powerups/doubler.md3",
         0, 0, 0},
        /* icon */ "icons/doubler",
        /* pickup */ "Doubler",
        30,
        IT_PERSISTANT_POWERUP,
        PW_DOUBLER,
        /* precache */ "",
        /* sounds */ ""},

    /*QUAKED item_doubler (.3 .3 1) (-16 -16 -16) (16 16 16) suspended redTeam blueTeam
     */
    {
        "item_ammoregen",
        "sound/items/ammoregen.wav",
        {"models/powerups/ammo.md3",
         0, 0, 0},
        /* icon */ "icons/ammo_regen",
        /* pickup */ "Ammo Regen",
        30,
        IT_PERSISTANT_POWERUP,
        PW_AMMOREGEN,
        /* precache */ "",
        /* sounds */ ""},

    /*QUAKED team_CTF_neutralflag (0 0 1) (-16 -16 -16) (16 16 16)
    Only in One Flag CTF games
    */
    {
        "team_CTF_neutralflag",
        NULL,
        {"models/flags/n_flag.md3",
         0, 0, 0},
        /* icon */ "icons/iconf_neutral1",
        /* pickup */ "Neutral Flag",
        0,
        IT_TEAM,
        PW_NEUTRALFLAG,
        /* precache */ "",
        /* sounds */ ""},

    {"item_redcube",
     "sound/misc/am_pkup.wav",
     {"models/powerups/orb/r_orb.md3",
      0, 0, 0},
     /* icon */ "icons/iconh_rorb",
     /* pickup */ "Red Cube",
     0,
     IT_TEAM,
     0,
     /* precache */ "",
     /* sounds */ ""},

    {"item_bluecube",
     "sound/misc/am_pkup.wav",
     {"models/powerups/orb/b_orb.md3",
      0, 0, 0},
     /* icon */ "icons/iconh_borb",
     /* pickup */ "Blue Cube",
     0,
     IT_TEAM,
     0,
     /* precache */ "",
     /* sounds */ ""},

#endif

  /*QUAKED item_invis (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
    */
  {
      "item_visibility",
      "sound/items/invisibility.wav",
      {"models/powerups/instant/invis.md3",
        "models/powerups/instant/invis_ring.md3",
        0, 0},
      /* icon */ "icons/invis",
      /* pickup */ "Extra Visibility",
      30,
      IT_POWERUP,
      PW_VISIBILITY,
      /* precache */ "",
      /* sounds */ "",
      {"models/powerups/instant/invis.skin%hue0.10%sat0.80",
        "models/powerups/instant/invis_ring.skin%hue0.10%sat0.80",
        0, 0}},

/*QUAKED item_doubler (.3 .3 1) (-16 -16 -16) (16 16 16) suspended redTeam blueTeam
*/
	{
		"item_regenammo",
		"sound/items/ammoregen.wav",
        { "models/powerups/instant/regen.md3",
         "models/powerups/instant/regen_ring.md3", 0, 0 },
/* icon */		"icons/regen%hue0.20",
/* pickup */	"Ammo Regen",
		30,
		IT_POWERUP,
		PW_REGENAMMO,
/* precache */ "",
/* sounds */ "sound/items/regen.wav",
	{"models/powerups/instant/regen.skin%hue0.20", 
    "models/powerups/instant/regen_ring.skin%hue0.20", NULL, NULL}},

/*QUAKED holdable_medkit (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
{
  "holdable_healer", 
  "sound/items/holdable.wav",
      { 
  "models/powerups/health/small_cross.md3",
     "models/powerups/health/small_sphere.md3",
  0, 0},
/* icon */		"icons/iconh_green",
/* pickup */	"Healer",
  60,
  IT_HOLDABLE,
  HI_HEALER,
/* precache */ "",
/* sounds */ "sound/items/use_medkit.wav"
},
