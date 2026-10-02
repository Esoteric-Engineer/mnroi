typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct {
    u32 tmemAddr;
} GXTlutRegion;

extern void __GXFlushTextureState(void);

// The CPU-side write port of the GP FIFO. Writing here issues raw GX commands directly to the graphics pipeline.
typedef union {
    volatile u8 u8;
    volatile u16 u16;
    volatile u32 u32;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

// Writes `val` into a `size`-bit field at bit `shift` of `reg`.
// Uses the CodeWarrior __rlwimi intrinsic, which emits exactly one rlwimi instruction (the plain-C mask/shift form emits extra masking).
#define SET_REG_FIELD(reg, size, shift, val)                                   \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift),                     \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXInitTlutRegion(GXTlutRegion* region, u32 tmem_addr, u32 tlut_size)
{
    region->tmemAddr = 0;
    SET_REG_FIELD(region->tmemAddr, 10, 0, (tmem_addr - 0x80000) >> 9);
    SET_REG_FIELD(region->tmemAddr, 11, 10, tlut_size);
    SET_REG_FIELD(region->tmemAddr, 8, 24, 0x65);
}

void GXInvalidateTexAll(void)
{
    __GXFlushTextureState();
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = 0x66001000;
    GXWGFifo.u8 = 0x61;
    GXWGFifo.u32 = 0x66001100;
    __GXFlushTextureState();
}
