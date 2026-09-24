typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef signed char s8;
typedef long s32;
typedef int BOOL;

typedef struct PADStatus {
    u16 button;
    s8 stickX;
    s8 stickY;
    s8 substickX;
    s8 substickY;
    u8 triggerL;
    u8 triggerR;
    u8 analogA;
    u8 analogB;
    s8 err;
} PADStatus;

extern BOOL OSDisableInterrupts(void);
extern void OSRestoreInterrupts(BOOL enabled);
extern void SIDisablePolling(u32 poll);
extern void OSSetWirelessID(int chan, unsigned short id);
extern BOOL SIGetResponse(int chan, void* data);
extern u32 SIGetStatus(int chan);
extern u32 SIGetType(int chan);
extern BOOL SIIsChanBusy(int chan);
extern void SIGetTypeAsync(int chan, void* callback);
extern BOOL SITransfer(int chan, void* output, u32 outputBytes, void* input, u32 inputBytes, void* callback,
                       long long delay);
extern void* memset(void* dst, int val, unsigned long n);
extern u32 PADReset(u32 mask);

extern void PADReceiveCheckCallback(void);
extern void PADOriginUpdateCallback(void);

extern long lbl_8066C49C;
extern void (*lbl_8066C4AC)(int chan, PADStatus* status, u32* data);
extern u32 lbl_8066C4B0;
extern u32 lbl_8066F3DC;
extern u32 lbl_8066F3E0;
extern u32 lbl_8066F3E8;
extern u32 lbl_8066F3EC;
extern u32 lbl_8066F3F0;
extern u32 lbl_8066F3F4;
extern unsigned char Origin[];

static inline void PADDisable(int chan)
{
    BOOL enabled;
    u32 chanBit;

    enabled = OSDisableInterrupts();
    chanBit = 0x80000000 >> chan;
    SIDisablePolling(chanBit);
    lbl_8066F3DC &= ~chanBit;
    lbl_8066F3E8 &= ~chanBit;
    lbl_8066F3EC &= ~chanBit;
    lbl_8066F3F0 &= ~chanBit;
    lbl_8066F3F4 &= ~chanBit;
    OSSetWirelessID(chan, 0);
    OSRestoreInterrupts(enabled);
}

u32 PADRead(PADStatus* status)
{
    BOOL enabled;
    int chan;
    u32 data[2];
    u32 chanBit;
    u32 sr;
    int chanShift;
    u32 motor;

    enabled = OSDisableInterrupts();
    motor = 0;

    for (chan = 0; chan < 4; chan++, status++) {
        chanBit = 0x80000000 >> chan;
        chanShift = (3 - chan) * 8;

        if (lbl_8066F3F0 & chanBit) {
            PADReset(0);
            status->err = -2;
            memset(status, 0, 10);
        } else if ((lbl_8066F3E0 & chanBit) || (lbl_8066C49C == chan)) {
            status->err = -2;
            memset(status, 0, 10);
        } else if (!(lbl_8066F3DC & chanBit)) {
            status->err = -1;
            memset(status, 0, 10);
        } else if (SIIsChanBusy(chan)) {
            status->err = -3;
            memset(status, 0, 10);
        } else {
            sr = SIGetStatus(chan);
            if (sr & 8) {
                SIGetResponse(chan, data);

                if (lbl_8066F3E8 & chanBit) {
                    status->err = 0;
                    memset(status, 0, 10);
                    if (!(lbl_8066F3EC & chanBit)) {
                        lbl_8066F3EC |= chanBit;
                        SIGetTypeAsync(chan, PADReceiveCheckCallback);
                    }
                } else {
                    PADDisable(chan);
                    status->err = -1;
                    memset(status, 0, 10);
                }
            } else {
                if (!(SIGetType(chan) & 0x20000000)) {
                    motor |= chanBit;
                }

                if (!SIGetResponse(chan, data)) {
                    status->err = -3;
                    memset(status, 0, 10);
                } else if (data[0] & 0x80000000) {
                    status->err = -3;
                    memset(status, 0, 10);
                } else {
                    lbl_8066C4AC(chan, status, data);

                    if (status->button & 0x2000) {
                        status->err = -3;
                        memset(status, 0, 10);
                        SITransfer(chan, &lbl_8066C4B0, 1, Origin + chan * 12, 10, PADOriginUpdateCallback, 0);
                    } else {
                        status->err = 0;
                        status->button &= ~0x80;
                    }
                }
            }
        }
    }

    OSRestoreInterrupts(enabled);
    return motor;
}
