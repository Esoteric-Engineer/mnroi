typedef struct AXVPB {
    struct AXVPB* next;
    unsigned char pad4[0x14];
    unsigned long index;
    unsigned long sync;
    unsigned long depop;
    unsigned long updateMS;
    unsigned long updateCounter;
    unsigned long pad2C;
    void* pbPtr;
    unsigned char pb[0x10C];
    unsigned short x140;
    unsigned short pad142;
    unsigned short x144;
    unsigned short state;
    unsigned char pad148[0x1DE - 0x148];
    unsigned short x1de;
    unsigned char pad1E0[0x1F2 - 0x1E0];
    unsigned short x1f2;
} AXVPB;

typedef struct {
    unsigned char pad0[0xE];
    unsigned short state;
    unsigned char pad10[0x44 - 0x10];
    unsigned short x44;
    unsigned short x46;
    unsigned short x48;
    unsigned short x4a;
    unsigned short x4c;
    unsigned char pad4E[0xF4 - 0x4E];
} AXPB;

AXPB lbl_80657100[64];
unsigned char lbl_8065AE00[0x1000];
unsigned char lbl_8065BE00[0x4000];
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
extern unsigned long lbl_8066FAC0;
extern unsigned long lbl_8066FAC4;
extern unsigned long lbl_8066FAC8;

extern void DCInvalidateRange(void*, unsigned long);
extern void DCFlushRange(void*, unsigned long);
extern unsigned long __AXGetCommandListCycles(void);
extern AXVPB* __AXGetStackHead(unsigned long);
extern void __AXDepopVoice(AXPB*);
extern void __AXPushCallbackStack(AXVPB*);
extern void fn_804085F8(AXVPB*);

void __AXSyncPBs(unsigned long baseCycles)
{
    AXPB* pb;
    AXPB* pbs = lbl_80657100;
    unsigned long cycles;
    long pri;
    AXVPB* p;
    unsigned long f;

    lbl_8066FAC8 = 0;
    DCInvalidateRange(pbs, 0x3D00);
    DCInvalidateRange(lbl_8065AE00, 0x1000);
    cycles = __AXGetCommandListCycles() + 0x10000 + baseCycles - 0x55F0;
    for (pri = 31; pri != 0; pri--) {
        for (p = __AXGetStackHead(pri); p != 0; p = p->next) {
            if (p->depop != 0) {
                __AXDepopVoice(&pbs[p->index]);
            }
            if (p->state == 1 || p->updateCounter != 0) {
                if (p->x140 != 2) {
                    cycles += tblA[p->x1de];
                }
                if (p->x1f2 != 0) {
                    cycles += 0x22B;
                }
                f = p->x144;
                cycles += tblB[f & 0xF] + tblC[(f >> 4) & 0x1F] + tblC[(f >> 9) & 0x1F] + 0x8C;
                if (lbl_8066FAC0 > cycles) {
                    fn_804085F8(p);
                } else {
                    if ((pb = &pbs[p->index])->state == 1) {
                        __AXDepopVoice(pb);
                    }
                    pb->x4c = 0;
                    pb->x4a = 0;
                    pb->x48 = 0;
                    pb->x46 = 0;
                    pb->x44 = 0;
                    pb->state = 0;
                    p->state = 0;
                    __AXPushCallbackStack(p);
                }
            } else {
                fn_804085F8(p);
            }
            p->sync = 0;
            p->depop = 0;
            p->updateCounter = 0;
            p->updateMS = 0;
            p->pbPtr = p->pb;
        }
    }
    lbl_8066FAC4 = cycles;
    for (p = __AXGetStackHead(0); p != 0; p = p->next) {
        if (p->depop != 0) {
            __AXDepopVoice(&pbs[p->index]);
        }
        p->depop = 0;
        pbs[p->index].x4c = 0;
        pbs[p->index].x4a = 0;
        pbs[p->index].x48 = 0;
        pbs[p->index].x46 = 0;
        pbs[p->index].x44 = 0;
        pbs[p->index].state = 0;
    }
    DCFlushRange(pbs, 0x3D00);
    DCFlushRange(lbl_8065AE00, 0x1000);
    DCFlushRange(lbl_8065BE00, 0x4000);
}
