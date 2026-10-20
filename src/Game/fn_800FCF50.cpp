// The .NOT template file loader (Misc/Global.not): reads a file's entry names into the template registry; docs/versus.md section 5, row 11.

struct TemplateFile;

typedef struct TemplateEntry
{
    char name[0x20];
    int unk20;
    unsigned int offset; // +0x24, file offset of the entry's body; the file is little-endian
    unsigned int propCount; // +0x28, set by fn_800FD9A0
    void *props;            // +0x2C, propCount * 0x24 bytes
} TemplateEntry;

struct TemplateFile
{
    char name[0x20];
    TemplateEntry *entries; // +0x20
    unsigned int count;     // +0x24
};

#define SWAP32(x) (((x) >> 24) | (((x) >> 8) & 0xFF00) | (((x) & 0xFF00) << 8) | ((x) << 24))

extern "C" {
extern char *strncpy(char *dst, const char *src, unsigned n);
extern char *strlwr(char *s);
extern int fn_801B3FBC(char *name, const char *ext);
extern const TemplateFile *fn_801B48AC(void *registry, char *name);
extern void *fn_801A8368(const char *name, const char *mode, int flags);
extern void fn_801A953C(void *file);
extern int fn_801A8B60(void *dst, int size, int count, void *file);
extern void fn_801A875C(void *file);
extern void *fn_801AD324(int size, const char *tag, int line);
extern void *memset(void *p, int c, unsigned n);
extern void fn_801B4628(void *registry, void *key, void *value);
extern void fn_800FD9A0(TemplateEntry *entry, void *file);

extern char lbl_8048FA44[]; // "NOT"
extern char lbl_8048FA48[]; // "rb"
extern char lbl_8048FA4C[]; // "Game:Templates"
extern int lbl_8066BAE8;
extern TemplateFile *lbl_80565860[0x40];
extern int lbl_8066BAF4;
extern void *lbl_8066BAF0;
extern void *lbl_8066BAE4;

}

extern "C" TemplateFile *fn_800FCF50(const char *name)
{
    unsigned int i;
    void *file;
    unsigned int version;
    unsigned int magic;
    TemplateFile *rec;
    char path[0x80];

    strncpy(path, name, 0x80);
    path[0x7F] = 0;
    fn_801B3FBC(path, lbl_8048FA44);
    rec = (TemplateFile *)fn_801B48AC(lbl_8066BAF0, path);
    if (rec) {
        return rec;
    }

    file = fn_801A8368(path, lbl_8048FA48, 7);
    if (!file) {
        return 0;
    }
    fn_801A953C(file);

    if (fn_801A8B60(&magic, 4, 1, file) != 1) {
        goto err1;
    }
    if (fn_801A8B60(&version, 4, 1, file) != 1) {
        goto err1;
    }
    version = SWAP32(version);
    if (version != 1) {
        goto err3;
    }

    rec = (TemplateFile *)fn_801AD324(0x28, lbl_8048FA4C, 0x180);
    if (!rec) {
        goto err2;
    }
    lbl_8066BAE8 += 0x40;
    memset(rec, 0, 0x28);
    strncpy(rec->name, path, 0x20);
    rec->name[0x1F] = 0;
    if (fn_801A8B60(&rec->count, 4, 1, file) != 1) {
        goto err1;
    }
    rec->count = SWAP32(rec->count);
    if (!rec->count) {
        goto err1;
    }
    rec->entries = (TemplateEntry *)fn_801AD324(rec->count * 0x30, lbl_8048FA4C, 0x197);
    if (!rec->entries) {
        goto err2;
    }
    lbl_8066BAE8 += (rec->count * 0x30 + 0x1F) & ~0x1F;
    memset(rec->entries, 0, rec->count * 0x30);

    for (i = 0; i < rec->count; i++) {
        TemplateEntry *e = rec->entries + i;

        if (fn_801A8B60(e, 1, 0x20, file) != 0x20) {
            goto err1;
        }
        strlwr(e->name);
        if (fn_801A8B60(&e->offset, 4, 1, file) != 1) {
            goto err1;
        }
        e->offset = SWAP32(e->offset);
        fn_801B4628(lbl_8066BAE4, e, e);
    }

    for (i = 0; i < rec->count; i++) {
        unsigned int n;
        char data[0x200];
        TemplateEntry *e = rec->entries + i;

        fn_800FD9A0(e, file);
        fn_801A8B60(&n, 4, 1, file);
        n = SWAP32(n);
        if (n) {
            fn_801A8B60(data, 1, n, file);
        }
    }

    fn_801B4628(lbl_8066BAF0, rec, rec);
    for (i = 0; i <= 0x3F; i++) {
        if (!lbl_80565860[i]) {
            lbl_80565860[i] = rec;
            break;
        }
    }
    fn_801A875C(file);
    lbl_8066BAF4++;
    return rec;

err1:
    goto fail;
err2:
    goto fail;
err3:
    goto fail;
fail:
    if (file) {
        fn_801A875C(file);
    }
    return 0;
}
