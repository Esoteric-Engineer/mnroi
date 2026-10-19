// Role-index tests: G+0x774 / G+0x770 greater than 0. See docs/versus.md (section 5, row 25).

extern char lbl_80552110[]; // the game-state object G

extern int fn_80432870(void *g);
extern int fn_80432844(void *g);

int fn_8013086C(void)
{
    return fn_80432870(lbl_80552110) > 0;
}

int fn_801308C0(void)
{
    return fn_80432844(lbl_80552110) > 0;
}
