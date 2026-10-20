// Material lookup by part name: the cache, then `<name>.nas`, then a texture of that name, then "dflt". docs/characters.md section 4.

typedef struct VEntry
{
    short delta;
    short index;
    void *pfn; // +0x4
} VEntry;

typedef struct Material
{
    char pad0[0x28];
    char name[0x30]; // +0x28 registry key
    VEntry *vptr;    // +0x58
} Material;

extern void *lbl_8066C84C; // material registry
extern int lbl_8066C85C;   // skips the .nas files
extern void *lbl_8066C860; // log file

// Literals still owned by the auto-generated .rodata.
extern char lbl_804A333C[]; // "nas"
extern char lbl_804A3340[]; // "rb"
extern char lbl_804A3344[]; // "%s\n"
extern char lbl_804A3348[]; // "dflt"

char *strncpy(char *dst, const char *src, unsigned long n);
int strcmp(const char *a, const char *b);
void fn_801A8E54(void *file, const char *fmt, ...);
void fn_801A9334(void *file);
void fn_801B4094(char *path, const char *ext);
void *fn_801A8368(const char *path, const char *mode, int flags);
void fn_801A875C(void *file);
void fn_801B4628(void *registry, void *key, void *value);
Material *fn_80234BC4(const char *name);
Material *fn_80234F44(void *file, const char *name);
Material *fn_80235820(const char *name);
void fn_802366BC(Material *m, const char *name);
void fn_80236860(Material *m);
int fn_802368FC(Material *m);

Material *fn_80234628(char *name, int keep)
{
    Material *m;
    void *file;
    char path[0x80];

    m = fn_80234BC4(name);
    if (m != 0) {
        if (lbl_8066C860 != 0 && fn_802368FC(m) == 0) {
            fn_801A8E54(lbl_8066C860, lbl_804A3344, name);
            fn_801A9334(lbl_8066C860);
        }
        if ((keep ^ 1) & 1) {
            fn_80236860(m);
        }
        return m;
    }
    if (lbl_8066C85C == 0) {
        strncpy(path, name, 0x20);
        path[0x1F] = 0;
        fn_801B4094(path, lbl_804A333C);
        file = fn_801A8368(path, lbl_804A3340, 1);
        if (file != 0) {
            m = fn_80234F44(file, name);
            if (m != 0) {
                fn_802366BC(m, name);
                fn_801B4628(lbl_8066C84C, m->name, m);
                if ((keep ^ 1) & 1) {
                    fn_80236860(m);
                }
                fn_801A875C(file);
                return m;
            } else {
                fn_801A875C(file);
            }
        }
    }
    m = fn_80235820(name);
    if (m != 0) {
        fn_802366BC(m, name);
        fn_801B4628(lbl_8066C84C, m->name, m);
        if ((keep ^ 1) & 1) {
            fn_80236860(m);
        }
        return m;
    }
    if (strcmp(name, lbl_804A3348) != 0) {
        return fn_80234628(lbl_804A3348, 0);
    }
    if (m != 0) {
        register VEntry *e = m->vptr + 1;
        ((void (*)(void *, int))e->pfn)((char *)m + e->delta, 3);
    } else {
    }
    return 0;
}
