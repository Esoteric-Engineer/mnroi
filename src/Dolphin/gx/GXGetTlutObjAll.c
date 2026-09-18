typedef unsigned short u16;
typedef unsigned long u32;

typedef struct {
    u32 tlut;
    u32 loadTlut0;
    u16 numEntries;
} GXTlutObj;

#define GET_REG_FIELD(reg, size, shift) ((int)((reg) >> (shift)) & ((1 << (size)) - 1))

void GXGetTlutObjAll(const GXTlutObj* tlut_obj, void** data, u32* format, u16* numEntries)
{
    *data = (void*)(GET_REG_FIELD(tlut_obj->loadTlut0, 21, 0) << 5);
    *format = GET_REG_FIELD(tlut_obj->tlut, 2, 10);
    *numEntries = tlut_obj->numEntries;
}
