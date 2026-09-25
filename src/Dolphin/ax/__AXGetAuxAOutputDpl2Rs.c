extern unsigned char lbl_806509C0[];
extern unsigned long lbl_8066FA34;

void __AXGetAuxAOutputDpl2Rs(unsigned long* out)
{
    *out = (unsigned long)(lbl_806509C0 + lbl_8066FA34 * 0x780 + 0x500);
}
