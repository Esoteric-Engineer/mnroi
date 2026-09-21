typedef unsigned long u32;
typedef unsigned char u8;
typedef int BOOL;

volatile u32 __EXIRegs[0x40] : 0xCC006800;

extern BOOL OSDisableInterrupts(void);
extern void OSRestoreInterrupts(BOOL enabled);
extern void __OSMaskInterrupts(u32 mask);

extern u8* lbl_8066F4D0;
extern u8 lbl_8066F4D4;
extern void (*lbl_8066F4C0)(void);

void DBInitComm(u8** flagPtr, void (*callback)(void))
{
    BOOL enabled = OSDisableInterrupts();
    lbl_8066F4D0 = &lbl_8066F4D4;
    *flagPtr = lbl_8066F4D0;
    lbl_8066F4C0 = callback;
    __OSMaskInterrupts(0x18000);
    __EXIRegs[10] = 0;
    OSRestoreInterrupts(enabled);
}
