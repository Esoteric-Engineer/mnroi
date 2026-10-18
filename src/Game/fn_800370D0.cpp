// Sets +0x198/+0x19C from where +0x180's value falls between GLOBALS 17 and 16; docs/versus.md row 21.

inline int sn_return_decl(int a) { return a; }

struct Obj;

extern "C" {
float fn_80433D20(void *record, int id, int slot);
float *fn_8042FB28(void *p);
extern void *lbl_8066C6C8; // the GLOBALS record
}

struct Obj {
    char pad0[0x180];
    char v180[0x198 - 0x180]; // +0x180
    float f198; // +0x198
    float f19C; // +0x19C
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
