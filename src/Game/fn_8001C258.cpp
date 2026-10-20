// fn_8001C258: turn a character's aura effect on or off.
//
// Called as fn_8001C258(actor, 1) / fn_8001C258(actor, 0) from 0x800BF2A0 and 0x800BF458, right after fn_800BE9AC(actor, 1/0).
//
// Only the five energy characters have an aura here: the switch maps the type ID fn_80020E60 returns (see Game/fn_80020E60.c) to an aura index, with the alternate costume (type + 20) landing on index + 8.
// 
// fn_80023010 fills the two tables the index addresses and spawns the same effect with 1 where this one passes 2.
//
// Built at -O0 and C++, not C: the two branches to the epilogue at 0x8001C4F8 are the C++ tail (docs/prodg.md). The real name is unknown, so the symbol stays extern "C".
// The unit owns the function's 12-byte float literal pool at 0x804845DC.

typedef struct Color4
{
    float r;
    float g;
    float b;
    float a;
} Color4;

// One live effect in the effect manager's table.
typedef struct Effect
{
    char unk0[0x30];
    int type;    // +0x30
    void *owner; // +0x34 the actor the effect is attached to
    char unk38[0x18];
} Effect;

typedef struct EffectManager
{
    char unk0[0x390];
    Effect effects[64]; // +0x390
    int numEffects;     // +0x1790
} EffectManager;

extern "C" {
extern int fn_80020E60(void *actor);
extern float fn_800B2620(void *actor);
extern Color4 *fn_8042D768(Color4 *c, float r, float g, float b, float a);
extern EffectManager *fn_80022EC8(void);
extern void fn_8002298C(EffectManager *mgr, int key, int arg, Color4 *color, int n, void *actor, float x, float y);
extern void fn_8002289C(EffectManager *mgr, int index);
}

// Effect handles, filled in at runtime; fn_80023010 reads the same two tables.
extern int lbl_805200A0[]; // -1 when the character has no aura effect loaded
extern int lbl_805200EC[];

extern "C" void fn_8001C258(void *actor, int enable)
{
    int type;
    int aura;
    Color4 color;
    int i;
    Effect *effect;

    type = fn_80020E60(actor);
    aura = -1;

    switch (type) {
    case 16: /* johnnyohm */
        aura = 3;
        break;
    case 2: /* ironman */
        aura = 5;
        break;
    case 7: /* storm */
        aura = 6;
        break;
    case 12: /* megalith */
        aura = 7;
        break;
    case 11: /* roekel */
        aura = 8;
        break;
    case 36: /* alt_johnnyohm */
        aura = 11;
        break;
    case 22: /* alt_ironman */
        aura = 13;
        break;
    case 27: /* alt_storm */
        aura = 14;
        break;
    case 32: /* alt_megalith */
        aura = 15;
        break;
    case 31: /* alt_roekel */
        aura = 16;
        break;
    default:
        break;
    }

    if (aura != -1) {
        if (lbl_805200A0[aura] != -1) {
            if (enable) {
                fn_8042D768(&color, 0.0f, 0.0f, fn_800B2620(actor) * 0.5f, 1.0f);
                fn_8002298C(fn_80022EC8(), lbl_805200A0[aura], lbl_805200EC[aura], &color, 2, actor, 0.0f, 0.0f);
            } else {
                for (i = 0; i < fn_80022EC8()->numEffects; i++) {
                    effect = &fn_80022EC8()->effects[i];
                    if (effect->type == 2 && effect->owner == actor) {
                        fn_8002289C(fn_80022EC8(), i);
                        i = 0;
                    }
                }
            }
        }
    }
}
