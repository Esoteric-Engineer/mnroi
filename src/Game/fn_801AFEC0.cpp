// File back end: the open-file record behind the stdio-style layer, read through two 64 KB async blocks (docs/core.md row 5).
// The record's fields are in docs/core.md section 4.1.

inline int sn_return_decl(int a) { return a; }

class Attr {
public:
    int a;                    // +0x0
    const void *b;            // +0x4
    mutable const Attr *link; // +0x8
    Attr(int a, int b);
    const Attr &chain(const Attr &next) const;
};

class Sink { // BufferAllocator's base
public:
    virtual void *alloc(unsigned int size, const Attr &attrs);
    virtual void free(void *p, const Attr *attrs);
};

struct Block {
    int req;   // +0x0, async read request
    char *buf; // +0x4
    Block() __asm__("fn_80466A0C");
};

class FileRec {
public:
    int *f0;               // +0x000
    int *f4;               // +0x004
    int *f8;               // +0x008
    char *path;            // +0x00C
    unsigned int *size;    // +0x010
    int handle;            // +0x014
    char name[0x100];      // +0x018
    int open;              // +0x118
    unsigned int readPos;  // +0x11C
    long long time;        // +0x120
    unsigned int fsize;    // +0x128
    unsigned int pos;      // +0x12C
    int cur;               // +0x130
    int base;              // +0x134
    int off;               // +0x138
    int avail;             // +0x13C
    Block blk[2];          // +0x140
    char *mem;             // +0x150
    int f154;              // +0x154
    FileRec();
};

#define NBLK (sizeof ((FileRec *)0)->blk / sizeof ((FileRec *)0)->blk[0])

extern "C" {
unsigned int strlen(const char *s);
char *strcpy(char *dst, const char *src);
void *memchr(const void *s, int c, unsigned int n);
const char *fn_801A7C30(void);
int fn_80244404(const char *path, int a, int b);
void fn_80242244(int handle, long long *time, long long *size);
unsigned int fn_802444E8(int handle, int n);
int fn_80244120(int req);
void fn_8024538C(void *dst, const void *src, int n);
void fn_80245AEC(void *p, unsigned int n);
int fn_80243EC0(int handle, unsigned int offset, char *buf, unsigned int len);
int fn_80243F94(int req);
void fn_80243FFC(int req, int a, int *avail);
void fn_800164A0(void);
int fn_8046655C(void);
int fn_80122228(void);
void fn_80125538(int p);
void fn_8023E98C(void);
void fn_801B0558(register FileRec *self, int n);
int fn_801B07CC(register FileRec *self);
void fn_801B0920(register FileRec *self, int n);

extern Sink *lbl_8066C6B8;

void fn_801AFEC0(Sink *p)
{
    lbl_8066C6B8 = p;
}
}

__asm__(".text\n\t.globl fn_801AFEE8\n\t.type fn_801AFEE8,@function\nfn_801AFEE8:");
FileRec::FileRec()
    : f0(&open), f4(&handle), f8(&handle), path(name), size(&fsize), handle(0), open(0), readPos(0),
      fsize(0), pos(0), cur(0), base(0), off(0), avail(0), mem(0)
{
}
__asm__(".size fn_801AFEE8, 0xF4");

extern "C" {
int fn_801AFFDC(register FileRec *self, const char *path, int a, int b)
{
    self->handle = fn_80244404(path, a, b);
    if (self->handle != 0) {
        long long size;
        strcpy(self->name, path + strlen(fn_801A7C30()));
        fn_80242244(self->handle, &self->time, &size);
        self->fsize = size;
        self->pos = 0;
        self->readPos = 0;
        self->open = 1;
    }
    return self->handle;
}

void fn_801B00AC(register FileRec *self, int n)
{
    if (self->open == 0) {
        return;
    }
    int r = fn_802444E8(self->handle, n);
    for (int i = 0; i < NBLK; i++) {
        if (self->blk[i].req != 0) {
            fn_80244120(self->blk[i].req);
            self->blk[i].req = 0;
        }
    }
    if (self->mem != 0) {
        lbl_8066C6B8->free(self->mem, 0);
        self->mem = 0;
    }
    self->handle = 0;
    self->open = 0;
}

unsigned int fn_801B01D4(register FileRec *self, char *ptr, unsigned int size, unsigned int count)
{
    if (self->pos >= self->fsize || !self->open || !self->handle) {
        return 0;
    }
    if (self->pos == 0) {
        fn_801B0558(self, 0);
    }
    int total = size * count;
    unsigned int got = count;
    int rem = self->fsize - self->pos;
    if (total > rem) {
        total = rem;
        got = total / size;
    }
    while (total > 0) {
        if (!fn_801B07CC(self)) {
            return 0;
        }
        if (self->avail <= 0) {
            return 0;
        }
        int n = self->avail > total ? total : self->avail;
        char *const &src = self->blk[self->cur].buf + self->off;
        fn_8024538C(ptr, src, n);
        fn_801B0920(self, n);
        total -= n;
        ptr += n;
    }
    return got;
}

char *fn_801B0380(register FileRec *self, char *buf, int n)
{
    int left = 0;
    char *out;
    char *cr;
    if (self->pos < self->fsize) {
        left = self->fsize - self->pos;
    }
    if (!left || !self->open || !self->handle) {
        return 0;
    }
    if (self->pos == 0) {
        fn_801B0558(self, 0);
    }
    out = buf;
    while (left != 0) {
        if (!fn_801B07CC(self)) {
            return 0;
        }
        char *const &src = self->blk[self->cur].buf + self->off;
        int cnt = self->avail > n ? n : self->avail;
        fn_8024538C(out, src, cnt);
        if ((cr = (char *)memchr(out, 13, cnt)) != 0) {
            *cr = 0;
            int k = cr - out + 2;
            fn_801B0920(self, k);
            return buf;
        }
        fn_801B0920(self, cnt);
        out += cnt;
        left -= cnt;
        n -= cnt;
    }
    return buf;
}
}

inline void sn_label_decl() { clear:; }

extern "C" {
void fn_801B0558(register FileRec *self, int n)
{
    if (self->mem == 0) {
        register const unsigned int bytes = 0x20000;
        self->mem = (char *)lbl_8066C6B8->alloc(bytes, Attr(4, 0).chain(Attr(2, 0x20)));
        fn_80245AEC(self->mem, bytes);
        for (int i = 0; i < NBLK; i++) {
            *&self->blk[i].buf = self->mem + i * 0x10000;
        }
    }
    self->readPos = n * 0x10000;
    for (int i = n; i < NBLK; i++) {
        int idx = i & 1;
        if (self->blk[idx].req != 0) {
            fn_80244120(self->blk[idx].req);
        }
        if (self->readPos < self->fsize) {
            unsigned int len = self->fsize - self->readPos > 0x10000 ? 0x10000 : self->fsize - self->readPos;
            self->blk[idx].req = fn_80243EC0(self->handle, self->readPos, self->blk[idx].buf, len);
            self->readPos += len;
        } else {
            self->blk[idx].req = 0;
        }
    }
    self->base = n;
    self->cur = self->base & 1;
    self->off = self->pos & 0xFFFF;
    self->avail = 0;
}

int fn_801B07CC(register FileRec *self)
{
    if (self->blk[self->cur].req != 0) {
        while (self->blk[self->cur].req != 0) {
            int st = fn_80243F94(self->blk[self->cur].req);
            switch (st) {
            case 1:
                fn_80243FFC(self->blk[self->cur].req, 0, &self->avail);
                self->avail -= self->off;
                self->blk[self->cur].req = 0;
                break;
            case 0:
                fn_800164A0();
                if (fn_8046655C() != 0) {
                    fn_80125538(fn_80122228());
                }
                fn_8023E98C();
                break;
            case -1:
                return 0;
            }
        }
    }
    return 1;
}

void fn_801B0920(register FileRec *self, int n)
{
    self->off += n;
    self->pos += n;
    self->avail -= n;
    if (self->avail <= 0 && self->pos < self->fsize) {
        int blkno = self->pos / 0x10000;
        int d = blkno - self->base;
        int cnt = d > NBLK ? NBLK : d;
        int start = self->base + 2;
        if (cnt > NBLK) {
            self->readPos = start * 0x10000;
        }
        for (int i = start; i < start + cnt; i++) {
            int idx = i & 1;
            if (self->blk[idx].req != 0) {
                fn_80244120(self->blk[idx].req);
            }
            if (self->readPos < self->fsize) {
                unsigned int len = self->fsize - self->readPos > 0x10000 ? 0x10000 : self->fsize - self->readPos;
                self->blk[idx].req = fn_80243EC0(self->handle, self->readPos, self->blk[idx].buf, len);
                self->readPos += len;
            } else {
                self->blk[idx].req = 0;
            }
        }
        self->base += d;
        self->cur = self->base & 1;
        self->off = self->pos & 0xFFFF;
        self->avail = 0;
    }
}
}
