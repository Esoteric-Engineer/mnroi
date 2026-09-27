typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define ALIGN_NEXT(u, align) ((u + (align - 1)) & (~(align - 1)))
#define OSPhysicalToUncached(paddr) ((void*)((u32)(paddr) + 0xC0000000))

#define DSP_CONTROL_STATUS   (5)
#define DSP_ARAM_SIZE        (9)
#define DSP_ARAM_MODE        (11)
#define DSP_ARAM_DMA_MM_HI   (16)
#define DSP_ARAM_DMA_MM_LO   (17)
#define DSP_ARAM_DMA_ARAM_HI (18)
#define DSP_ARAM_DMA_ARAM_LO (19)
#define DSP_ARAM_DMA_SIZE_HI (20)
#define DSP_ARAM_DMA_SIZE_LO (21)

extern void* memset(void* dst, int val, u32 n);
extern void DCFlushRange(void* addr, u32 nBytes);
extern void DCInvalidateRange(void* addr, u32 nBytes);
extern void PPCSync(void);

extern u32 lbl_8066F9BC; // __AR_Size
extern u32 lbl_8066F9C0; // __AR_InternalSize
extern u32 lbl_8066F9C4; // __AR_ExpansionSize

volatile u16 __DSPRegs[0x200] : 0xCC005000;

static inline void __ARClearInterrupt(void)
{
    u16 tmp = __DSPRegs[DSP_CONTROL_STATUS];
    tmp = (tmp & ~0x88) | 0x20;
    __DSPRegs[DSP_CONTROL_STATUS] = tmp;
}

static inline void __ARWaitForDMA(void)
{
    while (__DSPRegs[DSP_CONTROL_STATUS] & 0x200)
        ;
}

static inline void __ARWriteDMA(u32 mmem_addr, u32 aram_addr, u32 length)
{
    __DSPRegs[DSP_ARAM_DMA_MM_HI]
        = (u16)((__DSPRegs[DSP_ARAM_DMA_MM_HI] & ~0x03ff)
                | (u16)(mmem_addr >> 16));
    __DSPRegs[DSP_ARAM_DMA_MM_LO]
        = (u16)((__DSPRegs[DSP_ARAM_DMA_MM_LO] & ~0xffe0)
                | (u16)(mmem_addr & 0xffff));

    __DSPRegs[DSP_ARAM_DMA_ARAM_HI]
        = (u16)((__DSPRegs[DSP_ARAM_DMA_ARAM_HI] & ~0x03ff)
                | (u16)(aram_addr >> 16));
    __DSPRegs[DSP_ARAM_DMA_ARAM_LO]
        = (u16)((__DSPRegs[DSP_ARAM_DMA_ARAM_LO] & ~0xffe0)
                | (u16)(aram_addr & 0xffff));

    __DSPRegs[DSP_ARAM_DMA_SIZE_HI]
        = (u16)(__DSPRegs[DSP_ARAM_DMA_SIZE_HI] & ~0x8000);

    __DSPRegs[DSP_ARAM_DMA_SIZE_HI]
        = (u16)((__DSPRegs[DSP_ARAM_DMA_SIZE_HI] & ~0x03ff)
                | (u16)(length >> 16));
    __DSPRegs[DSP_ARAM_DMA_SIZE_LO]
        = (u16)((__DSPRegs[DSP_ARAM_DMA_SIZE_LO] & ~0xffe0)
                | (u16)(length & 0xffff));

    __ARWaitForDMA();
    __ARClearInterrupt();
}

static inline void __ARReadDMA(u32 mmem_addr, u32 aram_addr, u32 length)
{
    __DSPRegs[DSP_ARAM_DMA_MM_HI]
        = (u16)((__DSPRegs[DSP_ARAM_DMA_MM_HI] & ~0x03ff)
                | (u16)(mmem_addr >> 16));
    __DSPRegs[DSP_ARAM_DMA_MM_LO]
        = (u16)((__DSPRegs[DSP_ARAM_DMA_MM_LO] & ~0xffe0)
                | (u16)(mmem_addr & 0xffff));

    __DSPRegs[DSP_ARAM_DMA_ARAM_HI]
        = (u16)((__DSPRegs[DSP_ARAM_DMA_ARAM_HI] & ~0x03ff)
                | (u16)(aram_addr >> 16));
    __DSPRegs[DSP_ARAM_DMA_ARAM_LO]
        = (u16)((__DSPRegs[DSP_ARAM_DMA_ARAM_LO] & ~0xffe0)
                | (u16)(aram_addr & 0xffff));

    __DSPRegs[DSP_ARAM_DMA_SIZE_HI]
        = (u16)(__DSPRegs[DSP_ARAM_DMA_SIZE_HI] | 0x8000);

    __DSPRegs[DSP_ARAM_DMA_SIZE_HI]
        = (u16)((__DSPRegs[DSP_ARAM_DMA_SIZE_HI] & ~0x03ff)
                | (u16)(length >> 16));
    __DSPRegs[DSP_ARAM_DMA_SIZE_LO]
        = (u16)((__DSPRegs[DSP_ARAM_DMA_SIZE_LO] & ~0xffe0)
                | (u16)(length & 0xffff));

    __ARWaitForDMA();
    __ARClearInterrupt();
}

void __ARChecksize(void)
{
    u8 test_data_pad[63];
    u8 dummy_data_pad[63];
    u8 buffer_pad[63];
    u32* test_data;
    u32* dummy_data;
    u32* buffer;
    u16 ARAM_mode;
    u32 ARAM_size;
    u32 i;

    do {
    } while (!(__DSPRegs[DSP_ARAM_MODE] & 1));

    ARAM_mode = 3;
    ARAM_size = lbl_8066F9C0 = 0x1000000;

    __DSPRegs[DSP_ARAM_SIZE]
        = ((__DSPRegs[DSP_ARAM_SIZE] & 0xFFFFFFC0) | ARAM_mode) | 0x20;

    test_data  = (void*)ALIGN_NEXT((u32)test_data_pad, 0x20);
    dummy_data = (void*)ALIGN_NEXT((u32)dummy_data_pad, 0x20);
    buffer     = (void*)ALIGN_NEXT((u32)buffer_pad, 0x20);
    for (i = 0; i < 8; i++) {
        test_data[i]  = 0xDEADBEEF;
        dummy_data[i] = 0xBAD0BAD0;
    }

    DCFlushRange(test_data, 0x20);
    DCFlushRange(dummy_data, 0x20);

    lbl_8066F9C4 = 0;

    __ARWriteDMA((u32)dummy_data, ARAM_size + 0x0, 0x20U);
    __ARWriteDMA((u32)dummy_data, ARAM_size + 0x200000, 0x20U);
    __ARWriteDMA((u32)dummy_data, ARAM_size + 0x1000000, 0x20U);
    __ARWriteDMA((u32)dummy_data, ARAM_size + 0x200, 0x20U);
    __ARWriteDMA((u32)dummy_data, ARAM_size + 0x400000, 0x20U);

    memset(buffer, 0, 0x20);
    DCFlushRange(buffer, 0x20);

    __ARWriteDMA((u32)test_data, ARAM_size, 0x20U);
    DCInvalidateRange(buffer, 0x20);

    __ARReadDMA((u32)buffer, ARAM_size, 0x20U);
    PPCSync();

    if (*buffer == *test_data) {
        memset(buffer, 0, 0x20);
        DCFlushRange(buffer, 0x20);

        __ARReadDMA((u32)buffer, ARAM_size + 0x200000, 0x20U);
        PPCSync();

        if (*buffer == *test_data) {
            ARAM_size += 0x200000;
            lbl_8066F9C4 = 0x200000;
        } else {
            memset(buffer, 0, 0x20);
            DCFlushRange(buffer, 0x20);

            __ARReadDMA((u32)buffer, ARAM_size + 0x01000000, 0x20U);
            PPCSync();

            if (*buffer == *test_data) {
                ARAM_mode |= 8;
                ARAM_size += 0x400000;
                lbl_8066F9C4 = 0x400000;
            } else {
                memset(buffer, 0, 0x20);
                DCFlushRange(buffer, 0x20);

                __ARReadDMA((u32)buffer, ARAM_size + 0x200, 0x20U);
                PPCSync();

                if (*buffer == *test_data) {
                    ARAM_mode |= 0x10;
                    ARAM_size += 0x800000;
                    lbl_8066F9C4 = 0x800000;
                } else {
                    memset(buffer, 0, 0x20);
                    DCFlushRange(buffer, 0x20);

                    __ARReadDMA((u32)buffer, ARAM_size + 0x400000, 0x20U);
                    PPCSync();

                    if (*buffer == *test_data) {
                        ARAM_mode |= 0x18;
                        ARAM_size += 0x01000000;
                        lbl_8066F9C4 = 0x1000000;
                    } else {
                        ARAM_mode |= 0x20;
                        ARAM_size += 0x02000000;
                        lbl_8066F9C4 = 0x2000000;
                    }
                }
            }
        }

        __DSPRegs[DSP_ARAM_SIZE]
            = ((u16)(__DSPRegs[DSP_ARAM_SIZE] & 0xFFFFFFC0) | ARAM_mode);
    }
    *(u32*)OSPhysicalToUncached(0xD0) = ARAM_size;
    lbl_8066F9BC                      = ARAM_size;
}
