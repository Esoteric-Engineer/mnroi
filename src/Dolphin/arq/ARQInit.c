char lbl_804EEF40[] = "<< Dolphin SDK - ARQ\trelease build: Apr 17 2003 12:33:56 (0x2301) >>";
static char* __ARQVersion = lbl_804EEF40;

extern void* lbl_8066F9D8;
extern void* lbl_8066F9E0;
extern void* lbl_8066F9F0;
extern void* lbl_8066F9F4;
extern void* lbl_8066F9F8;
extern void* lbl_8066F9FC;
extern unsigned long lbl_8066FA00;
extern int lbl_8066FA04;

extern void OSRegisterVersion(char* version);
extern void ARRegisterDMACallback(void (*callback)(void));
extern void __ARQInterruptServiceRoutine(void);

void ARQInit(void)
{
    if (lbl_8066FA04 != 1) {
        OSRegisterVersion(__ARQVersion);
        lbl_8066F9D8 = lbl_8066F9E0 = 0;
        lbl_8066FA00 = 0x1000;
        ARRegisterDMACallback(__ARQInterruptServiceRoutine);
        lbl_8066F9F0 = 0;
        lbl_8066F9F4 = 0;
        lbl_8066F9F8 = 0;
        lbl_8066F9FC = 0;
        lbl_8066FA04 = 1;
    }
}
