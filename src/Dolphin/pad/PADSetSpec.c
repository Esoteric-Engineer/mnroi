typedef unsigned int u32;

extern u32 lbl_8066C4A8;
extern void* lbl_8066C4AC;
extern u32 __PADSpec;

extern void SPEC0_MakeStatus(void);
extern void SPEC1_MakeStatus(void);
extern void SPEC2_MakeStatus(void);

void PADSetSpec(u32 spec)
{
    __PADSpec = 0;
    switch (spec) {
    case 0:
        lbl_8066C4AC = SPEC0_MakeStatus;
        break;
    case 1:
        lbl_8066C4AC = SPEC1_MakeStatus;
        break;
    case 2:
    case 3:
    case 4:
    case 5:
        lbl_8066C4AC = SPEC2_MakeStatus;
        break;
    }
    lbl_8066C4A8 = spec;
}
