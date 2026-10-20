// Template entry body loader: reads an entry's property list from a .NOT file.

typedef struct Prop
{
    unsigned int id;
    union {
        unsigned int i;
        float f;
        float v[3];
    } u; // +0x4
    char pad[0x14];
} Prop;

typedef struct PropInfo
{
    char name[0x20];
    int kind;
    int type; // +0x24, 0 string, 2 float, 3 int, 4 vector
} PropInfo;

typedef struct TemplateEntry
{
    char name[0x20];
    int unk20;
    unsigned int offset;
    unsigned int propCount; // +0x28
    Prop *props;   // +0x2C, propCount * 0x24 bytes
} TemplateEntry;

#define SWAP32(x) (((x) >> 24) | (((x) >> 8) & 0xFF00) | (((x) & 0xFF00) << 8) | ((x) << 24))

extern "C" {
extern int fn_801A8B60(void *dst, int size, int count, void *file);
extern void *fn_801AD324(int size, const char *tag, int line);
extern void fn_801ACC44(void *p);

extern char lbl_8048FA4C[]; // "Game:Templates"
extern int lbl_8066BAE8;
extern PropInfo lbl_8048E748[];
}

extern "C" int fn_800FD9A0(TemplateEntry *entry, void *file)
{
    unsigned int i;
    unsigned int type;

    if (fn_801A8B60(&entry->propCount, 4, 1, file) != 1) {
        goto err1;
    }
    entry->propCount = SWAP32(entry->propCount);
    entry->props = (Prop *)fn_801AD324(entry->propCount * 0x24, lbl_8048FA4C, 0x2E3);
    if (!entry->props) {
        goto fail;
    }
    lbl_8066BAE8 += (entry->propCount * 0x24 + 0x1F) & ~0x1F;
    if (fn_801A8B60(entry->props, 0x24, entry->propCount, file) != (int)entry->propCount) {
        goto err1;
    }

    for (i = 0; i < entry->propCount; i++) {
        entry->props[i].id = SWAP32(entry->props[i].id);
        type = lbl_8048E748[entry->props[i].id].type;
        switch (type) {
        case 3:
            entry->props[i].u.i = SWAP32(entry->props[i].u.i);
            break;
        case 2:
            *(unsigned int *)&entry->props[i].u.f = SWAP32(*(unsigned int *)&entry->props[i].u.f);
            break;
        case 4:
            *(unsigned int *)&entry->props[i].u.v[0] = SWAP32(*(unsigned int *)&entry->props[i].u.v[0]);
            *(unsigned int *)&entry->props[i].u.v[1] = SWAP32(*(unsigned int *)&entry->props[i].u.v[1]);
            *(unsigned int *)&entry->props[i].u.v[2] = SWAP32(*(unsigned int *)&entry->props[i].u.v[2]);
            break;
        }
    }
    return 1;

err1:
    goto fail;
fail:
    if (entry->props) {
        fn_801ACC44(entry->props);
    }
    return 0;
}
