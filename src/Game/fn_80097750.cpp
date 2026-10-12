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
    char pad0[0x1A0];
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
    char pad4[3];
    int f208;
    int f20C;
    int f210;
    float f214;
    char pad5[0xC];
    unsigned int f224; // +0x224
    char pad6[4];
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
