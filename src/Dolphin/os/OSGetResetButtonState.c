typedef int BOOL;
typedef unsigned long u32;
typedef unsigned char u8;
typedef long long s64;
typedef s64 OSTime;

extern volatile u32 __PIRegs[0x20] : 0xCC003000;

extern OSTime lbl_8066F200;
extern int lbl_8066F254;
extern int lbl_8066F258;
extern OSTime lbl_8066F260;
extern OSTime lbl_8066F268;

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
        if (!lbl_8066F254) {
            lbl_8066F254 = 1;
            state = lbl_8066F260 ? 1 : 0;
            lbl_8066F268 = now;
        } else {
            state = lbl_8066F260 || (OSMicrosecondsToTicks(100) < now - lbl_8066F268) ? 1 : 0;
        }
    } else if (lbl_8066F254) {
        lbl_8066F254 = 0;
        state = lbl_8066F258;
        if (state) {
            lbl_8066F260 = now;
        } else {
            lbl_8066F260 = 0;
        }
    } else if (lbl_8066F260 && (now - lbl_8066F260 < OSMillisecondsToTicks(40))) {
        state = 1;
    } else {
        state = 0;
        lbl_8066F260 = 0;
    }

    lbl_8066F258 = state;

    if (GameChoice & 0x1F) {
        OSTime fire = (GameChoice & 0x1F) * 60;
        fire = lbl_8066F200 + OSSecondsToTicks(fire);
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
