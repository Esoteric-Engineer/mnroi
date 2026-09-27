extern unsigned long lbl_8066FA68;
extern volatile long long lbl_8066FA70;
extern long long OSGetTime(void);
extern void __AXOutNewFrame(unsigned long);

void __AXDSPResumeCallback(void)
{
    if (lbl_8066FA68 == 2) {
        lbl_8066FA68 = 0;
        __AXOutNewFrame((unsigned long)(OSGetTime() - lbl_8066FA70) / 4);
    } else {
        lbl_8066FA68 = 1;
    }
}
