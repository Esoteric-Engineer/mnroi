// Registry constructor (chained hash table header) and the 0x14-byte node pool behind it (grow, take); docs/characters.md section 3.

typedef struct Node
{
    struct Node *next; // +0x00
    char pad4[0x10];
} Node;

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
extern int lbl_8066C6E0; // nodes on the free list
extern int lbl_8066C6DC; // nodes ever allocated
extern struct Node *lbl_8066C6E4; // the free list
extern void fn_804673E0(void *node);

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

Node *fn_801B43D8(void)
{
    Node *node;

    if (lbl_8066C6E0 == 0) {
        fn_801B4454(0x200);
    }
    node = lbl_8066C6E4;
    lbl_8066C6E4 = lbl_8066C6E4->next;
    lbl_8066C6E0--;
    memset(node, 0, 0x14);
    return node;
}

void fn_801B4454(int n)
{
    Node *nodes;
    unsigned int i;

    nodes = fn_801AD324(n * 0x14, lbl_8049E560, 0x98);
    if (nodes == 0) {
        return;
    }
    lbl_8066C6D8 += (n * 0x14 + 0x1F) & ~0x1F;
    lbl_8066C6DC += n;
    for (i = 0; i < n; i++) {
        fn_804673E0(nodes + i);
    }
}
