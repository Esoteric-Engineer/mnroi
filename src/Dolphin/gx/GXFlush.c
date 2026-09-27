typedef unsigned char u8;
typedef unsigned long u32;

typedef struct {
    u8 pad[0x5AC];
    u32 dirtyState;
} __GXDataStruct;

extern __GXDataStruct* __GXData;

extern void __GXSetDirtyState(void);
extern void PPCSync(void);

volatile u32 GXWGFifo : 0xCC008000;

void GXFlush(void)
{
    if (__GXData->dirtyState) {
        __GXSetDirtyState();
    }
    GXWGFifo = 0;
    GXWGFifo = 0;
    GXWGFifo = 0;
    GXWGFifo = 0;
    GXWGFifo = 0;
    GXWGFifo = 0;
    GXWGFifo = 0;
    GXWGFifo = 0;
    PPCSync();
}
