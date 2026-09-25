extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int);
extern void OSSleepThread(void*);
extern void DSPCancelTask(void*);
extern void AIStopDMA(void);

extern char lbl_80657040[0x80];
extern unsigned long lbl_8066FA78;
extern unsigned long lbl_8066FA88[2];

void __AXOutQuit(void)
{
    int old = OSDisableInterrupts();
    lbl_8066FA78 = 0;
    DSPCancelTask(lbl_80657040);
    OSSleepThread(lbl_8066FA88);
    AIStopDMA();
    OSRestoreInterrupts(old);
}
