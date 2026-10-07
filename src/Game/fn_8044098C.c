// Teardown of the 12-byte-element array: free the storage unless it is borrowed (docs/versus.md, row 8).

extern int fn_80440D60(void *self);
extern void fn_80440D90(int data, int cap, int elemSize);

typedef struct Arr
{
    int data; // +0x0
    int n;    // +0x4
    int cap;  // +0x8
} Arr;

void fn_8044098C(register Arr *self)
{
    if ((self->cap & 0x80000000) == 0)
        fn_80440D90(self->data, fn_80440D60(self), 0x14);
}
