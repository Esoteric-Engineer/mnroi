typedef unsigned long u32;
typedef unsigned short u16;

typedef struct OSContext {
    u32 gpr[32];
    u32 cr;
    u32 lr;
    u32 ctr;
    u32 xer;
    double fpr[32];
    u32 fpscr_pad;
    u32 fpscr;
    u32 srr0;
    u32 srr1;
} OSContext;

extern void OSReport(char* msg, ...);
extern void DBPrintf(char* msg, ...);
extern void OSDumpContext(OSContext* context);
extern void PPCHalt(void);
extern u32 PPCMfhid0(void);
extern u32 PPCMfhid2(void);
extern void PPCMthid2(u32 val);
extern u32 PPCMfl2cr(void);
extern void PPCMtl2cr(u32 val);
extern u32 PPCMfmsr(void);
extern void PPCMtmsr(u32 val);
extern void ICEnable(void);
extern void DCEnable(void);
extern void L2GlobalInvalidate(void);
extern void OSSetErrorHandler(u16 error, void* handler);

char L2InvalidateStr[] = ">>> L2 INVALIDATE : SHOULD NEVER HAPPEN\n";

#pragma peephole off

void DMAErrorHandler(u16 error, OSContext* context, ...)
{
    u32 hid2 = PPCMfhid2();

    OSReport("Machine check received\n");
    OSReport("HID2 = 0x%x   SRR1 = 0x%x\n", hid2, context->srr1);
    if (!(hid2 & 0x00F00000) || !(context->srr1 & 0x00200000)) {
        OSReport("Machine check was not DMA/locked cache related\n");
        OSDumpContext(context);
        PPCHalt();
    }

    OSReport("DMAErrorHandler(): An error occurred while processing DMA.\n");
    OSReport("The following errors have been detected and cleared :\n");

    if (hid2 & 0x00800000) {
        OSReport("\t- Requested a locked cache tag that was already in the cache\n");
    }
    if (hid2 & 0x00400000) {
        OSReport("\t- DMA attempted to access normal cache\n");
    }
    if (hid2 & 0x00200000) {
        OSReport("\t- DMA missed in data cache\n");
    }
    if (hid2 & 0x00100000) {
        OSReport("\t- DMA queue overflowed\n");
    }

    PPCMthid2(hid2);
}

void __OSCacheInit(void)
{
    if (!(PPCMfhid0() & 0x8000)) {
        ICEnable();
        DBPrintf("L1 i-caches initialized\n");
    }
    if (!(PPCMfhid0() & 0x4000)) {
        DCEnable();
        DBPrintf("L1 d-caches initialized\n");
    }
    if (!(PPCMfl2cr() & 0x80000000)) {
        u32 oldMSR = PPCMfmsr();
        asm { sync }
        PPCMtmsr(0x30);
        asm { sync }
        asm { sync }
        PPCMtl2cr(PPCMfl2cr() & 0x7FFFFFFF);
        asm { sync }
        L2GlobalInvalidate();
        PPCMtmsr(oldMSR);
        PPCMtl2cr((PPCMfl2cr() | 0x80000000) & 0xFFDFFFFF);
        DBPrintf("L2 cache initialized\n");
    }
    OSSetErrorHandler(1, DMAErrorHandler);
    DBPrintf("Locked cache machine check handler installed\n");
}
