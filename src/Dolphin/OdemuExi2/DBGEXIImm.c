typedef unsigned long u32;
typedef unsigned char u8;
typedef int BOOL;
typedef long s32;

volatile u32 __EXIRegs[0x40] : 0xCC006800;

static inline BOOL DBGEXISync(void)
{
    while (__EXIRegs[13] & 1)
        ;
    return 1;
}

BOOL DBGEXIImm(void* data, s32 byte_size, u32 write)
{
    u32 writeVal;
    u32 readVal;
    int i;

    if (write) {
        writeVal = 0;
        for (i = 0; i < byte_size; ++i) {
            u8* nextWordPtr = (u8*)data + i;
            writeVal |= *nextWordPtr << ((3 - i) << 3);
        }
        __EXIRegs[14] = writeVal;
    }

    __EXIRegs[13] = 1 | (write << 2) | ((byte_size - 1U) << 4);

    DBGEXISync();
    if (!write) {
        u8* dataPtr = (u8*)data;
        readVal = __EXIRegs[14];
        for (i = 0; i < byte_size; ++i) {
            *dataPtr++ = readVal >> ((3 - i) << 3);
        }
    }

    return 1;
}
