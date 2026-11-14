// Task methods (enter, exit, update per class), from SLEEP on; see docs/ai.md row 12 and section 4.4.
// Owns .rodata 0x8049B838-0x8049B878.

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

// Pads .rodata to 8: MELEE update fn_801549D0's 0.33f.
extern "C" const float lbl_8049B884 __attribute__((section(".rodata"))) = 0.33f;
