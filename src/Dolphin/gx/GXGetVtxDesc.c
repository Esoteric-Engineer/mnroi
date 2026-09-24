typedef unsigned char u8;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x14];
    u32 vcdLo;
    u32 vcdHi;
    u8 pad1[0x4D4 - 0x1C];
    u8 hasNrms;
    u8 hasBiNrms;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

#define GET_REG_FIELD(reg, size, shift) ((int)((reg) >> (shift)) & ((1 << (size)) - 1))

void GXGetVtxDesc(u32 attr, u32* type)
{
    u32 cpType;

    switch (attr) {
    case 0: cpType = GET_REG_FIELD(__GXData->vcdLo, 1, 0); break;
    case 1: cpType = GET_REG_FIELD(__GXData->vcdLo, 1, 1); break;
    case 2: cpType = GET_REG_FIELD(__GXData->vcdLo, 1, 2); break;
    case 3: cpType = GET_REG_FIELD(__GXData->vcdLo, 1, 3); break;
    case 4: cpType = GET_REG_FIELD(__GXData->vcdLo, 1, 4); break;
    case 5: cpType = GET_REG_FIELD(__GXData->vcdLo, 1, 5); break;
    case 6: cpType = GET_REG_FIELD(__GXData->vcdLo, 1, 6); break;
    case 7: cpType = GET_REG_FIELD(__GXData->vcdLo, 1, 7); break;
    case 8: cpType = GET_REG_FIELD(__GXData->vcdLo, 1, 8); break;
    case 9: cpType = GET_REG_FIELD(__GXData->vcdLo, 2, 9); break;
    case 10: cpType = __GXData->hasNrms ? GET_REG_FIELD(__GXData->vcdLo, 2, 11) : 0; break;
    case 25: cpType = __GXData->hasBiNrms ? GET_REG_FIELD(__GXData->vcdLo, 2, 11) : 0; break;
    case 11: cpType = GET_REG_FIELD(__GXData->vcdLo, 2, 13); break;
    case 12: cpType = GET_REG_FIELD(__GXData->vcdLo, 2, 15); break;
    case 13: cpType = GET_REG_FIELD(__GXData->vcdHi, 2, 0); break;
    case 14: cpType = GET_REG_FIELD(__GXData->vcdHi, 2, 2); break;
    case 15: cpType = GET_REG_FIELD(__GXData->vcdHi, 2, 4); break;
    case 16: cpType = GET_REG_FIELD(__GXData->vcdHi, 2, 6); break;
    case 17: cpType = GET_REG_FIELD(__GXData->vcdHi, 2, 8); break;
    case 18: cpType = GET_REG_FIELD(__GXData->vcdHi, 2, 10); break;
    case 19: cpType = GET_REG_FIELD(__GXData->vcdHi, 2, 12); break;
    case 20: cpType = GET_REG_FIELD(__GXData->vcdHi, 2, 14); break;
    default: cpType = 0; break;
    }
    *type = cpType;
}
