typedef unsigned char u8;
typedef unsigned long u32;

// Real Dolphin SDK global GX state (gx). Only the fields this function touches are declared. The rest is padding to keep their offsets correct.
typedef struct {
    u8 pad0[0x14];
    u32 vcdLo;
    u32 vcdHi;
    u8 pad1[0x4D0 - 0x1C];
    u32 nrmType;
    u8 hasNrms;
    u8 hasBiNrms;
    u8 pad2[0x5AC - 0x4D6];
    u32 dirtyState;
} __GXDataStruct;

extern __GXDataStruct* const __GXData;

#define SET_REG_FIELD(reg, size, shift, val)               \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift), \
                          (32 - (shift) - (size)), (31 - (shift)))

typedef enum { A_NULL = 0xFF, A_MAX = 0x7FFFFFFF } GXAttr;
typedef enum { T_NONE = 0, T_MAX = 0x7FFFFFFF } GXAttrType;
typedef struct {
    GXAttr attr;
    GXAttrType type;
} GXVtxDescList;

static inline void SETVCDATTR(GXAttr attr, GXAttrType type)
{
    switch (attr) {
    case 0: SET_REG_FIELD(__GXData->vcdLo, 1, 0, type); break;
    case 1: SET_REG_FIELD(__GXData->vcdLo, 1, 1, type); break;
    case 2: SET_REG_FIELD(__GXData->vcdLo, 1, 2, type); break;
    case 3: SET_REG_FIELD(__GXData->vcdLo, 1, 3, type); break;
    case 4: SET_REG_FIELD(__GXData->vcdLo, 1, 4, type); break;
    case 5: SET_REG_FIELD(__GXData->vcdLo, 1, 5, type); break;
    case 6: SET_REG_FIELD(__GXData->vcdLo, 1, 6, type); break;
    case 7: SET_REG_FIELD(__GXData->vcdLo, 1, 7, type); break;
    case 8: SET_REG_FIELD(__GXData->vcdLo, 1, 8, type); break;
    case 9: SET_REG_FIELD(__GXData->vcdLo, 2, 9, type); break;
    case 10:
        if (type != 0) {
            __GXData->hasNrms = 1;
            __GXData->hasBiNrms = 0;
            __GXData->nrmType = type;
        } else {
            __GXData->hasNrms = 0;
        }
        break;
    case 25:
        if (type != 0) {
            __GXData->hasBiNrms = 1;
            __GXData->hasNrms = 0;
            __GXData->nrmType = type;
        } else {
            __GXData->hasBiNrms = 0;
        }
        break;
    case 11: SET_REG_FIELD(__GXData->vcdLo, 2, 13, type); break;
    case 12: SET_REG_FIELD(__GXData->vcdLo, 2, 15, type); break;
    case 13: SET_REG_FIELD(__GXData->vcdHi, 2, 0, type); break;
    case 14: SET_REG_FIELD(__GXData->vcdHi, 2, 2, type); break;
    case 15: SET_REG_FIELD(__GXData->vcdHi, 2, 4, type); break;
    case 16: SET_REG_FIELD(__GXData->vcdHi, 2, 6, type); break;
    case 17: SET_REG_FIELD(__GXData->vcdHi, 2, 8, type); break;
    case 18: SET_REG_FIELD(__GXData->vcdHi, 2, 10, type); break;
    case 19: SET_REG_FIELD(__GXData->vcdHi, 2, 12, type); break;
    case 20: SET_REG_FIELD(__GXData->vcdHi, 2, 14, type); break;
    }
}

void GXSetVtxDescv(const GXVtxDescList* list)
{
    while (list->attr != A_NULL) {
        SETVCDATTR(list->attr, list->type);
        list++;
    }
    if (__GXData->hasNrms || __GXData->hasBiNrms) {
        SET_REG_FIELD(__GXData->vcdLo, 2, 11, __GXData->nrmType);
    } else {
        SET_REG_FIELD(__GXData->vcdLo, 2, 11, 0);
    }
    __GXData->dirtyState |= 8;
}
