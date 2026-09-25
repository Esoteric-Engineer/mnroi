extern void fn_80406A0C(void);
extern void __AXVPBQuit(void);
extern void __AXSPBQuit(void);
extern void __AXAuxQuit(void);
extern void __AXClQuit(void);
extern void fn_804080D0(void);

void AXQuit(void)
{
    fn_80406A0C();
    __AXVPBQuit();
    __AXSPBQuit();
    __AXAuxQuit();
    __AXClQuit();
    fn_804080D0();
}
