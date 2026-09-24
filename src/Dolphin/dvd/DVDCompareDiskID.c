typedef int BOOL;
typedef struct DVDDiskID {
    char gameName[4];
    char company[2];
    unsigned char diskNumber;
    unsigned char gameVersion;
} DVDDiskID;

int strncmp(const char* s1, const char* s2, unsigned long n);

BOOL DVDCompareDiskID(DVDDiskID* id1, DVDDiskID* id2) {
    if (id1->gameName[0] && id2->gameName[0]) {
        if (strncmp(id1->gameName, id2->gameName, 4) != 0) {
            return 0;
        }
    }
    if (!id1->company[0] || !id2->company[0] || strncmp(id1->company, id2->company, 2) != 0) {
        return 0;
    }
    if (id1->diskNumber != 0xFF && id2->diskNumber != 0xFF && id1->diskNumber != id2->diskNumber) {
        return 0;
    }
    if (id1->gameVersion != 0xFF && id2->gameVersion != 0xFF && id1->gameVersion != id2->gameVersion) {
        return 0;
    }
    return 1;
}
