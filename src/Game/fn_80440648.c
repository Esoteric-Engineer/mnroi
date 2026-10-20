// Teardown of the byte array: free the storage unless the storage is borrowed (docs/versus.md, row 8).

extern int fn_8043FD4C(void *self);
extern void fn_80440C48(int data, int cap, int elemSize);

typedef struct Arr
{
    int data; // +0x0
    int n;    // +0x4
    int cap;  // +0x8
} Arr;

void fn_80440648(register Arr *self)
{
    if ((self->cap & 0x80000000) == 0)
        fn_80440C48(self->data, fn_8043FD4C(self), 0x14);
}
