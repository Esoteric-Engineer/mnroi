typedef int BOOL;
typedef unsigned long u32;
typedef unsigned char u8;
typedef long long s64;
typedef s64 OSTime;

extern volatile u32 __PIRegs[0x20] : 0xCC003000;

extern OSTime __OSStartTime;
extern int Down;
extern int ResetSwLastState;
extern OSTime HoldUp;
extern OSTime HoldDown;

extern u8 GameChoice : 0x800030E3;

#define OS_TIMER_CLOCK ((*(u32*)0x800000F8) / 4)
#define OSTicksToSeconds(ticks) ((ticks) / OS_TIMER_CLOCK)
#define OSSecondsToTicks(sec) ((sec) * OS_TIMER_CLOCK)
#define OSMillisecondsToTicks(msec) ((OS_TIMER_CLOCK / 1000) * (msec))
#define OSMicrosecondsToTicks(usec) (((OS_TIMER_CLOCK / 125000) * (usec)) / 8)

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
OSTime __OSGetSystemTime(void);

BOOL OSGetResetButtonState(void)
{
    BOOL enabled = OSDisableInterrupts();
    BOOL state;
    OSTime now = __OSGetSystemTime();
    u32 reg = __PIRegs[0];

    if (!(reg & 0x00010000)) {
        if (!Down) {
            Down = 1;
            state = HoldUp ? 1 : 0;
            HoldDown = now;
        } else {
            state = HoldUp || (OSMicrosecondsToTicks(100) < now - HoldDown) ? 1 : 0;
        }
    } else if (Down) {
        Down = 0;
        state = ResetSwLastState;
        if (state) {
            HoldUp = now;
        } else {
            HoldUp = 0;
        }
    } else if (HoldUp && (now - HoldUp < OSMillisecondsToTicks(40))) {
        state = 1;
    } else {
        state = 0;
        HoldUp = 0;
    }

    ResetSwLastState = state;

    if (GameChoice & 0x1F) {
        OSTime fire = (GameChoice & 0x1F) * 60;
        fire = __OSStartTime + OSSecondsToTicks(fire);
        if (fire < now) {
            now -= fire;
            now = OSTicksToSeconds(now) / 2;
            if ((now & 1) == 0) {
                state = 1;
            } else {
                state = 0;
            }
        }
    }

    OSRestoreInterrupts(enabled);
    return state;
}
