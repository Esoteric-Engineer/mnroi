// Character roster table accessor, then leaf accessors on small engine objects (docs/versus.md section 4.1).
// Built at -O0; the file may continue before or after this range.

// One roster entry (field offsets confirmed by this function).
typedef struct CharacterRecord
{
    char entityName[0x20];
    char nameKey[0x20];
    signed char stats[6];
    signed char unk46[2];
    int unlocked;
} CharacterRecord;

extern CharacterRecord lbl_804CA51C[20]; // normal costumes
extern CharacterRecord lbl_804CAB0C[20]; // alternate costumes
extern int lbl_804CB0FC[20];             // select-screen order -> roster index

CharacterRecord *fn_80431CCC(register int index, register int remap, register int alt)
{
    CharacterRecord *table = lbl_804CA51C;
    if (alt == 1)
        table = lbl_804CAB0C;

    if (remap != 0)
    {
        return &table[lbl_804CB0FC[index]];
    }

    return &table[index];
}

typedef struct Flags
{
    char unk0[0x40];
    unsigned int bits; // +0x40
} Flags;

int fn_80431D58(register char *self)
{
    return *(int *)(self + 0x0);
}

int fn_80431D84(register char *self)
{
    return *(int *)(self + 0x8);
}

int fn_80431DB0(register char *self)
{
    return *(int *)(self + 0x1A4);
}

int fn_80431DDC(register char *self)
{
    return *(int *)(self + 0x130);
}

int fn_80431E08(register char *self)
{
    return *(int *)(self + 0x4);
}

int fn_80431E34(register char *self)
{
    return (unsigned short)(*(unsigned short *)(self + 0x4) & 0x1);
}

int fn_80431E68(register char *self)
{
    return (unsigned short)(*(unsigned short *)(self + 0x4) & 0x6);
}

char *fn_80431E9C(register char *self, register int i)
{
    return self + i * 0x18;
}

int fn_80431ED0(register char *self)
{
    register int result = 0;
    if (fn_80431E34(fn_80431E9C(self, 0)) != 0 || fn_80431E34(fn_80431E9C(self, 1)) != 0)
        result = 1;
    return result;
}

char *fn_80431F5C(register char *self)
{
    return self + 0x8;
}

int fn_80431F88(register Flags *f)
{
    return f->bits & 0x1;
}

void fn_80431FB8(register Flags *f)
{
    f->bits |= 0x1;
}

void fn_80431FE4(register Flags *f)
{
    f->bits &= ~0x2;
}

int fn_80432010(register Flags *f)
{
    return f->bits & 0x4;
}

void fn_80432040(register Flags *f)
{
    f->bits |= 0x4;
}

void fn_8043206C(register Flags *f)
{
    f->bits &= ~0x4;
}

int fn_80432098(register char *self)
{
    return *(int *)(self + 0x44);
}

float fn_804320C4(register char *self)
{
    return *(float *)(self + 0x4C);
}

extern const float lbl_804854AC[]; // 0.0f
extern const float lbl_804854B0[]; // 1.0f

void fn_804320F0(register char *self, register float v)
{
    *(float *)(self + 0x4C) = v >= lbl_804854AC[0] ? (v <= lbl_804854B0[0] ? v : lbl_804854B0[0]) : lbl_804854AC[0];
}

float fn_80432160(register char *self)
{
    return *(float *)(self + 0x50);
}

extern const float lbl_804854B4[]; // 0.0f
extern const float lbl_804854B8[]; // 1.0f

void fn_8043218C(register char *self, register float v)
{
    *(float *)(self + 0x50) = v >= lbl_804854B4[0] ? (v <= lbl_804854B8[0] ? v : lbl_804854B8[0]) : lbl_804854B4[0];
}

float fn_804321FC(register char *self)
{
    return *(float *)(self + 0x14C);
}

extern const float lbl_804854BC[]; // 0.0f
extern const float lbl_804854C0[]; // 1.0f
extern char lbl_8057E430[];
extern void fn_801A6B28(char *obj, float v);

void fn_80432228(register char *self, register float v)
{
    *(float *)(self + 0x14C) = v >= lbl_804854BC[0] ? (v <= lbl_804854C0[0] ? v : lbl_804854C0[0]) : lbl_804854BC[0];
    fn_801A6B28(lbl_8057E430, *(float *)(self + 0x14C));
}

typedef struct Flags248
{
    char unk0[0x248];
    unsigned int bits; // +0x248
} Flags248;

extern int lbl_8066C640;

int fn_804322C0(register Flags248 *f)
{
    return f->bits & 0x1;
}

void fn_804322F0(register Flags248 *f, register int on)
{
    if (on) {
        f->bits |= 0x1;
    } else {
        f->bits &= ~0x1;
    }
    lbl_8066C640 = on;
}

int fn_8043233C(register Flags248 *f)
{
    return f->bits & 0x2;
}

void fn_8043236C(register Flags248 *f, register int on)
{
    if (on) {
        f->bits |= 0x2;
    } else {
        f->bits &= ~0x2;
    }
}

int fn_804323B4(register Flags248 *f)
{
    return f->bits & 0x4;
}

void fn_804323E4(register Flags248 *f, register int on)
{
    if (on) {
        f->bits |= 0x4;
    } else {
        f->bits &= ~0x4;
    }
}

int fn_8043242C(register char *self)
{
    return *(int *)(self + 0x24C);
}

int fn_80432458(register char *self)
{
    register int r = 1;
    if (*self == 0)
        r = 0;
    return r;
}

char *fn_80432498(register char *self)
{
    return self;
}

char *fn_804324C0(register char *self)
{
    return self + 0x20;
}

int fn_804324EC(register char *self)
{
    return *(int *)(self + 0xC);
}

extern long long OSGetTime(void);

typedef struct LowMem
{
    char unk0[0xF8];
    unsigned int busClock; // +0xF8
} LowMem;

void fn_80432518(register char *self)
{
    *(int *)(self + 0x8) = OSGetTime() / (((LowMem *)0x80000000)->busClock / 4 / 1000);
}

int fn_804325A0(register char *self)
{
    return *(int *)(self + 0x2C);
}

void fn_804325CC(register char *self)
{
    *(int *)(self + 0x5C) = 0;
}
