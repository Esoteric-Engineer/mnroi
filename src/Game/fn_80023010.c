// fn_80023010: fills the two aura tables for all 19 effect keys, then spawns the flame auras for the players in the match.
// The index space and what the tables hold are in docs/characters.md ("Auras"); fn_8001C258 reads the same tables.
//
// The unit owns the function's 12-byte float literal pool at 0x80484ADC.

typedef struct Color4
{
    float r;
    float g;
    float b;
    float a;
} Color4;

// One effect definition in an effect manager's table.
typedef struct EffectDef
{
    char unk0[0x24];
    int nameIndex; // +0x24 index into the manager's name table, 0 when unused
    char unk28[0x8];
} EffectDef;

typedef struct EffectManager
{
    char unk0[0x2C];
    EffectDef *defs; // +0x2C
    int numDefs;     // +0x30
    char unk34[0x10];
    char *names[1]; // +0x44
} EffectManager;

// One player slot in the game-state object (docs/versus.md section 4.1).
typedef struct Slot
{
    char unk0[0xB0];
} Slot;

typedef struct GameState
{
    char unk0[0x590];
    unsigned int numPlayers; // +0x590
} GameState;

extern int fn_80020E60(void *actor);
extern float fn_800B2620(void *actor);
extern void *fn_8042FF2C(Slot *slot);
extern Color4 *fn_8042D768(Color4 *c, float r, float g, float b, float a);
extern EffectManager *fn_80022EC8(void);
extern EffectManager *fn_80022F00(void);
extern void fn_8002298C(EffectManager *mgr, int key, int arg, Color4 *color, int n, void *actor, float x, float y);
extern int strcmp(const char *a, const char *b);

// Per aura index: the effect definition's index, and which manager holds it.
extern int lbl_805200A0[];
extern int lbl_805200EC[];

// The game-state object and its player slots (G and G+0x10).
extern char lbl_80552110[];
extern Slot lbl_80552120[];

// The effect keys still belong to the auto-generated .rodata.
extern char lbl_80484968[]; // "KEY_SMALL_EXPLOSION"
extern char lbl_8048497C[]; // "KEY_MED_EXPLOSION"
extern char lbl_80484990[]; // "KEY_LARGE_EXPLOSION"
extern char lbl_804849A4[]; // "KEY_JOHNNYOHM_AURA"
extern char lbl_804849B8[]; // "KEY_HUMANTORCH_AURA"
extern char lbl_804849CC[]; // "KEY_IRONMAN_AURA"
extern char lbl_804849E0[]; // "KEY_STORM_AURA"
extern char lbl_804849F0[]; // "KEY_BRIGADE_AURA"
extern char lbl_80484A04[]; // "KEY_ROEKEL_AURA"
extern char lbl_80484A14[]; // "KEY_HAZMAT_AURA"
extern char lbl_80484A24[]; // "KEY_SOLARA_AURA"
extern char lbl_80484A34[]; // "KEY_ALTJOHNNYOHM_AURA"
extern char lbl_80484A4C[]; // "KEY_ALTHUMANTORCH_AURA"
extern char lbl_80484A64[]; // "KEY_ALTIRONMAN_AURA"
extern char lbl_80484A78[]; // "KEY_ALTSTORM_AURA"
extern char lbl_80484A8C[]; // "KEY_ALTBRIGADE_AURA"
extern char lbl_80484AA0[]; // "KEY_ALTROEKEL_AURA"
extern char lbl_80484AB4[]; // "KEY_ALTHAZMAT_AURA"
extern char lbl_80484AC8[]; // "KEY_ALTSOLARA_AURA"

void fn_80023010(void)
{
    int i;
    char *key;
    int found;
    int which;
    int index;

    i = 0;
    while (i <= 18) {
        lbl_805200A0[i] = -1;
        lbl_805200EC[i] = 0;
        key = 0;

        switch (i) {
        case 0:
            key = lbl_80484968;
            break;
        case 1:
            key = lbl_8048497C;
            break;
        case 2:
            key = lbl_80484990;
            break;
        case 3:
            key = lbl_804849A4;
            break;
        case 4:
            key = lbl_804849B8;
            break;
        case 5:
            key = lbl_804849CC;
            break;
        case 6:
            key = lbl_804849E0;
            break;
        case 7:
            key = lbl_804849F0;
            break;
        case 8:
            key = lbl_80484A04;
            break;
        case 9:
            key = lbl_80484A14;
            break;
        case 10:
            key = lbl_80484A24;
            break;
        case 11:
            key = lbl_80484A34;
            break;
        case 12:
            key = lbl_80484A4C;
            break;
        case 13:
            key = lbl_80484A64;
            break;
        case 14:
            key = lbl_80484A78;
            break;
        case 15:
            key = lbl_80484A8C;
            break;
        case 16:
            key = lbl_80484AA0;
            break;
        case 17:
            key = lbl_80484AB4;
            break;
        case 18:
            key = lbl_80484AC8;
            break;
        /* No `break`: the DOL falls out of the switch. */
        default:
            key = 0;
        }

        if (key != 0) {
            int j;
            int n;

            found = 0;
            which = 0;
            index = 0;

            for (j = 0; j < fn_80022EC8()->numDefs && !found; j++) {
                n = fn_80022EC8()->defs[j].nameIndex;
                if (n > 0) {
                    char *name = fn_80022EC8()->names[n];
                    if (strcmp(name, key) == 0) {
                        found = 1;
                        which = 0;
                        index = j;
                    }
                }
            }

            {
                int k;

                for (k = 0; k < fn_80022F00()->numDefs && !found; k++) {
                    n = fn_80022F00()->defs[k].nameIndex;
                    if (n > 0) {
                        char *name = fn_80022F00()->names[n];
                        if (strcmp(name, key) == 0) {
                            found = 1;
                            which = 1;
                            index = k;
                        }
                    }
                }
            }

            if (found) {
                lbl_805200A0[i] = index;
                lbl_805200EC[i] = which;
            }
        }

        i++;
    }

    {
        int p;
        int aura;
        void *actor;
        int type;

        for (p = 0; p < ((GameState *)lbl_80552110)->numPlayers; p++) {
            aura = -1;
            actor = fn_8042FF2C(&lbl_80552120[p]);
            type = fn_80020E60(actor);

            switch (type) {
            case 8: /* humantorch */
                aura = 4;
                break;
            case 18: /* heatwave */
                aura = 10;
                break;
            case 28: /* alt_humantorch */
                aura = 12;
                break;
            case 38: /* alt_heatwave */
                aura = 18;
                break;
            default:
                break;
            }

            if (aura != -1) {
                if (lbl_805200A0[aura] != -1) {
                    Color4 color;

                    fn_8042D768(&color, 0.0f, 0.0f, fn_800B2620(actor) * 0.5f, 1.0f);
                    fn_8002298C(fn_80022EC8(), lbl_805200A0[aura], lbl_805200EC[aura], &color, 1, actor, 0.0f, 0.0f);
                }
            }
        }

        return;
    }

    return;
}
