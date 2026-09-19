typedef unsigned char u8;
typedef unsigned long u32;

volatile u32 __AIRegs[8] : 0xCC006C00;

extern u32 AIGetDSPSampleRate(void);
extern u32 AIGetStreamPlayState(void);
extern u32 AIGetStreamSampleRate(void);
extern u32 AIGetStreamVolLeft(void);
extern u32 AIGetStreamVolRight(void);
extern void AISetStreamVolLeft(u32 vol);
extern void AISetStreamVolRight(u32 vol);
extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int level);
extern void fn_8018BD24(void);

void AISetDSPSampleRate(u32 rate)
{
    u32 play_state;
    int old;
    u32 afr_state;
    u32 vol_left;
    u32 vol_right;

    if (rate != AIGetDSPSampleRate()) {
        __AIRegs[0] = (__AIRegs[0] & 0xFFFFFFBF);
        if (rate == 0) {
            vol_left = AIGetStreamVolLeft();
            vol_right = AIGetStreamVolRight();
            play_state = __AIRegs[0] & 1;
            afr_state = AIGetStreamSampleRate();
            AISetStreamVolLeft(0);
            AISetStreamVolRight(0);
            old = OSDisableInterrupts();
            fn_8018BD24();
            __AIRegs[0] = (__AIRegs[0] & 0xFFFFFFDF) | 0x20;
            __AIRegs[0] = (__AIRegs[0] & 0xFFFFFFFD) | (afr_state << 1);
            __AIRegs[0] = (__AIRegs[0] & 0xFFFFFFFE) | play_state;
            __AIRegs[0] |= 0x40;
            OSRestoreInterrupts(old);
            AISetStreamVolLeft(vol_left);
            AISetStreamVolRight(vol_right);
        }
    }
}
