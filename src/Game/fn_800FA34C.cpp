// Actor controller input (26 action states, 10 analog axes): the base class, its pad subclass and its AI subclass; docs/ai.md row 7.
// Owns .rodata from 0x8048E464 (extern_pool).

class Vector
{
public:
    float x, y, z, w;
    Vector();
} __attribute__((aligned(8)));

struct Mat4 {
    float m[16];
};

struct Ent {
    char pad0[0x194];
    virtual void s0();
};

struct PEnt : Ent { // matching_notes 44
    int x;
};

struct ViewOwner {
    char pad0[0x360];
    Mat4 m360; // +0x360
};

struct StickZone { // 0x14, lbl_804CC7F8
    int axis; // +0x0, index into AIInput::axes
    int mode; // +0x4, 1: the stick is camera-relative
    float x, y; // +0x8
    float radius; // +0x10
};

struct ComboStep { // 0x10
    float tMin, tMax; // +0x0, the window after the previous step
    int kind; // +0x8, 0-3 a PadState byte, 4 a StickZone test
    int arg; // +0xC, the pad or zone index
};

struct Combo { // 0x50, lbl_804CC810
    unsigned int count; // +0x0, steps to complete
    ComboStep steps[4]; // +0x4
    float timeout; // +0x44
    int button; // +0x48, set in AIInput::cur when the combo completes
    int pad4C;
};

extern StickZone lbl_804CC7F8[];
extern Combo lbl_804CC810[];
extern char lbl_80593BE8[];
extern unsigned int lbl_804CC80C[]; // 18, the number of combos
extern char lbl_80552110[];

struct InputAxis {
    int f0, f4, f8, fC; // fn_80447C84 sets these
    float f10; // +0x10
    float f14; // +0x14
    float f18; // +0x18
    char pad1C[4];
    Vector v20; // +0x20
};

struct Stick {
    float x, y;
};

struct PadState { // 0x18, one pad's raw read
    unsigned char b0, b1, b2, b3;
    int f4, f8, fC, f10;
    float f14;
};

class AIInput
{
public:
    int f0;
    unsigned int buf; // +0x4, which half of the double buffers is current
    int *cur; // +0x8, button states this frame
    int *prev; // +0xC, button states last frame, or 0
    int buttons[2][26]; // +0x10
    InputAxis *axes; // +0xE0
    InputAxis *axes2; // +0xE4
    char padE8[8];
    InputAxis axisBuf[2][10]; // +0xF0
    float f4B0[32]; // +0x4B0, per combo: time since its first step
    unsigned int f530[32]; // +0x530, per combo: steps done
    int f5B0; // +0x5B0, the last combo completed
    void *owner; // +0x5B4, the actor handle
    int f5B8; // +0x5B8
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void reset(); virtual void s4();
    virtual void s5(); virtual void update(); virtual void updateButtons(); virtual void updateAxes(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void resetAxis(int i); // +0x80
};

class PadInput : public AIInput
{
public:
    PadState *pads; // +0x5C0
    PadState *prevPads; // +0x5C4
    PadState padBuf[2][16]; // +0x5C8
    Stick *sticks; // +0x8C8
    Stick *prevSticks; // +0x8CC
    Stick stickBuf[2][2]; // +0x8D0
};

class AIObject
{
public:
    char d[0x5F0];
    AIObject(void *ent) __asm__("fn_80133C8C");
};

class AIDriven : public AIInput
{
public:
    AIObject *ai; // +0x5C0
};

extern char lbl_804F5708[]; // AIInput vtable
extern char lbl_804F5678[]; // PadInput vtable
extern char lbl_804F55E8[]; // AIDriven vtable
extern int lbl_8066BAAC;

inline int sn_return_decl(int a) { return a; }

extern "C" {
void fn_8042DC84(Vector *dst, Vector *src);
void fn_80447C38(Vector *v);
int fn_80041A8C(void);
void fn_800FA7B4(register AIInput *self);
void fn_800F9F88(InputAxis (*axes)[10]);
void fn_80447D18(PadState *p);
void fn_80447D84(Stick *p);
int fn_800FBF38(void);
int fn_80445F70(int port);
int fn_80447A18(int port);
int fn_80432708(int port);
int fn_80447A7C(int port);
int fn_80447AD8(int port, int flag);
int fn_80447B60(int port, int flag);
float fn_80447BE8(int port);
float fn_8043489C(int i, int axis);
void fn_80428FA8(Vector *v, float x, float y, float z);
void fn_8042D7B0(Mat4 *m);
void fn_80435754(Vector *v, Mat4 *m);
void fn_80434420(Mat4 *dst, void *src);
float fn_804290F8(Vector *a, Vector *b);
ViewOwner *fn_80094630(void *g);
PEnt *Entity_GetActor(void *self);
float fn_80426A84(void *timer);
float fn_8042EC54(Vector *v);
void fn_8042F76C(Vector *v);
float *fn_8042FB28(Vector *v);
void fn_800FAE5C(register PadInput *self);
void fn_800FAF4C(register PadInput *self);
void *fn_800859D4(PEnt *actor);
void fn_80133E5C(AIObject *ai, void *tmpl);
void fn_80133FA0(AIObject *ai);
void *AI_GetEntity(AIObject *ai);
void fn_800859AC(void *actor, void *ai);
void fn_80447DBC(AIObject *ai, int inChrg);
void fn_8013741C(AIObject *ai, int *buttons);
void fn_80137298(AIObject *ai, int kind, InputAxis *out);
InputAxis *fn_80447E68(InputAxis *a);
void __builtin_delete(void *p);
AIInput *fn_800FBF74(register AIInput *self);
void fn_800FC038(register AIInput *self, register int inChrg);
void *fn_800B1668(Ent &actor);
}

extern "C" int fn_800FA34C(register AIInput *self, int i)
{
    if (i > -1 && i <= 25) {
    } else {
        return 0;
    }
    if (!self->prev) {
        return self->cur[i];
    }
    return !self->prev[i] && self->cur[i];
}

extern "C" int fn_800FA414(register AIInput *self, int i)
{
    if (i > -1 && i <= 25) {
    } else {
        return 0;
    }
    if (!self->prev) {
        return !self->cur[i];
    }
    return self->prev[i] && !self->cur[i];
}

extern "C" int fn_800FA4E8(register AIInput *self, int i)
{
    if (i > -1 && i <= 25) {
    } else {
        return 0;
    }
    return self->cur[i];
}

extern "C" int fn_800FA554(register AIInput *self, int i)
{
    if (i > -1 && i <= 25) {
    } else {
        return 0;
    }
    return !self->cur[i];
}

extern "C" float fn_800FA5CC(register AIInput *self, int i, Vector *out)
{
    if (i > -1 && i <= 9) {
    } else {
        return 0.0f;
    }
    fn_8042DC84(out, &self->axes[i].v20);
    return self->axes[i].f18;
}

extern "C" void fn_800FA66C(register AIInput *self, int i)
{
    InputAxis *a = self->axes + i;
    if (a) {
        a->f10 = 0.0f;
        a->f14 = 0.0f;
        fn_80447C38(&a->v20);
        a->f18 = 0.0f;
    }
    if (self->axes2) {
        a = self->axes2 + i;
        if (a) {
            a->f10 = 0.0f;
            a->f14 = 0.0f;
            fn_80447C38(&a->v20);
            a->f18 = 0.0f;
        }
    }
}

extern "C" void fn_800FA76C(register AIInput *self)
{
    if (fn_80041A8C()) {
        fn_800FA7B4(self);
    }
}

extern "C" void fn_800FA7B4(register AIInput *self)
{
    unsigned int i = 0;
    for (i = 0; i <= 9; i++) {
        self->resetAxis(i);
    }
    for (i = 0; i <= 25; i++) {
        self->cur[i] = 0;
    }
}

extern "C" void fn_800FA888(register AIInput *self, void *v)
{
    self->f0 = 0;
    self->owner = v;
    self->reset();
}

extern "C" void fn_800FA8F8(register AIInput *self)
{
}

extern "C" void fn_800FA918(register PadInput *self)
{
    unsigned int i;
    unsigned int j;
    for (i = 0; i <= 1; i++) {
        for (j = 0; j <= 15; j++) {
            fn_80447D18(&self->padBuf[i][j]);
        }
        for (j = 0; j <= 1; j++) {
            fn_80447D84(&self->stickBuf[i][j]);
        }
        for (j = 0; j <= 25; j++) {
            self->buttons[i][j] = 0;
        }
    }
    fn_800F9F88(self->axisBuf);
    for (i = 0; i <= 31; i++) {
        self->f4B0[i] = 0.0f;
        self->f530[i] = 0;
    }
    self->prevPads = 0;
    self->prevSticks = 0;
    self->prev = 0;
    self->axes2 = 0;
    self->buf = 0;
    self->pads = self->padBuf[self->buf];
    self->sticks = self->stickBuf[self->buf];
    self->cur = self->buttons[self->buf];
    self->axes = self->axisBuf[self->buf];
    self->f5B8 = 0;
}

extern "C" void fn_800FAB6C(register PadInput *self)
{
    self->reset();
}

extern "C" void fn_800FABC8(register PadInput *self)
{
}

extern "C" void fn_800FABE8(register PadInput *self, unsigned int port)
{
    if (port > 15) {
        return;
    }
    PadState *p = self->pads + port;
    int on = fn_800FBF38();
    if (on == 0) {
        p->b0 = 0;
        p->b1 = 0;
        p->b2 = 0;
        p->b3 = 0;
        p->f4 = 0;
        p->f8 = 0;
        p->fC = 0;
        p->f10 = 0;
        p->f14 = 0.0f;
    } else {
        p->b0 = fn_80445F70(port);
        p->b1 = fn_80447A18(port);
        p->b2 = fn_80432708(port);
        p->b3 = fn_80447A7C(port);
        p->f4 = fn_80447AD8(port, 1);
        p->f8 = fn_80447AD8(port, 0);
        p->fC = fn_80447B60(port, 1);
        p->f10 = fn_80447B60(port, 0);
        p->f14 = fn_80447BE8(port);
    }
}

extern "C" void fn_800FAD90(register PadInput *self, int i)
{
    if (i >= 0 && (unsigned int)i <= 1) {
    } else {
    }
    Stick *s = self->sticks + i;
    if (fn_800FBF38() == 0) {
        s->x = 0.0f;
        s->y = 0.0f;
    } else {
        s->x = fn_8043489C(i, 0);
        s->y = fn_8043489C(i, 1);
    }
}

extern "C" void fn_800FAE5C(register PadInput *self)
{
    fn_800FABE8(self, 1);
    fn_800FABE8(self, 2);
    fn_800FABE8(self, 3);
    fn_800FABE8(self, 4);
    fn_800FABE8(self, 5);
    fn_800FABE8(self, 15);
    fn_800FABE8(self, 15);
    fn_800FABE8(self, 15);
    fn_800FABE8(self, 6);
    fn_800FABE8(self, 7);
    fn_800FABE8(self, 10);
    fn_800FABE8(self, 15);
    fn_800FABE8(self, 11);
    fn_800FABE8(self, 12);
    fn_800FABE8(self, 13);
    fn_800FABE8(self, 14);
}

extern "C" void fn_800FAF4C(register PadInput *self)
{
    fn_800FAD90(self, 0);
    fn_800FAD90(self, 1);
}

extern "C" int fn_800FAF94(register PadInput *self, int idx)
{
    if (idx != 0) {
        return 0;
    }
    StickZone *z = &lbl_804CC7F8[idx];
    InputAxis *a = self->axes + z->axis;
    Vector v;
    fn_80428FA8(&v, a->f10, a->f14, 0.0f);
    Vector c;
    fn_80428FA8(&c, z->x, z->y, 0.0f);
    if (z->mode == 1) {
        Mat4 m;
        fn_8042D7B0(&m);
        fn_80435754(&v, &fn_80094630(lbl_80552110)->m360);
        fn_80434420(&m, fn_800B1668(*Entity_GetActor(self->owner)));
        fn_80435754(&v, &m);
    }
    if (fn_804290F8(&v, &c) <= z->radius) {
        return 1;
    }
    return 0;
}

extern "C" void fn_800FB124(register PadInput *self, int i)
{
    Combo *c;
    float t;
    unsigned int step;
    float lim;
    PadState *pads;
    Stick *sticks;
    ComboStep *st;
    int *cur;
    int arg;

    c = &lbl_804CC810[i];
    t = self->f4B0[i];
    step = self->f530[i];
    if (step != 0) {
        t += fn_80426A84(lbl_80593BE8);
    }
    lim = c->steps[step].tMax;
    if (t > c->timeout || t > lim) {
        self->f4B0[i] = 0.0f;
        self->f530[i] = 0;
        return;
    }
    self->f4B0[i] = t;
    pads = self->pads;
    sticks = self->sticks;
    st = &c->steps[step];
    cur = self->cur;
    if (t >= st->tMin && t < st->tMax) {
        arg = st->arg;
        switch (st->kind) {
        case 0:
            if (pads[arg].b2) {
                step++;
            }
            break;
        case 1:
            if (pads[arg].b2) {
                step++;
            }
            break;
        case 2:
            if (pads[arg].b3) {
                step++;
            }
            break;
        case 3:
            if (pads[arg].b0) {
                step++;
            }
            break;
        case 4:
            if (fn_800FAF94(self, arg)) {
                step++;
            }
            break;
        default:
            break;
        }
        if (step >= c->count) {
            cur[c->button] = 1;
            self->f4B0[i] = 0.0f;
            self->f530[i] = 0;
            self->f5B0 = i;
            return;
        }
        self->f530[i] = step;
    }
}

extern "C" void fn_800FB488(register PadInput *self)
{
    int *cur = self->cur;
    unsigned int i;
    for (i = 0; i <= 25; i++) {
        cur[i] = 0;
    }
    unsigned int n = lbl_804CC80C[0];
    for (i = 0; i < n; i++) {
        fn_800FB124(self, i);
    }
}

extern "C" void fn_800FB550(register PadInput *self)
{
    InputAxis *axes = self->axes;
    int i;
    for (i = 0; i <= 9; i++) {
        InputAxis *a = axes + i;
        switch (a->f0) {
        case 0: {
            Stick *s = self->sticks + a->f8;
            a->f10 = s->x;
            a->f14 = s->y;
            Vector v;
            fn_80428FA8(&v, a->f10, -a->f14, 0.0f);
            float m = fn_8042EC54(&v);
            switch (a->f4) {
            case 2:
                break;
            case 0:
                if (m < 0.1f) {
                    m = 0.0f;
                } else if (m >= 1.0f) {
                    m = 1.0f;
                } else {
                    m = (m - 0.1f) * 1.1111112f;
                }
                fn_80435754(&v, &fn_80094630(lbl_80552110)->m360);
                v.z = 0.0f;
                fn_8042F76C(&v);
                break;
            case 1:
                break;
            case 3:
                fn_8042FB28(&v)[0] = -a->f10;
                fn_8042FB28(&v)[1] = 0.0f;
                fn_8042FB28(&v)[2] = -a->f14;
                m = fn_8042EC54(&v);
                if (m < 0.1f) {
                    m = 0.0f;
                }
                if (m > 1.0f) {
                    m = 1.0f;
                }
                break;
            case 4:
                fn_8042FB28(&v)[0] = a->f10;
                fn_8042FB28(&v)[1] = 0.0f;
                fn_8042FB28(&v)[2] = -a->f14;
                m = fn_8042EC54(&v);
                if (m < 0.1f) {
                    m = 0.0f;
                }
                if (m > 1.0f) {
                    m = 1.0f;
                }
                break;
            default:
                break;
            }
            fn_8042DC84(&a->v20, &v);
            a->f18 = m;
            break;
        }
        case 1: {
            float val;
            int pad = a->fC;
            PadState *p = self->pads + pad;
            val = p->f14;
            a->f18 = val;
            break;
        }
        default:
            break;
        }
    }
}

extern "C" void fn_800FB944(register PadInput *self)
{
    if (++self->buf > 1) {
        self->buf = 0;
    }
    self->prevPads = self->pads;
    self->pads = self->padBuf[self->buf];
    self->prevSticks = self->sticks;
    self->sticks = self->stickBuf[self->buf];
    self->prev = self->cur;
    self->cur = self->buttons[self->buf];
    fn_800FAE5C(self);
    fn_800FAF4C(self);
    self->updateAxes();
    self->updateButtons();
    fn_800FA76C(self);
}

extern "C" void fn_800FBA70(register AIDriven *self, void *owner)
{
    self->f0 = 1;
    self->owner = owner;
    self->reset();
    self->ai = new AIObject(self->owner);
    void *tmpl = fn_800859D4(Entity_GetActor(self->owner));
    fn_80133E5C(self->ai, tmpl);
}

extern "C" void fn_800FBB30(register AIDriven *self)
{
    if (self->ai) {
        fn_800859AC(AI_GetEntity(self->ai), 0);
        fn_80133FA0(self->ai);
        if (self->ai) {
            fn_80447DBC(self->ai, 3);
        } else {
        }
        self->ai = 0;
    }
}

extern "C" void fn_800FBBB8(register AIDriven *self)
{
    unsigned int i;
    unsigned int j;
    for (i = 0; i <= 1; i++) {
        for (j = 0; j <= 25; j++) {
            self->buttons[i][j] = 0;
        }
    }
    fn_800F9F88(self->axisBuf);
    self->prev = 0;
    self->axes2 = 0;
    self->buf = 0;
    self->cur = self->buttons[self->buf];
    self->axes = self->axisBuf[self->buf];
    self->f5B8 = 0;
}

extern "C" void fn_800FBCC4(register AIDriven *self)
{
    self->reset();
}

extern "C" void fn_800FBD28(register AIDriven *self)
{
}

extern "C" void fn_800FBD50(register AIDriven *self)
{
    if (++self->buf > 1) {
        self->buf = 0;
    }
    self->prev = self->cur;
    self->cur = self->buttons[self->buf];
    self->axes2 = self->axes;
    self->axes = self->axisBuf[self->buf];
    self->updateButtons();
    self->updateAxes();
    fn_800FA76C(self);
}

extern "C" void fn_800FBE4C(register AIDriven *self)
{
    fn_8013741C(self->ai, self->cur);
}

extern "C" void fn_800FBE90(register AIDriven *self)
{
    fn_80137298(self->ai, 0, self->axes);
    fn_80137298(self->ai, 9, self->axes + 9);
    fn_80137298(self->ai, 7, self->axes + 7);
}

extern "C" void fn_800FBF08(register AIDriven *self, int a, void *b)
{
}

extern "C" int fn_800FBF38(void)
{
    return !lbl_8066BAAC;
}

extern "C" AIInput *fn_800FBF74(register AIInput *self)
{
    *(char **)((char *)self + 0x5BC) = lbl_804F5708;
    register InputAxis (*base)[10];
    register int i;
    register InputAxis (*p)[10];
    // the axisBuf[2][10] member's loop, as cc1plus writes it
    ({
        base = self->axisBuf;
        p = self->axisBuf;
    });
    i = 1;
    if (i != -1) {
        for (;;) {
            register InputAxis *rowBase;
            register int j;
            register InputAxis *q;
            rowBase = *p;
            q = *p;
            j = 9;
            if (j != -1) {
                for (;;) {
                    fn_80447E68(q);
                    q++;
                    j--;
                    if (j == -1)
                        break;
                }
            }
            p++;
            i--;
            if (i == -1)
                break;
        }
    }
    self->f5B8 = 0;
    return self;
}

extern "C" void fn_800FC038(register AIInput *self, register int inChrg)
{
    *(char **)((char *)self + 0x5BC) = lbl_804F5708;
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}

extern "C" void fn_800FC090(register AIInput *self, register int a, register void *b)
{
}

extern "C" PadInput *fn_800FC0B8(register PadInput *self)
{
    fn_800FBF74(self);
    *(char **)((char *)self + 0x5BC) = lbl_804F5678;
    self->f5B8 = 0;
    return self;
}

extern "C" void fn_800FC10C(register PadInput *self, register int inChrg)
{
    *(char **)((char *)self + 0x5BC) = lbl_804F5678;
    fn_800FA8F8(self);
    fn_800FC038(self, inChrg);
}

extern "C" AIDriven *fn_800FC160(register AIDriven *self)
{
    fn_800FBF74(self);
    *(char **)((char *)self + 0x5BC) = lbl_804F55E8;
    return self;
}

extern "C" void fn_800FC1AC(register AIDriven *self, register int inChrg)
{
    *(char **)((char *)self + 0x5BC) = lbl_804F55E8;
    fn_800FC038(self, inChrg);
}
