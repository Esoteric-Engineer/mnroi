// The kind-7 actor class (vtable lbl_804F4A18): virtuals, constructor, property handler and accessors (docs/story.md row 24).
// Literal pool read from 0x804886AC (extern_pool).

inline int sn_return_decl(int a)
{
    return a;
}

struct Prop {
    unsigned int id;
    union {
        int i;
        float f;
        unsigned short h[2];
        unsigned char b[4];
        char s[0x20];
    } v;
};

struct SCtl {
    char data[0x3AC];
    virtual void v0();
    virtual void v1();
    virtual ~SCtl();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23(int a, int b);
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
};

struct Actor {
    char data[0x198];
    void *vptr;       // +0x198
    char pad19C[0xC];
    int f1A8;         // +0x1A8
    int f1AC;         // +0x1AC
    char pad1B0[0x290 - 0x1B0];
    char f290[0x24];  // +0x290, built by fn_801B54E8
    int f2B4;         // +0x2B4
    int f2B8;         // +0x2B8
    char pad2BC[4];
    char f2C0[0x10];  // +0x2C0
    int f2D0;         // +0x2D0
    char pad2D4[0x18];
    float f2EC;       // +0x2EC
    float f2F0;       // +0x2F0
    int f2F4;         // +0x2F4
    char pad2F8[4];
    int f2FC;         // +0x2FC
    unsigned int f300; // +0x300, ACTOR_FLAGS
    unsigned int f304; // +0x304
    unsigned int f308; // +0x308, ACTOR_ABILITIES
    unsigned int f30C; // +0x30C
    char pad310[4];
    short f314;       // +0x314
    short f316;       // +0x316
    char pad318[4];
    float f31C;       // +0x31C
    float f320;       // +0x320
    float f324;       // +0x324
    float f328;       // +0x328
    float f32C;       // +0x32C
    float f330;       // +0x330
    float f334;       // +0x334
    int f338;         // +0x338
    float f33C;       // +0x33C
    float f340;       // +0x340
    float f344;       // +0x344
    float f348;       // +0x348
    int f34C;         // +0x34C
    int f350;         // +0x350
    char pad354[0xC];
    char v360[0x10];  // +0x360, a Vector
    float f370[2];    // +0x370
    float f378[2];    // +0x378
    void *f380;       // +0x380
    unsigned short f384; // +0x384
    char pad386[2];
    int f388;         // +0x388
    int f38C;         // +0x38C
    int f390;         // +0x390
    char pad394[0xC];
    float v3A0[4];    // +0x3A0, a Vector
    int f3B0;         // +0x3B0
    int f3B4;         // +0x3B4
    float f3B8;       // +0x3B8
    int f3BC;         // +0x3BC
    int f3C0;         // +0x3C0
    float f3C4;       // +0x3C4
    float f3C8;       // +0x3C8
    float f3CC;       // +0x3CC
    float f3D0;       // +0x3D0
    int f3D4;         // +0x3D4
    float f3D8;       // +0x3D8
    SCtl *f3DC;       // +0x3DC
    int f3E0;         // +0x3E0
    int f3E4;         // +0x3E4
    int f3E8;         // +0x3E8
    int f3EC;         // +0x3EC
    int f3F0;         // +0x3F0
    int f3F4;         // +0x3F4
};

extern "C" {

void fn_8009A38C(Actor *self);
int fn_80086E2C(Actor *self);
float fn_80086C44(Actor *self, int i);
int fn_80086908(Actor *self);
int fn_80086B6C(Actor *self);
void fn_800863AC(Actor *self, int bit);
void fn_800863DC(Actor *self, int bit);
float fn_80086614(Actor *self);
void *fn_80085980(Actor *self);
int fn_80085EBC(Actor *self);
int fn_80085D6C(Actor *self);

void fn_80084030(register Actor *self)
{
    if (self->f3DC) {
        self->f3DC->v18();
        delete self->f3DC;
        self->f3DC = 0;
    }
    fn_8009A38C(self);
}

extern char lbl_804F4A18[];
void ActorK_ctor(void *self) __asm__("__6ActorK");
void Vector_ctor(void *self) __asm__("__6Vector");
void fn_801B54E8(void *self, int n, float f);
void *memset(void *dst, int c, unsigned long n);

Actor *fn_800840F8(register Actor *self)
{
    ActorK_ctor(self);
    self->vptr = lbl_804F4A18;
    fn_801B54E8(self->f290, 25, 0.2f);
    Vector_ctor(self->v360);
    Vector_ctor(self->v3A0);
    self->f300 = 0;
    self->f304 = 0;
    self->f308 = 0;
    self->f30C = 0;
    self->f314 = 0;
    self->f316 = 0;
    memset(self->v360, 0, 0x10);
    self->f3DC = 0;
    self->f350 = 0;
    self->f344 = 1.0f;
    self->f348 = 1.0f;
    self->f34C = 0;
    self->f1A8 = 0x10;
    self->f1AC = 0;
    self->f31C = 100.0f;
    self->f320 = 100.0f;
    self->f32C = self->f31C;
    self->f330 = 0.0f;
    self->f334 = 0.0f;
    self->f338 = 0;
    self->f388 = 0;
    self->f3B8 = 1.0f;
    for (unsigned int i = 0; i < 2; i++) {
        self->f370[i] = 20.0f;
        self->f378[i] = 20.0f;
    }
    self->f3E0 = 0;
    self->f3E4 = -1;
    self->f3E8 = 0;
    self->f3EC = 0;
    self->data[0] = 0;
    self->f3BC = 0;
    self->f3B0 = 0;
    self->f3B4 = 0;
    self->f3C0 = 0;
    self->f3F0 = 0;
    self->data[0] = 7;
    self->f2B4 = 0;
    self->f2B8 = 0;
    memset(self->f2C0, 0, 0x10);
    self->f328 = 100.0f;
    self->f324 = 100.0f;
    self->f2D0 = 0;
    self->f2EC = 1.0f;
    self->f2F0 = 1.0f;
    self->f2F4 = 0;
    self->f2FC = 0;
    self->f380 = 0;
    self->f384 = 0;
    self->f3C4 = 0.0f;
    self->f3C8 = 0.0f;
    self->f3CC = 0.0f;
    self->f3D4 = 0;
    self->f3D8 = 0.0f;
    self->f3F4 = 0;
    return self;
}

void fn_8009A490(Actor *self);
void fn_8007072C(Actor *self);
SCtl *fn_80085928(Actor *self);
void fn_801347B4(void *p);

void fn_800843C0(register Actor *self)
{
    fn_8009A490(self);
    if (fn_80085EBC(self))
        fn_8007072C(self);
    if (fn_80085928(self))
        fn_80085928(self)->v36();
    if (fn_80085980(self))
        fn_801347B4(fn_80085980(self));
    fn_800863DC(self, 0x84);
}

}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.text"); // "_%s"

extern char lbl_8064AA80[];

extern "C" {
int fn_80137CEC(char *name);
int fn_800FD5FC(char *name, int flag);
int fn_803A1AC4(char *tbl, char *name);
}

extern "C" int fn_80084498(register Actor *self, Prop *prop, int arg)
{
    switch (prop->id) {
    case 0x33:
        self->f31C = prop->v.i;
        self->f32C = self->f31C;
        break;
    case 0x34:
        self->f320 = prop->v.i;
        break;
    case 0x37:
        self->f33C = prop->v.f;
        break;
    case 0x38:
        self->f340 = prop->v.f;
        break;
    case 0x2E:
        self->f384 = fn_80137CEC(prop->v.s);
        break;
    case 0x31:
        self->f30C = prop->v.i;
        break;
    case 0x32:
        self->f308 = prop->v.i;
        break;
    case 0x35:
        self->f324 = prop->v.f;
        break;
    case 0x36:
        self->f328 = prop->v.f;
        break;
    case 0x30:
        self->f300 = prop->v.i;
        break;
    case 0x2D:
        self->f314 = prop->v.h[1];
        break;
    case 0x3A:
        self->f316 = prop->v.b[3];
        break;
    case 0x3B:
        self->f3B4 = fn_800FD5FC(prop->v.s, 0);
        if (self->f3B4 == 0) {
            self->f3B0 = fn_803A1AC4(lbl_8064AA80, prop->v.s);
        }
        break;
    case 0x6F:
        self->f3C0 = fn_803A1AC4(lbl_8064AA80, prop->v.s);
        break;
    default:
        return 0;
    }
    return 1;
}

extern int lbl_8066B8CC;
extern char lbl_8057217C[];

extern "C" {

int fn_8008582C(Actor *actor);
int fn_8043B31C(int h);
void fn_80428EEC(void *p, int id);

void fn_80084734(register Actor *self, int i, float v)
{
    float old = self->f378[i];
    self->f378[i] = v >= 0.0f ? (v <= 10000.0f ? v : 10000.0f) : 0.0f;
    switch (i) {
    case 0:
        self->f378[0] = v >= 0.0f ? (v <= self->f378[1] ? v : self->f378[1]) : 0.0f;
        break;
    }
}

void fn_80084838(register Actor *self, int i, float v)
{
    float old = fn_80086C44(self, i);
    self->f370[i] = v >= 0.0f ? (v <= 10000.0f ? v : 10000.0f) : 0.0f;
    switch (i) {
    case 0:
        self->f370[i] = v >= 0.0f ? (v <= self->f378[1] ? v : self->f378[1]) : 0.0f;
        break;
    }
}

void fn_80084958(register Actor *self, float v)
{
    float old = fn_80086614(self);
    self->f31C = v >= 0.0f ? (v <= self->f320 ? v : self->f320) : 0.0f;
}

void fn_800849EC(register Actor *self, float v)
{
    self->f324 = v >= 0.0f ? (v <= self->f328 ? v : self->f328) : 0.0f;
}

int fn_80084A60(register Actor *self, float v)
{
    if (lbl_8066B8CC || fn_80086B6C(self) || fn_80086908(self))
        return 1;
    if (v <= 0.0f)
        return 1;
    if (self->f324 < v) {
        if (self->f2FC && !fn_8008582C(self))
            fn_80428EEC(lbl_8057217C, fn_8043B31C(self->f2FC));
        return 0;
    }
    self->f324 -= v;
    return 1;
}

}

extern "C" {
int fn_8008618C(Actor *actor);
float fn_800B1884(void *actor, int id);
unsigned int fn_80435904(void);
}

extern "C" int fn_80084B68(register Actor *self, float f)
{
    if (fn_80086B6C(self) || fn_80086908(self)) {
        return 1;
    }
    if (self->f324 < f) {
        return 0;
    }
    if (fn_8008582C(self) && fn_8008618C(self)) {
        float t = fn_800B1884(self, 0xDE);
        if (self->f324 - f < t) {
            if (fn_80435904() % 100 == 0) {
            } else {
                return 0;
            }
        }
    }
    return 1;
}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.text"); // 0.0f

struct SVector {
    float x, y, z, w;
    SVector() __asm__("__6Vector");
} __attribute__((aligned(8)));

class VectorTriple {
public:
    char d[0x40];
    VectorTriple(void *a, void *b, float s);
};

class Placement {
public:
    char d[0x40];
    Placement();
};

struct SKind {
    virtual void v0();
    virtual void v1();
    virtual int v2();
};

extern char lbl_80593DE0[];
extern char lbl_80593DF0[];

extern "C" {

void fn_8042DC84(void *dst, void *src);
void fn_80050B04(Actor *self, int a, int b);
void fn_800981B4(Actor *self);
void fn_80070870(Actor *self);
void fn_80429090(SVector *out, void *a, void *b, float t);
SKind *fn_80435340(int p);
int fn_8004B2DC(int p, VectorTriple *t, int *key, Placement *out);
int fn_8004B150(int p, VectorTriple *t, Placement *out);
float fn_80434E0C(Placement *p);
SVector *fn_80437168(Placement *p);

int fn_80084C80(register Actor *self, Actor *other)
{
    if (other == 0)
        return 0;
    return fn_8008582C(self) == fn_8008582C(other);
}

void fn_80084CFC(register Actor *self, int a, int b)
{
    if (self->f3DC)
        self->f3DC->v23(a, b);
    else
        fn_80050B04(self, a, b);
}

void fn_80084D98(register Actor *self)
{
    fn_800981B4(self);
    if (fn_80085D6C(self))
        fn_80070870(self);
}

void fn_80084DF4(register Actor *self, int a, int b, int c, int d)
{
}

int fn_80084E2C(register Actor *self, void *pos, float *out)
{
    if (!fn_80086E2C(self))
        return 0;
    SVector a;
    fn_80429090(&a, pos, lbl_80593DE0, 0.05f);
    VectorTriple t(&a, lbl_80593DF0, 0.1f);
    Placement p;
    if (fn_80435340(self->f388)->v2() == 0x18) {
        if (fn_8004B2DC(self->f388, &t, &self->f38C, &p)) {
            if (out)
                *out = fn_80434E0C(&p);
            fn_8042DC84(self->v3A0, fn_80437168(&p));
            return 1;
        }
    } else if (fn_8004B150(self->f388, &t, &p)) {
        if (out)
            *out = fn_80434E0C(&p);
        fn_8042DC84(self->v3A0, fn_80437168(&p));
        return 1;
    }
    return 0;
}

}

struct SVec4 {
    float v[4];
    SVec4(float x, float y, float z, float w) __asm__("fn_8042D768");
};

extern "C" {

void *fn_800B1724(Actor *self);
int fn_8008543C(Actor *self, void *a, void *pos, int flags, float f, void *outPos, float *out);
void *fn_804367A8(int p);
int fn_80436900(void *p);

int fn_80085020(register Actor *self, float s)
{
    SVector p;
    fn_8042DC84(&p, fn_800B1724(self));
    p.z += 0.15f;
    SVec4 q(0.001f, 0.001f, -1.0f, 1.0f);
    VectorTriple t(&p, &q, s + 0.15f);
    int r = fn_8008543C(self, &t, fn_800B1724(self), 2, 0.7f, 0, 0);
    if (r)
        fn_800863AC(self, 0x400000);
    else
        fn_800863DC(self, 0x400000);
    return r;
}

int fn_8008515C(register Actor *self, float f, void *b, float s)
{
    SVector p;
    fn_8042DC84(&p, fn_800B1724(self));
    p.z += 0.15f;
    SVec4 q(0.001f, 0.001f, -1.0f, 1.0f);
    VectorTriple t(&p, &q, s + 0.15f);
    int r = fn_8008543C(self, &t, fn_800B1724(self), 2, f, b, 0);
    if (r)
        fn_800863AC(self, 0x400000);
    else
        fn_800863DC(self, 0x400000);
    return r;
}

int fn_8008529C(register Actor *self)
{
    if (self->f388 == 0)
        return 0;
    return fn_80436900(fn_804367A8(self->f388));
}

int fn_80085300(register Actor *self, void *pos, float f, float s, float *out)
{
    SVector p;
    fn_8042DC84(&p, pos);
    p.z += 0.15f;
    SVec4 q(0.001f, 0.001f, -1.0f, 1.0f);
    VectorTriple t(&p, &q, s + 0.15f);
    int r = fn_8008543C(self, &t, pos, 0x8002, f, 0, out);
    if (r && out)
        *out -= 0.15f;
    return r;
}

}

struct SEnt;

extern "C" {

void *fn_800B24AC(Actor *self);
void *fn_800B1CC8(Actor *self);
int fn_8004A8A4(void *a, int flags, Placement *p, void *b, void *c, int d, int e);
void *fn_80048A74(Placement *p);
int fn_800B247C(void *e);
int fn_80442888(Placement *p);
int fn_800489BC(Placement *p);
int &fn_80434E7C(Placement *p);

int fn_8008543C(register Actor *self, void *a, void *pos, int flags, float f, void *outPos, float *out)
{
    if (fn_80084E2C(self, pos, out) && self->v3A0[2] >= f) {
        if (outPos)
            fn_8042DC84(outPos, self->v3A0);
        return 1;
    }
    Placement p;
    int hit = fn_8004A8A4(a, flags | 0x448000, &p, fn_800B24AC(self), fn_800B1CC8(self), 0, 1);
    hit = hit && fn_80437168(&p)->z >= f;
    void *e = hit ? fn_80048A74(&p) : 0;
    if (hit && (!e || !fn_800B247C(e))) {
        self->f388 = fn_80442888(&p);
        self->f390 = fn_800489BC(&p);
        self->f38C = fn_80434E7C(&p);
        fn_8042DC84(self->v3A0, fn_80437168(&p));
    } else {
        self->f388 = 0;
    }
    if (hit) {
        if (outPos)
            fn_8042DC84(outPos, self->v3A0);
        if (out)
            *out = fn_80434E0C(&p);
    }
    return hit;
}

int fn_80095608(Actor *self);
SEnt *fn_800ACFA8(int h);
int fn_800B0DA0(SEnt *e);
void fn_800A10D4(SEnt *e);

void fn_80085690(register Actor *self, int a, int h)
{
    if (fn_80095608(self)) {
        SEnt &t = *fn_800ACFA8(h);
        if (&t && fn_800B0DA0(&t))
            fn_800A10D4(&t);
    }
    if (!fn_8008582C(self)) {
    } else {
    }
}

int fn_800B0CC0(void *e);
int fn_800A43A0(void *e);
int fn_800A4408(void *e);
int fn_800A4438(void *e);
int fn_8008621C(Actor *self);
int fn_8008624C(Actor *self);

int fn_8008572C(register Actor *self, void *e)
{
    if (e == 0)
        return 0;
    if (!fn_800B0CC0(e))
        return 0;
    if (fn_800A43A0(e))
        return 1;
    if (fn_800A4408(e) && (fn_8008621C(self) || fn_8008624C(self)))
        return 1;
    if (fn_800A4438(e) && fn_8008624C(self))
        return 1;
    return 0;
}

int fn_800CC60C(SCtl *c);

int fn_8008582C(register Actor *self)
{
    return self->f3DC && fn_800CC60C(self->f3DC);
}

void *AI_GetTargetList(void *ai);
void *fn_80150200(void *list);

void *fn_8008588C(register Actor *self)
{
    void *ai = fn_80085980(self);
    if (ai && AI_GetTargetList(ai)) {
        void *t = fn_80150200(AI_GetTargetList(ai));
        if (t)
            return t;
    }
    return 0;
}

SCtl *fn_80085928(register Actor *self)
{
    return self->f3DC;
}

SCtl *fn_80085954(register Actor *self)
{
    return self->f3DC;
}

}

extern "C" {

int fn_804428B4(int p);
void *fn_8042E83C(int p);

void *fn_80085980(register Actor *self)
{
    return self->f380;
}

void fn_800859AC(register Actor *self, register void *v)
{
    self->f380 = v;
}

unsigned short fn_800859D4(register Actor *self)
{
    return self->f384;
}

float fn_80085A04(register Actor *self)
{
    return self->f2EC;
}

float fn_80085A30(register Actor *self)
{
    return self->f2F0;
}

int fn_80085AF0(register Actor *self);

int fn_80085A5C(register Actor *self)
{
    return fn_80085AF0(self) ? fn_804428B4(fn_80085AF0(self)) : 1;
}

void fn_80085AC8(register Actor *self, register int v)
{
    self->f2FC = v;
}

int fn_80085AF0(register Actor *self)
{
    return self->f2FC;
}

void *fn_80085B1C(register Actor *self)
{
    return fn_8042E83C(self->f2FC);
}

}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.text"); // 1.0f

extern "C" {

float fn_80085B60(register Actor *self)
{
    return 1.0f;
}

int fn_80085B8C(register Actor *self)
{
    return 0;
}

int fn_80085BB4(register Actor *self)
{
    return ((self->f300 >> 3) ^ 1) & 1;
}

int fn_80085BEC(register Actor *self)
{
    return self->f300 & 0x20;
}

int fn_80085C1C(register Actor *self)
{
    return self->f300 & 0x10;
}

int fn_80085C4C(register Actor *self)
{
    return self->f300 & 0x4;
}

int fn_80085C7C(register Actor *self)
{
    return self->f300 & 0x40000;
}

int fn_80085CAC(register Actor *self)
{
    return self->f300 & 0x400000;
}

int fn_80085CDC(register Actor *self)
{
    return self->f300 & 0x40;
}

int fn_80085D0C(register Actor *self)
{
    return self->f300 & 0x2;
}

int fn_80085D3C(register Actor *self)
{
    return self->f300 & 0x200;
}

int fn_80085D6C(register Actor *self)
{
    return self->f300 & 0x8000;
}

int fn_80085D9C(register Actor *self)
{
    return self->f300 & 0x100;
}

int fn_80085DCC(register Actor *self)
{
    return self->f300 & 0x80;
}

int fn_80085DFC(register Actor *self)
{
    return self->f300 & 0x400;
}

int fn_80085E2C(register Actor *self)
{
    return self->f300 & 0x800;
}

int fn_80085E5C(register Actor *self)
{
    return self->f300 & 0x2000;
}

int fn_80085E8C(register Actor *self)
{
    return self->f300 & 0x100000;
}

int fn_80085EBC(register Actor *self)
{
    return self->f304 & 0x10000;
}

int fn_80085EEC(register Actor *self)
{
    return self->f304 & 0x100;
}

int fn_80085F1C(register Actor *self)
{
    return self->f304 & 0x4000000;
}

int fn_80085F4C(register Actor *self)
{
    return self->f304 & 0x1;
}

}

extern "C" {

int fn_80085F7C(register Actor *self)
{
    return self->f308 & 1;
}

int fn_80085FAC(register Actor *self)
{
    return self->f308 & 0x100000;
}

int fn_80085FDC(register Actor *self)
{
    return self->f308 & 0x200;
}

int fn_8008600C(register Actor *self)
{
    return self->f308 & 0x400000;
}

int fn_8008603C(register Actor *self)
{
    return self->f308 & 0x2;
}

int fn_8008606C(register Actor *self)
{
    return self->f308 & 0x80;
}

int fn_8008609C(register Actor *self)
{
    return self->f308 & 0x20000;
}

int fn_800860CC(register Actor *self)
{
    return self->f308 & 0x40;
}

int fn_800860FC(register Actor *self)
{
    return self->f308 & 0x2000;
}

int fn_8008612C(register Actor *self)
{
    return self->f308 & 0x4000000;
}

int fn_8008615C(register Actor *self)
{
    return self->f308 & 0x8;
}

int fn_8008618C(register Actor *self)
{
    return self->f308 & 0x8000;
}

int fn_800861BC(register Actor *self)
{
    return self->f308 & 0x1000;
}

int fn_800861EC(register Actor *self)
{
    return self->f308 & 0x2000000;
}

int fn_8008621C(register Actor *self)
{
    return self->f308 & 0x10;
}

int fn_8008624C(register Actor *self)
{
    return self->f308 & 0x20;
}

int fn_8008627C(register Actor *self)
{
    return self->f308 & 0x1000000;
}

int fn_800862AC(register Actor *self)
{
    return self->f308 & 0x100;
}

int fn_800862DC(register Actor *self)
{
    return ((self->f308 >> 27) ^ 1) & 1;
}

int fn_80086314(register Actor *self)
{
    return self->f308 & 0x10000000;
}

int fn_80086344(register Actor *self)
{
    return self->f308 & 0x20000000;
}

int fn_80086374(register Actor *self)
{
    return self->f308 & 0x810004;
}

}

extern "C" {

void fn_800863AC(register Actor *self, register int bits)
{
    self->f304 |= bits;
}

void fn_800863DC(register Actor *self, register int bits)
{
    self->f304 &= ~bits;
}

void fn_80086410(register Actor *self)
{
    self->f304 |= 1;
}

void fn_8008643C(register Actor *self)
{
    self->f304 &= ~1;
}

int fn_80086468(register Actor *self)
{
    return 0;
}

void fn_80086490(register Actor *self, register int bits)
{
    self->f30C |= bits;
}

void fn_800864C0(register Actor *self, register int bits)
{
    self->f30C &= ~bits;
}

void fn_800864F4(register Actor *self, register int on)
{
    if (on)
        self->f30C |= 1;
    else
        self->f30C &= ~1;
}

int fn_8008653C(register Actor *self)
{
    return self->f30C & 1;
}

void fn_8008656C(register Actor *self, register int on)
{
    if (on)
        self->f30C |= 0x10000000;
    else
        self->f30C &= ~0x10000000;
}

int fn_800865B4(register Actor *self)
{
    return self->f30C & 0x10000000;
}

int fn_800865E4(register Actor *self)
{
    return self->f30C & 2;
}

float fn_80086614(register Actor *self)
{
    return self->f31C;
}

float fn_80086640(register Actor *self)
{
    return self->f320;
}

float fn_8008666C(register Actor *self)
{
    if (self->f320 == 0.0f)
        return 0.0f;
    return self->f31C / self->f320;
}

int fn_800866C0(register Actor *self)
{
    return self->f32C <= 10.0f;
}

float fn_80086704(register Actor *self)
{
    return self->f32C;
}

float fn_80086730(register Actor *self)
{
    if (self->f304 & 0x1000)
        return self->f328;
    else
        return self->f324;
}

float fn_8008677C(register Actor *self)
{
    return self->f328;
}

float fn_800867A8(register Actor *self)
{
    if (self->f328 == 0.0f)
        return 0.0f;
    if (self->f304 & 0x1000)
        return 1.0f;
    return self->f324 / self->f328;
}

}

extern "C" {

void fn_80086818(register Actor *self, register float d)
{
    self->f324 = d + self->f324 >= 0.0f ? (d + self->f324 <= self->f328 ? d + self->f324 : self->f328) : 0.0f;
}

int fn_80086890(register Actor *self)
{
    return self->f304 & 0x8000;
}

void fn_800868C0(register Actor *self, register int on)
{
    if (on)
        self->f304 |= 0x8000;
    else
        self->f304 &= ~0x8000;
}

int fn_80086908(register Actor *self)
{
    return self->f304 & 0x1000000;
}

void fn_80086938(register Actor *self, register int on)
{
    if (on)
        self->f304 |= 0x1000000;
    else
        self->f304 &= ~0x1000000;
}

float fn_80086980(register Actor *self)
{
    return self->f3CC;
}

void fn_800869AC(register Actor *self, register float v)
{
    self->f3CC = v;
}

float fn_800869D4(register Actor *self)
{
    return self->f3D0;
}

float fn_80086A00(register Actor *self)
{
    return self->f330;
}

void fn_80086A2C(register Actor *self, register float d)
{
    self->f330 = d + self->f330 >= 0.0f ? (d + self->f330 <= 100.0f ? d + self->f330 : 100.0f) : 0.0f;
}

void fn_80086AAC(register Actor *self, register float v)
{
    if (v >= 0.0f) {
        if (v <= 100.0f)
            self->f330 = v;
        else
            self->f330 = 100.0f;
    } else {
        self->f330 = 0.0f;
    }
}

int fn_80086B1C(register Actor *self)
{
    return !(self->f304 & 0x1000) && (self->f304 & 0x2000);
}

int fn_80086B6C(register Actor *self)
{
    return self->f304 & 0x1000;
}

int fn_80086B9C(register Actor *self)
{
    return self->f304 & 0x4000;
}

int fn_80086BCC(register Actor *self)
{
    return self->f304 & 0x800000;
}

void fn_80086BFC(register Actor *self, register int on)
{
    if (on)
        self->f304 |= 0x800000;
    else
        self->f304 &= ~0x800000;
}

float fn_80086C44(register Actor *self, register int i)
{
    return self->f370[i];
}

}

extern "C" {

float fn_80086C80(register Actor *self, register int i)
{
    return 1.0f - fn_800B1884(self, 0x86 + i);
}

void fn_80086CDC(register Actor *self, register int on)
{
    if (on)
        self->f304 |= 0x8000000;
    else
        self->f304 &= ~0x8000000;
}

int fn_80086D24(register Actor *self)
{
    return self->f304 & 0x8000000;
}

float fn_80086D54(register Actor *self)
{
    return fn_800B1884(self, 0x68);
}

float fn_80086D9C(register Actor *self)
{
    return fn_800B1884(self, 0x67);
}

float fn_80086DE4(register Actor *self)
{
    return fn_800B1884(self, 0xA7);
}

int fn_800B13A8(SEnt *e);

int fn_80086E2C(register Actor *self)
{
    if (self->f388 == 0)
        return 0;
    if (self->f390) {
        SEnt *e = fn_800ACFA8(self->f390);
        if (!e || fn_800B13A8(e) || fn_800B247C(e)) {
            self->f388 = 0;
            return 0;
        }
    }
    return 1;
}

void *fn_80434ED0(SKind *k);
int fn_8008A624(void *p, int key, unsigned short *out);
void *fn_80436900x(void *p) __asm__("fn_80436900");
int fn_800B0F0C(void *e);
void *fn_800B1568(void *e);
int fn_8009ABC0(void *p);
int fn_8006BC08(void *p);

int fn_80086EDC(register Actor *self)
{
    unsigned short id;
    void *e;
    if (!fn_80086E2C(self))
        return 0;
    if (fn_80435340(self->f388)->v2() == 0x18 && fn_8008A624(fn_80434ED0(fn_80435340(self->f388)), self->f38C, &id))
        return id;
    e = fn_80436900x(fn_804367A8(self->f388));
    if (e && fn_800B0F0C(e))
        return fn_8009ABC0(fn_800B1568(e));
    if (fn_8006BC08(fn_804367A8(self->f388)))
        return 3;
    return 0;
}

}

