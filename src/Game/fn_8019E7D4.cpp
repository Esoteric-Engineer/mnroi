// .ngb animation bundles: record fixup, path, load into a slot; layout in docs/characters.md section 4.

struct NgbTrack {
    char pad00[0x8];
    unsigned keyCount;  // +0x08
    char *keys;         // +0x0C, keyCount * 0xC
};

struct NgbAnim {
    char pad00[0x20];
    unsigned flags;     // +0x20
    int loaded;         // +0x24
    char pad28[0x4];
    unsigned trackCount; // +0x2C
    NgbTrack *tracks;   // +0x30
    char pad34[0x4];
    int unk38;          // +0x38
    unsigned n3C;       // +0x3C
    char *p40;          // +0x40, n3C * 0xC
    unsigned n44;       // +0x44
    char *p48;          // +0x48, n44 * 0x50
    char pad4C[0x4];
};

struct NgbSlot {
    char name[0x20];
    char *data;      // +0x20
    unsigned size;   // +0x24
    int count;       // +0x28
};

extern "C" {
int sprintf(char *dst, const char *fmt, ...);
char *strncpy(char *dst, const char *src, unsigned long n);
int stricmp(const char *a, const char *b);
void fn_801B4094(char *path, const char *ext);
void fn_801B40EC(char *path);
int fn_80465B28(NgbSlot *slot);
int fn_8019EBF8(const char *name, unsigned char slot);
void fn_8019EE28(unsigned char slot);
void fn_801B4628(void *registry, void *key, void *value);
extern void *lbl_8066C584;
unsigned fn_801A8D40(const char *path);
void fn_801AD19C(void *heap);
void fn_801AD1C4(void);
char *fn_801AD37C(unsigned size, const char *file, int line, int align);
void *fn_801A89C0(char *path, unsigned *size, const char *tag, int a, int b);
void fn_801ACBC4(void *dst, void *src, unsigned size);
void fn_801ACC0C(void *p);
extern const char lbl_8049D304[];
extern const char lbl_8049D310[];
extern const char lbl_8049D314[];
extern const char lbl_8049D31C[];
extern const char lbl_8049D330[];
extern NgbSlot lbl_8057DCA0[];
extern NgbSlot lbl_8057DCF8[];
extern NgbSlot lbl_8057DDA8[];
extern void *lbl_8066C578;
extern unsigned lbl_8066C57C;
extern int lbl_8066C580;
extern int lbl_8066C660;
}

extern "C" NgbAnim *fn_8019E7D4(char **cursor)
{
    NgbAnim *anim;
    unsigned i;
    NgbTrack *track;

    anim = (NgbAnim *)*cursor;
    *cursor += sizeof(NgbAnim);
    fn_801B4628(lbl_8066C584, anim, anim);
    if (anim->trackCount) {
        anim->tracks = (NgbTrack *)*cursor;
        *cursor += anim->trackCount * sizeof(NgbTrack);
        for (i = 0; i < anim->trackCount; i++) {
            track = &anim->tracks[i];
            track->keys = *cursor;
            *cursor += track->keyCount * 0xC;
        }
    } else {
        anim->tracks = 0;
    }
    if (anim->n3C) {
        anim->p40 = *cursor;
        *cursor += anim->n3C * 0xC;
    } else {
        anim->p40 = 0;
    }
    anim->unk38 = 0;
    if (anim->n44) {
        anim->p48 = *cursor;
        *cursor += anim->n44 * 0x50;
    } else {
        anim->p48 = 0;
    }
    anim->flags |= 0x110000;
    anim->loaded = 1;
    return anim;
}

extern "C" void fn_8019E9DC(const char *name, char *path)
{
    sprintf(path, lbl_8049D304, name);
    fn_801B4094(path, lbl_8049D310);
}

extern "C" int fn_8019EA38(const char *name, int variant)
{
    char path[0x20];
    int mode;
    int ok;
    char base[0x20];

    fn_8019E9DC(name, path);
    mode = -1;
    if (fn_80465B28(lbl_8057DCF8)) {
        if (stricmp(path, lbl_8057DCF8->name) == 0) {
            return 1;
        }
        if (fn_80465B28(lbl_8057DDA8)) {
            if (stricmp(path, lbl_8057DDA8->name) == 0) {
                return 1;
            }
        } else {
            mode = 6;
        }
    } else {
        mode = 2;
    }
    if (mode == -1) {
        return 0;
    }
    ok = fn_8019EBF8(name, mode);
    strncpy(base, name, 0x20);
    base[0x1F] = 0;
    fn_801B40EC(base);
    if (variant > -1) {
        sprintf(path, lbl_8049D314, base, variant);
        ok = fn_8019EBF8(path, mode + 1) && ok;
    }
    return ok;
}

extern "C" int fn_8019EBF8(const char *name, unsigned char slot)
{
    NgbSlot *s = &lbl_8057DCA0[slot];
    char path[0x80];
    char *cursor;
    unsigned fileSize;
    void *file;
    int i;

    fn_8019E9DC(name, path);
    if (fn_80465B28(s)) {
        fn_8019EE28(slot);
    }
    strncpy(s->name, path, 0x20);
    if (slot == 0) {
        lbl_8066C660 = 1;
    }
    s->size = fn_801A8D40(path);
    if (s->size == 0) {
        return 0;
    }
    fn_801AD19C(lbl_8066C578);
    s->data = fn_801AD37C(s->size, lbl_8049D31C, 0xA15, 0x10);
    fn_801AD1C4();
    fileSize = 0;
    file = fn_801A89C0(path, &fileSize, lbl_8049D330, 2, 0x20);
    fn_801ACBC4(s->data, file, s->size);
    fn_801ACC0C(file);
    lbl_8066C660 = 0;
    if (s->size != 0) {
        i = 0;
        cursor = s->data;
        while (cursor < s->data + s->size) {
            fn_8019E7D4(&cursor);
        }
    }
    lbl_8066C580 += s->count;
    lbl_8066C57C += s->size;
    lbl_8066C660 = 0;
    return 1;
fail_read:
    lbl_8066C660 = 0;
    return 0;
fail_alloc:
    lbl_8066C660 = 0;
    return 0;
}
