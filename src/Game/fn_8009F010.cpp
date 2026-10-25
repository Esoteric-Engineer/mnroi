// Prop (entity kind 4) release, the target of animation event 0x05 and of a prop that has been hit.
// Sets flag 0x400000 once, then spawns the object named at +0x2B0 (a template from fn_800FD5FC at the prop's pose).
// With no template, spawns an effect of that name, and ends the prop's own state unless flag 0x8000 is set.

inline int sn_return_decl(int a) { return a; }

struct Obj {
    char pad0[0x78];
    char f78[0x10]; // +0x78, the pose handed to the spawn
    char pad88[0x290 - 0x88];
    unsigned int flags; // +0x290
    char pad294[0x2B0 - 0x294];
    signed char name[1]; // +0x2B0
};

struct Handle {
    char d[0xC8];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36();
    virtual void s37(void *v, int a); // +0x130
};

struct Mat {
    char d[0x30];
    char pos[0x10];
};

extern char lbl_8064AA80[];

extern "C" {
void *fn_800FD5FC(char *name, int flag);
void fn_8042D7B0(void *m);
void fn_8042E438(void *m, void *q);
int fn_800A1014(void *self);
void *fn_800B24AC(void *self);
void *fn_80318E84(void *p);
void fn_80434BA4(void *out, void *v);
void *fn_800B1A98(void *self);
void *fn_800B1CC8(void *self);
int fn_8009AC94(void *self);
void *fn_800AD0DC(void *tmpl, void *a, void *b, void *pose, int c);
void fn_800B0690(void *obj, void *v);
Handle *fn_803A20D8(char *tbl, char *name, void *self, int a, int b, int c, int d, float f);
void fn_8039D820(Handle *h, int v);
void fn_80393938(void *self, Handle *h, int v);
int fn_800A0E64(void *self);
void fn_800AE398(void *self, int a, int b);
}

extern "C" void fn_8009F010(register Obj *self, void *v)
{
    if (self->flags & 0x400000)
        return;
    self->flags |= 0x400000;
    if (self->name[0]) {
        void *tmpl = fn_800FD5FC((char *)self->name, 0);
        if (tmpl) {
            Mat m;
            fn_8042D7B0(&m);
            fn_8042E438(&m, self->f78);
            if (fn_800A1014(self) && fn_800B24AC(self))
                fn_80434BA4(m.pos, fn_80318E84(fn_800B24AC(self)));
            void *obj = fn_800AD0DC(tmpl, fn_800B1A98(self), fn_800B1CC8(self), self->f78, fn_8009AC94(self));
            if (obj)
                fn_800B0690(obj, v);
        } else {
            Handle *h = fn_803A20D8(lbl_8064AA80, (char *)self->name, self, 0, 0, 0, 0, 0.0f);
            if (h) {
                fn_8039D820(h, 1);
                fn_80393938(self, h, 1);
                h->s37(v, 0);
            }
        }
    }
    if (!fn_800A0E64(self))
        fn_800AE398(self, 0, 0);
}
