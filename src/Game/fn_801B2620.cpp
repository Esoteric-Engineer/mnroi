// stdBitmap: creates its registry and keeps the table of tuning classes fn_801B26DC fills; docs/core.md row 7.
// Owns the .rodata "stdBitmap" (0x8049E4DC).

extern "C" {
extern void *lbl_8066C6C0;           // the "stdBitmap" registry
extern int lbl_8066C6C4;
extern unsigned int lbl_8066C6CC;    // entries in lbl_80593C70
extern void *lbl_80593C70[32];
void *fn_801B4284(int hint, char *name);

void fn_801B2620(void)
{
    lbl_8066C6C0 = fn_801B4284(0x22D, "stdBitmap");
    lbl_8066C6C4 = 0;
}

inline int sn_return_decl(int a) { return a; }

void fn_801B2674(void *cls)
{
    if (cls == 0)
        return;
    if (lbl_8066C6CC < 32)
    {
        lbl_80593C70[lbl_8066C6CC] = cls;
        lbl_8066C6CC++;
        return;
    }
}
}
