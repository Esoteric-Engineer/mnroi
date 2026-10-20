// The two voice type-ID lookups through lbl_804CF638, docs/characters.md section 5.

extern int lbl_804CF638[];

int fn_80118CB4(register int id)
{
    if (id >= 0 && id <= 40) {
        return lbl_804CF638[id];
    } else {
        return 0;
    }
}

int fn_80118D0C(register int id)
{
    if (id >= 0 && id <= 40) {
        return lbl_804CF638[id];
    } else {
        return 0;
    }
}
