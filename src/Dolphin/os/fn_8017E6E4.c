typedef unsigned int u32;
typedef struct {
    double d[0x2C8 / 8];
} Context;

extern int OSDisableInterrupts(void);
extern void OSSetArenaLo(void* addr);
extern void OSSetArenaHi(void* addr);
extern void OSClearContext(void* context);
extern void OSSetCurrentContext(void* context);
extern void fn_8017D9EC(u32 a, u32 b, u32* c);

void fn_8017E6E4(u32 a, u32 b)
{
    Context context;
    u32 zero;

    OSDisableInterrupts();
    OSSetArenaLo((void*)0x81280000);
    OSSetArenaHi((void*)0x812F0000);
    OSClearContext(&context);
    OSSetCurrentContext(&context);
    zero = 0;
    fn_8017D9EC(b, a | 0x80000000, &zero);
}
