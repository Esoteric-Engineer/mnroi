// Character roster table accessor.
// Built at -O0; the file may continue before or after 0x80431CCC.

// One roster entry (field offsets confirmed by this function).
typedef struct CharacterRecord
{
    char entityName[0x20];
    char nameKey[0x20];
    signed char stats[6];
    signed char unk46[2];
    int unlocked;
} CharacterRecord;

extern CharacterRecord lbl_804CA51C[20]; // normal costumes
extern CharacterRecord lbl_804CAB0C[20]; // alternate costumes
extern int lbl_804CB0FC[20];             // select-screen order -> roster index

CharacterRecord *fn_80431CCC(register int index, register int remap, register int alt)
{
    CharacterRecord *table = lbl_804CA51C;
    if (alt == 1)
        table = lbl_804CAB0C;

    if (remap != 0)
    {
        return &table[lbl_804CB0FC[index]];
    }

    return &table[index];
}
