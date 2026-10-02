extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int);
extern void OSSleepThread(void*);
extern void DSPCancelTask(void*);
extern void AIStopDMA(void);

extern unsigned char __AXDSPTask[0x80];
extern unsigned long __AXUserFrameCallback;
extern unsigned long __AXOutThreadQueue[2];

void __AXOutQuit(void)
{
    int old = OSDisableInterrupts();
    __AXUserFrameCallback = 0;
    DSPCancelTask(__AXDSPTask);
    OSSleepThread(__AXOutThreadQueue);
    AIStopDMA();
    OSRestoreInterrupts(old);
}
