typedef unsigned char u8;
typedef unsigned long u32;

volatile u32 __AIRegs[8] : 0xCC006C00;

extern u32 AIGetStreamPlayState(void);
extern u32 AIGetStreamSampleRate(void);
extern u32 AIGetStreamVolLeft(void);
extern u32 AIGetStreamVolRight(void);
extern void AISetStreamVolLeft(u32 vol);
extern void AISetStreamVolRight(u32 vol);
extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int level);
extern void __AI_SRC_INIT(void);

void AISetStreamPlayState(u32 state)
{
    int old;
    u32 vol_left;
    u32 vol_right;

    if (state != AIGetStreamPlayState()) {
        if (AIGetStreamSampleRate() == 0 && state == 1) {
            vol_left = AIGetStreamVolRight();
            vol_right = AIGetStreamVolLeft();
            AISetStreamVolRight(0);
            AISetStreamVolLeft(0);
            old = OSDisableInterrupts();
            __AI_SRC_INIT();
            __AIRegs[0] = (__AIRegs[0] & 0xFFFFFFDF) | 0x20;
            __AIRegs[0] = (__AIRegs[0] & 0xFFFFFFFE) | 1;
            OSRestoreInterrupts(old);
            AISetStreamVolLeft(vol_left);
            AISetStreamVolRight(vol_right);
            return;
        }
        __AIRegs[0] = (__AIRegs[0] & 0xFFFFFFFE) | state;
    }
}
