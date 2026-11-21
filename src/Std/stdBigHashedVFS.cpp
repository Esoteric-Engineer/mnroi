// stdBigHashedVFS: the CLASH.BIG file system, a RealCore file system over the .BIG archives and their .BH indexes (docs/core.md row 6).
// Owns the .rodata from "bf:" (0x8049E3F4); the vtable 0x804F6808 (_vt.15stdBigHashedVFS) stays unclaimed.

inline int sn_return_decl(int a) { return a; }

__asm__(".section .rodata\n\t.balign 4\n\t.type sPrefix,@object\nsPrefix:\n\t.asciz \"bf:\"\n\t.size sPrefix,4\n\t.text");

class Attr {
public:
    int a;                    // +0x0
    const void *b;            // +0x4
    mutable const Attr *link; // +0x8
    Attr(int a, int b);
    Attr(int a, const char *b);
    const Attr &chain(const Attr &next) const;
};

class Sink {
public:
    virtual void *alloc(unsigned int size, const Attr &attrs);
    virtual void free(void *p, const Attr *attrs);
};

struct RCGlobals { // RealCore's globals
    int size;     // +0x0
    Sink *sink;   // +0x4
    int pad[2];
};

struct GXColor {
    unsigned char r, g, b, a;
};

class Rec { // a .BH entry
public:
    unsigned int off() __asm__("fn_80466BE0");
    unsigned int size() __asm__("fn_80466C0C");
    unsigned int unpacked() __asm__("fn_80466C38");
    unsigned int hash() __asm__("fn_80466C64");
};

class BHFile {
public:
    int count() __asm__("fn_80466CFC");
    const Rec *rec(unsigned int i) __asm__("fn_80466C90");
};

struct BF { // an open .BIG
    BF *next;                // +0x000
    int dev;                 // +0x004
    char *header;            // +0x008
    char name[0x104];        // +0x00C
    unsigned long long disc; // +0x110
    unsigned long long pos;  // +0x118
    BHFile *bh;              // +0x120
    void *hash;              // +0x124
};

struct H { // an open file inside a .BIG
    H *next;                   // +0x00
    int f4;                    // +0x04
    BF *bf;                    // +0x08
    int fC;                    // +0x0C
    unsigned long long offset; // +0x10
    unsigned long long size;   // +0x18
    unsigned long long packed; // +0x20, 0 when stored
};

class BFIter {
public:
    BF *node;
    BFIter() __asm__("fn_80466E70");
    BF *get() __asm__("fn_80466EEC");
    void next(int n) __asm__("fn_80466F18");
};

class BFList {
public:
    BF *head;
    BF *tail;
    int count;
    BFList() __asm__("fn_80467158");
    ~BFList();
    void push(BF *p) __asm__("fn_80466D28");
    BF *pop() __asm__("fn_80466DE8");
    BFIter begin() __asm__("fn_80466EA0");
};

class HList {
public:
    H *head;
    H *tail;
    int count;
    HList() __asm__("fn_80467254");
    ~HList();
    void push(H *p) __asm__("fn_80466D88");
    H *pop() __asm__("fn_80466F54");
    int remove(H *p, H *from) __asm__("fn_80466FDC");
};

class Inflater {
public:
    char data[0x28];
    Inflater() __asm__("fn_802E0C50");
    ~Inflater();
    void inflate(const void *src, void *dst) __asm__("fn_802E0DD8");
};

class FileSys {
public:
    char base[0x10];
    FileSys(const char *prefix) __asm__("fn_802407A8");
    virtual ~FileSys();
    virtual int v10();
    virtual void v18();
    virtual int open(const char *path, int mode, int *dev);
    virtual void close(int h);
    virtual unsigned int read(int h, void *buf, unsigned int size, FileSys *dev, int devh);
    virtual int v38(int a, int b, int c);
    virtual long long seek(int h, long long off, int whence, FileSys *dev, int devh);
};

class stdBigHashedVFS : public FileSys {
public:
    BF *bfs;          // +0x14
    int nBF;          // +0x18
    H *handles;       // +0x1C
    int nH;           // +0x20
    Inflater inflater; // +0x24
    BFList freeBF;    // +0x4C
    BFList openBF;    // +0x58
    HList freeH;      // +0x64
    HList openH;      // +0x70
    stdBigHashedVFS();
    virtual ~stdBigHashedVFS();
};

struct VPtr {
    char base[0x10];
    const void *vptr; // +0x10
};

extern "C" {
extern const char sPrefix[]; // "bf:"
extern RCGlobals lbl_804D80F0;
extern char sVtable[] __asm__("_vt.15stdBigHashedVFS");

int strncmp(const char *a, const char *b, unsigned int n);
int strcmp(const char *a, const char *b);
char *strcpy(char *dst, const char *src);
char *strncpy(char *dst, const char *src, unsigned int n);
char *strchr(const char *s, int c);
int sprintf(char *dst, const char *fmt, ...);
int printf(const char *fmt, ...);
void OSFatal(GXColor fg, GXColor bg, const char *msg);
void fn_801B738C(char *name);
void fn_801B4094(char *path, const char *ext);
void *fn_801B4284(int hint, char *name);
void fn_801B4764(void *registry, unsigned int key, const void *value);
void *fn_801B4938(void *registry, unsigned int key);
void *fn_80466BA0(void *p, int align);
int fn_80244404(const char *path, int a, int b);
void fn_80244444(int dev, int pos, void *buf, int len, int b);
int fn_802444E8(int dev, int n);
int fn_8024031C(const char *hdr);
void fn_8024538C(void *dst, const void *src, int n);
void fn_80245B14(void *dst, const void *src, unsigned int n);
void fn_80245AEC(void *p, unsigned int n);
void fn_80242244(int dev, unsigned long long *disc, long long *size);
int fn_802421AC(const char *path, int a, long long *disc, long long *size);
void fn_802443B0(const char *path, void *buf, unsigned int size, int a);
void fn_80467100(void *self, int inChrg);
void fn_80467198(void *self, int inChrg);
void fn_80467294(void *self, int inChrg);
void fn_802E0CC0(void *self, int inChrg);
void *fn_801B24A0(void *self);
void *fn_801B25CC(register unsigned int size, register void *p);
stdBigHashedVFS *fn_801B25F8(register FileSys *fs);

unsigned int fn_801B104C(const char *s)
{
    unsigned int h = 5381;
    int c;

    while ((c = *s++) != 0) {
        h = (h << 5) + h + c;
    }
    return h;
}

unsigned int fn_801B10CC(int nBF, int nH)
{
    return 0x80 + nBF * sizeof(BF) + nH * sizeof(H);
}

stdBigHashedVFS *fn_801B1110(int nBF, int nH, void *mem)
{
    int i;
    stdBigHashedVFS *vfs = (stdBigHashedVFS *)fn_801B24A0(fn_801B25CC(sizeof(stdBigHashedVFS), mem));

    vfs->bfs = (BF *)fn_80466BA0(vfs + 1, 8);
    vfs->nBF = nBF;
    vfs->handles = (H *)(vfs->bfs + vfs->nBF);
    vfs->nH = nH;
    for (i = 0; i < nBF; i++) {
        vfs->freeBF.push(&vfs->bfs[i]);
    }
    for (i = 0; i < nH; i++) {
        vfs->freeH.push(&vfs->handles[i]);
    }
    return vfs;
}

int fn_801B1270(register FileSys *fs, const char *path, int flags)
{
    char raw[0x880];
    char *hdr = (char *)(((unsigned int)raw + 0x7F) & ~0x7F);
    stdBigHashedVFS *vfs = fn_801B25F8(fs);
    BF *bf = vfs->freeBF.pop();
    if (bf == 0) {
        return -1;
    }
    bf->dev = fn_80244404(path, 1, 100);
    if (bf->dev == 0) {
        return -1;
    }
    fn_80244444(bf->dev, 0, hdr, 0x800, 100);
    int hsize = fn_8024031C(hdr);
    if (hsize <= 0) {
        fn_802444E8(bf->dev, 100);
        return -1;
    }
    char tag[0x100];
    sprintf(tag, "BF Header (%s)", path);
    bf->header = (char *)lbl_804D80F0.sink->alloc(hsize, Attr(flags & 0x100 ? 4 : 0, 1).chain(Attr(2, 0x10)).chain(Attr(1, tag)).chain(Attr(5, "c:/Clash/mainline/Code/Std/stdBigHashedVFS.cpp")).chain(Attr(6, 466)));
    fn_8024538C(bf->header, hdr, hsize > 0x800 ? 0x800 : hsize);
    if (hsize > 0x800) {
        fn_80244444(bf->dev, 0x800, bf->header + 0x800, hsize - 0x800, 100);
    }
    strcpy(bf->name, path);
    bf->pos = hsize;
    long long size;
    fn_80242244(bf->dev, &bf->disc, &size);
    char bh[0x80];
    strcpy(bh, path);
    fn_801B4094(bh, "BH");
    long long bhDisc;
    if (fn_802421AC(bh, 1, &bhDisc, &size)) {
        sprintf(tag, "BH File (%s)", bh);
        bf->bh = (BHFile *)lbl_804D80F0.sink->alloc(size, Attr(flags & 0x100 ? 4 : 0, 1).chain(Attr(2, 0x40)).chain(Attr(1, tag)).chain(Attr(5, "c:/Clash/mainline/Code/Std/stdBigHashedVFS.cpp")).chain(Attr(6, 514)));
        fn_802443B0(bh, bf->bh, size, 0);
        BHFile *&idx = bf->bh;
        const int n = idx->count();
        void *tbl = fn_801B4284(n, bh);
        for (int i = 0; i < n; i++) {
            const Rec *const rec = idx->rec(i);
            const unsigned int key = ((Rec *)rec)->hash();
            fn_801B4764(tbl, key, rec);
        }
        bf->hash = tbl;
    }
    vfs->openBF.push(bf);
    return bf - vfs->bfs;
}

int fn_801B183C(register stdBigHashedVFS *self, const char *path, int mode, int *dev)
{
    int off = 0;
    int size = 0;
    int unpacked = 0;
    int all;
    char subbuf[0x100];
    if (strncmp(path, sPrefix, 3) == 0) {
        path += 3;
    }
    if (*path == '/' || *path == '\\') {
        path++;
    }
    const char *bar = strchr(path, '|');
    char *sub = subbuf;
    const char *rest = path;
    if (bar) {
        strncpy(sub, path, bar - path);
        sub[bar - path] = 0;
        rest = bar + 1;
        all = 0;
    } else {
        *sub = 0;
        all = 1;
    }
    char lower[0x100];
    strcpy(lower, path);
    fn_801B738C(lower);
    unsigned int hash = fn_801B104C(lower);
    BFIter it;
    BF *found = 0;
    for (it = self->openBF.begin(); it.get() != 0 && found == 0; it.next(0)) {
        if (all || strcmp(it.get()->name, sub) == 0) {
            Rec *rec = (Rec *)fn_801B4938(it.get()->hash, hash);
            if (rec) {
                off = rec->off();
                size = rec->size();
                unpacked = rec->unpacked();
                found = it.get();
                break;
            } else if (!all) {
                break;
            }
        }
    }
    if (found) {
        H *h = self->freeH.pop();
        h->bf = found;
        h->offset = off;
        if (unpacked == 0) {
            h->size = size;
            h->packed = 0;
        } else {
            h->size = unpacked;
            h->packed = size;
        }
        self->openH.push(h);
        *dev = found->dev;
        return h - self->handles;
    }
    return -1;
}

void fn_801B1BCC(register stdBigHashedVFS *self, int h)
{
    H *e = self->handles + h;
    self->openH.remove(e, 0);
    fn_80245AEC(e, sizeof(H));
    self->freeH.push(e);
}

long long fn_801B1C44(register stdBigHashedVFS *self, int h, long long off, int whence, FileSys *dev, int devh)
{
    H *e = self->handles + h;
    if (e->bf->pos != e->offset + off) {
        e->bf->pos = dev->seek(devh, e->offset + off, whence, 0, 0);
    }
    return off;
}

int fn_801B1D74(register stdBigHashedVFS *self, int h, void *buf, unsigned int size, FileSys *dev, int devh)
{
    H *e = self->handles + h;
    int n = 0;
    if (e->packed == 0) {
        if (size > e->offset + e->size - e->bf->pos) {
            size = e->offset + e->size - e->bf->pos;
        }
        n = dev->read(devh, buf, size, 0, 0);
        e->bf->pos += n;
    } else {
        if (e->size > size) {
            char msg[0x100];
            sprintf(msg, "\nTarget buffer is not large enough for compressed file!\n\n");
            GXColor fg = {255, 255, 255, 255};
            GXColor bg = {255, 0, 0, 255};
            OSFatal(fg, bg, msg);
            return n;
        }
        unsigned int cap = size;
        size = e->packed;
        if (size > e->offset + e->packed - e->bf->pos) {
            size = e->offset + e->packed - e->bf->pos;
        }
        if (size > e->size + 16) {
            printf("\nTarget buffer is not large enough for inplace decompression!\n\n");
            void *tmp = lbl_804D80F0.sink->alloc(size, Attr(4, 1).chain(Attr(2, 0x20)).chain(Attr(1, "Decompession Buffer")).chain(Attr(5, "c:/Clash/mainline/Code/Std/stdBigHashedVFS.cpp")).chain(Attr(6, 884)));
            n = dev->read(devh, tmp, size, 0, 0);
            e->bf->pos += n;
            n = e->size;
            self->inflater.inflate(tmp, buf);
            lbl_804D80F0.sink->free(tmp, 0);
        } else {
            n = dev->read(devh, buf, size, 0, 0);
            e->bf->pos += n;
            n = e->size;
            char *src = (char *)buf + cap - e->packed;
            fn_80245B14(src, buf, e->packed);
            self->inflater.inflate(src, buf);
        }
    }
    return n;
}

unsigned long long fn_801B23E8(register stdBigHashedVFS *self, int h)
{
    H *e = self->handles + h;
    return e->size;
}

unsigned long long fn_801B2438(register stdBigHashedVFS *self, int h)
{
    H *e = self->handles + h;
    return e->bf->disc + e->offset;
}
}

__asm__(".text\n\t.globl fn_801B24A0\n\t.type fn_801B24A0,@function\nfn_801B24A0:");
stdBigHashedVFS::stdBigHashedVFS() : FileSys(sPrefix)
{
}
__asm__(".size fn_801B24A0, 0x90");

extern "C" {
void fn_801B2530(register stdBigHashedVFS *self, register int inChrg)
{
    ((VPtr *)self)->vptr = sVtable;
    fn_80467294(&self->openH, 2);
    fn_80467294(&self->freeH, 2);
    fn_80467198(&self->openBF, 2);
    fn_80467198(&self->freeBF, 2);
    fn_802E0CC0(&self->inflater, 2);
    fn_80467100(self, inChrg);
}

void *fn_801B25CC(register unsigned int size, register void *p)
{
    return p;
}

stdBigHashedVFS *fn_801B25F8(register FileSys *fs)
{
    return (stdBigHashedVFS *)fs;
}
}
