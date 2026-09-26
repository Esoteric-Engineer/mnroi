extern void __AXAllocQuit(void);
extern void __AXVPBQuit(void);
extern void __AXSPBQuit(void);
extern void __AXAuxQuit(void);
extern void __AXClQuit(void);
extern void __AXOutQuit(void);

void AXQuit(void)
{
    __AXAllocQuit();
    __AXVPBQuit();
    __AXSPBQuit();
    __AXAuxQuit();
    __AXClQuit();
    __AXOutQuit();
}
