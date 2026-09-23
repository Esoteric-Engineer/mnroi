typedef struct DVDCommandBlock DVDCommandBlock;

typedef struct {
    unsigned long bootFilePosition;
    unsigned long FSTPosition;
    unsigned long FSTLength;
    unsigned long FSTMaxLength;
    void* FSTAddress;
} DVDBB2;

extern unsigned long fstStatus;
extern DVDBB2* bb2;
extern void* idTmp;

typedef struct {
    char gameName[4];
    char company[2];
    unsigned char diskNumber;
    unsigned char gameVersion;
    unsigned char streaming;
    char pad[0x17];
} DVDDiskID;

typedef struct {
    DVDDiskID diskID;
    char pad[0x18];
    void* FSTLocation;
    unsigned long FSTMaxLength;
} OSBootInfo;

extern void* OSGetArenaHi(void);
extern void OSSetArenaHi(void* newHi);
extern void* memcpy(void* dst, const void* src, unsigned long n);
extern void OSReport(const char* msg, ...);
extern long DVDGetDriveStatus(void);

static unsigned char bb2Buf[63];
static unsigned char block[0x30];

extern void DVDReadAbsAsyncForBS(DVDCommandBlock* block, void* addr, long length, long offset,
                                 void (*callback)(long, DVDCommandBlock*));
extern int DVDReset(void);
extern int DVDReadDiskID(DVDCommandBlock* block, void* diskID,
                         void (*callback)(long, DVDCommandBlock*));

void cb_80186A80(long result, DVDCommandBlock* block)
{
    if (result > 0) {
        switch (fstStatus) {
        case 0:
            fstStatus = 1;
            DVDReadAbsAsyncForBS(block, bb2, 0x20, 0x420, cb_80186A80);
            return;
        case 1:
            fstStatus = 2;
            DVDReadAbsAsyncForBS(block, bb2->FSTAddress, (bb2->FSTLength + 0x1F) & 0xFFFFFFE0,
                                 bb2->FSTPosition, cb_80186A80);
        default:
            return;
        }
    }
    if (result == -1) {
        return;
    } else if (result == -4) {
        fstStatus = 0;
        DVDReset();
        DVDReadDiskID(block, idTmp, cb_80186A80);
    }
}

void __fstLoad(void)
{
    OSBootInfo* bootInfo;
    DVDDiskID* id;
    unsigned char idTmpBuf[63];
    long state;
    void* arenaHi;

    arenaHi = OSGetArenaHi();
    bootInfo = (OSBootInfo*)0x80000000;
    idTmp = (void*)(((unsigned long)idTmpBuf + 31) & ~31);
    bb2 = (DVDBB2*)(((unsigned long)bb2Buf + 31) & ~31);
    DVDReset();
    DVDReadDiskID((DVDCommandBlock*)block, idTmp, cb_80186A80);
    while (1) {
        state = DVDGetDriveStatus();
        if (state == 0) {
            break;
        }
    }
    bootInfo->FSTLocation = bb2->FSTAddress;
    bootInfo->FSTMaxLength = bb2->FSTMaxLength;
    id = &bootInfo->diskID;
    memcpy(id, idTmp, 0x20);
    OSReport("\n");
    OSReport("  Game Name ... %c%c%c%c\n", id->gameName[0], id->gameName[1], id->gameName[2],
             id->gameName[3]);
    OSReport("  Company ..... %c%c\n", id->company[0], id->company[1]);
    OSReport("  Disk # ...... %d\n", id->diskNumber);
    OSReport("  Game ver .... %d\n", id->gameVersion);
    OSReport("  Streaming ... %s\n", !(id->streaming) ? "OFF" : "ON");
    OSReport("\n");
    OSSetArenaHi(bb2->FSTAddress);
}
