typedef unsigned char u8;
typedef unsigned long u32;

extern u32 lbl_8066F3D0;
extern u8 lbl_8057D418[];

int OSDisableInterrupts(void);
void OSRestoreInterrupts(int level);
void fn_801885DC(void* horVer, void* tfbb, void* bfbb, void* rtfbb, void* rbfbb);

void VISetNextFrameBuffer(void* fb)
{
    int enabled;
    u8* tbl = lbl_8057D418;

    enabled = OSDisableInterrupts();
    *(u32*)(tbl + 0x120) = (u32)fb;
    lbl_8066F3D0 = 1;
    fn_801885DC(tbl + 0xF0, tbl + 0x124, tbl + 0x128, tbl + 0x13C, tbl + 0x140);
    OSRestoreInterrupts(enabled);
}
