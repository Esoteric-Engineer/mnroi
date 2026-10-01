typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef long s32;
typedef long long s64;
typedef unsigned long long u64;
typedef int BOOL;
typedef s64 OSTime;

extern void OSRegisterVersion(const char* version);
extern OSTime OSGetTime(void);
extern void SIRefreshSamplingRate(void);
extern void OSRegisterResetFunction(void* info);
extern void PADSetSpec(u32 spec);
extern BOOL PADReset(u32 mask);
extern BOOL OnReset_8018B438(BOOL final);

extern const char* __PADVersion;
extern int lbl_8066F3D8;
extern u32 lbl_8066F3E4;
extern u32 lbl_8066F288;
extern u32 __PADSpec;
extern u32 Type_8057D560[4];

u16 __OSWirelessPadFixMode : 0x800030E0;

char lbl_804D2C50[] = "<< Dolphin SDK - PAD\trelease build: Aug  6 2003 04:30:02 (0x2301) >>";

typedef struct OSResetFunctionInfo OSResetFunctionInfo;
struct OSResetFunctionInfo {
    BOOL (*func)(BOOL final);
    u32 priority;
    OSResetFunctionInfo* next;
    OSResetFunctionInfo* prev;
};

OSResetFunctionInfo lbl_804D2C98 = {
    OnReset_8018B438,
    0x7F,
};

BOOL PADInit(void)
{
    u8* base = (u8*)Type_8057D560;
    s32 chan;
    OSTime time;

    if (lbl_8066F3D8) {
        return 1;
    }
    OSRegisterVersion(__PADVersion);

    if (__PADSpec) {
        PADSetSpec(__PADSpec);
    }

    lbl_8066F3D8 = 1;
    if (lbl_8066F288 != 0) {
        time = OSGetTime();
        __OSWirelessPadFixMode
            = (u16)((((time) & 0xffff) + ((time >> 16) & 0xffff) + ((time >> 32) & 0xffff) + ((time >> 48) & 0xffff))
                    & 0x3fffu);
        lbl_8066F3E4 = 0xF0000000;
    }

    for (chan = 0; chan < 4; chan++) {
        ((u32*)(base + 0x40))[chan] = 0x4D000000 | (chan << 22) | (__OSWirelessPadFixMode & 0x3FFF) << 8;
    }

    SIRefreshSamplingRate();
    OSRegisterResetFunction(&lbl_804D2C98);

    return PADReset(0xF0000000);
}
