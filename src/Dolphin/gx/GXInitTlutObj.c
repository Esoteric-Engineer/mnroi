typedef unsigned short u16;
typedef unsigned long u32;

typedef struct {
    u32 tlut;
    u32 loadTlut0;
    u16 numEntries;
} GXTlutObj;

#define SET_REG_FIELD(reg, size, shift, val)                                   \
    (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift),                     \
                          (32 - (shift) - (size)), (31 - (shift)))

void GXInitTlutObj(GXTlutObj* tlut_obj, void* lut, u32 fmt, u16 n_entries)
{
    tlut_obj->tlut = 0;
    SET_REG_FIELD(tlut_obj->tlut, 2, 10, fmt);
    SET_REG_FIELD(tlut_obj->loadTlut0, 21, 0, (u32)lut >> 5);
    SET_REG_FIELD(tlut_obj->loadTlut0, 8, 24, 0x64);
    tlut_obj->numEntries = n_entries;
}
