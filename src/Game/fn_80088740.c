// A second entry point on the .nsc script table.
// Looks up the record the table is currently on and does nothing else, the rest being a release-stripped diagnostic like the empty if below.

typedef struct NameTable NameTable;
typedef struct ScriptTable ScriptTable;

extern int fn_80431DB0(ScriptTable *table); // table->unk1A4
extern NameTable *fn_804332C4(ScriptTable *table, int index);

void fn_80088740(register ScriptTable *table, void *actor, int flag)
{
    int unused = 0;
    NameTable *rec = fn_804332C4(table, fn_80431DB0(table));

    if (!flag) {
    }
}
