extern unsigned long lbl_8066FA48;
extern void* lbl_8066FA4C;
extern unsigned char lbl_80652040[];

void* __AXGetCommandListAddress(void)
{
    void* addr = lbl_80652040 + lbl_8066FA48++ * 0x300;
    lbl_8066FA48 &= 1;
    lbl_8066FA4C = lbl_80652040 + lbl_8066FA48 * 0x300;
    return addr;
}
