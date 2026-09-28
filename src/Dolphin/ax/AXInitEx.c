extern char* lbl_8066CED8;

extern void OSRegisterVersion(char* version);
extern void __AXAllocInit(void);
extern void __AXVPBInit(void);
extern void __AXSPBInit(void);
extern void __AXAuxInit(void);
extern void __AXClInit(void);
extern void __AXOutInit(unsigned long outputMode);

void AXInitEx(unsigned long outputMode)
{
    OSRegisterVersion(lbl_8066CED8);
    __AXAllocInit();
    __AXVPBInit();
    __AXSPBInit();
    __AXAuxInit();
    __AXClInit();
    __AXOutInit(outputMode);
}
