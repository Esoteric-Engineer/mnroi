typedef unsigned long u32;

extern u32 PPCMfwpar(void);
extern void PPCMtwpar(u32 value);

void GXResetWriteGatherPipe(void)
{
    while (PPCMfwpar() & 1) {
    }
    PPCMtwpar(0x0C008000);
}
