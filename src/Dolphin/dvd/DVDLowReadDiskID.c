typedef int BOOL;
typedef unsigned long u32;
typedef long long s64;
typedef void (*DVDLowCallback)(u32);

extern volatile u32 __DIRegs[0x20] : 0xCC006000;
extern DVDLowCallback Callback;
extern volatile BOOL StopAtNextInt;
extern unsigned char AlarmForTimeout[0x28];

void OSCreateAlarm(void* alarm);
void OSSetAlarm(void* alarm, s64 tick, void* handler);
void AlarmHandlerForTimeout(void* alarm, void* context);

static void SetTimeoutAlarm(s64 timeout)
{
    OSCreateAlarm(AlarmForTimeout);
    OSSetAlarm(AlarmForTimeout, timeout, AlarmHandlerForTimeout);
}

BOOL DVDLowReadDiskID(void* diskID, DVDLowCallback callback)
{
    Callback = callback;
    StopAtNextInt = 0;
    __DIRegs[2] = 0xA8000040;
    __DIRegs[3] = 0;
    __DIRegs[4] = 0x20;
    __DIRegs[5] = (u32)diskID;
    __DIRegs[6] = 0x20;
    __DIRegs[7] = 3;
    SetTimeoutAlarm((s64)((*(u32*)0x800000F8 / 4) * 10));
    return 1;
}
