typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef float f32;

typedef union {
    volatile u8 u8;
    volatile u32 u32;
    volatile f32 f32;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
} __GXDataStruct;

extern __GXDataStruct* __GXData;

static inline void WriteLightObj(register void* obj, register volatile void* dest)
{
    asm {
    lwz r0, 0xc(obj)
    xor r6, r6, r6
    psq_l f5, 0x10(obj), 0, 0
    psq_l f4, 0x18(obj), 0, 0
    psq_l f3, 0x20(obj), 0, 0
    psq_l f2, 0x28(obj), 0, 0
    psq_l f1, 0x30(obj), 0, 0
    psq_l f0, 0x38(obj), 0, 0
    stw r6, 0(dest)
    stw r6, 0(dest)
    stw r6, 0(dest)
    stw r0, 0(dest)
    psq_st f5, 0(dest), 0, 0
    psq_st f4, 0(dest), 0, 0
    psq_st f3, 0(dest), 0, 0
    psq_st f2, 0(dest), 0, 0
    psq_st f1, 0(dest), 0, 0
    psq_st f0, 0(dest), 0, 0
    }
}

void GXLoadLightObjImm(void* lt_obj, u32 light)
{
    u32 addr = ((31 - __cntlzw(light)) & 7) * 0x10 + 0x600;

    GXWGFifo.u8 = 0x10;
    GXWGFifo.u32 = addr | 0xF0000;
    WriteLightObj(lt_obj, &GXWGFifo.u32);
    __GXData->bpSentNot = 1;
}
