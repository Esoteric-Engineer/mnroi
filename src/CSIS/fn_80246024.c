// The CSIS allocator's init: records the heap handle once, and fails with -7 if it is already set up.
// Built at -O2 -fno-strength-reduce -G0 (docs/prodg.md, "Middleware"): the globals are reached through lis/lwz, not r13.

extern int lbl_804D853C; // initialized flag
extern int lbl_804D8530; // allocator object
extern int lbl_804D852C; // heap handle
extern int lbl_804D8528; // ready

int fn_80246024(int heap)
{
    if (lbl_804D853C == 0) {
        if (lbl_804D8530 != 0) {
            lbl_804D8530 = 0;
        }
        lbl_804D852C = heap;
        lbl_804D8528 = 1;
        return 0;
    }
    return -7;
}
