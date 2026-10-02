typedef int BOOL;
typedef void (*DVDLowCallback)(unsigned long);

extern volatile unsigned long __DIRegs[0x20] : 0xCC006000;
extern DVDLowCallback Callback;
extern volatile BOOL WaitingCoverClose;
extern volatile BOOL StopAtNextInt;

BOOL DVDLowWaitCoverClose(DVDLowCallback callback)
{
    Callback = callback;
    WaitingCoverClose = 1;
    StopAtNextInt = 0;
    __DIRegs[1] = 2;
    return 1;
}
