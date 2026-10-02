typedef unsigned long u32;
typedef unsigned char u8;
typedef int BOOL;

volatile u32 __EXIRegs[0x40] : 0xCC006800;

extern BOOL DBGEXIImm(void* data, int size, u32 write);

static BOOL DBGEXISelect(u32 v)
{
    u32 regs = __EXIRegs[10];
    regs &= 0x405;
    regs |= 0x80 | (v << 4);
    __EXIRegs[10] = regs;
    return 1;
}

static BOOL DBGEXISync(void)
{
    while (__EXIRegs[13] & 1)
        ;
    return 1;
}

static BOOL DBGEXIDeselect(void)
{
    __EXIRegs[10] &= 0x405;
    return 1;
}

BOOL DBGRead(u32 param1, u32* data, int byte_size)
{
    BOOL error = 0;
    u32* dataPtr = data;
    u32 writeValue;
    u32 readValue;

    if (!DBGEXISelect(4)) {
        return 0;
    }

    writeValue = (param1 << 8) & 0x1fffc00 | 0x20000000;
    error = !DBGEXIImm((u8*)&writeValue, sizeof(writeValue), 1);
    error |= !DBGEXISync();

    while (byte_size != 0) {
        error |= !DBGEXIImm((u8*)&readValue, sizeof(readValue), 0);
        error |= !DBGEXISync();

        *dataPtr++ = readValue;

        byte_size -= 4;
        if (byte_size < 0)
            byte_size = 0;
    }

    error |= !DBGEXIDeselect();

    return !error;
}
