typedef unsigned int u32;
typedef long s32;

volatile u32 __SIRegs[0x100] : 0xCC006400;

#define SI_COMCSR_IDX 13
#define SI_COMCSR_TCINT_MASK (1u << 31)
#define SI_COMCSR_TSTART_MASK (1u << 0)

typedef struct SIControl {
    s32 chan;
    u32 poll;
    u32 inputBytes;
    void* input;
    void* callback;
} SIControl;

typedef struct SIPacket {
    s32 chan;
    u32 pad[7];
} SIPacket;

extern SIPacket Packet[4];
extern SIControl Si;
extern const char* __SIVersion;

extern void OSRegisterVersion(const char* version);
extern void SISetSamplingRate(u32 msec);
extern void __OSSetInterruptHandler(short interrupt, void* handler);
extern u32 __OSUnmaskInterrupts(u32 mask);
extern void SIInterruptHandler(short interrupt, void* context);
extern u32 SIGetType(s32 chan);

void SIInit(void)
{
    unsigned char* base = (unsigned char*)Packet;

    OSRegisterVersion(__SIVersion);
    *(s32*)base = *(s32*)(base + 0x20) = *(s32*)(base + 0x40) = *(s32*)(base + 0x60) = -1;
    Si.poll = 0;
    SISetSamplingRate(0);
    do {
    } while (__SIRegs[SI_COMCSR_IDX] & SI_COMCSR_TSTART_MASK);
    __SIRegs[SI_COMCSR_IDX] = SI_COMCSR_TCINT_MASK;
    __OSSetInterruptHandler(0x14, SIInterruptHandler);
    __OSUnmaskInterrupts(0x800);
    SIGetType(0);
    SIGetType(1);
    SIGetType(2);
    SIGetType(3);
}
