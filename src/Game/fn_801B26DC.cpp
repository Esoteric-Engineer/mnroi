// Tuning init: loads Misc/defaults.ndb, the NVB registry and GLOBALS; docs/versus.md row 19, docs/characters.md section 4.

#define SWAP32(x) (((unsigned)(x) >> 24) | (((unsigned)(x) >> 8) & 0xFF00) | (((x) & 0xFF00) << 8) | ((x) << 24))

struct NdbField
{
    int type;                // +0x0
    char pad[0x1C];
    unsigned int *data;      // +0x20
};

struct NdbClass
{
    char pad[0x40];
    int nfields; // +0x40
    char pad2[8];
    int fileSize; // +0x4C
};

extern "C" {
extern char lbl_8049E4E8[]; // "defaults.ndb"
extern char lbl_8049E4F8[]; // "rb"
extern char lbl_8049E4FC[]; // "externals"
extern char lbl_8049E508[]; // "GLOBALS"
extern char lbl_8049E510[]; // "Globals"
extern char lbl_80593CF0[]; // pool
extern int lbl_8066C6CC;
extern void *lbl_8066C6D0;  // the NVB registry
extern void *lbl_8066C6C8;  // the GLOBALS record
extern void *fn_801A8368(char *name, char *mode, int flags);
extern void fn_801A953C(void *file);
extern int fn_801A8B60(void *dst, int size, int nclasses, void *file);
extern void fn_801A875C(void *file);
extern void fn_801B3168(void *pool, int size);
extern unsigned int *fn_801B31E4(void *pool, int size);
extern void fn_801B33EC(NdbClass *cls, char *name, int a, int b);
extern NdbField *fn_801B346C(NdbClass *cls, int idx);
extern void fn_801B2674(NdbClass *cls);
extern void fn_8042FC74(unsigned int *elem);
extern void fn_801B3C4C(void);
extern void *fn_801B4284(int size, char *tag);
extern void *fn_801B301C(char *a, char *b);
}

extern "C" int fn_801B26DC(void)
{
    void *file;
    int magic;
    int version;
    int fileSize;
    int nclasses;
    int i;
    char name[0x40];
    int a;
    int b;
    NdbClass *cls;
    int j;
    NdbField *fld;
    int size;

    lbl_8066C6CC = 0;
    file = fn_801A8368(lbl_8049E4E8, lbl_8049E4F8, 9);
    if (file == 0) {
        return 0;
    }
    fn_801A953C(file);
    fn_801A8B60(&magic, 1, 4, file);
    magic = SWAP32(magic);
    fn_801A8B60(&version, 1, 4, file);
    version = SWAP32(version);
    if (version != 0x10001) {
    }
    fn_801A8B60(&fileSize, 1, 4, file);
    fileSize = SWAP32(fileSize);
    fn_801A8B60(&nclasses, 1, 4, file);
    nclasses = SWAP32(nclasses);
    fn_801B3168(lbl_80593CF0, fileSize * 2 * nclasses);
    for (i = 0; i < nclasses; i++) {
        fn_801A8B60(name, 1, 0x40, file);
        fn_801A8B60(&a, 1, 4, file);
        a = SWAP32(a);
        fn_801A8B60(&b, 1, 4, file);
        b = SWAP32(b);
        cls = (NdbClass *)fn_801B31E4(lbl_80593CF0, 0x50);
        fn_801B33EC(cls, name, a, b);
        cls->fileSize = fileSize;
        for (j = 0; j < cls->nfields; j++) {
            fld = fn_801B346C(cls, j);
            fn_801A8B60(fld, 1, 4, file);
            fld->type = SWAP32(fld->type);
            switch (fld->type) {
            case -0x2775:
                fn_801A8B60(&size, 1, 4, file);
                size = SWAP32(size);
                fld->data = fn_801B31E4(lbl_80593CF0, size);
                fn_801A8B60(fld->data, 1, size, file);
                *fld->data = SWAP32(*fld->data);
                break;
            case -0x2776:
                fn_801A8B60(&size, 1, 4, file);
                size = SWAP32(size);
                fld->data = fn_801B31E4(lbl_80593CF0, size);
                fn_801A8B60(fld->data, 1, size, file);
                *fld->data = SWAP32(*fld->data);
                break;
            case -0x277C:
            case -0x277B:
            case -0x2777:
                fn_801A8B60(&size, 1, 4, file);
                size = SWAP32(size);
                fld->data = fn_801B31E4(lbl_80593CF0, size);
                fn_801A8B60(fld->data, 1, size, file);
                break;
            case -0x2778:
                fld->data = fn_801B31E4(lbl_80593CF0, 4);
                fn_801A8B60(fld->data, 1, 4, file);
                *fld->data = SWAP32(*fld->data);
                break;
            case -0x2779:
                fld->data = fn_801B31E4(lbl_80593CF0, 0x10);
                fn_801A8B60(fld->data, 1, 0x10, file);
                fn_8042FC74(fld->data);
                break;
            case -0x277A:
                fn_801A8B60(&size, 1, 4, file);
                size = SWAP32(size);
                fld->data = fn_801B31E4(lbl_80593CF0, size);
                fn_801A8B60(fld->data, 1, size, file);
                *fld->data = SWAP32(*fld->data);
                break;
            default:
                break;
            }
        }
        fn_801B2674(cls);
    }
    fn_801A875C(file);
    lbl_8066C6D0 = fn_801B4284(0x20, lbl_8049E4FC);
    fn_801B3C4C();
    lbl_8066C6C8 = fn_801B301C(lbl_8049E508, lbl_8049E510);
    return 1;
}
