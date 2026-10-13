// Common-property handler (kind 0) of the entity template dispatcher; property ids in docs/characters.md section 3.
// The unit owns the "Game:Objects" literal at 0x8048BA10 and the 0.0f pool after it.

struct Prop {
    unsigned int id;
    union {
        int i;
        float f;
        char s[0x20];
    } v;
};

struct Vec4 {
    float x, y, z, w;
};

struct Scene {
    char pad0[0xC];
    unsigned int count; // +0xC
    char pad1[0x11C];
    char *records; // +0x12C, 0x1C0-byte records
};

struct Ent {
    char pad0[1];
    unsigned char f1; // +0x1
    char pad1[0x26];
    int f28; // +0x28
    int f2C;
    int f30;
    char pad2[0xC];
    int f40; // +0x40
    float f44;
    float f48;
    float f4C;
    char pad3[0x28];
    char vec78[0x10]; // +0x78
    char pad4[0x74];
    char name[0x1F]; // +0xFC
    char term; // +0x11B
    char pad5[0x40];
    void *f15C; // +0x15C
    char f160;
    char pad6[3];
    float f164; // +0x164
    char pad7[0xC];
    int f174; // +0x174
    char pad8[0xC8];
    int f240; // +0x240
    int f244;
    char pad9[0x64];
    int f2AC; // +0x2AC
    int f2B0;
    char pad10[0x98];
    int f34C; // +0x34C
};

extern char lbl_80593BE8[];
extern char lbl_8064AA80[];

extern "C" {
char *strncpy(char *d, const char *s, unsigned int n);
void fn_804306D8(Vec4 *out, int *in);
void fn_8044513C(char *dst, Vec4 *v);
void fn_80445BF8(char *dst, Vec4 *v);
int fn_800AECF4(Ent *self, char *rec, int flag);
int fn_8042EFF8(char *g);
int fn_801A0814(int *s, int n);
void *fn_800B11C8(Ent *self);
void *fn_801AC988(int size, const char *tag, int line, int flags);
void fn_800B1D20(Ent *self);
void fn_800AFCA0(Ent *self);
void fn_800AFCD0(Ent *self);
int fn_800B0BEC(Ent *self);
int fn_800B0C58(Ent *self);
int fn_800FD5FC(int *name, int flag);
void *fn_803A20D8(char *tbl, int *name, Ent *self, int a, int b, int c, int d, float f);
void fn_8039CE18(void *p, int v);
void fn_80393938(Ent *self, void *p, int v);
int fn_80234628(int *name, int v);
}

extern "C" int fn_800AE534(register Ent *self, Prop *prop, Scene *scene)
{
    switch (prop->id) {
    case 1: {
        Vec4 v;
        fn_804306D8(&v, &prop->v.i);
        fn_8044513C(self->vec78, &v);
        break;
    }
    case 2: {
        Vec4 v;
        fn_804306D8(&v, &prop->v.i);
        fn_80445BF8(self->vec78, &v);
        break;
    }
    case 3: {
        unsigned int idx = prop->v.i;
        if (idx >= scene->count)
            return 0;
        return fn_800AECF4(self, scene->records + idx * 0x1C0, 1);
    }
    case 4:
        if (prop->v.i)
            self->f28 = fn_8042EFF8(lbl_80593BE8) + prop->v.i;
        break;
    case 0xF:
        self->f174 = fn_801A0814(&prop->v.i, 0x10);
        break;
    case 0x1F:
        self->f2C = prop->v.i;
        if (fn_800B11C8(self)) {
            self->f15C = fn_801AC988(0xF, "Game:Objects", 0x56B, 1);
            self->f160 = 0;
        }
        break;
    case 0x20:
        self->f30 = prop->v.i;
        break;
    case 7:
        if (prop->v.i < 0 ? 1 : prop->v.i > 0xB)
            return 0;
        self->f40 = prop->v.i;
        break;
    case 8:
        if (prop->v.f < 0.0f)
            return 0;
        self->f44 = prop->v.f;
        break;
    case 9:
        if (prop->v.f < 0.0f)
            return 0;
        self->f4C = prop->v.f;
        break;
    case 0x21:
        if (prop->v.f <= 0.0f || self->f1 != 1)
            return 0;
        break;
    case 5:
        break;
    case 6:
        switch (prop->v.i) {
        case 0:
            fn_800B1D20(self);
            break;
        case 3:
            fn_800AFCA0(self);
            break;
        case 1:
            self->f1 = 1;
            break;
        case 2:
            fn_800AFCD0(self);
            break;
        case 4:
            self->f1 = 4;
            break;
        default:
            return 0;
        }
        break;
    case 0x1A ... 0x1E:
        break;
    case 0x15:
        strncpy(self->name, (char *)&prop->v.i, 0x20);
        self->term = 0;
        break;
    case 0x67: {
        Ent *e = self;
        if (fn_800B0BEC(self) != 3)
            return 0;
        e->f240 = prop->v.i;
        return 1;
    }
    case 0x76: {
        Ent *e = self;
        if (fn_800B0BEC(self) != 3)
            return 0;
        e->f244 = prop->v.i;
        return 1;
    }
    case 0x22:
        if (fn_800B0C58(self)) {
            Ent *e = self;
            e->f34C = fn_800FD5FC(&prop->v.i, 0);
        } else if (fn_800B0BEC(self) == 8) {
            Ent *e = self;
            e->f2B0 = fn_800FD5FC(&prop->v.i, 0);
        } else
            return 0;
        break;
    case 0x28 ... 0x2B: {
        void *c = fn_803A20D8(lbl_8064AA80, &prop->v.i, self, 0, 0, 0, 0, 0.0f);
        if (c) {
            fn_8039CE18(c, 1);
            fn_80393938(self, c, 0);
        }
        break;
    }
    case 0x25:
        self->f48 = prop->v.f < 0.0f ? 0.0f : prop->v.f;
        break;
    case 0x26:
        if (fn_800B0BEC(self) == 4) {
            Ent *e = self;
            e->f2AC = fn_80234628(&prop->v.i, 0);
            if (e->f2AC == 0) {
            }
        }
        break;
    case 0x74:
        self->f164 = prop->v.f;
        break;
    default:
        return 0;
    }
    return 1;
}
