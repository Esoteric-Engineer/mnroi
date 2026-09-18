typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXTexObj GXTexObj;
typedef int GXTexMapID;

// Real Dolphin SDK global GX state (gx). Only the field this function touches is declared. The rest is padding to keep its offset correct.
typedef struct {
    u8 pad0[2];
    u16 bpSentNot;
    u8 pad1[1220];
    void* (*texRegionCallback)(GXTexObj*, GXTexMapID);
} __GXDataStruct;

extern __GXDataStruct* __GXData;

extern void GXLoadTexObjPreLoaded(GXTexObj* obj, void* region, GXTexMapID id);

void GXLoadTexObj(GXTexObj* obj, GXTexMapID id)
{
    void* region = __GXData->texRegionCallback(obj, id);

    GXLoadTexObjPreLoaded(obj, region, id);
}
