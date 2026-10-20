// Accessors and constructors of a Body family (class names and layouts guessed); see docs/versus.md, row 8.

inline int sn_return_decl(int a)
{
    return a;
}

extern "C" void __6Vector(void *self);
extern "C" void fn_804388D8(void *self, int v);
extern "C" void fn_80438900(void *self, int v);
extern "C" char lbl_804F32D0[];
extern "C" char lbl_804F32A8[];
extern "C" char lbl_804F3280[];

extern "C" int lbl_8066B7D0;
extern "C" void fn_80438928(void *self, void *a, void *b, float s);
extern "C" void *fn_8042FA34();
extern "C" int fn_8004A2FC(int a, int b, int c, int d, int e, int f);
extern "C" void fn_804379BC(void *a, int b);
extern "C" void fn_804379E0(void *a, int b, int c);
extern "C" void fn_80434988(void *self);
extern "C" void *memset(void *p, int c, unsigned n);

struct Entry
{
    int kind;
    int value;
    int pad8[2];
    char vec[0x10]; // +0x10
    float scale;    // +0x20
    int pad24[3];
} __attribute__((aligned(8)));

struct Queue
{
    char pad[0x40];
    Entry entries[0x80];
    unsigned count; // +0x1840
};

extern "C" Entry *fn_8004E3C4(void *self, float s);

struct Slot
{
    char pad[0xD8];
    int tag; // +0xD8
    char pad2[0x1C0 - 0xDC];
};

class Placement
{
public:
    char data[0x40];
    Placement();
};

class Body
{
public:
    char data[0x88];
    Body(void *src);
};

class BodyA : public Body
{
public:
    const void *vptr; // +0x88
    int pad8C;
    Placement placement; // +0x90
    BodyA(void *src);
};

class BodyB : public Body
{
public:
    const void *vptr; // +0x88
    int pad8C;
    Placement placement; // +0x90
    BodyB(void *src);
};

class BodyC : public Body
{
public:
    const void *vptr; // +0x88
    int pad8C;
    int slot90;
    int slot94;
    int pad98[2];
    Placement placement; // +0xA0
    int slotE0;
    BodyC(void *src, int a, int b, int c);
};

extern "C" void *fn_80437378(register char *self)
{
    return self + 0x40;
}

extern "C" int fn_804373A4(register char *self)
{
    return *(int *)(self + 0x80);
}

extern "C" int fn_804373D0(register char *self)
{
    return *(int *)(self + 0x84);
}

BodyA::BodyA(register void *src) : Body(src), vptr(lbl_804F32D0)
{
}

extern "C" void *fn_8043745C(register char *self)
{
    return self + 0x90;
}

BodyB::BodyB(register void *src) : Body(src), vptr(lbl_804F32A8)
{
}

extern "C" void *fn_804374E8(register char *self)
{
    return self + 0x90;
}

extern "C" void *fn_80437514(register char *self)
{
    return self + 0xA0;
}

extern "C" void fn_80437540(register Queue *self, register int a, register float s)
{
    if (self->count > 0x7f)
    {
        Entry *e = fn_8004E3C4(self, s);
        if (e)
        {
            e->kind = 1;
            e->value = a;
            e->scale = s;
            memset(e->vec, 0, 0x10);
        }
        else
        {
        }
        return;
    }
    self->entries[self->count].kind = 1;
    self->entries[self->count].value = a;
    self->entries[self->count].scale = s;
    memset(self->entries[self->count].vec, 0, 0x10);
    self->count = self->count + 1;
}

extern "C" void fn_8043764C(register Queue *self, register int a, register float s)
{
    if (self->count > 0x7f)
    {
        Entry *e = fn_8004E3C4(self, s);
        if (e)
        {
            e->kind = 2;
            e->value = a;
            e->scale = s;
            memset(e->vec, 0, 0x10);
        }
        else
        {
        }
        return;
    }
    self->entries[self->count].kind = 2;
    self->entries[self->count].value = a;
    self->entries[self->count].scale = s;
    memset(self->entries[self->count].vec, 0, 0x10);
    self->count = self->count + 1;
}

extern "C" void fn_80437758(register void *unused, register char *obj)
{
    *(int *)(obj + 0xD8) = lbl_8066B7D0;
}

extern "C" int fn_80437784(register void *unused, register char *obj)
{
    return *(int *)(obj + 0xD8) == lbl_8066B7D0;
}

class VectorTriple
{
public:
    VectorTriple(void *a, void *b, float s);
};

VectorTriple::VectorTriple(register void *a, register void *b, register float s)
{
    __6Vector(this);
    __6Vector((char *)this + 0x10);
    __6Vector((char *)this + 0x20);
    fn_80438928(this, a, b, s);
}

BodyC::BodyC(register void *src, register int a, register int b, register int c) : Body(src), vptr(lbl_804F3280)
{
    fn_804388D8(this, a);
    fn_80438900(this, b);
    slotE0 = c;
}

struct SlotList
{
    char pad[0xC];
    unsigned count; // +0xC
    char pad2[0x12C - 0x10];
    Slot *slots; // +0x12C
};

extern "C" void fn_804378CC(register SlotList *self)
{
    if (++lbl_8066B7D0 == 0)
    {
        lbl_8066B7D0++;
        unsigned i = 0;
        while (i < self->count)
        {
            self->slots[i].tag = 0;
            i++;
        }
    }
}

extern "C" void *fn_80437960(register char *self)
{
    return self + 0x50;
}

extern "C" int fn_8043798C(register char *self)
{
    return *(unsigned int *)self & 1;
}

extern "C" void fn_804379BC(register void *a, register int b)
{
}

extern "C" void fn_804379E0(register void *a, register int b, register int c)
{
}

extern "C" int fn_80437A08(register char *self)
{
    return **(int **)(self + 4);
}

class ShapeDataPair
{
public:
    ShapeDataPair();
};

ShapeDataPair::ShapeDataPair()
{
    fn_80434988(this);
    fn_80434988((char *)this + 0x10);
    *(int *)((char *)this + 0x20) = 0;
    *(int *)((char *)this + 0x24) = 0;
}

extern "C" int fn_80437A94(register void *a, register int b)
{
    return 0;
}

extern "C" int fn_80437AC0(register int a, register int b, register int c, register int d, register int e, register int f)
{
    fn_804379BC(fn_8042FA34(), 0x25);
    int result = fn_8004A2FC(a, b, c, d, e, f);
    fn_804379E0(fn_8042FA34(), 0x25, 1);
    return result;
}
