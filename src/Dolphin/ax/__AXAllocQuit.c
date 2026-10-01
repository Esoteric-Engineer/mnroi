extern void* __AXStackHead[];
extern void* __AXStackTail[];
extern unsigned long lbl_8066FA08;

void __AXAllocQuit(void)
{
    int i;

    lbl_8066FA08 = 0;
    for (i = 0; i < 32; i++) {
        __AXStackTail[i] = 0;
        __AXStackHead[i] = 0;
    }
}
