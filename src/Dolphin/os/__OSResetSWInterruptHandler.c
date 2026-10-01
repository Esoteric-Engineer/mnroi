typedef unsigned long u32;
typedef long long s64;
typedef s64 OSTime;
typedef void (*OSResetCallback)(void);

extern volatile u32 __PIRegs[0x20] : 0xCC003000;

static OSResetCallback ResetCallback;
OSTime HoldDown;
OSTime HoldUp;
int ResetSwLastState;
int Down;

OSTime __OSGetSystemTime(void);
void __OSMaskInterrupts(u32 mask);

// Declare-at-address (as in os.h) so MWCC hoists the load out of the wait loop.
u32 __OSBusClock : 0x800000F8;
#define OSMicrosecondsToTicks(usec) (((usec) * ((__OSBusClock / 4) / 125000)) / 8)

void __OSResetSWInterruptHandler(short exception, void* context)
{
    OSResetCallback callback;

    HoldDown = __OSGetSystemTime();
    while ((__OSGetSystemTime() - HoldDown) < OSMicrosecondsToTicks(100) && !(__PIRegs[0] & 0x00010000))
        ;
    if (!(__PIRegs[0] & 0x00010000)) {
        ResetSwLastState = Down = 1;
        __OSMaskInterrupts(0x200);
        if (ResetCallback) {
            callback = ResetCallback;
            ResetCallback = 0;
            callback();
        }
    }
    __PIRegs[0] = 2;
}
