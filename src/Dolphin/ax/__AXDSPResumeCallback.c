extern unsigned long __AXOutDspReady;
extern volatile long long __AXOsTime;
extern long long OSGetTime(void);
extern void __AXOutNewFrame(unsigned long);

void __AXDSPResumeCallback(void)
{
    if (__AXOutDspReady == 2) {
        __AXOutDspReady = 0;
        __AXOutNewFrame((unsigned long)(OSGetTime() - __AXOsTime) / 4);
    } else {
        __AXOutDspReady = 1;
    }
}
