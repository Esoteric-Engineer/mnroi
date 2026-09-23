typedef unsigned int u32;

extern u32 lbl_8066C4A8;
extern void* lbl_8066C4AC;
extern u32 lbl_8066F404;

extern void fn_8018ACE0(void);
extern void fn_8018AE54(void);
extern void fn_8018AFC8(void);

void PADSetSpec(u32 spec)
{
    lbl_8066F404 = 0;
    switch (spec) {
    case 0:
        lbl_8066C4AC = fn_8018ACE0;
        break;
    case 1:
        lbl_8066C4AC = fn_8018AE54;
        break;
    case 2:
    case 3:
    case 4:
    case 5:
        lbl_8066C4AC = fn_8018AFC8;
        break;
    }
    lbl_8066C4A8 = spec;
}
