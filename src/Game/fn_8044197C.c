// Teardown of the int array: free the storage unless it is borrowed (docs/versus.md, row 8).

extern int fn_8044194C(void *self);
extern void fn_80441A4C(int data, int cap, int elemSize);

typedef struct Arr
{
    int data; // +0x0
    int n;    // +0x4
    int cap;  // +0x8
} Arr;

void fn_8044197C(register Arr *self)
{
    if ((self->cap & 0x80000000) == 0)
        fn_80441A4C(self->data, fn_8044194C(self), 0x14);
}
