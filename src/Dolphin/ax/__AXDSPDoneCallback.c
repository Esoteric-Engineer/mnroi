extern unsigned long lbl_8066FA80;
extern unsigned long lbl_8066FA88[2];
extern void OSWakeupThread(void*);

void __AXDSPDoneCallback(void)
{
    lbl_8066FA80 = 1;
    OSWakeupThread(lbl_8066FA88);
}
