typedef struct DVDDiskID {
    unsigned long pad[8];
} DVDDiskID;

typedef struct CARDControl {
    unsigned char pad0[0x10C];
    DVDDiskID* diskID;
} CARDControl;

CARDControl __CARDBlock[2];
DVDDiskID __CARDDiskNone;

void __CARDSetDiskID(DVDDiskID* diskID)
{
    (void)__CARDBlock;
    (void)__CARDDiskNone;
    __CARDBlock[0].diskID = diskID ? diskID : &__CARDDiskNone;
    __CARDBlock[1].diskID = diskID ? diskID : &__CARDDiskNone;
}
