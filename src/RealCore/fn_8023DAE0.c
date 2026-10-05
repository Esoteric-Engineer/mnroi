// RealCore 6.27: one pass over the 8 registered callbacks.
// Built at -O2 (docs/prodg.md, "Middleware").

extern int lbl_8066C888; // passes run
extern int lbl_8066C88C; // callback slots visited
extern void (*lbl_804D7D70[8])(void);

void fn_8023DAE0(void)
{
    int i;

    lbl_8066C888++;
    for (i = 0; i < 8; i++) {
        lbl_8066C88C++;
        if (lbl_804D7D70[i]) {
            lbl_804D7D70[i]();
        }
    }
}
