// The save profile (singleton fn_8011CA74) and the save buffers it serializes into; docs/story.md row 3.
// Owns .rodata 0x804993D0-0x80499430; dtk's lbl_80499378 and lbl_80499428 are split at its edges.

typedef struct SaveBuffer
{
    char *cur;  // +0x0
    char *base; // +0x4
    int size;   // +0x8
} SaveBuffer;

struct Profile
{
    SaveBuffer buf0;  // +0x0
    SaveBuffer buf1;  // +0xC
    int unk18;
    int unk1C;
    int unk20;        // volume, 0-10
    int unk24;        // volume, 0-10
    int unk28;
    int unk2C;
    int unk30;
    int unk34;
    int unk38;
    int unk3C;
    int unk40;
    int unk44;
    int unk48;
    int unk4C;
    int unk50;
    int unk54;
    int unk58;
    int unk5C;
    int unk60;
    int unk64;
    int unk68;
    int unk6C;
    int unk70;
    int unk74;
    int unk78;
    int unk7C;
    int unk80;
    int unk84;
    int unk88;
    int unk8C[65];
    char unk190[4];
    int unk194;       // date, YYYYMMDD
    int unk198;       // play time, seconds
    int unk19C;       // play-time start tick
    int unk1A0[80];   // read as [i], [i + 25] and [i + 68]

    Profile() __asm__("fn_8011CADC");
};

extern "C" {

extern void *memset(void *dst, int c, unsigned n);
extern void *memcpy(void *dst, const void *src, unsigned n);
extern char *strncpy(char *dst, const char *src, unsigned int n);

extern void *fn_801AD324(int size, const char *tag, int align);
extern void fn_801ACC44(void *p);
extern int fn_80118E5C(void);
extern void fn_80118F18(int mode);
extern void fn_80119224(int channel, int volume);
extern void *fn_80122228(void);
extern int fn_80122378(void *pads);
extern int fn_80123240(void *pads);
extern void fn_8012326C(void *pads, int a);
extern void fn_80131878(int mode);
extern int fn_801224D0(void *pads);
extern void fn_801224FC(void *pads, int on);
extern void fn_80123214(void *pads, int on);
extern void fn_80124B94(void *pads, int slot, int v);
extern void fn_80124C4C(void *pads, int slot, int v);
extern void fn_801AF4CC(void *clock, void *date);
extern int fn_8042E96C(void *clock);

extern Profile *lbl_8066BE20;
extern int lbl_8066C640;
extern char lbl_80593BE8[];

void fn_8011C5B0(register SaveBuffer *buf, int size);
void fn_8011C628(register SaveBuffer *buf);
void fn_8011C730(register SaveBuffer *buf, const void *src);
int fn_8011D854(register Profile *self);
int fn_8011D8A4(register Profile *self);
int fn_8011DA4C(register Profile *self, int t);
int fn_8011DAF4(register Profile *self, int t);
int fn_8011DBCC(register Profile *self, int t);
void fn_8011C67C(register SaveBuffer *buf, const char *src);
void fn_8011C6D0(register SaveBuffer *buf, char *dst);
void fn_8011C780(register SaveBuffer *buf, void *dst);
void fn_8011C7D0(register SaveBuffer *buf, const void *src);
void fn_8011C820(register SaveBuffer *buf, void *dst);
void fn_8011C870(register SaveBuffer *buf, const int *src);
void fn_8011C8D8(register SaveBuffer *buf, int *dst);
char *fn_8011C954(register SaveBuffer *buf);
void fn_8011C980(register SaveBuffer *buf, const char *src, int n);
void fn_8011CD60(register Profile *self, int v);
void fn_8011CDC8(register Profile *self, int v);
void fn_8011CED0(register Profile *self, int v);
void fn_8011CFD8(register Profile *self, int v);
void fn_8011D120(register Profile *self, int mode, int apply);
void fn_8011D4E4(register Profile *self, int v);
void fn_8011D988(register Profile *self, int v);
void fn_8011E1DC(register Profile *self);
int fn_8011EC90(register Profile *self);

}

// 8-aligns the claim: the tail of the previous file's "Memcard:ThreadStack"
__asm__(".section .rodata\n\t.globl lbl_804993D0\nlbl_804993D0:\n\t.byte 0x61, 0x63, 0x6B, 0x00\n\t.text");

inline int sn_return_decl(int a) { return a; }

extern "C" void fn_8011C55C(void)
{
}

extern "C" SaveBuffer *fn_8011C578(register SaveBuffer *buf)
{
    buf->cur = 0;
    buf->base = 0;
    return buf;
}

extern "C" void fn_8011C5B0(register SaveBuffer *buf, int size)
{
    fn_8011C628(buf);
    buf->cur = (char *)fn_801AD324(size, "Game:SaveBuffer", 0x3C);
    memset(buf->cur, 0, size);
    buf->base = buf->cur;
    buf->size = size;
}

extern "C" void fn_8011C628(register SaveBuffer *buf)
{
    if (buf->base) {
        fn_801ACC44(buf->base);
    }
    buf->cur = 0;
    buf->base = 0;
}

extern "C" void fn_8011C67C(register SaveBuffer *buf, const char *src)
{
    int v = *src;

    fn_8011C730(buf, &v);
}

extern "C" void fn_8011C6D0(register SaveBuffer *buf, char *dst)
{
    int v;

    memcpy(&v, buf->cur, 4);
    *dst = v;
    buf->cur += 4;
}

extern "C" void fn_8011C730(register SaveBuffer *buf, const void *src)
{
    memcpy(buf->cur, src, 4);
    buf->cur += 4;
}

extern "C" void fn_8011C780(register SaveBuffer *buf, void *dst)
{
    memcpy(dst, buf->cur, 4);
    buf->cur += 4;
}

extern "C" void fn_8011C7D0(register SaveBuffer *buf, const void *src)
{
    memcpy(buf->cur, src, 4);
    buf->cur += 4;
}

extern "C" void fn_8011C820(register SaveBuffer *buf, void *dst)
{
    memcpy(dst, buf->cur, 4);
    buf->cur += 4;
}

extern "C" void fn_8011C870(register SaveBuffer *buf, const int *src)
{
    int v;

    if (*src) {
        v = 1;
    } else {
        v = 0;
    }
    fn_8011C730(buf, &v);
}

extern "C" void fn_8011C8D8(register SaveBuffer *buf, int *dst)
{
    int v;

    memcpy(&v, buf->cur, 4);
    if (v == 1) {
        *dst = 1;
    } else {
        *dst = 0;
    }
    buf->cur += 4;
}

extern "C" char *fn_8011C954(register SaveBuffer *buf)
{
    return buf->base;
}

extern "C" void fn_8011C980(register SaveBuffer *buf, const char *src, int n)
{
    int i;

    buf->base = buf->cur;
    for (i = 0; i < n; i++) {
        strncpy(buf->base, src + i, 1);
        buf->base++;
    }
    buf->base = buf->cur;
    buf->size = n;
}

extern "C" void fn_8011CA24(register Profile *self)
{
    fn_8011C5B0(&lbl_8066BE20->buf0, 0x12C);
    fn_8011C5B0(&lbl_8066BE20->buf1, 0x280);
}

extern "C" Profile *fn_8011CA74(void)
{
    if (!lbl_8066BE20) {
        lbl_8066BE20 = new Profile;
        fn_8011CA24(lbl_8066BE20);
    }
    return lbl_8066BE20;
}

extern "C" Profile *fn_8011CADC(register Profile *self)
{
    int i;
    int j;
    int k;

    fn_8011C578(&self->buf0);
    fn_8011C578(&self->buf1);
    self->unk18 = lbl_8066C640 != 0;
    self->unk1C = 8;
    self->unk20 = 8;
    self->unk24 = 8;
    self->unk28 = 0;
    switch (fn_80118E5C()) {
    case 0:
        self->unk30 = -1;
        break;
    case 2:
        self->unk30 = 1;
        break;
    case 3:
        self->unk30 = 1;
        break;
    case 1:
    default:
        self->unk30 = 0;
        break;
    }
    self->unk38 = self->unk18;
    self->unk3C = self->unk1C;
    self->unk40 = self->unk20;
    self->unk44 = self->unk24;
    self->unk48 = self->unk28;
    self->unk2C = 0;
    self->unk5C = 6;
    self->unk60 = 3;
    self->unk64 = 0;
    self->unk68 = -1;
    self->unk6C = 0;
    self->unk34 = 0;
    self->unk70 = 3;
    self->unk74 = 5;
    self->unk78 = 0;
    self->unk7C = 0;
    self->unk80 = 0;
    self->unk84 = 0;
    self->unk88 = 0;
    for (i = 0; i < 65; i++) {
        self->unk8C[i] = 0;
    }
    for (j = 0; j < 4; j++) {
        self->unk190[j] = 0;
    }
    self->unk194 = 0;
    self->unk198 = 0;
    self->unk19C = 0;
    for (k = 0; k < 80; k++) {
        self->unk1A0[k] = 0;
    }
    return self;
}

extern "C" int fn_8011CD30(register Profile *self)
{
    return lbl_8066BE20->unk18;
}

extern "C" void fn_8011CD60(register Profile *self, int v)
{
    lbl_8066BE20->unk18 = v;
    lbl_8066C640 = v;
}

extern "C" int fn_8011CD98(register Profile *self)
{
    return lbl_8066BE20->unk20;
}

extern "C" void fn_8011CDC8(register Profile *self, int v)
{
    double d;

    if (v < 0) {
        lbl_8066BE20->unk20 = 0;
    } else if (v > 10) {
        lbl_8066BE20->unk20 = 10;
    } else {
        lbl_8066BE20->unk20 = v;
    }
    d = lbl_8066BE20->unk20 / 10.0 * 127.0;
    fn_80119224(1, (int)d);
}

extern "C" int fn_8011CEA0(register Profile *self)
{
    return lbl_8066BE20->unk24;
}

extern "C" void fn_8011CED0(register Profile *self, int v)
{
    double d;

    if (v < 0) {
        lbl_8066BE20->unk24 = 0;
    } else if (v > 10) {
        lbl_8066BE20->unk24 = 10;
    } else {
        lbl_8066BE20->unk24 = v;
    }
    d = lbl_8066BE20->unk24 / 10.0 * 127.0;
    fn_80119224(0, (int)d);
}

extern "C" int fn_8011CFA8(register Profile *self)
{
    return lbl_8066BE20->unk28;
}

extern "C" void fn_8011CFD8(register Profile *self, int v)
{
    if ((!fn_80122378(fn_80122228()) && v) || !v) {
        lbl_8066BE20->unk28 = v;
        if (v && fn_80123240(fn_80122228())) {
            fn_8012326C(fn_80122228(), 0);
        }
    }
}

extern "C" int fn_8011D090(register Profile *self)
{
    return lbl_8066BE20->unk2C;
}

extern "C" void fn_8011D0C0(register Profile *self, int v)
{
    lbl_8066BE20->unk2C = v;
}

extern "C" int fn_8011D0F0(register Profile *self)
{
    return lbl_8066BE20->unk30;
}

extern "C" void fn_8011D120(register Profile *self, int mode, int apply)
{
    int m;

    lbl_8066BE20->unk30 = mode;
    m = 1;
    switch (mode) {
    case -1:
        m = 0;
        break;
    case 0:
        m = 1;
        break;
    case 1:
        m = 2;
        break;
    case 2:
        m = 2;
        break;
    }
    if (apply) {
        if (fn_80118E5C() == 0) {
            lbl_8066BE20->unk30 = -1;
            return;
        } else if (m == 0) {
            lbl_8066BE20->unk30 = 0;
            return;
        } else if (m == 1) {
            return;
        }
    }
    fn_80118F18(m);
}

extern "C" int fn_8011D244(register Profile *self, int bit)
{
    return lbl_8066BE20->unk5C & (1 << bit);
}

extern "C" void fn_8011D290(register Profile *self, int bit, int on)
{
    if (bit < 0) {
        lbl_8066BE20->unk5C = 0;
    } else if (on) {
        lbl_8066BE20->unk5C = lbl_8066BE20->unk5C | (1 << bit);
    }
}

extern "C" int fn_8011D308(register Profile *self, int bit)
{
    return lbl_8066BE20->unk60 & (1 << bit);
}

extern "C" void fn_8011D354(register Profile *self, int bit, int on)
{
    if (bit < 0) {
        lbl_8066BE20->unk60 = 0;
    } else if (on) {
        lbl_8066BE20->unk60 = lbl_8066BE20->unk60 | (1 << bit);
    }
}

extern "C" int fn_8011D3CC(register Profile *self)
{
    return lbl_8066BE20->unk64;
}

extern "C" void fn_8011D404(register Profile *self, int v)
{
    lbl_8066BE20->unk64 = v;
}

extern "C" int fn_8011D43C(register Profile *self)
{
    return lbl_8066BE20->unk68;
}

extern "C" void fn_8011D474(register Profile *self, int v)
{
    lbl_8066BE20->unk68 = v;
}

extern "C" int fn_8011D4AC(register Profile *self)
{
    return lbl_8066BE20->unk34;
}

extern "C" void fn_8011D4E4(register Profile *self, int v)
{
    int c = v;

    if (v < 0) {
        c = 0;
    } else if (v > 2) {
        c = 2;
    }
    lbl_8066BE20->unk34 = c;
    fn_80131878(c);
}

extern "C" int fn_8011D568(register Profile *self)
{
    return lbl_8066BE20->unk78;
}

extern "C" void fn_8011D5A0(register Profile *self, int v)
{
    lbl_8066BE20->unk78 = v;
}

extern "C" int fn_8011D5D8(register Profile *self)
{
    return lbl_8066BE20->unk80;
}

extern "C" void fn_8011D610(register Profile *self, int v)
{
    lbl_8066BE20->unk80 = v;
}

extern "C" int fn_8011D648(register Profile *self, int i)
{
    return lbl_8066BE20->unk8C[i];
}

extern "C" void fn_8011D694(register Profile *self, int i, int v)
{
    lbl_8066BE20->unk8C[i] = v;
}

extern "C" int fn_8011D6E0(register Profile *self, int i)
{
    return lbl_8066BE20->unk190[i];
}

extern "C" void fn_8011D728(register Profile *self, int i, char v)
{
    lbl_8066BE20->unk190[i] = v;
}

extern "C" int fn_8011D774(register Profile *self)
{
    return lbl_8066BE20->unk84;
}

extern "C" void fn_8011D7AC(register Profile *self, int v)
{
    lbl_8066BE20->unk84 = v;
}

extern "C" int fn_8011D7E4(register Profile *self)
{
    return lbl_8066BE20->unk88;
}

extern "C" void fn_8011D81C(register Profile *self, int v)
{
    lbl_8066BE20->unk88 = v;
}

extern "C" int fn_8011D854(register Profile *self)
{
    return lbl_8066BE20->unk194 / 10000;
}

extern "C" int fn_8011D8A4(register Profile *self)
{
    return (lbl_8066BE20->unk194 - fn_8011D854(self) * 10000) / 100;
}

extern "C" int fn_8011D918(register Profile *self)
{
    return lbl_8066BE20->unk194 - fn_8011D854(self) * 10000 - fn_8011D8A4(self) * 100;
}

extern "C" void fn_8011D988(register Profile *self, int v)
{
    lbl_8066BE20->unk194 = v;
}

extern "C" int fn_8011D9C0(register Profile *self)
{
    return lbl_8066BE20->unk198;
}

extern "C" int fn_8011D9F8(register Profile *self)
{
    return fn_8011DA4C(self, lbl_8066BE20->unk198);
}

extern "C" int fn_8011DA4C(register Profile *self, int t)
{
    return t / 86400;
}

extern "C" int fn_8011DAA0(register Profile *self)
{
    return fn_8011DAF4(self, lbl_8066BE20->unk198);
}

extern "C" int fn_8011DAF4(register Profile *self, int t)
{
    return (t - fn_8011DA4C(self, t) * 86400) / 3600;
}

extern "C" int fn_8011DB78(register Profile *self)
{
    return fn_8011DBCC(self, lbl_8066BE20->unk198);
}

extern "C" int fn_8011DBCC(register Profile *self, int t)
{
    return (t - fn_8011DA4C(self, t) * 86400 - fn_8011DAF4(self, t) * 3600) / 60;
}

extern "C" int fn_8011DC68(register Profile *self, int i)
{
    return lbl_8066BE20->unk1A0[i];
}

extern "C" int fn_8011DCB4(register Profile *self, int i)
{
    return lbl_8066BE20->unk1A0[i + 25];
}

extern "C" int fn_8011DD04(register Profile *self, int i)
{
    return lbl_8066BE20->unk1A0[i + 68];
}

extern "C" void fn_8011DD54(register Profile *self, int i, int v)
{
    lbl_8066BE20->unk1A0[i] = v;
}

extern "C" void fn_8011DDA0(register Profile *self, int i, int v)
{
    lbl_8066BE20->unk1A0[i + 25] = v;
}

extern "C" void fn_8011DDF0(register Profile *self, int i, int v)
{
    lbl_8066BE20->unk1A0[i + 68] = v;
}

extern "C" char *fn_8011DE40(register Profile *self)
{
    fn_8011C55C();
    fn_8011C628(&lbl_8066BE20->buf0);
    fn_8011C5B0(&lbl_8066BE20->buf0, 0x30);
    fn_8011C870(&lbl_8066BE20->buf0, &lbl_8066BE20->unk18);
    fn_8011C730(&lbl_8066BE20->buf0, &lbl_8066BE20->unk1C);
    fn_8011C730(&lbl_8066BE20->buf0, &lbl_8066BE20->unk20);
    fn_8011C730(&lbl_8066BE20->buf0, &lbl_8066BE20->unk24);
    if (fn_801224D0(fn_80122228())) {
        lbl_8066BE20->unk28 = 1;
        fn_8011C870(&lbl_8066BE20->buf0, &lbl_8066BE20->unk28);
        lbl_8066BE20->unk28 = 0;
    } else {
        fn_8011C870(&lbl_8066BE20->buf0, &lbl_8066BE20->unk28);
    }
    fn_8011C870(&lbl_8066BE20->buf0, &lbl_8066BE20->unk2C);
    fn_8011C730(&lbl_8066BE20->buf0, &lbl_8066BE20->unk30);
    fn_8011C730(&lbl_8066BE20->buf0, &lbl_8066BE20->unk34);
    fn_8011C730(&lbl_8066BE20->buf0, &lbl_8066BE20->unk5C);
    fn_8011C730(&lbl_8066BE20->buf0, &lbl_8066BE20->unk60);
    fn_8011C730(&lbl_8066BE20->buf0, &lbl_8066BE20->unk64);
    fn_8011C730(&lbl_8066BE20->buf0, &lbl_8066BE20->unk68);
    fn_8011C55C();
    return fn_8011C954(&lbl_8066BE20->buf0);
}

extern "C" void fn_8011DFE4(register Profile *self, const char *data, int size, int rumbleOnly)
{
    fn_8011C628(&lbl_8066BE20->buf0);
    fn_8011C5B0(&lbl_8066BE20->buf0, 0x30);
    fn_8011C980(&lbl_8066BE20->buf0, data, 0x30);
    if (rumbleOnly) {
        int flag;
        int v = 0;
        int unused = 0;

        fn_8011C8D8(&lbl_8066BE20->buf0, &flag);
        fn_8011C780(&lbl_8066BE20->buf0, &v);
        fn_8011C780(&lbl_8066BE20->buf0, &v);
        fn_8011C780(&lbl_8066BE20->buf0, &v);
        fn_8011C8D8(&lbl_8066BE20->buf0, &flag);
        fn_80123214(fn_80122228(), flag);
    } else {
        fn_8011C8D8(&lbl_8066BE20->buf0, &lbl_8066BE20->unk18);
        fn_8011C780(&lbl_8066BE20->buf0, &lbl_8066BE20->unk1C);
        fn_8011C780(&lbl_8066BE20->buf0, &lbl_8066BE20->unk20);
        fn_8011C780(&lbl_8066BE20->buf0, &lbl_8066BE20->unk24);
        fn_8011C8D8(&lbl_8066BE20->buf0, &lbl_8066BE20->unk28);
        fn_8011C8D8(&lbl_8066BE20->buf0, &lbl_8066BE20->unk2C);
        fn_8011C780(&lbl_8066BE20->buf0, &lbl_8066BE20->unk30);
        fn_8011C780(&lbl_8066BE20->buf0, &lbl_8066BE20->unk34);
        fn_8011C780(&lbl_8066BE20->buf0, &lbl_8066BE20->unk5C);
        fn_8011C780(&lbl_8066BE20->buf0, &lbl_8066BE20->unk60);
        fn_8011C780(&lbl_8066BE20->buf0, &lbl_8066BE20->unk64);
        fn_8011C780(&lbl_8066BE20->buf0, &lbl_8066BE20->unk68);
        fn_8011D120(self, lbl_8066BE20->unk30, 1);
    }
    fn_8011E1DC(self);
}

extern "C" void fn_8011E1DC(register Profile *self)
{
    double d;

    lbl_8066C640 = lbl_8066BE20->unk18;
    d = lbl_8066BE20->unk1C / 10.0 * 127.0;
    fn_80119224(2, (int)d);
    d = lbl_8066BE20->unk20 / 10.0 * 127.0;
    fn_80119224(1, (int)d);
    d = lbl_8066BE20->unk24 / 10.0 * 127.0;
    fn_80119224(0, (int)d);
    fn_80131878(lbl_8066BE20->unk34);
}

extern "C" char *fn_8011E34C(register Profile *self)
{
    int i;
    int j;
    int k;

    fn_8011C55C();
    fn_8011C628(&lbl_8066BE20->buf1);
    fn_8011C5B0(&lbl_8066BE20->buf1, 0x280);
    fn_8011C730(&lbl_8066BE20->buf1, &lbl_8066BE20->unk78);
    fn_8011C730(&lbl_8066BE20->buf1, &lbl_8066BE20->unk7C);
    fn_8011C730(&lbl_8066BE20->buf1, &lbl_8066BE20->unk80);
    fn_8011C730(&lbl_8066BE20->buf1, &lbl_8066BE20->unk84);
    fn_8011C730(&lbl_8066BE20->buf1, &lbl_8066BE20->unk88);
    for (i = 0; i < 65; i++) {
        fn_8011C730(&lbl_8066BE20->buf1, &lbl_8066BE20->unk8C[i]);
    }
    for (j = 0; j < 4; j++) {
        fn_8011C67C(&lbl_8066BE20->buf1, &lbl_8066BE20->unk190[j]);
    }
    fn_8011D988(lbl_8066BE20, fn_8011EC90(self));
    fn_8011C730(&lbl_8066BE20->buf1, &lbl_8066BE20->unk194);
    fn_8011C7D0(&lbl_8066BE20->buf1, &lbl_8066BE20->unk198);
    for (k = 0; k < 80; k++) {
        fn_8011C870(&lbl_8066BE20->buf1, &lbl_8066BE20->unk1A0[k]);
    }
    fn_8011C55C();
    return fn_8011C954(&lbl_8066BE20->buf1);
}

extern "C" void fn_8011E59C(register Profile *self)
{
    fn_8011CD60(self, 1);
    fn_8011CDC8(self, 8);
    fn_8011CED0(self, 8);
    fn_8011CFD8(self, 0);
    fn_8011D120(self, 0, 0);
    fn_8011D4E4(self, 0);
    fn_8011E1DC(self);
}

extern "C" void fn_8011E628(register Profile *self, const char *data, int peek, int slot)
{
    fn_8011C55C();
    fn_8011C628(&lbl_8066BE20->buf1);
    fn_8011C55C();
    fn_8011C5B0(&lbl_8066BE20->buf1, 0x280);
    fn_8011C55C();
    fn_8011C980(&lbl_8066BE20->buf1, data, 0x280);
    fn_8011C55C();
    if (peek) {
        int v = 0;
        int time = 0;
        char c;
        int i;
        int j;
        int k;
        int m;

        for (i = 0; i < 5; i++) {
            fn_8011C780(&lbl_8066BE20->buf1, &v);
        }
        fn_80124C4C(fn_80122228(), slot, v);
        for (j = 0; j < 65; j++) {
            fn_8011C780(&lbl_8066BE20->buf1, &v);
        }
        for (k = 0; k < 4; k++) {
            fn_8011C6D0(&lbl_8066BE20->buf1, &c);
        }
        for (m = 0; m < 2; m++) {
            fn_8011C820(&lbl_8066BE20->buf1, &time);
        }
        fn_80124B94(fn_80122228(), slot, time);
    } else {
        int a;
        int b;
        int c;

        fn_8011C780(&lbl_8066BE20->buf1, &lbl_8066BE20->unk78);
        fn_8011C780(&lbl_8066BE20->buf1, &lbl_8066BE20->unk7C);
        fn_8011C780(&lbl_8066BE20->buf1, &lbl_8066BE20->unk80);
        fn_8011C780(&lbl_8066BE20->buf1, &lbl_8066BE20->unk84);
        fn_8011C780(&lbl_8066BE20->buf1, &lbl_8066BE20->unk88);
        for (a = 0; a < 65; a++) {
            fn_8011C780(&lbl_8066BE20->buf1, &lbl_8066BE20->unk8C[a]);
        }
        for (b = 0; b < 4; b++) {
            fn_8011C6D0(&lbl_8066BE20->buf1, &lbl_8066BE20->unk190[b]);
        }
        fn_8011C780(&lbl_8066BE20->buf1, &lbl_8066BE20->unk194);
        fn_8011C820(&lbl_8066BE20->buf1, &lbl_8066BE20->unk198);
        for (c = 0; c < 80; c++) {
            fn_8011C8D8(&lbl_8066BE20->buf1, &lbl_8066BE20->unk1A0[c]);
        }
    }
    fn_8011C55C();
}

extern "C" int fn_8011E9C4(register Profile *self)
{
    return self->unk48;
}

extern "C" int fn_8011E9F8(register Profile *self)
{
    return self->unk4C;
}

extern "C" void fn_8011EA2C(register Profile *self, int keep)
{
    int i;
    int j;
    int k;

    self->unk78 = 0;
    self->unk7C = 0;
    self->unk80 = 0;
    self->unk84 = 0;
    self->unk88 = 0;
    for (i = 0; i < 65; i++) {
        self->unk8C[i] = self->unk8C[i] & ~0xC000;
    }
    for (j = 0; j < 4; j++) {
        self->unk190[j] = 0;
    }
    self->unk194 = 0;
    self->unk198 = 0;
    if (!keep) {
        for (k = 0; k < 80; k++) {
            self->unk1A0[k] = 0;
        }
    }
}

extern "C" void fn_8011EB68(register Profile *self)
{
    self->unk38 = self->unk18;
    self->unk3C = self->unk1C;
    self->unk40 = self->unk20;
    self->unk44 = self->unk24;
    self->unk48 = self->unk28;
    self->unk4C = fn_801224D0(fn_80122228());
    self->unk50 = self->unk2C;
    self->unk54 = self->unk30;
    self->unk58 = self->unk34;
}

extern "C" void fn_8011EBF8(register Profile *self)
{
    fn_8011CD60(self, self->unk38);
    fn_8011CDC8(self, self->unk40);
    fn_8011CED0(self, self->unk44);
    fn_8011CFD8(self, self->unk48);
    fn_801224FC(fn_80122228(), self->unk4C);
    fn_8011D120(self, self->unk54, 0);
    fn_8011D4E4(self, self->unk58);
}

struct Date
{
    unsigned short month; // +0x0
    unsigned short day;   // +0x2
    unsigned short year;  // +0x4
    long long unk8;       // guess: makes it 8-aligned
};

extern "C" int fn_8011EC90(register Profile *self)
{
    int stamp;
    Date date;

    fn_801AF4CC(lbl_80593BE8, &date);
    stamp = date.year * 10000 + date.month * 100 + date.day;
    return stamp;
}

extern "C" void fn_8011ED0C(register Profile *self)
{
    self->unk19C = fn_8042E96C(lbl_80593BE8);
}

extern "C" void fn_8011ED50(register Profile *self)
{
    if (self->unk19C) {
        int now = fn_8042E96C(lbl_80593BE8);

        if (now != self->unk19C) {
            self->unk198 += (unsigned int)(now - self->unk19C) / 1000;
        }
        self->unk19C = 0;
    }
}
