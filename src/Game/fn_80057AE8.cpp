// .cut cutscenes: in-place byte swaps of the header and records, and fn_80058284, which lays out and swaps one track;
// docs/characters.md "Cutscenes". Then the cut file's tail and static init (docs/story.md row 25).
// Owns the cut file's .bss, 0x80543260-0x80544ED0.

#define SWAP16(x) ((((x) & 0xFF) << 8) | ((unsigned short)(x) >> 8))
#define SWAP32(x) (((unsigned)(x) >> 24) | (((unsigned)(x) >> 8) & 0xFF00) | (((x) & 0xFF00) << 8) | ((x) << 24))

typedef struct CutRecord
{
    unsigned a;          // +0x0
    unsigned b;          // +0x4
    char name[0x48];     // +0x8, not swapped
    unsigned w[16];      // +0x50
} CutRecord;

typedef struct CutKey
{
    unsigned a;          // +0x0
    unsigned b;          // +0x4
    unsigned n;          // +0x8
    char *items;         // +0xC, n 12-byte items
} CutKey;

typedef struct CutEntry
{
    unsigned a;          // +0x0
    unsigned short h4;   // +0x4
    unsigned short h6;   // +0x6
    unsigned c;          // +0x8
} CutEntry;

typedef struct CutAnim
{
    char pad0[0x20];
    unsigned flags;      // +0x20
    char pad24[0x8];
    unsigned nKeys;      // +0x2C
    CutKey *keys;        // +0x30
    char pad34[0x8];
    unsigned nEntries;   // +0x3C
    CutEntry *entries;   // +0x40
} CutAnim;

typedef struct CutTrack
{
    unsigned f0;         // +0x0
    unsigned n;          // +0x4
    unsigned f8;         // +0x8
    unsigned fC;         // +0xC
    CutRecord *recs;     // +0x10
    CutAnim **anims;     // +0x14
} CutTrack;

typedef struct CutHeader
{
    unsigned magic;      // +0x0, 0x2715
    unsigned f4;         // +0x4
    unsigned nWords;     // +0x8
    unsigned nRecords;   // +0xC
    unsigned f10;        // +0x10
    char pad14[0x18C - 0x14];
    unsigned *words;     // +0x18C
    CutRecord *recs;     // +0x190
    CutTrack **tracks;   // +0x194
} CutHeader;

typedef struct CutPlayer
{
    char pad0[0x78];
    void *f78;           // +0x78
} CutPlayer;

extern char lbl_80552110[];
extern char lbl_8054ED80[];

extern "C" {

extern int fn_80056690(CutPlayer *player, int a, int b);
extern int fn_800567B4(CutPlayer *player, int a, int b);
extern int fn_8043A8E4(void *p);
extern int fn_80426AB0(void *p);
extern void *fn_804326B4(void *p);
extern int fn_8043A758(void *p);
extern void fn_80199D74(CutAnim *anim);
extern void fn_80438EA4(void *item);

extern void __6Marker(void *self);
extern void __10ElementSet(void *self);
extern void fn_8042D7B0(void *self);
extern void fn_80050BC4(void *self);
extern void fn_80050C30(void *self, int flags);
extern void fn_80050FD0(void *self);
extern void fn_80051064(void *self, int flags);
extern void fn_800520CC(void *self);
extern void fn_8005212C(void *self, int flags);
extern void fn_800522E8(void *self, int a, int b, int c);
extern void fn_800523F4(void *self, int a);

}

typedef struct Storage48 { int w[0x48 / 4]; } Storage48;
typedef struct Storage38 { int w[0x38 / 4]; } Storage38;
typedef struct Storage28 { int w[0x28 / 4]; } Storage28;
typedef struct Storage40 { int w[0x40 / 4]; } Storage40;
typedef struct Storage2C { int w[0x2C / 4]; } Storage2C;
typedef struct Storage59C { int w[0x59C / 4]; } Storage59C;
typedef struct Storage90 { int w[0x90 / 4]; } Storage90;

typedef struct CutPlayerStorage
{
    CutPlayer p;
    char pad[0x14B8 - sizeof(CutPlayer)];
} CutPlayerStorage;

Storage48 lbl_80543260;        // Marker
Storage38 lbl_805432A8;
CutPlayerStorage lbl_805432E0; // ElementSet, the cut player
Storage28 lbl_80544798;
Storage40 lbl_805447C0;        // fn_8042D7B0
Storage2C lbl_80544800;        // fn_80050BC4, ~fn_80050C30
Storage38 lbl_8054482C;        // fn_80050FD0, ~fn_80051064
Storage59C lbl_80544864;       // fn_800520CC, ~fn_8005212C
Storage40 lbl_80544E00;        // fn_8042D7B0
Storage90 lbl_80544E40;

inline int sn_return_decl(int a) { return a; }

extern "C" {

void fn_80057AE8(register CutRecord *rec)
{
    rec->a = SWAP32(rec->a);
    rec->b = SWAP32(rec->b);
    rec->w[0] = SWAP32(rec->w[0]);
    rec->w[1] = SWAP32(rec->w[1]);
    rec->w[2] = SWAP32(rec->w[2]);
    rec->w[3] = SWAP32(rec->w[3]);
    rec->w[4] = SWAP32(rec->w[4]);
    rec->w[5] = SWAP32(rec->w[5]);
    rec->w[6] = SWAP32(rec->w[6]);
    rec->w[7] = SWAP32(rec->w[7]);
    rec->w[8] = SWAP32(rec->w[8]);
    rec->w[9] = SWAP32(rec->w[9]);
    rec->w[10] = SWAP32(rec->w[10]);
    rec->w[11] = SWAP32(rec->w[11]);
    rec->w[12] = SWAP32(rec->w[12]);
    rec->w[13] = SWAP32(rec->w[13]);
    rec->w[14] = SWAP32(rec->w[14]);
    rec->w[15] = SWAP32(rec->w[15]);
}

void fn_80057EF8(register unsigned *p)
{
    p[0] = SWAP32(p[0]);
    p[1] = SWAP32(p[1]);
    p[2] = SWAP32(p[2]);
    p[3] = SWAP32(p[3]);
}

void fn_80057FF8(register CutHeader *h)
{
    h->magic = SWAP32(h->magic);
    h->f4 = SWAP32(h->f4);
    h->nWords = SWAP32(h->nWords);
    h->nRecords = SWAP32(h->nRecords);
    h->f10 = SWAP32(h->f10);
}

int fn_80058130(int a, int b)
{
    return fn_80056690(&lbl_805432E0.p, a, b);
}

int fn_80058184(int a, int b)
{
    return fn_800567B4(&lbl_805432E0.p, a, b);
}

int fn_800581D8(void)
{
    if (lbl_805432E0.p.f78 == 0 || fn_8043A8E4(lbl_805432E0.p.f78) == 0 || fn_80426AB0(lbl_80552110) == 0 ||
        fn_8043A758(fn_804326B4(lbl_8054ED80)) == 0) {
        return 0;
    }
    return 1;
}

unsigned fn_80058284(CutHeader *cut, char *base, unsigned index)
{
    unsigned off;
    unsigned i;
    unsigned j;
    CutAnim *anim;
    CutKey *key;
    unsigned k;
    unsigned m;

    off = 0;
    cut->tracks[index] = (CutTrack *)base;
    off += 0x18;
    fn_80057EF8((unsigned *)cut->tracks[index]);
    cut->tracks[index]->recs = (CutRecord *)(base + off);
    off += cut->tracks[index]->n * 0x90;
    for (i = 0; i < cut->tracks[index]->n; i++) {
        fn_80057AE8(&cut->tracks[index]->recs[i]);
    }
    cut->tracks[index]->anims = (CutAnim **)(base + off);
    off += cut->tracks[index]->n * 4;
    for (j = 0; j < cut->tracks[index]->n; j++) {
        anim = (CutAnim *)(base + off);
        off += 0x50;
        fn_80199D74(anim);
        cut->tracks[index]->anims[j] = anim;
        anim->flags = anim->flags | 0x10000;
        anim->keys = (CutKey *)(base + off);
        off += anim->nKeys * 16;
        for (k = 0; k < anim->nKeys; k++) {
            key = &anim->keys[k];
            key->a = SWAP32(key->a);
            key->b = SWAP32(key->b);
            key->n = SWAP32(key->n);
            key->items = base + off;
            off += key->n * 0xC;
            for (m = 0; m < key->n; m++) {
                fn_80438EA4(key->items + m * 0xC);
            }
        }
    }
    m = 0;
    while (m < cut->tracks[index]->n) {
        cut->tracks[index]->anims[m]->nEntries = (unsigned char)base[off];
        off += 4;
        m++;
    }
    k = 0;
    while (k < cut->tracks[index]->n) {
        if (cut->tracks[index]->anims[k]->nEntries != 0) {
            cut->tracks[index]->anims[k]->entries = (CutEntry *)(base + off);
            off += cut->tracks[index]->anims[k]->nEntries * 0xC;
            // The original reuses anim and key here as the entry pointer and its index.
            for (key = 0; (unsigned)key < cut->tracks[index]->anims[k]->nEntries; key = (CutKey *)((unsigned)key + 1)) {
                anim = (CutAnim *)&cut->tracks[index]->anims[k]->entries[(unsigned)key];
                ((CutEntry *)anim)->a = SWAP32(((CutEntry *)anim)->a);
                ((CutEntry *)anim)->h4 = SWAP16(((CutEntry *)anim)->h4);
                ((CutEntry *)anim)->h6 = SWAP16(((CutEntry *)anim)->h6);
                ((CutEntry *)anim)->c = SWAP32(((CutEntry *)anim)->c);
            }
        }
        k++;
    }
    return off;
}

void fn_80058A48(int a, int b, int c)
{
    fn_800522E8(&lbl_80544864, a, b, c);
}

void fn_80058A98(int a)
{
    fn_800523F4(&lbl_80544864, a);
}

void fn_80058AD8(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            __6Marker(&lbl_80543260);
            __10ElementSet(&lbl_805432E0);
            fn_8042D7B0(&lbl_805447C0);
            fn_80050BC4(&lbl_80544800);
            fn_80050FD0(&lbl_8054482C);
            fn_800520CC(&lbl_80544864);
            fn_8042D7B0(&lbl_80544E00);
        } else {
            fn_8005212C(&lbl_80544864, 2);
            fn_80051064(&lbl_8054482C, 2);
            fn_80050C30(&lbl_80544800, 2);
        }
    }
}

void fn_80058BB4(void)
{
    fn_80058AD8(1, 65535);
}

void fn_80058BF0(void)
{
    fn_80058AD8(0, 65535);
}

}

static void (*const sCtorEntry)(void) __attribute__((section(".ctors"))) = fn_80058BB4;
static void (*const sDtorEntry)(void) __attribute__((section(".dtors"))) = fn_80058BF0;
