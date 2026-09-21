extern unsigned long fn_8017AA48(void);

extern unsigned long lbl_8066F4B0;
extern unsigned long lbl_8066F4B4;
extern unsigned long lbl_8066F4B8;
extern unsigned long lbl_8066F4BC;

int InitializeUART(void)
{
    if (lbl_8066F4BC == 0xA5FF005A) {
        return 0;
    }

    if ((fn_8017AA48() & 0x10000000) == 0) {
        lbl_8066F4B8 = 0;
        return 2;
    }

    lbl_8066F4B0 = 0;
    lbl_8066F4B4 = 1;
    lbl_8066F4B8 = 0xA5FF005A;
    return 0;
}
