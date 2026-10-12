// Registry constructor (chained hash table header); docs/characters.md section 3.

typedef struct Registry
{
    char name[0x20];
    int count;       // +0x20
    int bucketCount; // +0x24
    void **buckets;  // +0x28
} Registry;

extern void *fn_801AD324(int size, char *tag, int line);
extern void *memset(void *dst, int c, unsigned n);
extern char *strncpy(char *dst, const char *src, unsigned n);
extern int fn_801B4DB4(int hint);
extern void fn_801B4454(int n);
extern char lbl_8049E560[]; // allocation tag
extern int lbl_8066C6D8;
extern int lbl_8066C6E0;

Registry *fn_801B4284(int hint, char *name)
{
    Registry *reg;

    reg = fn_801AD324(0x2C, lbl_8049E560, 0x5B);
    if (reg == 0) {
        return 0;
    }
    lbl_8066C6D8 += 0x2C;
    memset(reg, 0, 0x2C);
    reg->bucketCount = fn_801B4DB4(hint);
    reg->buckets = fn_801AD324(reg->bucketCount * 4, lbl_8049E560, 0x68);
    if (reg->buckets == 0) {
        return 0;
    }
    memset(reg->buckets, 0, reg->bucketCount * 4);
    lbl_8066C6D8 += reg->bucketCount * 4;
    strncpy(reg->name, name, 0x20);
    reg->name[0x1F] = 0;
    if (lbl_8066C6E0 == 0) {
        fn_801B4454(0x2000);
    }
    return reg;
}
