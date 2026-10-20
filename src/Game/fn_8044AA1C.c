// String-array owner helpers: sub-object destructor and vtable-entry getter; see docs/versus.md.
typedef struct VEntry
{
    short delta;
    short index;
    void *pfn; // +0x4
} VEntry;

typedef struct VTable
{
    char pad[0xA0];
    VEntry *entries; // +0xA0
} VTable;

extern void fn_8044A5B4(void *self);

void fn_8044AA1C(register void *self)
{
    fn_8044A5B4(self);
}

void *fn_8044AA54(register VTable *self, register int index)
{
    return self->entries[index].pfn;
}
