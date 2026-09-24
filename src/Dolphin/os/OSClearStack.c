typedef unsigned char u8;
typedef unsigned long u32;

typedef struct OSThread {
    u8 pad[0x308];
    u32* stackEnd;
} OSThread;

extern u32 OSGetStackPointer(void);

OSThread* __gCurrentThread : 0x800000E4;

void OSClearStack(u8 val)
{
    u32 sp;
    u32* p;
    u32 pattern = ((u32)val << 24) | ((u32)val << 16) | ((u32)val << 8) | val;

    sp = OSGetStackPointer();
    for (p = __gCurrentThread->stackEnd + 1; p < (u32*)sp; p++) {
        *p = pattern;
    }
}
