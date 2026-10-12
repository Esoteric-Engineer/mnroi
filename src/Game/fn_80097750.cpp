// Actor-class template property handler (kind 15); property ids and effects are in docs/characters.md section 3.
__asm__(".section .rodata\n\t.globl lbl_8048A748\nlbl_8048A748:\n\t.float 1.0\n\t.text"); // 8-aligns the claim: fn_800974B4's 1.0f, read through extern_pool

struct Prop {
    unsigned int id;
    union {
        int i;
        float f;
        char s[0x20];
    } v;
};

struct MotionSet {
    char pad0[0x24];
    unsigned int count; // +0x24
};

struct Anim {
    char pad0[0x18];
    int f18; // +0x18
    char pad1[0x28];
    int f44; // +0x44
};

struct Model {
    int unk0;
    int flags; // +0x4
    char pad8[0xA8];
    struct Anim *anim; // +0xB0
};

struct Clip {
    char pad0[0x28];
    float length; // +0x28
};

struct Actor {
    char pad00[0x30];
    unsigned int flags; // +0x30
    char pad0[0x16C];
    int f1A0; // +0x1A0
    int f1A4;
    int f1A8;
    int f1AC;
    int f1B0; // +0x1B0
    char pad1[8];
    Model *model; // +0x1BC
    struct MotionSet *f1C0;
    char pad2[0xC];
    char vec[0x10]; // +0x1D0
    char pad3[0x20];
    int f200; // +0x200
    char f204; // +0x204
    unsigned char f205; // +0x205
    char pad4[2];
    int f208;
    int f20C;
    int f210;
    float f214;
    unsigned int f218; // +0x218
    unsigned int f21C;
    int f220;
    unsigned int f224; // +0x224
    int f228; // +0x228
    int f22C;
};

struct State {
    char pad0[0x640];
    int slot; // +0x640
};

struct Factors {
    char pad0[0x30];
    float scale; // +0x30
};

extern State lbl_80552110;
extern char lbl_8064AA80[];
extern int lbl_8066B9C8;

extern "C" {
int fn_80444454(void *self);
void fn_801A1FC4(char *name);
void *fn_801A2894(int v);
void *fn_801A1A84(char *name);
Factors *fn_8009AD80(void *self);
int fn_80426AB0(State *g);
void fn_8019EA38(char *name, int variant);
void *fn_804317BC(State *g, int v);
void *fn_80443BC8(void *p);
int fn_800976C0(void *p);
void *fn_8008F470(char *name, int a, int b);
int fn_800B0C58(void *self);
void fn_80090F54(void *p);
int fn_8019DB94(Model *m, int v);
void fn_804442F0(Model *m, float v);
int fn_800FD5FC(char *name, int flag);
int fn_803A1AC4(char *tbl, char *name);
void fn_804354B8(void *dst, void *src);
}

extern "C" int fn_80097750(register Actor *self, Prop *prop, int arg)
{
    register char *name;
    void *m;
    int z;
    switch (prop->id) {
    case 0xA: {
        if (fn_80444454(self))
            fn_801A1FC4(prop->v.s);
        m = 0;
        if (lbl_8066B9C8 != -1)
            m = fn_801A2894(lbl_8066B9C8);
        if (m == 0)
            m = fn_801A1A84(prop->v.s);
        if (m != 0) {
            self->model = (Model *)m;
            self->f1C0 = 0;
            return 1;
        } else {
            return 0;
        }
    }
    case 0xD: {
        if (fn_8009AD80(self)) {
            fn_8009AD80(self)->scale *= prop->v.f;
        }
        break;
    }
    case 0x13: {
        if (self->model == 0)
            return 0;
        if (fn_80444454(self)) {
            if (fn_80426AB0(&lbl_80552110)) {
                fn_8019EA38(prop->v.s, -1);
            } else {
                z = lbl_80552110.slot == 0;
                name = prop->v.s;
                fn_8019EA38(name, fn_800976C0(fn_80443BC8(fn_804317BC(&lbl_80552110, z))));
            }
        }
        m = fn_8008F470(prop->v.s, 0, 1);
        if (m == 0)
            return 0;
        self->f1C0 = (MotionSet *)m;
        if (fn_800B0C58(self))
            fn_80090F54(m);
        if (fn_8019DB94(self->model, 0) == 0)
            return 0;
        return 1;
    }
    case 0xB:
        if (self->model == 0)
            return 1;
        self->model->flags = self->model->flags | prop->v.i;
        break;
    case 0xC:
        if (self->model == 0)
            return 1;
        fn_804442F0(self->model, prop->v.f);
        break;
    case 0x27:
        self->f200 = prop->v.i;
        break;
    case 0x24:
        self->f1A0 = fn_800FD5FC(prop->v.s, 1);
        if (self->f1A0 == 0) {
            self->f1A4 = fn_803A1AC4(lbl_8064AA80, prop->v.s);
            if (self->f1A4 == 0) {
            }
        }
        break;
    case 0x12:
        self->f1A8 = prop->v.i;
        break;
    case 0x70:
        self->f1AC = prop->v.i;
        break;
    case 0xE:
        fn_804354B8(self->vec, prop->v.s);
        break;
    case 0x6D:
        self->f208 = fn_800FD5FC(prop->v.s, 0);
        break;
    case 0x6C:
        self->f20C = (int)fn_801A1A84(prop->v.s);
        break;
    case 0x6E:
        self->f210 = fn_800FD5FC(prop->v.s, 0);
        break;
    case 0x19:
        self->f214 = prop->v.f;
        break;
    case 0x75:
        self->f22C = (int)fn_801A1A84(prop->v.s);
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void fn_800B0504(void *self);

// Resets the base state, then clears +0x1B0.
extern "C" void fn_80097C04(register Actor *self)
{
    fn_800B0504(self);
    self->f1B0 = 0;
}

// Selects variant n of the loaded motion set into +0x204; 0 if there is none, n is past its count or n is already set.
extern "C" int fn_80097C4C(register Actor *self, unsigned short n)
{
    if (!self->f1C0)
        return 0;
    if (n > self->f1C0->count)
        return 0;
    if ((unsigned short)(unsigned char)self->f204 == n)
        return 0;
    self->f204 = n;
    return 1;
}

extern "C" {
int fn_8009B0D8(void *self);
Clip *fn_8008FC18(void *set, int a, int *flags, float *scale, int b, float f);
void fn_8019AB64(Anim *a, Clip *c, float speed, int flags, float blend);
void fn_8019A9E4(Anim *a, Clip *c, float speed, int flags, float blend);
int fn_800419AC(void);
void fn_8003FE44(void *self, int a, int b);
}

// Starts clip `a` on the model's animator (mode 0 or 1); returns its length in milliseconds, or -1.
extern "C" int fn_80097CE8(register Actor *self, int a, int mode, float speed, void *set, float blend, float f)
{
    int ms;
    Clip *clip;
    int flags = 0;
    int b;
    float scale;
    if (set == 0)
        set = self->f1C0;
    if (!set || !self->model || !self->model->anim)
        return -1;
    b = fn_8009B0D8(self);
    clip = fn_8008FC18(set, a, &flags, &scale, b, f);
    if (clip == 0)
        return -1;
    speed = speed * scale;
    switch (mode) {
    case 0:
        self->model->anim->f44 = a;
        fn_8019AB64(self->model->anim, clip, speed, flags, blend);
        break;
    case 1:
        self->model->anim->f18 = a;
        fn_8019A9E4(self->model->anim, clip, speed, flags, blend);
        break;
    default:
        break;
    }
    if (mode == 0 && fn_800419AC())
        fn_8003FE44(self, 0, 0);
    ms = (int)(clip->length / speed * 1000.0f);
    return ms;
}

extern "C" float fn_8008FE88(void *set, int a, float f);

// Starts clip `a` of the loaded motion set on the model's animator in slot +0x18; returns its length in milliseconds, or -1.
extern "C" int fn_80097EC4(register Actor *self, int a, float f)
{
    int ms;
    Clip *clip;
    int flags = 0;
    float speed;
    float scale;
    void *set = self->f1C0;
    if (!set || !self->model || !self->model->anim)
        return -1;
    clip = fn_8008FC18(set, a, &flags, &scale, 0, 0.0f);
    if (clip == 0)
        return -1;
    speed = fn_8008FE88(set, a, f);
    self->model->anim->f18 = a;
    fn_8019A9E4(self->model->anim, clip, speed, flags, 7.5f);
    ms = (int)(clip->length / speed * 1000.0f);
    return ms;
}

extern "C" MotionSet *fn_8009AE00(Actor *self);
extern "C" Anim *fn_8009AF80(Actor *self);
extern "C" int fn_8009AFC8(Actor *self);
extern "C" void fn_80435578(void *self, float v);

// Retimes the model's animator for `f`: speed from the motion set's entry for the current clip (fn_8008FE88).
extern "C" void fn_80098008(register Actor *self, float f)
{
    int z = 0;
    float speed;
    if (!fn_8009AE00(self) || !self->model || !self->model->anim)
        return;
    speed = fn_8008FE88(fn_8009AE00(self), fn_8009AFC8(self), f);
    fn_80435578(fn_8009AF80(self), speed);
}



__asm__(".section .rodata\n\t.float -1.0\n\t.text"); // orphan pool word after fn_80097EC4's, which no code loads

extern "C" {
Clip *fn_8008FCEC(void *set, int a, int b, float f);
void fn_8019A1BC(Clip *c, float *out);
void fn_80435754(float *v, void *m);
}

// Looks up clip `a` (index `b`, or the actor's when negative), builds its pose into `out` and transforms it by the matrix at +0x78; returns 1 on success.
extern "C" int fn_800980C4(register Actor *self, int a, float *out, int b)
{
    Clip *clip;
    int idx;
    if (!self->f1C0 || !self->model || !self->model->anim)
        return 0;
    if (b < 0)
        idx = fn_8009B0D8(self);
    else
        idx = b;
    clip = fn_8008FCEC(self->f1C0, a, idx, -1.0f);
    if (clip == 0)
        return 0;
    fn_8019A1BC(clip, out);
    fn_80435754(out, (char *)self + 0x78);
    return 1;
}

extern "C" void fn_800B2600(void *self);
// Starts up to 0x28 of the template group's clips on a motion player, then retimes each by its share of the total length (guess).
extern "C" void fn_800981FC(register Actor *self);
extern "C" void fn_80098B18(register Actor *self);

// Runs the three setup steps on the actor in order.
extern "C" void fn_800981B4(register Actor *self)
{
    fn_800B2600(self);
    fn_800981FC(self);
    fn_80098B18(self);
}

struct Rec5C {
    int kind;
    char pad[0x58];
};

struct Group {
    char pad0[4];
    unsigned char n; // +0x4
    char pad1[0x13];
    Rec5C *recs; // +0x18
    char pad2[0x70];
    char sub[1]; // +0x8C
};

struct Flags {
    int f0;
    int f4; // +0x4
};

struct Info {
    char pad0[0x28];
    int f28; // +0x28
    int f2C;
};

extern "C" {
int fn_800B21A4(void *self);
int fn_800B2324(void *self);
int fn_8009B160(void *self);
int fn_800B22C4(void *self);
float fn_800B24D8(void *self);
void *fn_8007766C(void *a, int b, int c, short d);
int fn_80077D0C(void *a, int b);
void *fn_800775B4(void *a, int b, unsigned short c);
void fn_80077A2C(void *a, void *b, int c, int d, unsigned short e, float f, void *ext);
void *fn_800FD7E4(int a, void *ext, int b, int c);
Flags *fn_800FD698(int a, void *ext, void *b);
void fn_80383F14(void *q, float f, void *ext);
int fn_8043E690(void *self);
Flags *fn_800649F4(void *g, unsigned char j);
Flags *fn_80064670(void *g, unsigned char j, int f);
unsigned short fn_80441628(void *self);
void *fn_80441674(void *self, int i);
int fn_804415C8(void *h);
void fn_80078068(void *h, void *ext, float f);
float fn_80444428(void *h);
void *fn_8043D544(void *h);
void fn_802E769C(void *p, int v);
void ExtentCtor(void *self) __asm__("__6Extent");
}

__asm__(".section .rodata\n\t.float -1.0\n\t.float 30.0\n\t.text"); // pool words ahead of fn_800981FC's, which no code loads

// Starts up to 0x28 of the template group's clips on a motion player, then retimes each by its share of the total length (guess).
extern "C" void fn_800981FC(register Actor *self)
{
    Group *p;
    void *obj;
    int flag;
    char ext[0x200];
    void *h;
    Flags *q;
    unsigned short i;
    unsigned short n;
    float total;
    unsigned short j;
    float scale;
    float v;
    if (!fn_800B21A4(self))
        return;
    if (!self->f208)
        return;
    p = self->f20C ? *(Group **)self->f20C : *(Group **)self->model;
    if (!p || p->n == 1)
        return;
    obj = fn_8007766C(p->sub, 0, 0, 0x40);
    if (obj) {
        if (fn_80077D0C(obj, 1))
            return;
    } else {
        obj = fn_800775B4(p->sub, fn_800B2324(self), p->n);
    }
    flag = 0;
    h = fn_800FD7E4(((Info *)self->f208)->f2C, ext, ((Info *)self->f208)->f28, 0);
    if (h) {
        q = fn_800FD698(0x5B, ext, h);
        if (q)
            flag = q->f4 & 1;
        if (!flag) {
            q = fn_800FD698(0x5A, ext, h);
            if (q)
                flag = q->f4 & 0x20000;
        }
    }
    ExtentCtor(ext);
    n = 0;
    total = 0.0f;
    for (j = 0; j <= 0xFF; j++) {
        i = 0;
        while (i < p->n) {
            if ((unsigned short)fn_8043E690(&p->recs[i]) == j)
                break;
            i++;
        }
        if (i == p->n)
            break;
        if (fn_800B22C4(self))
            q = fn_800649F4(p, (unsigned char)j);
        else
            q = fn_80064670(p, (unsigned char)j, flag == 0);
        if (!q)
            continue;
        fn_80383F14(q, 1.0f, ext);
        total += *(float *)ext;
        fn_80077A2C(obj, q, 0, 1, (unsigned char)j, 0.0f, ext);
        n++;
        if (n > 0x27)
            break;
    }
    scale = fn_800B24D8(self);
    if (scale == 0.0f)
        scale = (float)(int)n * 15.0f;
    for (i = 0; i < fn_80441628(obj); i++) {
        h = fn_80441674(obj, i);
        if (fn_804415C8(h) != 1)
            continue;
        fn_80078068(h, ext, 1.0f);
        v = fn_80444428(h) / total * scale;
        v = v > 1.0f ? v : 1.0f;
        fn_802E769C(fn_8043D544(h), *(int *)&v);
    }
}

extern "C" {
void fn_800B07DC(void *self, int v);
void fn_800B1FA8(void *self, int v);
int fn_804415C8(void *h);
int fn_804415F8(void *h);
int fn_800B0DA0(void *self);
int *fn_801A36C4(void *group, unsigned char i);
int fn_802365D8(int v);
int fn_80444370(Model *m, int v);
unsigned int fn_802E7694(void *p);
void *fn_80064A68(int info, void *self, void *group, unsigned char i, void *p, int a, void *ext, int b, int c, int d, int e);
void *fn_800B24AC(void *self);
void fn_8043C18C(void *self, int flag);
void *fn_80318EB4(void *p);
void fn_80319074(void *a, void *q);
int fn_8004B60C(void *a, int b, float *c, float d, int e);
void fn_80434988(void *self);
void fn_8043632C(void *dst, void *src);
void fn_804363B8(void *self);
void fn_804363F0(void *a, void *b);
void *fn_804362D4(void *self, float *v);
void fn_80436454(void *self, float s);
}

// Spawns the template group's clip players on the actor (guess): one per track that fn_804415C8 reports as 1, combining their poses.
extern "C" void fn_80098710(register Actor *self, Actor *other, float f, int a, float *v)
{
    Group *p;
    void *r;
    char q[0x10];
    unsigned short i;
    float zero;
    void *obj;
    void *h;
    char ext[0x50];
    int t;
    float speed;
    int *e;
    int flag;
    char q2[0x10];
    if (!self->f208)
        return;
    p = self->f20C ? *(Group **)self->f20C : *(Group **)self->model;
    fn_80434988(q);
    zero = 0.0f;
    if (!p || p->n == 1)
        return;
    fn_800B07DC(self, 1);
    fn_800B1FA8(self, 1);
    obj = fn_8007766C(p->sub, 0, 0, 0x40);
    ExtentCtor(ext);
    for (i = 0; i < fn_80441628(obj); i++) {
        h = fn_80441674(obj, i);
        if (fn_804415C8(h) != 1)
            continue;
        e = fn_801A36C4(p, (unsigned char)fn_804415F8(h));
        if (!fn_80444370(self->model, fn_802365D8(*e)))
            continue;
        flag = e != 0 ? fn_802365D8(*e) == 8 : 0;
        t = fn_802E7694(fn_8043D544(h));
        speed = *(float *)&t;
        fn_80078068(h, ext, speed);
        r = fn_80064A68(self->f208, self, p, (unsigned char)fn_804415F8(h), fn_8043D544(h), 0, ext, 0, flag, 2, 0);
        fn_8043C18C(fn_800B24AC(r), 0);
        if (!flag) {
            if (fn_800B24AC(self))
                fn_8043632C(q, fn_80318EB4(fn_800B24AC(self)));
            else
                fn_804363B8(q);
            if (f > 0.0f && a && v) {
                if (fn_8004B60C(fn_800B24AC(r), a, v, 20.0f, 0)) {
                    if (other && fn_800B0DA0(other) && fn_800B24AC(other)) {
                        fn_804363F0(q, fn_80318EB4(fn_800B24AC(other)));
                    } else {
                        fn_804362D4(q2, v);
                        fn_80436454(q2, f);
                        fn_804363F0(q, q2);
                    }
                }
            }
            fn_80319074(fn_800B24AC(r), q);
        }
    }
}

extern "C" {
void *fn_8006AF90(void *rec, int a, int b);
}

// Starts one clip on the motion player for each of the template group's records whose kind is 12-21.
extern "C" void fn_80098B18(register Actor *self)
{
    Group *p;
    void *obj;
    Rec5C *rec;
    void *q;
    char ext[0x50];
    unsigned short i;
    if (!fn_8009B160(self))
        return;
    if (!self->model)
        return;
    p = *(Group **)self->model;
    obj = fn_8007766C(p->sub, 0, 0, 0x40);
    if (obj) {
        if (fn_80077D0C(obj, 5))
            return;
    } else {
        obj = fn_800775B4(p->sub, fn_800B2324(self), p->n);
    }
    ExtentCtor(ext);
    for (i = 0; i < p->n; i++) {
        rec = &p->recs[i];
        if (!((unsigned)fn_802365D8(rec->kind) > 11 && (unsigned)fn_802365D8(rec->kind) <= 21))
            continue;
        q = fn_8006AF90(rec, 0, 0);
        if (!q)
            continue;
        fn_80383F14(q, 1.0f, ext);
        fn_802E769C(q, i);
        fn_80077A2C(obj, q, 0, 5, (unsigned char)i, 0.0f, ext);
    }
}

__asm__(".section .rodata\n\t.globl lbl_8048A794\nlbl_8048A794:\n\t.float 1.0\n\t.text"); // pads the claim to 8; no code loads this word

__asm__(".section .rodata\n\t.float 0.0\n\t.text"); // orphan word ahead of fn_80098D30's pool, which no code loads

struct Target {
    char pad0[0x10];
    void *f10; // +0x10
    char pad1[4];
    float f18; // +0x18
    int f1C;
};

class Vector {
public:
    char d[0x10];
    Vector();
    void set(void *v) __asm__("fn_80434BA4");
};

class Placement {
public:
    char d[0x40];
    Placement();
};

extern char lbl_80593BE8[];

extern "C" {
unsigned int fn_8042EFF8(void *g);
void *fn_8043E2D4(void *t, int second);
float fn_8043BA58(void *p);
float fn_804365A0(void *p);
void fn_8006C028(void *out, void *t, int b, int c);
void *fn_80436684(void *p);
void fn_8042FE08(void *a, void *b, float t);
unsigned int fn_80048C14(void *pl, int v);
int fn_800B0F0C(void *self);
void *fn_800B1568(void *self);
unsigned int fn_8009ABC0(void *p);
unsigned int fn_8009ABEC(void *self);
int fn_8009B19C(void *self);
void fn_8010CDCC(void *self, int a, int b, int h, int c, int d, int e);
}

// Per-frame hook for a target: the clip-driven effect (ids 0x86/0x88) for the character types that have one.
extern "C" void fn_80098D30(register Actor *self, Target *t, int b, void *c, int d, int e)
{
    if (d && e)
        return;
    if (fn_8042EFF8(lbl_80593BE8) < self->f224)
        return;
    if (t->f18 < 0.0f ? -t->f18 < 1.5f : t->f18 < 1.5f)
        return;
    char &p1 = *(char *)fn_8043E2D4(t, b == 0);
    char &p2 = *(char *)fn_8043E2D4(t, b);
    float f24;
    float f28;
    int h;
    f24 = fn_8043BA58(fn_80318EB4(&p1));
    if ((c && f24 < 4.0f) || f24 < fn_8043BA58(fn_80318EB4(&p2)))
        return;
    f28 = fn_804365A0(fn_80318EB4(&p1));
    f28 = f28 * 0.05f >= 0.01f ? (f28 * 0.05f <= 1.0f ? f28 * 0.05f : 1.0f) : 0.01f;
    if (!d) {
        h = 0;
        if (c) {
            if (fn_800B0F0C(c))
                h = fn_8009ABC0(fn_800B1568(c));
        } else {
            void *tmp = fn_8043E2D4(t, b);
            Vector v1;
            Vector v2;
            fn_8006C028(&v2, t, b, 0);
            v1.set(fn_80436684(t->f10));
            fn_8042FE08(&v1, &v2, -0.1f);
            Placement pl;
            if (fn_8004B60C(tmp, (int)&v1, (float *)&v2, 0.2f, (int)&pl))
                h = fn_80048C14(&pl, 0);
        }
        switch (fn_8009ABEC(self)) {
        case 70:
        case 71:
        case 72:
        case 73:
        case 74:
        case 75:
        case 76:
        case 100:
        case 102:
        case 104:
        case 119:
        case 157:
        case 160:
        case 173:
        case 195:
        case 506:
        case 515:
            fn_8010CDCC(self, 0x88, 0, h, (int)(f28 * 1000.0f), 0, 0);
            break;
        case 125:
            fn_8010CDCC(self, 0x86, 0, h, (int)(f28 * 1000.0f), 0, 0);
            break;
        }
    }
    if (!e) {
        if (fn_8009B19C(self)) {
            Vector v3;
            float dead;
            v3.set(fn_80436684(t->f10));
            dead = f28 * 12.0f + 2.0f;
        }
    }
    self->f224 = fn_8042EFF8(lbl_80593BE8) + 0x258;
}

struct ActB {
    int pad;
};

struct ActD : ActB {
    int pad2;
};

struct CmpB {
    int get() __asm__("fn_800CDD58");
};

struct CmpD : CmpB {
    int pad;
};

struct EObj {
    char d[0x3AC];
    int ma() __asm__("fn_800CCA08");
    int mb() __asm__("fn_800CC9D8");
    int mc() __asm__("fn_800CCA88");
};

struct ESub : EObj {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void play(int id, void *at, int flag, float speed, int a, int b, int c, int d);
};

class EmitObj {
public:
    char d[0x10];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void emit(void *v, int a, int b);
};

extern int lbl_8066F060;

extern "C" {
int fn_800B0C1C(void *c);
void *fn_800B14C8(void *c);
void *fn_80085928(void *p);
int fn_800CD85C(void *p);
CmpD *fn_800CD834(void *p);
int fn_800B13D8(void *c);
int fn_800B0CC0(void *c);
void *fn_800B1478(void *c);
float fn_800A4620(void *p);
int fn_800A464C(void *p);
int fn_800B11F8(void *c);
unsigned int fn_8042E96C(void *g);
int fn_800B0BEC(void *c);
void *fn_800B14A0(void *c);
int fn_80085EEC(void *p);
int fn_80085EBC(void *p);
int fn_800E5B2C(void *obj, void *self, void *pos, void *dir, float f, int a, int b);
ESub *fn_80085954(void *p);
int fn_8008572C(void *a, void *b);
int fn_800B18EC(void *a, int b);
void *fn_800B1750(void *a);
float fn_8042EBF4(void *a, void *b);
void fn_800E8628(void *a, int b);
int fn_800A3F14(void *p);
int fn_800A3EE4(void *p);
int fn_800A4568(void *p);
int fn_8009AC94(void *self);
ActD *fn_800ACFA8(int h);
void fn_8002FD50(void *a, void *b, int c, int d, float f, void *g, void *h, int i, int j, float k, int l, int m, int n, int o);
EmitObj *fn_800707CC(void *p);
void fn_8042FDBC(void *out, void *v, float f);
int fn_8003119C(void *p);
void fn_80086A2C(void *p, float f);
float fn_800B1884(void *p, int v);
void *fn_80085AF0(void *p);
void fn_80130F88(void *a, void *b);
void fn_800D96A0(void *a, void *b, void *c, float f, int d, int e);
void fn_800A2F94(void *a, void *b, int c, int d, float f, void *g, void *h, float k, int l);
float fn_800A4054(void *p);
int fn_800B247C(void *c);
int fn_800B1078(void *c);
int fn_8006C7C0(void *c);
}

// Scales a target's contact speed into a reaction strength and fires the reaction effects on the way (guess); sets lbl_8066F060 for the target's type.
extern "C" float fn_80099228(register Actor *self, Target *t, int b, void *c)
{
    int i24 = 0;
    float fa = t->f18 < 0.0f ? -t->f18 : t->f18;
    float thr = 2.0f;
    float f30;
    float f34;
    if (fa < thr)
        return 0.0f;
    if (c && fn_800B0C1C(c)) {
        thr = 3.0f;
        if (fa < thr)
            return 0.0f;
        if (fn_800CD85C(fn_80085928(fn_800B14C8(c)))) {
            if (fn_800CD834(fn_80085928(fn_800B14C8(c)))->get() == fn_800B13D8(self))
                return 0.0f;
        }
    }
    if (fn_800B0CC0(self)) {
        f30 = fn_800A4620(fn_800B1478(self));
        f34 = fn_800A4620(fn_800B1478(self));
        i24 = fn_800A464C(fn_800B1478(self));
    } else {
        f30 = 12.0f;
        f30 = fa - thr < 20.0f ? (fa - thr) / 20.0f * 5.0f * f30 : f30 * 5.0f;
        f30 = f30 * self->f214;
        f34 = f30;
        if (fn_800B24D8(c) != 0.0f)
            f34 = f34 * (fn_800B24D8(self) / fn_800B24D8(c));
    }
    char &p1 = *(char *)fn_8043E2D4(t, b == 0);
    char &p2 = *(char *)fn_8043E2D4(t, b);
    float f40 = fn_8043BA58(fn_80318EB4(&p1));
    int g44 = f40 > 4.0f && f40 > fn_8043BA58(fn_80318EB4(&p2));
    int g48 = c && g44;
    if (c && !fn_800B11F8(c)) {
        g48 = g48 && (fn_8042E96C(lbl_80593BE8) > self->f218 + 1000 || self->f220 != fn_800B13D8(c));
    } else {
        g48 = 0;
    }
    if (g48) {
        Vector v50;
        Vector v60;
        v50.set(fn_80436684(t->f10));
        fn_8006C028(&v60, t, b, 0);
        switch (fn_800B0BEC(c)) {
        case 0:
        case 7: {
            void *e70 = fn_800B14A0(c);
            int i74 = fn_80085EEC(e70);
            int i78 = 1;
            if (fn_800E5B2C(fn_80085954(e70), self, &v50, &v60, f34, 0, i24)) {
                i78 = 0;
            } else if (fn_80085954(e70)->ma()) {
                i78 = 0;
            } else if (fn_800B0CC0(self) && !fn_8008572C(e70, fn_800B1478(self))) {
                i78 = 1;
            } else if (fn_80085954(e70)->mb() && (float)fn_800B18EC(e70, 0x81) < f34) {
                if (fn_8042EBF4(fn_800B1750(e70), &v60) < 0.5f) {
                    fn_800E8628(fn_80085954(e70), 0x6F);
                    i78 = 0;
                }
            } else {
                if (fn_80085954(e70)->mb())
                    i78 = 0;
            }
            lbl_8066F060 = 0;
            ESub *p7c = fn_80085954(e70);
            if (p7c->ma() && fn_8009ABEC(e70) != 0x11)
                lbl_8066F060 = 3;
            else if (p7c->mb())
                lbl_8066F060 = 1;
            else if (p7c->mc() && fn_8009ABEC(e70) != 0x11)
                lbl_8066F060 = 2;
            fn_8010CDCC(e70, 0xE, 0, 0, 500, 0, 0);
            if (fn_800B0CC0(self)) {
                int v;
                if (fn_800A3F14(fn_800B1478(self)) || (!fn_800A3EE4(fn_800B1478(self)) && !fn_800A4568(fn_800B1478(self))))
                    v = 0x88;
                else
                    v = 0x86;
                fn_8010CDCC(self, v, 0, 0, 500, 0, 0);
            }
            if (i78) {
                ActB *x80 = (ActB *)fn_800ACFA8(fn_8009AC94(self));
                if (x80 && !fn_800B0C58(x80))
                    x80 = 0;
                int i84 = 0;
                fn_8002FD50(e70, self, 7, 0, f34, &v50, &v60, i24, 1, 0.0f, 0, 0, 255, 255);
                if (fn_80085EEC(e70) && fn_80085EBC(e70)) {
                    EmitObj *o88 = fn_800707CC(e70);
                    float f8c = fn_800B24D8(self) / fn_800B24D8(e70) * fa;
                    Vector v90;
                    f8c = f8c * 10.0f;
                    fn_8042FDBC(&v90, &v60, f8c);
                    o88->emit(&v90, 0, 0);
                }
                if (!fn_80085EEC(e70) && fn_8003119C(e70)) {
                    if (f34 >= 40.0f)
                        i84 = 0x7F;
                    else
                        i84 = 0x6F;
                }
                if (x80 && fn_80085954(x80)) {
                    fn_80086A2C(x80, fn_800B1884(x80, 0xBE));
                    fn_80130F88(fn_80085AF0(x80), e70);
                }
                fn_800D96A0(e70, x80, fn_800B1478(self), f34, i24, i84);
                if (i84) {
                    fn_80085954(e70)->play(i84, &v50, 1, 1.0f, 0, 0, 0, 0);
                }
            }
            if (i74 == 0 && fn_80085EEC(fn_800B14A0(c)))
                t->f1C = 1;
            break;
        }
        case 2:
        case 8: {
            int i88;
            int i84;
            i88 = fn_800A4054(fn_800B1478(c)) <= 0.0f;
            i84 = fn_800B247C(c);
            fn_800A2F94(fn_800B1478(c), self, 7, 0, f34, &v50, &v60, 0.0f, 0);
            if (!i88 && fn_800A4054(fn_800B1478(c)) <= 0.0f && (fn_800B1078(c) || fn_8006C7C0(c)))
                t->f1C = 1;
            else if (!i84 && fn_800B247C(c))
                t->f1C = 1;
            break;
        }
        default:
            break;
        }
        self->f220 = fn_800B13D8(c);
        self->f218 = fn_8042E96C(lbl_80593BE8);
    }
    if (c && fn_800B0C1C(c)) {
        return 0.0f;
    } else {
        if (!g44) {
            return 0.0f;
        } else {
            if (fn_8042EFF8(lbl_80593BE8) > self->f21C + 250) {
                float f8c;
                f30 = fn_800A4620(fn_800B1478(self));
                f8c = (fa - 8.0f) * 0.5f;
                f8c = f8c >= 0.0f ? (f8c <= 2.0f ? f8c : 2.0f) : 0.0f;
                if (f40 < 64.0f)
                    f8c = 0.0f;
                if (f8c != 0.0f)
                    self->f21C = fn_8042EFF8(lbl_80593BE8);
                return f30 * f8c;
            } else {
                return 0.0f;
            }
        }
    }
}

extern "C" void fn_8007FAE4(void *self, int mode);

// Target-lock timer step: mode 0 counts down, 1 and 2 re-arm it 5 s ahead.
extern "C" void fn_80099F7C(register Actor *self, int mode, int notify)
{
    switch (mode) {
    case 0:
        self->f228 = self->f228 > 0 ? -1 : self->f228 - 1;
        break;
    case 1:
        self->f228 = self->f228 >= -1 ? fn_8042EFF8(lbl_80593BE8) + 5000 : self->f228 + 1;
        break;
    case 2:
        if (self->f228 >= 0)
            self->f228 = fn_8042EFF8(lbl_80593BE8) + 5000;
        break;
    default:
        break;
    }
    if (notify)
        fn_8007FAE4(self, mode);
}

extern "C" void *fn_8043E450(void *self, int second);

// Re-arms the target-lock timer of the entity picked from a pair (mode 2, notify).
extern "C" void fn_8009A088(register void *self, void *pair, int second)
{
    if (!fn_8009B19C(self))
        return;
    void *c = fn_8043E450(pair, second);
    if (c && fn_800B0F0C(c))
        fn_80099F7C((Actor *)fn_800B1568(c), 2, 1);
}

extern "C" void *fn_800B1668(void *self);
extern "C" void fn_801A57F4(void *f, int kind, int a, int *out, void *e, int p, int q, int r);

// Starts effect kind 14 on the entity's factors object; clears *out when it has none.
extern "C" void fn_8009A130(register void *self, int a, int *out)
{
    if (fn_8009AD80(self)) {
        register void *f = fn_8009AD80(self);
        fn_801A57F4(f, 0xE, a, out, fn_800B1668(self), 0, 0, 0);
    } else {
        *out = 0;
    }
}

struct Roster {
    char pad0[0x15C];
    unsigned char *ids; // +0x15C
    unsigned char count; // +0x160
};

struct Scene {
    char pad0[0x12C];
    char *records; // +0x12C, 0x1C0-byte records
};

extern "C" int fn_80430B30(void *f);
extern "C" int fn_80430BFC(void *f);
extern "C" void *fn_800B1CC8(void *self);
extern "C" void *fn_800B11C8(void *self);
extern "C" Scene *fn_800B1A98(void *self);

// True when the entity's factors pass fn_80430B30 and it, or one of its listed scene records, passes fn_80430BFC.
extern "C" int fn_8009A1D0(register void *self)
{
    if (!fn_8009AD80(self) || !fn_80430B30(fn_8009AD80(self)))
        return 0;
    if (fn_80430BFC(fn_800B1CC8(self)))
        return 1;
    if (fn_800B11C8(self)) {
        char *rec;
        unsigned short i;
        for (i = 0; i < ((Roster *)self)->count; i++) {
            rec = fn_800B1A98(self)->records + ((Roster *)self)->ids[i] * 0x1C0;
            if (fn_80430BFC(rec))
                return 1;
        }
    }
    return 0;
}

extern "C" char lbl_804F4CA8[];

extern "C" void fn_8042D7B0(void *self);

class ActorBase
{
public:
    char data[0x240];
    ActorBase() __asm__("__5Actor");
};

// Constructor of the kind-15 actor class (guessed name): base, vptr, a Root at +0x240, kind 0xF.
class ActorK : public ActorBase
{
public:
    char r240[0x40]; // +0x240, built by fn_8042D7B0
    int f280;
    ActorK();
};

ActorK::ActorK()
{
    *(void **)(data + 0x198) = lbl_804F4CA8;
    fn_8042D7B0(r240);
    data[0] = 0xF;
    f280 = 0;
}

extern "C" void fn_80097614(Actor *self);

// Release method of the kind-15 actor class: forwards to the base release.
extern "C" void fn_8009A38C(register Actor *self)
{
    fn_80097614(self);
}

extern "C" void fn_8042E438(void *self, void *v);

// Copies the actor's +0x78 value into its +0x240 Root.
extern "C" void fn_8009A3C4(register void *self)
{
    fn_8042E438((char *)self + 0x240, (char *)self + 0x78);
}

extern "C" void *fn_8004DCA0(void *a, void *b);
extern "C" void fn_800AFAB0(void *self, Scene *scene, void *found, void *r240, int flag);

// Looks up the entity's +0x270 key and, when found, hands it to fn_800AFAB0 with the +0x240 Root.
extern "C" void fn_8009A408(register void *self)
{
    void *found = fn_8004DCA0(fn_800B1CC8(self), (char *)self + 0x270);
    if (found)
        fn_800AFAB0(self, fn_800B1A98(self), found, (char *)self + 0x240, 1);
}

extern "C" int fn_8009B234(void *self);
extern "C" ActD *fn_8009B270(void *self);
extern "C" void fn_800F880C(void *reg, void *self, int a, int b);

// Actor's vtable lives at +0x198; slot 28 (+0xE8) is called by fn_8009A490.
class ActorV {
public:
    char data[0x198];
    virtual void v0(int);
    virtual void v1(int);
    virtual void v2(int);
    virtual void v3(int);
    virtual void v4(int);
    virtual void v5(int);
    virtual void v6(int);
    virtual void v7(int);
    virtual void v8(int);
    virtual void v9(int);
    virtual void v10(int);
    virtual void v11(int);
    virtual void v12(int);
    virtual void v13(int);
    virtual void v14(int);
    virtual void v15(int);
    virtual void v16(int);
    virtual void v17(int);
    virtual void v18(int);
    virtual void v19(int);
    virtual void v20(int);
    virtual void v21(int);
    virtual void v22(int);
    virtual void v23(int);
    virtual void v24(int);
    virtual void v25(int);
    virtual void v26(int);
    virtual void v27(int);
    virtual void v28(int);
};

// Release method of the kind-15 actor class: base reset, detaches from the owner's registry, then the vtable +0xE8 slot.
extern "C" void fn_8009A490(register ActorV *self)
{
    fn_80097C04((Actor *)self);
    if (fn_8009B234(self)) {
        ActB *owner = (ActB *)fn_8009B270(self);
        if (owner && fn_800B0C58(owner) && fn_80085928(owner))
            fn_800F880C(fn_80085928(owner), self, 0, 1);
        self->v28(0);
    }
}

extern "C" void fn_8004076C(void *a, void *b, int c, int d);

// Stores the key of `c` at +0x280 (0 when `c` is null) and, when fn_800419AC allows, registers `self` with `c`.
extern "C" void fn_8009A570(register void *self, void *c)
{
    if (c == 0)
        *(int *)((char *)self + 0x280) = 0;
    else
        *(int *)((char *)self + 0x280) = fn_800B13D8(c);
    if (fn_800419AC())
        fn_8004076C(c, self, 0, 0);
}

extern "C" int fn_801A5104(void *f, int kind, int a, void *vec, void *e);
extern "C" void fn_8042DC84(void *dst, void *src);
extern "C" void *fn_800B1724(void *self);

// Returns the vector at +0x1E0; unless effect kind 0x16 starts on the factors object, refreshes it from fn_800B1724 and nudges +0x1E8 by 1.3f.
extern "C" void *fn_8009A5F0(register void *self)
{
    if (!fn_8009AD80(self) || !fn_801A5104(fn_8009AD80(self), 0x16, 0, (char *)self + 0x1E0, fn_800B1668(self))) {
        fn_8042DC84((char *)self + 0x1E0, fn_800B1724(self));
        *(float *)((char *)self + 0x1E8) += 1.3f;
    }
    return (char *)self + 0x1E0;
}

// Same as fn_8009A5F0 for the vector at +0x1F0 and effect kind 0xF.
extern "C" void *fn_8009A6B4(register void *self)
{
    if (!fn_8009AD80(self) || !fn_801A5104(fn_8009AD80(self), 0xF, 0, (char *)self + 0x1F0, fn_800B1668(self))) {
        fn_8042DC84((char *)self + 0x1F0, fn_800B1724(self));
        *(float *)((char *)self + 0x1F8) += 1.3f;
    }
    return (char *)self + 0x1F0;
}

extern "C" {
int fn_800B0DDC(void *self);
void *fn_800AD1FC(void *self, int a, int b, int c);
void fn_801A5B1C(void *p, float a, float b);
void *fn_803A20D8(char *tbl, int a, void *self, int b, int c, int d, int e, float f);
void fn_80393938(void *self, void *c, int flag);
}

struct ActBase {
    int pad;
    int get() __asm__("fn_8009AC94");
};

struct ActDerived : ActBase {
    int pad2;
};

extern "C" ActDerived *fn_800B14F0(void *self); // derived-class result: the conversion for get() is what puts it in r30

// The effect object's vtable lives at +0xC8; slot 41 (+0x150) is the start method.
class EffectV {
public:
    char data[0xC8];
    virtual void v0(int);
    virtual void v1(int);
    virtual void v2(int);
    virtual void v3(int);
    virtual void v4(int);
    virtual void v5(int);
    virtual void v6(int);
    virtual void v7(int);
    virtual void v8(int);
    virtual void v9(int);
    virtual void v10(int);
    virtual void v11(int);
    virtual void v12(int);
    virtual void v13(int);
    virtual void v14(int);
    virtual void v15(int);
    virtual void v16(int);
    virtual void v17(int);
    virtual void v18(int);
    virtual void v19(int);
    virtual void v20(int);
    virtual void v21(int);
    virtual void v22(int);
    virtual void v23(int);
    virtual void v24(int);
    virtual void v25(int);
    virtual void v26(int);
    virtual void v27(int);
    virtual void v28(int);
    virtual void v29(int);
    virtual void v30(int);
    virtual void v31(int);
    virtual void v32(int);
    virtual void v33(int);
    virtual void v34(int);
    virtual void v35(int);
    virtual void v36(int);
    virtual void v37(int);
    virtual void v38(int);
    virtual void v39(int);
    virtual void v40(int);
    virtual void v41(int);
};

// Starts the attached effect: from template slot +0x1A0 (an fn_800AD1FC object, then fn_801A5B1C on its factors) or else slot +0x1A4 (an fn_803A20D8 object, then its virtual slot 41).
extern "C" void fn_8009A778(register Actor *self)
{
    int a;
    void *c;
    a = fn_800B13D8(self);
    if (fn_800B0DA0(self)) {
        a = fn_800B14F0(self)->get();
    } else if (fn_8009AC94(self) && fn_800B0CC0(self)) {
        a = fn_8009AC94(self);
    }
    if (self->f1A0) {
        c = fn_800AD1FC(self, self->f1A0, 0, a);
        if (fn_800B0DDC(self) && c && fn_800B0F0C(c) && fn_8009AD80(fn_800B1568(c))) {
            fn_800B1FA8(c, 10000);
            fn_801A5B1C(fn_8009AD80(fn_800B1568(c)), 0.0f, 9000.0f);
        }
    } else if (self->f1A4) {
        c = fn_803A20D8(lbl_8064AA80, 0, self, 0, self->f1A4, 0, 0, 0.0f);
        if (c) {
            fn_80393938(self, c, 1);
            ((EffectV *)c)->v41(a);
        }
    }
}

extern float lbl_8066B95C, lbl_8066B960;
extern float lbl_8066D658, lbl_8066D65C, lbl_8066D660, lbl_8066D664;

// Rewrites the four .sbss screen-edge floats from the two .sdata sizes when `id` is 0xFFFF; see docs/versus.md section 5.
extern "C" void fn_8009A974(void *self, int id)
{
    if (id == 0xFFFF && self) {
        lbl_8066D658 = 320.0f - lbl_8066B95C * 0.5f;
        lbl_8066D65C = lbl_8066D658 + lbl_8066B95C * 0.5f;
        lbl_8066D660 = 240.0f - lbl_8066B960 * 0.5f;
        lbl_8066D664 = lbl_8066B960 * 0.5f + lbl_8066D660 - 12.0f;
    } else {
    }
}

extern "C" void fn_80090034(void *, int);

extern "C" void fn_8009AA40(register Actor *self)
{
    if (self->f1C0) {
        fn_80090034(self->f1C0, 0);
    }
}

extern "C" void fn_8009AA88(register Actor *self)
{
}

extern "C" void fn_8009AAA8(register Actor *self)
{
}

extern "C" int fn_8009AAC8(register Actor *self)
{
    return self->flags & 0x2000;
}

extern "C" void fn_800B16D8(void *, void *);
extern "C" int fn_8009B108(void *);
extern "C" void fn_8042D854(void *, int);

extern "C" void fn_8009AAF8(register Actor *self, register void *p)
{
    fn_800B16D8(self, p);
    if (fn_8009AAC8(self)) {
        fn_8042D854(p, fn_8009B108(self));
    }
}

extern "C" unsigned char fn_8009AB64(register Actor *self)
{
    return self->f205;
}

extern "C" void fn_8009AB94(register Actor *self, register int v)
{
    self->f205 = v;
}

extern "C" unsigned int fn_8009ABC0(register void *self)
{
    return ((Actor *)self)->f1A8;
}

extern "C" unsigned int fn_8009ABEC(register void *self)
{
    return ((Actor *)self)->f1AC;
}

extern "C" void fn_8009AC18(register Actor *self, register int v)
{
    self->f1A8 = v;
}

extern "C" void fn_8009AC40(register Actor *self, register int v)
{
    self->f1AC = v;
}

extern "C" int fn_8009AC68(register Actor *self)
{
    return self->f200;
}

extern "C" int fn_8009AC94(register void *self)
{
    return ((Actor *)self)->f1B0;
}
