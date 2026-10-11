// Actor-class template property handler (kind 15); property ids and effects are in docs/characters.md section 3.
struct Prop {
    unsigned int id;
    union {
        int i;
        float f;
        char s[0x20];
    } v;
};

struct Model {
    int unk0;
    int flags; // +0x4
};

struct Actor {
    char pad0[0x1A0];
    int f1A0; // +0x1A0
    int f1A4;
    int f1A8;
    int f1AC;
    char pad1[0xC];
    Model *model; // +0x1BC
    void *f1C0;
    char pad2[0xC];
    char vec[0x10]; // +0x1D0
    char pad3[0x20];
    int f200; // +0x200
    char pad4[4];
    int f208;
    int f20C;
    int f210;
    float f214;
    char pad5[0x14];
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
        self->f1C0 = m;
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
