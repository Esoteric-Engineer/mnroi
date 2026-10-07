// Capacity getter and the array teardown that frees owned storage (docs/versus.md, row 8).

extern void fn_804407E8(int data, int cap, int elemSize);

typedef struct Arr
{
    int data; // +0x0
    int n;    // +0x4
    int cap;  // +0x8
} Arr;

int fn_8043FEC0(register Arr *self)
{
    return self->cap & 0x3FFFFFFF;
}

void fn_8043FEF0(register Arr *self)
{
    if ((self->cap & 0x80000000) == 0)
        fn_804407E8(self->data, fn_8043FEC0(self), 0x14);
}
