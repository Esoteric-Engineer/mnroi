// Teardown of the int array: free the storage unless it is borrowed (docs/versus.md, row 8).

extern int fn_8043FDCC(void *self);
extern void fn_80440CD4(int data, int cap, int elemSize);

typedef struct Arr
{
    int data; // +0x0
    int n;    // +0x4
    int cap;  // +0x8
} Arr;

void fn_80440718(register Arr *self)
{
    if ((self->cap & 0x80000000) == 0)
        fn_80440CD4(self->data, fn_8043FDCC(self), 0x14);
}
