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
