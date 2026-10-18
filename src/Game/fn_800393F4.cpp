// Moves a speed-like value (+0x144) toward a GLOBALS-derived target; docs/versus.md row 21.

inline int sn_return_decl(int a) { return a; }

struct Obj;

extern "C" {
float fn_80433D20(void *record, int id, int slot);
float fn_804351DC(Obj *self);
float fn_8042E998(char *globals);
extern void *lbl_8066C6C8;  // the GLOBALS record
extern char lbl_80593BE8[]; // the globals object of Game/fn_80443908.cpp
}

struct Obj {
    char pad0[0x144];
    float f144; // +0x144
    char pad148[0x170 - 0x148];
    float f170; // +0x170
    char pad174[0x198 - 0x174];
    float f198; // +0x198
    char pad19C[0x1FC - 0x19C];
    int i1FC; // +0x1FC
    char pad200[0x218 - 0x200];
    float f218; // +0x218
    float f21C; // +0x21C
    float f220; // +0x220
};

extern "C" void fn_800393F4(register Obj *self, unsigned int a, unsigned int b)
{
    float target;
    float rate;

    if (b & 0x40000)
        target = fn_804351DC(self);
    else if (a & 0x200)
        target = self->f170;
    else
        target = fn_80433D20(lbl_8066C6C8, 0x13, 0);
    if (!(b & 0x1000000))
        target += fn_80433D20(lbl_8066C6C8, 0x51, 0);
    rate = fn_80433D20(lbl_8066C6C8, 0x1D, 0);
    target = target * self->f198;
    target = target > 0.001f ? target : 0.001f;
    if (self->f198 < 1.0f) {
        if (a & 0x2000000)
            rate = fn_80433D20(lbl_8066C6C8, 0x45, 0);
        else
            rate = fn_80433D20(lbl_8066C6C8, 0x1E, 0);
    }
    if (self->i1FC != 0 || self->f220 < 1.0f)
        self->f144 -= self->f21C;
    if (a & 0x800)
        self->f144 = target;
    else
        self->f144 = self->f144 < target
            ? (fn_8042E998(lbl_80593BE8) * rate + self->f144 > target
                ? target : self->f144 + fn_8042E998(lbl_80593BE8) * rate)
            : (self->f144 - fn_8042E998(lbl_80593BE8) * rate < target
                ? target : self->f144 - fn_8042E998(lbl_80593BE8) * rate);
    if (self->i1FC != 0 || self->f220 < 1.0f)
        self->f144 += self->f218;
}
