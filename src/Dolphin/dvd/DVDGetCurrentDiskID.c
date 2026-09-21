typedef struct DVDDiskID DVDDiskID;

DVDDiskID* DVDGetCurrentDiskID(void)
{
    return (DVDDiskID*)0x80000000;
}
