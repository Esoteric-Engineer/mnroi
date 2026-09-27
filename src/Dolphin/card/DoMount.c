typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;
typedef int BOOL;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDControl {
    u8 pad0[0x8];
    u16 size;
    u8 pad0A[0xC - 0xA];
    s32 sectorSize;
    u16 cBlock;
    u8 pad12[0x14 - 0x12];
    s32 latency;
    u8 id[12];
    s32 mountStep;
    u8 pad28[0x80 - 0x28];
    void* workArea;
    u8 pad84[0x108 - 0x84];
    u32 cid;
    u8 pad10C[0x110 - 0x10C];
} CARDControl;

typedef struct OSSramEx {
    u8 flashID[2][12];
    u8 pad18[0x26 - 0x18];
    u8 flashIDCheckSum[2];
} OSSramEx;

extern CARDControl __CARDBlock[2];
extern s32 lbl_804F2BD8[8];
extern s32 lbl_804F2BF8[8];
extern u16 lbl_8066CEF8;

extern BOOL EXIGetID(s32 chan, u32 dev, u32* id);
extern s32 IsCard(u32 id);
extern s32 __CARDClearStatus(s32 chan);
extern s32 __CARDReadStatus(s32 chan, u8* status);
extern BOOL EXIProbe(s32 chan);
extern s32 __CARDUnlock(s32 chan, u8* id);
extern OSSramEx* __OSLockSramEx(void);
extern void __OSUnlockSramEx(int commit);
extern s32 __CARDEnableInterrupt(s32 chan, BOOL enable);
extern void __CARDExiHandler(s32 chan, void* context);
extern void* EXISetExiCallback(s32 chan, void* callback);
extern void EXIUnlock(s32 chan);
extern void DCInvalidateRange(void* addr, u32 nBytes);
extern s32 __CARDRead(s32 chan, u32 addr, s32 length, void* dst, CARDCallback callback);
extern void __CARDMountCallback(s32 chan, s32 result);
extern s32 __CARDPutControlBlock(CARDControl* card, s32 result);
extern void DoUnmount(s32 chan, s32 result);

s32 DoMount(s32 chan)
{
    CARDControl* card;
    u32 id;
    u8 status;
    s32 result;
    OSSramEx* sram;
    int i;
    u8 checkSum;
    int step;
    u16 vendorID;

    card = &__CARDBlock[chan];
    if (card->mountStep == 0) {
        if (EXIGetID(chan, 0, &id) == 0) {
            result = -3;
        } else if (IsCard(id)) {
            result = 0;
        } else {
            result = -2;
        }

        if (result < 0) {
            goto error;
        }

        card->cid = id;
        card->size = (u16)(id & 0xFC);
        card->sectorSize = lbl_804F2BD8[(id & 0x3800) >> 11];
        card->cBlock = (u16)((card->size * 1024 * 1024 / 8) / card->sectorSize);
        card->latency = lbl_804F2BF8[(id & 0x700) >> 8];

        result = __CARDClearStatus(chan);
        if (result < 0)
            goto error;
        result = __CARDReadStatus(chan, &status);
        if (result < 0)
            goto error;
        if (!EXIProbe(chan)) {
            result = -3;
            goto error;
        }

        if (!(status & 0x40)) {
            result = __CARDUnlock(chan, card->id);
            if (result < 0)
                goto error;

            checkSum = 0;
            sram = __OSLockSramEx();
            for (i = 0; i < 12; i++) {
                sram->flashID[chan][i] = card->id[i];
                checkSum += card->id[i];
            }
            sram->flashIDCheckSum[chan] = (u8)~checkSum;
            __OSUnlockSramEx(1);

            return result;
        } else {
            card->mountStep = 1;

            checkSum = 0;
            sram = __OSLockSramEx();
            for (i = 0; i < 12; i++)
                checkSum += sram->flashID[chan][i];

            __OSUnlockSramEx(0);
            if (sram->flashIDCheckSum[chan] != (u8)~checkSum) {
                result = -5;
                goto error;
            }
        }
    }

    if (card->mountStep == 1) {
        if (card->cid == 0x80000004) {
            sram = __OSLockSramEx();
            vendorID = *(u16*)sram->flashID[chan];
            __OSUnlockSramEx(0);

            if (lbl_8066CEF8 == 0xFFFF || (vendorID != lbl_8066CEF8)) {
                result = -2;
                goto error;
            }
        }

        card->mountStep = 2;

        result = __CARDEnableInterrupt(chan, 1);
        if (result < 0)
            goto error;

        EXISetExiCallback(chan, __CARDExiHandler);
        EXIUnlock(chan);
        DCInvalidateRange(card->workArea, 0xA000);
    }

    step = card->mountStep - 2;
    result = __CARDRead(chan, (u32)card->sectorSize * step, 0x2000,
                        (u8*)card->workArea + (0x2000 * step), __CARDMountCallback);
    if (result < 0)
        __CARDPutControlBlock(card, result);
    return result;

error:
    EXIUnlock(chan);
    DoUnmount(chan, result);
    return result;
}
