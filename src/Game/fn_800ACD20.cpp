// Per-entity tuning getter (entity, id): reads the record at +0x16C. Row 19 of docs/versus.md.

extern "C" {
int fn_800B0C58(void *self);
void *fn_800B14A0(void *self);
int fn_80085DCC(void *actor);
int fn_80445C4C(void *rec, int id, int slot);
}

struct Ent {
    char pad[0x16C];
    void *rec; // +0x16C
    int slot; // +0x170
};

extern "C" int fn_800ACD20(register Ent *self, int id)
{
    if (self->rec == 0)
        return 0;
    if (fn_800B0C58(self) && fn_80085DCC(fn_800B14A0(self)))
        return fn_80445C4C(self->rec, id, 5);
    else
        return fn_80445C4C(self->rec, id, self->slot);
}
