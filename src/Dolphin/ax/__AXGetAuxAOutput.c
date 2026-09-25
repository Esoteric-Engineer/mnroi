extern unsigned char lbl_8064F340[];
extern unsigned long lbl_8066FA34;

void __AXGetAuxAOutput(unsigned long* out)
{
    *out = (unsigned long)(lbl_8064F340 + lbl_8066FA34 * 0x780);
}
