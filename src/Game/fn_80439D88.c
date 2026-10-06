// Streamer's operator delete (the destructor's in-charge tail calls it); lbl_80593C58 is the object fn_80438FAC passes to fn_801B0C90.

extern char lbl_80593C58[];
extern void fn_801B0E50(char *, void *, int);

void fn_80439D88(register void *p)
{
    fn_801B0E50(lbl_80593C58, p, 0);
}
