typedef unsigned char u8;
typedef unsigned long u32;
typedef float f32;

typedef union {
    volatile u8 u8;
    volatile u32 u32;
    volatile f32 f32;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

static inline void WriteMTXPS4x3(const register f32 mtx[3][4], register volatile void* dest)
{
    asm {
        psq_l f5, 0x00(mtx), 0, 0
        psq_l f4, 0x08(mtx), 0, 0
        psq_l f3, 0x10(mtx), 0, 0
        psq_l f2, 0x18(mtx), 0, 0
        psq_l f1, 0x20(mtx), 0, 0
        psq_l f0, 0x28(mtx), 0, 0
        psq_st f5, 0(dest), 0, 0
        psq_st f4, 0(dest), 0, 0
        psq_st f3, 0(dest), 0, 0
        psq_st f2, 0(dest), 0, 0
        psq_st f1, 0(dest), 0, 0
        psq_st f0, 0(dest), 0, 0
    }
}

static inline void WriteMTXPS4x2(const register f32 mtx[2][4], register volatile void* dest)
{
    asm {
        psq_l f3, 0x00(mtx), 0, 0
        psq_l f2, 0x08(mtx), 0, 0
        psq_l f1, 0x10(mtx), 0, 0
        psq_l f0, 0x18(mtx), 0, 0
        psq_st f3, 0(dest), 0, 0
        psq_st f2, 0(dest), 0, 0
        psq_st f1, 0(dest), 0, 0
        psq_st f0, 0(dest), 0, 0
    }
}

void GXLoadTexMtxImm(f32 mtx[][4], u32 id, int type)
{
    u32 reg;
    u32 addr;
    u32 count;

    if (id >= 0x40) {
        addr = (id - 0x40) * 4 + 0x500;
    } else {
        addr = id * 4;
    }
    count = (type == 1) ? 8 : 12;
    reg = addr | ((count - 1) << 16);

    GXWGFifo.u8 = 0x10;
    GXWGFifo.u32 = reg;
    if (type == 0) {
        WriteMTXPS4x3(mtx, &GXWGFifo);
    } else {
        WriteMTXPS4x2(mtx, &GXWGFifo);
    }
}
