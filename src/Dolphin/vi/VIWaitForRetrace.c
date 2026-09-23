extern volatile unsigned long lbl_8066F37C;
extern unsigned char lbl_8066F384[8];

int OSDisableInterrupts(void);
void OSRestoreInterrupts(int level);
void OSSleepThread(void* queue);

void VIWaitForRetrace(void)
{
    int enabled;
    unsigned long count;

    enabled = OSDisableInterrupts();
    count = lbl_8066F37C;
    do {
        OSSleepThread(lbl_8066F384);
    } while (count == lbl_8066F37C);
    OSRestoreInterrupts(enabled);
}
