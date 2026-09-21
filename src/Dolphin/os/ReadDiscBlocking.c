#pragma peephole off
typedef signed long s32;
typedef unsigned char u8;
typedef struct DVDCommandBlock DVDCommandBlock;

extern s32 DVDReadAbsAsyncPrio(DVDCommandBlock* block, void* addr, s32 length, s32 offset, void* callback, s32 prio);
extern s32 DVDGetCommandBlockStatus(DVDCommandBlock* block);
extern s32 fn_8018637C(void);
extern void __OSDoHotReset(s32 resetCode);

void ReadDiscBlocking(void* addr, s32 length, s32 offset)
{
    u8 block[0x30];

    DVDReadAbsAsyncPrio((DVDCommandBlock*)block, addr, length, offset, 0, 0);
    while (DVDGetCommandBlockStatus((DVDCommandBlock*)block)) {
        if (!fn_8018637C()) {
            __OSDoHotReset(0);
        }
    }
}
