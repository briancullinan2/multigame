#ifdef USE_RUNES
// 1
/*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
 */
{
    "rune_strength",
    "sound/items/spread.wav",
    {"models/runes/strength.md3", 0, 0, 0},
    /* icon */ "icons/strength",
    /* pickup */ "Strength",
    30,
    IT_POWERUP,
    RUNE_STRENGTH,
    /* precache */ "",
    /* sounds */ ""},
    // 2
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_regen",
        "sound/items/regeneration.wav",
        {"models/runes/haste.md3", 0, 0, 0},
        /* icon */ "icons/regen",
        /* pickup */ "Regeneration",
        30,
        IT_POWERUP,
        RUNE_REGEN,
        /* precache */ "",
        /* sounds */ ""},
    // 3
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_resist",
        "sound/items/regeneration.wav",
        {"models/runes/regen.md3", 0, 0, 0},
        /* icon */ "icons/resistance",
        /* pickup */ "Resistance",
        30,
        IT_POWERUP,
        RUNE_RESIST,
        /* precache */ "",
        /* sounds */ ""},
    // 4
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_haste",
        "sound/items/haste.wav",
        {"models/runes/resist.md3", 0, 0, 0},
        /* icon */ "icons/haste",
        /* pickup */ "Haste",
        30,
        IT_POWERUP,
        RUNE_HASTE,
        /* precache */ "",
        /* sounds */ ""},

    // 5
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_enviro",
        "sound/items/protect.wav",
        {"models/runes/strength.md3", 0, 0, 0},
        /* icon */ "icons/strength",
        /* pickup */ "Environmental Protection",
        30,
        IT_POWERUP,
        RUNE_ENVIRO,
        /* precache */ "",
        /* sounds */ ""},
    // 6
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_flight",
        "sound/items/flight.wav",
        {"models/runes/haste.md3", 0, 0, 0},
        /* icon */ "icons/flight",
        /* pickup */ "Flight",
        30,
        IT_POWERUP,
        RUNE_FLIGHT,
        /* precache */ "",
        /* sounds */ ""},
    // 7
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_berserk",
        "sound/items/regeneration.wav",
        {"models/runes/regen.md3", "models/runes/regen.md3", 0, 0},
        /* icon */ "icons/berserk",
        /* pickup */ "Berserker",
        30,
        IT_POWERUP,
        RUNE_BERSERK,
        /* precache */ "",
        /* sounds */ ""},
    // 8
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_recall",
        "sound/items/holdable.wav",
        {"models/runes/resist.md3", 0, 0, 0},
        /* icon */ "icons/recall",
        /* pickup */ "Recall",
        30,
        IT_POWERUP,
        RUNE_RECALL,
        /* precache */ "",
        /* sounds */ ""},

    // 9
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_electric",
        "sound/items/protect.wav",
        {"models/runes/strength.md3", "models/runes/strength.md3", 0, 0},
        /* icon */ "icons/reflection",
        /* pickup */ "Electric",
        30,
        IT_POWERUP,
        RUNE_ELECTRIC,
        /* precache */ "",
        /* sounds */ ""},
    // 10
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_cloak",
        "sound/items/flight.wav",
        {"models/runes/haste.md3", 0, 0, 0},
        /* icon */ "icons/cloak",
        /* pickup */ "Cloak",
        30,
        IT_POWERUP,
        RUNE_CLOAK,
        /* precache */ "",
        /* sounds */ ""},
    // 11
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_divine",
        "sound/items/regeneration.wav",
        {"models/runes/regen.md3", "models/runes/regen.md3", 0, 0},
        /* icon */ "icons/divine",
        /* pickup */ "Divine Wind",
        30,
        IT_POWERUP,
        RUNE_DIVINE,
        /* precache */ "",
        /* sounds */ ""},
    // 12
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_death",
        "sound/items/kamikazerespawn.wav",
        {"models/runes/resist.md3", 0, 0, 0},
        /* icon */ "icons/death_spots",
        /* pickup */ "Death Spots",
        30,
        IT_POWERUP,
        RUNE_DEATH,
        /* precache */ "",
        /* sounds */ ""},

    // 13
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_holo",
        "sound/items/protect.wav",
        {"models/runes/strength.md3", "models/runes/strength.md3", 0, 0},
        /* icon */ "icons/hologram",
        /* pickup */ "Holorune",
        30,
        IT_POWERUP,
        RUNE_HOLO,
        /* precache */ "",
        /* sounds */ ""},
    // 14
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_orb",
        "sound/items/flight.wav",
        {"models/runes/haste.md3", 0, 0, 0},
        /* icon */ "icons/orb",
        /* pickup */ "Orb of Death",
        30,
        IT_POWERUP,
        RUNE_ORB,
        /* precache */ "",
        /* sounds */ ""},
    // 15
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_blink",
        "sound/items/regeneration.wav",
        {"models/runes/regen.md3", "models/runes/regen.md3", 0, 0},
        /* icon */ "icons/blink",
        /* pickup */ "Blink",
        30,
        IT_POWERUP,
        RUNE_BLINK,
        /* precache */ "",
        /* sounds */ ""},
    // 16
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_camo",
        "sound/items/kamikazerespawn.wav",
        {"models/runes/resist.md3", 0, 0, 0},
        /* icon */ "icons/illusion",
        /* pickup */ "Camouflage",
        30,
        IT_POWERUP,
        RUNE_CAMO,
        /* precache */ "",
        /* sounds */ ""},

    // 17
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_jump",
        "sound/items/protect.wav",
        {"models/runes/strength.md3", 0, 0, 0},
        /* icon */ "icons/jump",
        /* pickup */ "Uncontrollable Jumping",
        30,
        IT_POWERUP,
        RUNE_JUMP,
        /* precache */ "",
        /* sounds */ ""},
    // 18
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_action",
        "sound/items/flight.wav",
        {"models/runes/haste.md3", 0, 0, 0},
        /* icon */ "icons/overkill",
        /* pickup */ "Action Movie Arsenal",
        30,
        IT_POWERUP,
        RUNE_ACTION,
        /* precache */ "",
        /* sounds */ ""},
    // 19
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_vampire",
        "sound/items/regeneration.wav",
        {"models/runes/regen.md3", "models/runes/regen.md3", 0, 0},
        /* icon */ "icons/vamp",
        /* pickup */ "Vampiric",
        30,
        IT_POWERUP,
        RUNE_VAMPIRE,
        /* precache */ "",
        /* sounds */ ""},
    // 20
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_shield",
        "sound/items/protect.wav",
        {"models/runes/resist.md3", 0, 0, 0},
        /* icon */ "icons/shield",
        /* pickup */ "Shielding",
        30,
        IT_POWERUP,
        RUNE_SHIELD,
        /* precache */ "",
        /* sounds */ ""},

    // 21
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_health",
        "sound/items/protect.wav",
        {"models/runes/strength.md3", "models/runes/strength.md3", 0, 0},
        /* icon */ "icons/goodhealth",
        /* pickup */ "Good Health",
        30,
        IT_POWERUP,
        RUNE_HEALTH,
        /* precache */ "",
        /* sounds */ ""},
    // 22
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_radio",
        "sound/items/flight.wav",
        {"models/runes/haste.md3", 0, 0, 0},
        /* icon */ "icons/radioactivity",
        /* pickup */ "Radioactivity",
        30,
        IT_POWERUP,
        RUNE_RADIO,
        /* precache */ "",
        /* sounds */ ""},
    // 23
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_switch",
        "sound/items/regeneration.wav",
        {"models/runes/regen.md3", "models/runes/regen.md3", 0, 0},
        /* icon */ "icons/switch",
        /* pickup */ "Switch",
        30,
        IT_POWERUP,
        RUNE_SWITCH,
        /* precache */ "",
        /* sounds */ ""},
    // 24
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_icetrap",
        "sound/items/protect.wav",
        {"models/runes/icetrap.md3", 0, 0, 0},
        /* icon */ "icons/ice_trap",
        /* pickup */ "Ice Traps",
        30,
        IT_POWERUP,
        RUNE_ICETRAP,
        /* precache */ "",
        /* sounds */ ""},

    // 25
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_gravity",
        "sound/items/protect.wav",
        {"models/runes/strength.md3", 0, 0, 0},
        /* icon */ "icons/gravity",
        /* pickup */ "Gravity",
        30,
        IT_POWERUP,
        RUNE_GRAVITY,
        /* precache */ "",
        /* sounds */ ""},
    // 26
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_tele",
        "sound/items/flight.wav",
        {"models/runes/haste.md3", "models/runes/haste.md3", 0, 0},
        /* icon */ "icons/teleport",
        /* pickup */ "Teleport Shuffle",
        30,
        IT_POWERUP,
        RUNE_TELE,
        /* precache */ "",
        /* sounds */ ""},
    // 27
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_impact",
        "sound/items/regeneration.wav",
        {"models/runes/regen.md3", 0, 0, 0},
        /* icon */ "icons/impact",
        /* pickup */ "Impact",
        30,
        IT_POWERUP,
        RUNE_IMPACT,
        /* precache */ "",
        /* sounds */ ""},
    // 28
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_vengeance",
        "sound/items/protect.wav",
        {"models/runes/resist.md3", 0, 0, 0},
        /* icon */ "icons/vengeance",
        /* pickup */ "Vengeance",
        30,
        IT_POWERUP,
        RUNE_VENGEANCE,
        /* precache */ "",
        /* sounds */ ""},

    // 29
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_shubhat",
        "sound/items/protect.wav",
        {"models/runes/strength.md3", 0, 0, 0},
        /* icon */ "icons/skull_red",
        /* pickup */ "Shub Hat",
        30,
        IT_POWERUP,
        RUNE_SHUBHAT,
        /* precache */ "",
        /* sounds */ ""},
    // 30
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_repulsion",
        "sound/items/flight.wav",
        {"models/runes/haste.md3", "models/runes/haste.md3", 0, 0},
        /* icon */ "icons/repulsion",
        /* pickup */ "Repulsion",
        30,
        IT_POWERUP,
        RUNE_REPULSION,
        /* precache */ "",
        /* sounds */ ""},
    // 31
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_phasing",
        "sound/items/regeneration.wav",
        {"models/runes/regen.md3", 0, 0, 0},
        /* icon */ "icons/phase",
        /* pickup */ "Phasing",
        30,
        IT_POWERUP,
        RUNE_PHASING,
        /* precache */ "",
        /* sounds */ ""},
    // 32
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_shambler",
        "sound/items/protect.wav",
        {"models/runes/resist.md3", 0, 0, 0},
        /* icon */ "icons/lightning",
        /* pickup */ "Shambler",
        30,
        IT_POWERUP,
        RUNE_SHAMBLER,
        /* precache */ "",
        /* sounds */ ""},

    // 33
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_dualrecall",
        "sound/items/protect.wav",
        {"models/runes/strength.md3", "models/runes/strength.md3", 0, 0},
        /* icon */ "icons/dual",
        /* pickup */ "Dual Recall",
        30,
        IT_POWERUP,
        RUNE_DUALRECALL,
        /* precache */ "",
        /* sounds */ ""},
    // 34
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_weirdness",
        "sound/items/flight.wav",
        {"models/runes/haste.md3", 0, 0, 0},
        /* icon */ "icons/weirdness",
        /* pickup */ "Weirdness",
        30,
        IT_POWERUP,
        RUNE_WEIRDNESS,
        /* precache */ "",
        /* sounds */ ""},
    // 35
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_phoenix",
        "sound/items/regeneration.wav",
        {"models/runes/regen.md3", 0, 0, 0},
        /* icon */ "icons/phoenix",
        /* pickup */ "Phoenix",
        30,
        IT_POWERUP,
        RUNE_PHOENIX,
        /* precache */ "",
        /* sounds */ ""},
    // 36
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_spikecloud",
        "sound/items/protect.wav",
        {"models/runes/icetrap.md3", 0, 0, 0},
        /* icon */ "icons/plague",
        /* pickup */ "Plague",
        30,
        IT_POWERUP,
        RUNE_SPIKECLOUD,
        /* precache */ "",
        /* sounds */ ""},

    // 37
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_firewalk",
        "sound/items/protect.wav",
        {"models/runes/strength.md3", 0, 0, 0},
        /* icon */ "icons/iconw_flamethrower",
        /* pickup */ "Fire Walk",
        30,
        IT_POWERUP,
        RUNE_FIREWALK,
        /* precache */ "",
        /* sounds */ ""},
    // 38
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_grapple",
        "sound/items/flight.wav",
        {"models/runes/haste.md3", 0, 0, 0},
        /* icon */ "icons/iconw_grapple",
        /* pickup */ "Grappling",
        30,
        IT_POWERUP,
        RUNE_GRAPPLE,
        /* precache */ "",
        /* sounds */ ""},
    // 39
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_athletic",
        "sound/items/regeneration.wav",
        {"models/runes/regen.md3", 0, 0, 0},
        /* icon */ "icons/athletics",
        /* pickup */ "Athletics",
        30,
        IT_POWERUP,
        RUNE_ATHLETIC,
        /* precache */ "",
        /* sounds */ ""},
    // 40
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_lumberjack",
        "sound/items/protect.wav",
        {"models/runes/resist.md3", 0, 0, 0},
        /* icon */ "icons/charm",
        /* pickup */ "Lumberjack",
        30,
        IT_POWERUP,
        RUNE_LUMBERJACK,
        /* precache */ "",
        /* sounds */ ""},

    // 41
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_houngan",
        "sound/items/protect.wav",
        {"models/runes/strength.md3", 0, 0, 0},
        /* icon */ "icons/necro",
        /* pickup */ "Houngan",
        30,
        IT_POWERUP,
        RUNE_HOUNGAN,
        /* precache */ "",
        /* sounds */ ""},
    // 42
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_piercing",
        "sound/items/flight.wav",
        {"models/runes/haste.md3", 0, 0, 0},
        /* icon */ "icons/piercing",
        /* pickup */ "Armor Piercing",
        30,
        IT_POWERUP,
        RUNE_PIERCING,
        /* precache */ "",
        /* sounds */ ""},
    // 43
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_preserve",
        "sound/items/regeneration.wav",
        {"models/runes/regen.md3", 0, 0, 0},
        /* icon */ "icons/selfpres",
        /* pickup */ "Self Preservation",
        30,
        IT_POWERUP,
        RUNE_PRESERVE,
        /* precache */ "",
        /* sounds */ ""},
    // 44
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_zenmonk",
        "sound/items/protect.wav",
        {"models/runes/resist.md3", 0, 0, 0},
        /* icon */ "icons/luck",
        /* pickup */ "Zen Monk",
        30,
        IT_POWERUP,
        RUNE_ZENMONK,
        /* precache */ "",
        /* sounds */ ""},

    // 45
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_torch",
        "sound/items/protect.wav",
        {"models/runes/strength.md3", 0, 0, 0},
        /* icon */ "icons/fire",
        /* pickup */ "Human Torch",
        30,
        IT_POWERUP,
        RUNE_TORCH,
        /* precache */ "",
        /* sounds */ ""},
    // 46
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_packrat",
        "sound/items/flight.wav",
        {"models/runes/backpack.md3", 0, 0, 0},
        /* icon */ "icons/packrat",
        /* pickup */ "Pack Rat",
        30,
        IT_POWERUP,
        RUNE_PACKRAT,
        /* precache */ "",
        /* sounds */ ""},
    // 47
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_armor",
        "sound/items/regeneration.wav",
        {"models/runes/regen.md3", 0, 0, 0},
        /* icon */ "icons/plentifularmor",
        /* pickup */ "Good Armor",
        30,
        IT_POWERUP,
        RUNE_ARMOR,
        /* precache */ "",
        /* sounds */ ""},
    // 48
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_quad",
        "sound/items/protect.wav",
        {"models/runes/resist.md3", 0, 0, 0},
        /* icon */ "icons/quad",
        /* pickup */ "Quad Damage",
        30,
        IT_POWERUP,
        RUNE_QUAD,
        /* precache */ "",
        /* sounds */ ""},

    // 49
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_jack",
        "sound/items/protect.wav",
        {"models/runes/strength.md3", 0, 0, 0},
        /* icon */ "icons/antigrav",
        /* pickup */ "Jack of All Runes",
        30,
        IT_POWERUP,
        RUNE_JACK,
        /* precache */ "",
        /* sounds */ ""},
    // 50
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_bluegoo",
        "sound/items/flight.wav",
        {"models/runes/haste.md3", 0, 0, 0},
        /* icon */ "icons/emp",
        /* pickup */ "Blue Goo",
        30,
        IT_POWERUP,
        RUNE_BLUEGOO,
        /* precache */ "",
        /* sounds */ ""},
    // 51
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_blizzard",
        "sound/items/regeneration.wav",
        {"models/runes/icetrap.md3", "models/runes/icetrap.md3", 0, 0},
        /* icon */ "icons/ice_trap",
        /* pickup */ "Blizzard",
        30,
        IT_POWERUP,
        RUNE_BLIZZARD,
        /* precache */ "",
        /* sounds */ ""},
    // 52
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_thor",
        "sound/items/protect.wav",
        {"models/runes/resist.md3", 0, 0, 0},
        /* icon */ "icons/lightning",
        /* pickup */ "Thor",
        30,
        IT_POWERUP,
        RUNE_THOR,
        /* precache */ "",
        /* sounds */ ""},

    // 53
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_sniper",
        "sound/items/protect.wav",
        {"models/runes/strength.md3", 0, 0, 0},
        /* icon */ "icons/sight",
        /* pickup */ "Sniper",
        30,
        IT_POWERUP,
        RUNE_SNIPER,
        /* precache */ "",
        /* sounds */ ""},
    // 54
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_antipack",
        "sound/items/flight.wav",
        {"models/runes/backpack.md3", 0, 0, 0},
        /* icon */ "icons/icon_backpack",
        /* pickup */ "Anti-Pack",
        30,
        IT_POWERUP,
        RUNE_ANTIPACK,
        /* precache */ "",
        /* sounds */ ""},
    // 55
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_antitele",
        "sound/items/regeneration.wav",
        {"models/runes/regen.md3", "models/runes/regen.md3", 0, 0},
        /* icon */ "icons/forcefield",
        /* pickup */ "Telefrag Deflect",
        30,
        IT_POWERUP,
        RUNE_ANTITELE,
        /* precache */ "",
        /* sounds */ ""},
    // 56
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_cluster",
        "sound/items/protect.wav",
        {"models/runes/resist.md3", 0, 0, 0},
        /* icon */ "icons/iconw_clustergrenade",
        /* pickup */ "Cluster Grenades",
        30,
        IT_POWERUP,
        RUNE_CLUSTER,
        /* precache */ "",
        /* sounds */ ""},

    // 57
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_tornado",
        "sound/items/protect.wav",
        {"models/runes/icetrap.md3", 0, 0, 0},
        /* icon */ "icons/ceasefire",
        /* pickup */ "Tornado",
        30,
        IT_POWERUP,
        RUNE_TORNADO,
        /* precache */ "",
        /* sounds */ ""},
    // 58
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_requiem",
        "sound/items/flight.wav",
        {"models/runes/haste.md3", 0, 0, 0},
        /* icon */ "icons/arsenal",
        /* pickup */ "Requiem",
        30,
        IT_POWERUP,
        RUNE_REQUIEM,
        /* precache */ "",
        /* sounds */ ""},
    // 59
    /*QUAKED item_spread (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
     */
    {
        "rune_lithium",
        "sound/items/regeneration.wav",
        {"models/runes/regen.md3", 0, 0, 0},
        /* icon */ "icons/iconw_grapple",
        /* pickup */ "Lithium Grapple",
        30,
        IT_POWERUP,
        RUNE_LITHIUM,
        /* precache */ "",
        /* sounds */ ""},
#endif
