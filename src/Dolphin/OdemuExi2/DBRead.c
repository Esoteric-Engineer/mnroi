typedef unsigned long u32;
typedef unsigned char u8;
typedef int BOOL;

extern BOOL OSDisableInterrupts(void);
extern void OSRestoreInterrupts(BOOL enabled);
extern BOOL fn_80196464(u32 param1, u32* data, int byte_size);

extern u32 lbl_8066F4C8;
extern int lbl_8066F4CC;
extern u8 lbl_8066F4D4;

int DBRead(void* param1, u32 param2)
{
    BOOL enabled;
    u32 lVar3;

    enabled = OSDisableInterrupts();
    if (lbl_8066F4C8 & 0x10000) {
        lVar3 = 0x1000;
    } else {
        lVar3 = 0;
    }
    fn_80196464(lVar3 + 0x1e000, param1, (param2 + 3U) & 0xfffffffc);
    lbl_8066F4CC = 0;
    lbl_8066F4D4 = 0;
    OSRestoreInterrupts(enabled);
    return 0;
}
