typedef struct {
    unsigned short flag;
    unsigned short bufferHi;
    unsigned short bufferLo;
    unsigned short shiftL;
    unsigned short shiftR;
    unsigned short targetShiftL;
    unsigned short targetShiftR;
} AXPBITD;

typedef struct {
    unsigned short updNum[5];
    unsigned short dataHi;
    unsigned short dataLo;
} AXPBUPDATE;

typedef struct {
    unsigned short nextHi;
    unsigned short nextLo;
    unsigned short currHi;
    unsigned short currLo;
    unsigned short srcSelect;
    unsigned short coefSelect;
    unsigned short mixerCtrl;
    unsigned short state;
    unsigned short type;
    unsigned short mix[18];
    AXPBITD itd;
    AXPBUPDATE update;
    unsigned char pad52[0xA6 - 0x52];
    unsigned short xa6;
    unsigned char padA8[0xBA - 0xA8];
    unsigned short xba;
    unsigned char padBC[0xF4 - 0xBC];
} AXPB;

typedef struct {
    unsigned char data[0x40];
} AXPBITDBUFFER;

typedef struct {
    unsigned char data[0x100];
} AXPBU;

typedef struct AXVPB {
    struct AXVPB* next;
    void* prev;
    void* next1;
    unsigned long priority;
    void* callback;
    unsigned long userContext;
    unsigned long index;
    unsigned long sync;
    unsigned long depop;
    unsigned long updateMS;
    unsigned long updateCounter;
    unsigned long updateTotal;
    unsigned short* updateWrite;
    unsigned short updateData[128];
    void* itdBuffer;
    AXPB pb;
} AXVPB;

AXPB __AXPB[64] __attribute__((aligned(32)));
AXPBITDBUFFER __AXITD[64] __attribute__((aligned(32)));
AXPBU __AXUpdates[64] __attribute__((aligned(32)));
AXVPB __AXVPB[64] __attribute__((aligned(32)));
static unsigned long tblA[5] = { 0xDF8, 0xF78, 0x14B8, 0x19F8, 0x19F8 };
static unsigned long tblB[16] = {
    0x0, 0x2F8, 0x2F8, 0x5BE, 0x2F8, 0x5F0, 0x5F0, 0x8B6,
    0x0, 0x4F1, 0x4F1, 0x9A6, 0x4F1, 0x9E2, 0x9E2, 0xE97,
};
static unsigned long tblC[32] = {
    0x0, 0x2F8, 0x2F8, 0x5BE, 0x0, 0x4F1, 0x4F1, 0x9A6,
    0x2F8, 0x5F0, 0x5F0, 0x8B6, 0x2F8, 0x7E9, 0x7E9, 0xC9E,
    0x0, 0x2F8, 0x2F8, 0x5BE, 0x0, 0x4F1, 0x4F1, 0x9A6,
    0x4F1, 0x7E9, 0x7E9, 0xAAF, 0x4F1, 0x9E2, 0x9E2, 0xE97,
};
extern unsigned long __AXMaxDspCycles;
extern unsigned long __AXRecDspCycles;
extern unsigned long __AXNumVoices;

unsigned long __OSBusClock : 0x800000F8;

extern void DCInvalidateRange(void*, unsigned long);
extern void DCFlushRange(void*, unsigned long);
extern unsigned long __AXGetCommandListCycles(void);
extern AXVPB* __AXGetStackHead(unsigned long);
extern void __AXDepopVoice(AXPB*);
extern void __AXPushCallbackStack(AXVPB*);
extern void __AXPushFreeStack(AXVPB*);
extern void __AXServiceVPB(AXVPB*);

void __AXSyncPBs(unsigned long baseCycles)
{
    AXPB* pb;
    AXPB* pbs = __AXPB;
    unsigned long cycles;
    long pri;
    AXVPB* p;
    unsigned long f;

    __AXNumVoices = 0;
    DCInvalidateRange(pbs, 0x3D00);
    DCInvalidateRange(__AXITD, 0x1000);
    cycles = __AXGetCommandListCycles() + 0x10000 + baseCycles - 0x55F0;
    for (pri = 31; pri != 0; pri--) {
        for (p = __AXGetStackHead(pri); p != 0; p = p->next) {
            if (p->depop != 0) {
                __AXDepopVoice(&pbs[p->index]);
            }
            if (p->pb.state == 1 || p->updateCounter != 0) {
                if (p->pb.srcSelect != 2) {
                    cycles += tblA[p->pb.xa6];
                }
                if (p->pb.xba != 0) {
                    cycles += 0x22B;
                }
                f = p->pb.mixerCtrl;
                cycles += tblB[f & 0xF] + tblC[(f >> 4) & 0x1F] + tblC[(f >> 9) & 0x1F] + 0x8C;
                if (__AXMaxDspCycles > cycles) {
                    __AXServiceVPB(p);
                } else {
                    if ((pb = &pbs[p->index])->state == 1) {
                        __AXDepopVoice(pb);
                    }
                    pb->update.updNum[4] = 0;
                    pb->update.updNum[3] = 0;
                    pb->update.updNum[2] = 0;
                    pb->update.updNum[1] = 0;
                    pb->update.updNum[0] = 0;
                    pb->state = 0;
                    p->pb.state = 0;
                    __AXPushCallbackStack(p);
                }
            } else {
                __AXServiceVPB(p);
            }
            p->sync = 0;
            p->depop = 0;
            p->updateCounter = 0;
            p->updateMS = 0;
            p->updateWrite = p->updateData;
        }
    }
    __AXRecDspCycles = cycles;
    for (p = __AXGetStackHead(0); p != 0; p = p->next) {
        if (p->depop != 0) {
            __AXDepopVoice(&pbs[p->index]);
        }
        p->depop = 0;
        pbs[p->index].update.updNum[4] = 0;
        pbs[p->index].update.updNum[3] = 0;
        pbs[p->index].update.updNum[2] = 0;
        pbs[p->index].update.updNum[1] = 0;
        pbs[p->index].update.updNum[0] = 0;
        pbs[p->index].state = 0;
    }
    DCFlushRange(pbs, 0x3D00);
    DCFlushRange(__AXITD, 0x1000);
    DCFlushRange(__AXUpdates, 0x4000);
}

void* __AXGetPBs(void)
{
    return __AXPB;
}

void __AXSetPBDefault(AXVPB* p)
{
    p->pb.state = 0;
    p->pb.itd.flag = 0;
    p->sync = 0xA4;
    p->updateCounter = 0;
    p->updateMS = 0;
    p->updateWrite = p->updateData;
    p->pb.update.updNum[4] = 0;
    p->pb.update.updNum[3] = 0;
    p->pb.update.updNum[2] = 0;
    p->pb.update.updNum[1] = 0;
    p->pb.update.updNum[0] = 0;
    p->pb.xba = 0;
}

void __AXVPBInit(void)
{
    unsigned long i;
    AXPB* pb;
    AXPBITDBUFFER* itd;
    AXPBU* u;
    AXVPB* pvpb;
    unsigned long* p;

    __AXMaxDspCycles = __OSBusClock / 400;
    __AXRecDspCycles = 0;

    p = (unsigned long*)__AXPB;
    for (i = sizeof(__AXPB) / 4; i != 0; i--) {
        *p++ = 0;
    }
    p = (unsigned long*)__AXITD;
    for (i = sizeof(__AXITD) / 4; i != 0; i--) {
        *p++ = 0;
    }
    p = (unsigned long*)__AXVPB;
    for (i = sizeof(__AXVPB) / 4; i != 0; i--) {
        *p++ = 0;
    }

    for (i = 0; i < 64; i++) {
        pb = &__AXPB[i];
        itd = &__AXITD[i];
        u = &__AXUpdates[i];
        pvpb = &__AXVPB[i];

        pvpb->index = i;
        pvpb->updateWrite = pvpb->updateData;
        pvpb->itdBuffer = itd;
        __AXSetPBDefault(pvpb);

        if (i == 63) {
            pvpb->pb.nextHi = pvpb->pb.nextLo = pb->nextHi = pb->nextLo = 0;
        } else {
            pvpb->pb.nextHi = (unsigned short)((unsigned long)(pb + 1) >> 16);
            pvpb->pb.nextLo = (unsigned short)(unsigned long)(pb + 1);
            pb->nextHi = (unsigned short)((unsigned long)(pb + 1) >> 16);
            pb->nextLo = (unsigned short)(unsigned long)(pb + 1);
        }

        pvpb->pb.currHi = (unsigned short)((unsigned long)pb >> 16);
        pvpb->pb.currLo = (unsigned short)(unsigned long)pb;
        pb->currHi = (unsigned short)((unsigned long)pb >> 16);
        pb->currLo = (unsigned short)(unsigned long)pb;

        pvpb->pb.itd.bufferHi = (unsigned short)((unsigned long)itd >> 16);
        pvpb->pb.itd.bufferLo = (unsigned short)(unsigned long)itd;
        pb->itd.bufferHi = (unsigned short)((unsigned long)itd >> 16);
        pb->itd.bufferLo = (unsigned short)(unsigned long)itd;

        pvpb->pb.update.dataHi = (unsigned short)((unsigned long)u >> 16);
        pvpb->pb.update.dataLo = (unsigned short)(unsigned long)u;
        pb->update.dataHi = (unsigned short)((unsigned long)u >> 16);
        pb->update.dataLo = (unsigned short)(unsigned long)u;

        pvpb->priority = 1;
        __AXPushFreeStack(pvpb);
    }

    DCFlushRange(__AXPB, sizeof(__AXPB));
}
