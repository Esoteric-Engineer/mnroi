extern void* lbl_8066FA10;
extern void* lbl_8066FA14;
extern unsigned long lbl_8066FA18;
extern unsigned long lbl_8066FA1C;
extern unsigned long lbl_8066FA30;
extern unsigned long lbl_8066FA34;
extern unsigned long lbl_8066FA38;
extern unsigned long lbl_8066FA3C;
extern unsigned long lbl_8066FA40;
extern unsigned long lbl_8064F340[];
extern unsigned long lbl_806509C0[];

void __AXAuxInit(void)
{
    unsigned long* a;
    unsigned long* b;
    int i;

    lbl_8066FA10 = 0;
    lbl_8066FA14 = 0;
    lbl_8066FA18 = 0;
    lbl_8066FA1C = 0;
    lbl_8066FA30 = 0;
    lbl_8066FA34 = 1;
    lbl_8066FA38 = 0;
    lbl_8066FA3C = 1;
    lbl_8066FA40 = 2;

    a = lbl_8064F340;
    b = lbl_806509C0;
    for (i = 0; i < 0x1E0; i++) {
        *a++ = 0;
        *b++ = 0;
    }
}
