typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef enum {
    GX_PERF0_VERTICES,
    GX_PERF0_CLIP_VTX,
    GX_PERF0_CLIP_CLKS,
    GX_PERF0_XF_WAIT_IN,
    GX_PERF0_XF_WAIT_OUT,
    GX_PERF0_XF_XFRM_CLKS,
    GX_PERF0_XF_LIT_CLKS,
    GX_PERF0_XF_BOT_CLKS,
    GX_PERF0_XF_REGLD_CLKS,
    GX_PERF0_XF_REGRD_CLKS,
    GX_PERF0_CLIP_RATIO,

    GX_PERF0_TRIANGLES,
    GX_PERF0_TRIANGLES_CULLED,
    GX_PERF0_TRIANGLES_PASSED,
    GX_PERF0_TRIANGLES_SCISSORED,
    GX_PERF0_TRIANGLES_0TEX,
    GX_PERF0_TRIANGLES_1TEX,
    GX_PERF0_TRIANGLES_2TEX,
    GX_PERF0_TRIANGLES_3TEX,
    GX_PERF0_TRIANGLES_4TEX,
    GX_PERF0_TRIANGLES_5TEX,
    GX_PERF0_TRIANGLES_6TEX,
    GX_PERF0_TRIANGLES_7TEX,
    GX_PERF0_TRIANGLES_8TEX,
    GX_PERF0_TRIANGLES_0CLR,
    GX_PERF0_TRIANGLES_1CLR,
    GX_PERF0_TRIANGLES_2CLR,

    GX_PERF0_QUAD_0CVG,
    GX_PERF0_QUAD_NON0CVG,
    GX_PERF0_QUAD_1CVG,
    GX_PERF0_QUAD_2CVG,
    GX_PERF0_QUAD_3CVG,
    GX_PERF0_QUAD_4CVG,
    GX_PERF0_AVG_QUAD_CNT,

    GX_PERF0_CLOCKS,
    GX_PERF0_NONE
} GXPerf0;

typedef enum {
    GX_PERF1_TEXELS,
    GX_PERF1_TX_IDLE,
    GX_PERF1_TX_REGS,
    GX_PERF1_TX_MEMSTALL,
    GX_PERF1_TC_CHECK1_2,
    GX_PERF1_TC_CHECK3_4,
    GX_PERF1_TC_CHECK5_6,
    GX_PERF1_TC_CHECK7_8,
    GX_PERF1_TC_MISS,

    GX_PERF1_VC_ELEMQ_FULL,
    GX_PERF1_VC_MISSQ_FULL,
    GX_PERF1_VC_MEMREQ_FULL,
    GX_PERF1_VC_STATUS7,
    GX_PERF1_VC_MISSREP_FULL,
    GX_PERF1_VC_STREAMBUF_LOW,
    GX_PERF1_VC_ALL_STALLS,
    GX_PERF1_VERTICES,

    GX_PERF1_FIFO_REQ,
    GX_PERF1_CALL_REQ,
    GX_PERF1_VC_MISS_REQ,
    GX_PERF1_CP_ALL_REQ,

    GX_PERF1_CLOCKS,
    GX_PERF1_NONE
} GXPerf1;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x59C];
    GXPerf0 perf0;
    GXPerf1 perf1;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

extern volatile u16* __cpReg;

// The two halves of a CP counter are latched separately, so the high half is
// re-read until it is stable. Copying the pointer parameters into locals is
// what keeps each counter's tail (slwi/or) ahead of the next one's setup.
static u32 GXReadCPCounter(volatile u16* rL, volatile u16* rH)
{
    volatile u16* regH = rH;
    volatile u16* regL = rL;
    u32 ctrh, ctrl, ctrh2;

    ctrh = *regH;
    do {
        ctrh2 = ctrh;
        ctrl = *regL;
        ctrh = *regH;
    } while (ctrh != ctrh2);
    return (ctrh << 16) | ctrl;
}
void GXReadGPMetric(u32* cnt0, u32* cnt1)
{
    u32 cpCtr0, cpCtr1, cpCtr2, cpCtr3;

    cpCtr0 = GXReadCPCounter(&__cpReg[32], &__cpReg[33]);
    cpCtr1 = GXReadCPCounter(&__cpReg[34], &__cpReg[35]);
    cpCtr2 = GXReadCPCounter(&__cpReg[36], &__cpReg[37]);
    cpCtr3 = GXReadCPCounter(&__cpReg[38], &__cpReg[39]);

    switch (__GXData->perf0) {
    case GX_PERF0_CLIP_RATIO:
        *cnt0 = cpCtr1 * 0x3E8 / cpCtr0;
        break;
    case GX_PERF0_VERTICES:
    case GX_PERF0_CLIP_VTX:
    case GX_PERF0_CLIP_CLKS:
    case GX_PERF0_XF_WAIT_IN:
    case GX_PERF0_XF_WAIT_OUT:
    case GX_PERF0_XF_XFRM_CLKS:
    case GX_PERF0_XF_LIT_CLKS:
    case GX_PERF0_XF_BOT_CLKS:
    case GX_PERF0_XF_REGLD_CLKS:
    case GX_PERF0_XF_REGRD_CLKS:
    case GX_PERF0_TRIANGLES:
    case GX_PERF0_TRIANGLES_CULLED:
    case GX_PERF0_TRIANGLES_PASSED:
    case GX_PERF0_TRIANGLES_SCISSORED:
    case GX_PERF0_TRIANGLES_0TEX:
    case GX_PERF0_TRIANGLES_1TEX:
    case GX_PERF0_TRIANGLES_2TEX:
    case GX_PERF0_TRIANGLES_3TEX:
    case GX_PERF0_TRIANGLES_4TEX:
    case GX_PERF0_TRIANGLES_5TEX:
    case GX_PERF0_TRIANGLES_6TEX:
    case GX_PERF0_TRIANGLES_7TEX:
    case GX_PERF0_TRIANGLES_8TEX:
    case GX_PERF0_TRIANGLES_0CLR:
    case GX_PERF0_TRIANGLES_1CLR:
    case GX_PERF0_TRIANGLES_2CLR:
    case GX_PERF0_QUAD_0CVG:
    case GX_PERF0_QUAD_NON0CVG:
    case GX_PERF0_QUAD_1CVG:
    case GX_PERF0_QUAD_2CVG:
    case GX_PERF0_QUAD_3CVG:
    case GX_PERF0_QUAD_4CVG:
    case GX_PERF0_AVG_QUAD_CNT:
    case GX_PERF0_CLOCKS:
        *cnt0 = cpCtr0;
        break;
    case GX_PERF0_NONE:
        *cnt0 = 0;
        break;
    default:
        *cnt0 = 0;
        break;
    }

    switch (__GXData->perf1) {
    case GX_PERF1_TEXELS:
        *cnt1 = cpCtr3 * 4;
        break;
    case GX_PERF1_TC_CHECK1_2:
        *cnt1 = cpCtr2 + (cpCtr3 * 2);
        break;
    case GX_PERF1_TC_CHECK3_4:
        *cnt1 = (cpCtr2 * 3) + (cpCtr3 * 4);
        break;
    case GX_PERF1_TC_CHECK5_6:
        *cnt1 = (cpCtr2 * 5) + (cpCtr3 * 6);
        break;
    case GX_PERF1_TC_CHECK7_8:
        *cnt1 = (cpCtr2 * 7) + (cpCtr3 * 8);
        break;
    case GX_PERF1_TX_IDLE:
    case GX_PERF1_TX_REGS:
    case GX_PERF1_TX_MEMSTALL:
    case GX_PERF1_TC_MISS:
    case GX_PERF1_VC_ELEMQ_FULL:
    case GX_PERF1_VC_MISSQ_FULL:
    case GX_PERF1_VC_MEMREQ_FULL:
    case GX_PERF1_VC_STATUS7:
    case GX_PERF1_VC_MISSREP_FULL:
    case GX_PERF1_VC_STREAMBUF_LOW:
    case GX_PERF1_VC_ALL_STALLS:
    case GX_PERF1_VERTICES:
    case GX_PERF1_CLOCKS:
        *cnt1 = cpCtr3;
        break;
    case GX_PERF1_FIFO_REQ:
    case GX_PERF1_CALL_REQ:
    case GX_PERF1_VC_MISS_REQ:
    case GX_PERF1_CP_ALL_REQ:
        *cnt1 = cpCtr2;
        break;
    case GX_PERF1_NONE:
        *cnt1 = 0;
        break;
    default:
        *cnt1 = 0;
        break;
    }
}
