// Havok glue (an entity listener, the hkMemory pool allocator, ShapeRepository, the .nhg loader fn_800777C4),
// then the script class table and the base class methods (docs/story.md rows 4 and 22, section 4.1).
// One pool from 0x80487BF0 (extern_pool). The base virtuals follow the static init, in slot order.

inline int sn_return_decl(int a) { return a; }

struct SObj {
    int unk0;
};

struct SBodyBase {
    int unk0;
};

struct SBody : SBodyBase { // what fn_800B24AC returns
    int pad;
};

struct Lsn {
    void *vptr;
};

struct Pair8 {
    int a, b;
};

struct PairArray {
    Pair8 *data; // +0x0
    int n;       // +0x4
};

struct Coll {
    char pad0[0x18];
    Lsn lsn;         // +0x18
    PairArray pairs; // +0x1C
};

struct MemHdr { // 0x10, in front of every block from fn_80076834
    int magic; // 0x2345656, 0xdeadbeef once freed
    int size;  // +0x4
    int align; // +0x8
    int pad;
};

class MemV { // hkMemory, vptr at +0x3C
public:
    char d[0x3c];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void *v4(int size, int align);          // +0x28
    virtual void v5(MemHdr *block, int size, int align); // +0x30
};

struct Mem : MemV { // 0x340
    void **free40;   // +0x40
    int f44;         // +0x44
    int f48;         // +0x48
    int f4C;         // +0x4C
    int a50[17];     // +0x50
    int a94[17];     // +0x94
    char bD8[0x204]; // +0xD8
    int a2DC[8];     // +0x2DC
    int s2FC[17];    // +0x2FC
};

struct MemStats { // 0x1C
    int count;   // +0x0, big blocks live
    int bigUsed; // +0x4
    int bigPeak; // +0x8
    int fC;      // +0xC
    int f10;     // +0x10
    int f14;     // +0x14
    int used;    // +0x18, small blocks
};

struct MemRaw {
    char d[0x20];
    MemStats stats;  // +0x20
    void *vptr;      // +0x3C
    void **free40;   // +0x40, page list
    char *f44;       // +0x44, current page
    char *f48;       // +0x48, end of the carve area
    char *f4C;       // +0x4C, carve cursor
    int *a50[17];    // +0x50, free list per size class
    int a94[17];     // +0x94, size of each class
    signed char bD8[0x204]; // +0xD8, class of each size up to 0x200
    int a2DC[8];     // +0x2DC, class of each 1 KB step
    int s2FC[17];    // +0x2FC, blocks out per class
};


class SMat4 {
public:
    float m[4][4];
    SMat4() __asm__("fn_8042D7B0");
};

struct ShapeXf { // what fn_80077EF4's last argument points at
    float scale;  // +0x0
    float f4;     // +0x4
    int pad[2];
    float pos[4]; // +0x10
    float rot[4]; // +0x20
};

struct Shape { // 0x70
    void *handle;         // +0x0, released by fn_8043B878
    char name[0x20];      // +0x4
    unsigned char kind;   // +0x24
    unsigned short sub;   // +0x26
    float f28;            // +0x28
    float scale;          // +0x2C
    SMat4 mat;            // +0x30
    Shape(void *handle, char *name, unsigned char kind, unsigned short sub, float f, ShapeXf *xf) __asm__("fn_80077EF4");
};

struct ShapeArr { // fn_801B5BA8's container
    int d[9];
};

struct ShapeEntry { // 0x48, one per name in the ShapeRepository
    char name[0x20];       // +0x0
    unsigned short flags;  // +0x20, bit 0 from the ctor's flag
    ShapeArr arr;          // +0x24, the Shapes (0x70 each)
    ShapeEntry(char *name, int flag, unsigned short cap) __asm__("fn_8007788C");
};

struct RepoNode {
    RepoNode *next;  // +0x0
    char pad[0xc];
    ShapeEntry *val; // +0x10
};

struct Repo {
    char pad[0x24];
    unsigned int n;     // +0x24
    RepoNode **buckets; // +0x28
};

struct IntArr { // fn_804405E0's container
    int d[4];
};

struct Watch { // a body listener with five vtables
    void *vptr;  // +0x0
    int f4;      // +0x4
    void *v8;    // +0x8
    void *vC;    // +0xC
    void *v10;   // +0x10
    void *v14;   // +0x14
    Lsn lsn;     // +0x18
    IntArr arr;  // +0x1C, the bodies
};

class Flag {
public:
    char v;
    Flag(int v);
};

extern char lbl_804F46C0[];
extern char lbl_804F4740[];
extern char lbl_804F4758[];
extern char lbl_804F4770[];
extern char lbl_804F47A8[];
extern char lbl_804F47C8[];
extern char lbl_804F47E8[];

extern "C" {

void fn_8006668C(SObj *o, float f);
void *fn_80077064(MemRaw *self, int size, int k);
void fn_80077330(MemRaw *self, int size, int align);
void fn_80077358(MemRaw *self, int size, int align);
SBody *fn_800B24AC(SObj &o);
void *fn_801AC9EC(int size, char *tag, int line, int a, int align, int b);
void fn_801ACC0C(void *p);
void fn_802E2974(MemRaw *self, int inChrg);
void fn_802E29B0(MemRaw *self);
int fn_802E2BE0(MemRaw *self, int size);
void fn_802E2D7C(int out, char *fmt, ...);
void *fn_80317948(int body);
void fn_80317A18(int body, Lsn *l);
void fn_80317AD4(int body, Lsn *l);
int fn_8032A228(SBodyBase &body);
void fn_8043BF78(int a, int b);
void fn_8043C0C8(SBody *b);
int fn_8043F114(void *arr, Lsn *const &key);
int fn_80441D78(PairArray *self);
Pair8 *fn_80441DA4(PairArray *self, int i);
void fn_80441DE0(PairArray *self, int i);
int *fn_80441E44(int *self);

int fn_80076E08(MemRaw *self, int size);
int fn_80076E64(MemRaw *self, int size);
void fn_80076FDC(MemRaw *self, void *p, int k);

extern Repo *lbl_8066FB2C; // ShapeRepository
extern int lbl_8066B888;

Repo *fn_801B4284R(int capacity, char *name) __asm__("fn_801B4284");
void *__builtin_new(int size);
void __builtin_delete(void *p);
char *strncpy(char *d, const char *s, int n);
int fn_80441EA0(ShapeEntry *e);
void fn_801B4B28(Repo *r, RepoNode *n, int key);
void *fn_801B48AC(void *table, char *name);
int fn_801B4628(Repo *r, int key, ShapeEntry *e);
void fn_801B4094(char *path, char *ext);
void *fn_801A8368(char *path, char *mode, int flags);
void fn_801A875C(void *file);
void fn_801B5BA8(ShapeArr *a, int cap, float grow);
int fn_801B6A44(ShapeArr *a);
void *fn_801B5D3C(ShapeArr *a, int i);
void fn_801B60F4(ShapeArr *a);
void fn_801B5C74(ShapeArr *a, int inChrg);
void fn_801B6040(ShapeArr *a, Shape *s);
void fn_801B5E38(ShapeArr *a, int n);
int fn_801A8B60(void *buf, int size, int n, void *file);
float fn_8043D570(Shape *s);
void *fn_8043D544(Shape *s);
int fn_804415C8(Shape *s);
int fn_804415F8(Shape *s);
char *fn_80441E74(Shape *s);
int stricmp(const char *a, const char *b);
void fn_8043B878(void *h);
void fn_8006EAC4(SMat4 *m, float *q);
void fn_80434BA4(float *out, float *v);
void fn_8042DCC0(SMat4 *m);
void fn_8042D7B0(SMat4 *m);
void fn_8006EB5C(float *q, SMat4 *m);
void fn_80385F34(float f, ShapeXf *xf);
void fn_80436878(float *out, float *v);
void *fn_8006EEDC(void *file);
int fn_804405E0(IntArr *a);
int &fn_80441894(IntArr *a, int i);
int fn_80441EC8(IntArr *a, const int &v);
void fn_80441810(IntArr *a, const int &v);
void fn_80441F50(IntArr *a, int i);
void fn_80441738(IntArr *a, int inChrg);
void fn_8043F9B4(Lsn *l, int inChrg);
void fn_8043D9B0(Watch *w, int inChrg);
void fn_8043DAEC(Watch *w);
int fn_804367A8(int a);

void fn_8007608C(register SObj *o)
{
    if (!fn_800B24AC(*o))
        return;
    fn_8043BF78(fn_8032A228(*fn_800B24AC(*o)), 2);
    fn_8006668C(o, 0.8f);
    fn_8043C0C8(fn_800B24AC(*o));
}

void fn_8007611C(register Lsn *self)
{
}

int fn_8007613C(register Lsn *self, int a, float b, int c, int d)
{
    return 0;
}

void fn_80076174(register Lsn *self)
{
}


void fn_80076194(register Coll *self, int body)
{
    int found;
    int i;

    found = 0;
    i = 0;
    while (i < fn_80441D78(&self->pairs)) {
        int a = fn_80441DA4(&self->pairs, i)->a;
        int b = fn_80441DA4(&self->pairs, i)->b;

        if (a == body || b == body) {
            fn_80441DE0(&self->pairs, i);
            found = 1;
        } else
            i++;
    }
    if (found) {
        if (fn_8043F114(fn_80317948(body), &self->lsn) != -1)
            fn_80317AD4(body, &self->lsn);
    }
}

void fn_800762D0(register Coll *self, int old, int nw)
{
    int found;
    int i;

    found = 0;
    i = 0;
    while (i < fn_80441D78(&self->pairs)) {
        int a = fn_80441DA4(&self->pairs, i)->a;
        int b = fn_80441DA4(&self->pairs, i)->b;

        if (a == old) {
            fn_80441DA4(&self->pairs, i)->a = nw;
            found = 1;
        } else if (b == old) {
            fn_80441DA4(&self->pairs, i)->b = nw;
            found = 1;
        } else
            i++;
    }
    if (found) {
        if (fn_8043F114(fn_80317948(old), &self->lsn) != -1)
            fn_80317AD4(old, &self->lsn);
        fn_80317A18(nw, &self->lsn);
    }
}

void fn_80076458(register Lsn *self, int a)
{
}

void fn_8007647C(register Coll *self, int body)
{
    fn_80076194(self, body);
}

void fn_800764BC()
{
}


int fn_800764D8(register MemRaw *self, int size)
{
    if (size <= 0x2000) {
        int k = fn_80076E08(self, size);
        int n = self->a94[k];

        return n;
    }
    return fn_802E2BE0(self, size);
}

MemRaw *fn_80076568(register MemRaw *self)
{
    fn_802E29B0(self);
    self->vptr = lbl_804F46C0;
    register int *base;
    register int i;
    register int *p;
    ({
        base = self->s2FC;
        p = self->s2FC;
    });
    i = 16;
    if (i != -1) {
        for (;;) {
            fn_80441E44(p);
            p++;
            i--;
            if (i == -1)
                break;
        }
    }
    self->f44 = 0;
    self->f48 = 0;
    self->f4C = 0;
    self->free40 = 0;
    int j;
    for (j = 16; j >= 0; j--)
        self->a50[j] = 0;
    for (j = 0; j <= 0x200; j++) {
        int k = fn_80076E64(self, j);

        self->bD8[j] = k;
        self->a94[k] = j;
    }
    for (j = 0; j <= 7; j++) {
        int sz = (j + 1) << 10;
        int k = fn_80076E64(self, sz);

        self->a2DC[j] = k;
        self->a94[k] = sz;
    }
    self->stats.count = 0;
    self->stats.bigUsed = 0;
    self->stats.bigPeak = 0;
    self->stats.fC = 0;
    self->stats.f10 = 0x2000;
    self->stats.f14 = 0x40;
    self->stats.used = 0;
    return self;
}

void fn_80076770(register MemRaw *self, int inChrg)
{
    self->vptr = lbl_804F46C0;
    while (self->free40) {
        void **p = self->free40;

        self->free40 = (void **)*self->free40;
        fn_801ACC0C(p);
    }
    fn_802E2974(self, inChrg);
}

inline void *sn_havok_tag(int size) { return fn_801AC9EC(size, "Havok", 0, 2, 0x40, 0); }

void fn_800767EC(register MemRaw *self, int out)
{
    fn_802E2D7C(out, "Statistics are disabled, please enable them in hkbase/config/hkConfigMemoryStats.h\n");
}

MemHdr *fn_80076834(register Mem *self, int size, int align)
{
    MemHdr *h = (MemHdr *)self->v4(size + 0x10, align);

    h->magic = 0x2345656;
    h->size = size;
    h->align = align;
    return h + 1;
}

void fn_800768E4(register Mem *self, void *p)
{
    if (p) {
        MemHdr *h = (MemHdr *)p - 1;

        h->magic = 0xdeadbeef;
        self->v5(h, h->size + 0x10, h->align);
    }
}


int fn_80076988(register Mem *self, int align, int size, int flags)
{
    int raw = (int)self->v4(align + size + 0x10, flags);
    int aligned = ((raw + 0x10) + (align - 1)) & ~(align - 1);
    MemHdr *h = (MemHdr *)aligned - 1;

    h->magic = 0x2345656;
    h->size = size + align;
    h->align = flags;
    h->pad = aligned - raw;
    return aligned;
}

void fn_80076A8C(register Mem *self, void *p)
{
    if (p) {
        MemHdr *h = (MemHdr *)p - 1;

        h->magic = 0xdeadbeef;
        int raw = (int)p - h->pad;
        self->v5((MemHdr *)raw, h->size + 0x10, h->align);
    }
}

void *fn_80076B44(register MemRaw *self, int size, int align)
{
    fn_80077330(self, size, align);
    if (size <= 0x2000) {
        int k = fn_80076E08(self, size);

        self->s2FC[k]++;
        self->stats.used += self->a94[k];
        int *p = self->a50[k];
        if (p) {
            self->a50[k] = (int *)*p;
            return p;
        }
        return fn_80077064(self, size, k);
    } else {
        self->stats.count++;
        self->stats.bigUsed += size;
        if (self->stats.bigUsed > self->stats.bigPeak)
            self->stats.bigPeak = self->stats.bigUsed;
        void *q = fn_801AC9EC(size, "Havok", 0x2ad, 2, 0x40, 0);
        return q;
    }
}

void fn_80076CDC(register MemRaw *self, void *p, int size, int align)
{
    if (p) {
        fn_80077358(self, size, align);
        if (size <= 0x2000) {
            int k = fn_80076E08(self, size);

            self->stats.used -= self->a94[k];
            fn_80076FDC(self, p, k);
        } else {
            self->stats.bigUsed -= size;
            fn_801ACC0C(p);
        }
    }
}

void fn_80076DA0(register MemRaw *self, MemStats *out)
{
    *out = self->stats;
}

int fn_80076E08(register MemRaw *self, register int size)
{
    return size <= 0x200 ? self->bD8[size] : self->a2DC[(size - 1) >> 10];
}

int fn_80076E64(register MemRaw *self, register int size)
{
    if (size <= 8)
        return 1;
    else if (size <= 0x10)
        return 2;
    else if (size <= 0x20)
        return 3;
    else if (size <= 0x30)
        return 4;
    else if (size <= 0x40)
        return 5;
    else if (size <= 0x60)
        return 6;
    else if (size <= 0x80)
        return 7;
    else if (size <= 0xa0)
        return 8;
    else if (size <= 0xc0)
        return 9;
    else if (size <= 0x100)
        return 10;
    else if (size <= 0x140)
        return 11;
    else if (size <= 0x200)
        return 12;
    else if (size <= 0x400)
        return 13;
    else if (size <= 0x800)
        return 14;
    else if (size <= 0x1000)
        return 15;
    else if (size <= 0x2000)
        return 16;
    else {
        *(int *)0 = 0;
        return -1;
    }
}

void fn_80076FDC(register MemRaw *self, register void *p, register int k)
{
    self->s2FC[k]--;
    int *node = (int *)p;

    *node = (int)self->a50[k];
    self->a50[k] = node;
}


void *fn_80077064(register MemRaw *self, register int size, register int k)
{
    if (size <= 0x200) {
        int row = k;
        int bs = self->a94[row];
        int n = bs;

        if (self->f4C + bs > self->f48) {
            void **page = (void **)fn_801AC9EC(0x2040, "Havok", 0x87, 2, 0x40, 0);

            *page = self->free40;
            self->free40 = page;
            self->f44 = (char *)page + 0x40;
            self->f4C = self->f44;
            self->f48 = self->f4C + 0x2000;
            self->stats.fC++;
        }
        char *res = self->f4C;
        self->f4C += bs;
        int saved = self->s2FC[row];

        for (; n <= 0xff; n += bs) {
            if (self->f4C + bs < self->f48) {
                fn_80076FDC(self, self->f4C, row);
                self->f4C += bs;
            } else
                break;
        }
        self->s2FC[row] = saved;
        return res;
    } else {
        int row = k;
        int bs = self->a94[row];
        void **page = (void **)fn_801AC9EC(0x2040, "Havok", 0xc7, 2, 0x40, 0);

        if (self->free40) {
            *page = *self->free40;
            *self->free40 = page;
        } else {
            *page = 0;
            self->free40 = page;
        }
        self->stats.fC++;
        int saved = self->s2FC[row];
        char *res = (char *)page + 0x40;
        char *cur = res + bs;
        int n;

        for (n = bs; n <= 0x1fff; n += bs) {
            fn_80076FDC(self, cur, row);
            cur += bs;
        }
        self->s2FC[row] = saved;
        return res;
    }
}

void fn_80077330(register MemRaw *self, register int size, register int align)
{
}

void fn_80077358(register MemRaw *self, register int size, register int align)
{
}

void fn_80077404();

void fn_80077380()
{
    lbl_8066FB2C = fn_801B4284R(0x200, "ShapeRepository");
    lbl_8066B888 = 0;
}

void fn_800773CC()
{
    fn_80077404();
    lbl_8066B888 = 0;
}


void fn_8007794C(register ShapeEntry *self, int inChrg);
int fn_800781FC(void *file);
void *fn_80077ADC(register ShapeEntry *self, char *name, unsigned char kind, unsigned short sub, float *out, ShapeXf *xf, float f);
void fn_80078010(Shape *self, int inChrg);
ShapeEntry *fn_8007766C(char *name, int create, int flag, unsigned short cap);
Shape *fn_80077A2C(register ShapeEntry *self, void *handle, char *name, unsigned char kind, unsigned short sub, float f, ShapeXf *xf);

void fn_80077404()
{
    ShapeEntry *val;
    RepoNode *node;
    RepoNode *next;
    unsigned int i;

    if (!lbl_8066FB2C)
        return;
    for (i = 0; i < lbl_8066FB2C->n; i++) {
        for (node = lbl_8066FB2C->buckets[i]; node; node = next) {
            next = node->next;
            val = node->val;
            fn_801B4B28(lbl_8066FB2C, node, fn_80441EA0(val));
            if (val) {
                fn_8007794C(val, 3);
            } else {
            }
        }
    }
}

Shape *fn_800774FC(void *handle, char *name, char *sname, unsigned char kind, unsigned short sub, int flag, float f, ShapeXf *xf, unsigned short e)
{
    ShapeEntry *ent = fn_8007766C(name, 1, flag, 0x40);

    return fn_80077A2C(ent, handle, sname, kind, sub, f, xf);
}

ShapeEntry *fn_800775B4(char *name, int flag, unsigned short cap)
{
    if (fn_801B48AC(lbl_8066FB2C, name))
        return 0;
    ShapeEntry *e = new ShapeEntry(name, flag, cap);

    fn_801B4628(lbl_8066FB2C, fn_80441EA0(e), e);
    return e;
}

ShapeEntry *fn_8007766C(char *name, int create, int flag, unsigned short cap)
{
    ShapeEntry *e = (ShapeEntry *)fn_801B48AC(lbl_8066FB2C, name);

    if (!e && create)
        e = fn_800775B4(name, flag, cap);
    return e;
}

void *fn_80077704(char *name, char *sname, unsigned char kind, unsigned short sub, float *out, ShapeXf *xf, float f)
{
    ShapeEntry *e = fn_8007766C(name, 0, 0, 0x40);

    if (e)
        return fn_80077ADC(e, sname, kind, sub, out, xf, f);
    else
        return 0;
}

int fn_800777C4(char *name, int flag)
{
    char path[0x80];

    strncpy(path, name, 0x20);
    fn_801B4094(path, "nhg");
    void *file = fn_801A8368(path, "rb", 0x21);

    if (!file)
        return 0;
    int e = fn_800781FC(file);

    fn_801A875C(file);
    if (flag)
        lbl_8066B888 = 1;
    return e;
}

ShapeEntry *fn_8007788C(register ShapeEntry *self, char *name, int flag, unsigned short cap)
{
    fn_801B5BA8(&self->arr, cap, 1.0f);
    if (name) {
        strncpy(self->name, name, 0x20);
        self->name[0x1f] = 0;
    } else
        self->name[0] = 0;
    self->flags = 0;
    if (flag)
        self->flags |= 1;
    return self;
}

void fn_8007794C(register ShapeEntry *self, int inChrg)
{
    unsigned short i;
    register Shape *s;

    for (i = 0; i < fn_801B6A44(&self->arr); i++) {
        s = (Shape *)fn_801B5D3C(&self->arr, i);

        if (s) {
            fn_80078010(s, 3);
        } else {
        }
    }
    fn_801B60F4(&self->arr);
    fn_801B5C74(&self->arr, 2);
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}

Shape *fn_80077A2C(register ShapeEntry *self, void *handle, char *name, unsigned char kind, unsigned short sub, float f, ShapeXf *xf)
{
    Shape *s = new Shape(handle, name, kind, sub, f, xf);

    fn_801B6040(&self->arr, s);
    return s;
}


Shape *fn_80077BC0(register ShapeEntry *self, char *name, unsigned char kind, unsigned short sub);
void fn_80078068(Shape *s, ShapeXf *xf, float f);
int fn_8007810C(Shape *s, void *file);

void *fn_80077ADC(register ShapeEntry *self, char *name, unsigned char kind, unsigned short sub, float *out, ShapeXf *xf, float f)
{
    Shape *s = fn_80077BC0(self, name, kind, sub);

    if (s) {
        if (out)
            *out = fn_8043D570(s);
        if (xf)
            fn_80078068(s, xf, f);
        return fn_8043D544(s);
    } else
        return 0;
}

Shape *fn_80077BC0(register ShapeEntry *self, char *name, unsigned char kind, unsigned short sub)
{
    Shape *s;
    unsigned short i;

    for (i = 0; i < fn_801B6A44(&self->arr); i++) {
        s = (Shape *)fn_801B5D3C(&self->arr, i);
        if (fn_804415C8(s) == kind && fn_804415F8(s) == sub
            && ((name && !stricmp(fn_80441E74(s), name)) || (!name && !*fn_80441E74(s))))
            return s;
    }
    return 0;
}

int fn_80077D0C(register ShapeEntry *self, unsigned char kind)
{
    Shape *s;
    unsigned short i;

    for (i = 0; i < fn_801B6A44(&self->arr); i++) {
        s = (Shape *)fn_801B5D3C(&self->arr, i);
        if (fn_804415C8(s) == kind)
            return 1;
    }
    return 0;
}

int fn_80077DD0(register ShapeEntry *self, void *file)
{
    unsigned short n;
    Shape *s;
    unsigned short i;

    fn_801A8B60(self->name, 1, 0x20, file);
    fn_801A8B60(&self->flags, 2, 1, file);
    fn_801A8B60(&n, 2, 1, file);
    fn_801B5E38(&self->arr, n);
    for (i = 0; i < n; i++) {
        s = new Shape(0, 0, 0, 0, 0.0f, 0);
        fn_8007810C(s, file);
        fn_801B6040(&self->arr, s);
    }
    return 1;
}

Shape *fn_80077EF4(register Shape *self, void *handle, char *name, unsigned char kind, unsigned short sub, float f, ShapeXf *xf)
{
    fn_8042D7B0(&self->mat);
    self->handle = handle;
    if (name) {
        strncpy(self->name, name, 0x20);
        self->name[0x1f] = 0;
    } else
        self->name[0] = 0;
    self->kind = kind;
    self->sub = sub;
    self->f28 = f;
    if (xf) {
        self->scale = xf->scale;
        fn_8006EAC4(&self->mat, xf->rot);
        fn_80434BA4(self->mat.m[3], xf->pos);
    } else {
        self->scale = 1.0f;
        fn_8042DCC0(&self->mat);
    }
    return self;
}

void fn_80078010(register Shape *self, int inChrg)
{
    fn_8043B878(self->handle);
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}


void fn_80078068(register Shape *self, ShapeXf *xf, float f)
{
    xf->f4 = 1.0f;
    xf->scale = self->scale;
    fn_8006EB5C(xf->rot, &self->mat);
    fn_80436878(xf->pos, self->mat.m[3]);
    if (f != 1.0f)
        fn_80385F34(f, xf);
}

int fn_8007810C(register Shape *self, void *file)
{
    fn_801A8B60(self->name, 1, 0x20, file);
    fn_801A8B60(&self->kind, 1, 1, file);
    fn_801A8B60(&self->sub, 2, 1, file);
    fn_801A8B60(&self->f28, 4, 1, file);
    fn_801A8B60(&self->scale, 4, 1, file);
    fn_801A8B60(&self->mat, 0x40, 1, file);
    self->handle = fn_8006EEDC(file);
    return self->handle != 0;
}

int fn_800781FC(void *file)
{
    unsigned short ver;

    fn_801A8B60(&ver, 2, 1, file);
    if (ver != 4)
        return 0;
    ShapeEntry *e;
    unsigned short tag;

    while (1) {
        if (fn_801A8B60(&tag, 2, 1, file) != 1)
            break;
        e = new ShapeEntry(0, 0, 0x40);
        if (!fn_80077DD0(e, file))
            return 0;
        if (!fn_801B4628(lbl_8066FB2C, fn_80441EA0(e), e)) {
            if (e) {
                fn_8007794C(e, 3);
            } else {
            }
        }
    }
    return 1;
}

void fn_80078324(register Watch *self, int inChrg)
{
    int i;

    self->v8 = lbl_804F4758;
    self->vC = lbl_804F47C8;
    self->v10 = lbl_804F47A8;
    self->v14 = lbl_804F4740;
    self->lsn.vptr = lbl_804F4770;
    self->vptr = lbl_804F47E8;
    for (i = 0; i < fn_804405E0(&self->arr); i++) {
        if (fn_8043F114(fn_80317948(fn_80441894(&self->arr, i)), &self->lsn) >= 0)
            fn_80317AD4(fn_80441894(&self->arr, i), &self->lsn);
    }
    fn_80441738(&self->arr, 2);
    fn_8043F9B4(&self->lsn, 0);
    fn_8043D9B0(self, 0);
    if (inChrg & 1)
        fn_8043DAEC(self);
}

void fn_80078484(register Watch *self, int body)
{
    if (fn_80441EC8(&self->arr, body) != -1)
        return;
    fn_80441810(&self->arr, body);
    if (fn_8043F114(fn_80317948(body), &self->lsn) < 0)
        fn_80317A18(body, &self->lsn);
}

Flag fn_8007852C(register Watch *self, int a, int b)
{
    register int r = fn_80441EC8(&self->arr, fn_804367A8(a)) < 0 && fn_80441EC8(&self->arr, fn_804367A8(b)) < 0;

    return Flag(r);
}

Flag fn_800785E0(register Watch *self, int a, int b, int c, int d, int e)
{
    return Flag(1);
}

Flag fn_80078640(register Watch *self, int a, int b, int c)
{
    return Flag(1);
}

Flag fn_80078698(register Watch *self, int a, int b)
{
    return Flag(1);
}

void fn_800786EC(register Watch *self, int a)
{
}

void fn_80078710(register Watch *self, int body)
{
    int i = fn_80441EC8(&self->arr, body);

    if (i != -1) {
        fn_80441F50(&self->arr, i);
        if (fn_8043F114(fn_80317948(body), &self->lsn) != -1)
            fn_80317AD4(body, &self->lsn);
    }
}

void fn_800787C0(register Watch *self, int old, int nw)
{
    int i = fn_80441EC8(&self->arr, old);

    if (i != -1) {
        fn_80441894(&self->arr, i) = nw;
        if (fn_8043F114(fn_80317948(old), &self->lsn) != -1)
            fn_80317AD4(old, &self->lsn);
        fn_80317A18(nw, &self->lsn);
    }
}

void fn_80078894(register Watch *self, int body)
{
    fn_80078710(self, body);
}

int fn_800788D4(register Watch *self)
{
    return fn_804405E0(&self->arr);
}

}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.text"); // 0x80487C78-0x80487C80, a 1.0f and a 0.0f no function loads

inline int sn_return_decl3(int a)
{
    return a;
}

class cScript;

struct ScriptClass { // 0x28
    char name[0x20];
    cScript *prototype; // +0x20
    int count;          // +0x24, live instances
};

struct ScriptLink { // 8
    int type;
    union {
        void *p; // +0x4
        int v;
        unsigned int u;
        float f;
        char *str;
    };
};

class cScript
{
public:
    ScriptClass *entry;  // +0x0
    int id;              // +0x4
    cScript *owner;      // +0x8
    unsigned int nlinks; // +0xc
    ScriptLink *links;   // +0x10
    int f14;             // +0x14
    int f18;             // +0x18
    int f1c;             // +0x1c
    int f20;             // +0x20
    cScript() __asm__("fn_80441FAC");
    virtual ~cScript();          // slot 1
    virtual cScript *clone();    // slot 2
    virtual void slot3();        // slot 3
};

extern "C" {

void *fn_801B4284(int capacity, char *name);
void *fn_801B48AC(void *table, char *name);
void fn_801ACC0C(void *p);
void fn_8007D1B0(cScript *self);
void fn_8007D8B0(cScript *self);
ScriptClass *fn_8007A2C4(cScript *self);
void fn_8007A2F0(cScript *self, ScriptClass *entry);
void fn_80078FDC(cScript *self, cScript *owner);
int fn_800B13D8(cScript *actor);
int atoi(const char *s);
double atof(const char *s);
int sprintf(char *buf, const char *fmt, ...);

extern char lbl_8054DD54[];
extern char lbl_8054D130[]; // Sub24
extern char lbl_8066D5FC[];
extern char lbl_8066D604[];
extern char lbl_8066D60C[];
extern char lbl_804F4810[]; // the base vtable

void fn_801B54E8(void *self, int n, float f);
void Sub24_dtor(void *self, int flags) __asm__("_._5Sub24");
int *fn_80441FE0(void *self, int a);
void __builtin_delete(void *p);

extern int lbl_8066B898;
extern void *lbl_8066D614;
extern unsigned int lbl_8066D618;
extern int lbl_8066D61C;
extern cScript *lbl_8054D554[];

int fn_8007891C()
{
    if (lbl_8066B898 != 0)
        return 0;
    lbl_8066D614 = fn_801B4284(0x3F, "ScriptClasses");
    lbl_8066D618 = 0;
    lbl_8066D61C = 1;
    lbl_8066B898 = 1;
    return 1;
}

ScriptClass *ScriptClass_Find(char *name)
{
    return (ScriptClass *)fn_801B48AC(lbl_8066D614, name);
}

cScript *Script_Create(char *name, int init)
{
    cScript *copy;
    ScriptClass *entry;
    cScript *proto;

    copy = 0;
    entry = ScriptClass_Find(name);
    if (entry == 0)
        return 0;
    proto = entry->prototype;
    if (proto == 0)
        return 0;
    copy = proto->clone();
    if (copy != 0) {
        fn_8007A2F0(copy, entry);
        copy->nlinks = 0;
        copy->links = 0;
        copy->f14 = 0;
        copy->f18 = 0;
        copy->f1c = 0;
        if (init != 0)
            fn_80078FDC(copy, 0);
    }
    return copy;
}

void Script_RemoveLive(cScript *self);

void Script_Destroy(cScript *self)
{
    unsigned int i;
    ScriptLink *link;

    fn_8007D1B0(self);
    fn_8007D8B0(self);
    Script_RemoveLive(self);
    if (self->links != 0) {
        for (i = 0; i < self->nlinks; i++) {
            link = &self->links[i];
            if (link->p != 0 && (link->type == 7 || link->type == 8 || link->type == 9))
                fn_801ACC0C(link->p);
        }
        fn_801ACC0C(self->links);
    }
    delete self;
}

void Script_AddLive(cScript *self)
{
    lbl_8054D554[lbl_8066D618++] = self;
    if (fn_8007A2C4(self) != 0)
        fn_8007A2C4(self)->count++;
}

void Script_RemoveLive(cScript *self)
{
    unsigned int i;

    for (i = 0; i < lbl_8066D618; i++) {
        if (lbl_8054D554[i] == self) {
            lbl_8054D554[i] = lbl_8054D554[--lbl_8066D618];
            if (fn_8007A2C4(self) != 0)
                fn_8007A2C4(self)->count--;
            return;
        }
    }
    return;
}

cScript *fn_80078DD4(register cScript *self)
{
    return new cScript;
}

struct ScriptSource {
    char pad[0x14C];
    cScript *links; // +0x14C
};

void fn_80078E28(register cScript *self, ScriptSource *src, cScript **map)
{
    cScript *list;
    unsigned int i;
    cScript *t;

    list = src->links;
    for (i = 0; i < list->nlinks; i++) {
        switch (list->links[i].type) {
        case 3:
        case 5:
        case 10:
        case 11:
        case 12:
        case 13:
            switch (list->links[i].v) {
            case -2:
                list->links[i].v = 0;
                break;
            case -1:
                list->links[i].v = 0;
                break;
            default:
                t = map[list->links[i].v];
                if (t != 0)
                    list->links[i].v = fn_800B13D8(t);
            }
            break;
        }
    }
}

void fn_80078FDC(register cScript *self, cScript *owner)
{
    self->id = lbl_8066D61C++;
    self->owner = owner;
    Script_AddLive(self);
    self->slot3();
}

int Script_GetParamInt(register cScript *self, unsigned int i)
{
    if (i >= self->nlinks)
        return 0;
    switch (self->links[i].type) {
    case 1:
        return self->links[i].v;
    case 3:
    case 5:
    case 10:
    case 11:
    case 12:
    case 13:
        return self->links[i].v;
    case 2:
        return (int)self->links[i].f;
    case 7:
    case 8:
    case 9:
        return atoi(self->links[i].str);
    default:
        return 0;
    }
}

unsigned int Script_GetParamUInt(register cScript *self, unsigned int i)
{
    if (i >= self->nlinks)
        return 0;
    switch (self->links[i].type) {
    case 1:
        return self->links[i].u;
    case 3:
    case 5:
    case 10:
    case 11:
    case 12:
    case 13:
        return self->links[i].u;
    case 2:
        return (unsigned int)self->links[i].f;
    case 7:
    case 8:
    case 9:
        return atoi(self->links[i].str);
    default:
        return 0;
    }
}

float Script_GetParamFloat(register cScript *self, unsigned int i)
{
    if (i >= self->nlinks)
        return 0.0f;
    switch (self->links[i].type) {
    case 1:
        return self->links[i].v;
    case 3:
    case 5:
    case 10:
    case 11:
    case 12:
    case 13:
        return self->links[i].u;
    case 2:
        return self->links[i].f;
    case 7:
    case 8:
    case 9:
        return atof(self->links[i].str);
    default:
        return 0.0f;
    }
}

char *Script_GetParamString(register cScript *self, unsigned int i)
{
    if (i >= self->nlinks)
        return "Invalid Param";
    switch (self->links[i].type) {
    case 1:
        sprintf(lbl_8054DD54, "%d", self->links[i].v);
        return lbl_8054DD54;
    case 3:
    case 5:
    case 10:
    case 11:
    case 12:
    case 13:
        sprintf(lbl_8054DD54, "%u", self->links[i].u);
        return lbl_8054DD54;
    case 2:
        sprintf(lbl_8054DD54, "%f", self->links[i].f);
        return lbl_8054DD54;
    case 7:
    case 8:
    case 9:
        return self->links[i].str;
    default:
        return 0;
    }
}

void fn_800796A4(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            fn_801B54E8(lbl_8054D130, 0x19, 0.2f);
            fn_80441FE0(lbl_8066D5FC, 0);
            fn_80441FE0(lbl_8066D604, 1);
            fn_80441FE0(lbl_8066D60C, 2);
        } else {
            Sub24_dtor(lbl_8054D130, 2);
        }
    }
}

}

inline int sn_return_decl2(int a)
{
    return a;
}

struct cScriptVptr {
    char pad[0x24];
    void *vptr; // +0x24
};

extern "C" {

void fn_8007975C(register cScript *self, register int inChrg) // slot 1
{
    ((cScriptVptr *)self)->vptr = lbl_804F4810;
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}

void fn_800797B4(register cScript *self) // slot 3
{
}

cScript *Script_GetOwner(register cScript *self)
{
    return self->owner;
}

void fn_80079800(register cScript *self) // slot 4
{
    return;
}

void fn_80079824(register cScript *self) // slot 5
{
    return;
}

void fn_80079848(register cScript *self) // slot 6
{
    return;
}

void fn_8007986C(register cScript *self) // slot 7
{
    return;
}

void fn_80079890(register cScript *self, register int a0, register float f1, register float f2, register float f3, register float f4, register int a5) // slot 8
{
    return;
}

int fn_800798CC(register cScript *self, register int a0, register int a1, register int a2, register int a3) // slot 9
{
    return 1;
}

void fn_80079904(register cScript *self, register int a0, register int a1) // slot 10
{
    return;
}

void fn_80079930(register cScript *self, register int a0, register int a1, register int a2) // slot 11
{
    return;
}

void fn_80079960(register cScript *self, register int a0) // slot 12
{
    return;
}

void fn_80079988(register cScript *self, register int a0, register int a1) // slot 13
{
    return;
}

void fn_800799B4(register cScript *self, register int a0, register int a1, register int a2) // slot 14
{
    return;
}

void fn_800799E4(register cScript *self, register int a0, register int a1, register int a2) // slot 15
{
    return;
}

void fn_80079A14(register cScript *self, register int a0, register int a1, register int a2) // slot 16
{
    return;
}

int fn_80079A44(register cScript *self, register int a0, register int a1, register int a2) // slot 17
{
    return 0;
}

void fn_80079A78(register cScript *self, register int a0, register int a1, register int a2) // slot 18
{
    return;
}

void fn_80079AA8(register cScript *self, register int a0, register int a1) // slot 19
{
    return;
}

int fn_80079AD4(register cScript *self, register int a0, register int a1, register int a2, register float f3) // slot 20
{
    return 1;
}

float fn_80079B0C(register cScript *self, register int a0, register int a1, register int a2, register int a3, register float f4, register int a5, register int a6) // slot 21
{
    return f4;
}

void fn_80079B40(register cScript *self, register int a0, register int a1, register int a2, register float f3) // slot 22
{
    return;
}

void fn_80079B74(register cScript *self, register int a0, register int a1, register int a2, register float f3, register float f4, register float f5, register float f6, register int a7) // slot 23
{
    return;
}

void fn_80079BB8(register cScript *self, register int a0, register int a1, register int a2, register float f3, register float f4, register float f5, register float f6) // slot 24
{
    return;
}

void fn_80079BF8(register cScript *self, register int a0, register int a1, register int a2) // slot 25
{
    return;
}

int fn_80079C28(register cScript *self, register int a0, register int a1, register int a2, register int a3) // slot 26
{
    return 1;
}

void fn_80079C60(register cScript *self, register int a0, register int a1, register int a2) // slot 27
{
}

void fn_80079C8C(register cScript *self, register int a0, register int a1) // slot 28
{
    return;
}

void fn_80079CB8(register cScript *self, register int a0, register int a1, register int a2) // slot 29
{
    return;
}

void fn_80079CE8(register cScript *self, register int a0, register int a1, register int a2) // slot 30
{
    return;
}

void fn_80079D18(register cScript *self) // slot 31
{
    return;
}

void fn_80079D3C(register cScript *self) // slot 32
{
    return;
}

void fn_80079D60(register cScript *self) // slot 33
{
    return;
}

void fn_80079D84(register cScript *self) // slot 34
{
    return;
}

void fn_80079DA8(register cScript *self) // slot 35
{
    return;
}

void fn_80079DCC(register cScript *self) // slot 36
{
    return;
}

float fn_80079DF0(register cScript *self, register int a0, register int a1, register int a2) // slot 37
{
    return -1.0f;
}

void fn_80079E28(register cScript *self, register int a0, register int a1, register int a2) // slot 38
{
    return;
}

void fn_80079E58(register cScript *self, register int a0, register int a1) // slot 39
{
    return;
}

void fn_80079E84(register cScript *self, register int a0, register int a1) // slot 40
{
    return;
}

void fn_80079EB0(register cScript *self, register int a0, register int a1) // slot 41
{
    return;
}

void fn_80079EDC(register cScript *self, register int a0, register int a1, register int a2) // slot 42
{
    return;
}

void fn_80079F0C(register cScript *self, register int a0, register int a1, register int a2) // slot 43
{
    return;
}

void fn_80079F3C(register cScript *self, register int a0, register int a1) // slot 44
{
    return;
}

void fn_80079F68(register cScript *self, register int a0, register int a1) // slot 45
{
    return;
}

void fn_80079F94(register cScript *self, register int a0, register int a1) // slot 46
{
    return;
}

int fn_80079FC0(register cScript *self, register int a0, register int a1) // slot 47
{
    return 1;
}

int fn_80079FF0(register cScript *self, register int a0, register int a1) // slot 48
{
    return 1;
}

void fn_8007A020(register cScript *self, register int a0, register int a1) // slot 49
{
    return;
}

void fn_8007A04C(register cScript *self, register int a0, register int a1, register int a2) // slot 50
{
    return;
}

void fn_8007A07C(register cScript *self, register int a0, register int a1, register int a2, register float f3, register float f4, register float f5) // slot 51
{
    return;
}

void fn_8007A0B8(register cScript *self, register int a0, register int a1, register int a2, register float f3) // slot 52
{
}

void fn_8007A0E8(register cScript *self, register int a0, register float f1, register int a2, register int a3) // slot 53
{
}

void fn_8007A118(register cScript *self, register float f0, register int a1, register int a2) // slot 54
{
}

void fn_8007A144(register cScript *self, register int a0) // slot 55
{
}

void fn_8007A168(register cScript *self, register int a0, register int a1, register int a2) // slot 56
{
    return;
}

void fn_8007A198(register cScript *self, register int a0, register int a1, register int a2) // slot 57
{
    return;
}

void fn_8007A1C8(register cScript *self, register int a0, register int a1, register int a2) // slot 58
{
    return;
}

void fn_8007A1F8(register cScript *self, register int a0, register int a1) // slot 59
{
    return;
}

void fn_8007A224(register cScript *self, register int a0) // slot 60
{
    return;
}

void fn_8007A24C(register cScript *self, register int a0, register int a1, register int a2) // slot 61
{
}

void fn_8007A278(register cScript *self, register int a0, register int a1) // slot 62
{
}

void fn_8007A2A0(register cScript *self) // slot 63
{
    return;
}

ScriptClass *fn_8007A2C4(register cScript *self)
{
    return self->entry;
}

void fn_8007A2F0(register cScript *self, register ScriptClass *entry)
{
    self->entry = entry;
}

}

inline void sn_label_decl() { clear:; } // the pair on the two wrappers (prodg.md)

extern "C" {

void fn_8007A318(void)
{
    fn_800796A4(1, 65535);
}

void fn_8007A35C(void)
{
    fn_800796A4(0, 65535);
}

}

static void (*const sCtorEntry)(void) __attribute__((section(".ctors"))) = fn_8007A318;
static void (*const sDtorEntry)(void) __attribute__((section(".dtors"))) = fn_8007A35C;
