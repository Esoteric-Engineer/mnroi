typedef unsigned long u32;
typedef unsigned char u8;
typedef int BOOL;

volatile u32 __EXIRegs[0x40] : 0xCC006800;

extern BOOL OSDisableInterrupts(void);
extern void OSRestoreInterrupts(BOOL enabled);
extern BOOL fn_801965EC(void* data, int size, u32 write);
extern BOOL DBGWrite(u32 param1, u32* data, int byte_size);

extern u8 lbl_8066C558;

static inline BOOL DBGEXISelect(u32 v)
{
    u32 regs = __EXIRegs[10];
    regs &= 0x405;
    regs |= 0x80 | (v << 4);
    __EXIRegs[10] = regs;
    return 1;
}

static inline BOOL DBGEXISync(void)
{
    while (__EXIRegs[13] & 1)
        ;
    return 1;
}

static inline BOOL DBGEXIDeselect(void)
{
    __EXIRegs[10] &= 0x405;
    return 1;
}

static inline BOOL DBGReadStatus(void* param_1)
{
    BOOL error = 0;
    u32 value;

    if (!DBGEXISelect(4)) {
        return 0;
    }

    value = 0x40000000;
    error |= !fn_801965EC((u8*)&value, 2, 1);
    error |= !DBGEXISync();
    error |= !fn_801965EC(param_1, sizeof(param_1), 0);
    error |= !DBGEXISync();
    error |= !DBGEXIDeselect();

    return !error;
}

static inline BOOL DBGWriteMailbox(u32 param_1)
{
    BOOL error = 0;
    u32 value;

    if (!DBGEXISelect(4)) {
        return 0;
    }

    value = (param_1 & 0x1fffffff) | 0xc0000000;
    error |= !fn_801965EC((u8*)&value, sizeof(value), 1);
    error |= !DBGEXISync();
    error |= !DBGEXIDeselect();

    return !error;
}

int DBWrite(const void* data, u32 size)
{
    u32 value;
    u32 busyFlag;
    BOOL enabled;

    enabled = OSDisableInterrupts();
    do {
        DBGReadStatus(&busyFlag);
    } while (busyFlag & 2);

    ++lbl_8066C558;

    value = ((lbl_8066C558 & 1) ? 0x1000 : 0);
    while (!DBGWrite(value | 0x1c000, (u32*)data, (size + 3) & ~3))
        ;

    do {
        DBGReadStatus(&busyFlag);
    } while (busyFlag & 2);

    value = (lbl_8066C558 << 0x10) | 0x1f000000 | size;
    while (!DBGWriteMailbox(value))
        ;

    do {
        while (!DBGReadStatus(&busyFlag))
            ;
    } while (busyFlag & 2);

    OSRestoreInterrupts(enabled);

    return 0;
}
