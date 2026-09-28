char lbl_804EEF88[] = "<< Dolphin SDK - AX\trelease build: Jul 29 2003 16:15:36 (0x2301) >>";
static char* __AXVersion = lbl_804EEF88;

extern void OSRegisterVersion(char* version);
extern void __AXAllocInit(void);
extern void __AXVPBInit(void);
extern void __AXSPBInit(void);
extern void __AXAuxInit(void);
extern void __AXClInit(void);
extern void __AXOutInit(unsigned long outputMode);

void AXInitEx(unsigned long outputMode)
{
    OSRegisterVersion(__AXVersion);
    __AXAllocInit();
    __AXVPBInit();
    __AXSPBInit();
    __AXAuxInit();
    __AXClInit();
    __AXOutInit(outputMode);
}
