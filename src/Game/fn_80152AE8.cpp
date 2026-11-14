// Task methods (enter, exit, update per class), from SLEEP on; see docs/ai.md row 12 and section 4.4.
// Owns .rodata 0x8049B838-0x8049B9B8.

struct Ent {
    int pad;
};

struct PEnt : Ent { // matching_notes 44
    int x;
    char pad8[0x300];
    unsigned int f308; // +0x308, bit 0x4000 tested by SEARCH
};

struct Ctl {
    int pad;
};

struct SCtl : Ctl { // reference arguments convert, matching_notes 50
    int x;
};

struct TaskBase {
    int pad;
};

struct Task : TaskBase {
    int x;
};

struct Vec {
    float x, y, z;
};

struct Self {
    void *ai;    // +0x0
    void *brain; // +0x4
};

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

extern "C" {
void *fn_80464068(void *ai);
void *fn_80462780(void *ai);
void fn_804618B0(void *set);
int fn_80151B90(void *brain, void *task);
void *fn_8015105C(void *brain, int id);
void fn_8046412C(void *ai, int bit);
void fn_80464170(void *ai, int bit);
float fn_80461F94(void *ai);
float fn_8046439C(void *ai);
float fn_80461F10(void *ai);
float fn_80461F68(void *ai);
float fn_80464318(void *ai);
float fn_80461EE4(void *ai);
void fn_80442130(void *ai, unsigned int bit);
void fn_80442174(void *ai, unsigned int bit);
PEnt *fn_80442080(void *ai);
int fn_80133208(void *actor);
int fn_801368B8(void *ai);
float fn_8015E64C(void *ai);
float fn_800B1884(Ent &actor, int id);
Ent *fn_80134870(void *ai);
int fn_800B0C58(void *actor);
void *fn_804420D8(void *ai);
void fn_8014F7B0(void *list, int mode);
char *fn_804420AC(void *ai);
int fn_800B13D8(void *actor);
void fn_8014B63C(char *mover, int handle, int flag);
void *fn_800B14A0(Ent &e);
SCtl *fn_80085954(void *e);
SCtl *fn_8044203C(void *ai);
int fn_800CCF90(Ctl &c);
int fn_800CCB38(Ctl &c);
int fn_800CCBD8(Ctl &c);
int fn_800CC6DC(Ctl &c);
int fn_800CD21C(Ctl &c);
int fn_800CCC28(Ctl &c);
int fn_800CC96C(Ctl &c);
int fn_800CCA58(Ctl &c);
void *Entity_GetActor(Ctl &c);
float fn_80086730(void *actor);
float fn_8008677C(void *actor);
int fn_801500C4(void *list);
int fn_8015EC1C(float chance);
int fn_8015E97C(float chance);
void *fn_80442104(void *ai);
int fn_80151AF8(void *brain, int id);
extern char lbl_80593BE8[];
unsigned int fn_8042EFF8(void *clock);
void fn_80464208(void *ai, unsigned int t);
void fn_80464290(void *ai, unsigned int t);
int fn_80464230(void *ai);
int fn_8015F410(void *ai, float min);
void *fn_80461DD4(void *ai);
int fn_80442508(void *set, int bit);
float fn_80464344(void *ai);
float fn_80462A04(void *ai);
int fn_8015FFD4(void *ai);
int fn_80086374(void *actor);
int fn_8015EE34(void *ai, Ent *e);
int fn_8015EEA0(void *ai);
int fn_8015EF54(void *ai);
int fn_804628AC(void *ai);
int fn_80461D48(void *ai, int bit);
int fn_80085F7C(void *actor);
int fn_80086B1C(void *actor);
int fn_80086B6C(void *actor);
int fn_8044734C(char *mover);
int fn_80444570(int wp);
int fn_8015EA18(unsigned int n);
int fn_804642B8(void *ai);
int fn_8015F008(void *ai);
Vec *fn_800B1724(Ent &e);
Vec *fn_800B1750(Ent &e);
float fn_8015E580(Vec *a, Vec *b);
float fn_800B2620(Ent &e);
int fn_8015F384(void *ai);
float fn_8015E8A8(void *ai, Vec *p);
int fn_80461B58(char *mover);
Ent *fn_8015F7A4(Ent *actor, float range, int mode, Vec *dir, float cosmin);
int fn_8015E764(void *ai, Vec *p);
void fn_80442414(TaskBase *task, int v);
int fn_8008606C(void *actor);
int fn_8015E830(void *ai);
int fn_801514C0(void *brain, int id);
int fn_800B18EC(Ent &e, int id);
int fn_80085D3C(void *actor);
int fn_801369B0(void *ai);
PEnt *fn_8014F8BC(void *list);
void fn_8014B900(char *mover);
float fn_8014B824(char *mover);
int fn_8015F07C(void *ai);
int fn_80085300(void *actor, Vec *node, float a, float b, float *out);
int fn_800CE4D0(void *ctl);
float fn_8042CE28(unsigned int n);
float fn_80464094(void *ai);
void fn_801513D8(void *brain, int len);
void fn_804643C8(Self *task, int done);
int fn_804643F0(Self *task);
void *fn_800CD9B0(Ctl &c);
int fn_800B0CC0(void *e);
void *fn_800B1478(void *e);
int fn_800A4130(void *e);
void fn_80136214(void *ai, int n);
int fn_80462624(char *mover);
int fn_80151430(void *brain);
void fn_804641B4(void *ai, int v);
int fn_804641DC(void *ai);
float fn_80462A30(void *ai);
float fn_80464370(void *ai);
float fn_80462A5C(void *ai);
float fn_80461FC0(void *ai);
int fn_8008615C(void *actor);
int fn_800860FC(void *actor);
void *fn_801332C0(void *actor);
unsigned int fn_80148024(void *grp);
int fn_8008612C(void *actor);
int fn_8008603C(void *actor);
void *fn_8013726C(void *ai);
void *fn_8014630C(void *p, Vec *pos);
int fn_800CCA08(Ctl &c);
int fn_800CDA20(Ctl &c);
int fn_800CD014(Ctl &c);
int fn_800CCE00(Ctl &c);
int fn_800CCAE8(Ctl &c);
int fn_8015F4A4(void *ai, float f);
int fn_800865E4(void *actor);
int fn_8015F6CC(void *ai, Vector *out);
void fn_8042DC84(Vector *dst, Vec *src);
void fn_8042D8A8(Vector *dst, Vector *src);
float fn_8042EBF4(Vector *a, Vector *b);
float fn_8042EC54(Vector *v);
int fn_800866C0(void *actor);
unsigned int fn_8015EA6C(int n, float *w);
int fn_800B24AC(Ent &e);
int fn_800B1CC8(Ent &e);
int fn_8004A9CC(Vec *from, Vector *dir, float len, int a, int b, int c, int d, int e, int f);
int fn_804421B8(void *ai, unsigned int bit);
}

inline int sn_return_decl(int a) { return a; } // sets the flag: no function-end branch pair (prodg.md)

// SLEEP enter
extern "C" int fn_80152AE8(register Self *self)
{
    fn_804618B0(fn_80464068(self->ai));
    fn_804618B0(fn_80462780(self->ai));
    return 1;
}

// SLEEP exit
extern "C" int fn_80152B48(register Self *self)
{
    return 1;
}

// SLEEP update
extern "C" int fn_80152B70(register Self *self)
{
    if (fn_80151B90(self->brain, self)) {
        fn_8015105C(self->brain, 1);
    } else {
    }
    return 1;
}

// SEARCH enter
extern "C" int fn_80152BD0(register Self *self)
{
    fn_8046412C(self->ai, 0);
    fn_8046412C(self->ai, 5);
    fn_8046412C(self->ai, 3);
    if (fn_80461F94(self->ai) > 0.0f)
        fn_8046412C(self->ai, 1);
    if (fn_8046439C(self->ai) > 0.0f)
        fn_8046412C(self->ai, 2);
    fn_8046412C(self->ai, 6);
    fn_804618B0(fn_80462780(self->ai));
    fn_80442130(self->ai, 0x1a);
    fn_80442130(self->ai, 0x1c);
    fn_80442130(self->ai, 0);
    if (fn_80133208(fn_80442080(self->ai))) {
        if (fn_80461F10(self->ai) > 0.0f)
            fn_80442130(self->ai, 1);
        else if (fn_80461F68(self->ai) > 0.0f)
            fn_80442130(self->ai, 2);
        if (fn_80464318(self->ai) > 0.0f)
            fn_80442130(self->ai, 0x1d);
    }
    fn_80442130(self->ai, 3);
    fn_80442130(self->ai, 4);
    fn_80442130(self->ai, 0xf);
    if (fn_801368B8(self->ai)) {
        register float d = fn_8015E64C(self->ai);
        if (d >= fn_800B1884(*fn_80442080(self->ai), 0xd4))
            fn_80442130(self->ai, 0xe);
    }
    fn_80442130(self->ai, 0x15);
    fn_80442130(self->ai, 0x16);
    fn_80442130(self->ai, 0x17);
    fn_80442130(self->ai, 0x1b);
    if (!fn_80134870(self->ai) || (fn_80134870(self->ai) && !fn_800B0C58(fn_80134870(self->ai))))
        fn_8014F7B0(fn_804420D8(self->ai), 0);
    if (fn_80134870(self->ai))
        fn_8014B63C(fn_804420AC(self->ai), fn_800B13D8(fn_80134870(self->ai)), 1);
    return 1;
}

// SEARCH exit
extern "C" int fn_80152EB8(register Self *self)
{
    fn_80464170(self->ai, 4);
    if (fn_80461F94(self->ai) > 0.0f)
        fn_80464170(self->ai, 1);
    if (fn_8046439C(self->ai) > 0.0f)
        fn_80464170(self->ai, 2);
    if (fn_80461EE4(self->ai) > 0.0f)
        fn_80442174(self->ai, 0x12);
    return 1;
}

// SEARCH update
extern "C" int fn_80152F74(register Self *self)
{
    if (fn_80134870(self->ai) && fn_800B0C58(fn_80134870(self->ai))) {
        Ent *t = fn_80134870(self->ai);
        if (fn_800CCF90(*fn_80085954(fn_800B14A0(*t)))) {
            int n = fn_801500C4(fn_804420D8(self->ai));
            if (n > 2 && fn_8015EC1C((fn_80461F94(self->ai) + fn_8046439C(self->ai)) / 2.0f)) {
                if (fn_80151AF8(fn_80442104(self->ai), 4)) {
                    fn_80464290(self->ai, fn_8042EFF8(lbl_80593BE8) - 1);
                    fn_80464208(self->ai, fn_8042EFF8(lbl_80593BE8) - 1);
                    fn_8015105C(fn_80442104(self->ai), 4);
                    return 1;
                }
            } else if (fn_8015F410(self->ai, 0.75f) && !fn_80151AF8(fn_80442104(self->ai), 0x19)) {
                fn_8015105C(fn_80442104(self->ai), 0x19);
                return 1;
            }
        }
    }
    if (fn_80151B90(self->brain, self)) {
        if (fn_800CCB38(*fn_8044203C(self->ai))) {
            fn_8015105C(fn_80442104(self->ai), 0x12);
            return 1;
        }
        if ((fn_80442508(fn_80461DD4(self->ai), 1) && fn_8015E97C(fn_80464344(self->ai) / 100.0f * 20.0f))
            || (fn_80442508(fn_80461DD4(self->ai), 2) && fn_8015E97C(fn_80462A04(self->ai) / 100.0f * 80.0f))
            || fn_8015FFD4(self->ai))
            fn_80442130(self->ai, 7);
        else
            fn_80442174(self->ai, 7);
        if (fn_80134870(self->ai) && fn_800B0C58(fn_80134870(self->ai))
            && fn_800CCBD8(*fn_80085954(fn_800B14A0(*fn_80134870(self->ai))))
            && fn_80086374(fn_800B14A0(*fn_80134870(self->ai)))
            && (fn_8015EE34(self->ai, fn_80134870(self->ai)) || fn_8015EEA0(self->ai))
            && fn_8015E64C(self->ai) < fn_800B1884(*fn_80442080(self->ai), 0xd4))
            fn_80442130(self->ai, 7);
        if (fn_804628AC(self->ai) && fn_80461D48(self->ai, 0x3c) && fn_80085F7C(fn_80442080(self->ai)))
            fn_80442130(self->ai, 0xe);
        float a = fn_80464318(self->ai) / 100.0f;
        float b = fn_80461EE4(self->ai) / 100.0f;
        float c = fn_80461F94(self->ai) / 100.0f;
        float d = fn_8046439C(self->ai) / 100.0f;
        if (fn_80086B1C(fn_80442080(self->ai)) || fn_80086B6C(fn_80442080(self->ai))
            || fn_800CCBD8(*fn_8044203C(self->ai)) || fn_800CC6DC(*fn_8044203C(self->ai)) == 5) {
        } else {
            int busy = 0;
            if (fn_8044734C(fn_804420AC(self->ai)) && fn_80444570(fn_8044734C(fn_804420AC(self->ai))))
                busy = 1;
            if (fn_80461F94(self->ai) > 0.0f) {
                if (fn_80461D48(self->ai, 0xc) && fn_801500C4(fn_804420D8(self->ai)) > 0.0f) {
                    fn_8015105C(self->brain, 7);
                    return 1;
                }
                if (fn_80461D48(self->ai, 0xb) && fn_80464230(self->ai) && !busy) {
                    fn_8015105C(self->brain, 4);
                    int wait = fn_8015EA18(4) * 100 * (int)(100.0f - fn_80461F94(self->ai)) + 7500;
                    fn_80464208(self->ai, fn_8042EFF8(lbl_80593BE8) + wait);
                    return 1;
                }
            }
            if (fn_8046439C(self->ai) > 0.0f) {
                if (fn_80461D48(self->ai, 0xe)) {
                    fn_8015105C(self->brain, 8);
                    return 1;
                }
                if (fn_80461D48(self->ai, 0xd) && fn_804642B8(self->ai) && !fn_80461D48(self->ai, 0x2b) && !busy
                    && fn_8015EE34(self->ai, fn_80134870(self->ai)) && fn_801500C4(fn_804420D8(self->ai)) > 0.0f) {
                    fn_8015105C(self->brain, 5);
                    int wait = fn_8015EA18(4) * 100 * (int)(100.0f - fn_8046439C(self->ai)) + 10000;
                    fn_80464290(self->ai, fn_8042EFF8(lbl_80593BE8) + wait);
                    return 1;
                }
            }
        }
        if (fn_80461D48(self->ai, 3) && !fn_80461D48(self->ai, 4) && fn_80461D48(self->ai, 0x2b)
            && fn_80461F68(self->ai) > 0.0f) {
            fn_8015105C(self->brain, 3);
            return 1;
        }
        int flag12 = fn_8015F008(self->ai);
        if (fn_800CD21C(*fn_8044203C(self->ai))) {
            float chance = fn_80464344(self->ai) / 100.0f * 5.0f;
            if (fn_8015E97C(chance))
                fn_80442130(self->ai, 7);
        }
        float range211 = fn_800B1884(*fn_80442080(self->ai), 0xd3);
        float range210 = fn_800B1884(*fn_80442080(self->ai), 0xd2);
        float range212 = fn_800B1884(*fn_80442080(self->ai), 0xd4);
        float range213 = fn_800B1884(*fn_80442080(self->ai), 0xd5);
        if (fn_80442080(self->ai)->f308 & 0x4000) {
            range212 = range211;
            range213 = range212;
        }
        Ent *target = fn_80134870(self->ai);
        if (target && fn_800B0C58(target)) {
            float dist = fn_8015E580(fn_800B1724(*fn_80442080(self->ai)), fn_800B1724(*target));
            int near = dist <= range211;
            int mid = dist >= range212 && dist <= range213;
            if (fn_800CCC28(*fn_80085954(fn_800B14A0(*target))))
                near = dist <= range210;
            if (dist > range212 + range210 || fn_800CC6DC(*fn_80085954(fn_800B14A0(*target))) == 13) {
                if (fn_80086730(Entity_GetActor(*fn_8044203C(self->ai)))
                        < fn_8008677C(Entity_GetActor(*fn_8044203C(self->ai))) * 0.4f
                    && !fn_8015F384(self->ai) && !fn_80461D48(self->ai, 0x3f)) {
                    fn_8015105C(fn_80442104(self->ai), 0x19);
                    return 1;
                }
            }
            if (fn_800CC96C(*fn_8044203C(self->ai))) {
                float dz = fn_800B1724(*fn_80442080(self->ai))->z - fn_800B1724(*target)->z;
                if (dz > fn_800B2620(*fn_80134870(self->ai)) && dist < range212 && dist > range211)
                    near = 1;
            }
            if (fn_8015E64C(self->ai) < fn_800B1884(*fn_80442080(self->ai), 0xd3)
                && (fn_8015EEA0(self->ai) || fn_8015EF54(self->ai))) {
                if (fn_8015E8A8(self->ai, fn_800B1724(*target)) > fn_800B1884(*fn_80442080(self->ai), 0xd8)) {
                    if (!fn_80461D48(self->ai, 0x14) && fn_8015EC1C(fn_80461F68(self->ai))) {
                        fn_8015105C(self->brain, 3);
                    } else if (fn_80461B58(fn_804420AC(self->ai))) {
                        void *p = fn_8015F7A4(fn_80442080(self->ai), 20.0f, 2,
                                              fn_800B1750(*fn_80442080(self->ai)), 0.0f);
                        if (p && fn_801500C4(fn_804420D8(self->ai)) > 0)
                            fn_8015105C(self->brain, 4);
                    }
                } else if (fn_8015EC1C(fn_80461F10(self->ai))) {
                    fn_8015105C(self->brain, 2);
                } else {
                    fn_8015105C(self->brain, 4);
                }
            }
            if (fn_80461F10(self->ai) > 0.0f && near && fn_8015EE34(self->ai, target)) {
                if (fn_8015E764(self->ai, fn_800B1724(*target))) {
                    TaskBase *task = (TaskBase *)(Task *)fn_8015105C(self->brain, 2);
                    if (task && fn_80461D48(self->ai, 0x2e)) {
                        fn_80442414(task, 1);
                        fn_80442130(self->ai, 8);
                    }
                } else {
                    fn_80442130(self->ai, 1);
                    fn_80442174(self->ai, 2);
                    if (fn_8008606C(fn_80442080(self->ai))) {
                        if (fn_8015E830(self->ai))
                            fn_80442130(self->ai, 0x20);
                        else
                            fn_80442174(self->ai, 0x20);
                    }
                }
            } else if (fn_8015EC1C(fn_80461F68(self->ai)) && mid) {
                int same = fn_801514C0(self->brain, 3) > fn_800B18EC(*fn_80442080(self->ai), 0xc7);
                if ((same && !fn_80085D3C(fn_80442080(self->ai)))
                    || (same && fn_80085D3C(fn_80442080(self->ai))
                        && (fn_801369B0(self->ai) || fn_80086B1C(fn_80442080(self->ai))
                            || fn_80086B6C(fn_80442080(self->ai))))) {
                    fn_8015105C(self->brain, 3);
                } else {
                    fn_80442130(self->ai, 1);
                    fn_80442174(self->ai, 2);
                }
            } else if (!fn_8015EE34(self->ai, target) && fn_800CCA58(*fn_80085954(fn_800B14A0(*target)))
                       && fn_8015E8A8(self->ai, fn_800B1724(*fn_80134870(self->ai)))
                              > fn_800B1884(*fn_80442080(self->ai), 0xd7)
                       && !fn_8015F008(self->ai)) {
                fn_8015105C(self->brain, 2);
            } else {
                int same = fn_801514C0(self->brain, 3) > fn_800B18EC(*fn_80442080(self->ai), 0xc7);
                if (!fn_80086B6C(fn_80442080(self->ai)) && !fn_80086B1C(fn_80442080(self->ai))
                    && fn_8015EC1C(fn_80461F68(self->ai)) && mid && same) {
                    fn_80442174(self->ai, 1);
                    fn_80442130(self->ai, 2);
                } else {
                    fn_80442130(self->ai, 1);
                    fn_80442174(self->ai, 2);
                }
                fn_8014B63C(fn_804420AC(self->ai), fn_800B13D8(target), 0);
                if (fn_8008606C(fn_80442080(self->ai))) {
                    if (fn_8015E830(self->ai))
                        fn_80442130(self->ai, 0x20);
                    else
                        fn_80442174(self->ai, 0x20);
                }
                return 1;
            }
        } else if (!target) {
            target = fn_8014F8BC(fn_804420D8(self->ai));
            if (target) {
                if (!fn_80461B58(fn_804420AC(self->ai)))
                    fn_8014B63C(fn_804420AC(self->ai), fn_800B13D8(target), 0);
                if (fn_80461F10(self->ai) > 0.0f)
                    fn_8015105C(self->brain, 2);
            } else {
                fn_8014B900(fn_804420AC(self->ai));
            }
        }
        if (fn_80461D48(self->ai, 0x1c) && fn_801368B8(self->ai))
            fn_80442130(self->ai, 0xe);
        float dh = fn_800B1724(*fn_80442080(self->ai))->z - fn_8014B824(fn_804420AC(self->ai)) < 0.0f
            ? -(fn_800B1724(*fn_80442080(self->ai))->z - fn_8014B824(fn_804420AC(self->ai)))
            : fn_800B1724(*fn_80442080(self->ai))->z - fn_8014B824(fn_804420AC(self->ai));
        if (dh > 4.0f || fn_80086B1C(fn_80442080(self->ai)) || fn_80086B6C(fn_80442080(self->ai))) {
            if (fn_801368B8(self->ai)) {
                fn_80442130(self->ai, 0xe);
            } else if (fn_80134870(self->ai)) {
                if (!fn_80461B58(fn_804420AC(self->ai)) || fn_8015E97C(1.0f))
                    fn_80464208(self->ai, fn_8042EFF8(lbl_80593BE8));
            }
        } else if (fn_80134870(self->ai) && fn_8015F07C(self->ai)) {
            float out;
            int hit = fn_80085300(fn_80442080(self->ai), fn_800B1724(*fn_80442080(self->ai)), 0.7f, 4.0f, &out);
            if (hit) {
                if (fn_801368B8(self->ai))
                    fn_80442174(self->ai, 0xe);
                else
                    fn_8014B63C(fn_804420AC(self->ai), fn_800B13D8(fn_80134870(self->ai)), 0);
            }
        }
        if (fn_80461D48(self->ai, 0x1d))
            fn_80442130(self->ai, 0x1b);
        if (flag12)
            fn_80442130(self->ai, 0x12);
        else
            fn_80442174(self->ai, 0x12);
    } else {
    }
    return 1;
}

// MELEE enter
extern "C" int fn_801546B0(register Self *self)
{
    fn_80442130(self->ai, 0);
    if (fn_80461F68(self->ai) > 0.0f)
        fn_8046412C(self->ai, 0);
    fn_8046412C(self->ai, 3);
    fn_8046412C(self->ai, 5);
    fn_8046412C(self->ai, 6);
    fn_804618B0(fn_80462780(self->ai));
    fn_80442130(self->ai, 0x1a);
    fn_80442130(self->ai, 0x1c);
    fn_80442130(self->ai, 0);
    fn_80442130(self->ai, 4);
    fn_80442130(self->ai, 1);
    fn_80442130(self->ai, 0x1b);
    fn_80442130(self->ai, 0x1d);
    if (fn_801368B8(self->ai) && fn_800CE4D0(fn_8044203C(self->ai)))
        fn_80442130(self->ai, 0xe);
    fn_80442130(self->ai, 0x15);
    fn_80442130(self->ai, 0x16);
    fn_80442130(self->ai, 0x17);
    fn_80442130(self->ai, 8);
    unsigned int n = 1500;
    n += fn_8015EA18(1500);
    float len = fn_8042CE28(n);
    len = 1.0f - fn_80461EE4(self->ai) / 100.0f >= 0.25f
        ? (1.0f - fn_80461EE4(self->ai) / 100.0f <= 1.0f ? (1.0f - fn_80461EE4(self->ai) / 100.0f) * len : len)
        : len * 0.25f;
    len = len / fn_80464094(self->ai);
    fn_801513D8(self->brain, (int)len);
    fn_80442414((TaskBase *)self, 0);
    fn_8014F7B0(fn_804420D8(self->ai), 0);
    if (fn_80134870(self->ai))
        fn_8014B63C(fn_804420AC(self->ai), fn_800B13D8(fn_80134870(self->ai)), 1);
    return 1;
}

// MELEE exit
extern "C" int fn_801549A8(register Self *self)
{
    return 1;
}

// MELEE update: weighs ten attack choices, picks one with fn_8015EA6C and sets the task length.
extern "C" int fn_801549D0(register Self *self)
{
    if (fn_80151B90(self->brain, self)) {
        if (!fn_80461D48(self->ai, 2)) {
            fn_804643C8(self, 1);
            return 1;
        }
        if (fn_800CCB38(*fn_8044203C(self->ai))) {
            fn_8015105C(fn_80442104(self->ai), 0x12);
            return 1;
        }
        void *grab = fn_800CD9B0(*fn_8044203C(self->ai));
        if (grab) {
            if (fn_800B0CC0(grab)) {
                if (fn_800A4130(fn_800B1478(grab)))
                    fn_8015105C(fn_80442104(self->ai), 8);
                else
                    fn_8015105C(fn_80442104(self->ai), 7);
            }
            fn_804643C8(self, 1);
            return 1;
        }
        if (fn_80461D48(self->ai, 0x14)) {
            fn_80136214(self->ai, 8);
            fn_804643C8(self, 1);
            return 1;
        }
        if (fn_80462624(fn_804420AC(self->ai)) == 1) {
            fn_804643C8(self, 1);
            return 1;
        }
        if (fn_80461D48(self->ai, 3)) {
            if (fn_80461D48(self->ai, 4)) {
                fn_804643C8(self, 1);
                return 1;
            } else if (fn_80461D48(self->ai, 0x2b) && fn_8015F008(self->ai)) {
                fn_804643C8(self, 1);
                return 1;
            }
        }
        if (fn_80134870(self->ai)
            && fn_8015E8A8(self->ai, fn_800B1724(*fn_80134870(self->ai))) > fn_800B1884(*fn_80442080(self->ai), 0xd8)) {
            fn_804643C8(self, 1);
            return 1;
        }
        if (fn_801368B8(self->ai) && fn_80461D48(self->ai, 0x1c)) {
            if (!fn_8015EE34(self->ai, fn_80134870(self->ai)) && !fn_80461D48(self->ai, 0x28))
                fn_80442130(self->ai, 0xe);
            else
                fn_80442174(self->ai, 0xe);
        }
        int ready = !fn_80151430(self->brain);
        if (ready) {
            if (!fn_8015F008(self->ai) || fn_8015EEA0(self->ai) || fn_8015EF54(self->ai)) {
                unsigned int n = 1500;
                float w[10];
                fn_80442174(self->ai, 8);
                fn_80442174(self->ai, 7);
                fn_80442174(self->ai, 0xd);
                fn_80442174(self->ai, 0x11);
                fn_80442174(self->ai, 0x19);
                fn_80442174(self->ai, 0xa);
                fn_80442174(self->ai, 0xb);
                fn_80442174(self->ai, 0xc);
                fn_80442174(self->ai, 3);
                fn_80442174(self->ai, 0x13);
                if (fn_80085D3C(fn_80442080(self->ai))) {
                    float hp = fn_80086730(fn_80442080(self->ai)) / fn_8008677C(fn_80442080(self->ai));
                    if (hp < 0.33f)
                        fn_804641B4(self->ai, 1);
                    else if (hp > 0.66f)
                        fn_804641B4(self->ai, 0);
                }
                w[0] = fn_80461EE4(self->ai) * 3.0f * fn_80461F10(self->ai);
                w[1] = fn_80461EE4(self->ai) * (fn_804641DC(self->ai) ? 6.0f : 3.0f) * fn_80462A30(self->ai);
                w[2] = fn_80464318(self->ai) * (fn_804641DC(self->ai) ? 9.0f : 3.0f) * fn_80464344(self->ai);
                w[3] = fn_80464318(self->ai) * 3.2f * fn_80462A30(self->ai);
                w[4] = fn_80461EE4(self->ai) * 3.0f * fn_80464370(self->ai);
                w[5] = (101.0f - fn_80461EE4(self->ai)) * (101.0f - fn_80461F10(self->ai));
                w[6] = fn_80461EE4(self->ai) * 2.0f * fn_80462A5C(self->ai);
                w[7] = (101.0f - fn_80461EE4(self->ai)) * 100.0f;
                w[8] = fn_80461EE4(self->ai) * 10.0f * fn_80461FC0(self->ai);
                w[9] = fn_80461EE4(self->ai) * fn_80461F94(self->ai);
                if (fn_8008615C(fn_80442080(self->ai)))
                    w[9] *= 3.0f;
                if (!fn_80461D48(self->ai, 0x25) && !fn_80461D48(self->ai, 0x30))
                    w[2] = 0.0f;
                if (!fn_800860FC(fn_80442080(self->ai)) || !fn_80085F7C(fn_80442080(self->ai)))
                    w[9] = 0.0f;
                if (fn_80461D48(self->ai, 0x28)) {
                    w[4] = 0.0f;
                    if (fn_804643F0(self) == 1) {
                    } else {
                        w[1] = 0.0f;
                        w[2] = 0.0f;
                    }
                    w[3] = 0.0f;
                    w[5] = 0.0f;
                    w[6] = 0.0f;
                    w[7] = 0.0f;
                    w[0] *= 3.0f;
                }
                if (fn_80461D48(self->ai, 0x27)) {
                    w[1] = 0.0f;
                    w[3] = 0.0f;
                    w[2] = 0.0f;
                    w[5] = 0.0f;
                    w[9] *= 2.0f;
                    w[6] *= 2.0f;
                }
                void *grp = fn_801332C0(fn_80442080(self->ai));
                if (grp && fn_80148024(grp) <= 1) {
                    w[5] = 0.0f;
                    w[7] = 0.0f;
                    w[4] *= 2.0f;
                    if (!fn_80085D3C(fn_80442080(self->ai)))
                        w[0] *= 2.0f;
                }
                if (fn_804643F0(self) == 1) {
                    fn_80442414((TaskBase *)self, 0);
                    if (fn_8015EC1C(fn_80464370(self->ai))) {
                        w[4] *= 2.0f;
                        w[0] = 0.0f;
                    } else {
                        w[4] = 0.0f;
                        w[0] *= 2.0f;
                    }
                    w[3] = 0.0f;
                    w[5] = 0.0f;
                    w[6] = 0.0f;
                    w[7] = 0.0f;
                    if (fn_80461D48(self->ai, 0x28)) {
                        if (fn_8015EC1C(fn_80462A30(self->ai))) {
                            w[1] *= 2.0f;
                            w[2] = 0.0f;
                        } else {
                            w[1] = 0.0f;
                            w[2] *= 2.0f;
                        }
                    } else {
                        w[1] = 0.0f;
                        w[2] = 0.0f;
                    }
                }
                if (!fn_800860FC(fn_80442080(self->ai))
                    && fn_8015E64C(self->ai) >= fn_800B1884(*fn_80442080(self->ai), 0xd2))
                    w[4] = 0.0f;
                if (fn_80134870(self->ai) && !fn_8015EE34(self->ai, fn_80134870(self->ai))) {
                    w[0] = 0.0f;
                    w[1] = 0.0f;
                    w[3] = 0.0f;
                }
                if (!fn_8008612C(fn_80442080(self->ai)) && !fn_8008603C(fn_80442080(self->ai)))
                    w[8] = 0.0f;
                else if (!fn_8014630C(fn_8013726C(self->ai), fn_800B1724(*fn_80442080(self->ai))))
                    w[8] = 0.0f;
                if (fn_80461D48(self->ai, 0x35)) {
                    w[5] = 0.0f;
                    w[7] = 0.0f;
                } else {
                    w[4] = 0.0f;
                    w[0] = 0.0f;
                    w[2] = 0.0f;
                    w[5] = 0.0f;
                    w[6] = 0.0f;
                }
                if (fn_80134870(self->ai) && fn_800B0C58(fn_80134870(self->ai))) {
                    void *te = fn_800B14A0(*fn_80134870(self->ai));
                    if (fn_800CCA08(*fn_80085954(te)) || fn_800CDA20(*fn_80085954(te)) || fn_80461D48(self->ai, 0x30))
                        w[3] *= 3.2f;
                    if (fn_800CD014(*fn_80085954(te)) || fn_800CCE00(*fn_80085954(te)) || fn_80461D48(self->ai, 0x30))
                        w[1] *= 3.0f;
                }
                if (fn_80462624(fn_804420AC(self->ai)) == 1
                    || fn_8015E64C(self->ai) < fn_800B1884(*fn_80442080(self->ai), 0xd3))
                    w[6] = 0.0f;
                if (!fn_8015F4A4(self->ai, 0.33f) && fn_80085D3C(fn_80442080(self->ai))) {
                    if (fn_80464344(self->ai) > 0.0f)
                        w[2] = fn_80461EE4(self->ai) * 2.0f * 100.0f;
                    if (fn_80462A30(self->ai) > 0.0f)
                        w[1] = fn_80461EE4(self->ai) * 2.0f * 100.0f;
                }
                if (fn_800865E4(fn_80442080(self->ai)) && !fn_80461D48(self->ai, 0x28)) {
                    w[0] = 0.0f;
                    w[1] = 0.0f;
                    w[2] = 0.0f;
                    w[3] = 0.0f;
                    w[4] = 10000.0f;
                    w[5] = 0.0f;
                    w[6] = 0.0f;
                    w[8] = 0.0f;
                    w[9] = 0.0f;
                }
                Vector dir;
                fn_8015F6CC(self->ai, &dir);
                Vector face;
                fn_8042DC84(&face, fn_800B1750(*fn_80442080(self->ai)));
                float dist = fn_8015E64C(self->ai);
                int inRange = dist > fn_800B1884(*fn_80442080(self->ai), 0xd3)
                    && dist < fn_800B1884(*fn_80442080(self->ai), 0xd4);
                float dot = fn_8042EBF4(&face, &dir);
                if (fn_80461D48(self->ai, 0x3d) || dot < 0.66f || !inRange)
                    w[6] = 0.0f;
                if (fn_80461D48(self->ai, 0x40)) {
                    w[6] = 0.0f;
                    w[0] = 0.0f;
                    w[3] = 0.0f;
                    w[1] = 0.0f;
                }
                Ent *target = fn_80134870(self->ai);
                if (target && fn_800B0C58(target) && fn_80085D3C(fn_80442080(self->ai))
                    && !fn_80461D48(self->ai, 0x28) && fn_800866C0(fn_800B14A0(*target))) {
                    w[1] = 0.0f;
                    w[2] = 0.0f;
                    w[3] = 0.0f;
                    w[4] = 0.0f;
                    w[5] = 0.0f;
                    w[6] = 0.0f;
                    w[7] = 0.0f;
                    w[8] = 0.0f;
                    w[9] = 0.0f;
                }
                if (fn_8015E64C(self->ai) < fn_800B1884(*fn_80442080(self->ai), 0xd1))
                    w[1] = 0.0f;
                unsigned int choice = fn_8015EA6C(10, w);
                switch (choice) {
                case 0:
                    if (fn_8015EEA0(self->ai) && !fn_80461D48(self->ai, 0x3d)) {
                        fn_80442130(self->ai, 0xb);
                    } else {
                        fn_80442130(self->ai, 8);
                        n = 1000;
                    }
                    break;
                case 1:
                    fn_80442130(self->ai, 0x19);
                    fn_80442174(self->ai, 1);
                    fn_80442174(self->ai, 7);
                    n /= 2;
                    break;
                case 2:
                    fn_80442130(self->ai, 7);
                    fn_80442174(self->ai, 1);
                    fn_80442174(self->ai, 3);
                    break;
                case 3:
                    if (fn_8015EC1C(fn_80462A30(self->ai))) {
                        fn_80442130(self->ai, 0x19);
                    } else {
                        fn_80442130(self->ai, 0xd);
                        fn_80442174(self->ai, 1);
                        fn_80442174(self->ai, 3);
                        n /= 2;
                    }
                    break;
                case 4: {
                    Vector from;
                    fn_8042DC84(&from, fn_800B1724(*fn_80442080(self->ai)));
                    from.z += 1.0f;
                    Vector to;
                    fn_8042DC84(&to, fn_800B1724(*fn_80134870(self->ai)));
                    to.z += 1.0f;
                    Vector ray;
                    fn_8042DC84(&ray, (Vec *)&to);
                    fn_8042D8A8(&ray, &from);
                    float len = fn_8042EC54(&ray);
                    len -= 1.0f;
                    if (len < 0.0f)
                        len = 0.0f;
                    int hit = 0;
                    if (len > 0.5f)
                        hit = fn_8004A9CC(fn_800B1724(*fn_80442080(self->ai)), &ray, len, 1, 0,
                                          fn_800B24AC(*fn_80442080(self->ai)), fn_800B1CC8(*fn_80442080(self->ai)),
                                          fn_800B13D8(fn_80134870(self->ai)), 0);
                    if (hit) {
                        fn_80442130(self->ai, 1);
                        fn_80442174(self->ai, 0x11);
                    } else {
                        fn_80442174(self->ai, 1);
                        fn_80442130(self->ai, 0x11);
                    }
                    break;
                }
                case 5:
                    fn_80442174(self->ai, 1);
                    fn_80442174(self->ai, 3);
                    n /= 2;
                    break;
                case 6:
                    if (!fn_8015EA18(4)
                        || (fn_8015E64C(self->ai) < fn_800B1884(*fn_80442080(self->ai), 0xd2) && fn_8015EEA0(self->ai)))
                        fn_80442130(self->ai, 0xb);
                    else if (!fn_8015EA18(3)
                             || (fn_8015E64C(self->ai) < fn_800B1884(*fn_80442080(self->ai), 0xd2)
                                 && fn_8015EF54(self->ai)))
                        fn_80442130(self->ai, 0xc);
                    else
                        fn_80442130(self->ai, 0xa);
                    fn_80442130(self->ai, 1);
                    break;
                case 7:
                    fn_804643C8(self, 1);
                    return 1;
                    break;
                case 8:
                    if (fn_80461D48(self->ai, 0x28)) {
                        fn_80442130(self->ai, 8);
                    } else {
                        fn_8015105C(fn_80442104(self->ai), 0x15);
                        return 1;
                    }
                    break;
                case 9:
                    fn_8015105C(fn_80442104(self->ai), 4);
                    fn_804643C8(self, 1);
                    return 1;
                    break;
                }
                n += fn_8015EA18(1500);
                float t = fn_8042CE28(n);
                t = 1.0f - fn_80461EE4(self->ai) / 100.0f >= 0.25f
                    ? (1.0f - fn_80461EE4(self->ai) / 100.0f <= 1.0f ? (1.0f - fn_80461EE4(self->ai) / 100.0f) * t : t)
                    : t * 0.25f;
                t = t / fn_80464094(self->ai);
                fn_801513D8(self->brain, (int)t);
            } else {
                fn_804643C8(self, 1);
            }
        }
        if (fn_804628AC(self->ai)) {
            if (fn_80085F7C(fn_80442080(self->ai)))
                fn_80442130(self->ai, 0xe);
            if (fn_8008606C(fn_80442080(self->ai)))
                fn_80442130(self->ai, 0x20);
        }
        if (fn_8008606C(fn_80442080(self->ai))) {
            if (fn_8015E830(self->ai))
                fn_80442130(self->ai, 0x20);
            else
                fn_80442174(self->ai, 0x20);
        }
        if ((fn_80442508(fn_80461DD4(self->ai), 1) && fn_8015E97C(fn_80464344(self->ai) / 100.0f * 20.0f))
            || (fn_80442508(fn_80461DD4(self->ai), 2) && fn_8015E97C(fn_80462A04(self->ai) / 100.0f * 80.0f))
            || fn_8015FFD4(self->ai)) {
            if (!fn_804421B8(self->ai, 0x19))
                fn_80442130(self->ai, 7);
        }
        if (fn_800CD21C(*fn_8044203C(self->ai))) {
            float chance = fn_80464344(self->ai) / 100.0f * 5.0f;
            if (fn_8015E97C(chance))
                fn_80442130(self->ai, 7);
        }
        if (fn_80134870(self->ai) && fn_800B0C58(fn_80134870(self->ai))
            && fn_800CCBD8(*fn_80085954(fn_800B14A0(*fn_80134870(self->ai))))
            && fn_80086374(fn_800B14A0(*fn_80134870(self->ai)))
            && (fn_8015EE34(self->ai, fn_80134870(self->ai)) || fn_8015EEA0(self->ai))
            && fn_8015E64C(self->ai) < fn_800B1884(*fn_80442080(self->ai), 0xd4)) {
            if (fn_8015EC1C(fn_80462A30(self->ai))) {
                if (!fn_804421B8(self->ai, 7))
                    fn_80442130(self->ai, 0x19);
            } else {
                if (!fn_804421B8(self->ai, 0x19))
                    fn_80442130(self->ai, 7);
            }
        }
        if (!fn_80461D48(self->ai, 0x3d) && !fn_804421B8(self->ai, 0xb) && !fn_804421B8(self->ai, 0xc)
            && !fn_804421B8(self->ai, 0xa) && fn_8015E64C(self->ai) < fn_800B1884(*fn_80442080(self->ai), 0xd2)) {
            if (fn_8015EEA0(self->ai))
                fn_80442130(self->ai, 0xb);
            else if (fn_8015EF54(self->ai))
                fn_80442130(self->ai, 0xc);
        }
        if (!fn_804628AC(self->ai)) {
            if (fn_800CCA58(*fn_8044203C(self->ai)) && !fn_8015F008(self->ai))
                fn_80442174(self->ai, 0xe);
            if (fn_800CCAE8(*fn_8044203C(self->ai)) && !fn_8015F008(self->ai))
                fn_80442174(self->ai, 0x20);
        }
        if (fn_804421B8(self->ai, 0x19) && fn_8015E64C(self->ai) < fn_800B1884(*fn_80442080(self->ai), 0xd1)) {
            fn_80442174(self->ai, 0x19);
            fn_801513D8(fn_80442104(self->ai), 0);
        }
    } else {
    }
    return 1;
}

struct RangedTask : Self {
    char pad8[0x20];
    int f28; // +0x28, set by the script API for RANGEDONLY
};

// RANGED enter
extern "C" int fn_801567F0(register RangedTask *self)
{
    register float d;
    register PEnt *e;
    self->f28 = 0;
    fn_804618B0(fn_80462780(self->ai));
    fn_80442130(self->ai, 0);
    if (fn_80461F68(self->ai) > 0.0f)
        fn_8046412C(self->ai, 0);
    fn_8046412C(self->ai, 3);
    fn_8046412C(self->ai, 5);
    fn_80442174(self->ai, 1);
    fn_80442130(self->ai, 2);
    fn_80442130(self->ai, 4);
    fn_80442130(self->ai, 9);
    fn_80442174(self->ai, 8);
    fn_8046412C(self->ai, 6);
    fn_80442130(self->ai, 0x1a);
    fn_80442130(self->ai, 0x1c);
    if (fn_801368B8(self->ai)) {
        d = fn_8015E64C(self->ai);
        e = fn_80442080(self->ai);
        if (d >= fn_800B1884(*e, 0xd4))
            fn_80442130(self->ai, 0xe);
    }
    float t = fn_80461F68(self->ai) * 2000.0f + 1000.0f;
    fn_801513D8(self->brain, (unsigned int)(fn_80464094(self->ai) * 1500.0f));
    fn_80442130(self->ai, 0x15);
    fn_80442130(self->ai, 0x16);
    fn_80442130(self->ai, 0x17);
    if (fn_80134870(self->ai))
        fn_8014B63C(fn_804420AC(self->ai), fn_800B13D8(fn_80134870(self->ai)), 1);
    return 1;
}

// RANGED exit
extern "C" int fn_80156A50(register RangedTask *self)
{
    self->f28 = 0;
    return 1;
}

#define ABS(x) ((x) < 0.0f ? -(x) : (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

struct Body {
    char pad0[0x50];
    float f50, f54; // +0x50
    char pad58[0x8];
    float f60, f64; // +0x60
    char pad68[0x130];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5(Vector *out, int a); // vtable +0x30
};

struct BodyD : Body { // matching_notes 44
    int x;
};

extern "C" {
Body *fn_80134870B(void *ai) __asm__("fn_80134870");
BodyD *fn_80442080B(void *ai) __asm__("fn_80442080");
void fn_8042D8A8V(Vector *dst, Vec *src) __asm__("fn_8042D8A8");
float fn_8042EBF4V(Vector *a, Vec *b) __asm__("fn_8042EBF4");
int fn_8004A9CCV(Vector *from, Vector *dir, float len, int a, int b, int c, int d, int e, int f) __asm__("fn_8004A9CC");
int fn_8008618C(void *actor);
}

// RANGED update: weighs eight ranged choices and checks the line of fire with a raycast.
extern "C" int fn_80156A88(register RangedTask *self)
{
    if (fn_80151B90(self->brain, self)) {
        if (!fn_80461D48(self->ai, 2)) {
            fn_804643C8(self, 1);
            return 1;
        }
        int ready = !fn_80151430(self->brain);
        if (!fn_801369B0(self->ai) && fn_80085D3C(fn_80442080(self->ai))) {
            fn_804643C8(self, 1);
            return 0;
        }
        if (!fn_8015F008(self->ai) && fn_80134870(self->ai) && fn_8015EE34(self->ai, fn_80134870(self->ai))) {
            if (!fn_80461D48(self->ai, 4) && fn_80461D48(self->ai, 0x2b)) {
            } else {
                fn_804643C8(self, 1);
            }
        } else if (ready) {
            register unsigned int base = 1500;
            unsigned int n = 1500;
            if (fn_80461D48(self->ai, 0x2b) && fn_8015EC1C(fn_80461F68(self->ai))) {
                fn_80442130(self->ai, 9);
                n = 3000;
                return 1;
            }
            fn_80442174(self->ai, 9);
            fn_80442174(self->ai, 0x19);
            fn_80442174(self->ai, 0xa);
            fn_80442174(self->ai, 2);
            fn_80442174(self->ai, 0xd);
            fn_80442174(self->ai, 7);
            fn_80442174(self->ai, 1);
            fn_80442174(self->ai, 0x13);
            float m25 = 0.0f;
            if (fn_80461D48(self->ai, 0x25))
                m25 = 1.0f;
            float m28 = 0.0f;
            if (!fn_80461D48(self->ai, 0x28))
                m28 = 1.0f;
            float w[8];
            w[0] = fn_80461EE4(self->ai) * 3.0f * fn_80461F68(self->ai);
            w[1] = 2.0f * fn_80464318(self->ai) * fn_80462A30(self->ai);
            w[2] = 2.0f * fn_80464318(self->ai) * fn_80464344(self->ai) * m25;
            w[3] = 2.0f * fn_80464318(self->ai) * fn_80462A30(self->ai);
            w[4] = 2.0f * (100.0f - fn_80461EE4(self->ai)) * (100.0f - fn_80461F68(self->ai));
            w[5] = (100.0f - fn_80461EE4(self->ai)) * 100.0f;
            w[6] = 2.0f * fn_80461EE4(self->ai) * fn_80461F94(self->ai);
            w[7] = 2.0f * fn_80461EE4(self->ai) * fn_80461F68(self->ai);
            if (fn_80461D48(self->ai, 3) && !fn_80461D48(self->ai, 4) && fn_80461D48(self->ai, 0x2b)) {
                w[2] = 0.0f;
                w[4] = 0.0f;
                w[5] = 0.0f;
                w[1] = 0.0f;
            }
            if (!fn_800860FC(fn_80442080(self->ai)))
                w[6] = 0.0f;
            if (fn_800CCA58(*fn_8044203C(self->ai)))
                w[0] *= 2.0f;
            if (!fn_801368B8(self->ai) || !fn_8015F410(self->ai, 0.3f))
                w[7] = 0.0f;
            if (!fn_80461D48(self->ai, 0x25) && !fn_80461D48(self->ai, 0x2c) && !fn_80461D48(self->ai, 0x2d)
                && !fn_80461D48(self->ai, 0x30))
                w[1] = 0.0f;
            Vector dir;
            fn_80134870B(self->ai)->s5(&dir, 0);
            fn_8042D8A8V(&dir, fn_800B1724(*fn_80442080(self->ai)));
            float len = fn_8042EC54(&dir);
            float dot = fn_8042EBF4V(&dir, fn_800B1750(*fn_80442080(self->ai)));
            float ext = MAX(ABS(fn_80134870B(self->ai)->f60 - fn_80134870B(self->ai)->f50),
                            ABS(fn_80134870B(self->ai)->f64 - fn_80134870B(self->ai)->f54));
            len -= ext;
            Vector from;
            fn_80442080B(self->ai)->s5(&from, 0);
            int hit = fn_8004A9CCV(&from, &dir, len, 0x8000, 0, fn_800B24AC(*fn_80442080(self->ai)),
                                   fn_800B1CC8(*fn_80442080(self->ai)), 0, 3);
            if (hit)
                w[0] = 0.0f;
            unsigned int choice = fn_8015EA6C(8, w);
            switch (choice) {
            case 0:
                fn_80442130(self->ai, 9);
                if (fn_8008618C(fn_80442080(self->ai)))
                    n = 750;
                else
                    n = 3000;
                break;
            case 1:
                fn_80442130(self->ai, 0x19);
                fn_80442174(self->ai, 7);
                break;
            case 2:
                fn_80442130(self->ai, 7);
                break;
            case 3:
                fn_80442130(self->ai, 0xd);
                n /= 2;
                break;
            case 4:
                fn_80442174(self->ai, 2);
                n /= 4;
                break;
            case 5:
                fn_804643C8(self, 1);
                break;
            case 6:
                fn_8015105C(fn_80442104(self->ai), 4);
                return 1;
            case 7:
                fn_8015105C(fn_80442104(self->ai), 0x18);
                return 1;
            }
            n += fn_8015EA18(1500);
            float t = fn_8042CE28(n);
            t = 1.0f - fn_80461EE4(self->ai) / 100.0f >= 0.25f
                ? (1.0f - fn_80461EE4(self->ai) / 100.0f <= 1.0f ? (1.0f - fn_80461EE4(self->ai) / 100.0f) * t : t)
                : t * 0.25f;
            t = t / fn_80464094(self->ai);
            fn_801513D8(self->brain, (int)t);
        } else {
            if (fn_80461D48(self->ai, 3) && !fn_80461D48(self->ai, 0x2b)) {
                if (fn_8008606C(fn_80442080(self->ai)) || fn_801368B8(self->ai)) {
                    fn_80442130(self->ai, 1);
                    fn_80442174(self->ai, 2);
                    if (!fn_80461B58(fn_804420AC(self->ai)) && fn_80134870(self->ai))
                        fn_8014B63C(fn_804420AC(self->ai), fn_800B13D8(fn_80134870(self->ai)), 0);
                }
                if (fn_8008606C(fn_80442080(self->ai))) {
                    if (fn_8015E830(self->ai))
                        fn_80442130(self->ai, 0x20);
                    else
                        fn_80442174(self->ai, 0x20);
                }
            } else if (fn_8008606C(fn_80442080(self->ai))) {
                fn_80442174(self->ai, 0x20);
            }
            Vector dir;
            fn_80134870B(self->ai)->s5(&dir, 0);
            fn_8042D8A8V(&dir, fn_800B1724(*fn_80442080(self->ai)));
            float len = fn_8042EC54(&dir);
            float dot = fn_8042EBF4V(&dir, fn_800B1750(*fn_80442080(self->ai)));
            float ext = MAX(ABS(fn_80134870B(self->ai)->f60 - fn_80134870B(self->ai)->f50),
                            ABS(fn_80134870B(self->ai)->f64 - fn_80134870B(self->ai)->f54));
            len -= ext;
            Vector from;
            fn_80442080B(self->ai)->s5(&from, 0);
            int hit = fn_8004A9CCV(&from, &dir, len, 0x8000, 0, fn_800B24AC(*fn_80442080(self->ai)),
                                   fn_800B1CC8(*fn_80442080(self->ai)), 0, 3);
            if (hit)
                fn_804643C8(self, 1);
        }
        if ((fn_80442508(fn_80461DD4(self->ai), 1) && fn_8015E97C(fn_80464344(self->ai) / 100.0f * 20.0f))
            || (fn_80442508(fn_80461DD4(self->ai), 2) && fn_8015E97C(fn_80462A04(self->ai) / 100.0f * 80.0f))
            || fn_8015FFD4(self->ai))
            fn_80442130(self->ai, 7);
    } else {
    }
    return 1;
}

extern "C" {
int fn_80463F90(void *finder);
int fn_80463FBC(void *finder);
Ent *fn_800ACFA8(int handle);
void fn_801501AC(void *finder, Ent *actor);
}

// FINDTHROWABLE enter: done at once when the held actor is far enough from its throw target.
extern "C" int fn_80157D58(register Self *self)
{
    register SCtl *c;
    if (fn_80134870(self->ai) && fn_800B0C58(fn_80134870(self->ai))) {
        c = fn_80085954(fn_800B14A0(*fn_80134870(self->ai)));
        if (!fn_800CCF90(*c)) {
            float d = fn_8015E8A8(self->ai, fn_800B1724(*fn_80134870(self->ai)));
            if (d > 3.0f) {
                fn_804643C8(self, 1);
                return 0;
            }
        }
    }
    fn_8046412C(self->ai, 1);
    fn_8046412C(self->ai, 3);
    fn_8046412C(self->ai, 5);
    fn_804618B0(fn_80462780(self->ai));
    fn_80442130(self->ai, 1);
    fn_80442130(self->ai, 0x1a);
    fn_80442130(self->ai, 0x1c);
    fn_80442130(self->ai, 4);
    fn_80442130(self->ai, 0xf);
    fn_80442130(self->ai, 0);
    fn_80442130(self->ai, 0x1d);
    if (fn_801368B8(self->ai))
        fn_80442130(self->ai, 0xe);
    if (fn_8008606C(fn_80442080(self->ai)))
        fn_80442130(self->ai, 0x20);
    Ent *t = fn_800ACFA8(fn_80463F90(fn_804420D8(self->ai)));
    if (t)
        fn_801501AC(fn_804420D8(self->ai), t);
    fn_801513D8(self->brain, 5000);
    return 1;
}

// FINDTHROWABLE exit
extern "C" int fn_80157F88(register Self *self)
{
    fn_80464170(self->ai, 1);
    if (!fn_80134870(self->ai) || (fn_80134870(self->ai) && !fn_800B0C58(fn_80134870(self->ai))))
        fn_8014F7B0(fn_804420D8(self->ai), 0);
    return 1;
}

extern "C" {
PEnt *fn_8044203CF(void *a) __asm__("fn_8044203C");
int fn_800CD21CF(Ent &a) __asm__("fn_800CD21C");
Ent *fn_800CD9B0F(Ent &a) __asm__("fn_800CD9B0");
int fn_800CCA58F(Ent &a) __asm__("fn_800CCA58");
PEnt *fn_8015F7A4F(PEnt *a, float f1, int kind, Vector *v, float f2) __asm__("fn_8015F7A4");
void *fn_800B1478F(Ent &a) __asm__("fn_800B1478");
int fn_800B13D8F(Ent &actor) __asm__("fn_800B13D8");
int fn_800B0CC0F(Ent &a) __asm__("fn_800B0CC0");
int fn_800A3F44(void *a);
int fn_8015ED50(void *a, void *b);
void fn_800C98BC(void *self, PEnt *node, int v);
}

// FINDTHROWABLE update: picks a throwable (fn_8015F7A4), walks to it and sets bit 0x13 within reach.
extern "C" int fn_80158038(register Self *self)
{
    if (fn_80151B90(self->brain, self)) {
        if (!fn_80151430(self->brain)) {
            fn_804643C8(self, 1);
            return 1;
        }
        if (fn_800CD21CF(*fn_8044203CF(self->ai))) {
            fn_804643C8(self, 1);
            return 1;
        }
        if (fn_80461D48(self->ai, 0x1c) && fn_801368B8(self->ai))
            fn_80442130(self->ai, 0xe);
        Ent *e = fn_800CD9B0F(*fn_8044203CF(self->ai));
        if (!e) {
            Vector v;
            if (fn_8015F6CC(self->ai, &v)) {
                float hi = 0.5f;
                if (fn_800CCA58F(*fn_8044203CF(self->ai)) && fn_800860FC(fn_80442080(self->ai)))
                    hi = 0.0f;
                if (fn_80134870(self->ai)) {
                    if (fn_8015E8A8(self->ai, fn_800B1724(*fn_80134870(self->ai)))
                        > fn_800B1884(*fn_80442080(self->ai), 216))
                        hi = 0.0f;
                }
                Ent *t = fn_8015F7A4F(fn_80442080(self->ai), 20.0f, 2, &v, hi);
                if (t && !fn_800A3F44(fn_800B1478F(*t))) {
                    fn_8014B63C(fn_804420AC(self->ai), fn_800B13D8F(*t), 0);
                    fn_801501AC(fn_804420D8(self->ai), t);
                    float d = fn_8015E580(fn_800B1724(*t), fn_800B1724(*fn_80442080(self->ai)));
                    float lim = fn_800B1884(*fn_80442080(self->ai), 210);
                    if (fn_800860FC(fn_80442080(self->ai)))
                        lim = fn_800B1884(*fn_80442080(self->ai), 240);
                    if (d <= lim) {
                        fn_80442130(self->ai, 0x13);
                        if (fn_801368B8(self->ai) && !fn_800860FC(fn_80442080(self->ai)))
                            fn_80442174(self->ai, 0xe);
                        if (fn_8008606C(fn_80442080(self->ai)))
                            fn_80442174(self->ai, 0x20);
                    } else {
                        fn_80442130(self->ai, 0x12);
                        if (fn_80461D48(self->ai, 0x34)) {
                            fn_804643C8(self, 1);
                            return 1;
                        }
                    }
                } else {
                    fn_804643C8(self, 1);
                    return 1;
                }
            } else {
                if (fn_80461D48(self->ai, 0x33)) {
                    fn_804643C8(self, 1);
                    return 1;
                }
            }
        } else {
            fn_804643C8(self, 1);
            if (!fn_8015F384(self->ai)) {
                if (fn_800B0CC0F(*e) && fn_800A4130(fn_800B1478F(*e)) && fn_8046439C(self->ai) > 0.0f) {
                    if (fn_80134870(self->ai) && fn_8015ED50(self->ai, fn_800B1724(*fn_80134870(self->ai))))
                        fn_8015105C(self->brain, 8);
                    else
                        fn_80442130(self->ai, 0x10);
                } else {
                    fn_804643C8(self, 1);
                    fn_8015105C(self->brain, 7);
                }
                PEnt *t = fn_8014F8BC(fn_804420D8(self->ai));
                if (t) {
                    fn_800C98BC(fn_8044203CF(self->ai), t, 1);
                    fn_8014B63C(fn_804420AC(self->ai), fn_800B13D8F(*t), 0);
                }
            }
        }
    } else {
    }
    return 1;
}

// FINDWIELDABLE enter: done at once when the held actor is beyond 3 units.
extern "C" int fn_801585E4(register Self *self)
{
    if (fn_80134870(self->ai)) {
        float d = fn_8015E8A8(self->ai, fn_800B1724(*fn_80134870(self->ai)));
        if (d > 3.0f) {
            fn_804643C8(self, 1);
            return 0;
        }
    }
    fn_8046412C(self->ai, 2);
    fn_804618B0(fn_80462780(self->ai));
    fn_80442130(self->ai, 1);
    fn_80442130(self->ai, 0x1a);
    fn_80442130(self->ai, 0x1c);
    fn_80442130(self->ai, 4);
    fn_80442130(self->ai, 0xf);
    fn_80442130(self->ai, 0x12);
    fn_80442130(self->ai, 0);
    fn_80442130(self->ai, 0x15);
    fn_80442130(self->ai, 0x16);
    fn_80442130(self->ai, 0x17);
    if (fn_801368B8(self->ai))
        fn_80442130(self->ai, 0xe);
    if (fn_8008606C(fn_80442080(self->ai)))
        fn_80442130(self->ai, 0x20);
    Ent *t = fn_800ACFA8(fn_80463FBC(fn_804420D8(self->ai)));
    if (t)
        fn_801501AC(fn_804420D8(self->ai), t);
    fn_801513D8(self->brain, 3000);
    return 1;
}

// FINDWIELDABLE exit
extern "C" int fn_801587C8(register Self *self)
{
    fn_80464170(self->ai, 2);
    fn_80442174(self->ai, 0x13);
    fn_80442174(self->ai, 5);
    fn_801501AC(fn_804420D8(self->ai), 0);
    return 1;
}

extern "C" {
float fn_8015F608(void *ai, Vec *p, Vector *out);
}

// FINDWIELDABLE update: picks a wieldable (fn_8015F7A4 kind 1), walks to it and sets bit 0x13 within reach.
extern "C" int fn_80158844(register Self *self)
{
    if (fn_80151B90(self->brain, self)) {
        if (!fn_80151430(self->brain)) {
            fn_804643C8(self, 1);
            return 1;
        }
        if (fn_80461D48(self->ai, 0x1c) && fn_801368B8(self->ai))
            fn_80442130(self->ai, 0xe);
        Ent *e = fn_800CD9B0F(*fn_8044203CF(self->ai));
        if (!e) {
            e = fn_80134870(self->ai);
            if (!e)
                return 0;
            Vector v;
            float a = fn_8015F608(self->ai, fn_800B1724(*e), &v);
            float lo = fn_800B1884(*fn_80442080(self->ai), 213);
            float hi = 0.5f;
            Ent *t = fn_8015F7A4F(fn_80442080(self->ai), lo, 1, &v, hi);
            if (t) {
                fn_8014B63C(fn_804420AC(self->ai), fn_800B13D8F(*t), 0);
                fn_801501AC(fn_804420D8(self->ai), t);
                float lim = fn_800B1884(*fn_80442080(self->ai), 210);
                lim = 5.0f;
                float d = fn_8015E580(fn_800B1724(*t), fn_800B1724(*fn_80442080(self->ai)));
                if (d <= lim) {
                    fn_80442130(self->ai, 0x13);
                    if (fn_80085F7C(fn_80442080(self->ai)))
                        fn_80442174(self->ai, 0xe);
                    if (fn_8008606C(fn_80442080(self->ai)))
                        fn_80442174(self->ai, 0x20);
                    return 1;
                }
                if (fn_80461D48(self->ai, 0x33)) {
                    fn_804643C8(self, 1);
                    return 0;
                }
            }
        } else {
            fn_804643C8(self, 1);
            fn_8015105C(self->brain, 8);
            PEnt *t = fn_8014F8BC(fn_804420D8(self->ai));
            if (t) {
                fn_800C98BC(fn_8044203CF(self->ai), t, 1);
                fn_8014B63C(fn_804420AC(self->ai), fn_800B13D8F(*t), 0);
            }
        }
    } else {
    }
    return 1;
}

extern "C" {
void fn_80463B20(void *task);
void fn_80463B60(void *task);
void fn_80464014(char *mover);
void fn_8014DEB8(void *list);
void fn_8014DE58(void *list);
}

// POSSESS enter
extern "C" int fn_80158BBC(register Self *self)
{
    fn_80463B20(self);
    fn_804618B0(fn_80462780(self->ai));
    fn_80442130(self->ai, 0);
    fn_8014B900(fn_804420AC(self->ai));
    return 1;
}

// POSSESS exit
extern "C" int fn_80158C38(register Self *self)
{
    fn_80463B60(self);
    fn_80464014(fn_804420AC(self->ai));
    fn_8014DEB8(fn_804420D8(self->ai));
    fn_8014DE58(fn_804420D8(self->ai));
    return 1;
}

// POSSESS update
extern "C" int fn_80158CBC(register Self *self)
{
    return 1;
}

extern "C" {
int fn_801504BC(void *finder, Vector *out);
void fn_8014B518(char *mover, Vector *pos, int index);
}

// CARRYTHROWABLE enter: walks to the finder's point.
extern "C" int fn_80158CEC(register Self *self)
{
    fn_804618B0(fn_80462780(self->ai));
    fn_80442130(self->ai, 0x1a);
    fn_80442130(self->ai, 0x1c);
    fn_80442130(self->ai, 4);
    fn_80442130(self->ai, 0xf);
    fn_80442130(self->ai, 0x12);
    fn_80442130(self->ai, 0);
    fn_80442130(self->ai, 0x1b);
    fn_80442130(self->ai, 0x15);
    fn_80442130(self->ai, 0x16);
    fn_80442130(self->ai, 0x17);
    Ent *t = fn_8014F8BC(fn_804420D8(self->ai));
    if (t) {
        fn_801501AC(fn_804420D8(self->ai), t);
        fn_8014B63C(fn_804420AC(self->ai), fn_800B13D8F(*t), 0);
    }
    if (fn_8015F384(self->ai)) {
        fn_80442174(self->ai, 1);
        fn_80442130(self->ai, 5);
    } else {
        fn_80442130(self->ai, 1);
    }
    if (fn_80085F7C(fn_80442080(self->ai)))
        fn_80442130(self->ai, 0xe);
    fn_80442130(self->ai, 0x1a);
    fn_80442130(self->ai, 0);
    fn_80442130(self->ai, 4);
    fn_80442174(self->ai, 9);
    fn_801513D8(self->brain, 1000);
    fn_80442414((TaskBase *)self, 0);
    Vector v;
    if (fn_801504BC(fn_804420D8(self->ai), &v))
        fn_8014B518(fn_804420AC(self->ai), &v, -1);
    return 1;
}

extern "C" {
void fn_80464040(char *mover, int v);
void fn_800F8B90(SCtl *c);
}

// CARRYTHROWABLE exit: rearms the ranged and melee timers.
extern "C" int fn_80158F20(register Self *self)
{
    fn_80442174(self->ai, 0x10);
    int wait = fn_8015EA18(4) * 100 * (int)(100.0f - fn_8046439C(self->ai)) + 10000;
    fn_80464290(self->ai, fn_8042EFF8(lbl_80593BE8) + wait);
    wait = fn_8015EA18(4) * 100 * (int)(100.0f - fn_80461F94(self->ai)) + 7500;
    fn_80464208(self->ai, fn_8042EFF8(lbl_80593BE8) + wait);
    fn_80464040(fn_804420AC(self->ai), 0);
    if (fn_800CDA20(*fn_8044203C(self->ai)))
        fn_800F8B90(fn_8044203C(self->ai));
    return 1;
}

extern "C" {
void fn_80461BF8(char *mover, Vector *v);
void fn_80463410(char *mover, Vector *v);
}

// CARRYTHROWABLE update: carries the throwable toward the held actor and sets bit 0x10 to throw.
extern "C" int fn_80159088(register Self *self)
{
    if (fn_80151B90(self->brain, self)) {
        if (!fn_80151430(self->brain)) {
            if (!fn_804643F0(self)) {
                if (fn_80134870(self->ai) && fn_8015E8A8(self->ai, fn_800B1724(*fn_80134870(self->ai))) < 3.0f
                    && fn_8015E64C(self->ai) < fn_800B1884(*fn_80442080(self->ai), 211)) {
                    fn_804643C8(self, 1);
                    return 1;
                } else {
                    if (fn_801368B8(self->ai) && fn_8015F008(self->ai))
                        fn_80442130(self->ai, 0xe);
                    else
                        fn_80442174(self->ai, 0xe);
                    fn_80442414((TaskBase *)self, 1);
                    fn_801513D8(self->brain, 2000);
                }
            } else {
                fn_804643C8(self, 1);
                return 1;
            }
        }
        float dh = fn_800B1724(*fn_80442080(self->ai))->z - fn_8014B824(fn_804420AC(self->ai)) < 0.0f
            ? -(fn_800B1724(*fn_80442080(self->ai))->z - fn_8014B824(fn_804420AC(self->ai)))
            : fn_800B1724(*fn_80442080(self->ai))->z - fn_8014B824(fn_804420AC(self->ai));
        if (dh > 6.0f) {
            if (fn_801368B8(self->ai))
                fn_80442130(self->ai, 0xe);
        } else if (dh < 3.0f && !fn_8015F008(self->ai)) {
            float out;
            int hit = fn_80085300(fn_80442080(self->ai), fn_800B1724(*fn_80442080(self->ai)), 0.7f, 3.0f, &out);
            if (hit && fn_80085F7C(fn_80442080(self->ai)) && !fn_804628AC(self->ai))
                fn_80442174(self->ai, 0xe);
        }
        if (fn_804628AC(self->ai) && fn_80461D48(self->ai, 0x3c)) {
            if (fn_80085F7C(fn_80442080(self->ai)))
                fn_80442130(self->ai, 0xe);
            if (fn_8008606C(fn_80442080(self->ai)))
                fn_80442130(self->ai, 0x20);
        }
        if (fn_80461D48(self->ai, 0x1c) && fn_801368B8(self->ai))
            fn_80442130(self->ai, 0xe);
        if (fn_80085F7C(fn_80442080(self->ai)) && fn_8015F07C(self->ai) && !fn_804628AC(self->ai))
            fn_80442174(self->ai, 0xe);
        if (fn_80461D48(self->ai, 0xc)) {
            Ent *t = fn_80134870(self->ai);
            if (t && fn_800B0C58(t) && fn_804643F0(self)
                && (fn_80086B1C(fn_80442080(self->ai)) || fn_80086B6C(fn_80442080(self->ai))
                    || (fn_8015F07C(self->ai) && fn_8015E830(self->ai))
                    || (fn_8015EEA0(self->ai) && fn_8015F07C(self->ai)))) {
                fn_800C98BC(fn_8044203CF(self->ai), (PEnt *)t, 1);
                Vector v;
                fn_80464040(fn_804420AC(self->ai), 0);
                if (fn_801504BC(fn_804420D8(self->ai), &v)) {
                    fn_80464040(fn_804420AC(self->ai), 1);
                    fn_80461BF8(fn_804420AC(self->ai), &v);
                    fn_80463410(fn_804420AC(self->ai), &v);
                }
                fn_80442130(self->ai, 0x10);
            }
        } else {
            fn_804643C8(self, 1);
        }
    }
    return 1;
}

extern "C" {
Ent *fn_800E89B0(void *self, float a, float b, int c, Vector *dir, int d);
}

// WIELDING enter: done at once when the held actor is beyond 3 units.
extern "C" int fn_801596B0(register Self *self)
{
    if (fn_80134870(self->ai)) {
        float d = fn_8015E8A8(self->ai, fn_800B1724(*fn_80134870(self->ai)));
        if (d > 3.0f) {
            fn_804643C8(self, 1);
            return 0;
        }
    }
    Ent *t = fn_8014F8BC(fn_804420D8(self->ai));
    if (t) {
        fn_801501AC(fn_804420D8(self->ai), t);
        fn_8014B63C(fn_804420AC(self->ai), fn_800B13D8F(*t), 0);
    }
    fn_804618B0(fn_80462780(self->ai));
    fn_80442130(self->ai, 1);
    fn_80442130(self->ai, 0x1a);
    fn_80442130(self->ai, 0x1c);
    fn_80442130(self->ai, 4);
    fn_80442130(self->ai, 0xf);
    fn_80442130(self->ai, 0x12);
    fn_80442130(self->ai, 0);
    fn_80442130(self->ai, 0x1b);
    fn_80442130(self->ai, 0x15);
    fn_80442130(self->ai, 0x16);
    fn_80442130(self->ai, 0x17);
    if (fn_801368B8(self->ai))
        fn_80442130(self->ai, 0xe);
    fn_80442130(self->ai, 0x1a);
    fn_80442174(self->ai, 9);
    fn_80442174(self->ai, 0x13);
    fn_800E89B0(fn_8044203C(self->ai), fn_800B1884(*fn_80442080(self->ai), 223), fn_800B1884(*fn_80442080(self->ai), 2), 0, 0, 0);
    fn_801513D8(self->brain, 0);
    return 1;
}

// WIELDING exit: rearms the ranged and melee timers.
extern "C" int fn_8015990C(register Self *self)
{
    fn_80442174(self->ai, 1);
    fn_80442174(self->ai, 0x10);
    fn_80442174(self->ai, 8);
    int wait = fn_8015EA18(4) * 100 * (int)(100.0f - fn_8046439C(self->ai)) + 10000;
    fn_80464290(self->ai, fn_8042EFF8(lbl_80593BE8) + wait);
    wait = fn_8015EA18(4) * 100 * (int)(100.0f - fn_80461F94(self->ai)) + 7500;
    fn_80464208(self->ai, fn_8042EFF8(lbl_80593BE8) + wait);
    return 1;
}

// WIELDING update: keeps the wielded thing ready while in reach and picks a swing (0x10), 0xA or 8.
extern "C" int fn_80159A40(register Self *self)
{
    if (fn_80151B90(self->brain, self)) {
        if (!fn_80151430(self->brain))
            fn_80442174(self->ai, 8);
        if (!fn_800CDA20(*fn_8044203C(self->ai))) {
            fn_804643C8(self, 1);
            return 1;
        }
        void *grab = fn_800CD9B0(*fn_8044203C(self->ai));
        if (grab && fn_800B0CC0(grab) && !fn_800A4130(fn_800B1478(grab))) {
            fn_804643C8(self, 1);
            return 1;
        }
        float h = fn_8014B824(fn_804420AC(self->ai));
        if (fn_80134870(self->ai))
            h = fn_800B1724(*fn_80134870(self->ai))->z;
        float dh = ABS(fn_800B1724(*fn_80442080(self->ai))->z - h);
        if (dh > 4.0f) {
            if (fn_801368B8(self->ai)) {
                fn_80442130(self->ai, 0xe);
            } else {
                fn_804643C8(self, 1);
                if (fn_8015F008(self->ai) || dh > 6.0f)
                    fn_80442130(self->ai, 0x10);
                else
                    fn_80442130(self->ai, 0xa);
            }
        }
        if (fn_80461D48(self->ai, 0x1c) && fn_801368B8(self->ai))
            fn_80442130(self->ai, 0xe);
        if (fn_804628AC(self->ai)) {
            if (fn_80085F7C(fn_80442080(self->ai)))
                fn_80442130(self->ai, 0xe);
            if (fn_8008606C(fn_80442080(self->ai)))
                fn_80442130(self->ai, 0x20);
        }
        if (fn_8015E64C(self->ai) > fn_800B1884(*fn_80442080(self->ai), 210)) {
            Ent *t = fn_80134870(self->ai);
            if (t) {
                fn_80442130(self->ai, 1);
                fn_8014B63C(fn_804420AC(self->ai), fn_800B13D8F(*t), 0);
            }
        } else if (!fn_80151430(self->brain)) {
            fn_80442174(self->ai, 1);
            fn_80442174(self->ai, 0x10);
            fn_80442174(self->ai, 8);
            fn_80442174(self->ai, 0xa);
            if (dh < 3.0f && !fn_8015F008(self->ai)) {
                int hit;
                float out;
                hit = fn_80085300(fn_80442080(self->ai), fn_800B1724(*fn_80442080(self->ai)), 0.7f, 3.0f, &out);
                if (hit && fn_801368B8(self->ai))
                    fn_80442174(self->ai, 0xe);
            }
            fn_801513D8(self->brain, fn_8015EA18(500) + 500);
            switch ((unsigned int)fn_8015EA18(6)) {
            case 0:
                fn_80442130(self->ai, 0x10);
                break;
            case 1:
            case 2:
                if (fn_80134870(self->ai) && !fn_8015EE34(self->ai, fn_80134870(self->ai)) && !fn_80461D48(self->ai, 0x3d))
                    fn_80442130(self->ai, 0xa);
                else
                    fn_80442130(self->ai, 8);
                break;
            case 3:
            case 4:
            case 5:
                fn_80442130(self->ai, 8);
                break;
            }
        }
    } else {
    }
    return 1;
}

extern "C" {
int fn_80461C94(char *mover);
float fn_800A4054(void *e);
float fn_80086614(void *e);
}

// ATTACKTHING enter: targets the thing the mover is aimed at.
extern "C" int fn_80159FB4(register Self *self)
{
    fn_804618B0(fn_80462780(self->ai));
    fn_80442130(self->ai, 0x1a);
    fn_80442130(self->ai, 0x1c);
    fn_80442130(self->ai, 0);
    fn_80442130(self->ai, 4);
    fn_80442130(self->ai, 1);
    fn_80442130(self->ai, 0x1b);
    fn_80442130(self->ai, 0x1d);
    int h = fn_80461C94(fn_804420AC(self->ai));
    if (h) {
        Ent *t = fn_800ACFA8(h);
        if (t)
            fn_801501AC(fn_804420D8(self->ai), t);
    }
    fn_80442414((TaskBase *)self, 0);
    fn_801513D8(self->brain, 1000);
    return 1;
}

// ATTACKTHING exit
extern "C" int fn_8015A0D0(register Self *self)
{
    return 1;
}

// ATTACKTHING update: done once the thing is destroyed; swings (bit 8) while within half its extent.
extern "C" int fn_8015A100(register Self *self)
{
    if (!fn_80151B90(self->brain, self))
        return 0;
    Body *t = fn_80134870B(self->ai);
    if (!t)
        fn_804643C8(self, 1);
    int gone = 0;
    if (fn_800B0CC0(t))
        gone = fn_800A4054(fn_800B1478(t)) < 0.1f;
    else if (fn_800B0C58(t))
        gone = fn_80086614(fn_800B14A0(*(Ent *)t)) < 0.1f;
    if (gone) {
        fn_804643C8(self, 1);
        return 1;
    }
    if (!fn_80151430(fn_80442104(self->ai))) {
        float d = fn_8015E64C(self->ai);
        float reach = MAX(ABS(t->f60 - t->f50), ABS(t->f64 - t->f54)) / 2.0f;
        if (d < reach) {
            fn_80442130(self->ai, 8);
            fn_80442174(self->ai, 1);
            if (!fn_804643F0(self)) {
                fn_80442414((TaskBase *)self, 1);
                fn_801513D8(fn_80442104(self->ai), 500);
            } else if (fn_804643F0(self) == 1) {
                fn_80442174(self->ai, 8);
                fn_80442414((TaskBase *)self, 0);
                fn_801513D8(fn_80442104(self->ai), 500);
            }
        } else {
            fn_80442174(self->ai, 8);
            fn_80442130(self->ai, 1);
        }
    }
    return 1;
}

// BUZZPLAYER enter
extern "C" int fn_8015A4BC(register Self *self)
{
    fn_8014B900(fn_804420AC(self->ai));
    return 1;
}

// BUZZPLAYER exit
extern "C" int fn_8015A510(register Self *self)
{
    return 1;
}

// BUZZPLAYER update
extern "C" int fn_8015A540(register Self *self)
{
    if (fn_80151B90(self->brain, self)) {
    } else {
    }
    return 1;
}

struct MoveTo : Self {
    char pad8[0x28];
    Vector dest; // +0x30
};

extern "C" {
float fn_8015E580V(Vec *a, Vector *b) __asm__("fn_8015E580");
float fn_804290F8(Vec *a, Vector *b);
void fn_80135668(void *ai, int on);
int fn_80463FE8(char *mover);
void fn_80149A6C(int kind, const char *fmt, ...);
int fn_800861EC(void *actor);
}

// MOVETO enter: walks to dest.
extern "C" int fn_8015A59C(register MoveTo *self)
{
    fn_8046412C(self->ai, 0);
    fn_8046412C(self->ai, 5);
    fn_8046412C(self->ai, 3);
    fn_8046412C(self->ai, 6);
    fn_804618B0(fn_80462780(self->ai));
    fn_80442130(self->ai, 0);
    fn_80442130(self->ai, 0x1a);
    fn_80442130(self->ai, 0x1c);
    fn_80442130(self->ai, 4);
    fn_80442130(self->ai, 0xf);
    fn_80442130(self->ai, 0x15);
    fn_80442130(self->ai, 0x16);
    fn_80442130(self->ai, 0x17);
    fn_80442130(self->ai, 0x1b);
    fn_80442130(self->ai, 5);
    fn_8014B518(fn_804420AC(self->ai), &self->dest, -1);
    if (!fn_80134870(self->ai) || (fn_80134870(self->ai) && !fn_800B0C58(fn_80134870(self->ai))))
        fn_8014F7B0(fn_804420D8(self->ai), 0);
    float d = fn_8015E580V(fn_800B1724(*fn_80442080(self->ai)), &self->dest);
    if (d < 4.0f) {
        if (fn_800CCAE8(*fn_8044203C(self->ai)))
            fn_80442174(self->ai, 0x20);
    }
    if (fn_801368B8(self->ai)) {
        if (fn_800861EC(fn_80442080(self->ai))) {
            fn_80442130(self->ai, 0x18);
            fn_80442174(self->ai, 5);
            fn_80442130(self->ai, 0x28);
        } else if (d > 2.0f) {
            fn_80442130(self->ai, 0xe);
        }
    }
    if (fn_8008606C(fn_80442080(self->ai)) && d > 4.0f)
        fn_80442130(self->ai, 0x20);
    if (fn_804628AC(self->ai)) {
        if (fn_80085F7C(fn_80442080(self->ai)))
            fn_80442130(self->ai, 0xe);
        if (fn_8008606C(fn_80442080(self->ai)))
            fn_80442130(self->ai, 0x20);
    }
    return 1;
}

// MOVETO exit
extern "C" int fn_8015A8B4(register MoveTo *self)
{
    fn_80135668(self->ai, 0);
    return 1;
}

// MOVETO update: done within 2 of dest, and tells the actor it arrived.
extern "C" int fn_8015A900(register MoveTo *self)
{
    if (fn_80151B90(self->brain, self)) {
        fn_8014B518(fn_804420AC(self->ai), &self->dest, -1);
        float d = 3.40282347e+38f;
        Vector v;
        if (fn_804628AC(self->ai)) {
            if (fn_80085F7C(fn_80442080(self->ai)))
                fn_80442130(self->ai, 0xe);
            if (fn_8008606C(fn_80442080(self->ai)))
                fn_80442130(self->ai, 0x20);
        }
        d = fn_8015E580V(fn_800B1724(*fn_80442080(self->ai)), &self->dest);
        if (d < 4.0f) {
            if (fn_800CCA58(*fn_8044203C(self->ai)))
                fn_80442174(self->ai, 0xe);
        }
        if (d < 8.0f) {
            if (fn_800CCAE8(*fn_8044203C(self->ai)))
                fn_80442174(self->ai, 0x20);
        }
        if (!fn_800861EC(fn_80442080(self->ai)))
            d = fn_804290F8(fn_800B1724(*fn_80442080(self->ai)), &self->dest);
        if (d < 2.0f) {
            fn_804643C8(self, 1);
            int at = fn_80463FE8(fn_804420AC(self->ai));
            fn_80149A6C(0, "%udl %udl", fn_800B13D8F(*fn_80442080(self->ai)), at);
        }
    } else {
    }
    return 1;
}

// FORCECONTROL enter
extern "C" int fn_8015AB70(register Self *self)
{
    return 1;
}

// FORCECONTROL exit
extern "C" int fn_8015ABA0(register Self *self)
{
    return 1;
}

// FORCECONTROL update: done once state bit 0x33 is set.
extern "C" int fn_8015ABD0(register Self *self)
{
    if (fn_80151B90(self->brain, self)) {
        if (fn_80461D48(self->ai, 0x33))
            fn_804643C8(self, 1);
    } else {
    }
    return 1;
}

// STOP enter
extern "C" int fn_8015AC50(register Self *self)
{
    fn_8014B900(fn_804420AC(self->ai));
    return 1;
}

// STOP exit
extern "C" int fn_8015ACA4(register Self *self)
{
    return 1;
}

// STOP update: done once state bit 0x33 is set.
extern "C" int fn_8015ACD4(register Self *self)
{
    if (fn_80151B90(self->brain, self) && fn_80461D48(self->ai, 0x33)) {
        fn_804643C8(self, 1);
    } else {
    }
    return 1;
}

// ENSLAVE enter
extern "C" int fn_8015AD54(register Self *self)
{
    fn_80463B20(self);
    fn_804618B0(fn_80462780(self->ai));
    fn_80442130(self->ai, 0);
    fn_8014B900(fn_804420AC(self->ai));
    return 1;
}

// ENSLAVE exit
extern "C" int fn_8015ADD0(register Self *self)
{
    fn_80463B60(self);
    return 1;
}

extern "C" {
int fn_8014FCAC(void *list);
void *fn_8014FCD8(void *list, int i);
int fn_8015F2D0(void *a, void *b);
}

// ENSLAVE update: done once any actor in the list holds this one, and tells the actor.
extern "C" int fn_8015AE18(register Self *self)
{
    if (!fn_804420D8(self->ai))
        return 0;
    int n = fn_8014FCAC(fn_804420D8(self->ai));
    for (int i = 0; i < n; i++) {
        void *e = fn_8014FCD8(fn_804420D8(self->ai), i);
        if (fn_8015F2D0(e, fn_80442080(self->ai))) {
            fn_804643C8(self, 1);
            fn_80149A6C(2, "%udl", fn_800B13D8F(*fn_80442080(self->ai)));
        }
    }
    return 1;
}

// FORCEJUMP enter
extern "C" int fn_8015AF3C(register Self *self)
{
    fn_8014B900(fn_804420AC(self->ai));
    return 1;
}

// FORCEJUMP exit
extern "C" int fn_8015AF90(register Self *self)
{
    return 1;
}

// FORCEJUMP update: done once state bit 0x33 is set.
extern "C" int fn_8015AFC0(register Self *self)
{
    if (fn_80151B90(self->brain, self) && fn_80461D48(self->ai, 0x33)) {
        fn_804643C8(self, 1);
    } else {
    }
    return 1;
}

// SWING enter
extern "C" int fn_8015B040(register Self *self)
{
    fn_8014B900(fn_804420AC(self->ai));
    return 1;
}

// SWING exit
extern "C" int fn_8015B094(register Self *self)
{
    return 1;
}

// SWING update: done once state bit 0x33 is set.
extern "C" int fn_8015B0C4(register Self *self)
{
    if (fn_80151B90(self->brain, self) && fn_80461D48(self->ai, 0x33)) {
        fn_804643C8(self, 1);
    } else {
    }
    return 1;
}

// GETANDTHROWAT enter
extern "C" int fn_8015B144(register Self *self)
{
    return 1;
}

// GETANDTHROWAT exit
extern "C" int fn_8015B174(register Self *self)
{
    return 1;
}

struct GetThrow : Self {
    char pad8[0x20];
    int thing;  // +0x28, script handle of the thing to throw
    int target; // +0x2C, script handle of the target
};

extern "C" {
int fn_800CD9F4(Ctl &c);
void *fn_80151BCC(void *brain);
int fn_804423E8(void *task);
void fn_800F63DC(SCtl *c, int handle, int on);
}

// GETANDTHROWAT update: picks the thing up (steps 0-2), then throws it at the target (3-4).
extern "C" int fn_8015B1A4(register GetThrow *self)
{
    if (!fn_80151B90(self->brain, self))
        return 0;
    Ent *thing = fn_800ACFA8(self->thing);
    Ent *target = fn_800ACFA8(self->target);
    if (!thing || !target) {
        fn_80149A6C(1, "%udl %udl", fn_800B13D8F(*fn_80442080(self->ai)), self->thing);
        fn_804643C8(self, 1);
        return 0;
    }
    switch ((unsigned int)fn_804643F0(self)) {
    case 0:
        if (fn_800CD9F4(*fn_8044203C(self->ai)) == self->thing) {
            fn_80442414((TaskBase *)self, 3);
        } else {
            fn_8015105C(fn_80442104(self->ai), 4);
            fn_801501AC(fn_804420D8(self->ai), thing);
            fn_80442414((TaskBase *)self, 1);
        }
        break;
    case 1:
        if (fn_800CD9B0(*fn_8044203C(self->ai))) {
            fn_80442414((TaskBase *)self, 3);
        } else if (fn_804423E8(fn_80151BCC(fn_80442104(self->ai))) != 4) {
            fn_8015105C(fn_80442104(self->ai), 4);
            fn_801501AC(fn_804420D8(self->ai), thing);
            fn_80442414((TaskBase *)self, 2);
        }
        break;
    case 2:
        if (fn_800CD9B0(*fn_8044203C(self->ai))) {
            fn_80442414((TaskBase *)self, 3);
        } else if (fn_804423E8(fn_80151BCC(fn_80442104(self->ai))) != 4) {
            if (fn_8015E580(fn_800B1724(*thing), fn_800B1724(*fn_80442080(self->ai))) > 4.0f) {
                fn_80149A6C(1, "%udl %udl", fn_800B13D8F(*fn_80442080(self->ai)), self->thing);
                fn_804643C8(self, 1);
                return 0;
            } else {
                fn_800F63DC(fn_8044203C(self->ai), self->thing, 1);
            }
        }
        break;
    case 3:
        if (fn_800CCE00(*fn_8044203C(self->ai))) {
            fn_80442414((TaskBase *)self, 4);
        } else if (fn_800CDA20(*fn_8044203C(self->ai)) && !fn_80151AF8(fn_80442104(self->ai), 7)) {
            fn_8015105C(fn_80442104(self->ai), 7);
            fn_801501AC(fn_804420D8(self->ai), target);
            fn_8014B63C(fn_804420AC(self->ai), fn_800B13D8(target), 0);
        }
        if (!fn_800CDA20(*fn_8044203C(self->ai)))
            fn_80442414((TaskBase *)self, 4);
        break;
    case 4:
        if (!fn_800CD9B0(*fn_8044203C(self->ai))) {
            fn_804643C8(self, 1);
            fn_80149A6C(1, "%udl %udl", fn_800B13D8F(*fn_80442080(self->ai)), self->thing);
        }
        break;
    }
    return 1;
}

// GOGETANDTHROWAT enter
extern "C" int fn_8015B648(register Self *self)
{
    fn_8046412C(self->ai, 0);
    fn_8046412C(self->ai, 5);
    fn_8046412C(self->ai, 3);
    fn_8046412C(self->ai, 6);
    fn_804618B0(fn_80462780(self->ai));
    fn_80442130(self->ai, 0);
    fn_80442130(self->ai, 0x1a);
    fn_80442130(self->ai, 0x1c);
    fn_80442130(self->ai, 4);
    fn_80442130(self->ai, 0xf);
    fn_80442130(self->ai, 0x15);
    fn_80442130(self->ai, 0x16);
    fn_80442130(self->ai, 0x17);
    fn_80442130(self->ai, 0x1b);
    fn_80442130(self->ai, 1);
    return 1;
}

// GOGETANDTHROWAT exit
extern "C" int fn_8015B744(register Self *self)
{
    return 1;
}

extern "C" {
Body *fn_800ACFA8B(int handle) __asm__("fn_800ACFA8");
float fn_804290F8E(Vec *a, Vec *b) __asm__("fn_804290F8");
}

// GOGETANDTHROWAT update: walks to the thing (steps 0-1) and picks it up within half its extent (2),
// then throws it at the target (3-4).
extern "C" int fn_8015B774(register GetThrow *self)
{
    if (!fn_80151B90(self->brain, self))
        return 0;
    Body *thing = fn_800ACFA8B(self->thing);
    Ent *target = fn_800ACFA8(self->target);
    if (!thing || !target) {
        fn_80149A6C(1, "%udl %udl", fn_800B13D8F(*fn_80442080(self->ai)), self->thing);
        fn_804643C8(self, 1);
        return 0;
    }
    switch ((unsigned int)fn_804643F0(self)) {
    case 0:
        if (fn_800CD9F4(*fn_8044203C(self->ai)) == self->thing) {
            fn_80442414((TaskBase *)self, 3);
        } else {
            fn_801501AC(fn_804420D8(self->ai), (Ent *)thing);
            fn_8014B63C(fn_804420AC(self->ai), fn_800B13D8(thing), 0);
            fn_80442414((TaskBase *)self, 1);
        }
        break;
    case 1: {
        float reach = MAX(ABS(thing->f60 - thing->f50), ABS(thing->f64 - thing->f54)) / 2.0f < 3.0f
            ? 3.0f
            : MAX(ABS(thing->f60 - thing->f50), ABS(thing->f64 - thing->f54)) / 2.0f;
        fn_801501AC(fn_804420D8(self->ai), (Ent *)thing);
        fn_8014B63C(fn_804420AC(self->ai), fn_800B13D8(thing), 0);
        if (fn_804290F8E(fn_800B1724(*(Ent *)thing), fn_800B1724(*fn_80442080(self->ai))) < reach) {
            fn_80442414((TaskBase *)self, 2);
            fn_801501AC(fn_804420D8(self->ai), (Ent *)thing);
            fn_80442130(self->ai, 0x13);
        }
        break;
    }
    case 2:
        if (fn_800CD9B0(*fn_8044203C(self->ai))) {
            fn_80442174(self->ai, 0x13);
            fn_80442414((TaskBase *)self, 3);
        } else {
        }
        break;
    case 3:
        if (fn_800CCE00(*fn_8044203C(self->ai))) {
            fn_80442414((TaskBase *)self, 4);
        } else if (fn_800CDA20(*fn_8044203C(self->ai)) && !fn_80151AF8(fn_80442104(self->ai), 7)) {
            fn_8015105C(fn_80442104(self->ai), 7);
            fn_801501AC(fn_804420D8(self->ai), target);
            fn_8014B63C(fn_804420AC(self->ai), fn_800B13D8(target), 0);
        }
        if (!fn_800CDA20(*fn_8044203C(self->ai)))
            fn_80442414((TaskBase *)self, 4);
        break;
    case 4:
        if (!fn_800CD9B0(*fn_8044203C(self->ai))) {
            fn_804643C8(self, 1);
            fn_80149A6C(1, "%udl %udl", fn_800B13D8F(*fn_80442080(self->ai)), self->thing);
        }
        break;
    }
    return 1;
}

extern "C" int fn_801362DC(void *ai, int id);

// WALLCLIMB enter
extern "C" int fn_8015BED8(register Self *self)
{
    fn_8014B900(fn_804420AC(self->ai));
    fn_804618B0(fn_80462780(self->ai));
    fn_80442130(self->ai, 0x21);
    fn_801362DC(self->ai, 4);
    fn_801513D8(fn_80442104(self->ai), (int)(fn_80464318(self->ai) * 20.0f));
    return 1;
}

// WALLCLIMB exit
extern "C" int fn_8015BF98(register Self *self)
{
    return 1;
}

// WALLCLIMB update: done once the climb ends or the actor's regenerating meter is under 5%.
extern "C" int fn_8015BFC8(register Self *self)
{
    if (!fn_80151B90(self->brain, self))
        return 0;
    if (!fn_800CCB38(*fn_8044203C(self->ai)))
        fn_804643C8(self, 1);
    if (!fn_8015F410(self->ai, 0.05f)) {
        fn_804643C8(self, 1);
        return 0;
    }
    if (fn_80151430(fn_80442104(self->ai)))
        return 1;
    fn_80442174(self->ai, 0x21);
    fn_80442174(self->ai, 0x22);
    if (!fn_8015E830(self->ai))
        fn_80442130(self->ai, 0x22);
    else
        fn_801513D8(fn_80442104(self->ai), (int)(fn_80464318(self->ai) * 20.0f));
    return 1;
}

struct PlayAnim : Self {
    char pad8[0x20];
    int anim; // +0x28, animation id
    int loop; // +0x2C, nonzero restarts the animation when it ends
};

class Puppet
{
public:
    char d[0x3ac];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(int state); // vtable +0x30
};
struct PuppetD : Puppet { // matching_notes 50
    int x;
};

extern "C" {
PuppetD *fn_8044203CP(void *ai) __asm__("fn_8044203C");
int fn_800CC6AC(Ctl &c);
int fn_800CC2E0(Ctl &c);
unsigned int fn_80097CE8(Ent &actor, int anim, int mode, float speed, int set, float blend, float f);
void fn_800BD2D0(void *actor, int clip);
}

// PLAYANIM enter
extern "C" int fn_8015C128(register Self *self)
{
    fn_8014B900(fn_804420AC(self->ai));
    return 1;
}

// PLAYANIM exit
extern "C" int fn_8015C17C(register Self *self)
{
    return 1;
}

// PLAYANIM update: puts the controller in state 0x24 and plays the animation, once or looped.
extern "C" int fn_8015C1AC(register PlayAnim *self)
{
    if (!fn_80151B90(self->brain, self))
        return 0;
    if (fn_800CC6AC(*fn_8044203C(self->ai)) != 0x24) {
        fn_8044203CP(self->ai)->s5(0x24);
        int clip = fn_80097CE8(*fn_80442080(self->ai), self->anim, 1, 30.0f, 0, 7.5f, -1.0f);
        fn_800BD2D0(fn_8044203C(self->ai), clip);
    }
    if (fn_800CC2E0(*fn_8044203C(self->ai))) {
    } else {
        if (self->loop) {
            fn_8044203CP(self->ai)->s5(0x24);
            int clip = fn_80097CE8(*fn_80442080(self->ai), self->anim, 1, 30.0f, 0, 7.5f, -1.0f);
            fn_800BD2D0(fn_8044203C(self->ai), clip);
        } else {
            fn_804643C8(self, 1);
        }
    }
    return 1;
}

struct RangedOnly : Self {
    char pad8[0x20];
    int target; // +0x28, script handle of the target; 0 shoots at the current enemy
};

extern "C" {
void *fn_80151C8C(void *brain);
void fn_8044243C(void *set, int v);
void fn_804424A0(void *set, int v);
void fn_800CD6C4(Ctl &c, int on);
void fn_800BD3A8(void *ctl, int v);
void fn_80429038V(Vector *out, Vec *a, Vector *b) __asm__("fn_80429038");
float fn_800B2670(Ent &e);
}

// RANGEDONLY enter
extern "C" int fn_8015C39C(register RangedOnly *self)
{
    fn_8014B900(fn_804420AC(self->ai));
    fn_8046412C(self->ai, 0);
    fn_8046412C(self->ai, 3);
    fn_8046412C(self->ai, 5);
    fn_804618B0(fn_80462780(self->ai));
    fn_80442130(self->ai, 0);
    fn_80442130(self->ai, 9);
    fn_80442130(self->ai, 4);
    if (self->target) {
        Ent *t = fn_800ACFA8(self->target);
        fn_801501AC(fn_804420D8(self->ai), t);
    } else {
        fn_8014F7B0(fn_804420D8(self->ai), 1);
    }
    fn_804618B0(fn_80151C8C(self->brain));
    fn_801513D8(self->brain, fn_800B18EC(*fn_80442080(self->ai), 0xb8));
    fn_8044243C(fn_80151C8C(self->brain), 1);
    fn_800CD6C4(*fn_8044203C(self->ai), 1);
    return 1;
}

// RANGEDONLY exit
extern "C" int fn_8015C508(register RangedOnly *self)
{
    fn_800CD6C4(*fn_8044203C(self->ai), 0);
    return 1;
}

// RANGEDONLY update: alternates two brain phases, firing (bit 9) only while the line of fire is clear.
extern "C" int fn_8015C560(register RangedOnly *self)
{
    if (!fn_80151B90(self->brain, self))
        return 0;
    Ent *t = 0;
    if (self->target) {
        t = fn_800ACFA8(self->target);
        if (!t)
            self->target = 0;
    } else {
        t = fn_80134870(self->ai);
        if (!t)
            fn_8014F7B0(fn_804420D8(self->ai), 1);
    }
    if (fn_80442508(fn_80151C8C(self->brain), 1)) {
        if (!fn_80151430(self->brain)) {
            fn_80442174(self->ai, 9);
            fn_801513D8(self->brain, fn_800B18EC(*fn_80442080(self->ai), 0xb9));
            fn_804424A0(fn_80151C8C(self->brain), 1);
            fn_8044243C(fn_80151C8C(self->brain), 0);
            fn_800BD3A8(fn_8044203C(self->ai), fn_800B18EC(*fn_80442080(self->ai), 0xb9));
        }
    } else if (fn_80442508(fn_80151C8C(self->brain), 0)) {
        if (!fn_80151430(self->brain)) {
            if (t) {
                Vector from;
                Vector dir;
                fn_8042DC84(&from, fn_800B1724(*fn_80442080(self->ai)));
                from.z += 1.0f;
                fn_80429038V(&dir, fn_800B1724(*t), &from);
                float len = fn_8042EC54(&dir);
                len -= fn_800B2670(*t);
                if (!fn_8004A9CCV(&from, &dir, len, 0x8000, 0, fn_800B24AC(*fn_80442080(self->ai)),
                                  fn_800B1CC8(*fn_80442080(self->ai)), 0, 3))
                    fn_80442130(self->ai, 9);
                else
                    fn_80442174(self->ai, 9);
            }
            fn_801513D8(self->brain, fn_800B18EC(*fn_80442080(self->ai), 0xb8));
            fn_8044243C(fn_80151C8C(self->brain), 1);
        }
    } else {
    }
    return 1;
}

extern "C" {
void *fn_80444904(void *link, int i);
void *fn_80444984(void *link, int i);
Vector *fn_80444688(void *spot);
void fn_80428FE0(Vector *dst, Vector *a, Vector *b);
void fn_80435530(Vector *v, float s);
void fn_804640E8(void *ai, Vector *v);
void fn_80135F94(void *ai);
Vector *fn_80462854(void *ai);
unsigned int fn_80151470(void *brain);
}

// CLIMBATTACK enter
extern "C" int fn_8015C8BC(register Self *self)
{
    fn_8046412C(self->ai, 0);
    fn_8046412C(self->ai, 3);
    fn_8046412C(self->ai, 5);
    fn_804618B0(fn_80462780(self->ai));
    fn_80442130(self->ai, 0);
    fn_80442130(self->ai, 4);
    fn_80442130(self->ai, 0x1a);
    fn_80442130(self->ai, 0x1c);
    fn_80442130(self->ai, 0x15);
    fn_80442130(self->ai, 0x16);
    void *link = fn_8014630C(fn_8013726C(self->ai), fn_800B1724(*fn_80442080(self->ai)));
    if (link) {
        Vector mid;
        fn_80428FE0(&mid, fn_80444688(fn_80444904(link, 0)), fn_80444688(fn_80444984(link, 0)));
        fn_80435530(&mid, 0.5f);
        fn_804640E8(self->ai, &mid);
        fn_80442414((TaskBase *)self, 1);
        fn_80442130(self->ai, 0x24);
        fn_80461BF8(fn_804420AC(self->ai), &mid);
        fn_80135F94(self->ai);
    } else {
        fn_804643C8(self, 1);
    }
    fn_801513D8(fn_80442104(self->ai), 3000);
    return 1;
}

// CLIMBATTACK exit
extern "C" int fn_8015CAA0(register Self *self)
{
    fn_80136214(self->ai, 0x24);
    if (fn_80134870(self->ai))
        fn_8014B63C(fn_804420AC(self->ai), fn_800B13D8(fn_80134870(self->ai)), 1);
    return 1;
}

// CLIMBATTACK update
extern "C" int fn_8015CB34(register Self *self)
{
    if (!fn_80151B90(self->brain, self))
        return 0;
    fn_8014B518(fn_804420AC(self->ai), fn_80462854(self->ai), -1);
    if (fn_804643F0(self) != 1)
        fn_804643C8(self, 1);
    if (!fn_80151430(self->brain)) {
        fn_804643C8(self, 1);
        return 0;
    }
    if (fn_80461D48(self->ai, 0x28)) {
        fn_804643C8(self, 1);
        return 0;
    }
    fn_80442174(self->ai, 7);
    Ent *t = fn_80134870(self->ai);
    if (!t)
        fn_8014F7B0(fn_804420D8(self->ai), 3);
    if (fn_800CCB38(*fn_8044203C(self->ai))) {
        fn_8015105C(fn_80442104(self->ai), 0x12);
        fn_804643C8(self, 1);
    } else if (fn_800CC96C(*fn_8044203C(self->ai)) && fn_80151470(self->brain) > 2000) {
        if (fn_8015EC1C(fn_80461F10(self->ai)))
            fn_80442130(self->ai, 8);
        if (fn_8015EC1C(fn_80461F68(self->ai)))
            fn_80442130(self->ai, 9);
    }
    return 1;
}

// FORCESUPERBLOCK enter
extern "C" int fn_8015CD44(register Self *self)
{
    fn_8014B900(fn_804420AC(self->ai));
    fn_8046412C(self->ai, 3);
    fn_804618B0(fn_80462780(self->ai));
    fn_80442130(self->ai, 0);
    fn_80442130(self->ai, 4);
    fn_80442130(self->ai, 0x25);
    return 1;
}

// FORCESUPERBLOCK exit
extern "C" int fn_8015CDDC(register Self *self)
{
    fn_80442174(self->ai, 0x25);
    fn_80136214(self->ai, 0x25);
    return 1;
}

// FORCESUPERBLOCK update
extern "C" int fn_8015CE34(register Self *self)
{
    return 1;
}

// FORCEPOWERSTAND enter
extern "C" int fn_8015CE64(register Self *self)
{
    fn_8014B900(fn_804420AC(self->ai));
    fn_8046412C(self->ai, 3);
    fn_804618B0(fn_80462780(self->ai));
    fn_80442130(self->ai, 0);
    fn_80442130(self->ai, 4);
    fn_80442130(self->ai, 0x26);
    return 1;
}

// FORCEPOWERSTAND exit
extern "C" int fn_8015CEFC(register Self *self)
{
    fn_80442174(self->ai, 0x26);
    fn_80136214(self->ai, 0x26);
    return 1;
}

// FORCEPOWERSTAND update
extern "C" int fn_8015CF54(register Self *self)
{
    return 1;
}

struct HoverFire : Self {
    char pad8[0x20];
    int hover; // +0x28, set to 1 by the script API
};

// HOVERANDFIRE enter
extern "C" int fn_8015CF84(register HoverFire *self)
{
    fn_8014B900(fn_804420AC(self->ai));
    fn_8046412C(self->ai, 0);
    fn_8046412C(self->ai, 3);
    fn_8046412C(self->ai, 5);
    fn_804618B0(fn_80462780(self->ai));
    fn_80442130(self->ai, 0);
    fn_80442130(self->ai, 0x27);
    fn_80442130(self->ai, 9);
    fn_8014F7B0(fn_804420D8(self->ai), 1);
    fn_801513D8(self->brain, fn_8015EA18(2000) + 1000);
    self->hover = 0;
    return 1;
}

// HOVERANDFIRE exit
extern "C" int fn_8015D070(register HoverFire *self)
{
    return 1;
}

// HOVERANDFIRE update
extern "C" int fn_8015D0A0(register HoverFire *self)
{
    if (!self->hover && (!fn_80151430(self->brain) || !fn_8015F410(self->ai, 0.25f)))
        fn_804643C8(self, 1);
    return 1;
}
