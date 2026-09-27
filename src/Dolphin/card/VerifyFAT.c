typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef unsigned long u32;
typedef long s32;
typedef int BOOL;

typedef struct CARDControl {
    u8 pad0[0x10];
    u16 cBlock;
    u8 pad12[0x80 - 0x12];
    void* workArea;
    void* currentDir;
    u16* currentFat;
    u8 pad8C[0x110 - 0x8C];
} CARDControl;

static inline void __CARDCheckSum(void* ptr, int length, u16* checksum, u16* checksumInv)
{
    u16* p;
    int i;

    length /= sizeof(u16);
    *checksum = *checksumInv = 0;
    for (i = 0, p = ptr; i < length; i++, p++) {
        *checksum += *p;
        *checksumInv += ~*p;
    }
    if (*checksum == 0xffff)
        *checksum = 0;
    if (*checksumInv == 0xffff)
        *checksumInv = 0;
}
extern void* memcpy(void* dst, const void* src, unsigned long n);

#define CARD_SYSTEM_BLOCK_SIZE (8 * 1024u)
#define CARD_FAT_CHECKSUM 0
#define CARD_FAT_CHECKSUMINV 1
#define CARD_FAT_CHECKCODE 2
#define CARD_FAT_FREEBLOCKS 3
#define CARD_NUM_SYSTEM_BLOCK 5
#define CARD_FAT_AVAIL 0

s32 VerifyFAT(CARDControl* card, int* outCurrent)
{
    u16* fat[2];
    u16* fatp;
    u16 nBlock;
    u16 cFree;
    int i;
    u16 checkSum;
    u16 checkSumInv;
    int errors;
    int current;

    current = errors = 0;
    for (i = 0; i < 2; i++) {
        fatp = fat[i] = (u16*)((u8*)card->workArea + (3 + i) * CARD_SYSTEM_BLOCK_SIZE);

        __CARDCheckSum(&fatp[CARD_FAT_CHECKCODE], CARD_SYSTEM_BLOCK_SIZE - sizeof(u32), &checkSum, &checkSumInv);
        if (fatp[CARD_FAT_CHECKSUM] != checkSum || fatp[CARD_FAT_CHECKSUMINV] != checkSumInv) {
            ++errors;
            current = i;
            card->currentFat = 0;
            continue;
        }

        cFree = 0;
        for (nBlock = CARD_NUM_SYSTEM_BLOCK; nBlock < card->cBlock; nBlock++) {
            if (fatp[nBlock] == CARD_FAT_AVAIL)
                cFree++;
        }
        if (cFree != fatp[CARD_FAT_FREEBLOCKS]) {
            ++errors;
            current = i;
            card->currentFat = 0;
            continue;
        }
    }

    if (0 == errors) {
        if (card->currentFat == 0) {
            if (((s16)fat[0][CARD_FAT_CHECKCODE] - (s16)fat[1][CARD_FAT_CHECKCODE]) < 0)
                current = 0;
            else
                current = 1;
            card->currentFat = fat[current];
            memcpy(fat[current], fat[current ^ 1], CARD_SYSTEM_BLOCK_SIZE);
        } else
            current = (card->currentFat == fat[0]) ? 0 : 1;
    }
    if (outCurrent)
        *outCurrent = current;
    return errors;
}
