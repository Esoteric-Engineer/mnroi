typedef unsigned long u32;

typedef struct {
    u32 tlut;
    u32 loadTlut0;
} GXTlutObj;

#define GET_REG_FIELD(reg, size, shift) ((int)((reg) >> (shift)) & ((1 << (size)) - 1))

void* GXGetTlutObjData(const GXTlutObj* tlut_obj)
{
    return (void*)(GET_REG_FIELD(tlut_obj->loadTlut0, 21, 0) << 5);
}
