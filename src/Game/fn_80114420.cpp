// fn_8011406C: preload the SFX bank of every venue ambience named by the level's resource list (the versus list when a role index is set).
// fn_80114420: preload the SFX bank of every active player's character.
// Built at -O0 and C++; the real name is unknown, so the symbol stays extern "C".

extern "C" {

extern int strcmp(const char *a, const char *b);
extern int strncmp(const char *a, const char *b, int n);
extern char *strcpy(char *dst, const char *src);

extern int fn_80432844(void *g);             // G+0x770
extern int fn_80432870(void *g);             // G+0x774
extern int fn_80434900(void *g);             // G+0x590, the active slot count
extern void *fn_804317BC(void *g, int i);    // &G.slots[i]
extern void *fn_8042FF2C(void *slot);        // slot+0x28, the slot's actor
extern unsigned int fn_8009ABEC(void *actor);         // actor+0x1AC, the character type ID
extern void fn_8045777C(void *bank, char *name, int n);

// The game-state object and its level-name buffer at G+0x59C (docs/versus.md section 4.1).
extern char lbl_80552110[];
extern char lbl_805526AC[];

extern void *fn_804326B4(void *table);
extern char *fn_80454384(void *list, int index);
extern void fn_80456EB8(void *x, int a);
extern void fn_80457B44(void *x);
extern void fn_8010D294(void);

extern int lbl_8066B63C;
extern int lbl_8066BD10;
extern void *lbl_8066BD88;
extern void *lbl_8066BD8C;
extern void *lbl_8066BD9C;
extern char lbl_8054EF38[]; // the versus resource list
extern char lbl_8054ED80[];

// Venue ambience banks: each venue's SFX name is followed by its two resource names.
extern char lbl_80497710[]; // "SFX_generic"
extern char lbl_8049772C[]; // "SFX_"
extern char lbl_80497734[]; // "SFX_ambiance_mansion"
extern char lbl_8049774C[]; // "AvengersMansion_NGC"
extern char lbl_80497760[]; // "SFX_ambiance_mansion_GC"
extern char lbl_80497778[]; // "SFX_ambiance_bridge"
extern char lbl_8049778C[]; // "BrooklynBridge_NGC"
extern char lbl_804977A0[]; // "SFX_ambiance_bridge_GC"
extern char lbl_804977B8[]; // "SFX_ambiance_Bugle"
extern char lbl_804977CC[]; // "DailyBugle_NGC"
extern char lbl_804977DC[]; // "SFX_ambiance_Bugle_GC"
extern char lbl_804977F4[]; // "SFX_ambiance_GrandCentral"
extern char lbl_80497810[]; // "GrandCentral_NGC"
extern char lbl_80497824[]; // "SFX_ambiance_GrandCentr_GC"
extern char lbl_80497840[]; // "SFX_ambiance_NYC"
extern char lbl_80497854[]; // "NYCStreets_NGC"
extern char lbl_80497864[]; // "SFX_ambiance_NYC_GC"
extern char lbl_80497878[]; // "SFX_ambiance_power_plant"
extern char lbl_80497894[]; // "PowerPlant_NGC"
extern char lbl_804978A4[]; // "SFX_ambiance_power_plant_GC"
extern char lbl_804978C0[]; // "SFX_ambiance_Roekel"
extern char lbl_804978D4[]; // "RoekelFacility_NGC"
extern char lbl_804978E8[]; // "SFX_ambiance_Roekel_GC"

// The bank names still belong to the auto-generated .rodata.
extern char lbl_8049771C[]; // "0_Test_Arena"
extern char lbl_80497900[]; // "SFX_Iron2"
extern char lbl_8049790C[]; // "SFX_Wolv1"
extern char lbl_80497918[]; // "SFX_Thing"
extern char lbl_80497924[]; // "SFX_Spidey"
extern char lbl_80497930[]; // "SFX_Venom"
extern char lbl_8049793C[]; // "SFX_Ohm"
extern char lbl_80497944[]; // "SFX_AfterShk"
extern char lbl_80497954[]; // "SFX_Brigade"
extern char lbl_80497960[]; // "SFX_DefCon"
extern char lbl_8049796C[]; // "SFX_Devil"
extern char lbl_80497978[]; // "SFX_Elektra"
extern char lbl_80497984[]; // "SFX_Hazmat"
extern char lbl_80497990[]; // "SFX_Heatwave"
extern char lbl_804979A0[]; // "SFX_Magneto"
extern char lbl_804979AC[]; // "SFX_Roekel"
extern char lbl_804979B8[]; // "SFX_Storm"
extern char lbl_804979C4[]; // "SFX_Torch"
extern char lbl_804979D0[]; // "SFX_Wink"

// Emits no code. A top-level `return <parameter>;` makes cc1plus drop the function-end branch pair for the functions after it.
inline int sn_return_decl(int a) { return a; }

void fn_8011406C(void)
{
    int isTestArena;
    void *list;
    int i;
    char *name;

    if (lbl_8066B63C == 0) {
        return;
    }
    if (lbl_8066BD10 != 0) {
        return;
    }
    if (lbl_8066BD9C != 0) {
        if (lbl_8066BD9C != 0) {
            fn_80456EB8(lbl_8066BD9C, 3);
        } else {
        }
        lbl_8066BD9C = 0;
    }
    fn_80457B44(lbl_8066BD8C);
    fn_8010D294();
    fn_80457B44(lbl_8066BD88);
    fn_8045777C(lbl_8066BD88, lbl_80497710, 1);
    isTestArena = strcmp(lbl_805526AC, lbl_8049771C) == 0;
    if (isTestArena == 0) {
        if (fn_80432844(lbl_80552110) || fn_80432870(lbl_80552110)) {
            list = fn_804326B4(lbl_8054EF38);
        } else {
            list = fn_804326B4(lbl_8054ED80);
        }
        for (i = 0; i <= 8; i++) {
            name = fn_80454384(list, i);
            if (*name == 0) {
                continue;
            }
            if (strncmp(name, lbl_8049772C, 4) == 0) {
                if (strcmp(name, lbl_80497734) == 0) {
                    fn_8045777C(lbl_8066BD88, lbl_8049774C, 1);
                    fn_8045777C(lbl_8066BD88, lbl_80497760, 1);
                } else if (strcmp(name, lbl_80497778) == 0) {
                    fn_8045777C(lbl_8066BD88, lbl_8049778C, 1);
                    fn_8045777C(lbl_8066BD88, lbl_804977A0, 1);
                } else if (strcmp(name, lbl_804977B8) == 0) {
                    fn_8045777C(lbl_8066BD88, lbl_804977CC, 1);
                    fn_8045777C(lbl_8066BD88, lbl_804977DC, 1);
                } else if (strcmp(name, lbl_804977F4) == 0) {
                    fn_8045777C(lbl_8066BD88, lbl_80497810, 1);
                    fn_8045777C(lbl_8066BD88, lbl_80497824, 1);
                } else if (strcmp(name, lbl_80497840) == 0) {
                    fn_8045777C(lbl_8066BD88, lbl_80497854, 1);
                    fn_8045777C(lbl_8066BD88, lbl_80497864, 1);
                } else if (strcmp(name, lbl_80497878) == 0) {
                    fn_8045777C(lbl_8066BD88, lbl_80497894, 1);
                    fn_8045777C(lbl_8066BD88, lbl_804978A4, 1);
                } else if (strcmp(name, lbl_804978C0) == 0) {
                    fn_8045777C(lbl_8066BD88, lbl_804978D4, 1);
                    fn_8045777C(lbl_8066BD88, lbl_804978E8, 1);
                } else {
                    fn_8045777C(lbl_8066BD88, name, 1);
                }
            }
        }
    }
}

void fn_80114420(void)
{
    int isTestArena;
    int p;
    char bank[0x20];
    register void *actor;

    if (lbl_8066B63C == 0) {
        return;
    }
    if (lbl_8066BD10 != 0) {
        return;
    }

    isTestArena = strcmp(lbl_805526AC, lbl_8049771C) == 0;

    if (fn_80432844(lbl_80552110) || fn_80432870(lbl_80552110) || isTestArena) {
        for (p = 0; p < fn_80434900(lbl_80552110); p++) {
            bank[0] = 0;

            actor = fn_8042FF2C(fn_804317BC(lbl_80552110, p));

            switch (fn_8009ABEC(actor)) {
            case 2: /* ironman */
                strcpy(bank, lbl_80497900);
                break;
            case 1: /* wolverine */
                strcpy(bank, lbl_8049790C);
                break;
            case 10: /* thing */
                strcpy(bank, lbl_80497918);
                break;
            case 3: /* spiderman */
                strcpy(bank, lbl_80497924);
                break;
            case 4: /* venom */
                strcpy(bank, lbl_80497930);
                break;
            case 16: /* johnnyohm */
                strcpy(bank, lbl_8049793C);
                break;
            case 15: /* aftershock */
                strcpy(bank, lbl_80497944);
                break;
            case 12: /* megalith */
                strcpy(bank, lbl_80497954);
                break;
            case 13: /* defcon */
                strcpy(bank, lbl_80497960);
                break;
            case 9: /* daredevil */
                strcpy(bank, lbl_8049796C);
                break;
            case 6: /* elektra */
                strcpy(bank, lbl_80497978);
                break;
            case 17: /* biohazard */
                strcpy(bank, lbl_80497984);
                break;
            case 18: /* heatwave */
                strcpy(bank, lbl_80497990);
                break;
            case 5: /* magneto */
                strcpy(bank, lbl_804979A0);
                break;
            case 11: /* roekel */
                strcpy(bank, lbl_804979AC);
                break;
            case 7: /* storm */
                strcpy(bank, lbl_804979B8);
                break;
            case 8: /* humantorch */
                strcpy(bank, lbl_804979C4);
                break;
            case 14: /* paradox */
                strcpy(bank, lbl_804979D0);
                break;
            }

            if (bank[0]) {
                fn_8045777C(lbl_8066BD88, bank, 1);
            }
        }
    }
}

}
