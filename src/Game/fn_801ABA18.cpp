// Memory manager: VM and OS heap setup, the tagged allocator, operator new and delete (docs/core.md row 2).
// Owns the .rodata from "MC:VM" (0x8049D960).

inline int sn_return_decl(int a) { return a; }

struct HeapClass {
    char name[0x20]; // +0x00
    int f20;         // +0x20 heap id
    void *f24;       // +0x24 base, 0 when free
    int f28;         // +0x28 total (fn_8023FDBC)
    int f2C;         // +0x2C
    int f30;         // +0x30 total less used
};

struct HeapPick {
    int heap; // +0x0
    int cls;  // +0x4
};

extern "C" {
void VMInit(int a, int b, int c);
void *VMAlloc(int addr, int size);
void VMSetLogStatsCallback(void (*cb)(int, int, int, int, int));
void *OSGetArenaLo(void);
void *OSGetArenaHi(void);
void *OSInitAlloc(void *lo, void *hi, int n);
void OSSetArenaLo(void *lo);
int OSCreateHeap(void *lo, void *hi);
int OSSetCurrentHeap(int heap);
void *OSAllocFromHeap(int heap, unsigned int size);
extern volatile int __OSCurrHeap;

void fn_80219808(int n);
int fn_8023F604(void);
void fn_8023F378(int id, const char *name, void *base, unsigned int size, int a, int b, int c, int d);
void fn_8023EC38(void);
int fn_801AC3B4(const char *name, unsigned int size, int n);
void fn_8023FB4C(int id);
int fn_8023FD34(int id);
int fn_8023FDBC(int id);
void OSReport(const char *fmt, ...);
void fn_801AC1E0(int i);
void fn_801ACE18(unsigned int *total, unsigned int *used);
char *strncpy(char *dst, const char *src, unsigned int n);
void *fn_8023F2F8(const char *name, unsigned int size, int flags);
void *fn_8023F2D4(const char *name, unsigned int size, int align, int a, int heap);
void *fn_8023F328(const char *name, unsigned int size, int heap);
void *fn_801AC9EC(unsigned int size, const char *name, int c, int kind, int align, int f);
void fn_80245584(void *a, void *b, unsigned int n);
void fn_8024538C(void *a, void *b, unsigned int n);
void fn_8023F63C(void *p);
int fn_8023FCE8(void *p);
int fn_8023FCF0(void *p);
void fn_8023FE2C(void *p, unsigned int size);
void fn_8023F58C(int id);
void *fn_801AD37C(unsigned int size, const char *name, int c, int align);

extern void *lbl_8066C66C;       // main heap block
extern int lbl_8066C670;         // VM base
extern int lbl_8066C674;         // VM heap id
extern int lbl_8066C678;         // the MC:SMALL class
extern int lbl_8066C67C;         // current class, -99 for none
extern int lbl_8066C680;         // current ARAM class, -99 for none
extern int lbl_8066C688;         // initialised
extern unsigned int lbl_8066C68C; // main heap size
extern int lbl_8066C698;         // main heap id
extern int lbl_8066C660;
extern int lbl_8066C664;
extern char lbl_804D398C[];       // tag override
extern HeapClass lbl_80593940[5];
extern HeapClass lbl_80593A44[5];

void fn_801ABA18(int a, int b, int c, int d, int e)
{
}

int fn_801ABA48(void)
{
    void *lo = 0;
    void *hi = 0;
    int i;
    int j;

    if (lbl_8066C688 != 0) {
        return 1;
    }
    VMInit(0x100000, 0x800000, 0x7FC000);
    fn_80219808(0);
    lbl_8066C670 = 0x7E000000;
    VMAlloc(0x7E000000, 0x7FC000);
    VMSetLogStatsCallback(fn_801ABA18);
    lbl_8066C674 = fn_8023F604();
    fn_8023F378(lbl_8066C674, "MC:VM", (void *)lbl_8066C670, 0x7FC000, 0x20, 0x80, 0, 0x800);
    lo = OSGetArenaLo();
    hi = OSGetArenaHi();
    lo = OSInitAlloc(lo, hi, 1);
    OSSetArenaLo(lo);
    lo = (void *)(((unsigned int)lo + 0x1F) & ~0x1F);
    hi = (void *)((unsigned int)hi & ~0x1F);
    lbl_8066C68C = (unsigned int)hi - (unsigned int)lo - 0x10000;
    OSSetCurrentHeap(OSCreateHeap(lo, hi));
    OSSetArenaLo(lo = hi);
    lbl_8066C66C = OSAllocFromHeap(__OSCurrHeap, lbl_8066C68C);
    lbl_8066C698 = 0;
    fn_8023F378(lbl_8066C698, "default", lbl_8066C66C, lbl_8066C68C, 0x10, 0x10, 0, 0x800);
    fn_8023EC38();
    for (i = 0; i <= 4; i++) {
        lbl_80593940[i].name[0] = 0;
        lbl_80593940[i].f20 = -99;
        lbl_80593940[i].f24 = 0;
        lbl_80593940[i].f28 = 0;
        lbl_80593940[i].f2C = 0;
        lbl_80593940[i].f30 = 0;
    }
    for (j = 0; j <= 4; j++) {
        lbl_80593A44[j].name[0] = 0;
        lbl_80593A44[j].f20 = -99;
        lbl_80593A44[j].f24 = 0;
        lbl_80593A44[j].f28 = 0;
        lbl_80593A44[j].f2C = 0;
        lbl_80593A44[j].f30 = 0;
    }
    lbl_8066C678 = fn_801AC3B4("MC:SMALL", 0x200000, 2);
    lbl_8066C688 = 1;
    return 1;
}

void fn_801ABDB4(int i)
{
    float ratio;

    if (lbl_80593A44[i].f24 == 0) {
        return;
    }
    fn_8023FB4C(lbl_80593A44[i].f20);
    ratio = 1.0f - (float)fn_8023FD34(lbl_80593A44[i].f20) / (float)fn_8023FDBC(lbl_80593A44[i].f20);
    OSReport("*****************************************************\n", 0, 0, 0, 0);
    OSReport("ARAM_CLASS: %s Actual(%d KB/%d KB) fragRatio:%.2f \n", lbl_80593A44[i].name,
             fn_8023FD34(lbl_80593A44[i].f20) / 1024, fn_8023FDBC(lbl_80593A44[i].f20) / 1024, ratio);
    OSReport("*****************************************************\n", 0, 0, 0, 0);
}

void fn_801ABFA4(void)
{
    float ratio;
    int i;
    int j;
    unsigned int total;
    unsigned int used;

    fn_8023FB4C(lbl_8066C698);
    fn_8023FB4C(lbl_8066C674);
    ratio = 1.0f - (float)fn_8023FD34(lbl_8066C698) / (float)fn_8023FDBC(lbl_8066C698);
    for (i = 0; i <= 4; i++) {
        if (lbl_80593940[i].f24 != 0) {
            fn_801AC1E0(i);
        }
    }
    for (j = 0; j <= 4; j++) {
        if (lbl_80593A44[j].f24 != 0) {
            fn_801ABDB4(j);
        }
    }
    fn_801ACE18(&total, &used);
    OSReport("*****************************************************\n", 0, 0, 0, 0);
    OSReport("CLASS: Main Heap (%d KB/%d KB) fragRatio:%.2f \n", fn_8023FD34(lbl_8066C698) / 1024,
             fn_8023FDBC(lbl_8066C698) / 1024, ratio, 0);
    OSReport("CLASS: Virt Heap (%d KB/%d KB)\n", used / 1024, total / 1024, 0, 0);
    OSReport("*****************************************************\n", 0, 0, 0, 0);
}

void fn_801AC1E0(int i)
{
    float ratio;

    if (lbl_80593940[i].f24 == 0) {
        return;
    }
    ratio = 1.0f - (float)fn_8023FD34(lbl_80593940[i].f20) / (float)fn_8023FDBC(lbl_80593940[i].f20);
    OSReport("*****************************************************\n", 0, 0, 0, 0);
    OSReport("CLASS: %s Actual(%d KB/%d KB) fragRatio:%.2f \n", lbl_80593940[i].name,
             fn_8023FD34(lbl_80593940[i].f20) / 1024, fn_8023FDBC(lbl_80593940[i].f20) / 1024, ratio);
    OSReport("*****************************************************\n", 0, 0, 0, 0);
}

__asm__(".section .rodata\n\t.long 0\n\t.long 0x43300000\n\t.long 0x80000000\n\t.long 0x3F800000\n\t.text"); // orphan pool 0x8049DA94

int fn_801AC3B4(const char *name, unsigned int size, int kind)
{
    int flags = 0x500;
    int i;

    if (kind == 2) {
        flags = 0x400;
    }
    for (i = 0; i <= 4; i++) {
        if (lbl_80593940[i].f24 == 0) {
            strncpy(lbl_80593940[i].name, name, 0x20);
            lbl_80593940[i].name[0x1F] = 0;
            lbl_80593940[i].f24 = fn_8023F2F8(name, size, flags);
            lbl_80593940[i].f20 = fn_8023F604();
            lbl_80593940[i].f2C = 0;
            fn_8023F378(lbl_80593940[i].f20, lbl_80593940[i].name, lbl_80593940[i].f24, size, 0x10, 0x10, 0, 0x800);
            lbl_80593940[i].f28 = fn_8023FDBC(lbl_80593940[i].f20);
            lbl_80593940[i].f30 = lbl_80593940[i].f28 - fn_8023FD34(lbl_80593940[i].f20);
            return i;
        }
    }
    return -99;
}

void fn_801AC5F8(int cls)
{
    lbl_8066C67C = cls;
}

void fn_801AC620(void)
{
    lbl_8066C67C = -99;
}

void fn_801AC644(int a, int b)
{
}

void fn_801AC668(HeapPick *out, int size)
{
    HeapClass *small;

    out->heap = lbl_8066C698;
    out->cls = -99;
    small = &lbl_80593940[lbl_8066C678];
    if (size <= 0x44C) {
        out->heap = small->f20;
        out->cls = lbl_8066C678;
    } else if (lbl_8066C67C != -99) {
        HeapClass *cur = &lbl_80593940[lbl_8066C67C];
        out->heap = cur->f20;
        out->cls = lbl_8066C67C;
    }
}

void fn_801AC72C(void *p, const char *name, int size)
{
    if (p == 0) {
        fn_801ABFA4();
        OSReport("!!!!!!!!!!  OUT OF MEMORY!!!  MALLOC requested name:%s size:%d\n", name, size, 0, 0);
        while (1) {
        }
    }
}

void *fn_801AC7A0(HeapPick *pick, const char *name, unsigned int size, int align, int flags)
{
    void *p = 0;
    int i;

    for (i = 0; i <= 4; i++) {
        if (pick->cls != i && i != lbl_8066C678 && lbl_80593940[i].f24 != 0) {
            pick->cls = i;
            pick->heap = lbl_80593940[i].f20;
            if (align != 0) {
                p = fn_8023F2D4(name, size, align, 0, pick->heap | flags);
            } else {
                p = fn_8023F328(name, size, pick->heap | flags);
            }
            if (p != 0) {
                break;
            }
        }
    }
    if (p == 0) {
        pick->cls = 0;
        pick->heap = lbl_8066C698;
        if (align != 0) {
            p = fn_8023F2D4(name, size, align, 0, lbl_8066C698 | flags);
        } else {
            p = fn_8023F328(name, size, lbl_8066C698 | flags);
        }
    }
    return p;
}

void *fn_801AC988(unsigned int size, const char *name, int align, int flags)
{
    return fn_801AC9EC(size, name, align, flags, 0, 0);
}

void *fn_801AC9EC(unsigned int size, const char *name, int c, int kind, int align, int f)
{
    void *p;
    unsigned int sz;
    int unused = 0;
    const char *tag;
    int flags;
    HeapPick pick;

    if (lbl_8066C688 == 0) {
        fn_801ABA48();
    }
    sz = size;
    tag = lbl_804D398C[0] == 0 ? name : lbl_804D398C;
    flags = kind == 1 ? 0x100 : 0;
    if (lbl_8066C664 != 0) {
        flags = 0x100;
    } else if (lbl_8066C660 != 0) {
        flags = 0;
    }
    fn_801AC668(&pick, sz);
    if (align != 0) {
        p = fn_8023F2D4(tag, sz, align, 0, pick.heap | flags);
    } else {
        p = fn_8023F328(tag, sz, pick.heap | flags);
    }
    if (p == 0) {
        p = fn_801AC7A0(&pick, tag, sz, align, flags);
    }
    fn_801AC72C(p, tag, sz);
    return p;
}

void fn_801ACB7C(void *a, void *b, unsigned int n)
{
    fn_80245584(a, b, n);
}

void fn_801ACBC4(void *a, void *b, unsigned int n)
{
    fn_8024538C(a, b, n);
}

void fn_801ACC0C(void *p)
{
    fn_8023F63C(p);
}

void fn_801ACC44(void *p)
{
    fn_8023F63C(p);
}

void *fn_801ACC7C(void *p, unsigned int size, const char *name, int flags)
{
    unsigned int have; // never set in the original
    unsigned int old;
    unsigned int now;
    int kind;
    void *q;

    if (p == 0) {
        return fn_801AC988(size, name, 0, flags);
    }
    if (size == 0) {
        fn_801ACC0C(p);
        return 0;
    }
    old = fn_8023FCE8(p);
    if (size <= 0x10) {
        if (size > have || have > 0x10) {
            size = 0x10;
        } else {
            return p;
        }
    }
    fn_8023FE2C(p, size);
    now = fn_8023FCE8(p);
    if (now == size) {
        fn_801AC644((int)p, now - have);
        return p;
    }
    kind = fn_8023FCF0(p);
    q = fn_801AC988(size, name, 0, kind == 0x100 ? 1 : 2);
    if (q == 0) {
        return 0;
    }
    fn_8024538C(q, p, size);
    fn_8023F63C(p);
    return q;
}

void fn_801ACE18(unsigned int *total, unsigned int *used)
{
    *total = fn_8023FDBC(lbl_8066C674);
    *used = fn_8023FD34(lbl_8066C674);
}

void fn_801ACE74(const char *tag)
{
    if (tag != 0) {
        strncpy(lbl_804D398C, tag, 0x20);
        lbl_804D398C[0x1F] = 0;
    }
}
}

void *operator new(register __SIZE_TYPE__ size)
{
    if (lbl_8066C688 == 0) {
        fn_801ABA48();
    }
    return fn_801AC988(size, "new", 0, 2);
}

void *operator new[](register __SIZE_TYPE__ size)
{
    if (lbl_8066C688 == 0) {
        fn_801ABA48();
    }
    return fn_801AC988(size, "new[]", 0, 2);
}

void operator delete(register void *p)
{
    fn_801ACC0C(p);
}

void operator delete[](register void *p)
{
    fn_801ACC0C(p);
}

extern "C" {
int fn_801AD00C(const char *name, unsigned int size, int kind)
{
    int flags = 0x500;
    int i;

    if (kind == 2) {
        flags = 0x400;
    }
    for (i = 0; i <= 4; i++) {
        if (lbl_80593940[i].f24 == 0) { // tests the main table, fills the ARAM one
            HeapClass *c = &lbl_80593A44[i];
            strncpy(c->name, name, 0x20);
            c->name[0x1F] = 0;
            c->f24 = fn_8023F2F8(name, size, flags | lbl_8066C674);
            c->f20 = fn_8023F604();
            c->f2C = 0;
            fn_8023F378(c->f20, c->name, c->f24, size, 0x10, 0x10, 0, 0x800);
            c->f28 = fn_8023FDBC(c->f20);
            c->f30 = c->f28 - fn_8023FD34(c->f20);
            return i;
        }
    }
    return -99;
}

void fn_801AD19C(int cls)
{
    lbl_8066C680 = cls;
}

void fn_801AD1C4(void)
{
    lbl_8066C680 = -99;
}

void fn_801AD1E8(int *cls)
{
    HeapClass *c = &lbl_80593A44[*cls];

    if (lbl_80593A44[*cls].f24 != 0) {
        fn_8023F63C(lbl_80593A44[*cls].f24);
    }
    lbl_80593A44[*cls].f24 = 0;
    lbl_80593A44[*cls].f30 = 0;
    lbl_80593A44[*cls].f2C = 0;
    fn_8023F58C(lbl_80593A44[*cls].f20);
    lbl_80593A44[*cls].f20 = -99;
    *cls = -99;
}

void *fn_801AD324(unsigned int size, const char *name, int c)
{
    return fn_801AD37C(size, name, c, 0);
}

void *fn_801AD37C(unsigned int size, const char *name, int c, int align)
{
    void *p;
    HeapPick pick;

    if (lbl_8066C688 == 0) {
        fn_801ABA48();
    }
    pick.heap = lbl_8066C674;
    if (lbl_8066C680 != -99) {
        HeapClass *cur = &lbl_80593A44[lbl_8066C680];
        pick.heap = cur->f20;
        pick.cls = lbl_8066C680;
    }
    if (align != 0) {
        p = fn_8023F2D4(name, size, align, 0, pick.heap | 0x400);
    } else {
        p = fn_8023F328(name, size, pick.heap | 0x400);
    }
    if (p == 0) {
        return fn_801AC9EC(size, name, c, align, 0, 0);
    }
    return p;
}
}

struct SinkObj {
    void *vtable; // +0x0, 0x804F6768
    int f4;       // +0x4
};

extern "C" {
void fn_80168690(SinkObj *obj);
void fn_801686E4(SinkObj *obj, int inChrg);
}

SinkObj lbl_8066F4F4;

static void __static_initialization_and_destruction_0(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            fn_80168690(&lbl_8066F4F4);
        } else {
            fn_801686E4(&lbl_8066F4F4, 2);
        }
    }
}

extern "C" {
void fn_801AD510(void)
{
    __static_initialization_and_destruction_0(1, 65535);
}

void fn_801AD54C(void)
{
    __static_initialization_and_destruction_0(0, 65535);
}
}

static void (*const sCtorEntry)(void) __attribute__((section(".ctors"))) = fn_801AD510;
static void (*const sDtorEntry)(void) __attribute__((section(".dtors"))) = fn_801AD54C;
