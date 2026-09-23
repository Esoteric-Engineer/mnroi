typedef unsigned long u32;
typedef unsigned char u8;
typedef int BOOL;

volatile u32 __EXIRegs[0x40] : 0xCC006800;

extern BOOL fn_801965EC(void* data, int size, u32 write);

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

BOOL DBGReadMailbox(void* param_1)
{
    BOOL error = 0;
    u32 value;

    if (!DBGEXISelect(4)) {
        return 0;
    }

    value = 0x60000000;
    error |= !fn_801965EC((u8*)&value, 2, 1);
    error |= !DBGEXISync();
    error |= !fn_801965EC(param_1, sizeof(param_1), 0);
    error |= !DBGEXISync();
    error |= !DBGEXIDeselect();

    return !error;
}
