extern unsigned char lbl_806509C0[];
extern unsigned long lbl_8066FA30;

void __AXGetAuxAInputDpl2(unsigned long* out)
{
    *out = (unsigned long)(lbl_806509C0 + lbl_8066FA30 * 0x780 + 0x500);
}
