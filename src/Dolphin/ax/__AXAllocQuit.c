extern void* lbl_8064F228[];
extern void* lbl_8064F2A8[];
extern unsigned long lbl_8066FA08;

void __AXAllocQuit(void)
{
    int i;

    lbl_8066FA08 = 0;
    for (i = 0; i < 32; i++) {
        lbl_8064F2A8[i] = 0;
        lbl_8064F228[i] = 0;
    }
}
