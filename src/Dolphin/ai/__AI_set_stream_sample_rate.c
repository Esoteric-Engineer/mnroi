typedef unsigned char u8;
typedef unsigned long u32;

volatile u32 __AIRegs[8] : 0xCC006C00;

extern u32 AIGetStreamSampleRate(void);
extern u32 AIGetStreamVolLeft(void);
extern u32 AIGetStreamVolRight(void);
extern void AISetStreamPlayState(u32 state);
extern void AISetStreamVolLeft(u32 vol);
extern void AISetStreamVolRight(u32 vol);
extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int level);
extern void fn_8018BD24(void);

static inline u32 GetPlayState(void) { return __AIRegs[0] & 1; }

void __AI_set_stream_sample_rate(u32 rate)
{
    int old;
    u32 play_state;
    u32 vol_left;
    u32 vol_right;
    u32 dsp_src_state;

    if (rate != AIGetStreamSampleRate()) {
        play_state = GetPlayState();
        vol_left = AIGetStreamVolLeft();
        vol_right = AIGetStreamVolRight();
        AISetStreamVolRight(0);
        AISetStreamVolLeft(0);
        dsp_src_state = __AIRegs[0] & 0x40;
        __AIRegs[0] = __AIRegs[0] & 0xFFFFFFBF;
        old = OSDisableInterrupts();
        fn_8018BD24();
        __AIRegs[0] |= dsp_src_state;
        __AIRegs[0] = (__AIRegs[0] & 0xFFFFFFDF) | 0x20;
        __AIRegs[0] = (__AIRegs[0] & 0xFFFFFFFD) | (rate << 1);
        OSRestoreInterrupts(old);
        AISetStreamPlayState(play_state);
        AISetStreamVolLeft(vol_left);
        AISetStreamVolRight(vol_right);
    }
}
