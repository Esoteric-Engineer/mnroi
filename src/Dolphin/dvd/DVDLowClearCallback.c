typedef void (*DVDLowCallback)(unsigned long);

extern volatile unsigned long __DIRegs[0x20] : 0xCC006000;
extern DVDLowCallback Callback;
extern unsigned long WaitingCoverClose;

DVDLowCallback DVDLowClearCallback(void)
{
    DVDLowCallback old;
    __DIRegs[1] = 0;
    old = Callback;
    WaitingCoverClose = 0;
    Callback = 0;
    return old;
}
