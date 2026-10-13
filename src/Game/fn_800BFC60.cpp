// Virtual method on a slot-owning object: throttled UI feedback (guess), then fn_80446F10 on the owner's type ID. Unit owns the 1.0f/0.3f/0.6f pool.

inline int sn_return_decl(int a) { return a; }

extern "C" {
void *fn_800CE5B0(void *self);
void *fn_800CC5E0(void *self);
int fn_8042EFF8(void *g);
int fn_8008582C(void *actor);
int fn_8043B2C8(void *slot);
float fn_80086640(void *actor);
float fn_80086614(void *actor);
int fn_80442624(void *slot);
void fn_801AA414(int id, float a, float b, int c, int d);
int fn_8009ABEC(void *actor);
void fn_80446F10(void *list, int type, float s);
extern char lbl_80593BE8[];
extern char lbl_80572538[];
}

struct Obj {
    char pad0[0x558];
    int lastTime; // +0x558
};

extern "C" void fn_800BFC60(register Obj *self, int a, int b, int c, float f, int d, int e, int g, int h)
{
    if (fn_800CE5B0(self) != 0) {
        if ((unsigned int)fn_8042EFF8(lbl_80593BE8) > (unsigned int)self->lastTime) {
            if (fn_8008582C(fn_800CC5E0(self)) == 0) {
                if (fn_8043B2C8(fn_800CE5B0(self)) != 0) {
                    float t = f / fn_80086640(fn_800CC5E0(self)) + 1.0f;
                    fn_801AA414(fn_80442624(fn_800CE5B0(self)), t * 0.3f, t * 0.6f, 0x32, 2);
                    self->lastTime = fn_8042EFF8(lbl_80593BE8);
                }
            }
        }
    }
    register void *actor = fn_800CC5E0(self);
    register int type = fn_8009ABEC(actor);
    register float h2 = fn_80086614(fn_800CC5E0(self));
    fn_80446F10(lbl_80572538, type, h2 / fn_80086640(fn_800CC5E0(self)));
}
