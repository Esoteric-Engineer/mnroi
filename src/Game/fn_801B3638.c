// NVB loader and the Misc/nvblist.txt reader; docs/versus.md section 5, row 12.

#define SWAP32(x) (((unsigned)(x) >> 24) | (((unsigned)(x) >> 8) & 0xFF00) | (((x) & 0xFF00) << 8) | ((x) << 24))

typedef struct NvbSource NvbSource;

typedef struct NvbEntry
{
    int type;               // +0x0
    unsigned int count;     // +0x4
    unsigned int *elems[6]; // +0x8
    int unk20;
} NvbEntry;

typedef struct Nvb
{
    char name[0x20];
    int count;         // +0x20
    NvbEntry *entries; // +0x24
    void *unk28;
    char pool[0x10]; // +0x2C
} Nvb;

extern int sprintf(char *dst, const char *fmt, ...);
extern char *strncpy(char *dst, const char *src, unsigned n);
extern int strcmp(const char *a, const char *b);
extern char lbl_8049E518[]; // "%s_%s.nvb"
extern char lbl_8049E52C[]; // allocation tag
extern char lbl_8049E4F8[]; // "rb"
extern NvbSource *fn_801B2F6C(char *a);
extern void *fn_801AC988(int size, char *tag, int line, int flags);
extern void fn_801B34D8(Nvb *nvb, NvbSource *src);
extern void *fn_801A8368(char *name, char *mode, int flags);
extern void fn_801A953C(void *file);
extern int fn_801A8B60(void *dst, int size, int count, void *file);
extern void fn_801A875C(void *file);
extern NvbEntry *fn_801B35CC(Nvb *nvb, int idx);
extern unsigned int *fn_801B31E4(void *pool, int size);
extern void fn_8042FC74(unsigned int *elem);
extern char lbl_8049E540[]; // "nvblist.txt"
extern char lbl_8049E54C[]; // "ra"
extern char lbl_8049E550[]; // " \t\r\n/;"
extern char lbl_8049E558[]; // "|"
extern char *strtok(char *s, const char *delim);
extern char *strcat(char *dst, const char *src);
extern int fn_801A8C84(void *file);
extern char *fn_801A8C08(char *dst, int size, void *file);
extern void *fn_804673B8(Nvb *nvb);
extern void fn_801B4628(void *registry, void *key, Nvb *nvb);
extern void *lbl_8066C6D0;

Nvb *fn_801B3638(char *a, char *b)
{
    NvbSource *src;
    Nvb *nvb;
    char name[0x80];
    void *file;
    int h0;
    int h1;
    int h2;
    char nameA[0x40];
    char nameB[0x40];
    int count;
    int i;
    int x;
    int type;
    unsigned int y;
    unsigned int j;
    unsigned int idx;
    NvbEntry *p;
    unsigned int *elem;
    int size;
    unsigned int k;

    src = fn_801B2F6C(a);
    if (src == 0) {
        return 0;
    }
    nvb = fn_801AC988(0x3C, lbl_8049E52C, 0x27C, 2);
    fn_801B34D8(nvb, src);
    sprintf(name, lbl_8049E518, a, b);
    strncpy(nvb->name, name, 0x20);
    nvb->name[0x1F] = 0;
    file = fn_801A8368(name, lbl_8049E4F8, 9);
    if (file) {
        fn_801A953C(file);
        fn_801A8B60(&h0, 1, 4, file);
        fn_801A8B60(&h1, 1, 4, file);
        fn_801A8B60(&h2, 1, 4, file);
        fn_801A8B60(nameA, 1, 0x40, file);
        fn_801A8B60(nameB, 1, 0x40, file);
        if (strcmp(nameA, a) != 0) {
        }
        if (strcmp(nameB, b) != 0) {
        }
        fn_801A8B60(&count, 1, 4, file);
        count = SWAP32(count);
        for (i = 0; i < count; i++) {
            fn_801A8B60(&x, 1, 4, file);
            x = SWAP32(x);
            fn_801A8B60(&y, 1, 4, file);
            y = SWAP32(y);
            for (j = 0; j < y; j++) {
                fn_801A8B60(&idx, 1, 4, file);
                idx = SWAP32(idx);
                fn_801A8B60(&type, 1, 4, file);
                type = SWAP32(type);
                p = fn_801B35CC(nvb, x);
                if (type != p->type) {
                }
                p->count = y;
                elem = 0;
                switch (type) {
                case -0x2778:
                    size = 4;
                    break;
                case -0x2779:
                    size = 0x10;
                    break;
                default:
                    fn_801A8B60(&size, 1, 4, file);
                    size = SWAP32(size);
                }
                elem = fn_801B31E4(nvb->pool, size);
                p->elems[idx] = elem;
                fn_801A8B60(elem, 1, size, file);
                switch (type) {
                case -0x2779:
                    fn_8042FC74(elem);
                    break;
                case -0x2776:
                    *elem = SWAP32(*elem);
                    break;
                case -0x277C:
                case -0x277B:
                case -0x2777:
                    break;
                default:
                    *elem = SWAP32(*elem);
                }
                if (j == 0 && y != 0) {
                    for (k = 1; k <= 5; k++) {
                        p->elems[k] = p->elems[0];
                    }
                }
            }
        }
        fn_801A875C(file);
    } else {
    }
    return nvb;
}

void fn_801B3C4C(void)
{
    Nvb *nvb;
    char *a;
    char *b;
    char list[0x200] = "\0";
    void *file;
    char line[0x200];

    file = fn_801A8368(lbl_8049E540, lbl_8049E54C, 9);
    if (file) {
        while (!fn_801A8C84(file)) {
            if (fn_801A8C08(line, 0x200, file)) {
                if (line[0] == ' ' || line[0] == '/') {
                    continue;
                }
                a = strtok(line, lbl_8049E550);
                if (!a) {
                    continue;
                }
                b = strtok(0, lbl_8049E550);
                if (!b) {
                    continue;
                }
                strcat(list, a);
                strcat(list, lbl_8049E558);
                strcat(list, b);
                strcat(list, lbl_8049E558);
            }
        }
        fn_801A875C(file);
    }
    a = strtok(list, lbl_8049E558);
    while (a) {
        b = strtok(0, lbl_8049E558);
        nvb = fn_801B3638(a, b);
        if (nvb) {
            fn_801B4628(lbl_8066C6D0, fn_804673B8(nvb), nvb);
        }
        a = strtok(0, lbl_8049E558);
    }
}
