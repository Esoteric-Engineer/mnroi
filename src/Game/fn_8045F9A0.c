// Block's release: drops the count at +0x24 and, at zero, calls the vtable entry at +0x30 with 3 (docs/versus.md section 5).
typedef struct VEntry
{
    short delta;
    short index;
    void *pfn; // +0x4
} VEntry;

typedef struct Block
{
    VEntry *vptr; // +0x0
    int pad[8];
    int refs; // +0x24
} Block;

int fn_8045F9A0(register Block *self)
{
    if (--self->refs <= 0) {
        if (self != 0) {
            register VEntry *e = self->vptr + 6;
            ((void (*)(void *, int))e->pfn)((char *)self + e->delta, 3);
        } else {
        }
        return 0;
    }
    return self->refs;
}
