typedef unsigned char u8;
typedef unsigned int u32;
typedef long s32;
typedef long long s64;

volatile u32 __SIRegs[0x100] : 0xCC006400;

#define SI_COMCSR_IDX 13
#define SI_STATUS_IDX 14
#define SI_COMCSR_TCINT_MASK (1u << 31)
#define SI_COMCSR_TCINTMSK_MASK (1u << 30)
#define SI_COMCSR_RDSTINT_MASK (1u << 28)
#define SI_COMCSR_RDSTINTMSK_MASK (1u << 27)
#define SI_ERROR_BUSY 0x80

typedef void (*SICallback)(s32 chan, u32 sr, void* context);
typedef void (*IntHandler)(short interrupt, void* context);

extern s64 __OSGetSystemTime(void);
extern void OSCancelAlarm(void* alarm);
extern u32 VIGetCurrentLine(void);
extern u32 CompleteTransfer(void);
extern int __SITransfer(s32 chan, void* output, u32 outputBytes, void* input, u32 inputBytes, SICallback callback);
extern int SITransfer(s32 chan, void* output, u32 outputBytes, void* input, u32 inputBytes, SICallback callback, s64 delay);
extern int SIGetResponseRaw(s32 chan);
extern void GetTypeCallback(s32 chan, u32 error, void* context);

typedef struct SIControl {
    s32 chan;
    u32 poll;
    u32 inputBytes;
    void* input;
    SICallback callback;
} SIControl;

typedef struct SIPacket {
    s32 chan;
    void* output;
    u32 outputBytes;
    void* input;
    u32 inputBytes;
    SICallback callback;
    s64 fire;
} SIPacket;

typedef struct SIAlarm { u8 pad[0x28]; } SIAlarm;

// Declared in reverse of address order.
u32 lbl_8066F288; // likely __PADFixBits
u32 SIGetType_cmdTypeAndStatus;  // SIGetType's function-local static
u32 lbl_8066F280; // SIInterruptHandler's own function-local static (cmdTypeAndStatus)

// SIBios.c's translation unit. Global because SIBios.c's unclaimed asm references them.
char lbl_804D1B78[] = "<< Dolphin SDK - SI\trelease build: Apr 17 2003 12:33:19 (0x2301) >>";
SIControl Si = { -1, 0, 0, 0, 0 };
u32 Type[4] = { 0x08, 0x08, 0x08, 0x08 };
SIPacket Packet[4];
SIAlarm Alarm[4];
s64 TypeTime[4];
s64 XferTime[4];
void* TypeCallback[4][4];
IntHandler RDSTHandler[4];
s32 InputBufferValid[4];
u32 InputBuffer[4][2];
volatile u32 InputBufferVcount[4];

// SIGetTypeString's name table; dead-stripped (SIGetTypeString itself is unreferenced).
#pragma force_active on
char lbl_804D1BE0[] = "No response";
char lbl_804D1BEC[] = "N64 controller";
char lbl_804D1BFC[] = "N64 microphone";
char lbl_804D1C0C[] = "N64 keyboard";
char lbl_804D1C1C[] = "N64 mouse";
char lbl_804D1C28[] = "GameBoy Advance";
char lbl_804D1C38[] = "Standard controller";
char lbl_804D1C4C[] = "Wireless receiver";
char lbl_804D1C60[] = "WaveBird controller";
char lbl_804D1C74[] = "Keyboard";
char lbl_804D1C80[] = "Steering";
#pragma force_active reset

// Rest of SIBios.c's .bss; unreferenced anywhere in the project.
#pragma force_active on
u8 lbl_8057D200[0x20];
#pragma force_active reset

static inline void SITransferNext(s32 chan) {
    int i;
    SIPacket* packet;

    for (i = 0; i < 4; i++) {
        chan++;
        chan %= 4;
        packet = &Packet[chan];

        if (packet->chan != -1) {
            if (packet->fire <= __OSGetSystemTime()) {
                if (__SITransfer(packet->chan, packet->output, packet->outputBytes, packet->input, packet->inputBytes, packet->callback) != 0) {
                    OSCancelAlarm(&Alarm[chan]);
                    packet->chan = -1;
                }
                return;
            }
        }
    }
}

static inline int SIIsChanBusy(s32 chan) {
    return Packet[chan].chan != -1 || Si.chan == chan;
}

void SIInterruptHandler(short interrupt, void* context) {
    u32 reg;
    s32 chan;
    u32 sr;
    SICallback callback;
    int i;
    u32 vcount;
    u32 x;

    (void)lbl_804D1B78;
    (void)Si;
    (void)Type;
    (void)Packet;
    (void)Alarm;
    (void)TypeTime;
    (void)XferTime;
    (void)TypeCallback;
    (void)RDSTHandler;
    (void)InputBufferValid;
    (void)InputBuffer;
    (void)InputBufferVcount;

    reg = __SIRegs[SI_COMCSR_IDX];
    if ((reg & (SI_COMCSR_TCINT_MASK | SI_COMCSR_TCINTMSK_MASK)) == (SI_COMCSR_TCINT_MASK | SI_COMCSR_TCINTMSK_MASK)) {
        chan = Si.chan;
        sr = CompleteTransfer();
        callback = Si.callback;
        Si.callback = 0;
        SITransferNext(chan);

        if (callback) {
            callback(chan, sr, context);
        }

        sr = __SIRegs[SI_STATUS_IDX];
        sr &= 0x0F000000 >> (chan << 3);
        __SIRegs[SI_STATUS_IDX] = sr;

        if (Type[chan] == SI_ERROR_BUSY && !SIIsChanBusy(chan)) {
            SITransfer(chan, &lbl_8066F280, 1, &Type[chan], 3, (SICallback)&GetTypeCallback,
                       (s64)(u32)((((*(u32*)0x800000F8) / 4) / 125000 * 65) / 8));
        }
    }

    if ((reg & (SI_COMCSR_RDSTINT_MASK | SI_COMCSR_RDSTINTMSK_MASK)) == (SI_COMCSR_RDSTINT_MASK | SI_COMCSR_RDSTINTMSK_MASK)) {
        vcount = 1 + VIGetCurrentLine();
        x = (Si.poll & (0x3FF << 16)) >> 16;

        for (i = 0; i < 4; i++) {
            if (SIGetResponseRaw(i)) {
                InputBufferVcount[i] = vcount;
            }
        }

        for (i = 0; i < 4; i++) {
            if ((Si.poll & (0x80000000 >> (24 + i))) != 0) {
                if (InputBufferVcount[i] == 0 || ((x >> 1) + InputBufferVcount[i]) < vcount) {
                    return;
                }
            }
        }

        for (i = 0; i < 4; i++) {
            InputBufferVcount[i] = 0;
        }

        for (i = 0; i < 4; i++) {
            if (RDSTHandler[i] != 0) {
                (*RDSTHandler[i])(interrupt, context);
            }
        }
    }
}
