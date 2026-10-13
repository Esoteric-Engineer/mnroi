// Per-entity tuning getters (float, int): read slot +0x170 of the record at +0x16C. Row 19 of docs/versus.md.

inline int sn_return_decl(int a) { return a; }

struct Entity {
    char pad0[0x16C];
    char *record; // +0x16C
    int slot;     // +0x170
};

extern "C" float fn_80433D20(char *record, int id, int slot);
extern "C" int fn_80433D70(char *record, int id, int slot);

extern "C" float fn_800B1884(register Entity *self, register int id)
{
    if (self->record == 0)
        return 0.0f;
    return fn_80433D20(self->record, id, self->slot);
}

extern "C" int fn_800B18EC(register Entity *self, register int id)
{
    if (self->record == 0)
        return 0;
    return fn_80433D70(self->record, id, self->slot);
}
