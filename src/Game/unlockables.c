// Roster, venue, card and comic tables; see docs/versus.md section 5 (row 2) and docs/characters.md section 2.

typedef struct CharacterRecord
{
    char name[0x20]; // +0x00
    char key[0x20];  // +0x20
    signed char stats[6]; // +0x40, intel, strength, speed, durability, energy, skill
    signed char pad[2];   // +0x46
    int unlocked;         // +0x48
} CharacterRecord;

typedef struct Rec
{
    char name[0x20]; // +0x00
    char key[0x20];  // +0x20
    int unlocked;    // +0x40
} Rec;

CharacterRecord lbl_804CA51C[20] = {
    { "plr_wolverine", "~kT_WOLVERINE", { 2, 4, 2, 4, 1, 7 }, { 0, 0 }, 1 },
    { "plr_ironman", "~kT_IRONMAN", { 6, 6, 5, 6, 6, 3 }, { 0, 0 }, 0 },
    { "plr_wolverine", "~kT_WOLVERINE", { 2, 4, 2, 4, 1, 7 }, { 0, 0 }, 1 },
    { "plr_spiderman", "~kT_SPIDERMAN", { 4, 4, 3, 3, 1, 4 }, { 0, 0 }, 1 },
    { "plr_venom", "~kT_VENOM", { 2, 4, 2, 4, 1, 2 }, { 0, 0 }, 0 },
    { "plr_magneto", "~kT_MAGNETO", { 5, 2, 5, 6, 5, 3 }, { 0, 0 }, 0 },
    { "plr_elektra", "~kT_ELEKTRA", { 3, 2, 2, 3, 1, 6 }, { 0, 0 }, 1 },
    { "plr_storm", "~kT_STORM", { 2, 2, 3, 2, 5, 3 }, { 0, 0 }, 0 },
    { "plr_humantorch", "~kT_HUMANTORCH", { 2, 2, 5, 2, 5, 3 }, { 0, 0 }, 0 },
    { "plr_daredevil", "~kT_DAREDEVIL", { 3, 2, 2, 2, 1, 6 }, { 0, 0 }, 0 },
    { "plr_thing", "~kT_THING", { 2, 6, 2, 6, 1, 5 }, { 0, 0 }, 1 },
    { "plr_defcon", "~kT_DEFCON1", { 3, 5, 3, 6, 3, 6 }, { 0, 0 }, 0 },
    { "plr_biohazard", "~kT_BIOHAZARD", { 5, 3, 2, 4, 4, 2 }, { 0, 0 }, 0 },
    { "plr_aftershock", "~kT_AFTERSHOCK", { 5, 3, 2, 4, 4, 2 }, { 0, 0 }, 0 },
    { "plr_johnnyohm", "~kT_JOHNNYOHM", { 2, 3, 3, 3, 4, 4 }, { 0, 0 }, 1 },
    { "plr_paradox", "~kT_PARADOX", { 3, 2, 4, 2, 1, 5 }, { 0, 0 }, 1 },
    { "plr_heatwave", "~kT_HEATWAVE", { 3, 2, 3, 3, 5, 3 }, { 0, 0 }, 0 },
    { "plr_megalith", "~kT_MEGALITH", { 4, 5, 2, 5, 4, 6 }, { 0, 0 }, 0 },
    { "plr_roekel", "~kT_VANROEKEL", { 6, 6, 3, 7, 4, 3 }, { 0, 0 }, 0 },
    { "plr_thing", "~kT_THING", { 2, 6, 2, 6, 1, 5 }, { 0, 0 }, 1 },
};

CharacterRecord lbl_804CAB0C[20] = {
    { "plr_altWolverine", "~kT_WOLVERINE", { 2, 4, 2, 4, 1, 7 }, { 0, 0 }, 1 },
    { "plr_altIronman", "~kT_IRONMAN", { 6, 7, 5, 6, 6, 3 }, { 0, 0 }, 0 },
    { "plr_altWolverine", "~kT_WOLVERINE", { 2, 4, 2, 4, 1, 7 }, { 0, 0 }, 1 },
    { "plr_altSpiderman", "~kT_SPIDERMAN", { 4, 4, 3, 3, 1, 4 }, { 0, 0 }, 1 },
    { "plr_altVenom", "~kT_VENOM", { 2, 4, 2, 4, 1, 2 }, { 0, 0 }, 0 },
    { "plr_altMagneto", "~kT_MAGNETO", { 5, 2, 5, 6, 5, 3 }, { 0, 0 }, 0 },
    { "plr_altElektra", "~kT_ELEKTRA", { 2, 4, 2, 4, 1, 7 }, { 0, 0 }, 1 },
    { "plr_altStorm", "~kT_STORM", { 2, 2, 3, 2, 5, 3 }, { 0, 0 }, 0 },
    { "plr_altHumantorch", "~kT_HUMANTORCH", { 2, 2, 5, 2, 5, 3 }, { 0, 0 }, 0 },
    { "plr_altDaredevil", "~kT_DAREDEVIL", { 3, 2, 2, 2, 1, 5 }, { 0, 0 }, 0 },
    { "plr_altThing", "~kT_THING", { 2, 6, 2, 6, 1, 5 }, { 0, 0 }, 1 },
    { "plr_altDefcon", "~kT_DEFCON1", { 3, 5, 4, 6, 3, 6 }, { 0, 0 }, 0 },
    { "plr_altBiohazard", "~kT_BIOHAZARD", { 5, 3, 2, 4, 4, 2 }, { 0, 0 }, 0 },
    { "plr_altAftershock", "~kT_AFTERSHOCK", { 2, 2, 2, 3, 4, 2 }, { 0, 0 }, 0 },
    { "plr_altJohnnyohm", "~kT_JOHNNYOHM", { 5, 3, 3, 3, 4, 4 }, { 0, 0 }, 1 },
    { "plr_altParadox", "~kT_PARADOX", { 3, 2, 4, 2, 1, 5 }, { 0, 0 }, 1 },
    { "plr_altHeatwave", "~kT_HEATWAVE", { 2, 2, 3, 3, 5, 3 }, { 0, 0 }, 0 },
    { "plr_altMegalith", "~kT_MEGALITH", { 4, 5, 2, 5, 4, 6 }, { 0, 0 }, 0 },
    { "plr_altRoekel", "~kT_VANROEKEL", { 6, 6, 3, 7, 4, 3 }, { 0, 0 }, 0 },
    { "plr_altThing", "~kT_THING", { 2, 6, 2, 6, 1, 5 }, { 0, 0 }, 1 },
};

int lbl_804CB0FC[20] = { 0, 10, 2, 15, 6, 14, 3, 9, 7, 13, 4, 16, 8, 1, 17, 5, 12, 11, 18, 0 };

Rec lbl_804CB14C[7] = {
    { "BrooklynBridge", "~kT_BROOKLYNBRIDGE", 1 },
    { "NYCStreets", "~kT_NYCSTREET", 1 },
    { "AvengersMansion", "~kT_AVENGERSMANSION", 1 },
    { "DailyBugle", "~kT_DAILYBUGLE", 0 },
    { "GrandCentralStation", "~kT_GRANDCENTRALSTATION", 0 },
    { "PowerPlant", "~kT_POWERPLANT", 0 },
    { "RoekelFacility", "~kT_ROEKELFACILITY", 0 },
};

Rec lbl_804CB328[43] = {
    { "~kT_CARDS0", "~kT_CARDSDESC0", 0 },
    { "~kT_CARDS1", "~kT_CARDSDESC1", 0 },
    { "~kT_CARDS2", "~kT_CARDSDESC2", 0 },
    { "~kT_CARDS3", "~kT_CARDSDESC3", 0 },
    { "~kT_CARDS4", "~kT_CARDSDESC4", 0 },
    { "~kT_CARDS5", "~kT_CARDSDESC5", 0 },
    { "~kT_CARDS6", "~kT_CARDSDESC6", 0 },
    { "~kT_CARDS7", "~kT_CARDSDESC7", 0 },
    { "~kT_CARDS8", "~kT_CARDSDESC8", 0 },
    { "~kT_CARDS9", "~kT_CARDSDESC9", 0 },
    { "~kT_CARDS10", "~kT_CARDSDESC10", 0 },
    { "~kT_CARDS11", "~kT_CARDSDESC11", 0 },
    { "~kT_CARDS12", "~kT_CARDSDESC12", 0 },
    { "~kT_CARDS13", "~kT_CARDSDESC13", 0 },
    { "~kT_CARDS14", "~kT_CARDSDESC14", 0 },
    { "~kT_CARDS15", "~kT_CARDSDESC15", 0 },
    { "~kT_CARDS16", "~kT_CARDSDESC16", 0 },
    { "~kT_CARDS17", "~kT_CARDSDESC17", 0 },
    { "~kT_CARDS18", "~kT_CARDSDESC18", 0 },
    { "~kT_CARDS19", "~kT_CARDSDESC19", 0 },
    { "~kT_CARDS20", "~kT_CARDSDESC20", 0 },
    { "~kT_CARDS21", "~kT_CARDSDESC21", 0 },
    { "~kT_CARDS22", "~kT_CARDSDESC22", 0 },
    { "~kT_CARDS23", "~kT_CARDSDESC23", 0 },
    { "~kT_CARDS24", "~kT_CARDSDESC24", 0 },
    { "~kT_CARDS25", "~kT_CARDSDESC25", 0 },
    { "~kT_CARDS26", "~kT_CARDSDESC26", 0 },
    { "~kT_CARDS27", "~kT_CARDSDESC27", 0 },
    { "~kT_CARDS28", "~kT_CARDSDESC28", 0 },
    { "~kT_CARDS29", "~kT_CARDSDESC29", 0 },
    { "~kT_CARDS30", "~kT_CARDSDESC30", 0 },
    { "~kT_CARDS31", "~kT_CARDSDESC31", 0 },
    { "~kT_CARDS32", "~kT_CARDSDESC32", 0 },
    { "~kT_CARDS33", "~kT_CARDSDESC33", 0 },
    { "~kT_CARDS34", "~kT_CARDSDESC34", 0 },
    { "~kT_CARDS35", "~kT_CARDSDESC35", 0 },
    { "~kT_CARDS36", "~kT_CARDSDESC36", 0 },
    { "~kT_CARDS37", "~kT_CARDSDESC37", 0 },
    { "~kT_CARDS38", "~kT_CARDSDESC38", 0 },
    { "~kT_CARDS39", "~kT_CARDSDESC39", 0 },
    { "~kT_CARDS40", "~kT_CARDSDESC40", 0 },
    { "~kT_CARDS41", "~kT_CARDSDESC41", 0 },
    { "~kT_CARDS42", "~kT_CARDSDESC42", 0 },
};

int lbl_804CBE94[9] = { 0 };

Rec lbl_804CBEB8[25] = {
    { "~kT_COMIC0", "~kT_COMICDESC0", 0 },
    { "~kT_COMIC1", "~kT_COMICDESC1", 0 },
    { "~kT_COMIC2", "~kT_COMICDESC2", 0 },
    { "~kT_COMIC3", "~kT_COMICDESC3", 0 },
    { "~kT_COMIC4", "~kT_COMICDESC4", 0 },
    { "~kT_COMIC5", "~kT_COMICDESC5", 0 },
    { "~kT_COMIC6", "~kT_COMICDESC6", 0 },
    { "~kT_COMIC7", "~kT_COMICDESC7", 0 },
    { "~kT_COMIC8", "~kT_COMICDESC8", 0 },
    { "~kT_COMIC9", "~kT_COMICDESC9", 0 },
    { "~kT_COMIC10", "~kT_COMICDESC10", 0 },
    { "~kT_COMIC11", "~kT_COMICDESC11", 0 },
    { "~kT_COMIC12", "~kT_COMICDESC12", 0 },
    { "~kT_COMIC13", "~kT_COMICDESC13", 0 },
    { "~kT_COMIC14", "~kT_COMICDESC14", 0 },
    { "~kT_COMIC15", "~kT_COMICDESC15", 0 },
    { "~kT_COMIC16", "~kT_COMICDESC16", 0 },
    { "~kT_COMIC17", "~kT_COMICDESC17", 0 },
    { "~kT_COMIC18", "~kT_COMICDESC18", 0 },
    { "~kT_COMIC19", "~kT_COMICDESC19", 0 },
    { "~kT_COMIC20", "~kT_COMICDESC20", 0 },
    { "~kT_COMIC21", "~kT_COMICDESC21", 0 },
    { "~kT_COMIC22", "~kT_COMICDESC22", 0 },
    { "~kT_COMIC23", "~kT_COMICDESC23", 0 },
    { "~kT_COMIC24", "~kT_COMICDESC24", 0 },
};
