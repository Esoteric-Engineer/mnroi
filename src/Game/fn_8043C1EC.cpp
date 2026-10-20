// Forwarder through the actor's sub-object handle, two constructors, then pair-less accessors (docs/versus.md, row 8).
// Class names are guesses. The pool 0x804873B4 is read through extern_pool.

class Handle
{
public:
    virtual void v0();
    virtual void v1();
    virtual int v2();
};

extern "C" {
void *fn_8032A228(void *self);
void *fn_80435340(void *self);
int fn_8043CA98(register Handle *self);

int fn_8043C1EC(register void *self)
{
    return fn_8043CA98((Handle *)fn_80435340(fn_8032A228(self)));
}
}

extern "C" void fn_80434988(void *self);
extern "C" void fn_8043B954(void *self);
extern "C" void fn_804363B8(void *self);
extern "C" void fn_8043C84C(void *self);

class Extent
{
public:
    float lo; // +0x0
    float hi; // +0x4
    Extent();
};

Extent::Extent()
{
    lo = 0.0f;
    hi = 0.0f;
    fn_80434988((char *)this + 0x10);
    fn_8043B954((char *)this + 0x20);
    fn_804363B8((char *)this + 0x10);
    fn_8043C84C((char *)this + 0x20);
}

class Byte1
{
public:
    char value;
    Byte1();
};

class ByteSet
{
public:
    char pad[0x10];
    Byte1 first[3]; // +0x10
    Byte1 second[3]; // +0x13
    Byte1 a; // +0x16
    Byte1 b; // +0x17
    Byte1 c; // +0x18
    Byte1 d; // +0x19
    ByteSet();
};

ByteSet::ByteSet()
{
}

extern "C" {
void fn_80234CFC(void *self, int a);
extern char lbl_804F3CD8[];

struct Entry18 {
    char pad[0xB];
    unsigned char kind; // +0xB
    char tail[0xC];
} __attribute__((aligned(4)));

struct Table {
    char pad[0x20];
    Entry18 entries[1]; // +0x20, 0x18 bytes each
};

struct Holder {
    char pad0[4];
    Table *table; // +0x4
    char pad1[0x35];
    unsigned char index; // +0x3D
};

struct Holder48 {
    char pad[0x48];
    unsigned char flag; // +0x48
};

struct HolderB {
    char pad[4];
    Holder48 *sub; // +0x4
};

unsigned char fn_8043C3C0(register Holder *self)
{
    return self->table->entries[self->index].kind;
}

unsigned short fn_8043C404(register char *self)
{
    return (unsigned short)(*(unsigned short *)(self + 0x18) & 1);
}

unsigned short fn_8043C438(register char *self)
{
    return (unsigned short)(*(unsigned short *)(self + 0x18) & 2);
}

unsigned char fn_8043C46C(register HolderB *self)
{
    return self->sub->flag;
}

void *fn_8043C4A0(register void *self)
{
    *(char **)self = lbl_804F3CD8;
    return self;
}

void fn_8043C4D4(register void *self, register int a)
{
    fn_80234CFC(self, a);
}
}

class ObjA
{
public:
    char data[0xFC];
    ObjA();
};

class ObjB
{
public:
    char data[0x120];
    ObjB();
};

extern "C" {
double __ieee754_acos(double x);

ObjA *fn_8043C514(void)
{
    return new ObjA;
}

void fn_8043C564(register void *self, register int a)
{
    fn_8043C4D4(self, a);
}

ObjB *fn_8043C5A4(void)
{
    return new ObjB;
}

void fn_8043C5F4(register char *self, register int value)
{
    *self = value;
}

}

Byte1::Byte1()
{
}

extern "C" {
float fn_8043C648(register float x)
{
    return __ieee754_acos(x);
}

float fn_8043C69C(register float *self, register int i)
{
    return self[i];
}

void fn_8043C6D8(register float *self, register float s, register float *v)
{
    float t = s;
    self[0] = self[0] - t * v[0];
    self[1] = self[1] - t * v[1];
    self[2] = self[2] - t * v[2];
    self[3] = self[3] - t * v[3];
}

float fn_8043C764(register float *a, register float *b)
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
}

float fn_8043CCAC(register float *self);
void fn_80436454(register float *self, register float s);
void fn_8043C4D4(void *self, int a);
void fn_8043C564(void *self, int a);
float fn_80438CC8(float x);

void fn_8043C7CC(register float *self)
{
    fn_80436454(self, fn_8043CCAC(self));
}

void *fn_8043C814(register char *self, register int i)
{
    return self + i * 0x10;
}

void *fn_8043BAA0(void *self, int i);
void fn_8043632C(void *dst, void *src);

void fn_8043C84C(register void *self)
{
    char tmp[0x10];
    fn_80434988(tmp);
    fn_804363B8(tmp);
    fn_8043632C(fn_8043BAA0(self, 0), tmp);
    fn_8043632C(fn_8043BAA0(self, 1), tmp);
    fn_8043632C(fn_8043BAA0(self, 2), tmp);
}

void fn_8043C8E0(register char *self, register int a)
{
    *(int *)(self + 0x8) = a;
}

void fn_8043C908(register void *self)
{
}

void fn_8043C928(register void *self, register int a)
{
}

void fn_8043C94C(register void *self, register int a, register int b, register int c)
{
}

int fn_8043C978(register void *self, register int a, register int b, register float f, register int c)
{
    return 0;
}

void fn_8043C9B0(register void *self, register int a, register int b, register int c)
{
}

int fn_8043C9DC(register void *self, register int a, register float f, register float g)
{
    return 0;
}

struct IntList {
    int *items; // +0x0
    int count; // +0x4
};

int fn_8043CA10(register IntList *self, register int *key)
{
    int i;
    i = 0;
    while (i < self->count) {
        if (self->items[i] == *key) {
            return i;
        }
        i++;
    }
    return -1;
}

int fn_8043CA98(register Handle *self)
{
    switch (self->v2()) {
    case 2:
    case 12:
    case 13:
    case 16:
        return 1;
    default:
        return 0;
    }
}

inline int sn_return_decl(int a)
{
    return a;
}

void fn_8043CB38(register void *self, register int a)
{
}

void fn_8043CB5C(register void *self, register int a, register int b)
{
}
}

extern "C" void fn_8005E8B4(void *self);
extern "C" void fn_800613E4(void *self);
extern char lbl_804F3EA8[];
extern char lbl_804F3D68[];

ObjA::ObjA()
{
    fn_8005E8B4(this);
    *(char **)((char *)this + 0x58) = lbl_804F3EA8;
    *(int *)((char *)this + 0x5C) = 1;
}

ObjB::ObjB()
{
    fn_800613E4(this);
    *(char **)((char *)this + 0x58) = lbl_804F3D68;
    *(int *)((char *)this + 0x5C) = 5;
}

extern "C" {
void fn_8043CC2C(register void *self, register int a)
{
    fn_8043C4D4(self, a);
}

void fn_8043CC6C(register void *self, register int a)
{
    fn_8043C564(self, a);
}
}
