extern unsigned long lbl_8066FA48;
extern void* lbl_8066FA4C;
extern unsigned long __AXCompressor;
extern unsigned long lbl_8066FA58;
extern unsigned char lbl_80652040[];

void __AXClInit(void)
{
    lbl_8066FA58 = 0;
    lbl_8066FA48 = 0;
    lbl_8066FA4C = lbl_80652040;
    __AXCompressor = 1;
}
