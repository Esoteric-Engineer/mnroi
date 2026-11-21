// Scene reader file: the .nsd scene reader fn_800A4DF8 and its helpers (docs/story.md row 14).
// Owns .rodata 0x8048B508-0x8048B678 (opens with "CAsyncLoader:Instance", ends with a header tail; no code loads either) and .ctors 0x8048261C.

#define SWAP32(x) (((x) >> 24) | (((x) >> 8) & 0xFF00) | (((x) & 0xFF00) << 8) | ((x) << 24))
#define SWAP16(x) ((((x) & 0xFF) << 8) | ((unsigned short)(x) >> 8))
#define SWAPF(f) (*(unsigned int *)&(f) = SWAP32(*(unsigned int *)&(f)))

__asm__(".section .rodata\n\t.string \"CAsyncLoader:Instance\"\n\t.balign 4\n\t.long 0\n\t.text");

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

struct Vec4 {
    float v[4];
};

class EntV;

struct Thing { // 0x1C0 bytes
    char pad0[0x12];
    unsigned short f12; // +0x12, entries used in f58
    char pad14[0x44];
    EntV *f58[0x20]; // +0x58
    char padD8[0xE8];
};

struct PlayerStart { // 0x50 bytes, "Game:Scene:tPlayerStart"
    int f0; // +0x0
    int f4; // +0x4
    int f8; // +0x8
    int fC; // +0xC
    float f10[4]; // +0x10
    float f20[4]; // +0x20
    float f30[4]; // +0x30
    float f40[4]; // +0x40
};

struct InterestSpot { // 0x54 bytes, "Game:Scene:tInterestSpot"
    unsigned int f0; // +0x0
    unsigned int f4[0x10]; // +0x4
    unsigned int f44; // +0x44
    float f48; // +0x48
    unsigned int f4C; // +0x4C
    float f50; // +0x50
};

struct Spot3 { // 0x50 bytes
    int f0; // +0x0
    char pad4[0x4C];
};

struct Level {
    char pad0[0x4];
    unsigned int f4; // +0x4, bytes allocated
    char pad8[0x4];
    unsigned int fC; // +0xC, entries in f12C
    int f10; // +0x10
    int f14; // +0x14
    int f18; // +0x18
    char pad1C[0x110];
    Thing *f12C; // +0x12C
    char pad130[0xC];
    PlayerStart *f13C; // +0x13C
    InterestSpot *f140; // +0x140
    Spot3 *f144; // +0x144
};

struct ModelData {
    char pad0[0x9];
    unsigned char f9; // +0x9
};

struct Model {
    ModelData *f0; // +0x0
    unsigned int f4; // +0x4
    char pad8[0xA8];
    void *fB0; // +0xB0
};

struct Scene;
struct ThingFrame;

class EntV {
public:
    char pad0[0x70];
    Scene *f70; // +0x70
    int f74; // +0x74
    char pad78[0xCC];
    unsigned int f144; // +0x144
    ThingFrame *f148; // +0x148
    void *f14C; // +0x14C, the object's script
    char pad150[0x48];
    virtual void v0();
    virtual void v1();
};

struct Sector { // 0x30 bytes, "Game:Scene:Sector"
    char name[0x20]; // +0x0
    float f20; // +0x20
    float f24; // +0x24
    unsigned int f28; // +0x28
    int f2C; // +0x2C
};

struct Scene { // 0x1A0 bytes, "Game:Scene:tScene"
    unsigned int f0; // +0x0, entries in f194
    unsigned int f4; // +0x4
    char pad8[0x4];
    char name[0x20]; // +0xC
    char f2C[0x20]; // +0x2C
    char f4C[0x20]; // +0x4C
    int f6C; // +0x6C
    unsigned int f70; // +0x70
    char pad74[0xC];
    float f80[4]; // +0x80
    float f90; // +0x90
    float f94; // +0x94
    char pad98[0x8];
    float fA0[4]; // +0xA0
    float fB0; // +0xB0
    float fB4; // +0xB4
    float fB8; // +0xB8
    float fBC; // +0xBC
    float fC0; // +0xC0
    unsigned int fC4; // +0xC4
    unsigned int fC8; // +0xC8
    Model *fCC; // +0xCC
    void *fD0; // +0xD0
    char fD4[0x30]; // +0xD4
    float f104[4]; // +0x104
    unsigned int f114; // +0x114
    char f118[0x20]; // +0x118
    unsigned int f138; // +0x138
    char f13C[0x20]; // +0x13C
    unsigned int f15C; // +0x15C
    unsigned int f160; // +0x160
    struct Sector *f164; // +0x164
    unsigned int f168; // +0x168
    char (*f16C)[0x50]; // +0x16C
    unsigned int f170; // +0x170
    int f174[8]; // +0x174
    EntV **f194; // +0x194
    Level *f198; // +0x198
    char pad19C[0x4];
};

class GameFlow
{
public:
    char pad[0x300]; // size is a placeholder; > 8 keeps the instance out of .sdata
    void SetLoadProgress(float progress, int redraw);
};

extern GameFlow lbl_80552920;

extern "C" {
extern int lbl_8066B9C8;
extern int lbl_8066B9CC;
char *strncpy(char *dst, const char *src, unsigned n);
void *memset(void *dst, int c, unsigned n);
void fn_801B4094(char *path, const char *ext);
void *fn_801A8368(const char *path, const char *mode, int flags);
void fn_801A953C(void *file);
int fn_801A8B60(void *buf, int size, int n, void *file);
void *fn_801AC988(int size, const char *tag, int line, int x);
void *fn_801AC9EC(unsigned size, const char *tag, int line, int align, int a, int b);
void fn_801ACC0C(void *p);
int fn_800FCF50(const char *name);
int fn_800A7208(Scene *scene, void *file);
int fn_800A7A0C(Scene *scene, void *file);
int fn_800A82B8(Scene *scene);
void fn_804306D8(Vec4 *out, void *in);
void fn_8042FC74(void *v);
void fn_8042DCC0(void *m);
void fn_8042DC84(void *dst, void *src);
int fn_8004DD38(Level *lv, void *pos);
void fn_8044517C(unsigned int *p);
void fn_801B4038(char *s);
Model *fn_801A1A84(char *name);
void fn_801A5E3C(Model *m, int a);
int fn_8019DB94(Model *m, int v);
void *fn_80198DE4(char *name, int flags);
void fn_8019AB64(void *anim, void *clip, float speed, int flags, float blend);
int fn_80430D90(Scene *scene);
float *fn_8042FB28(Vector *v);
void fn_8044513C(char *dst, Vector *v);
void fn_80220C9C(ModelData *d);
void fn_80033A38(float a, float b);
void fn_801A875C(void *file);
void fn_801A0520();
void fn_800AE398(void *actor, int a, int b);
void fn_800FD4AC(int id);
void fn_8019E364(Model *m);
void fn_801A646C(void *p, int flag);
void fn_8019A51C(void *anim);
void fn_800B3E68(Level *lv, void *rec);
void fn_800B3FD4(Level *lv, void *rec);
void fn_8042FE08(void *a, void *b, float t);
void fn_8021B1A0(void *p, int a, float x, float y, void *q);
extern char lbl_80594E00[];
unsigned int fn_801A8CE0(void *file);
struct Act;
Act *fn_800B1568(void *e);
int fn_800B0D64(void *a);
int fn_800A4D38(void *a);
void *fn_801A2894(int v);
void *fn_801A0FA4(void *file, int flags);
unsigned int *fn_8043D6CC(void *m);
void fn_801A16BC(unsigned int *n);
struct Shape;
Shape *fn_8009AD80(void *a);
void *fn_8009AE00(void *a);
void fn_8008F53C(void *p);
void fn_8009ADAC(void *a, void *s);
void fn_8009AE2C(void *a, int v);
}

struct Act {
    char pad0[0x234];
    void *f234; // +0x234
};

struct Shape {
    char pad0[0xE0];
    int fE0; // +0xE0
};

extern "C" Scene *fn_800A4DF8(const char *name, Level *lv, int a)
{
    void *file;
    unsigned int version;
    unsigned int magic;
    char tname[0x20];
    char path[0x20];
    Scene *scene = 0;
    unsigned int i;
    unsigned int n1;
    unsigned int n2;
    unsigned int n3;

    lbl_8066B9C8 = !a ? lbl_8066B9CC : -1;
    strncpy(path, name, 0x20);
    path[0x1F] = 0;
    fn_801B4094(path, "NSD");
    file = fn_801A8368(path, "rb", 8);
    if (!file) {
        return 0;
    }
    fn_801A953C(file);

    if (!fn_801A8B60(&magic, 4, 1, file)) {
        goto readerr;
    }
    magic = SWAP32(magic);
    if (!fn_801A8B60(&version, 4, 1, file)) {
        goto readerr;
    }
    version = SWAP32(version);
    if (version <= 10) {
        goto fail;
    }

    scene = (Scene *)fn_801AC988(0x1A0, "Game:Scene:tScene", 0xCD, 1);
    if (!scene) {
        goto nomem;
    }
    memset(scene, 0, 0x1A0);
    lv->f4 += 0x1A0;
    scene->f198 = lv;
    strncpy(scene->name, name, 0x20);
    scene->name[0x1F] = 0;
    if (fn_801A8B60(scene->f2C, 1, 0x20, file) != 0x20) {
        goto readerr;
    }
    if (fn_801A8B60(scene->f4C, 1, 0x20, file) != 0x20) {
        goto readerr;
    }
    if (!fn_801A8B60(&scene->f4, 4, 1, file)) {
        goto readerr;
    }
    scene->f4 = SWAP32(scene->f4);
    if (!fn_801A8B60(&scene->f170, 4, 1, file)) {
        goto readerr;
    }
    scene->f170 = SWAP32(scene->f170);
    for (i = 0; i < scene->f170; i++) {
        lbl_80552920.SetLoadProgress((float)i / (float)scene->f170, 1);
        if (fn_801A8B60(tname, 1, 0x20, file) != 0x20) {
            goto readerr;
        }
        scene->f174[i] = fn_800FCF50(tname);
        if (!scene->f174[i]) {
        }
    }
    if (!fn_800A7208(scene, file)) {
    }
    lbl_8066B9CC = lbl_8066B9C8;
    lbl_8066B9C8 = -1;
    if (version == 11) {
        if (!fn_800A7A0C(scene, file)) {
        }
    }

    if (!fn_801A8B60(&n1, 4, 1, file)) {
        goto readerr;
    }
    n1 = SWAP32(n1);
    if (n1) {
        if (lv->f13C) {
            if (lv->f10) {
                lv->f4 -= (lv->f10 * 0x50 + 0x1F) & ~0x1F;
            }
            fn_801ACC0C(lv->f13C);
        }
        lv->f10 = n1;
        lv->f13C = (PlayerStart *)fn_801AC9EC(lv->f10 * 0x50, "Game:Scene:tPlayerStart", 0x11D, 2, 0x10, 0);
        if (!lv->f13C) {
            goto nomem;
        }
        lv->f4 += (lv->f10 * 0x50 + 0x1F) & ~0x1F;
        for (i = 0; i < lv->f10; i++) {
            struct {
                unsigned int f0;
                float f4[3];
                float f10[3];
                float f1C[3];
                float f28[3];
                unsigned int f34;
                unsigned int f38;
            } rec;
            PlayerStart *e;
            Vec4 v0;
            Vec4 v1;
            Vec4 v2;
            Vec4 v3;

            e = lv->f13C + i;
            if (fn_801A8B60(&rec, 0x3C, 1, file) != 1) {
                goto readerr;
            }
            fn_804306D8(&v0, rec.f4);
            fn_804306D8(&v1, rec.f10);
            fn_804306D8(&v2, rec.f1C);
            fn_804306D8(&v3, rec.f28);
            fn_8042FC74(&v0);
            fn_8042FC74(&v1);
            fn_8042FC74(&v2);
            fn_8042FC74(&v3);
            rec.f34 = SWAP32(rec.f34);
            rec.f38 = SWAP32(rec.f38);
            rec.f0 = SWAP32(rec.f0);
            fn_8042DCC0(e->f10);
            fn_8042DC84(e->f10, &v0);
            fn_8042DC84(e->f20, &v1);
            fn_8042DC84(e->f30, &v2);
            fn_8042DC84(e->f40, &v3);
            e->f8 = rec.f38;
            e->f4 = rec.f34;
            e->f0 = fn_8004DD38(lv, e->f40);
        }
    }

    if (version == 11) {
        if (!fn_801A8B60(&n2, 4, 1, file)) {
            goto readerr;
        }
        n2 = SWAP32(n2);
        if (n2) {
            if (lv->f140) {
                if (lv->f14) {
                    lv->f4 -= (lv->f14 * 0x54 + 0x1F) & ~0x1F;
                }
                fn_801ACC0C(lv->f140);
            }
            lv->f14 = n2;
            lv->f140 = (InterestSpot *)fn_801AC988(lv->f14 * 0x54, "Game:Scene:tInterestSpot", 0x15D, 1);
            if (!lv->f140) {
                goto nomem;
            }
            lv->f4 += (lv->f14 * 0x54 + 0x1F) & ~0x1F;
            if (fn_801A8B60(lv->f140, 0x54, lv->f14, file) != lv->f14) {
                goto readerr;
            }
            for (i = 0; i < lv->f14; i++) {
                SWAPF(lv->f140[i].f50);
                lv->f140[i].f4C = SWAP32(lv->f140[i].f4C);
                lv->f140[i].f44 = SWAP32(lv->f140[i].f44);
                lv->f140[i].f0 = SWAP32(lv->f140[i].f0);
                lv->f140[i].f0 = SWAP32(lv->f140[i].f0);
                SWAPF(lv->f140[i].f48);
                fn_8044517C(lv->f140[i].f4);
                lv->f140[i].f0 = (unsigned int)(lv->f12C + lv->f140[i].f0);
            }
        }

        if (!fn_801A8B60(&n3, 4, 1, file)) {
            goto readerr;
        }
        n3 = SWAP32(n3);
        if (n3) {
            if (lv->f144) {
                if (lv->f18) {
                    lv->f4 -= (lv->f18 * 0x50 + 0x1F) & ~0x1F;
                }
                fn_801ACC0C(lv->f144);
            }
            lv->f18 = n3;
            lv->f144 = (Spot3 *)fn_801AC988(lv->f18 * 0x50, "Game:Scene:tPlayerStart", 0x18C, 2);
            if (!lv->f144) {
                goto nomem;
            }
            lv->f4 += (lv->f18 * 0x50 + 0x1F) & ~0x1F;
            if (fn_801A8B60(lv->f144, 0x50, lv->f18, file) != lv->f18) {
                goto readerr;
            }
            for (i = 0; i < lv->f18; i++) {
                lv->f144[i].f0 = (int)(lv->f12C + lv->f144[i].f0);
            }
        }

        fn_801A8B60(scene->f118, 1, 0x20, file);
        fn_801B4038(scene->f118);
        fn_801A8B60(scene->f13C, 1, 0x20, file);
        fn_801B4038(scene->f13C);
        fn_801A8B60(&scene->f114, 4, 1, file);
        fn_801A8B60(&scene->f138, 4, 1, file);
        fn_801A8B60(&scene->f15C, 4, 1, file);
        fn_801A8B60(&scene->fC8, 4, 1, file);
        scene->f114 = SWAP32(scene->f114);
        scene->f138 = SWAP32(scene->f138);
        scene->f15C = SWAP32(scene->f15C);
        scene->fC8 = SWAP32(scene->fC8);
        fn_801A8B60(&scene->f70, 4, 1, file);
        fn_801A8B60(scene->f80, 0x10, 1, file);
        fn_801A8B60(&scene->f90, 4, 1, file);
        fn_801A8B60(&scene->f94, 4, 1, file);
        fn_801A8B60(&scene->fC0, 4, 1, file);
        fn_801A8B60(&scene->fC4, 4, 1, file);
        scene->f70 = SWAP32(scene->f70);
        fn_8042FC74(scene->f80);
        SWAPF(scene->f90);
        SWAPF(scene->f94);
        SWAPF(scene->fC0);
        scene->fC4 = SWAP32(scene->fC4);
        {
            char model[0x20];

            fn_801A8B60(model, 1, 0x20, file);
            if (model[0]) {
                scene->fCC = fn_801A1A84(model);
                if (scene->fCC) {
                    fn_801A5E3C(scene->fCC, 0);
                }
            } else {
                scene->fCC = 0;
            }
            if (scene->fCC) {
                scene->fCC->f4 = scene->fCC->f4 | 2;
                fn_8019DB94(scene->fCC, 0);
                if (model[0] && scene->fCC->f0->f9 > 1) {
                    scene->fD0 = fn_80198DE4(model, 0);
                    if (scene->fD0) {
                        fn_8019AB64(scene->fCC->fB0, scene->fD0, 30.0f, 0, 7.5f);
                    }
                } else {
                    scene->fD0 = 0;
                }
            }
            if (fn_80430D90(scene)) {
                Vector pos;
                Vector rot;

                fn_801A8B60(fn_8042FB28(&pos), 0x10, 1, file);
                fn_801A8B60(fn_8042FB28(&rot), 0x10, 1, file);
                fn_8042FC74(&pos);
                fn_8042FC74(&rot);
                fn_8044513C(scene->fD4, &rot);
                fn_8042DC84(scene->f104, &pos);
            }
        }
    } else {
        Vector va;
        Vector vb;
        Vector vc;
        Vector vd;
        Vector pos;
        Vector rot;
        float unused;
        char model[0x20];
        char anim[0x20];
        char s3[0x20];
        char s4[0x20];
        float fa;
        float fb;

        fn_801A8B60(fn_8042FB28(&vb), 0x10, 1, file);
        fn_8042FC74(&vb);
        fn_801A8B60(fn_8042FB28(&va), 0x10, 1, file);
        fn_8042FC74(&va);
        fn_801A8B60(fn_8042FB28(&vd), 0x10, 1, file);
        fn_8042FC74(&vd);
        fn_801A8B60(fn_8042FB28(&vc), 0x10, 1, file);
        fn_8042FC74(&vc);
        fn_801A8B60(&unused, 4, 1, file);
        SWAPF(unused);
        fn_801A8B60(&scene->fC0, 4, 1, file);
        SWAPF(scene->fC0);
        fn_801A8B60(&scene->f70, 4, 1, file);
        scene->f70 = SWAP32(scene->f70);
        fn_801A8B60(scene->f80, 0x10, 1, file);
        fn_8042FC74(scene->f80);
        fn_801A8B60(&scene->f90, 4, 1, file);
        SWAPF(scene->f90);
        fn_801A8B60(&scene->f94, 4, 1, file);
        SWAPF(scene->f94);
        fn_801A8B60(model, 1, 0x20, file);
        if (model[0]) {
            scene->fCC = fn_801A1A84(model);
            if (scene->fCC) {
                fn_801A5E3C(scene->fCC, 0);
            }
            if (scene->fCC->f0) {
                fn_80220C9C(scene->fCC->f0);
            }
        } else {
            scene->fCC = 0;
        }
        fn_801A8B60(anim, 1, 0x20, file);
        if (scene->fCC) {
            scene->fCC->f4 = scene->fCC->f4 | 2;
            fn_8019DB94(scene->fCC, 0);
            if (scene->fCC->f0->f9 > 1) {
                scene->fD0 = fn_80198DE4(anim, 0);
                if (scene->fD0) {
                    fn_8019AB64(scene->fCC->fB0, scene->fD0, 30.0f, 0, 7.5f);
                }
            } else {
                scene->fD0 = 0;
            }
        }
        fn_801A8B60(fn_8042FB28(&pos), 0x10, 1, file);
        fn_8042FC74(&pos);
        fn_801A8B60(fn_8042FB28(&rot), 0x10, 1, file);
        fn_8042FC74(&rot);
        if (fn_80430D90(scene)) {
            fn_8044513C(scene->fD4, &rot);
            fn_8042DC84(scene->f104, &pos);
        }
        fn_801A8B60(s3, 1, 0x20, file);
        fn_801A8B60(s4, 1, 0x20, file);
        fa = 0.0f;
        fb = -14.0f;
        fn_801A8B60(&fa, 4, 1, file);
        SWAPF(fa);
        fn_801A8B60(&fb, 4, 1, file);
        SWAPF(fb);
        fn_80033A38(fb, fa);
    }

    fn_801A875C(file);
    if (!fn_800A82B8(scene)) {
    }
    fn_801A0520();
    return scene;

readerr:
    goto fail;
nomem:
    goto fail;
fail:
    if (file) {
        fn_801A875C(file);
    }
    return 0;
}

extern "C" void fn_800A6B28(register Scene *self)
{
    unsigned int i;

    for (i = 0; i < self->f0; i++) {
        if (self->f194[i]) {
            fn_800AE398(self->f194[i], 1, 0);
            self->f194[i]->v1();
            self->f194[i] = 0;
        }
    }
    for (i = 0; i < self->f170; i++) {
        if (self->f174[i]) {
            fn_800FD4AC(self->f174[i]);
        }
    }
    if (self->f194) {
        fn_801ACC0C(self->f194);
    }
    if (self->fCC) {
        fn_8019E364(self->fCC);
        fn_801A646C(self->fCC, 1);
    }
    if (self->fD0) {
        fn_8019A51C(self->fD0);
    }
    for (i = 0; i < self->f168; i++) {
        if (self->f198) {
            fn_800B3E68(self->f198, &self->f16C[i]);
        }
    }
    if (self->f16C) {
        fn_801ACC0C(self->f16C);
    }
    for (i = 0; i < self->f160; i++) {
        if (self->f198) {
            fn_800B3FD4(self->f198, &self->f164[i]);
        }
    }
    if (self->f164) {
        fn_801ACC0C(self->f164);
    }
    if (self->f198) {
        self->f198->f4 -= 0x1A0;
        self->f198->f4 -= (self->f0 * 4 + 0x1F) & ~0x1F;
        self->f198->f4 -= (self->f160 * 0x30 + 0x1F) & ~0x1F;
        self->f198->f4 -= (self->f168 * 0x50 + 0x1F) & ~0x1F;
    }
    fn_801ACC0C(self);
}

__asm__(".section .rodata\n\t.float 0.0\n\t.float 1.0\n\t.text"); // 0x8048B590: orphan words no code loads

extern "C" void fn_800A6E58(register Scene *self, float dt)
{
    float t;
    float d;

    if (self->fB8 == 0.0f) {
        return;
    }
    t = self->fB8 - dt * self->fBC;
    t = t > 0.0f ? t : 0.0f;
    d = self->fB8 - t;
    self->fB8 = t;
    if (d != 0.0f) {
        self->f90 += d * self->fB0;
        self->f94 += d * self->fB4;
        fn_8042FE08(self->f80, self->fA0, d);
        fn_8021B1A0(lbl_80594E00, self->f70, self->f90, self->f94, self->f80);
    }
}

extern "C" int fn_800A6F80(void *e, void *file)
{
    int r = fn_801A8CE0(file);
    unsigned int kind;

    fn_801A8B60(&kind, 4, 1, file);
    kind = SWAP32(kind);
    if (!kind) {
        return 1;
    }
    Act *a = fn_800B1568(e);
    int flags = 0;
    if (fn_800B0D64(a) && !fn_800A4D38(a)) {
        flags = 0x30;
    }
    void *s = 0;
    if (lbl_8066B9C8 != -1) {
        s = fn_801A2894(lbl_8066B9C8);
        if (s) {
            void *m = fn_801A0FA4(file, 0x11);
            unsigned int *n = fn_8043D6CC(m);
            *n = *n | 0x800;
            fn_801A646C(m, 1);
            fn_801A16BC(n);
        }
    }
    if (!s) {
        s = fn_801A0FA4(file, flags);
    }
    if ((void *)fn_8009AD80(a) != s) {
        if (fn_8009AD80(a)) {
            fn_801A646C(fn_8009AD80(a), 1);
            if (fn_8009AE00(a)) {
                fn_8008F53C(fn_8009AE00(a));
            }
        }
        fn_8009ADAC(a, s);
        if (fn_8009AD80(a)) {
            fn_8009AE2C(a, 0);
            fn_8009AD80(a)->fE0 = r;
        } else {
            fn_8009ADAC(a, 0);
        }
    }
    if (kind == 2) {
        a->f234 = fn_801A0FA4(file, flags | 0x10);
    }
    return 1;
}

struct Prop {
    unsigned int id;
    union {
        unsigned int i;
        float f;
        float v[3];
    } u; // +0x4
    char pad[0x14];
};

struct PropInfo {
    char name[0x20];
    int kind;
    int type; // +0x24, 0 string, 2 float, 3 int, 4 vector
};

extern "C" {
extern PropInfo lbl_8048E748[];
extern int lbl_8066B598;
int fn_800AFEC0();
EntV *fn_800AC1AC(Prop *props, int n, Level *lv, int a);
void fn_800A89C8(Scene *self, EntV *obj);
void fn_800AF360(EntV *obj, Level *lv, int a);
void fn_800ACDE0(EntV *obj);
int fn_800B0C58(EntV *obj);
void *fn_800B14A0(EntV *obj);
int fn_80085D3C(void *p);
int fn_800B13D8(EntV *obj);
int fn_800A85F8(EntV *obj, void *file);
void fn_8007CABC(EntV *obj, int n, void *file);
int fn_800A87A4(EntV *obj, void *file);
int fn_800A8A30(EntV *obj, void *file);
int fn_800A837C(EntV *obj, void *file);
void fn_800AD480(EntV *obj, int a);
}

extern "C" int fn_800A7208(register Scene *self, void *file)
{
    unsigned int n;
    unsigned int scripts;
    EntV *obj;
    Prop props[0x80];
    unsigned int i;
    int keep = 1;
    unsigned int count;
    unsigned int j;
    unsigned int type;

    if (fn_801A8B60(&count, 4, 1, file) != 1) {
        goto fail;
    }
    count = SWAP32(count);
    if (!count) {
        return 1;
    }
    self->f6C = fn_800AFEC0();
    self->f194 = (EntV **)fn_801AC988(count * 4, "Game:Scene:Objects", 0x3AD, 2);
    memset(self->f194, 0, count * 4);
    self->f198->f4 += (count * 4 + 0x1F) & ~0x1F;
    for (i = 0; i < count; i++) {
        lbl_8066B9C8++;
        if (fn_801A8B60(&n, 4, 1, file) != 1) {
            goto fail;
        }
        n = SWAP32(n);
        if (!n || n > 0x80) {
            goto fail;
        }
        if (fn_801A8B60(props, 0x24, n, file) != n) {
            goto fail;
        }
        for (j = 0; j < n; j++) {
            props[j].id = SWAP32(props[j].id);
            type = lbl_8048E748[props[j].id].type;
            switch (type) {
            case 3:
                props[j].u.i = SWAP32(props[j].u.i);
                break;
            case 2:
                *(unsigned int *)&props[j].u.f = SWAP32(*(unsigned int *)&props[j].u.f);
                break;
            case 4:
                *(unsigned int *)&props[j].u.v[0] = SWAP32(*(unsigned int *)&props[j].u.v[0]);
                *(unsigned int *)&props[j].u.v[1] = SWAP32(*(unsigned int *)&props[j].u.v[1]);
                *(unsigned int *)&props[j].u.v[2] = SWAP32(*(unsigned int *)&props[j].u.v[2]);
                break;
            }
        }
        obj = fn_800AC1AC(props, n, self->f198, 0);
        if (!obj) {
            continue;
        }
        fn_800A89C8(self, obj);
        fn_800AF360(obj, self->f198, 1);
        fn_800ACDE0(obj);
        if (fn_800B0C58(obj) && fn_80085D3C(fn_800B14A0(obj))) {
            lbl_8066B598 = fn_800B13D8(obj);
        }
        if (!fn_800A85F8(obj, file)) {
            goto fail;
        }
        if (fn_801A8B60(&scripts, 4, 1, file) != 1) {
            goto fail;
        }
        scripts = SWAP32(scripts);
        if (scripts) {
            fn_8007CABC(obj, scripts, file);
        }
        if (!fn_800A6F80(obj, file)) {
            goto fail;
        }
        if (!fn_800A87A4(obj, file)) {
            goto fail;
        }
        if (!fn_800A8A30(obj, file)) {
            goto fail;
        }
        if (!fn_800A837C(obj, file)) {
            goto fail;
        }
        if (!keep) {
            obj->v1();
            obj = 0;
        } else {
            fn_800AD480(obj, 0);
        }
    }
    return 1;

fail:
    return 0;
}

class PointSound { // 0x50 bytes, "Game:Scene:tPointSound"
public:
    char name[0x20];
    char pad20[0x30];
    PointSound() __asm__("fn_8044554C");
};

extern "C" {
int strcmp(const char *a, const char *b);
void fn_800A934C(Thing *t, Sector *sec);
}

extern "C" int fn_800A7A0C(register Scene *self, void *file)
{
    unsigned int count = 0;
    PointSound snd;
    Sector *sec;
    int unused;
    struct {
        char name[0x20];
        float f20;
        float f24;
        unsigned int f28;
    } rec;
    unsigned int i;
    unsigned int j;
    unsigned int n;
    Thing *t;
    unsigned int things[0x400];
    int found;
    unsigned int nsec;
    unsigned int k;
    unsigned int m;

    if (fn_801A8B60(&count, 4, 1, file) != 1) {
        goto fail;
    }
    count = SWAP32(count);
    if (!count) {
        return 1;
    }
    if (fn_801A8B60(&self->f160, 4, 1, file) != 1) {
        goto fail;
    }
    self->f160 = SWAP32(self->f160);
    if (self->f160) {
        self->f164 = (Sector *)fn_801AC988(self->f160 * 0x30, "Game:Scene:Sector", 0x475, 1);
        memset(self->f164, 0, self->f160 * 0x30);
        self->f198->f4 += (self->f160 * 0x30 + 0x1F) & ~0x1F;
        nsec = 0;
        for (i = 0; i < self->f160; i++) {
            found = 0;
            if (fn_801A8B60(&rec, 0x2C, 1, file) != 1) {
                goto fail;
            }
            if (fn_801A8B60(&n, 4, 1, file) != 1) {
                goto fail;
            }
            n = SWAP32(n);
            if (n) {
                if (fn_801A8B60(things, 4, n, file) != n) {
                    goto fail;
                }
                for (j = 0; j < n; j++) {
                    things[j] = SWAP32(things[j]);
                }
            }
            fn_801B4038(rec.name);
            for (k = 0; k < nsec; k++) {
                if (!strcmp(self->f164[k].name, rec.name)) {
                    for (m = 0; m < n; m++) {
                        fn_800A934C(&self->f198->f12C[things[m]], &self->f164[k]);
                    }
                    found = 1;
                    break;
                }
            }
            if (!found) {
                sec = self->f164 + nsec++;
                strncpy(sec->name, rec.name, 0x20);
                sec->name[0x1F] = 0;
                sec->f20 = rec.f20;
                sec->f24 = rec.f24;
                sec->f28 = rec.f28;
                sec->f2C = 0;
                SWAPF(sec->f20);
                SWAPF(sec->f24);
                sec->f28 = SWAP32(sec->f28);
                for (j = 0; j < n; j++) {
                    t = self->f198->f12C + things[j];
                    fn_800A934C(t, sec);
                }
            }
        }
        self->f160 = nsec;
    }

    if (fn_801A8B60(&self->f168, 4, 1, file) != 1) {
        goto fail;
    }
    self->f168 = SWAP32(self->f168);
    if (self->f168) {
        self->f16C = (char (*)[0x50])fn_801AC988(self->f168 * 0x50, "Game:Scene:tPointSound", 0x4D3, 1);
        self->f198->f4 += (self->f168 * 0x50 + 0x1F) & ~0x1F;
        m = 0;
        for (i = 0; i < self->f168; i++) {
            if (fn_801A8B60(&snd, 0x50, 1, file) != 1) {
                goto fail;
            }
            if (fn_801A8B60(&n, 4, 1, file) != 1) {
                goto fail;
            }
            n = SWAP32(n);
            if (n) {
                if (fn_801A8B60(things, 4, n, file) != n) {
                    goto fail;
                }
                for (j = 0; j < n; j++) {
                    things[j] = SWAP32(things[j]);
                }
            }
            fn_801B4038(snd.name);
        }
        self->f168 = m;
    }
    return 1;

fail:
    return 0;
}

extern "C" {
void fn_80078E28(void *script, EntV *obj, EntV **objs);
void fn_800AD9A4(EntV *obj);
}

extern "C" int fn_800A82B8(register Scene *self)
{
    unsigned int i;
    EntV *e;

    for (i = 0; i < self->f0; i++) {
        e = self->f194[i];
        if (!e) {
            continue;
        }
        if (e->f14C) {
            fn_80078E28(e->f14C, e, self->f194);
        }
        fn_800AD9A4(e);
    }
    return 1;
}

struct ShapeH {
    ModelData *f0; // +0x0
    unsigned int f4; // +0x4
};

extern "C" {
int fn_800B0F0C(EntV *e);
ShapeH *fn_8009AD80H(void *a) __asm__("fn_8009AD80");
void fn_80222B8C(void *a, int id, void *file);
int fn_8022302C(ShapeH *s, int id, void *file);
int fn_8044551C(ShapeH *s);
ShapeH *fn_8009B134(EntV *e);
int fn_800B0CC0(EntV *e);
void *fn_800B1478(EntV *e);
ShapeH *fn_800A45C8(void *p);
}

extern "C" int fn_800A837C(register EntV *e, register void *file)
{
    unsigned short id;

    if (fn_801A8B60(&id, 2, 1, file) != 1) {
        return 0;
    }
    id = SWAP16(id);
    if (id) {
        if (!fn_800B0F0C(e) || !fn_8009AD80H(fn_800B1568(e))) {
            fn_80222B8C(0, id, file);
        } else if (!fn_8022302C(fn_8009AD80H(fn_800B1568(e)), id, file)) {
            fn_8009AD80H(fn_800B1568(e))->f4 &= ~1;
            fn_80220C9C(fn_8009AD80H(fn_800B1568(e))->f0);
        }
    } else if (fn_800B0F0C(e)) {
        EntV *a = e;

        if (fn_8009AD80H(a)) {
            if (!fn_8044551C(fn_8009AD80H(a))) {
                fn_8009AD80H(a)->f4 &= ~1;
            }
            fn_80220C9C(fn_8009AD80H(a)->f0);
        }
        if (fn_8009B134(a)) {
            fn_80220C9C(fn_8009B134(a)->f0);
        }
        if (fn_800B0CC0(a) && fn_800A45C8(fn_800B1478(a))) {
            fn_80220C9C(fn_800A45C8(fn_800B1478(a))->f0);
        }
    }
    return 1;
}

struct ThingFrame { // 0x30 bytes, "Game:Scene:tThingFrame"
    float f0[4]; // +0x0
    float f10[4]; // +0x10
    unsigned short f20; // +0x20
    char pad22[0xE];
};

extern "C" int fn_800A85F8(register EntV *e, register void *file)
{
    unsigned int i;
    ThingFrame *f;

    if (fn_801A8B60(&e->f144, 4, 1, file) != 1) {
        return 0;
    }
    e->f144 = SWAP32(e->f144);
    if (e->f144) {
        e->f148 = (ThingFrame *)fn_801AC988(e->f144 * 0x30, "Game:Scene:tThingFrame", 0x5B8, 1);
        if (!e->f148) {
            return 0;
        }
        if (fn_801A8B60(e->f148, 0x30, e->f144, file) != e->f144) {
            return 0;
        }
        for (i = 0; i < e->f144; i++) {
            f = e->f148 + i;
            fn_8042FC74(f->f0);
            fn_8042FC74(f->f10);
            f->f20 = SWAP16(f->f20);
        }
    }
    return 1;
}

extern "C" Level *fn_800B1A98(EntV *e);

extern "C" int fn_800A87A4(register EntV *e, register void *file)
{
    unsigned int n;
    unsigned int id;
    unsigned int i;
    Thing *t;
    unsigned int k;

    if (fn_801A8B60(&n, 4, 1, file) != 1) {
        return 0;
    }
    n = SWAP32(n);
    if (!n) {
        return 1;
    }
    for (i = 0; i < n; i++) {
        if (fn_801A8B60(&id, 4, 1, file) != 1) {
            return 0;
        }
        id = SWAP32(id);
        if (id < fn_800B1A98(e)->fC) {
            t = fn_800B1A98(e)->f12C + id;
            for (k = 0; k < 0x20; k++) {
                if (!t->f58[k]) {
                    break;
                }
            }
            if (k < 0x20) {
                t->f58[k] = e;
                t->f12++;
            } else {
            }
        } else {
        }
    }
    return 1;
}

extern "C" void fn_800A89C8(register Scene *self, EntV *obj)
{
    self->f194[self->f0] = obj;
    obj->f70 = self;
    obj->f74 = self->f0;
    self->f0++;
}

struct CamFrame { // 0x60 bytes, "Game:Scene:tCameraFrameData"
    char pad0[0x4];
    unsigned int f4; // +0x4
    float f8; // +0x8
    char padC[0x4];
    float f10[4]; // +0x10
    float f20[4]; // +0x20
    float f30; // +0x30
    char pad34[0x2C];
};

struct CamRegion { // 0x1C bytes, "Game:Scene:tCameraRegionData", the kind-3 object's +0x288
    unsigned int f0; // +0x0
    unsigned int f4; // +0x4
    CamFrame *f8; // +0x8
    unsigned int fC; // +0xC, entries in f8
    float f10; // +0x10
    float f14; // +0x14
    float f18; // +0x18
};

extern "C" int fn_800B0BEC(EntV *e);

extern "C" int fn_800A8A30(register EntV *e, register void *file)
{
    unsigned short has = 0;
    CamRegion **slot;
    CamRegion *r;
    unsigned int i;
    CamFrame *f;

    fn_801A8B60(&has, 2, 1, file);
    has = SWAP16(has);
    if (has != 1) {
        return 1;
    }
    if (fn_800B0BEC(e) == 3) {
        slot = (CamRegion **)((char *)e + 0x288);
    } else {
        return 1;
    }
    *slot = (CamRegion *)fn_801AC988(0x1C, "Game:Scene:tCameraRegionData", 0x63A, 1);
    if (!*slot) {
        return 0;
    }
    r = *slot;
    fn_801A8B60(&r->f0, 4, 1, file);
    r->f0 = SWAP32(r->f0);
    fn_801A8B60(&r->f4, 4, 1, file);
    r->f4 = SWAP32(r->f4);
    if (r->f4 & 0x10000) {
        fn_801A8B60(&r->f10, 4, 1, file);
        SWAPF(r->f10);
        fn_801A8B60(&r->f14, 4, 1, file);
        SWAPF(r->f14);
        fn_801A8B60(&r->f18, 4, 1, file);
        SWAPF(r->f18);
    }
    fn_801A8B60(&r->fC, 4, 1, file);
    r->fC = SWAP32(r->fC);
    if (r->fC) {
        r->f8 = (CamFrame *)fn_801AC988(r->fC * 0x60, "Game:Scene:tCameraFrameData", 0x65A, 1);
        fn_801A8B60(r->f8, 0x60, r->fC, file);
        for (i = 0; i < r->fC; i++) {
            f = r->f8 + i;
            SWAPF(f->f8);
            SWAPF(f->f30);
            f->f4 = SWAP32(f->f4);
            fn_8042FC74(f->f20);
            fn_8042FC74(f->f10);
        }
    } else {
        r->f8 = 0;
    }
    return 1;
}

extern float lbl_8066B9C0, lbl_8066B9C4;
extern float lbl_8066D68C, lbl_8066D690, lbl_8066D694, lbl_8066D698;

// Static initializer: the four .sbss screen-edge floats, as fn_8009A974.
extern "C" void fn_800A8FDC(int init, int priority)
{
    if (priority == 0xFFFF && init) {
        lbl_8066D68C = 320.0f - lbl_8066B9C0 * 0.5f;
        lbl_8066D690 = lbl_8066D68C + lbl_8066B9C0 * 0.5f;
        lbl_8066D694 = 240.0f - lbl_8066B9C4 * 0.5f;
        lbl_8066D698 = lbl_8066B9C4 * 0.5f + lbl_8066D694 - 12.0f;
    } else {
    }
}

extern "C" void fn_800A90B0(void)
{
    fn_800A8FDC(1, 65535);
}

static void (*const sCtorEntry)(void) __attribute__((section(".ctors"))) = fn_800A90B0;

__asm__(".section .rodata\n\t.float 1.0\n\t.float 1.0\n\t.float 1.0\n\t.float 1.2\n\t.float 0.8\n\t.float 2.0\n\t.float 0.5\n\t.float 0.8\n\t.float 0.8\n\t.float 1.0\n\t.float 1.25\n\t.float 0.75\n\t.long 2000\n\t.long 0\n\t.text"); // 0x8048B640-0x8048B678: header tail no code loads
