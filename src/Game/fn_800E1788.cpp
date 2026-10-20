// The player controller's animation event handler: one case per event type, which sets controller fields from the event's value. Returns 0 for a type it does not handle. docs/versus.md row 28.

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

struct Ent {
    int pad;
};

struct ActBase : Ent {
    char d[0x194];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41();
    virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
    virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53();
    virtual void s54(); virtual void s55(); virtual void s56();
};

struct Act : ActBase {
    virtual int s57(float t); // +0x1D0
};

struct Handle {
    char pad0[0x28];
    float f28; // clip length (30.0f / f28 is the rate)
    char pad2C[0xC8 - 0x2C];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(Vector *pos, int z); // +0xE8
};

struct HSub : Handle {
    int pad;
};

struct EObj {
    char pad0[0x10];
    unsigned int f10;
    char pad14[0x18 - 0x14];
    unsigned int f18;
    char pad1C[0x3AC - 0x1C];
};

struct EBase : EObj {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(int state); // +0x30
};

struct Obj : EBase {
    char pad3B0[0x3EF - 0x3B0];
    unsigned char b3EF;
    char pad3F0[0x3F4 - 0x3F0];
    unsigned int f3F4;
    float f3F8;
    int f3FC;
    int f400;
    float f404;
    unsigned char b408;
    unsigned char b409;
    unsigned char b40A;
    unsigned char b40B;
    unsigned char b40C;
    char pad40D[0x414 - 0x40D];
    float f414;
};

extern "C" {
Act *Entity_GetActor(void *self);
int fn_800ACD20(Ent &actor, int id);
Handle *fn_80393D0C(Ent &actor, int id, int a, int b);
Vector *fn_800B1724(Ent &actor);
Vector *fn_800B1750(Ent &actor);
void fn_8042DC84(Vector *dst, Vector *src);
void fn_8042FE08(Vector *out, Vector *dir, float t);
void fn_800D5514(void *self);
int fn_80084A60(void *actor, float f);
int fn_800CD7D4(void *self);
void fn_80065AF8(Ent &actor, int a, int b);
void fn_800CC578(void *self, int a, int b);
void fn_800E8768(void *self, int v);
void fn_800E880C(void *self, int v);
void fn_800CBE8C(void *self);
HSub *fn_800C9FD0(void *self);
void fn_800CBE1C(void *self, void *target);
void *fn_8009AE00(Ent &actor);
Handle *fn_8008FCEC(void *set, int a, int b, float f);
char *fn_8009AF80(Ent &actor);
int fn_8044667C(void *axis, void *owner, float v, float w, int mode);
float fn_800B1884(Ent &actor, int id);
void fn_800E6B44(void *self, int v);
void fn_800F0C70(void *self, int a, int b, int c, int d);
int fn_800CD0EC(void *self);
int fn_800CD064(void *self);
int fn_800E0458(void *self);
void fn_8009AEC8(Ent &actor, int v);
void fn_800BD2D0(void *self, int handle);
void fn_800CD77C(void *self);
int fn_800B0C58(void *actor);
Obj *fn_80085954(void *p);
int fn_800CC6DC(EObj &c);
}

extern "C" int fn_800E1788(register Obj *self, int unused, int type, unsigned int value, int extra)
{
    Handle *f18;
    switch (type) {
    case 0x23: {
        if (value == 1)
            f18 = fn_80393D0C(*Entity_GetActor(self), fn_800ACD20(*Entity_GetActor(self), 0xA8), 0x15, 2);
        else
            f18 = fn_80393D0C(*Entity_GetActor(self), fn_800ACD20(*Entity_GetActor(self), 0xA8), 0x15, 1);
        Vector v20;
        fn_8042DC84(&v20, fn_800B1724(*Entity_GetActor(self)));
        fn_8042FE08(&v20, fn_800B1750(*Entity_GetActor(self)), 3.0f);
        v20.z += 10.0f;
        if (f18)
            f18->s28(&v20, 0);
        break;
    }
    case 0x24:
        fn_800D5514(self);
        break;
    case 0x48:
        if (!(self->f10 & 0x1000) && self->f414 != 0.0f) {
            fn_80084A60(Entity_GetActor(self), self->f414);
            self->f10 |= 0x1000;
        }
        break;
    case 0x28:
        self->f10 |= 2;
        if (!fn_800CD7D4(self))
            fn_80065AF8(*Entity_GetActor(self), 0, 0);
        break;
    case 0x5A:
        self->f10 &= ~2;
        if (!fn_800CD7D4(self))
            fn_80065AF8(*Entity_GetActor(self), 1, 0);
        break;
    case 0x2C:
    case 0x2F:
        self->f10 |= 4;
        self->f10 &= ~0x10;
        break;
    case 0x2D:
    case 0x30:
        self->f10 &= ~4;
        fn_800CC578(self, 0, 0);
        break;
    case 0x18:
        if (self->f18 & 0x1000)
            fn_800E8768(self, 0);
        else
            fn_800E8768(self, 2);
        break;
    case 0x39:
        if (self->f18 & 0x1000)
            fn_800E8768(self, 1);
        else
            fn_800E8768(self, 3);
        break;
    case 0x19:
        if (self->f18 & 0x1000)
            fn_800E880C(self, 0);
        else
            fn_800E880C(self, 2);
        break;
    case 0x3A:
        if (self->f18 & 0x1000)
            fn_800E880C(self, 1);
        else
            fn_800E880C(self, 3);
        break;
    case 0x3C:
        fn_800E8768(self, 4);
        break;
    case 0x3D:
        fn_800E880C(self, 4);
        break;
    case 0x3E:
        fn_800E8768(self, 5);
        break;
    case 0x3F:
        fn_800E880C(self, 5);
        break;
    case 0x56:
        fn_800E8768(self, 6);
        break;
    case 0x57:
        fn_800E880C(self, 6);
        break;
    case 0x65:
        if (value)
            fn_800CBE8C(self);
        else
            fn_800CBE1C(self, fn_800C9FD0(self));
        break;
    case 0x40:
        f18 = fn_8008FCEC(fn_8009AE00(*Entity_GetActor(self)), 0x137, 0, -1.0f);
        if (f18) {
            self->f18 |= 0x1000;
            fn_8044667C(fn_8009AF80(*Entity_GetActor(self)) + 0xCC, f18, 0.0f, 30.0f / f18->f28, 1);
        }
        break;
    case 0x41:
        f18 = fn_8008FCEC(fn_8009AE00(*Entity_GetActor(self)), 0x137, 0, -1.0f);
        if (f18) {
            self->f18 &= ~0x1000;
            fn_8044667C(fn_8009AF80(*Entity_GetActor(self)) + 0xCC, f18, 1.0f, 30.0f / f18->f28, 1);
        }
        break;
    case 0x4C:
        self->f3F4 |= value;
        break;
    case 0x4D:
        self->f3F4 &= ~value;
        break;
    case 0x4E:
        self->b409 = (int)value - 1 >= 0 ? ((int)value - 1 <= 3 ? (int)value - 1 : 3) : 0;
        break;
    case 0x4F:
        self->b40B = value;
        if (extra)
            self->b40C = extra;
        else
            self->b40C = 0x15;
        break;
    case 0x50:
        self->b40A = value - 1 <= 3 ? value - 1 : 3;
        break;
    case 0x1C:
        switch (value) {
        case 0:
            self->f400 = 0x27;
            break;
        case 1:
            self->f400 = 0x28;
            break;
        case 2:
            self->f400 = 0x29;
            break;
        case 3:
            self->f400 = 0x2B;
            break;
        case 4:
            self->f400 = 0x2D;
            break;
        case 6:
            self->f400 = 0x2C;
            break;
        case 7:
            self->f400 = 0x2E;
            break;
        case 8:
            self->f400 = 0x37;
            break;
        case 9:
            self->f400 = 0x38;
            break;
        case 10:
            self->f400 = 0x3E;
            break;
        case 11:
            self->f400 = 0x3F;
            break;
        case 12:
            self->f400 = 0x5E;
            break;
        case 13:
            self->f400 = 0x60;
            break;
        case 14:
            self->f400 = 0x62;
            break;
        case 15:
            self->f400 = 0x2A;
            break;
        }
        break;
    case 0x1A:
        switch (value) {
        case 0:
            self->f3FC = 0x69;
            break;
        case 1:
            self->f3FC = 0x6C;
            break;
        case 2:
            self->f3FC = 0x6F;
            break;
        case 3:
            self->f3FC = 0x75;
            break;
        case 4:
            self->f3FC = 0x76;
            break;
        case 5:
            self->f3FC = 0x7F;
            break;
        case 6:
            self->f3FC = 0x84;
            break;
        case 7:
            self->f3FC = 0x72;
            break;
        case 8:
            self->f3FC = 0x73;
            break;
        case 9:
            self->f3FC = 0x7D;
            break;
        case 10:
            self->f3FC = 0x7E;
            break;
        case 11:
            self->f3FC = 0x80;
            break;
        case 12:
            self->f3FC = 0x65;
            break;
        case 13:
            self->f3FC = 0x6A;
            break;
        case 14:
            self->f3FC = 0x6B;
            break;
        case 15:
            self->f3FC = 0x6D;
            break;
        case 16:
            self->f3FC = 0x6E;
            break;
        case 17:
            self->f3FC = 0x70;
            break;
        case 18:
            self->f3FC = 0x71;
            break;
        case 19:
            self->f3FC = 0x66;
            break;
        case 20:
            self->f3FC = 0x67;
            break;
        case 21:
            self->f3FC = 0x68;
            break;
        case 22:
            self->f3FC = 0x81;
            break;
        case 23:
            self->f3FC = 0x82;
            break;
        case 24:
            self->f3FC = 0x83;
            break;
        }
        break;
    case 0x4B:
        self->b408 = value <= 10 ? value : 10;
        break;
    case 0x64:
        self->f3F8 = 0.0f;
        break;
    case 0x1B:
        switch (value) {
        case 0:
            self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x16);
            break;
        case 1:
        default:
            self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x17);
            break;
        case 2:
            self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x18);
            break;
        case 3:
            self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x19);
            break;
        case 4:
            self->f3F8 = fn_800B1884(*Entity_GetActor(self), 0x1A);
            break;
        }
        break;
    case 6:
        self->f404 = (float)value * 0.01f;
        self->f404 = self->f404 >= 0.2f ? (self->f404 <= 10.0f ? self->f404 : 10.0f) : 0.2f;
        break;
    case 5:
        fn_800E6B44(self, 0);
        break;
    case 0x1F:
        fn_800E6B44(self, 1);
        break;
    case 0x20:
        fn_800E6B44(self, 4);
        break;
    case 0x21:
        fn_800E6B44(self, 5);
        break;
    case 4:
        fn_800F0C70(self, 1, 0, 0, 0);
        break;
    case 0x16:
        if (!Entity_GetActor(self)->s57(0.15f)) {
            if ((fn_800CD0EC(self) || fn_800CD064(self)) && fn_800E0458(self))
                break;
            fn_8009AEC8(*Entity_GetActor(self), 0);
            fn_800BD2D0(self, 0);
            self->s5(5);
        }
        break;
    case 0x58:
        self->b3EF = value <= 4 ? value : 4;
        break;
    case 0x12:
        fn_800CD77C(self);
        break;
    case 0x67:
        self->f10 |= 0x10000;
        break;
    case 0x63:
        if (value)
            self->f10 |= 0x2000;
        else
            self->f10 &= ~0x2000;
        break;
    case 0x59:
        f18 = (Handle *)fn_800C9FD0(self);
        if (f18 && fn_800B0C58(f18) && fn_80085954(f18) && fn_800CC6DC(*fn_80085954(f18)) == 0xC) {
            if (value) {
                self->f10 |= 0x400;
                fn_80085954(f18)->f10 |= 2;
            } else {
                self->f10 &= ~0x400;
                fn_80085954(f18)->f10 &= ~2;
            }
        }
        break;
    default:
        return 0;
    }
    return 1;
}
