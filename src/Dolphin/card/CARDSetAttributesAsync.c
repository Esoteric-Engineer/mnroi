typedef unsigned char u8;
typedef unsigned long u32;
typedef long s32;

typedef void (*CARDCallback)(s32, s32);

typedef struct CARDDir {
    u8 gameName[4];
    u8 company[2];
    u8 pad[0x34 - 6];
    u8 permission;
    u8 pad1[0x40 - 0x35];
} CARDDir;

extern u8 lbl_8066CEFA;
extern s32 __CARDGetStatusEx(s32 chan, s32 fileNo, CARDDir* dirent);
extern s32 fn_80410F6C(s32 chan, s32 fileNo, CARDDir* dirent, CARDCallback callback);

s32 CARDSetAttributesAsync(s32 chan, s32 fileNo, u8 attr, CARDCallback callback)
{
    CARDDir dirent;
    s32 result;
    u32 perm;
    u32 permCompany;
    u32 permGlobal;
    u32 attrGlobal;

    if (attr & ~lbl_8066CEFA) {
        return -10;
    }

    result = __CARDGetStatusEx(chan, fileNo, &dirent);
    if (result < 0) {
        return result;
    }

    perm = dirent.permission;

    if (((permGlobal = (perm & 0x20)) && !(attr & 0x20))
        || ((permCompany = (perm & 0x40)) && !(attr & 0x40))) {
        return -10;
    }

    attrGlobal = attr & 0x20;

    if ((attrGlobal && (attr & 0x40)) || (attrGlobal && permCompany)
        || ((attr & 0x40) && permGlobal)) {
        return -10;
    }

    dirent.permission = attr;
    return fn_80410F6C(chan, fileNo, &dirent, callback);
}
