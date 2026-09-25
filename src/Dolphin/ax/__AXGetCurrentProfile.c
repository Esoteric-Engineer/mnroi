extern unsigned long lbl_8066FAD0;
extern unsigned long lbl_8066FAD4;
extern unsigned long lbl_8066FAD8;
extern unsigned long lbl_8066FADC;

void* __AXGetCurrentProfile(void)
{
    void* profile;

    if (lbl_8066FADC != 0) {
        profile = (void*)(lbl_8066FAD0 + lbl_8066FAD8++ * 0x38);
        lbl_8066FAD8 %= lbl_8066FAD4;
        return profile;
    }
    return 0;
}
