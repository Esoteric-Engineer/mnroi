typedef unsigned char u8;

typedef struct CARDDir {
    u8 gameName[4];
    u8 company[2];
    u8 pad0[2];
    u8 fileName[32];
    u8 pad1[0x40 - 0x28];
} CARDDir;

int __CARDCompareFileName(CARDDir* ent, const char* fileName)
{
    char* entName = (char*)ent->fileName;
    char c1;
    char c2;
    int n = 32;

    while (--n >= 0) {
        if ((c1 = *entName++) != (c2 = *fileName++)) {
            return 0;
        } else if (c2 == '\0') {
            return 1;
        }
    }

    if (*fileName == '\0') {
        return 1;
    }
    return 0;
}
