typedef struct __va_list_struct {
    char gpr;
    char fpr;
    char reserved[2];
    char* input_arg_area;
    char* reg_save_area;
} va_list[1];

extern int vprintf(const char* format, va_list arg);
extern void OSReport(const char* msg, ...);
extern int OSDisableInterrupts(void);
extern unsigned long OSGetStackPointer(void);
extern void PPCHalt(void);

char OSPanicStr_804D0EF8[] = " in \"%s\" on line %d.\n";

void OSPanic(const char* file, int line, const char* msg, ...)
{
    va_list args;
    unsigned long i;
    unsigned long* p;

    OSDisableInterrupts();
    __builtin_va_info(&args);
    vprintf(msg, args);
    OSReport(OSPanicStr_804D0EF8, file, line);

    OSReport("\nAddress:      Back Chain    LR Save\n");
    for (i = 0, p = (unsigned long*)OSGetStackPointer(); p && (unsigned long)p != 0xffffffff && i++ < 16; p = (unsigned long*)*p) {
        OSReport("0x%08x:   0x%08x    0x%08x\n", p, p[0], p[1]);
    }

    PPCHalt();
}
