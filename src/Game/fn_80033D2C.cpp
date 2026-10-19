// Resets the object fn_80034DB0 and its neighbours update (GLOBALS 21, 19); docs/versus.md row 21.

inline int sn_return_decl(int a) { return a; }

struct Vector {
    float x;
    float y;
    float z;
    float w;
};

struct Obj {
    int f0;          // +0x0
    int f4;          // +0x4
    char pad8[0x80 - 0x8];
    Vector v80;      // +0x80
    float f90;       // +0x90
    float f94;       // +0x94
    char pad98[0x9C - 0x98];
    float f9C;       // +0x9C
    float fA0;       // +0xA0
    char padA4[0xB0 - 0xA4];
    Vector vB0;      // +0xB0
    char padC0[0xD0 - 0xC0];
    Vector vD0;      // +0xD0
    int fE0;         // +0xE0
    char padE4[0x114 - 0xE4];
    int f114;        // +0x114
    char pad118[0x120 - 0x118];
    Vector v120;     // +0x120
    char pad130[0x140 - 0x130];
    float f140;      // +0x140
    float f144;      // +0x144
    char pad148[0x180 - 0x148];
    Vector v180;     // +0x180
    float f190;      // +0x190
    float f194;      // +0x194
    float f198;      // +0x198
    float f19C;      // +0x19C
    char pad1A0[0x1A8 - 0x1A0];
    float f1A8;      // +0x1A8
    int f1AC;        // +0x1AC
    int f1B0;        // +0x1B0
    int f1B4;        // +0x1B4
    char pad1B8[0x1BC - 0x1B8];
    float f1BC;      // +0x1BC
    float f1C0;      // +0x1C0
    char pad1C4[0x1C8 - 0x1C4];
    int f1C8;        // +0x1C8
    char pad1CC[0x1F4 - 0x1CC];
    void *p1F4;      // +0x1F4
    void *p1F8;      // +0x1F8
    void *p1FC;      // +0x1FC
    char pad200[0x210 - 0x200];
    float f210;      // +0x210
    float f214;      // +0x214
    float f218;      // +0x218
    float f21C;      // +0x21C
    float f220;      // +0x220
    char pad224[0x258 - 0x224];
    float f258;      // +0x258
    char pad25C[0x290 - 0x25C];
    Vector v290;     // +0x290
    char pad2A0[0x2A8 - 0x2A0];
    float f2A8;      // +0x2A8
    float f2AC;      // +0x2AC
    Vector v2B0;     // +0x2B0
    int f2C0;        // +0x2C0
    char pad2C4[0x310 - 0x2C4];
    Vector v310;     // +0x310
    char pad320[0x350 - 0x320];
    Vector v350;     // +0x350
    char m360[0x30]; // +0x360, a matrix whose last row is +0x390
    Vector v390;     // +0x390
    char pad3A0[0x3A4 - 0x3A0];
    int f3A4;        // +0x3A4
    int f3A8;        // +0x3A8
    Vector v3AC;     // +0x3AC
    char a3BC[0x160]; // +0x3BC
    char pad51C[0x520 - 0x51C];
    Vector v520;     // +0x520
    Vector v530;     // +0x530
    int f540;        // +0x540
    int f544;        // +0x544
};

extern "C" {
void *memset(void *dst, int c, unsigned int n);
float fn_80433D20(void *record, int id, int slot);
float fn_801BDB9C(float v);
void fn_8042DCC0(void *m);
void fn_8042DC84(Vector *dst, Vector *src);
void fn_80428FA8(Vector *v, float x, float y, float z);
extern void *lbl_8066C6C8; // the GLOBALS record
extern float lbl_8066D5C0;
}

extern "C" void fn_80033D2C(register Obj *self)
{
    memset(&self->v350, 0, 0x10);
    memset(&self->v80, 0, 0x10);
    self->f90 = fn_80433D20(lbl_8066C6C8, 0x15, 0);
    self->f94 = fn_80433D20(lbl_8066C6C8, 0x15, 0);
    self->f0 = 0;
    self->f4 = 0;
    memset(&self->vB0, 0, 0x10);
    self->f9C = 255.0f;
    self->fA0 = 0.0f;
    self->p1F4 = 0;
    self->p1F8 = 0;
    self->p1FC = 0;
    self->f210 = 0.0f;
    self->f214 = 0.0f;
    self->f218 = 0.0f;
    self->f21C = 0.0f;
    self->f220 = 1.0f;
    self->f258 = 0.0f;
    memset(&self->v290, 0, 0x10);
    self->f2A8 = fn_801BDB9C(-80.0f);
    self->f2AC = fn_801BDB9C(80.0f);
    fn_8042DCC0(self->m360);
    self->f3A4 = 0;
    self->f3A8 = 1;
    memset(self->a3BC, 0, 0x160);
    memset(&self->v3AC, 0, 0x10);
    fn_8042DC84(&self->vD0, &self->v390);
    memset(&self->v120, 0, 0x10);
    self->f2C0 = 0;
    self->f114 = 0;
    self->f144 = fn_80433D20(lbl_8066C6C8, 0x13, 0);
    self->f140 = 1.3f;
    self->f1AC = 0;
    self->f1B0 = 0;
    self->f1B4 = 0;
    self->f190 = 0.0f;
    self->f194 = 0.0f;
    self->f1A8 = 0.0f;
    self->f198 = 1.0f;
    self->f19C = 0.0f;
    self->f1C0 = 0.0f;
    self->f1BC = 0.0f;
    self->f1C8 = 0;
    memset(&self->v520, 0, 0x10);
    memset(&self->v530, 0, 0x10);
    fn_80428FA8(&self->v180, lbl_8066D5C0, 0.0f, 0.0f);
    fn_80428FA8(&self->v2B0, 0.2606f, 0.6303f, 0.9546f);
    fn_80428FA8(&self->v310, -14.0f, 0.0f, 0.0f);
    self->fE0 = 0;
    self->f544 = -1;
    self->f540 = 0;
}
