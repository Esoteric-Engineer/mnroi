// Streamer load-complete step: waits for the read, byte-swaps the header tables and queues the result; docs/versus.md, row 8.
struct StreamBuf {
    unsigned magic;     // +0x0
    char pad0[4];
    unsigned a;         // +0x8
    unsigned b;         // +0xC
    char pad1[0x18C - 0x10];
    unsigned *tbl;      // +0x18C
    char *recs;         // +0x190
    char *aux;          // +0x194
};
extern int fn_80243F94(int h);
extern void fn_8023E98C(void);
extern int fn_80243FFC(int h, int *p, int *q);
extern void fn_80057FF8(void *buf);
extern void fn_80057AE8(void *rec);
extern void fn_8023E3D4(void *queue, void *self);
extern char lbl_80543240[];

void fn_80439778(register char *self, register int flag)
{
    int v8;
    int vC;
    register struct StreamBuf **tmp;
    struct StreamBuf **ref;
    char *base;
    unsigned off;
    unsigned i;
    unsigned j;
    unsigned k;

    if (flag != 0) {
        while (fn_80243F94(*(int *)(self + 0x8)) != 1)
            fn_8023E98C();
    }
    if (fn_80243FFC(*(int *)(self + 0x8), &vC, &v8) == 1) {
        tmp = (struct StreamBuf **)(self + 0x30);
        ref = tmp;
        base = *(char **)(self + 0x30);
        fn_80057FF8(*ref);
        off = 0;
        off += 0x198;
        (*ref)->tbl = (unsigned *)(base + off);
        off += (*ref)->a * 4;
        (*ref)->recs = base + off;
        off += (*ref)->b * 0x90;
        (*ref)->aux = base + off;
        off += (*ref)->a * 4;
        for (i = 0; i < (*ref)->a; i++) {
            (*ref)->tbl[i] = ((*ref)->tbl[i] >> 24) | (((*ref)->tbl[i] >> 8) & 0xFF00) | (((*ref)->tbl[i] & 0xFF00) << 8) | ((*ref)->tbl[i] << 24);
        }
        j = 0;
        while (j < (*ref)->b) {
            fn_80057AE8((*ref)->recs + j * 0x90);
            j++;
        }
        if ((*ref)->magic != 0x2715)
            return;
        k = 0;
        while (k < (*ref)->a) {
            if ((*ref)->tbl[k] > 0x4B001)
                return;
            k++;
        }
        fn_8023E3D4(lbl_80543240, self);
        *(int *)(self + 0x74) = 1;
    }
    *(int *)(self + 0x8) = 0;
}
