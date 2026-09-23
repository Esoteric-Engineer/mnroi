typedef int BOOL;

typedef struct SramControlBlock {
    unsigned char sram[64];
    unsigned long offset;
    BOOL enabled;
    BOOL locked;
    BOOL sync;
} SramControlBlock;

extern SramControlBlock Scb;

extern BOOL WriteSram(void* buffer, unsigned long offset, unsigned long size);

void WriteSramCallback(long chan, void* ctx)
{
    Scb.sync = WriteSram(Scb.sram + Scb.offset, Scb.offset, 64 - Scb.offset);

    if (Scb.sync) {
        Scb.offset = 64;
    }
}
