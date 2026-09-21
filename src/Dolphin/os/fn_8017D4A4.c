#pragma peephole off
typedef signed long s32;
typedef unsigned long u32;
typedef unsigned char u8;
typedef struct DVDCommandBlock DVDCommandBlock;

extern void* OSAllocFromArenaLo(u32 size, u32 align);
extern s32 DVDReadAbsAsyncPrio(DVDCommandBlock* block, void* addr, s32 length, s32 offset, void* callback, s32 prio);
extern s32 DVDGetCommandBlockStatus(DVDCommandBlock* block);
extern s32 fn_8018637C(void);
extern void __OSDoHotReset(s32 resetCode);
extern s32 lbl_8066F21C;

static inline void ReadDisc(void* addr, s32 length, s32 offset)
{
    u8 block[0x30];
    void* p = addr;

    DVDReadAbsAsyncPrio((DVDCommandBlock*)block, addr, length, offset, 0, 0);
    while (DVDGetCommandBlockStatus((DVDCommandBlock*)block)) {
        if (!fn_8018637C()) {
            __OSDoHotReset(0);
        }
    }
    (void)p;
}

s32 fn_8017D4A4(void)
{
    u8* buf;

    if (lbl_8066F21C != 0) {
        return lbl_8066F21C;
    }
    if (*(s32*)0x800030F4 != 0) {
        buf = (u8*)OSAllocFromArenaLo(0x40, 0x20);
        ReadDisc(buf, 0x40, *(s32*)0x800030F4);
        lbl_8066F21C = *(u32*)0x800030F4 + *(u32*)(buf + 0x38);
    } else {
        lbl_8066F21C = 0x2440;
    }
    return lbl_8066F21C;
}
