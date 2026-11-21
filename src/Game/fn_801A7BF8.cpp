// File layer: the stdio-style open-file table, the search folders and the CLASH.BIG mount (docs/core.md row 3).
// Owns the .rodata from "bf:" (0x8049D6C4).

#include <stdarg.h>

inline int sn_return_decl(int a) { return a; }

class FileRec {
public:
    int *f0;         // +0x000, *f0 == 0 when the slot is free
    int *f4;         // +0x004
    int *f8;         // +0x008, *f8 != 0 when open for writing (a guess)
    char *path;      // +0x00C
    int *pos;        // +0x010, write position
    char f14[0x144]; // +0x014
    FileRec() __asm__("fn_801AFEE8");
    ~FileRec();
};

struct Folders {
    int count;       // +0x0
    char *paths[64]; // +0x4
};

struct Root { // also a directory entry read back: f80 is then is-directory
    char name[0x80]; // +0x00
    int f80;         // +0x80
};

struct DirDesc { // DVD directory, 12 bytes
    int f0;
    int f4;
    int f8;
};

struct DirEntry { // DVD directory entry
    int entryNum; // +0x0
    int isDir;    // +0x4
    char *name;   // +0x8
};

struct DirFind { // stdFile:Find, 0xC0 bytes
    int open;        // +0x00
    DirDesc dvd;     // +0x04
    DirEntry entry;  // +0x10
    char dir[0x80];  // +0x1C
    char ext[0x20];  // +0x9C
    int type;        // +0xBC
};

struct SysParams { // RealCore, filled by fn_8024337C
    int size;     // +0x00
    void *p4;     // +0x04
    int f8;       // +0x08
    int fC[7];    // +0x0C
    int f28;      // +0x28
    int f2C[3];   // +0x2C
};

extern "C" {
extern const char _ctype_[];
unsigned int strlen(const char *s);
char *strcpy(char *dst, const char *src);
void *memset(void *dst, int c, unsigned int n);
void *fn_801AC988(unsigned int size, const char *tag, int line, int kind);
void fn_801A8FC4(void);
void fn_801A7F5C(const char *folder, int type, int unused);
void fn_801A92D4(Root *dst, const char *name, int n);
void fn_801A935C(void);
void fn_801AFEC0(void *p);
void fn_8024337C(SysParams *p);
void fn_802433D0(SysParams *p);
int fn_80241888(void);
void fn_80241548(void *buf, int size);
void fn_80243BD4(int a, int b);
int fn_801A8500(const char *path, const char *mode);
void fn_801A875C(int handle);
void fn_801B41B4(char *dst, int n, const char *src);
int stricmp(const char *a, const char *b);
int strcmp(const char *a, const char *b);
char *strncpy(char *dst, const char *src, unsigned int n);
int snprintf(char *dst, unsigned int n, const char *fmt, ...);
int sprintf(char *dst, const char *fmt, ...);
char *strchr(const char *s, int c);
int fn_801A7CD8(const char *mode);
int fn_801AFFDC(FileRec *rec, const char *path, int flags, int n);
void fn_801B00AC(FileRec *rec, int n);
int fn_80243FFC(int a, void *b, int c);
int fn_80243F94(int a);
int fn_80244120(int a);
void fn_801ACC0C(void *p);
void fn_801B4220(char *path);
void fn_802421AC(const char *path, int a, long long *b, long long *size);
void *fn_801AC9EC(unsigned int size, const char *tag, int line, int kind, int align, int f);
int fn_80243E30(const char *path, void *buf, unsigned int size);
int fn_8046655C(void);
int fn_80122228(void);
void fn_80125538(int p);
void fn_8023E98C(void);
int fn_801B01D4(FileRec *rec, void *ptr, unsigned int size, unsigned int count);
char *fn_801B0380(FileRec *rec, char *buf, int n);
int fn_80466584(FileRec *rec);
int *fn_804665C4(FileRec *rec);
int fn_80244538(int a, int b);
int fn_801A8DC0(int handle);
int vsnprintf(char *dst, unsigned int n, const char *fmt, va_list ap);
int fn_802444A8(int a, int pos, const void *buf, int len, int b);
int fn_801A9424(const char *name);
unsigned int fn_801B10CC(int a, int b);
void *fn_801B1110(int a, int b, void *buf);
int fn_801B1270(void *vfs, const char *path, int a);
int fn_80242628(void *vfs, int a);
void fn_802424F8(const char *prefix, int a);
char *strcat(char *dst, const char *src);
void DVDCloseDir(DirDesc *dir);
int DVDOpenDir(const char *path, DirDesc *dir);
int DVDReadDir(DirDesc *dir, DirEntry *entry);
char *strstr(const char *s, const char *sub);
int fn_801A9584(const char *dir, int type, const char *ext);
int fn_801A9748(int handle, Root *out);
void fn_801A96D4(int dir);

extern FileRec *lbl_8066F4EC;      // the open-file table, 12 records
extern char lbl_8066F4F4[8];
extern int lbl_8066C618;           // initialised
extern void *lbl_8066C620;
extern char lbl_8058883C[];
extern Root lbl_805888C0[];
extern char lbl_80593C58[];
extern Folders lbl_805864B0[35];  // search folders by file type
extern unsigned int lbl_8066C604;  // names found
extern char lbl_8057E4B0[0x400][0x20];
extern int lbl_8066C61C;          // search the third root too
extern char lbl_805889C8[0x80];
extern char lbl_80588A48[0x800];
extern void *lbl_8066C628;         // VFS buffer
extern void *lbl_8066C624;         // the VFS
extern unsigned int lbl_8066C630;
extern int lbl_8066C62C;           // archives added
extern int lbl_80589248[6];        // archive handles

extern int lbl_8066C608; // use the "bf:" prefix

const char *fn_801A7C88(void);

void fn_801A7BF8(void)
{
}

void fn_801A7C14(void)
{
}

const char *fn_801A7C30(void)
{
    if (lbl_8066C608 != 0) {
        return "bf:";
    } else {
        return fn_801A7C88();
    }
}

const char *fn_801A7C88(void)
{
    return "";
}

const char *fn_801A7CB0(void)
{
    return "";
}

int fn_801A7CD8(const char *mode)
{
    int len = strlen(mode);
    int flags = 0;
    int i;

    for (i = 0; i < len; i++) {
        char c = ({ int x = mode[i]; ((_ctype_ + 1)[x] & 1) ? x - 'A' + 'a' : x; });
        switch (c) {
        case 'r':
            flags |= 0x11;
            break;
        case 'w':
            flags |= 0x6;
            break;
        case 'a':
        case 'b':
            break;
        }
    }
    return flags;
}
}

inline const char *sn_event_name(int e) // emits no code; its strings are 0x8049D6CC-0x8049D78C
{
    switch (e) {
    case 0:
        return "FS_EVNT_CLOSE";
    case 1:
        return "FS_EVNT_AS_READ";
    case 2:
        return "FS_EVNT_AS_WRITE";
    case 3:
        return "FS_EVNT_AS_EXIST";
    case 4:
        return "FS_EVNT_AS_ADDBIG";
    case 5:
        return "FS_EVNT_CD_READ";
    case 6:
        return "FS_EVNT_CD_READCOMPL";
    case 7:
        return "FS_EVNT_CACHEFILE";
    case 8:
        return "FS_EVNT_CACHEWRITE";
    case 9:
        return "FS_EVNT_CACHEHIT";
    }
    return 0;
}

extern "C" {
void fn_801A7DF0(int noMount)
{
    SysParams params;
    int size;

    fn_801A8FC4();
    memset(lbl_8058883C, 0, 0x18C);
    fn_801A92D4(lbl_805888C0, ".", 1);
    lbl_8066F4EC = new FileRec[12];
    fn_801AFEC0(lbl_80593C58);
    register int unused = -1; // never read
    params.size = 0x38;
    fn_8024337C(&params);
    params.p4 = lbl_8066F4F4;
    params.f8 = 0x20;
    params.f28 = -1;
    fn_802433D0(&params);
    size = fn_80241888();
    lbl_8066C620 = fn_801AC988(size, "File", 475, 2);
    fn_80241548(lbl_8066C620, size);
    if (noMount == 0) {
        fn_801A935C();
    }
    fn_80243BD4(0xC, 0x400);
    lbl_8066C618 = 1;
}

void fn_801A7F5C(const char *folder, int type, int unused)
{
    char *p = (char *)fn_801AC988(strlen(folder) + 1, "File", 579, 1);

    strcpy(p, folder);
    lbl_805864B0[type].paths[lbl_805864B0[type].count] = p;
    lbl_805864B0[type].count++;
}

int fn_801A8088(const char *path)
{
    int h = fn_801A8500(path, "rb");

    if (h == 0) {
        return 0;
    }
    fn_801A875C(h);
    return 1;
}

int fn_801A80FC(const char *name)
{
    char buf[0x20];
    unsigned int i;

    if (lbl_8066C604 > 0x3FF) {
        return 0;
    }
    fn_801B41B4(buf, 0x20, name);
    for (i = 0; i < lbl_8066C604; i++) {
        if (stricmp(buf, lbl_8057E4B0[i]) == 0) {
            return 0;
        }
    }
    strncpy(lbl_8057E4B0[lbl_8066C604], buf, 0x20);
    lbl_8066C604++;
    return 1;
}

unsigned int fn_801A8204(const char *dir, const char *ext)
{
    unsigned int i;
    char *root;
    int h;
    Root name;

    lbl_8066C604 = 0;
    root = lbl_8058883C;
    for (i = 0; i <= 2; root += 0x84, i++) {
        if (root[0] != 0) {
            if (i == 2 && lbl_8066C61C == 0) {
                continue;
            }
            if (strcmp(root, ".") == 0) {
                snprintf(lbl_805889C8, 0x80, dir);
            } else {
                snprintf(lbl_805889C8, 0x80, "%s\\%s", root, dir);
            }
            h = fn_801A9584(dir, 3, ext);
            while (fn_801A9748(h, &name) != 0) {
                fn_801A80FC(name.name);
            }
            fn_801A96D4(h);
        }
    }
    return lbl_8066C604;
}

int fn_801A8368(const char *name, const char *mode, int type)
{
    Folders *f = &lbl_805864B0[type];
    char path[0x80];
    unsigned int i;
    int h;

    if (name[0] == 0) {
        return 0;
    }
    if (type == 3 || type == 23 || type == 24) {
        lbl_8066C61C = 1;
    } else {
        lbl_8066C61C = 0;
    }
    for (i = 0; i < f->count; i++) {
        sprintf(path, "%s%c%s", f->paths[i], '/', name);
        h = fn_801A8500(path, mode);
        if (h != 0) {
            lbl_8066C61C = 1;
            return h;
        }
    }
    h = fn_801A8500(name, mode);
    if (h != 0) {
        lbl_8066C61C = 1;
        return h;
    }
    lbl_8066C61C = 1;
    return 0;
}

int fn_801A8500(const char *path, const char *mode)
{
    unsigned int i;
    char *root;
    int ok;
    unsigned int slot;
    int res;

    for (slot = 0; slot <= 11; slot++) {
        if (*lbl_8066F4EC[slot].f0 == 0) {
            break;
        }
    }
    if (slot > 11) {
        return 0;
    }
    ok = 0;
    root = lbl_8058883C;
    for (i = 0; i <= 2 && ok == 0; root += 0x84, i++) {
        if (root[0] != 0) {
            if (i == 2 && lbl_8066C61C == 0) {
                continue;
            }
            if (strcmp(root, ".") == 0 || strchr(path, ':') != 0) {
                snprintf(lbl_805889C8, 0x80, "%s", path);
            } else {
                snprintf(lbl_805889C8, 0x80, "%s\\%s", root, path);
            }
            char full[0x80];
            sprintf(full, "%s%s", fn_801A7C30(), lbl_805889C8);
            int r = 0;
            int unused = 0;
            int n = 100;
            r = fn_801AFFDC(&lbl_8066F4EC[slot], full, fn_801A7CD8(mode), n);
            res = r;
            if (res != 0) {
                ok = 1;
            }
        }
    }
    if (ok == 0) {
        return 0;
    }
    return slot + 1;
}

void fn_801A875C(int handle)
{
    FileRec *rec = &lbl_8066F4EC[handle - 1];

    fn_801B00AC(rec, 0x64);
}

int fn_801A87B0(int a, void *b, int c)
{
    return fn_80243FFC(a, b, c);
}

int fn_801A8804(int a)
{
    return fn_80243F94(a);
}

int fn_801A8848(int a)
{
    void *p = 0;

    fn_80243FFC(a, &p, 0);
    if (p != 0) {
        fn_801ACC0C(p);
    }
    return fn_80244120(a);
}

int fn_801A88BC(const char *name, int kind, const char *tag)
{
    int res = 0;
    long long size;
    long long b;
    char path[0x80];
    void *p;

    sprintf(path, "%s%s", fn_801A7C30(), name);
    fn_801B4220(path);
    fn_802421AC(path, 1, &b, &size);
    if (size != 0) {
        p = fn_801AC9EC((unsigned int)size + 0x10, tag, 1232, kind, 0x20, 0);
        res = fn_80243E30(path, p, (unsigned int)size + 0x10);
    }
    return res;
}

int fn_801A89C0(const char *name, int b, const char *tag, int kind, int e)
{
    int result = 0;
    int h = fn_801A88BC(name, kind, tag);

    while (h != 0) {
        switch (fn_801A8804(h)) {
        case 1:
            fn_801A87B0(h, &result, b);
            h = 0;
            break;
        case 0:
            if (fn_8046655C() != 0) {
                fn_80125538(fn_80122228());
            }
            fn_8023E98C();
            break;
        case -1:
            break;
        }
    }
    return result;
}

int fn_801A8AC4(const char *name, int type, char *out)
{
    int h = fn_801A8368(name, "rb", type);

    if (h == 0) {
        return 0;
    }
    strncpy(out, (lbl_8066F4EC + h - 1)->path, 0x80);
    fn_801A875C(h);
    return 1;
}

unsigned int fn_801A8B60(void *ptr, unsigned int size, unsigned int count, int handle)
{
    FileRec *rec;
    int unused;
    void *dst = ptr;
    unsigned int n;

    if (count == 0) {
        return 0;
    }
    if (size == 0) {
        return 0;
    }
    rec = &lbl_8066F4EC[handle - 1];
    n = fn_801B01D4(rec, ptr, size, count);
    return n;
}

char *fn_801A8C08(char *buf, int n, int handle)
{
    FileRec *rec;
    int unused;
    int len = n;
    char *dst = buf;

    rec = &lbl_8066F4EC[handle - 1];
    return fn_801B0380(rec, buf, n);
}

int fn_801A8C84(int handle)
{
    FileRec *rec = &lbl_8066F4EC[handle - 1];

    return fn_80466584(rec);
}

int fn_801A8CE0(int handle)
{
    FileRec *rec = &lbl_8066F4EC[handle - 1];

    return *fn_804665C4(rec);
}

int fn_801A8D40(const char *path)
{
    int h = fn_801A8500(path, "rb");
    int size;

    if (h == 0) {
        return 0;
    }
    size = fn_801A8DC0(h);
    fn_801A875C(h);
    return size;
}

int fn_801A8DC0(int handle)
{
    FileRec *rec = &lbl_8066F4EC[handle - 1];

    if (*rec->f0 == 0) {
        return 0;
    }
    int size = 0;
    size = fn_80244538(*rec->f4, 0x64);
    return size;
}

int fn_801A8E54(int handle, const char *fmt, ...)
{
    FileRec *rec = &lbl_8066F4EC[handle - 1];
    int n;
    va_list ap;

    if (*rec->f8 != 0) {
        va_start(ap, fmt);
        int len = vsnprintf(lbl_80588A48, 0x800, fmt, ap);
        int pos = *rec->pos;
        n = fn_802444A8(*rec->f4, pos, lbl_80588A48, len, 0x64);
        *rec->pos += n;
    } else {
        n = 0;
    }
    return n;
}

void fn_801A8FC4(void)
{
    memset(lbl_805864B0, 0, 0x238C);
    fn_801A7F5C("Misc", 10, 0);
    fn_801A7F5C("Misc", 20, 0);
    fn_801A7F5C("Levels", 3, 0);
    fn_801A7F5C("Levels", 8, 0);
    fn_801A7F5C("Materials", 1, 0);
    fn_801A7F5C("Materials/Effects", 1, 0);
    fn_801A7F5C("Materials/Levels", 1, 0);
    fn_801A7F5C("Materials/Models", 1, 0);
    fn_801A7F5C("Materials/Shaders", 1, 0);
    fn_801A7F5C("UI", 1, 0);
    fn_801A7F5C("Levels", 1, 0);
    fn_801A7F5C("Models", 2, 0);
    fn_801A7F5C("Anims", 0, 0);
    fn_801A7F5C("AnimTags", 34, 0);
    fn_801A7F5C("Motions", 6, 0);
    fn_801A7F5C("UI", 4, 0);
    fn_801A7F5C("Misc", 7, 0);
    fn_801A7F5C("Misc", 9, 0);
    fn_801A7F5C("Misc", 15, 0);
    fn_801A7F5C("Misc", 13, 0);
    fn_801A7F5C("Misc", 14, 0);
    fn_801A7F5C("Misc", 21, 0);
    fn_801A7F5C("Sound", 11, 0);
    fn_801A7F5C("Sound", 24, 0);
    fn_801A7F5C("Misc", 12, 0);
    fn_801A7F5C("Misc", 16, 0);
    fn_801A7F5C("Quests", 18, 0);
    fn_801A7F5C("Stores", 19, 0);
    fn_801A7F5C("Video", 23, 0);
    fn_801A7F5C("Cutscenes", 25, 0);
    fn_801A7F5C("Terrains", 26, 0);
    fn_801A7F5C("Levels", 29, 0);
    fn_801A7F5C("Levels", 30, 0);
    fn_801A7F5C("Levels", 31, 0);
    fn_801A7F5C("Profiles", 32, 0);
    fn_801A7F5C("Bundles", 33, 0);
}

void fn_801A92D4(Root *dst, const char *name, int n)
{
    strncpy(dst->name, name, 0x80);
    dst->name[0x7F] = 0;
    dst->f80 = 0;
}

int fn_801A9334(int a)
{
    return 0;
}

void fn_801A935C(void)
{
    lbl_8066C628 = fn_801AC988(fn_801B10CC(4, 0x20), "File:Big", 2227, 2);
    lbl_8066C624 = fn_801B1110(4, 0x20, lbl_8066C628);
    lbl_8066C608 = 1;
    if (fn_801A9424("CLASH.BIG") == 0) {
        lbl_8066C608 = 0;
        fn_801ACC0C(lbl_8066C628);
    } else {
        lbl_8066C630 = fn_80242628(lbl_8066C624, 0);
        fn_802424F8("bf:", 1);
    }
}

int fn_801A9424(const char *name)
{
    char path[0x80];

    if (lbl_8066C608 == 0) {
        return 0;
    }
    if (lbl_8066C624 == 0 || name == 0) {
        return 0;
    }
    strcpy(path, fn_801A7C88());
    strcat(path, fn_801A7CB0());
    strcat(path, name);
    lbl_80589248[lbl_8066C62C] = fn_801B1270(lbl_8066C624, path, 0);
    if (lbl_80589248[lbl_8066C62C] == -1) {
        return 0;
    }
    lbl_8066C62C++;
    return 1;
}

int fn_801A953C(int a)
{
    return 0;
}

void fn_801A9564(int size)
{
}

int fn_801A9584(const char *dir, int type, const char *ext)
{
    DirFind *d = (DirFind *)fn_801AC988(0xC0, "stdFile:Find", 87, 1);

    if (d == 0) {
        return 0;
    }
    memset(d, 0, 0xC0);
    d->type = type;
    if (dir[0] == 0) {
        strcpy(d->dir, ".\0"); // its own copy of "." at 0x8049D8C0, not merged with the first
    } else {
        strcpy(d->dir, dir);
    }
    switch (type) {
    case 3:
        if (strchr(ext, '.') == 0) {
            strcpy(d->ext, ext);
        } else {
            strcpy(d->ext, ext + 1);
        }
        break;
    case 0:
    case 1:
    case 2:
    default:
        break;
    }
    return (int)d;
}

void fn_801A96D4(int handle)
{
    DirFind *d = (DirFind *)handle;

    if (d != 0) {
        if (d->open != 0) {
            DVDCloseDir(&d->dvd);
        }
        fn_801ACC0C(d);
    }
}

int fn_801A9748(int handle, Root *out)
{
    DirFind *d = (DirFind *)handle;
    int got = 0;
    int more = 1;

    if (d == 0) {
        return 0;
    }
    while (more) {
        if (d->open == 0) {
            if (DVDOpenDir(d->dir, &d->dvd) != 0) {
                d->open = 1;
                got = DVDReadDir(&d->dvd, &d->entry);
            }
        } else {
            got = DVDReadDir(&d->dvd, &d->entry);
        }
        if (got != 0) {
            strcpy(out->name, d->entry.name);
            out->f80 = d->entry.isDir;
            if (d->type == 1 && out->f80 != 0) {
                got = 0;
                more = 1;
            } else if (d->type == 2 && out->f80 == 0) {
                got = 0;
                more = 1;
            } else if (d->type == 3 && strstr(out->name, d->ext) != out->name + strlen(out->name) - strlen(d->ext)) {
                got = 0;
                more = 1;
            } else {
                more = 0;
            }
        } else {
            more = 0;
        }
    }
    return got;
}
}
