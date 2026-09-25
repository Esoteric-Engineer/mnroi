extern unsigned char lbl_806509C0[];
extern unsigned long lbl_8066FA14;
extern unsigned long lbl_8066FA30;

void __AXGetAuxBInput(unsigned long* out)
{
    if (lbl_8066FA14 != 0) {
        *out = (unsigned long)(lbl_806509C0 + lbl_8066FA30 * 0x780);
    } else {
        *out = 0;
    }
}
