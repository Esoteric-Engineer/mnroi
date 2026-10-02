extern unsigned long __AXSpbABS;
extern unsigned long __AXSpbABR;
extern unsigned long __AXSpbABL;
extern unsigned long __AXSpbAAS;
extern unsigned long __AXSpbAAR;
extern unsigned long __AXSpbAAL;
extern unsigned long __AXSpbAS;
extern unsigned long __AXSpbAR;
extern unsigned long __AXSpbAL;

void __AXSPBInit(void)
{
    __AXSpbABS = 0;
    __AXSpbABR = 0;
    __AXSpbABL = 0;
    __AXSpbAAS = 0;
    __AXSpbAAR = 0;
    __AXSpbAAL = 0;
    __AXSpbAS = 0;
    __AXSpbAR = 0;
    __AXSpbAL = 0;
}
