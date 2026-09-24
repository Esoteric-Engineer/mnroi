#pragma peephole off
extern void* memcpy(void* dst, const void* src, unsigned long n);
void __OSGetExecParams(void* dst)
{
    if (0x80000000 <= *(unsigned long*)0x800030F0) {
        memcpy(dst, *(void**)0x800030F0, 0x1C);
    } else {
        *(unsigned long*)dst = 0;
    }
}
