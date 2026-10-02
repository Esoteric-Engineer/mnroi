typedef unsigned char u8;
typedef unsigned long u32;
typedef float f32;

typedef union {
    volatile u8 u8;
    volatile u32 u32;
    volatile f32 f32;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

static inline void WriteMTXPS3x3from3x4(const register f32 mtx[3][4], register volatile void* dest)
{
    asm {
    psq_l f5, 0x00(mtx), 0, 0
    lfs f4, 0x08(mtx)
    psq_l f3, 0x10(mtx), 0, 0
    lfs f2, 0x18(mtx)
    psq_l f1, 0x20(mtx), 0, 0
    lfs f0, 0x28(mtx)
    psq_st f5, 0(dest), 0, 0
    stfs f4, 0(dest)
    psq_st f3, 0(dest), 0, 0
    stfs f2, 0(dest)
    psq_st f1, 0(dest), 0, 0
    stfs f0, 0(dest)
    }
}

void GXLoadNrmMtxImm(f32 mtx[3][4], u32 id)
{
    u32 reg;
    u32 addr;

    addr = id * 3 + 0x400;
    reg = addr | 0x80000;

    GXWGFifo.u8 = 0x10;
    GXWGFifo.u32 = reg;
    WriteMTXPS3x3from3x4(mtx, &GXWGFifo.f32);
}
