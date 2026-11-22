// The memory-card device's inline functions (docs/core.md row 18).
// Pools in the device's .rodata from 0x8049D8D8 (extern_pool).

inline int sn_return_decl(int a) { return a; }

struct Slot {
    int chan;
    unsigned short flags;
    unsigned short pad6;
    int memSize;
    int sectorSize;
    unsigned long long serial;
    Slot() __asm__("fn_80466664");
};

struct Card {
    Slot slots[2];
    char f30[0x10];
    Card();
};

__asm__(".text\n\t.globl fn_804665F0\n\t.type fn_804665F0,@function\nfn_804665F0:");
Card::Card()
{
}
__asm__(".size fn_804665F0, 0x74");

extern "C" Slot *fn_80466664(register Slot *self)
{
    self->flags = 0;
    return self;
}

extern "C" {
double ceil(double x);
int fn_804667FC(register Slot *self);

int fn_80466694(register Slot *self, register int size)
{
    return (int)(float)ceil((float)size / fn_804667FC(self)) * fn_804667FC(self);
}

int fn_80466764(register Slot *self, register int size)
{
    return (int)(float)ceil((float)size / 512.0f) * 512;
}

int fn_804667FC(register Slot *self)
{
    return self->sectorSize;
}
}
