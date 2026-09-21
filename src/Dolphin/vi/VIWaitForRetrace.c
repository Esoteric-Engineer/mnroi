extern volatile unsigned long lbl_8066F37C;
extern unsigned char lbl_8066F384[8];

int OSDisableInterrupts(void);
void OSRestoreInterrupts(int level);
void fn_80180BFC(void* queue);

void VIWaitForRetrace(void)
{
    int enabled;
    unsigned long count;

    enabled = OSDisableInterrupts();
    count = lbl_8066F37C;
    do {
        fn_80180BFC(lbl_8066F384);
    } while (count == lbl_8066F37C);
    OSRestoreInterrupts(enabled);
}
