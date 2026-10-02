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

static inline void PushLight(const register void* lt_obj, register void* dest)
{
    register u32 zero, color;
    register f32 a0_a1, a2_k0, k1_k2;
    register f32 px_py, pz_dx, dy_dz;

    asm {
    lwz color, 0xc(lt_obj)
    xor zero, zero, zero
    psq_l a0_a1, 0x10(lt_obj), 0, 0
    psq_l a2_k0, 0x18(lt_obj), 0, 0
    psq_l k1_k2, 0x20(lt_obj), 0, 0
    psq_l px_py, 0x28(lt_obj), 0, 0
    psq_l pz_dx, 0x30(lt_obj), 0, 0
    psq_l dy_dz, 0x38(lt_obj), 0, 0
    stw zero, 0(dest)
    stw zero, 0(dest)
    stw zero, 0(dest)
    stw color, 0(dest)
    psq_st a0_a1, 0(dest), 0, 0
    psq_st a2_k0, 0(dest), 0, 0
    psq_st k1_k2, 0(dest), 0, 0
    psq_st px_py, 0(dest), 0, 0
    psq_st pz_dx, 0(dest), 0, 0
    psq_st dy_dz, 0(dest), 0, 0
    }
}

void GXLoadLightObjImm(void* lt_obj, u32 light)
{
    u32 addr;
    u32 idx;
    void* obj;

    obj = lt_obj;

    idx = 31 - __cntlzw(light);
    idx &= 7;

    addr = 0x600 + idx * 0x10;

    GXWGFifo.u8 = 0x10;
    GXWGFifo.u32 = addr | 0xF0000;

    PushLight(obj, (void*)0xCC008000);
    __GXData->bpSentNot = 1;
}
