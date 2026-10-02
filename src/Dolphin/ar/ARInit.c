typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*ARCallback)(void);
typedef struct OSContext OSContext;

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int level);
extern void OSRegisterVersion(char* version);
extern void __OSSetInterruptHandler(int interrupt, void (*handler)(int, OSContext*));
extern u32 __OSUnmaskInterrupts(u32 mask);
extern void __ARHandler(int exception, OSContext* context);
extern void __ARChecksize(void);

char lbl_804EEEF8[] = "<< Dolphin SDK - AR\trelease build: Apr 17 2003 12:33:55 (0x2301) >>";
static char* __ARVersion = lbl_804EEEF8;

extern ARCallback __AR_Callback;
extern u32 __AR_StackPointer;
extern u32 __AR_FreeBlocks;
extern u32* __AR_BlockLength;
extern int __AR_init_flag;

volatile u16 __DSPRegs[0x200] : 0xCC005000;

u32 ARInit(u32* stack_index_addr, u32 num_entries)
{
    int enabled;

    if (__AR_init_flag == 1) {
        return 0x4000;
    }
    OSRegisterVersion(__ARVersion);
    enabled = OSDisableInterrupts();
    __AR_Callback = 0;
    __OSSetInterruptHandler(6, __ARHandler);
    __OSUnmaskInterrupts(0x02000000);
    __AR_StackPointer = 0x4000;
    __AR_FreeBlocks = num_entries;
    __AR_BlockLength = stack_index_addr;
    __DSPRegs[13] = (__DSPRegs[13] & 0xFF) | (__DSPRegs[13] & ~0xFF);
    __ARChecksize();
    __AR_init_flag = 1;
    OSRestoreInterrupts(enabled);
    return __AR_StackPointer;
}
