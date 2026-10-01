typedef unsigned int u32;

extern u32 Spec;
extern void* MakeStatus;
extern u32 __PADSpec;

extern void SPEC0_MakeStatus(void);
extern void SPEC1_MakeStatus(void);
extern void SPEC2_MakeStatus(void);

void PADSetSpec(u32 spec)
{
    __PADSpec = 0;
    switch (spec) {
    case 0:
        MakeStatus = SPEC0_MakeStatus;
        break;
    case 1:
        MakeStatus = SPEC1_MakeStatus;
        break;
    case 2:
    case 3:
    case 4:
    case 5:
        MakeStatus = SPEC2_MakeStatus;
        break;
    }
    Spec = spec;
}
