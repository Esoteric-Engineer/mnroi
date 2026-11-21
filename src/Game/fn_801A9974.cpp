// Memory-card device: two card slots over CARD (mount, probe, format, read, write) (docs/core.md row 4).
// Owns "MemUnit:Buffer" (0x8049D8C8); the tail inlines' pools after it stay unclaimed.

inline int sn_return_decl(int a) { return a; }

__asm__(".section .rodata\n\t.balign 8\n\t.text"); // the section is 8-aligned: its unclaimed tail pools hold doubles

struct CardFileInfo { // CARDFileInfo
    int chan;
    int fileNo;
    int offset;
    int length;
    unsigned short iBlock;
    unsigned short pad;
};

struct Slot { // 0x18 bytes
    int chan;               // +0x00
    unsigned short flags;   // +0x04: 1 present, 2 and 4 the mount warnings, 8 mounted
    unsigned short pad6;    // +0x06
    int memSize;            // +0x08
    int sectorSize;         // +0x0C
    unsigned long long serial; // +0x10
};

struct Card {
    Slot slots[2];   // +0x00
    char f30[0x10];  // +0x30
};

extern "C" {
void CARDInit(void);
int CARDProbeEx(int chan, int *memSize, int *sectorSize);
int CARDMount(int chan, void *workArea, void (*detach)(int, int));
int CARDUnmount(int chan);
int CARDCheck(int chan);
int CARDFormat(int chan);
int CARDGetSerialNo(int chan, unsigned long long *serial);
int CARDCreate(int chan, const char *name, unsigned int size, CardFileInfo *info);
int CARDOpen(int chan, const char *name, CardFileInfo *info);
int CARDWrite(CardFileInfo *info, const void *buf, int length, int offset);
int CARDRead(CardFileInfo *info, void *buf, int length, int offset);
int CARDClose(CardFileInfo *info);
int CARDDelete(int chan, const char *name);
void *memcpy(void *dst, const void *src, unsigned int n);
void *fn_801AC988(unsigned int size, const char *tag, int line, int kind);
void fn_801ACC0C(void *p);
Slot &fn_80431E9C(Card *card, int i);
Slot *fn_80431E9C_p(Card *card, int i) __asm__("fn_80431E9C");
int fn_80431E68(Slot *slot);
int fn_80466694(Slot *slot, int size);
int fn_80466764(Slot *slot, int size);
void fn_804665F0(Card *card);
int fn_801A9CB4(register Slot *self);
int fn_801AA0C8(register Slot *self, const char *name);

extern char lbl_805892A0[0xA000]; // CARD work area

Card lbl_80589260;

void fn_801A9974(register Card *self)
{
    CARDInit();
    fn_80431E9C(self, 0).chan = 0;
    fn_80431E9C(self, 1).chan = 1;
}

void fn_801A99E0(register Card *self)
{
    Slot *s;
    int r;

    s = fn_80431E9C_p(self, 0);
    r = CARDProbeEx(0, &s->memSize, &s->sectorSize);
    if (r == 0) {
        s->flags |= 1;
    }
    s = fn_80431E9C_p(self, 1);
    r = CARDProbeEx(1, &s->memSize, &s->sectorSize);
    if (r == 0) {
        s->flags |= 1;
    }
}

void fn_801A9AD0(register Slot *self, int result)
{
    self->flags &= ~1;
}

void fn_801A9B04(int chan, int result)
{
    fn_801A9AD0(&fn_80431E9C(&lbl_80589260, chan), result);
}

int fn_801A9B58(register Slot *self)
{
    int r = CARDMount(self->chan, lbl_805892A0, fn_801A9B04);

    if (r != 0 && r != -13 && r != -6) {
        return 0;
    }
    self->flags |= 8;
    if (r == -6) {
        self->flags |= 2;
    } else if (r == -13) {
        self->flags |= 4;
    }
    r = CARDCheck(self->chan);
    if (r != 0 && r != -13) {
        fn_801A9CB4(self);
        return 0;
    }
    if (fn_80431E68(self) == 0) {
        r = CARDGetSerialNo(self->chan, &self->serial);
        if (r != 0) {
            return 0;
        }
    }
    return 1;
}

int fn_801A9CB4(register Slot *self)
{
    self->flags &= ~8;
    int r = CARDUnmount(self->chan);
    return r == 0 || r == -3;
}

int fn_801A9D34(register Slot *self)
{
    int r = CARDFormat(self->chan);

    if (r != 0) {
        return 0;
    }
    self->flags &= ~6;
    r = CARDGetSerialNo(self->chan, &self->serial);
    if (r != 0) {
        return 0;
    }
    return 1;
}

int fn_801A9DCC(register Slot *self, const char *name, void *data, int size, int alloc)
{
    int len;
    char *buf;
    CardFileInfo info;
    int r;

    if (fn_801AA0C8(self, name) == 0) {
        return 0;
    }
    buf = 0;
    if (alloc != 0) {
        len = fn_80466694(self, size);
    } else {
        len = size;
        buf = (char *)data;
    }
    r = CARDCreate(self->chan, name, len, &info);
    if (r != 0) {
        return 0;
    }
    if (alloc != 0) {
        buf = (char *)fn_801AC988(len, "MemUnit:Buffer", 190, 1);
        memcpy(buf, data, size);
    }
    r = CARDWrite(&info, buf, len, 0);
    if (r != 0) {
        goto fail;
    }
    if (alloc != 0) {
        fn_801ACC0C(buf);
    }
    r = CARDClose(&info);
    if (r != 0) {
        return 0;
    }
    return 1;
fail:
    if (alloc != 0 && buf != 0) {
        fn_801ACC0C(buf);
    }
    return 0;
}

int fn_801A9F78(register Slot *self, const char *name, void *dst, int size, int alloc)
{
    CardFileInfo info;
    int r;
    int len;
    char *buf;

    r = CARDOpen(self->chan, name, &info);
    if (r != 0) {
        return 0;
    }
    if (alloc != 0) {
        len = fn_80466764(self, size);
        buf = (char *)fn_801AC988(len, "MemUnit:Buffer", 236, 1);
    } else {
        len = size;
        buf = (char *)dst;
    }
    r = CARDRead(&info, buf, len, 0);
    if (r != 0) {
        return 0;
    }
    if (alloc != 0) {
        memcpy(dst, buf, size);
        fn_801ACC0C(buf);
    }
    r = CARDClose(&info);
    if (r != 0) {
        return 0;
    }
    return 1;
}

int fn_801AA0C8(register Slot *self, const char *name)
{
    int r = CARDDelete(self->chan, name);

    return r == 0 || r == -4;
}

}

inline int sn_return_decl_2(int a) { return a; }

// 65535 is GCC 2.95's default init priority.
static void __static_initialization_and_destruction_0(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            fn_804665F0(&lbl_80589260);
        } else {
        }
    }
}

extern "C" {
void fn_801AA1AC(void)
{
    __static_initialization_and_destruction_0(1, 65535);
}

static void (*const sCtorEntry)(void) __attribute__((section(".ctors"))) = fn_801AA1AC;
}
