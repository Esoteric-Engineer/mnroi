// Attachment spawner (guess): spawns entities from the actor's 0x5C-byte attachment records. Type-ID use: docs/characters.md section 3.
// The unit owns the "prp_propbust" string and its float pool.

inline int sn_return_decl(int a) { return a; }

struct Rec5C {
    int kind;
    char pad4[0x44];
    unsigned char f48; // +0x48
    char pad49[0x13];
};

struct Info {
    char pad0[4];
    unsigned char kind; // +0x4
    char pad5[0x13];
    Rec5C *recs; // +0x18
    char pad1C[0x70];
    char sub[1]; // +0x8C
};

struct Model {
    Info *info;
};

struct Actor {
    char pad0[0x2C];
    unsigned int flags; // +0x2C
    char pad30[0x18C];
    Model *model; // +0x1BC
    char pad1C0[0xD0];
    unsigned int f290; // +0x290
    char pad294[0x28];
    unsigned int f2BC; // +0x2BC
    unsigned short f2C0;
    unsigned short f2C2;
    Info **f2C4; // +0x2C4
};

struct Event {
    int kind; // +0x0
    void *f4;
    int f8;
    char padC[4];
    int f10; // +0x10
    char pad14[0x34];
    int f48; // +0x48
    int f4C;
    int f50;
    char pad54[0xC];
};

extern int lbl_8066B9FC;

extern "C" {
int fn_800A4568(void *self);
int fn_800A4598(void *self);
int fn_80436964(void);
char *fn_8043E204(char *self);
void *fn_800B24AC(void *self);
int fn_800B13D8(void *self);
void fn_8006C304(void *ev);
void fn_80434988(void *self);
void ExtentCtor(void *self) __asm__("__6Extent");
void *fn_8007766C(void *a, int b, int c, short d);
void fn_800695B4(void *self, void *bank, int a, int b);
unsigned short fn_80441628(void *self);
void *fn_80441674(void *self, int i);
int fn_804415C8(void *h);
int fn_804415F8(void *h);
int fn_802365D8(int v);
int fn_80236608(int v);
int fn_800A21FC(int v);
int fn_800FD5FC(char *name, int flag);
void fn_80078068(void *h, void *ext, float f);
void *fn_8043D544(void *h);
void *fn_8043B80C(void *model, int i);
void *fn_80064A68(int info, void *self, void *group, unsigned char i, void *p, int a, void *ext, int b, int c, int d, int e);
int fn_80236660(int v);
int fn_80236690(int v);
int fn_80236804(int v);
void fn_8009AB94(void *self, int v);
void fn_8009AC40(void *self, int v);
void fn_8009AC18(void *self, int v);
int fn_8009ABEC(void *self);
int fn_8009ABC0(void *self);
int fn_800B1D78(void *self);
int fn_800664C0(void *self);
void *fn_80318EB4(void *p);
void *fn_80318E84(void *p);
void fn_8043632C(void *dst, void *src);
void fn_804349B0(void *out, void *a, void *b);
float *fn_80438360(void *self, int i);
void fn_80436610(void *self);
void fn_804364BC(void *self, float s, void *v);
void fn_80319074(void *a, void *q);
void fn_80066794(void *self, int v);
void fn_800A20A4(void *self, int v);
void fn_80393894(void *self);
void fn_8043B244(void *model, unsigned int bit);
void fn_800A29C8(void *self, unsigned char type, int a);
void fn_8007FC00(void *self, int a, int b, int c);
}

extern "C" void fn_800A22CC(register Actor *self, unsigned char type, int a, int b, int c, int d)
{
    int saved = lbl_8066B9FC;
    if (!fn_800A4568(self))
        return;
    if (a && !fn_800A4598(self))
        return;
    if (fn_80436964()) {
        Event ev;
        fn_8043E204((char *)&ev);
        ev.kind = 10;
        ev.f4 = fn_800B24AC(self);
        ev.f8 = fn_800B13D8(self);
        ev.f10 = type;
        ev.f48 = a;
        ev.f4C = b;
        ev.f50 = c;
        fn_8006C304(&ev);
        return;
    }
    Info *info = self->f2C4 ? *self->f2C4 : self->model->info;
    char v1[0x10];
    char v2[0x10];
    void *child;
    unsigned short i;
    char ext[0x50];
    void *obj;
    void *h;
    Rec5C *rec;
    int tmpl;
    unsigned char want;
    fn_80434988(v1);
    fn_80434988(v2);
    ExtentCtor(ext);
    if (info == 0 || info->kind == 1)
        return;
    if (type == 12 && fn_800A4598(self))
        fn_800A22CC(self, 0, 1, 0, 0, 0);
    if (a)
        type = 22;
    obj = fn_8007766C(info->sub, 0, 0, 0x40);
    if (a)
        fn_800695B4(self, obj, 22, 0);
    else
        fn_800695B4(self, obj, type, 0);
    if (!d) {
        want = a ? 9 : 8;
        for (i = 0; i < fn_80441628(obj); i++) {
            h = fn_80441674(obj, i);
            if (fn_804415C8(h) != want)
                continue;
            rec = &info->recs[fn_804415F8(h)];
            if (fn_802365D8(rec->kind) != type)
                continue;
            tmpl = fn_80236608(rec->kind);
            if (c && !fn_800A21FC(tmpl))
                continue;
            if (!tmpl)
                tmpl = fn_800FD5FC("prp_propbust", 0);
            fn_80078068(h, ext, 1.0f);
            child = fn_80064A68(tmpl, self, info, (unsigned char)fn_804415F8(h), fn_8043D544(h), (int)fn_8043B80C(self->model, rec->f48), ext, 1, 0, 1, 1);
            fn_8009AB94(child, fn_80236660(rec->kind));
            if (fn_80236690(rec->kind) != 400) {
                fn_8009AC40(child, fn_80236690(rec->kind));
                fn_8009AC18(child, fn_80236804(rec->kind));
            } else if (fn_8009ABEC(child) == 400) {
                fn_8009AC40(child, fn_8009ABEC(self));
                fn_8009AC18(child, fn_8009ABC0(self));
            }
            if (!fn_800B1D78(child) && !fn_800664C0(child) && fn_800B24AC(self)) {
                fn_8043632C(v1, fn_80318EB4(fn_800B24AC(self)));
                fn_804349B0(v2, fn_80318E84(fn_800B24AC(child)), fn_80318E84(fn_800B24AC(self)));
                *fn_80438360(v2, 2) = *fn_80438360(v2, 2) < 0.1f ? *fn_80438360(v2, 2) : 0.1f;
                fn_80436610(v2);
                fn_804364BC(v1, 5.0f, v2);
                fn_80319074(fn_800B24AC(child), v1);
                fn_80066794(child, 1);
            }
        }
    }
    fn_800A20A4(self, 1);
    fn_80393894(self);
    fn_8043B244(self->model, type);
    if (!b)
        fn_800A29C8(self, type, a);
    if (a) {
        self->f290 &= ~0x10000000;
        self->flags &= ~0x40;
        fn_8007FC00(self, 1, 0, self->f2C2);
    } else {
        self->f2BC &= ~(1 << type);
        self->f2C0--;
        fn_8007FC00(self, 0, type - 12, self->f2C2);
    }
}
