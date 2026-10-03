// Character roster field accessors, called by clashCharSelect_GetCharList.
// Built at -O0; the file may continue before or after this range.

// One roster entry (field offsets confirmed by fn_80431CCC.c).
typedef struct CharacterRecord
{
    char entityName[0x20];
    char nameKey[0x20];
    signed char stats[6];
    signed char unk46[2];
    int unlocked;
} CharacterRecord;

extern CharacterRecord *fn_80431CCC(register int index, register int remap, register int alt);

char *fn_8044B1D4(register int index, register int remap, register int alt)
{
    CharacterRecord *rec = fn_80431CCC(index, remap, alt);
    return rec->nameKey;
}

char fn_8044B234(register int index, register int remap, register int alt)
{
    CharacterRecord *rec = fn_80431CCC(index, remap, alt);
    return rec->stats[0];
}

char fn_8044B298(register int index, register int remap, register int alt)
{
    CharacterRecord *rec = fn_80431CCC(index, remap, alt);
    return rec->stats[1];
}

char fn_8044B2FC(register int index, register int remap, register int alt)
{
    CharacterRecord *rec = fn_80431CCC(index, remap, alt);
    return rec->stats[2];
}

char fn_8044B360(register int index, register int remap, register int alt)
{
    CharacterRecord *rec = fn_80431CCC(index, remap, alt);
    return rec->stats[3];
}

char fn_8044B3C4(register int index, register int remap, register int alt)
{
    CharacterRecord *rec = fn_80431CCC(index, remap, alt);
    return rec->stats[4];
}

char fn_8044B428(register int index, register int remap, register int alt)
{
    CharacterRecord *rec = fn_80431CCC(index, remap, alt);
    return rec->stats[5];
}

int fn_8044B48C(register int index, register int remap, register int alt)
{
    CharacterRecord *rec = fn_80431CCC(index, remap, alt);
    return rec->unlocked;
}
