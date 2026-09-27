typedef struct AXVPB {
    struct AXVPB* next;
    void* pad4[2];
    unsigned long priority;
    unsigned char pad10[0x20 - 0x10];
    unsigned long depop;
    unsigned char pad24[0x146 - 0x24];
    unsigned short state;
} AXVPB;

extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int);
extern void __AXRemoveFromStack(AXVPB* p);
extern void __AXSetPBDefault(AXVPB* p);
extern AXVPB* lbl_8064F228[];

void AXFreeVoice(AXVPB* p)
{
    int old = OSDisableInterrupts();

    __AXRemoveFromStack(p);
    if (p->state == 1) {
        p->depop = 1;
    }
    __AXSetPBDefault(p);
    p->next = lbl_8064F228[0];
    lbl_8064F228[0] = p;
    p->priority = 0;
    OSRestoreInterrupts(old);
}
