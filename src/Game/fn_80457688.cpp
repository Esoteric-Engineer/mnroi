// RecArr (guessed name): an array of 0x40-byte named-resource records; the constructor, fn_8045777C (loads one by name) and fn_80457B44 (releases them all) and fn_80457CDC (the same without clearing the used flag).
// HandleA/B/C (guessed names) are the 0x68-byte handle constructors: vptr, then a 0x10-byte impl over fn_8045DB68/DBD4/DC40.

extern "C" int fn_80119398(void *table, int size, void *attr);
extern char lbl_804975BC[];
extern char lbl_80568DF0[0x10];
extern "C" int strcmp(const char *a, const char *b);
extern "C" char *strcpy(char *dst, const char *src);
extern "C" int sprintf(char *buf, const char *fmt, ...);
extern "C" char *fn_801A7C30(void);
extern "C" int fn_801B0C90(char *a, int b, const class Attr &c);
extern "C" void fn_801B0E50(char *, int, int);
extern "C" int fn_802421AC(char *path, int a, long long *b, long long *c);
extern "C" void fn_8011931C(char *a, char *b);
extern "C" int fn_80249E08(char *a, int b, char *c, int d, int e, int f, int (*cb)());
extern "C" int fn_80249F74(void);
extern "C" void fn_800164A0(void);
extern "C" void fn_8023E98C(void);
extern "C" int fn_80111BB8();
extern "C" void fn_8024936C(int handle);
extern "C" void fn_80119404(void *table, int p, int flag);
extern char lbl_80593C58[];
extern char lbl_804975C8[];
extern char lbl_804975D8[];
extern char lbl_804975E8[];
extern char lbl_804975F8[];
extern int lbl_8066C660;
extern int lbl_8066C664;
extern int lbl_8066BD7C;
extern int lbl_8066BD80;

class Attr
{
public:
    int a;                    // +0x0
    const void *b;            // +0x4
    mutable const Attr *link; // +0x8
    Attr(register int a, register const char *b);
    Attr(register int a, register int b);
    const Attr &chain(register const Attr &next) const;
};

struct Rec
{
    int w0;  // +0x0
    int w4;  // +0x4
    int w8;  // +0x8
    int words[4]; // +0xC
    int w1C; // +0x1C
    char pad20[0x20];
};

class RecArr
{
public:
    int count; // +0x0
    Rec *recs; // +0x4
    RecArr(register int n);
};

RecArr::RecArr(register int n)
{
    count = n;
    Attr attr(1, lbl_804975BC);
    recs = (Rec *)fn_80119398(lbl_80568DF0, n * 0x40, &attr);
    for (int i = 0; i < n; i++) {
        recs[i].w0 = 0;
        recs[i].w1C = 0;
        recs[i].w4 = 0;
    }
}

extern "C" void fn_8045777C(register RecArr *self, register char *name, register int flag)
{
    int i;
    int j;
    int h;
    for (i = 0; i < self->count; i++) {
        if (self->recs[i].w0 != 0 && strcmp((char *)&self->recs[i] + 0x20, name) == 0) {
            return;
        }
    }
    for (j = 0; j < self->count; j++) {
        if (self->recs[j].w0 == 0) {
            h = fn_801B0C90(lbl_80593C58, 0x20000, Attr(4, 1).chain(Attr(2, 0x20)).chain(Attr(1, lbl_804975C8)));
            char path[0x40];
            char full[0x40];
            long long sizeA;
            long long sizeB;
            char alt[0x40];
            int ready;
            lbl_8066C664 = flag;
            lbl_8066C660 = flag == 0;
            lbl_8066BD80 = 0;
            lbl_8066BD7C = (int)((char *)&self->recs[j] + 0xC);
            sprintf(path, lbl_804975D8, fn_801A7C30(), name);
            sprintf(full, lbl_804975E8, fn_801A7C30(), name);
            if (fn_802421AC(full, 0, &sizeA, &sizeB) != 0) {
                sprintf(alt, lbl_804975F8, name);
                fn_8011931C(alt, full);
                self->recs[j].w8 = fn_80249E08(path, 0, full, 0, h, 0x20000, fn_80111BB8);
            } else {
                self->recs[j].w8 = fn_80249E08(path, 0, 0, 0, h, 0x20000, fn_80111BB8);
            }
            ready = 0;
            for (;;) {
                ready = fn_80249F74();
                if (ready != 0) {
                    break;
                }
                fn_800164A0();
                fn_8023E98C();
            }
            lbl_8066BD7C = 0;
            self->recs[j].w4 = 1;
            self->recs[j].w0 = 1;
            lbl_8066C660 = 0;
            lbl_8066C664 = 0;
            strcpy((char *)&self->recs[j] + 0x20, name);
            fn_801B0E50(lbl_80593C58, h, 0);
            return;
        }
    }
}

extern "C" void fn_80457B44(register RecArr *self)
{
    for (int i = 0; i < self->count; i++) {
        if (self->recs[i].w0 != 0) {
            if (self->recs[i].w4 != 0) {
                fn_8024936C(self->recs[i].w8);
                self->recs[i].w4 = 0;
            }
            for (int j = 0; j < self->recs[i].w1C; j++) {
                int p = self->recs[i].words[j];
                if (p != 0) {
                    fn_80119404(lbl_80568DF0, p, 0);
                }
            }
            self->recs[i].w1C = 0;
            self->recs[i].w0 = 0;
        }
    }
}

extern "C" void fn_80457CDC(register RecArr *self)
{
    for (int i = 0; i < self->count; i++) {
        if (self->recs[i].w0 != 0) {
            if (self->recs[i].w4 != 0) {
                fn_8024936C(self->recs[i].w8);
                self->recs[i].w4 = 0;
            }
            for (int j = 0; j < self->recs[i].w1C; j++) {
                int p = self->recs[i].words[j];
                if (p != 0) {
                    fn_80119404(lbl_80568DF0, p, 0);
                }
            }
            self->recs[i].w1C = 0;
        }
    }
}

extern "C" void fn_80457E58(register RecArr *self)
{
    for (int i = 0; i < self->count; i++) {
        if (self->recs[i].w0 != 0 && self->recs[i].w4 == 0) {
            self->recs[i].w0 = 0;
            fn_8045777C(self, (char *)&self->recs[i] + 0x20, 1);
            self->recs[i].w4 = 1;
        }
    }
}

extern char lbl_804F2E28[];

class ImplA
{
public:
    char data[0x10];
    ImplA(register const void *name) __asm__("fn_8045DB68");
};

class HandleA
{
public:
    ImplA *impl;      // +0x0
    const void *vptr; // +0x4
    HandleA(register const void *name);
};

HandleA::HandleA(register const void *name)
{
    vptr = lbl_804F2E28;
    impl = new ImplA(name);
}

extern char lbl_804F3148[];
extern char lbl_804F2E40[];

class ImplB
{
public:
    char data[0x10];
    ImplB(register const void *name) __asm__("fn_8045DBD4");
};

class ImplC
{
public:
    char data[0x10];
    ImplC(register const void *name) __asm__("fn_8045DC40");
};

class HandleB
{
public:
    ImplB *impl;      // +0x0
    const void *vptr; // +0x4
    HandleB(register const void *name);
};

class HandleC
{
public:
    ImplC *impl;      // +0x0
    const void *vptr; // +0x4
    HandleC(register const void *name);
};

HandleB::HandleB(register const void *name)
{
    vptr = lbl_804F3148;
    impl = new ImplB(name);
}

HandleC::HandleC(register const void *name)
{
    vptr = lbl_804F2E40;
    impl = new ImplC(name);
}

class WordTriple
{
public:
    int a; // +0x0
    int b; // +0x4
    int c; // +0x8
    WordTriple();
};

WordTriple::WordTriple()
{
    a = 0;
    b = 0;
    c = 0;
}
