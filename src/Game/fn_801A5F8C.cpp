// Per-frame update: slides +0x48 toward +0x4C, fades +0x54/+0x58/+0x5C (GLOBALS 0x3B, 0x3A).

inline int sn_return_decl(int a) { return a; }

struct Owner {
    char pad0[0x220];
    unsigned int flags; // +0x220
};

struct Child {
    char pad0[0x48];
    float pos; // +0x48
};

class Driver
{
public:
    char data[0x58]; // the vptr follows at +0x58
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void update(); // vtable +0x48
};

struct Obj {
    char pad0[0x4];
    unsigned int flags; // +0x4
    char pad8[0x10 - 0x8];
    Child *kids[4]; // +0x10
    char pad20[0x48 - 0x20];
    float pos;    // +0x48
    float target; // +0x4C
    float speed;  // +0x50
    float f54;    // +0x54
    float f58;    // +0x58
    float f5C;    // +0x5C
    char pad60[0xB0 - 0x60];
    Owner *owner; // +0xB0
};

extern "C" {
int fn_804662C8(Obj *self);
int fn_80466298(Obj *self);
Driver *fn_804661A8(Obj *self);
void fn_8019A5B4(Owner *owner, float dt, int a);
float fn_80433D20(void *record, int id, int slot);
float fn_80426A84(void *g);
float fn_801A6884(float cur, float target, float step);
extern void *lbl_8066C6C8; // the GLOBALS record
extern char lbl_80593BE8[];
}

extern "C" void fn_801A5F8C(register Obj *self, float dt)
{
    unsigned int i;

    if (self->owner != 0 && !fn_804662C8(self) && !(self->owner->flags & 2))
        fn_8019A5B4(self->owner, dt, 0);
    if (fn_80466298(self)) {
        if (self->speed == 0.0f)
            self->flags &= ~0x200;
        self->pos += self->speed * dt;
        if (self->speed > 0.0f && self->pos >= self->target || self->speed < 0.0f && self->pos <= self->target) {
            self->pos = self->target;
            self->flags &= ~0x200;
        }
        for (i = 0; i < 4; i++)
            if (self->kids[i] != 0)
                self->kids[i]->pos = self->pos;
    }
    if (fn_804661A8(self))
        fn_804661A8(self)->update();
    if (self->flags & 0x800000) {
        self->f54 = fn_801A6884(self->f54, fn_80433D20(lbl_8066C6C8, 0x3B, 0), 2.0f * fn_80426A84(lbl_80593BE8));
        self->flags &= ~0x800000;
    } else if (self->f54 != 1.0f)
        self->f54 = fn_801A6884(self->f54, 1.0f, 2.0f * fn_80426A84(lbl_80593BE8));
    if (self->flags & 0x2000000) {
        self->f58 = fn_801A6884(self->f58, fn_80433D20(lbl_8066C6C8, 0x3A, 0), 2.0f * fn_80426A84(lbl_80593BE8));
        self->flags &= ~0x2000000;
    } else if (self->f58 != 1.0f)
        self->f58 = fn_801A6884(self->f58, 1.0f, 2.0f * fn_80426A84(lbl_80593BE8));
    if (self->flags & 0x4000000) {
        self->f5C = fn_801A6884(self->f5C, 0.0f, fn_80426A84(lbl_80593BE8) * 5.0f);
        self->flags &= ~0x4000000;
    } else if (self->f5C != 1.0f)
        self->f5C = fn_801A6884(self->f5C, 1.0f, fn_80426A84(lbl_80593BE8) * 5.0f);
}
