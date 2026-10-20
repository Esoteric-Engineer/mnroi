// RealCore 6.27: one pass over the 8 registered callbacks.
// Built at -O2 (docs/prodg.md, "Middleware").

extern volatile int lbl_8066C888; // passes run
extern volatile int lbl_8066C88C; // bumped once per pass too, before the loop
extern void (*lbl_804D7D70[8])(void);

void fn_8023DAE0(void)
{
    int i;

    lbl_8066C888++;
    lbl_8066C88C++;
    for (i = 0; i < 8; i++) {
        if (lbl_804D7D70[i]) {
            lbl_804D7D70[i]();
        }
    }
}
