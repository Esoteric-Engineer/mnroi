// Scene reader file: the .nsd scene reader fn_800A4DF8 and its helpers (docs/story.md row 14).
// Owns .rodata from 0x8048B508 ("CAsyncLoader:Instance", which no code loads).

#define SWAP32(x) (((x) >> 24) | (((x) >> 8) & 0xFF00) | (((x) & 0xFF00) << 8) | ((x) << 24))
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

struct Thing { // 0x1C0 bytes
    char pad[0x1C0];
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
    char pad8[0x8];
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

struct Scene { // 0x1A0 bytes, "Game:Scene:tScene"
    char pad0[0x4];
    unsigned int f4; // +0x4
    char pad8[0x4];
    char name[0x20]; // +0xC
    char f2C[0x20]; // +0x2C
    char f4C[0x20]; // +0x4C
    char pad6C[0x4];
    unsigned int f70; // +0x70
    char pad74[0xC];
    float f80[4]; // +0x80
    float f90; // +0x90
    float f94; // +0x94
    char pad98[0x28];
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
    char pad160[0x10];
    unsigned int f170; // +0x170
    int f174[9]; // +0x174
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
}

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
