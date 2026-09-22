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

BOOL DVDLowAudioBufferConfig(BOOL enable, u32 size, DVDLowCallback callback)
{
    Callback = callback;
    StopAtNextInt = 0;
    __DIRegs[2] = 0xE4000000 | (enable != 0 ? 0x10000 : 0) | size;
    __DIRegs[7] = 1;
    SetTimeoutAlarm((s64)((*(u32*)0x800000F8 / 4) * 10));
    return 1;
}
