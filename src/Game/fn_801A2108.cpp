// Reads Bundles/<name>.ngm into model-bundle slot `slot`, building each model it holds; docs/characters.md section 4.

struct ModelBundle {
    char name[0x20];
    void *data;          // +0x20
    unsigned int size;   // +0x24
    unsigned int count;  // +0x28
    void *entries;       // +0x2C, 8 bytes each
    unsigned int nEntries; // +0x30
    int nUsed;           // +0x34
};

struct Model {
    char pad0[0x8C];
    char name[0xAC - 0x8C]; // +0x8C
    int memSize;            // +0xAC, summed into lbl_8066C5BC (name a guess)
};

extern "C" {
char *strncpy(char *dst, const char *src, unsigned n);
void *memset(void *dst, int c, unsigned n);
void fn_801B4094(char *path, const char *ext);
int fn_804660DC(ModelBundle *bundle);
void fn_801A2588(unsigned char slot);
void *fn_801A8368(const char *path, const char *mode, int flags);
void fn_801A953C(void *file);
int fn_801A8B60(void *dst, int size, int count, void *file);
void fn_801A875C(void *file);
void *fn_801AC988(unsigned size, const char *tag, int line, int align);
void *fn_801AD324(unsigned size, const char *tag, int line);
Model *fn_801A3ECC(char **cursor, unsigned char a, unsigned char b, unsigned char c, unsigned short d);
int fn_80221C08(Model *model, void *file, ModelBundle *bundle);
void fn_801B4628(void *registry, const char *name, void *item);
void fn_801A27D4(ModelBundle *bundle, int index, Model *model);
void fn_8023E98C(void);
extern const char lbl_8049D44C[];
extern const char lbl_8049D49C[];
extern const char lbl_8049D4A0[];
extern const char lbl_8049D4BC[];
extern ModelBundle lbl_8057E110[];
extern int lbl_8066C660;
extern void *lbl_8066C5CC;
extern int lbl_8066C5C0;
extern int lbl_8066C5BC;
}

extern "C" int fn_801A2108(const char *name, unsigned char slot)
{
    ModelBundle *bundle;
    int unused;
    char path[0x20];
    void *file;
    unsigned int i;
    int version;
    char *cursor;
    Model *model;
    unsigned char b4c;
    unsigned char b4d;
    unsigned char b4e;
    unsigned short u50;
    int index;
    int skip;

    if (slot == 0)
        lbl_8066C660 = 1;
    bundle = &lbl_8057E110[slot];
    strncpy(path, name, 0x20);
    fn_801B4094(path, lbl_8049D49C);
    if (fn_804660DC(bundle))
        fn_801A2588(slot);
    strncpy(bundle->name, path, 0x20);
    bundle->count = 0;
    file = fn_801A8368(path, lbl_8049D44C, 0x21);
    if (file == 0) {
        lbl_8066C660 = 0;
        return 0;
    }
    fn_801A953C(file);
    version = 0;
    if (!fn_801A8B60(&version, 4, 1, file))
        goto readError;
    if (version != 5)
        goto badVersion;
    fn_801A8B60(&skip, 4, 1, file);
    fn_801A8B60(&skip, 4, 1, file);
    fn_801A8B60(&bundle->count, 4, 1, file);
    fn_801A8B60(&bundle->nEntries, 4, 1, file);
    if (bundle->nEntries) {
        bundle->entries = fn_801AC988(bundle->nEntries * 8, lbl_8049D4A0, 0x51F, 2);
        bundle->nUsed = 0;
    }
    fn_801A8B60(&bundle->size, 4, 1, file);
    if (bundle->size == 0)
        goto done;
    bundle->data = fn_801AD324(bundle->size, lbl_8049D4BC, 0x52B);
    if (bundle->data == 0)
        goto noMemory;
    memset(bundle->data, 0, bundle->size);
    cursor = (char *)bundle->data;
    for (i = 0; i < bundle->count; i++) {
        fn_801A8B60(&index, 4, 1, file);
        fn_801A8B60(&b4d, 1, 1, file);
        fn_801A8B60(&b4c, 1, 1, file);
        fn_801A8B60(&b4e, 1, 1, file);
        fn_801A8B60(&u50, 2, 1, file);
        model = fn_801A3ECC(&cursor, b4c, b4e, b4d, u50);
        if (!fn_80221C08(model, file, bundle))
            goto readError;
        fn_801B4628(lbl_8066C5CC, model->name, model);
        if (index != -1)
            fn_801A27D4(bundle, index, model);
        lbl_8066C5C0++;
        lbl_8066C5BC += model->memSize;
        fn_8023E98C();
    }
done:
    lbl_8066C660 = 0;
    fn_801A875C(file);
    return 1;
readError:
    lbl_8066C660 = 0;
    fn_801A875C(file);
    return 0;
noMemory:
    lbl_8066C660 = 0;
    fn_801A875C(file);
    return 0;
badVersion:
    lbl_8066C660 = 0;
    if (file)
        fn_801A875C(file);
    return 0;
}
