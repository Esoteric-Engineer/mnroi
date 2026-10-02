typedef unsigned int u32;
typedef void (*ARCallback)(void);

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int level);

// ar.c's .sbss state, declared in reverse address order: mwld reverses a run of @sda21 scalars.
int __AR_init_flag;
u32* __AR_BlockLength;
u32 __AR_FreeBlocks;
u32 __AR_StackPointer;
u32 __AR_ExpansionSize;
u32 __AR_InternalSize;
u32 __AR_Size;
ARCallback __AR_Callback;

ARCallback ARRegisterDMACallback(ARCallback callback)
{
    ARCallback old_callback;
    int old;

    old_callback = __AR_Callback;
    old = OSDisableInterrupts();
    __AR_Callback = callback;
    OSRestoreInterrupts(old);
    return old_callback;
}
