// BufferAllocator: a Sink that hands out blocks from one heap over its own buffer (docs/core.md row 5).
// Owns the .rodata from "BufferAllocator" (0x8049E3AC); the vtable 0x804F67D0 (_vt.15BufferAllocator) stays unclaimed.

struct Attr { // RealCore attribute list entry
    unsigned int key; // +0x0
    int value;        // +0x4
    Attr *next;       // +0x8
};

class Sink { // only its slots: fn_801B0C90, fn_801B0E50, fn_801B0E90, fn_801B0EC8, then the destructor
public:
    Sink();
    virtual void *alloc(unsigned int size, Attr *attrs);
    virtual void free(void *p, Attr *attrs);
    virtual int addRef();
    virtual int release();
    virtual ~Sink();
};

class BufferAllocator : public Sink {
public:
    char *buf;        // +0x04
    int heap;         // +0x08
    int cls;          // +0x0C
    int used;         // +0x10
    int refs;         // +0x14
    BufferAllocator(unsigned int size);
    virtual ~BufferAllocator(); // fn_801B0C00, written below as a plain function
};

struct BufAlloc { // the same object, for the plain functions
    const void *vptr; // +0x00
    char *buf;        // +0x04
    int heap;         // +0x08
    int cls;          // +0x0C
    int used;         // +0x10
    int refs;         // +0x14
};

extern "C" {
void fn_8045E2A4(BufAlloc *self, int inChrg);
void *fn_801AC988(unsigned int size, const char *tag, int line, int kind);
void fn_801ACC0C(void *p);
int fn_8023F604(void);
int fn_8023F378(int id, const char *name, void *base, unsigned int size, int a, int b, int c, int d);
int fn_8023FDBC(int id);
void fn_8023FB4C(int id);
void fn_8023F58C(int id);
void *fn_8023F2D4(const char *name, unsigned int size, int align, int a, int heap);
void *fn_8023F328(const char *name, unsigned int size, int heap);
void fn_8023F63C(void *p);
BufAlloc *fn_801B0B40(BufAlloc *self, unsigned int size);
void fn_801B0C00(register BufAlloc *self, int inChrg);

extern char sVtable[] __asm__("_vt.15BufferAllocator");

BufAlloc lbl_80593C58;

}

__asm__(".text\n\t.globl fn_801B0B40\n\t.type fn_801B0B40,@function\nfn_801B0B40:");
BufferAllocator::BufferAllocator(unsigned int size)
    : buf((char *)fn_801AC988(size, "BufferAllocator", 34, 2)), heap(0), cls(0), refs(1)
{
    heap = fn_8023F604();
    cls = fn_8023F378(heap, "BuffMan", buf, size, 0x20, 0x80, 0, 0x800);
}
__asm__(".size fn_801B0B40, 0xC0");

extern "C" {
void fn_801B0C00(register BufAlloc *self, int inChrg)
{
    self->vptr = sVtable;
    if (self->used != fn_8023FDBC(self->heap)) {
        fn_8023FB4C(self->heap);
    }
    fn_8023F58C(self->heap);
    if (self->buf != 0) {
        fn_801ACC0C(self->buf);
        self->buf = 0;
    }
    fn_8045E2A4(self, inChrg);
}

void *fn_801B0C90(register BufAlloc *self, unsigned int size, Attr *attrs)
{
    int align = 0;
    int b = 0;
    int flags = 0;
    const char *tag = "BufferAllocator";
    const char *file = "c:/Clash/mainline/Code/Std/BufferAllocator.cpp";
    int line = 140;
    Attr *a;
    void *p;

    for (a = attrs; a != 0; a = a->next) {
        switch (a->key) {
        case 2:
            align = a->value;
            break;
        case 3:
            b = a->value;
            break;
        case 4:
            if (a->value > 0) {
                flags = 0x100;
            }
            break;
        case 1:
            tag = (const char *)a->value;
            break;
        case 5:
            file = (const char *)a->value;
            break;
        case 6:
            line = a->value;
            break;
        }
    }
    p = 0;
    if (align > 0) {
        p = fn_8023F2D4(tag, size, align, b, self->heap | flags);
    } else {
        p = fn_8023F328(tag, size, self->heap | flags);
    }
    return p;
}

void fn_801B0E50(register BufAlloc *self, void *p, Attr *attrs)
{
    fn_8023F63C(p);
}

int fn_801B0E90(register BufAlloc *self)
{
    return ++self->refs;
}

int fn_801B0EC8(register BufAlloc *self)
{
    if (--self->refs == 0) {
        delete (Sink *)self;
    }
    return self->refs;
}
}

// 65535 is GCC 2.95's default init priority.
static void __static_initialization_and_destruction_0(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            fn_801B0B40(&lbl_80593C58, 0x60400);
        } else {
            fn_801B0C00(&lbl_80593C58, 2);
        }
    }
}

extern "C" {
void fn_801B0FD4(void)
{
    __static_initialization_and_destruction_0(1, 65535);
}

void fn_801B1010(void)
{
    __static_initialization_and_destruction_0(0, 65535);
}

static void (*const sCtorEntry)(void) __attribute__((section(".ctors"))) = fn_801B0FD4;
static void (*const sDtorEntry)(void) __attribute__((section(".dtors"))) = fn_801B1010;
}
