// The small-object allocator, the class row 15's wrapper builds (docs/core.md row 18).

inline int sn_return_decl(int a) { return a; }

class Empty {
};

struct Alloc {
    char c;
};

struct Node {
    Node *next;
};

class SOABins {
public:
    Alloc alloc;
    unsigned int size[20];
    int count[20];
    unsigned int maxSize;
    SOABins(register Alloc a);
};

class SOA {
public:
    SOABins bins;
    Node *freeList[20];    // +0x0A8
    unsigned int end[20];  // +0x0F8, each bin's end offset in the pool
    char *pool;            // +0x148
    unsigned int poolSize; // +0x14C
    int peak[20];          // +0x150
    int used[20];          // +0x1A0
    int requests[20];      // +0x1F0
    int overflows[20];     // +0x240
    Empty a0;              // +0x290, the pool
    Alloc a1;              // +0x291, the fill byte
    Alloc a2;              // +0x292, the fallback
    Alloc a3;              // +0x293, sizes over 0x800
    int ready;             // +0x294
    SOA(register int tag, register SOABins *src, register Empty a, register Alloc b, register Alloc c,
        register Alloc d);
};

extern "C" {
void *memset(void *dst, int c, unsigned int n);
void fn_801ACC0C(void *p);
void *fn_801AC988(unsigned int size, int tag, int line, int kind);
void __builtin_delete(void *p);
void fn_80467E58(register SOA *self, register SOABins *src, register int tag);
void fn_80467CC0(register SOA *self);
int fn_80467F30(register SOA *self, register char *p);
void fn_80467FC0(register SOA *self, register char *p, register int i);
void *fn_804680C4(register SOA *self, register int *pi, register unsigned int size, register int tag);
int fn_80467AD8(register void *self);
void fn_80467B00(register void *self, register void *p);
void *fn_80467B3C(register void *self, register unsigned int size, register int tag);
int fn_80467B90(register SOABins *self, register unsigned int size);
int fn_80467BF8(register SOA *self, register int i);
unsigned int fn_80467C5C(register SOA *self, register int i);
unsigned int fn_804682EC(register SOA *self);
void *fn_80468294(register void *self, register unsigned int size, register int tag);
void fn_80468388(register SOA *self);
void fn_80468520(register SOA *self, register unsigned int size);
}

__asm__(".text\n\t.globl fn_80467494\n\t.type fn_80467494,@function\nfn_80467494:");
SOABins::SOABins(register Alloc a) : alloc(a), maxSize(0)
{
    int i;
    for (i = 0; i < 20; i++) {
        size[i] = 0x7FFFFFFF;
        count[i] = 0;
    }
}
__asm__(".size fn_80467494, 0xA4");

extern "C" void fn_80467538(register SOABins *self, register unsigned int size, register int count)
{
    int i;
    i = fn_80467B90(self, size);
    if (i >= 0 && i <= 19) {
        self->count[i] = count;
        self->size[i] = size;
        if (self->maxSize < size) {
            self->maxSize = size;
        }
    }
}

__asm__(".text\n\t.globl fn_804675D4\n\t.type fn_804675D4,@function\nfn_804675D4:");
SOA::SOA(register int tag, register SOABins *src, register Empty a, register Alloc b, register Alloc c,
         register Alloc d)
    : bins(Alloc()), freeList(), end(), pool(0), poolSize(0), peak(), used(), a0(a), a1(b), a2(c), a3(d), ready(0)
{
    int i;
    if (src) {
        fn_80467E58(this, src, tag);
    }
    if (0) {
        for (i = 0; i < 20; i++) {
            peak[i] = 0;
            used[i] = 0;
            overflows[i] = 0;
            requests[i] = 0;
        }
    }
}
__asm__(".size fn_804675D4, 0x1D0");

extern "C" {
void fn_804677A4(register SOA *self, register int inChrg)
{
    fn_80467CC0(self);
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}

void fn_804677F8(register SOA *self, register char *p)
{
    int i;
    if (p == 0) {
        return;
    }
    if (p < self->pool || p >= self->pool + self->poolSize) {
        fn_80467B00(&self->a2, p);
        return;
    }
    i = fn_80467F30(self, p);
    fn_80467FC0(self, p, i);
}

void *fn_80467894(register SOA *self, register unsigned int size, register int tag)
{
    unsigned int sz = size;
    int i;
    void *p;

    if (sz > 0x800) {
        return fn_80467B3C(&self->a3, sz, tag);
    }
    i = sz & 3;
    if (i) {
        sz = sz + (4 - i);
    }
    if (0) {
    } else {
    }
    i = fn_80467B90(&self->bins, sz);
    if (0) {
        self->requests[i]++;
    }
    p = fn_804680C4(self, &i, sz, tag);
    if (p) {
        return p;
    }
    p = self->freeList[i];
    self->freeList[i] = self->freeList[i]->next;
    if (0) {
        self->used[i]++;
        if (self->used[i] > self->peak[i]) {
            self->peak[i] = self->used[i];
        }
    }
    if (0) {
        memset(p, fn_80467AD8(&self->a1), fn_80467C5C(self, i));
    }
    return p;
}

int fn_80467AD8(register void *self)
{
    return 0xD;
}

void fn_80467B00(register void *self, register void *p)
{
    fn_801ACC0C(p);
}

void *fn_80467B3C(register void *self, register unsigned int size, register int tag)
{
    return fn_80468294(self, size, tag);
}

int fn_80467B90(register SOABins *self, register unsigned int size)
{
    int i = 0;
    while (size > self->size[i]) {
        i++;
    }
    return i;
}

int fn_80467BF8(register SOA *self, register int i)
{
    if (self->bins.size[i] == 0x7FFFFFFF) {
        return 0;
    }
    return self->bins.count[i];
}

unsigned int fn_80467C5C(register SOA *self, register int i)
{
    if (self->bins.size[i] == 0x7FFFFFFF) {
        return 0;
    }
    return self->bins.size[i];
}

void fn_80467CC0(register SOA *self)
{
    int i;
    Node *n;
    Node *next;
    int j;

    if (0) {
        for (i = 0; i < 20; i++) {
            if (self->used[i] > 0) {
                n = self->freeList[i];
                next = 0;
                while (n) {
                    next = n->next;
                    n->next = (Node *)0xDEFECA7E;
                    n = next;
                }
                if (i == 0) {
                    n = (Node *)self->pool;
                } else {
                    n = (Node *)(self->pool + self->end[i - 1]);
                }
                for (j = 0; j < fn_80467BF8(self, i); j++) {
                    if (n->next != (Node *)0xDEFECA7E) {
                    }
                    n = (Node *)((char *)n + fn_80467C5C(self, i));
                }
            }
        }
    }
    fn_80467B00(&self->a0, self->pool);
    self->pool = 0;
    self->ready = 0;
}

void fn_80467E58(register SOA *self, register SOABins *src, register int tag)
{
    if (self->ready) {
        fn_80467CC0(self);
    }
    self->bins = *src;
    self->poolSize = fn_804682EC(self);
    self->pool = (char *)fn_80468294(&self->a0, self->poolSize, tag);
    fn_80468388(self);
    self->ready = 1;
}

int fn_80467F30(register SOA *self, register char *p)
{
    unsigned int off = p - self->pool;
    int i = 19;
    while (i > 0) {
        if (self->end[i - 1] <= off) {
            return i;
        }
        i--;
    }
    return 0;
}

void fn_80467FC0(register SOA *self, register char *p, register int i)
{
    Node *n;
    if (0) {
        n = self->freeList[i];
        while (n) {
            n = n->next;
        }
    }
    if (0) {
        memset(p, fn_80467AD8(&self->a1), fn_80467C5C(self, i));
    }
    n = (Node *)p;
    n->next = self->freeList[i];
    self->freeList[i] = (Node *)p;
    if (0) {
        self->used[i]--;
    }
}

void *fn_804680C4(register SOA *self, register int *pi, register unsigned int size, register int tag)
{
    if (0) {
        if (self->freeList[*pi] == 0) {
            self->overflows[*pi]++;
            if (0) {
                fn_80468520(self, size);
            }
            return fn_80467B3C(&self->a2, size, tag);
        }
    } else {
        for (; *pi <= 19 && self->freeList[*pi] == 0; (*pi)++) {
            self->overflows[*pi]++;
            if (0) {
                self->requests[*pi]++;
            }
            continue;
        }
        if (*pi == 20) {
            if (0) {
                fn_80468520(self, size);
            }
            return fn_80467B3C(&self->a2, size, tag);
        }
    }
    return 0;
}

void *fn_80468294(register void *self, register unsigned int size, register int tag)
{
    return fn_801AC988(size, tag, 0, 2);
}

unsigned int fn_804682EC(register SOA *self)
{
    unsigned int total = 0;
    int i;
    for (i = 0; i < 20; i++) {
        total += fn_80467BF8(self, i) * fn_80467C5C(self, i);
    }
    return total;
}

void fn_80468388(register SOA *self)
{
    unsigned int off = 0;
    int i;
    for (i = 0; i < 20; i++) {
        if (fn_80467BF8(self, i) == 0) {
            self->freeList[i] = 0;
        } else {
            char *p = self->pool + off;
            Node *last = 0;
            unsigned int n = fn_80467BF8(self, i);
            int sz = fn_80467C5C(self, i);
            unsigned int j;
            for (j = 0; j < n; j++) {
                last = (Node *)p;
                last->next = (Node *)(p + sz);
                p += sz;
            }
            if (n) {
                last->next = 0;
            }
            self->freeList[i] = (Node *)(self->pool + off);
            off = off + fn_80467BF8(self, i) * sz;
        }
        self->end[i] = off;
    }
}

void fn_80468520(register SOA *self, register unsigned int size)
{
    int i;
    if (0) {
        for (i = 0; i < 20; i++) {
            if (!fn_80467BF8(self, i)) {
                continue;
            }
        }
    }
}
}
