extern unsigned int PPCMfhid2(void);
extern void PPCMthid2(unsigned int val);
extern void ICFlashInvalidate(void);

void __OSPSInit(void)
{
    PPCMthid2(PPCMfhid2() | 0x80000000 | 0x20000000);
    ICFlashInvalidate();
    asm {
        sync
        li r3, 0
        mtspr GQR0, r3
        mtspr GQR1, r3
        mtspr GQR2, r3
        mtspr GQR3, r3
        mtspr GQR4, r3
        mtspr GQR5, r3
        mtspr GQR6, r3
        mtspr GQR7, r3
    }
}
