// Sets +0x198/+0x19C from where +0x180's value falls between GLOBALS 17 and 16, then moves +0x180
// toward a GLOBALS 15..16 window or a target (fn_800372A8).
// Owns the .rodata pools at 0x80486040 (extern_pool).

inline int sn_return_decl(int a) { return a; }

struct Obj;

extern "C" {
float fn_80433D20(void *record, int id, int slot);
float *fn_8042FB28(void *p);
float fn_8043517C(Obj *self);
float fn_8042E998(void *timer);
float fn_801BDB9C(float x);
int fn_80037048(Obj *self, unsigned int flags, unsigned int flags2);
extern void *lbl_8066C6C8; // the GLOBALS record
extern float lbl_8066D5C0;
extern char lbl_80593BE8[0x70];
}

struct Obj {
    char pad0[0x80];
    char v80[0x180 - 0x80]; // +0x80
    char v180[0x14]; // +0x180
    float f194; // +0x194
    float f198; // +0x198
    float f19C; // +0x19C
    char pad1A0[0x214 - 0x1A0];
    float f214; // +0x214
};

extern "C" void fn_800370D0(register Obj *self, float scale, unsigned int flags)
{
    float t;

    if (*fn_8042FB28(self->v180) > fn_80433D20(lbl_8066C6C8, 0x11, 0)) {
        t = (*fn_8042FB28(self->v180) - fn_80433D20(lbl_8066C6C8, 0x11, 0))
            / (fn_80433D20(lbl_8066C6C8, 0x10, 0) - fn_80433D20(lbl_8066C6C8, 0x11, 0));
        t = t >= 0.0f ? (t <= 1.0f ? t : 1.0f) : 0.0f;
        if (flags & 0x2000000)
            self->f198 = (fn_80433D20(lbl_8066C6C8, 0x44, 0) - 1.0f) * t + 1.0f;
        else
            self->f198 = (fn_80433D20(lbl_8066C6C8, 0x12, 0) - 1.0f) * t + 1.0f;
        self->f19C = t * scale;
    } else {
        self->f198 = 1.0f;
        self->f19C = 0.0f;
    }
}

extern "C" void fn_800372A8(register Obj *self, unsigned int flags, unsigned int flags2)
{
    float scale;
    float lo;
    float hi;

    if (flags & 0x4)
        scale = 0.3f;
    else if (flags & 0x80)
        scale = 0.3f;
    else if (flags & 0x100)
        scale = 0.3f;
    else
        scale = 0.3f;

    if (*fn_8042FB28(self->v80) != 0.0f && !(flags2 & 0x100000)) {
        lo = fn_80433D20(lbl_8066C6C8, 0xF, 0) < *fn_8042FB28(self->v180)
            ? fn_80433D20(lbl_8066C6C8, 0xF, 0) : *fn_8042FB28(self->v180);
        hi = fn_80433D20(lbl_8066C6C8, 0x10, 0) > *fn_8042FB28(self->v180)
            ? fn_80433D20(lbl_8066C6C8, 0x10, 0) : *fn_8042FB28(self->v180);
        if (flags2 & 0x10000) {
            lo = fn_80433D20(lbl_8066C6C8, 0xF, 0) < fn_8043517C(self)
                ? fn_80433D20(lbl_8066C6C8, 0xF, 0) : fn_8043517C(self);
            hi = fn_80433D20(lbl_8066C6C8, 0x10, 0) > fn_8043517C(self)
                ? fn_80433D20(lbl_8066C6C8, 0x10, 0) : fn_8043517C(self);
        }
        *fn_8042FB28(self->v180) = fn_801BDB9C(
            *fn_8042FB28(self->v180) + fn_801BDB9C(*fn_8042FB28(self->v80)) >= lo
                ? (*fn_8042FB28(self->v180) + fn_801BDB9C(*fn_8042FB28(self->v80)) <= hi
                    ? *fn_8042FB28(self->v180) + fn_801BDB9C(*fn_8042FB28(self->v80)) : hi)
                : lo);
        fn_800370D0(self, scale, flags);
    } else {
        fn_800370D0(self, scale, flags);
        if (flags & 0x10000)
            return;
        if (flags2 & 0x10000) {
            if (!(flags2 & 0x80000) && !(flags2 & 0x80))
                return;
            *fn_8042FB28(self->v180) = *fn_8042FB28(self->v180) < fn_8043517C(self)
                ? (*fn_8042FB28(self->v180) + fn_8042E998(lbl_80593BE8) * 80.0f > fn_8043517C(self)
                    ? fn_8043517C(self) : *fn_8042FB28(self->v180) + fn_8042E998(lbl_80593BE8) * 80.0f)
                : (*fn_8042FB28(self->v180) - fn_8042E998(lbl_80593BE8) * 80.0f < fn_8043517C(self)
                    ? fn_8043517C(self) : *fn_8042FB28(self->v180) - fn_8042E998(lbl_80593BE8) * 80.0f);
        } else {
            if (!fn_80037048(self, flags, flags2))
                return;
            hi = lbl_8066D5C0 + self->f194 + self->f214;
            lo = flags2 & 0x8000 ? fn_80433D20(lbl_8066C6C8, 0x20, 0) : fn_80433D20(lbl_8066C6C8, 0x1F, 0);
            *fn_8042FB28(self->v180) = *fn_8042FB28(self->v180) < hi
                ? (*fn_8042FB28(self->v180) + fn_8042E998(lbl_80593BE8) * lo > hi
                    ? hi : *fn_8042FB28(self->v180) + fn_8042E998(lbl_80593BE8) * lo)
                : (*fn_8042FB28(self->v180) - fn_8042E998(lbl_80593BE8) * lo < hi
                    ? hi : *fn_8042FB28(self->v180) - fn_8042E998(lbl_80593BE8) * lo);
        }
    }
}
