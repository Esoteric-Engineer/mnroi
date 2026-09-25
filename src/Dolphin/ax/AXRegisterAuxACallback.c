extern void* lbl_8066FA10;
extern unsigned long lbl_8066FA18;

void AXRegisterAuxACallback(void* callback, unsigned long context)
{
    lbl_8066FA10 = callback;
    lbl_8066FA18 = context;
}
