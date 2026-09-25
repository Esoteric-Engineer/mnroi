extern char* lbl_8066CED8;

extern void OSRegisterVersion(char* version);
extern void fn_80406958(void);
extern void fn_80409008(void);
extern void __AXSPBInit(void);
extern void fn_80406D94(void);
extern void __AXClInit(void);
extern void fn_80407D30(unsigned long outputMode);

void AXInitEx(unsigned long outputMode)
{
    OSRegisterVersion(lbl_8066CED8);
    fn_80406958();
    fn_80409008();
    __AXSPBInit();
    fn_80406D94();
    __AXClInit();
    fn_80407D30(outputMode);
}
