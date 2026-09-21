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

// Real Dolphin SDK global GX state (gx). Only the fields these functions touch are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
    u8 pad1[0x59C - 0x4];
    GXPerf0 perf0;
    GXPerf1 perf1;
    u32 perfSel;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

extern volatile u16* __cpReg;

typedef union {
    volatile u8 u8;
    volatile u16 u16;
    volatile u32 u32;
} GXFifoObj;

#define GXWGFifo (*(GXFifoObj*)0xCC008000)

#define GX_WRITE_U8(ub) (GXWGFifo.u8 = (u8)(ub))
#define GX_WRITE_U32(ui) (GXWGFifo.u32 = (u32)(ui))

#define GX_WRITE_XF_REG(addr, value) \
    do {                             \
        GX_WRITE_U8(0x10);           \
        GX_WRITE_U32(0x1000 + (addr)); \
        GX_WRITE_U32(value);         \
    } while (0)

#define GX_WRITE_RAS_REG(value) \
    do {                        \
        GX_WRITE_U8(0x61);      \
        GX_WRITE_U32(value);    \
    } while (0)

#define GX_WRITE_SOME_REG4(a, b, c) \
    do {                            \
        GX_WRITE_U8(a);             \
        GX_WRITE_U8(b);             \
        GX_WRITE_U32(c);            \
    } while (0)

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXSetGPMetric(GXPerf0 perf0, GXPerf1 perf1)
{
    u32 reg;

    switch (__GXData->perf0) {
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
    case GX_PERF0_CLIP_RATIO:
    case GX_PERF0_CLOCKS:
        reg = 0;
        GX_WRITE_XF_REG(6, reg);
        break;
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
        reg = 0x23000000;
        GX_WRITE_RAS_REG(reg);
        break;
    case GX_PERF0_QUAD_0CVG:
    case GX_PERF0_QUAD_NON0CVG:
    case GX_PERF0_QUAD_1CVG:
    case GX_PERF0_QUAD_2CVG:
    case GX_PERF0_QUAD_3CVG:
    case GX_PERF0_QUAD_4CVG:
    case GX_PERF0_AVG_QUAD_CNT:
        reg = 0x24000000;
        GX_WRITE_RAS_REG(reg);
        break;
    case GX_PERF0_NONE:
        break;
    }

    switch (__GXData->perf1) {
    case GX_PERF1_TEXELS:
    case GX_PERF1_TX_IDLE:
    case GX_PERF1_TX_REGS:
    case GX_PERF1_TX_MEMSTALL:
    case GX_PERF1_TC_CHECK1_2:
    case GX_PERF1_TC_CHECK3_4:
    case GX_PERF1_TC_CHECK5_6:
    case GX_PERF1_TC_CHECK7_8:
    case GX_PERF1_TC_MISS:
    case GX_PERF1_CLOCKS:
        reg = 0x67000000;
        GX_WRITE_RAS_REG(reg);
        break;
    case GX_PERF1_VC_ELEMQ_FULL:
    case GX_PERF1_VC_MISSQ_FULL:
    case GX_PERF1_VC_MEMREQ_FULL:
    case GX_PERF1_VC_STATUS7:
    case GX_PERF1_VC_MISSREP_FULL:
    case GX_PERF1_VC_STREAMBUF_LOW:
    case GX_PERF1_VC_ALL_STALLS:
    case GX_PERF1_VERTICES:
        SET_REG_FIELD(__GXData->perfSel, 4, 4, 0);
        GX_WRITE_SOME_REG4(8, 0x20, __GXData->perfSel);
        break;
    case GX_PERF1_FIFO_REQ:
    case GX_PERF1_CALL_REQ:
    case GX_PERF1_VC_MISS_REQ:
    case GX_PERF1_CP_ALL_REQ:
        reg = 0;
        __cpReg[3] = reg;
        break;
    case GX_PERF1_NONE:
        break;
    }

    __GXData->perf0 = perf0;
    switch (__GXData->perf0) {
    case GX_PERF0_VERTICES:            reg = 0x273;      GX_WRITE_XF_REG(6, reg); break;
    case GX_PERF0_CLIP_VTX:            reg = 0x14A;      GX_WRITE_XF_REG(6, reg); break;
    case GX_PERF0_CLIP_CLKS:           reg = 0x16B;      GX_WRITE_XF_REG(6, reg); break;
    case GX_PERF0_XF_WAIT_IN:          reg = 0x84;       GX_WRITE_XF_REG(6, reg); break;
    case GX_PERF0_XF_WAIT_OUT:         reg = 0xC6;       GX_WRITE_XF_REG(6, reg); break;
    case GX_PERF0_XF_XFRM_CLKS:        reg = 0x210;      GX_WRITE_XF_REG(6, reg); break;
    case GX_PERF0_XF_LIT_CLKS:         reg = 0x252;      GX_WRITE_XF_REG(6, reg); break;
    case GX_PERF0_XF_BOT_CLKS:         reg = 0x231;      GX_WRITE_XF_REG(6, reg); break;
    case GX_PERF0_XF_REGLD_CLKS:       reg = 0x1AD;      GX_WRITE_XF_REG(6, reg); break;
    case GX_PERF0_XF_REGRD_CLKS:       reg = 0x1CE;      GX_WRITE_XF_REG(6, reg); break;
    case GX_PERF0_CLOCKS:              reg = 0x21;       GX_WRITE_XF_REG(6, reg); break;
    case GX_PERF0_CLIP_RATIO:          reg = 0x153;      GX_WRITE_XF_REG(6, reg); break;
    case GX_PERF0_TRIANGLES:           reg = 0x2300AE7F; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_CULLED:    reg = 0x23008E7F; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_PASSED:    reg = 0x23009E7F; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_SCISSORED: reg = 0x23001E7F; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_0TEX:      reg = 0x2300AC3F; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_1TEX:      reg = 0x2300AC7F; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_2TEX:      reg = 0x2300ACBF; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_3TEX:      reg = 0x2300ACFF; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_4TEX:      reg = 0x2300AD3F; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_5TEX:      reg = 0x2300AD7F; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_6TEX:      reg = 0x2300ADBF; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_7TEX:      reg = 0x2300ADFF; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_8TEX:      reg = 0x2300AE3F; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_0CLR:      reg = 0x2300A27F; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_1CLR:      reg = 0x2300A67F; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_2CLR:      reg = 0x2300AA7F; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_QUAD_0CVG:           reg = 0x2402C0C6; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_QUAD_NON0CVG:        reg = 0x2402C16B; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_QUAD_1CVG:           reg = 0x2402C0E7; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_QUAD_2CVG:           reg = 0x2402C108; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_QUAD_3CVG:           reg = 0x2402C129; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_QUAD_4CVG:           reg = 0x2402C14A; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_AVG_QUAD_CNT:        reg = 0x2402C1AD; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_NONE: break;
    }

    __GXData->perf1 = perf1;
    switch (__GXData->perf1) {
    case GX_PERF1_TEXELS:      reg = 0x67000042; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF1_TX_IDLE:     reg = 0x67000084; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF1_TX_REGS:     reg = 0x67000063; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF1_TX_MEMSTALL: reg = 0x67000129; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF1_TC_MISS:     reg = 0x67000252; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF1_CLOCKS:      reg = 0x67000021; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF1_TC_CHECK1_2: reg = 0x6700014B; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF1_TC_CHECK3_4: reg = 0x6700018D; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF1_TC_CHECK5_6: reg = 0x670001CF; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF1_TC_CHECK7_8: reg = 0x67000211; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF1_VC_ELEMQ_FULL:    SET_REG_FIELD(__GXData->perfSel, 4, 4, 2); GX_WRITE_SOME_REG4(8, 0x20, __GXData->perfSel); break;
    case GX_PERF1_VC_MISSQ_FULL:    SET_REG_FIELD(__GXData->perfSel, 4, 4, 3); GX_WRITE_SOME_REG4(8, 0x20, __GXData->perfSel); break;
    case GX_PERF1_VC_MEMREQ_FULL:   SET_REG_FIELD(__GXData->perfSel, 4, 4, 4); GX_WRITE_SOME_REG4(8, 0x20, __GXData->perfSel); break;
    case GX_PERF1_VC_STATUS7:       SET_REG_FIELD(__GXData->perfSel, 4, 4, 5); GX_WRITE_SOME_REG4(8, 0x20, __GXData->perfSel); break;
    case GX_PERF1_VC_MISSREP_FULL:  SET_REG_FIELD(__GXData->perfSel, 4, 4, 6); GX_WRITE_SOME_REG4(8, 0x20, __GXData->perfSel); break;
    case GX_PERF1_VC_STREAMBUF_LOW: SET_REG_FIELD(__GXData->perfSel, 4, 4, 7); GX_WRITE_SOME_REG4(8, 0x20, __GXData->perfSel); break;
    case GX_PERF1_VC_ALL_STALLS:    SET_REG_FIELD(__GXData->perfSel, 4, 4, 9); GX_WRITE_SOME_REG4(8, 0x20, __GXData->perfSel); break;
    case GX_PERF1_VERTICES:         SET_REG_FIELD(__GXData->perfSel, 4, 4, 8); GX_WRITE_SOME_REG4(8, 0x20, __GXData->perfSel); break;
    case GX_PERF1_FIFO_REQ:    reg = 2; __cpReg[3] = reg; break;
    case GX_PERF1_CALL_REQ:    reg = 3; __cpReg[3] = reg; break;
    case GX_PERF1_VC_MISS_REQ: reg = 4; __cpReg[3] = reg; break;
    case GX_PERF1_CP_ALL_REQ:  reg = 5; __cpReg[3] = reg; break;
    case GX_PERF1_NONE: break;
    }

    __GXData->bpSentNot = 0;
}

#define GX_GET_CP_REG(offset) (*(volatile u16*)((__cpReg) + (offset)))

inline u32 __GXReadCPCounterU32(u32 regAddrL, u32 regAddrH)
{
    u32 ctrH0;
    u32 ctrH1;
    u32 ctrL;

    ctrH0 = GX_GET_CP_REG(regAddrH);
    while (1) {
        ctrH1 = ctrH0;
        ctrL = GX_GET_CP_REG(regAddrL);
        ctrH0 = GX_GET_CP_REG(regAddrH);

        if (ctrH0 == ctrH1) {
            break;
        }
    }

    return (ctrH0 << 16) | (ctrL);
}

#pragma scheduling off
void GXReadGPMetric(u32* cnt0, u32* cnt1)
{
    u32 cpCtr0, cpCtr1, cpCtr2, cpCtr3;

    cpCtr0 = __GXReadCPCounterU32(32, 33);
    cpCtr1 = __GXReadCPCounterU32(34, 35);
    cpCtr2 = __GXReadCPCounterU32(36, 37);
    cpCtr3 = __GXReadCPCounterU32(38, 39);

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
