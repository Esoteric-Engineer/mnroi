// AI inline functions: AIObject+0x210 setters, AIObject accessors (bit set +0x508, timers +0x558/+0x55C, weights +0x598), the task done flag.
// docs/ai.md row 5. Pool at 0x8049B9E0 (extern_pool), in another file's .rodata.

inline int sn_return_decl(int a) { return a; }

struct Vector
{
    float x, y, z, w;
};

extern "C" {
void fn_8042DC84(void *dst, void *src);
int fn_8044243C(void *set, int bit);
int fn_804424A0(void *set, int bit);
unsigned int fn_8042EFF8(void *clock);
extern char lbl_80593BE8[];
}

// AIObject+0x210 (docs/ai.md 4.1)
struct Sub210
{
    char pad[0x278];
    float f278; // +0x278
    char pad27C[0x44];
    int i2C0; // +0x2C0
};

// docs/ai.md 4.1
struct AIObject
{
    char pad[0x508];
    char bits508[0x18]; // +0x508
    int i520; // +0x520
    char pad524[0x34];
    unsigned int t558; // +0x558
    unsigned int t55C; // +0x55C
    char pad560[0x20];
    Vector v580; // +0x580
    int i590; // +0x590
    char pad594[0x4];
    float weights[22]; // +0x598
};

// docs/ai.md 4.4
struct AITask
{
    char pad[0x1C];
    int done; // +0x1C
};

extern "C" void fn_80464014(register Sub210 *self)
{
    self->f278 = 0.0f;
}

extern "C" void fn_80464040(register Sub210 *self, register int v)
{
    self->i2C0 = v;
}

extern "C" void *fn_80464068(register AIObject *self)
{
    return self->bits508;
}

extern "C" float fn_80464094(register char *self)
{
    return *(float *)(self + 0x8);
}

extern "C" void fn_804640C0(register AIObject *self, register int v)
{
    self->i520 = v;
}

extern "C" void fn_804640E8(register AIObject *self, register void *v)
{
    fn_8042DC84(&self->v580, v);
}

extern "C" void fn_8046412C(register AIObject *self, register int bit)
{
    fn_8044243C(self->bits508, bit);
}

extern "C" void fn_80464170(register AIObject *self, register int bit)
{
    fn_804424A0(self->bits508, bit);
}

extern "C" void fn_804641B4(register AIObject *self, register int v)
{
    self->i590 = v;
}

extern "C" int fn_804641DC(register AIObject *self)
{
    return self->i590;
}

extern "C" void fn_80464208(register AIObject *self, register unsigned int t)
{
    self->t558 = t;
}

extern "C" int fn_80464230(register AIObject *self)
{
    if (fn_8042EFF8(lbl_80593BE8) >= self->t558) {
        return 1;
    } else {
        return 0;
    }
}

extern "C" void fn_80464290(register AIObject *self, register unsigned int t)
{
    self->t55C = t;
}

extern "C" int fn_804642B8(register AIObject *self)
{
    if (fn_8042EFF8(lbl_80593BE8) >= self->t55C) {
        return 1;
    } else {
        return 0;
    }
}

extern "C" float fn_80464318(register AIObject *self)
{
    return self->weights[0];
}

extern "C" float fn_80464344(register AIObject *self)
{
    return self->weights[6];
}

extern "C" float fn_80464370(register AIObject *self)
{
    return self->weights[15];
}

extern "C" float fn_8046439C(register AIObject *self)
{
    return self->weights[16];
}

extern "C" void fn_804643C8(register AITask *self, register int v)
{
    self->done = v;
}

// Receiver unknown (called from the task methods and row 9's helpers)
extern "C" int fn_804643F0(register char *self)
{
    return *(int *)(self + 0x20);
}

extern "C" int fn_8046441C(register char *self)
{
    return *(int *)(self + 0x28);
}
