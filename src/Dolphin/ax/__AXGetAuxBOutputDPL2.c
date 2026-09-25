extern unsigned char lbl_806509C0[];
extern unsigned long lbl_8066FA3C;

void __AXGetAuxBOutputDPL2(unsigned long* out)
{
    *out = (unsigned long)(lbl_806509C0 + lbl_8066FA3C * 0x780);
}
