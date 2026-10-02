typedef unsigned short u16;
typedef unsigned long u32;

typedef struct OSContext {
    u32 gpr[32];
    u32 pad[0x1A0 / 4 - 32];
    u16 mode;
    u16 state;
} OSContext;

#define __OSFPUContext (*(OSContext**)0x800000D8)

#pragma peephole off
void OSClearContext(OSContext* context)
{
    context->mode = 0;
    context->state = 0;
    if (context == __OSFPUContext)
        __OSFPUContext = 0;
}
