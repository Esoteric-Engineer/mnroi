extern long long OSGetTime(void);
extern void AIInitDMA(void*, unsigned long);
extern void fn_80407960(unsigned long);
extern void fn_804097F4(void*);

extern char lbl_80652640[];
extern char lbl_80657040[0x80];
extern unsigned long lbl_8066FA64;
extern unsigned long lbl_8066FA68;
extern volatile long long lbl_8066FA70;
extern unsigned long lbl_8066FA90;

void __AXOutAiCallback(void)
{
    if (lbl_8066FA68 == 0) {
        lbl_8066FA70 = OSGetTime();
    }
    if (lbl_8066FA68 == 1) {
        lbl_8066FA68 = 0;
        fn_80407960(0);
    } else {
        lbl_8066FA68 = 2;
        fn_804097F4(lbl_80657040);
    }
    if (lbl_8066FA90 == 1) {
        AIInitDMA(lbl_80652640 + lbl_8066FA64 * 0x280, 0x280);
        lbl_8066FA64 = lbl_8066FA64 + 1;
        lbl_8066FA64 = lbl_8066FA64 % 3;
    }
}
