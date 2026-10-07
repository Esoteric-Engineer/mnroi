// Array constructor and teardown of the byte array family (docs/versus.md, row 8).

extern int fn_80440490(void *self);
extern void fn_80440E18(int data, int cap, int elemSize);

typedef struct Arr
{
    int data; // +0x0
    int n;    // +0x4
    int cap;  // +0x8
} Arr;

Arr *fn_80440B38(register Arr *self)
{
    self->data = 0;
    self->n = 0;
    self->cap = 0x80000000;
    return self;
}

void fn_80440B78(register Arr *self)
{
    if ((self->cap & 0x80000000) == 0)
        fn_80440E18(self->data, fn_80440490(self), 0x14);
}
