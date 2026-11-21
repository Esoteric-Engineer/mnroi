// Pad manager: init, probe, read, rumble and stick shaping over PADRead (docs/core.md row 12, section 4.6).
// .rodata 0x8049D8F0-0x8049D960.

struct PADStatus
{
    unsigned short button;
    signed char stickX;
    signed char stickY;
    signed char substickX;
    signed char substickY;
    unsigned char triggerL;
    unsigned char triggerR;
    unsigned char analogA;
    unsigned char analogB;
    signed char err;
};

struct Key
{
    float value;
    int pressFrame;
    int pressTime;
    int releaseFrame;
    int releaseTime;
    int held;
};

struct Pad
{
    int connected;
    int unk4;
    unsigned int rumble;
    float sx;
    float sy;
    float cx;
    float cy;
    Key keys[16];
};

extern "C" {
void *memset(void *dst, int c, unsigned int n);
void SISetSamplingRate(unsigned int msec);
int PADInit(void);
unsigned int SIProbe(int chan);
int PADReset(unsigned int mask);
unsigned int fn_8042D324(void *g);
int fn_80433314(void *p);
void fn_801AA30C(void);
void fn_801AA5E4(void);
void fn_801AA75C(void);
void fn_801AAF24(void);
void fn_801AB2EC(void);
unsigned int fn_80443970(void *g);
void PADRead(PADStatus *status);
void fn_801AB440(PADStatus *status);
void fn_801AB838(register int key, register unsigned short value, register int t, register int analog);
unsigned int fn_8042F024(void *g);
void PADControlMotor(int chan, unsigned int command);
float __ieee754_sqrtf(float x);
void fn_801AB554(signed char *x, signed char *y, float r, float r2, int dz);
void fn_801AB790(unsigned char *v, unsigned char lo, unsigned char hi);
}

extern char lbl_80593BE8[];
extern "C" const unsigned int lbl_8049D950[4];

Pad lbl_805932A0[4];
unsigned int lbl_80593910[4];
int lbl_80593920[4];
unsigned int lbl_80593930[4];
static unsigned char sFlags[2];
int lbl_8066C638 = 0;
Pad *lbl_8066C63C = 0;
int lbl_8066C640 = 1;
void (*lbl_8066C644)(unsigned short) = 0;
void (*lbl_8066C648)(unsigned short) = 0;

inline int sn_return_decl(int a) { return a; }

extern "C" void fn_801AADF8(Pad *p, unsigned short a, unsigned short b, int t, int x);

extern "C" int fn_801AA1E8(void)
{
    unsigned int i;
    unsigned int t;

    memset(lbl_805932A0, 0, sizeof(lbl_805932A0));
    memset(sFlags, 0, sizeof(sFlags));
    SISetSamplingRate(1);
    PADInit();
    fn_801AA30C();
    for (i = 0; i < 4; i++) {
        lbl_80593910[i] = 0;
        lbl_80593920[i] = 0;
        lbl_80593930[i] = 0;
    }
    t = fn_8042D324(lbl_80593BE8) + 0x32;
    while (fn_8042D324(lbl_80593BE8) < t) {
        fn_801AA5E4();
    }
    return 1;
}

extern "C" void fn_801AA30C(void)
{
}

extern "C" void fn_801AA328(void)
{
    lbl_8066C638++;
    fn_801AA75C();
    fn_801AAF24();
}

extern "C" void fn_801AA368(void)
{
    unsigned int i;

    fn_801AB2EC();
    for (i = 0; i < 4; i++) {
        lbl_80593910[i] = 0;
        lbl_80593920[i] = 0;
        lbl_80593930[i] = 0;
    }
}

extern "C" void fn_801AA414(unsigned short ch, float a, float b, int t, int x)
{
    Pad *p;

    if (lbl_8066C640 == 0) {
        return;
    }
    if (ch > 3) {
        return;
    }
    if (t == 0 || a + b <= 0.0f) {
        return;
    }
    p = &lbl_805932A0[ch];
    if (fn_80433314(p) != 0) {
        fn_801AADF8(p, a * 65535.0f, b * 65535.0f, t, x);
    }
}

__asm__(".section .rodata\n\t.float 65535.0\n\t.text");

extern "C" void fn_801AA548(void)
{
    lbl_8066C638++;
}

extern "C" void fn_801AA570(unsigned short ch)
{
    if (ch == 99 || ch > 3) {
        lbl_8066C63C = 0;
    } else {
        lbl_8066C63C = &lbl_805932A0[ch];
    }
}

inline void sn_label_decl() { clear:; }

extern "C" void fn_801AA5E4(void)
{
    unsigned int i;
    int type;

    for (i = 0; i < 4; i++) {
        type = SIProbe(i);
        switch (type) {
        case 0x8B100000:
        case 0x09000000:
            if (fn_80433314(lbl_805932A0 + i) == 0) {
                PADReset(lbl_8049D950[i]);
                lbl_805932A0[i].connected = 1;
                if (lbl_8066C648 != 0) {
                    lbl_8066C648(i);
                }
            }
            break;
        default:
            if (lbl_805932A0[i].connected == 1) {
                lbl_805932A0[i].connected = 0;
                if (lbl_8066C644 != 0) {
                    lbl_8066C644(i);
                }
            }
            break;
        }
    }
}

extern "C" void fn_801AA75C(void)
{
    PADStatus status[4];
    int t;
    Pad *prev;
    unsigned short i;

    t = fn_80443970(lbl_80593BE8);
    prev = lbl_8066C63C;
    PADRead(status);
    fn_801AB440(status);
    for (i = 0; i < 4; i++) {
        if (status[i].err == -1) {
            PADReset(lbl_8049D950[i]);
            if (fn_80433314(lbl_805932A0 + i) != 0) {
                lbl_805932A0[i].connected = 0;
                if (lbl_8066C644 != 0) {
                    lbl_8066C644(i);
                }
            }
            continue;
        }
        if (status[i].err != 0) {
            continue;
        }
        if (fn_80433314(lbl_805932A0 + i) == 0 && PADReset(lbl_8049D950[i]) != 0) {
            lbl_805932A0[i].connected = 1;
            if (lbl_8066C648 != 0) {
                lbl_8066C648(i);
            }
        } else {
        }
        lbl_8066C63C = &lbl_805932A0[i];
        lbl_805932A0[i].sx = (float)status[i].stickX / 56.0f;
        lbl_805932A0[i].sy = (float)status[i].stickY * -1.0f / 56.0f;
        lbl_805932A0[i].cx = (float)status[i].substickX / 44.0f;
        lbl_805932A0[i].cy = (float)status[i].substickY * -1.0f / 44.0f;
        fn_801AB838(13, status[i].button & 0x8, t, 0);
        fn_801AB838(14, status[i].button & 0x4, t, 0);
        fn_801AB838(11, status[i].button & 0x1, t, 0);
        fn_801AB838(12, status[i].button & 0x2, t, 0);
        fn_801AB838(10, status[i].button & 0x1000, t, 0);
        fn_801AB838(1, status[i].button & 0x100, t, 0);
        fn_801AB838(2, status[i].button & 0x200, t, 0);
        fn_801AB838(3, status[i].button & 0x400, t, 0);
        fn_801AB838(4, status[i].button & 0x800, t, 0);
        fn_801AB838(5, status[i].button & 0x10, t, 0);
        fn_801AB838(6, status[i].triggerL, t, 1);
        fn_801AB838(7, status[i].triggerR, t, 1);
        fn_801AB838(8, status[i].button & 0x40, t, 0);
        fn_801AB838(9, status[i].button & 0x20, t, 0);
    }
    lbl_8066C63C = prev;
}

extern "C" void fn_801AADF8(Pad *p, unsigned short a, unsigned short b, int t, int x)
{
    int ch;

    if (lbl_8066C640 == 0) {
        return;
    }
    if (p->rumble != 0) {
        return;
    }
    ch = p - lbl_805932A0;
    if (lbl_80593910[ch] > 9000 && lbl_80593920[ch] == 0) {
        lbl_80593920[ch] = 2000;
    }
    if (lbl_80593920[ch] == 0) {
        PADControlMotor(ch, 1);
        p->rumble = t;
    }
}

extern "C" void fn_801AAF24(void)
{
    unsigned short i;

    if (lbl_8066C640 == 0) {
        return;
    }
    for (i = 0; i < 4; i++) {
        if (lbl_805932A0[i].connected == 0) {
            continue;
        }
        if (lbl_80593920[i] != 0) {
            lbl_80593920[i] = lbl_80593920[i] - fn_8042F024(lbl_80593BE8);
            if (lbl_80593920[i] < 0) {
                lbl_80593920[i] = 0;
                lbl_80593910[i] = 0;
            }
        }
        if (lbl_805932A0[i].rumble == 0) {
            if (lbl_80593930[i] <= 3) {
                lbl_80593910[i] = lbl_80593910[i] + fn_8042F024(lbl_80593BE8);
                lbl_80593930[i]++;
            } else {
                lbl_80593910[i] = 0;
            }
            continue;
        } else {
            lbl_80593910[i] = lbl_80593910[i] + fn_8042F024(lbl_80593BE8);
        }
        if (lbl_805932A0[i].rumble <= fn_8042F024(lbl_80593BE8)) {
            lbl_805932A0[i].rumble = 0;
            PADControlMotor(i, 0);
        } else {
            lbl_805932A0[i].rumble = lbl_805932A0[i].rumble - fn_8042F024(lbl_80593BE8);
        }
        if (lbl_805932A0[i].rumble != 0) {
            lbl_80593930[i] = 0;
        }
    }
}

extern "C" void fn_801AB2EC(void)
{
    unsigned short i;

    if (lbl_8066C640 == 0) {
        return;
    }
    for (i = 0; i < 4; i++) {
        if (lbl_805932A0[i].connected == 0) {
            continue;
        }
        if (lbl_805932A0[i].rumble == 0) {
            continue;
        }
        lbl_805932A0[i].rumble = 0;
        PADControlMotor(i, 0);
        lbl_80593910[i] = 0;
        lbl_80593920[i] = 0;
        lbl_80593930[i] = 0;
    }
}

extern "C" void fn_801AB440(PADStatus *s)
{
    unsigned int i;

    for (i = 0; i < 4; i++, s++) {
        if (s->err != 0) {
            continue;
        }
        fn_801AB554(&s->stickX, &s->stickY, 56.0f, 3136.0f, 15);
        fn_801AB554(&s->substickX, &s->substickY, 44.0f, 1936.0f, 15);
        fn_801AB790(&s->triggerL, 30, 180);
        fn_801AB790(&s->triggerR, 30, 180);
    }
}

extern "C" void fn_801AB554(signed char *x, signed char *y, float r, float r2, int dz)
{
    float d2;
    int ix = *x;
    int iy = *y;
    float len;

    if (ix < dz && ix > -dz) {
        ix = 0;
    } else if (ix > 0) {
        ix = ix - dz;
    } else {
        ix = ix + dz;
    }
    if (iy < dz && iy > -dz) {
        iy = 0;
    } else if (iy > 0) {
        iy = iy - dz;
    } else {
        iy = iy + dz;
    }
    d2 = ix * ix + iy * iy;
    if (d2 > r2) {
        len = __ieee754_sqrtf(d2);
        ix = ix / len * r;
        iy = iy / len * r;
    }
    *x = ix;
    *y = iy;
}

extern "C" void fn_801AB790(unsigned char *v, unsigned char lo, unsigned char hi)
{
    if (*v <= lo) {
        *v = 0;
    } else {
        if (*v > hi) {
            *v = hi;
        }
        *v = *v - lo;
    }
}

inline int sn_return_decl2(int a) { return a; }

extern "C" void fn_801AB838(register int key, register unsigned short value, register int t, register int analog)
{
    if (analog != 0 && lbl_8066C63C->keys[key].value > 0.0f && value != 0) {
        lbl_8066C63C->keys[key].value = (unsigned int)value / 255.0f;
    }
    if (value != 0 && lbl_8066C63C->keys[key].value == 0.0f) {
        lbl_8066C63C->keys[key].value = analog != 0 ? (unsigned int)value / 255.0f : value;
        lbl_8066C63C->keys[key].pressFrame = lbl_8066C638;
        lbl_8066C63C->keys[key].pressTime = t;
    } else if (value == 0 && lbl_8066C63C->keys[key].value > 0.0f) {
        lbl_8066C63C->keys[key].value = 0.0f;
        lbl_8066C63C->keys[key].held = t - lbl_8066C63C->keys[key].pressTime;
        lbl_8066C63C->keys[key].releaseTime = t;
        lbl_8066C63C->keys[key].releaseFrame = lbl_8066C638;
    }
}

extern "C" const unsigned int lbl_8049D950[4] = { 0x80000000, 0x40000000, 0x20000000, 0x10000000 };
