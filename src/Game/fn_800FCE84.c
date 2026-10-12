// Template system init: allocates the "gameTemplate" buffers and loads Misc/Global.not; docs/versus.md section 5, row 11.

extern void *fn_801B4284(int size, const char *tag);
extern int fn_800FCF50(const char *name);
extern void *memset(void *p, int c, unsigned n);

extern char lbl_8048FA08[]; // "gameTemplate - Files"
extern char lbl_8048FA20[]; // "gameTemplate - Templates"
extern char lbl_8048FA3C[]; // "global"
extern char lbl_80565860[];
extern int lbl_8066BAF4;
extern void *lbl_8066BAF0;
extern void *lbl_8066BAE4;
extern int lbl_8066BAEC;

int fn_800FCE84(void)
{
    lbl_8066BAF4 = 0x12C0;
    lbl_8066BAF0 = fn_801B4284(0x20, lbl_8048FA08);
    lbl_8066BAE4 = fn_801B4284(0x200, lbl_8048FA20);
    if (!lbl_8066BAE4 || !lbl_8066BAF0) {
        return 0;
    }
    memset(lbl_80565860, 0, 0x100);
    lbl_8066BAF4 = 0;
    if (!fn_800FCF50(lbl_8048FA3C)) {
    }
    lbl_8066BAEC = 1;
    return 1;
}
