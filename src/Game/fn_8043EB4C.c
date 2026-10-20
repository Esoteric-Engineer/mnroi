// Table lookups, byte setters and the growable-array constructor/destructor (docs/versus.md, row 8).
// Names are guesses.

typedef struct Rec
{
    int w0;             // +0x0
    char *recs;         // +0x4, 0x18-byte records from +0x1C
    char pad8[0x35];
    unsigned char kind; // +0x3D
} Rec;

typedef struct Obj
{
    int w0;               // +0x0
    char *p4;             // +0x4
    char pad8[6];
    unsigned short idx;   // +0xE
} Obj;

extern unsigned char lbl_80670800[], lbl_806707F8[];
extern int fn_8043D694(void *p);
extern int fn_804400F4(char *p, void *self, int a);
extern void fn_80440180(void *p);
extern void fn_804401E4(void *p);

int fn_8043EB4C(register Rec *self, register int a)
{
    return fn_804400F4(self->recs + (self->kind * 0x18 + 0x1c), self, a);
}

int fn_8043EBB4(register Obj *self, register void *p, register int n)
{
    if (!fn_8043D694(p)) {
        return self->w0 + n * lbl_80670800[self->idx];
    } else {
        return self->w0 + *(unsigned short *)(self->p4 + n * 6) * lbl_806707F8[self->idx];
    }
}

void fn_8043EC70(register char *self, register int v)
{
    *self = v;
}

void fn_8043EC9C(register char *self, register int v)
{
    *self = v;
}

void fn_8043ECC8(register char *self, register int v)
{
    *self = v;
}

void fn_8043ECF4(register void *self, register int inChrg)
{
    fn_80440180(self);
    if (inChrg & 1)
        fn_804401E4(self);
}

int *fn_8043ED44(register int *self)
{
    self[0] = 0;
    self[1] = 0;
    self[2] = 0x80000000;
    return self;
}
