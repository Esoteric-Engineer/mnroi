typedef long s32;
typedef int BOOL;

typedef struct DVDDiskID {
    unsigned long pad[8];
} DVDDiskID;

typedef struct CARDControl {
    unsigned char pad0[4];
    s32 result;
    unsigned char pad8[0x8C - 0x8];
    unsigned char threadQueue[8];
    unsigned char pad94[0xE0 - 0x94];
    unsigned char alarm[0x28];
    unsigned char padDiskID[0x10C - 0x108];
    DVDDiskID* diskID;
} CARDControl;

CARDControl __CARDBlock[2];
DVDDiskID __CARDDiskNone;

extern char lbl_804F2BC8[0x10];
extern char* lbl_8066CEF0;
extern unsigned short lbl_8066FB10;

extern unsigned short OSGetFontEncode(void);
extern void OSRegisterVersion(char* version);
extern void DSPInit(void);
extern void OSInitAlarm(void);
extern void OSInitThreadQueue(void* queue);
extern void OSCreateAlarm(void* alarm);
extern void OSRegisterResetFunction(void* info);

void __CARDSetDiskID(DVDDiskID* diskID);

void CARDInit(void)
{
    int chan;

    if (!__CARDBlock[0].diskID || !__CARDBlock[1].diskID) {
        lbl_8066FB10 = OSGetFontEncode();
        OSRegisterVersion(lbl_8066CEF0);
        DSPInit();
        OSInitAlarm();

        for (chan = 0; chan < 2; ++chan) {
            CARDControl* card = &__CARDBlock[chan];

            card->result = -3;
            OSInitThreadQueue(&card->threadQueue);
            OSCreateAlarm(&card->alarm);
        }
        __CARDSetDiskID((DVDDiskID*)0x80000000);

        OSRegisterResetFunction(lbl_804F2BC8);
    }
}

unsigned short __CARDGetFontEncode(void)
{
    return lbl_8066FB10;
}

void __CARDSetDiskID(DVDDiskID* diskID)
{
    __CARDBlock[0].diskID = diskID ? diskID : &__CARDDiskNone;
    __CARDBlock[1].diskID = diskID ? diskID : &__CARDDiskNone;
}
