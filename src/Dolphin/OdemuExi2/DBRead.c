typedef unsigned long u32;
typedef unsigned char u8;
typedef int BOOL;

extern BOOL OSDisableInterrupts(void);
extern void OSRestoreInterrupts(BOOL enabled);
extern BOOL DBGRead(u32 param1, u32* data, int byte_size);

u8 lbl_8066F4D4;
u8* lbl_8066F4D0;
int lbl_8066F4CC;
u32 lbl_8066F4C8;
void (*lbl_8066F4C4)(short interrupt, void* context);
void (*lbl_8066F4C0)(void);

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
    DBGRead(lVar3 + 0x1e000, param1, (param2 + 3U) & 0xfffffffc);
    lbl_8066F4CC = 0;
    lbl_8066F4D4 = 0;
    OSRestoreInterrupts(enabled);
    return 0;
}
