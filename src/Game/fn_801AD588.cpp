// System monitor CSysMon: drive errors, reset button, system font (docs/core.md row 13).
// CTask (row 15's base class, section 4.7) and CSysLock are guessed names.

extern "C" {
int DVDGetDriveStatus(void);
void PADControlAllMotors(const unsigned int *cmds);
int fn_80123038(void);
int fn_801230B8(void);
void *fn_80122228(void);
void fn_8012557C(void *p);
void *fn_80432BC4(void);
int fn_80466878(void *p);
void fn_801671F8(void *p);
void fn_80167250(void *p);
int fn_8042E868(void *p);
void fn_801AF754(void *p);
void fn_80466828(void *p);
void fn_80466850(void *p);
void fn_804325CC(void *p);
void fn_80112B94(int on);
int fn_801191FC(void);
int fn_801192D4(int chan);
void fn_80119224(int chan, int value);
void fn_801AD768(void *a, void *b);
int fn_804668A4(void);
int OSGetFontEncode(void);
int OSInitFont(void *data);
void *fn_801AC9EC(int size, const char *tag, int line, int a, int align, int b);
void fn_801ACC0C(void *p);
void *fn_801969CC(float c, float d, float e, float f, int a, int b);
void fn_80196BF0(void *p);
void fn_80196B30(void *p);
void fn_80213828(int a);
void fn_80016A68(void *p, int *ref, float a, float b, float c, float d, float e, float f, float g, float h);
void fn_80016F4C(void *p, int a, int b, int c, int d);
void fn_80016B80(void *p, int a);
void fn_800168F8(void *p, int a);
void fn_80219EAC(int a);
void fn_80219E64(void);
void fn_80219DA0(int a, int b, int c);
void fn_8021A164(int a);
void fn_8021C4C4(void *p);
void fn_8021C460(void *p);
}

struct OSFontHeader
{
    unsigned short fontType;
    unsigned short firstChar;
    unsigned short lastChar;
    unsigned short invalChar;
    unsigned short ascent;
    unsigned short descent;
    unsigned short width;
    unsigned short leading;
    unsigned short cellWidth;
    unsigned short cellHeight;
    unsigned int sheetSize;
    unsigned short sheetFormat;
    unsigned short sheetColumn;
    unsigned short sheetRow;
    unsigned short sheetWidth;
    unsigned short sheetHeight;
};

struct GXTexObj
{
    unsigned int dummy[8];
};

struct GXVtxAttrFmtList
{
    int attr;
    int cnt;
    int compType;
    unsigned char shift;
};

struct GXVtxDescList
{
    int attr;
    int type;
};

extern "C" {
char *OSGetFontWidth(const char *string, int *width);
char *OSGetFontTexture(const char *string, void **image, int *x, int *y, int *width);
void C_MTXOrtho(float m[][4], float t, float b, float l, float r, float n, float f);
void PSMTXIdentity(float m[][4]);
void PSMTXScale(float m[][4], float x, float y, float z);
void GXSetProjection(float m[][4], int type);
void GXLoadPosMtxImm(float m[][4], int id);
void GXLoadTexMtxImm(float m[][4], int id, int type);
void GXSetCurrentMtx(int id);
void GXSetZMode(int compare, int func, int update);
void GXSetNumChans(int n);
void GXSetNumTevStages(int n);
void GXSetTevOp(int stage, int mode);
void GXSetTevOrder(int stage, int coord, int map, int color);
void GXSetNumTexGens(int n);
void GXSetBlendMode(int type, int src, int dst, int op);
void GXGetVtxAttrFmtv(int fmt, GXVtxAttrFmtList *list);
void GXSetVtxAttrFmtv(int fmt, GXVtxAttrFmtList *list);
void GXGetVtxDescv(GXVtxDescList *list);
void GXSetVtxDescv(GXVtxDescList *list);
void GXClearVtxDesc(void);
void GXSetVtxDesc(int attr, int type);
void GXSetVtxAttrFmt(int fmt, int attr, int cnt, int type, int frac);
void GXInitTexObj(GXTexObj *obj, void *image, int width, int height, int format, int wrapS, int wrapT, int mipmap);
void GXInitTexObjLOD(GXTexObj *obj, int minFilt, int magFilt, float minLod, float maxLod, float bias, int clamp, int edge, int aniso);
void GXLoadTexObj(GXTexObj *obj, int id);
void GXBegin(int type, int fmt, int n);
void GXFlush(void);
void GXSetTexCoordGen2(int dst, int func, int src, unsigned int mtx, int normalize, unsigned int pt);
int OSGetResetButtonState(void);
void OSResetSystem(int reset, unsigned int code, int menu);
int PADRecalibrate(unsigned int mask);
int PADReset(unsigned int mask);
void PADRead(struct PADStatus *status);
void VIWaitForRetrace(void);
void VISetBlack(int black);
void VIFlush(void);
void AXRegisterAuxACallback(void *cb, void *ctx);
void AXQuit(void);
int fn_8024FBBC(void);
int OSGetLanguage(void);
void fn_8024C670(int v);
int fn_8021A9EC(int a, int b);
void fn_8021A5FC(int a);
void fn_8021A1F0(unsigned int a, int b);
unsigned int fn_8042D324(void *p);
}

struct PADStatus
{
    unsigned short button;
    signed char stickX;
    signed char stickY;
    signed char substickX;
    signed char substickY;
    unsigned char triggerL;
    unsigned char triggerR;
    unsigned char analogA;
    unsigned char analogB;
    signed char err;
};

struct Mode
{
    char pad[0x78];
    unsigned short f78;
    unsigned short f7A;
    char pad7C[4];
};

class Text
{
public:
    char pad[0x100];
    Text() __asm__("fn_800166B0");
};

extern int lbl_8066BB0C;
extern int lbl_8066C788;

float lbl_8066C6A0 = 400.0f;
float lbl_8066C6A4 = 30.0f;
int lbl_8066C6A8 = 0;
void *lbl_8066C6AC = 0;
int lbl_8066C6B0[2] = { 0, 0 };
float lbl_8066F508 = 320.0f - lbl_8066C6A0 * 0.5f;
float lbl_8066F50C = lbl_8066F508 + lbl_8066C6A0 * 0.5f;
float lbl_8066F510 = 240.0f - lbl_8066C6A4 * 0.5f;
float lbl_8066F514 = lbl_8066C6A4 * 0.5f + lbl_8066F510 - 12.0f;

union PPCWGPipe
{
    unsigned char u8;
    short s16;
    unsigned int u32;
    float f32;
};

extern volatile PPCWGPipe GXWGFifo[] __asm__("0xCC008000");

static inline void GXEnd(void)
{
}

static inline void GXSetTexCoordGen(int dst, int func, int src, unsigned int mtx)
{
    GXSetTexCoordGen2(dst, func, src, mtx, 0, 0x7D);
}

static inline void GXPosition3s16(short x, short y, short z)
{
    {
        register volatile PPCWGPipe *p = GXWGFifo;
        p->s16 = x;
    }
    {
        register volatile PPCWGPipe *p = GXWGFifo;
        p->s16 = y;
    }
    {
        register volatile PPCWGPipe *p = GXWGFifo;
        p->s16 = z;
    }
    return;
}

static inline void GXTexCoord2s16(short s, short t)
{
    {
        register volatile PPCWGPipe *p = GXWGFifo;
        p->s16 = s;
    }
    {
        register volatile PPCWGPipe *p = GXWGFifo;
        p->s16 = t;
    }
    return;
}

class CSysLock
{
public:
    int f0;
    CSysLock() __asm__("fn_80466920");
    ~CSysLock();
};

extern "C" {
CSysLock *fn_801AF090(void);
void fn_801AF0EC(register CSysLock *self);
void fn_801AF10C(register CSysLock *self);
void fn_801AF12C(register CSysLock *self);
}
extern Mode lbl_8057E430;
extern char lbl_80594E00[];
extern char lbl_80594EF0[];

extern char lbl_80552920[];
extern char lbl_80593BE8[];

__asm__(".section .rodata\n"
        "\t.4byte 0x00000000, 0x41737365, 0x72743A20, 0x25733A25\n"
        "\t.4byte 0x69202573, 0x20282573, 0x29000000, 0x634D6F76\n"
        "\t.4byte 0x6965506C, 0x61796572, 0x3A496E73, 0x74616E63\n"
        "\t.4byte 0x65000000, 0x00000000, 0x63417474, 0x72616374\n"
        "\t.4byte 0x4D6F7669, 0x653A496E, 0x7374616E, 0x63650000\n"
        "\t.4byte 0x4D656D43, 0x6172643A, 0x47656E65, 0x72616C00\n"
        "\t.4byte 0x4D656D63, 0x6172643A, 0x4D757465, 0x78000000\n"
        "\t.4byte 0x4D656D63, 0x6172643A, 0x47656E65, 0x72616C00\n"
        "\t.4byte 0x4D656D63, 0x6172643A, 0x54687265, 0x61640000\n"
        "\t.4byte 0x4D656D63, 0x6172643A, 0x54687265, 0x61645374\n"
        "\t.4byte 0x61636B00, 0x43417379, 0x6E634C6F, 0x61646572\n"
        "\t.4byte 0x3A496E73, 0x74616E63, 0x65000000, 0x55492F65\n"
        "\t.4byte 0x61666F6E, 0x74300000, 0x55492F65, 0x61666F6E\n"
        "\t.4byte 0x74310000, 0x55492F65, 0x61666F6E, 0x74330000\n"
        "\t.4byte 0x55492F65, 0x61626566, 0x6E743000, 0x55492F65\n"
        "\t.4byte 0x61626566, 0x6E743100, 0x55492F65, 0x61626566\n"
        "\t.4byte 0x6E743300, 0x4575726F, 0x7374696C, 0x65204C54\n"
        "\t.4byte 0x20537464, 0x00000000, 0x4575726F, 0x7374696C\n"
        "\t.4byte 0x65204C54, 0x20537464, 0x20436F6E, 0x64656E73\n"
        "\t.4byte 0x65640000, 0x45415320, 0x53616E73, 0x436F6E64\n"
        "\t.4byte 0x656E7365, 0x64000000\n"
        "\t.text");

const char *lbl_804D39AC[4][6] = {
    {
        "Licensed by Nintendo",
        "The Disc Cover is open.\n" "If you want to continue\n" "the game, please close\n" "the Disc Cover.",
        "Please insert the\n" "Imperfects Game Disc.",
        "Please insert the\n" "Imperfects Game Disc.",
        "The Game Disc could not\n" "be read. Please read the\n" "Nintendo GameCube\n" "Instruction Booklet\n" "for more information.",
        "An error has occurred.\n" "Turn the power off and refer\n" "to the Nintendo GameCube\n" "Instruction Booklet\n" "for further instructions.",
    },
    {
        "Licensed by Nintendo",
        "Le couvercle est ouvert.\n" "Pour continuer \340 jouer,\n" "veuillez fermer le couvercle.",
        "Veuillez ins\351rer le disque\n" "Les Imparfaits.",
        "Veuillez ins\351rer le disque\n" "Les Imparfaits.",
        "La lecture du disque a \351chou\351.\n" "Veuillez vous r\351f\351rer au\n" "manuel d'instructions\n" "Nintendo GameCube pour de plus\n" "amples informations.",
        "Une erreur est survenue.\n" "Eteignez la console et r\351f\351rez-vous\n" "au manuel d'instructions\n" "Nintendo GameCube pour de plus\n" "amples informations.",
    },
    {
        "Licensed by Nintendo",
        "Der Disc-Deckel ist ge\366ffnet.\n" "Bitte den Disc-Deckel schlie\337en,\n" "um mit dem Spiel fortzufahren.\n",
        "Bitte die Imperfects\n" "Game Disc einlegen.",
        "Bitte die Imperfects\n" "Game Disc einlegen.",
        "Diese Game Disc kann\n" "nicht gelesen werden.\n" "Bitte Bedienungsanleitung\n" "des Nintendo GameCube lesen,\n" "um weitere Informationen zu\n" "erhalten.",
        "Ein Fehler ist aufgetreten.\n" "Bitte den Nintendo GameCube\n" "ausschalten und die\n" "Bedienungsanleitung lesen, um weitere\n" "Informationen zu erhalten.",
    },
    {
        "Licensed by Nintendo",
        "Il coperchio del disco \350 aperto.\n" "Se vuoi proseguire nel gioco,\n" "chiudi il coperchio del disco.",
        "Inserisci il disco di gioco di\n" "Imperfetti.",
        "Inserisci il disco di gioco di\n" "Imperfetti.",
        "Impossibile leggere il disco di gioco.\n" "Consulta il manuale d'istruzioni\n" "del Nintendo GameCube\n" "per ulteriori indicazioni.",
        "Si \350 verificato un errore.\n" "Spegni (OFF) e controlla\n" "il manuale d'istruzioni\n" " del Nintendo GameCube\n" "per ulteriori indicazioni.",
    },
};

class CTask
{
public:
    unsigned char flags;
    char pad04[0x70];
    int handle;
    CTask() __asm__("fn_801B6D8C");
    ~CTask();
    void Start(void (*fn)(void *, void *)) __asm__("fn_801B6E44");
    void Stop() __asm__("fn_801B6EC0");
    void fn_801B6FCC(const char *s, float *w, float *h) __asm__("fn_801B6FCC");
    void fn_801B71EC(float x, float y, float z, const char *s) __asm__("fn_801B71EC");
};

class CSysMon : public CTask
{
public:
    int prevStatus; // +0x78
    int status;
    int error;
    int f84;
    int f88;
    int f8C;
    void *f90;
    Text *f94;
    int motor0;
    int motor1;
    CSysMon();
    ~CSysMon();
};

extern "C" {
CSysMon *fn_801AD68C(void);
void fn_801AD730(register CSysMon *self);
void fn_801AD7BC(register CSysMon *self);
void fn_801ADC04(register CSysMon *self);
void fn_801ADDF4(register CSysMon *self);
void fn_801ADEB8(register CSysMon *self, int clear);
void fn_801AE03C(register CSysMon *self, const char *s, float *w, float *h);
void fn_801AE0CC(register CSysMon *self, float x, float y, float z, const char *s);
void fn_801AE164(register CSysMon *self, const char *s, float *w, float *h);
void fn_801AE3CC(register CSysMon *self, float x, float y, float z, const char *s);
void fn_801AEAE8(register CSysMon *self);
void fn_801AECE8(register CSysMon *self, int reset);
int fn_80466950(CSysMon *self);
int fn_801AEFA0(void);
}

CSysMon::CSysMon()
{
    status = 0;
    prevStatus = status;
    error = -1;
    f84 = 0;
    f90 = 0;
    f88 = 1;
    motor0 = 100;
    motor1 = 100;
}

CSysMon::~CSysMon()
{
    fn_801AD730(this);
}

extern "C" CSysMon *fn_801AD68C(void)
{
    static CSysMon inst;
    return &inst;
}

extern "C" void fn_801AD6F0(register CSysMon *self)
{
    self->Start(fn_801AD768);
}

extern "C" void fn_801AD730(register CSysMon *self)
{
    self->Stop();
}

extern "C" void fn_801AD768(void *a, void *b)
{
    register CSysMon *r = fn_801AD68C();
    CSysMon *m = r;
    fn_801AEAE8(m);
    fn_801AD7BC(m);
    return;
}

extern "C" void fn_801AD7BC(register CSysMon *self)
{
    int ok;
    self->prevStatus = self->status;
    self->status = DVDGetDriveStatus();
    ok = 1;
    if (!((self->flags & 0x10) && self->status == self->prevStatus)) {
        switch (self->status) {
        case 5:
            if (fn_80123038()) {
                self->error = 1;
            } else {
                ok = 0;
            }
            break;
        case 4:
            if (fn_80123038()) {
                self->error = 2;
            } else {
                ok = 0;
            }
            break;
        case 6:
            if (fn_80123038()) {
                self->error = 3;
            } else {
                ok = 0;
            }
            break;
        case 11:
            if (fn_80123038()) {
                self->error = 4;
            } else {
                ok = 0;
            }
            break;
        case -1:
            if (fn_80123038()) {
                self->error = 5;
                self->f88 = 0;
            } else {
                ok = 0;
            }
            break;
        default:
            if (self->flags & 0x10) {
                ok = self->status != 0;
            } else {
                ok = 0;
            }
            break;
        }
    }
    if (ok && !(self->flags & 0x10)) {
        self->f84 = fn_801AEFA0();
        unsigned int cmds[4] = { 2, 2, 2, 2 };
        PADControlAllMotors(cmds);
        if (fn_80466878(fn_80432BC4()) == 3) {
            fn_801671F8(fn_80432BC4());
        }
        if (!fn_8042E868(lbl_80552920)) {
            fn_801AF754(lbl_80593BE8);
            fn_80466828(lbl_80593BE8);
            fn_80112B94(1);
            if (fn_801191FC()) {
                self->motor0 = fn_801192D4(0);
                self->motor1 = fn_801192D4(1);
                fn_80119224(0, 0);
                fn_80119224(1, 0);
            }
        }
        fn_801ADC04(self);
        self->flags |= 0x10;
        fn_801ADEB8(self, 0);
        while (self->flags & 0x10) {
            if (fn_801230B8()) {
                fn_8012557C(fn_80122228());
            }
            fn_801AD768(0, 0);
        }
    } else if (ok && self->status != 8) {
        fn_801ADEB8(self, 0);
    } else if (!ok && (self->flags & 0x10)) {
        self->error = -1;
        fn_801ADEB8(self, 1);
        fn_801ADDF4(self);
        if (fn_80466878(fn_80432BC4()) == 4) {
            fn_80167250(fn_80432BC4());
        }
        if (!fn_8042E868(lbl_80552920)) {
            fn_80112B94(0);
            fn_80466850(lbl_80593BE8);
            fn_804325CC(lbl_80593BE8);
            if (fn_801191FC()) {
                fn_80119224(0, self->motor0);
                fn_80119224(1, self->motor1);
            }
        }
        self->flags &= ~0x10;
    }
}

extern "C" void fn_801ADC04(register CSysMon *self)
{
    int size;
    if (!(lbl_8066BB0C && fn_804668A4())) {
        if (lbl_8066C6AC == 0) {
            size = OSGetFontEncode() == 1 ? 0x120F00 : 0x20120;
            lbl_8066C6AC = fn_801AC9EC(size, "CSysMon::SysFont", 0x20F, 1, 0x20, 0);
            if (!OSInitFont(lbl_8066C6AC)) {
                fn_801ACC0C(lbl_8066C6AC);
                lbl_8066C6AC = 0;
            }
        }
    }
    fn_801AF0EC(fn_801AF090());
    self->f8C = lbl_8066C788;
    if (self->f8C == 0) {
        self->f90 = fn_801969CC(80.0f, 0.01f, 300.0f, 1.0f, lbl_8057E430.f7A, lbl_8057E430.f78);
        fn_80196BF0(self->f90);
    }
    self->f94 = new Text;
    fn_80016A68(self->f94, lbl_8066C6B0, 0.0f, 0.0f, 0.0f, 2.0f, 2.0f, 2.0f, 2.0f, 0.0f);
    fn_80016F4C(self->f94, 0xFF, 0, 0, 0);
    fn_80219EAC(1);
    fn_80016B80(self->f94, 0x31);
    fn_80219E64();
}

extern "C" void fn_801ADDF4(register CSysMon *self)
{
    if (self->f94) {
        if (self->f94) {
            fn_800168F8(self->f94, 3);
        } else {
        }
        self->f94 = 0;
    }
    if (lbl_8066C6AC) {
        fn_801ACC0C(lbl_8066C6AC);
        lbl_8066C6AC = 0;
    }
    fn_801AF12C(fn_801AF090());
    if (self->f8C == 0) {
        fn_80213828(self->f8C);
    }
    if (self->f90) {
        fn_80196B30(self->f90);
        self->f90 = 0;
    }
}

extern "C" void fn_801ADEB8(register CSysMon *self, int clear)
{
    int show = self->error != -1;
    if (show && !clear) {
        const char *msg = lbl_804D39AC[self->f84][self->error];
        float w;
        float h;
        fn_80219EAC(1);
        fn_80219DA0(0, 0, 0);
        fn_801AE03C(self, msg, &w, &h);
        fn_801AE0CC(self, 320.0f - w / 2.0f, 240.0f - h / 2.0f, 0.0f, msg);
        fn_8021A164(1);
        fn_80219E64();
    } else if (clear) {
        if (!(lbl_8066BB0C && fn_804668A4())) {
            fn_8021C4C4(lbl_80594E00);
            fn_8021C460(lbl_80594EF0);
        }
        fn_801AF10C(fn_801AF090());
    }
}

extern "C" void fn_801AE03C(register CSysMon *self, const char *s, float *w, float *h)
{
    if (lbl_8066BB0C && fn_804668A4()) {
        self->fn_801B6FCC(s, w, h);
        return;
    } else {
        fn_801AE164(self, s, w, h);
    }
}

extern "C" void fn_801AE0CC(register CSysMon *self, float x, float y, float z, const char *s)
{
    if (lbl_8066BB0C && fn_804668A4()) {
        self->fn_801B71EC(x, y, z, s);
    } else {
        fn_801AE3CC(self, x, y, z, s);
    }
}

extern "C" void fn_801AE164(register CSysMon *self, const char *s, float *w, float *h)
{
    if (lbl_8066C6AC == 0) {
        return;
    }
    const char *p = s;
    int width = 0;
    int lines = 0;
    int x = 0;
    int maxX = 0;
    int height = 0;
    OSFontHeader *font = (OSFontHeader *)lbl_8066C6AC;
    short scale = font->cellWidth << 4;
    short spacing = -16;
    while (*p != 0) {
        if (*p == '\n') {
            if (maxX < x) {
                maxX = x;
            }
            x = 0;
            lines++;
        }
        p = OSGetFontWidth(p, &width);
        x += scale * width / font->cellWidth + spacing;
        if (maxX < x) {
            maxX = x;
        }
    }
    height = font->leading * scale / font->cellWidth * lines + (font->ascent + font->descent) * scale / font->cellWidth;
    *w = (maxX + 15) / 16;
    *h = (height + 15) / 16;
}

extern "C" void fn_801AE3CC(register CSysMon *self, float x, float y, float z, const char *s)
{
    if (lbl_8066C6AC == 0) {
        return;
    }
    const char *p = s;
    GXTexObj texObj;
    int pos[4][2];
    int tex[4][2];
    GXVtxAttrFmtList fmt[27];
    GXVtxDescList desc[27];
    int cx = (int)x << 4;
    int cy = (int)y << 4;
    int cz = (int)z << 4;
    int fx = 0;
    int fy = 0;
    int fw = 0;
    void *image = 0;
    void *lastImage = 0;
    OSFontHeader *font = (OSFontHeader *)lbl_8066C6AC;
    short scale = font->cellWidth << 4;
    short spacing = -16;
    float m[3][4];

    C_MTXOrtho(m, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -1.0f);
    GXSetProjection(m, 1);
    PSMTXIdentity(m);
    GXLoadPosMtxImm(m, 0);
    GXSetCurrentMtx(0);
    GXSetZMode(1, 7, 1);
    GXSetNumChans(0);
    GXSetNumTevStages(1);
    GXSetTevOp(0, 3);
    GXSetTevOrder(0, 0, 0, 0xFF);
    PSMTXScale(m, 1.0f / (unsigned int)font->sheetWidth, 1.0f / (unsigned int)font->sheetHeight, 1.0f);
    GXLoadTexMtxImm(m, 0x1E, 1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen(0, 1, 4, 0x1E);
    GXSetBlendMode(1, 1, 0, 0);
    GXGetVtxAttrFmtv(0, fmt);
    GXGetVtxDescv(desc);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 9, 1, 3, 4);
    GXSetVtxAttrFmt(0, 0xD, 1, 3, 0);
    while (*p != 0) {
        if (*p == '\n') {
            cx = (int)x << 4;
            cy += font->leading * scale / font->cellWidth;
            do {
                p++;
            } while (*p != 0 && (*p == ' ' || *p == '\t'));
        } else {
            p = OSGetFontTexture(p, &image, &fx, &fy, &fw);
            if (lastImage != image) {
                lastImage = image;
                GXInitTexObj(&texObj, image, font->sheetWidth, font->sheetHeight, font->sheetFormat, 0, 0, 0);
                GXInitTexObjLOD(&texObj, 1, 1, 0.0f, 0.0f, 0.0f, 0, 0, 0);
                GXLoadTexObj(&texObj, 0);
            }
            pos[0][0] = cx;
            pos[0][1] = cy;
            pos[1][0] = cx + scale;
            pos[1][1] = pos[0][1];
            pos[2][0] = pos[1][0];
            pos[2][1] = cy + (font->ascent + font->descent) * scale / font->cellWidth;
            pos[3][0] = pos[0][0];
            pos[3][1] = pos[2][1];
            tex[0][0] = fx;
            tex[0][1] = fy;
            tex[1][0] = fx + font->cellWidth;
            tex[1][1] = tex[0][1];
            tex[2][0] = tex[1][0];
            tex[2][1] = fy + font->cellHeight;
            tex[3][0] = tex[0][0];
            tex[3][1] = tex[2][1];
            GXBegin(0x80, 0, 4);
            GXPosition3s16(pos[0][0], pos[0][1], cz);
            GXTexCoord2s16(tex[0][0], tex[0][1]);
            GXPosition3s16(pos[1][0], pos[1][1], cz);
            GXTexCoord2s16(tex[1][0], tex[1][1]);
            GXPosition3s16(pos[2][0], pos[2][1], cz);
            GXTexCoord2s16(tex[2][0], tex[2][1]);
            GXPosition3s16(pos[3][0], pos[3][1], cz);
            GXTexCoord2s16(tex[3][0], tex[3][1]);
            GXEnd();
            cx += scale * fw / font->cellWidth + spacing;
        }
    }
    PSMTXIdentity(m);
    GXLoadTexMtxImm(m, 0x1E, 1);
    GXSetVtxAttrFmtv(0, fmt);
    GXSetVtxDescv(desc);
    GXFlush();
}

extern "C" void fn_801AEAE8(register CSysMon *self)
{
    int pressed = OSGetResetButtonState() != 0;
    if (!pressed && (self->flags & 0x4)) {
        if (self->f88 == 0) {
            self->flags &= ~0x4;
            return;
        }
        self->flags |= 0x8;
    } else if (pressed) {
        self->flags |= 0x4;
    }
    if (self->flags & 0x8) {
        if (!((self->flags & 0x10) && fn_80466950(self) == -1)) {
            fn_801AECE8(self, 0);
        }
    }
}

extern "C" void fn_801AEBFC(void)
{
    int pressed = OSGetResetButtonState() != 0;
    register CSysMon *r = fn_801AD68C();
    CSysMon *m = r;
    if (!pressed && (m->flags & 0x4)) {
        if (m->f88 == 0) {
            m->flags &= ~0x4;
            return;
        }
        m->flags |= 0x8;
    } else if (pressed) {
        m->flags |= 0x4;
    }
}

extern "C" void fn_801AECE8(register CSysMon *self, int reset)
{
    int tries = 10;
    int i;
    int n;
    PADStatus status[4];
    unsigned int chans[4] = { 0x80000000, 0x40000000, 0x20000000, 0x10000000 };
    int unused;
    if (!fn_80123038()) {
        return;
    }
    for (i = 0; i < 4; i++) {
        n = 0;
        if (!PADRecalibrate(chans[i])) {
            do {
                PADReset(chans[i]);
                VIWaitForRetrace();
                PADRead(status);
                n++;
            } while (status[i].err == -1 && n < 10);
        } else {
        }
    }
    int ax = fn_8024FBBC();
    int fade = lbl_8066BB0C && !(self->flags & 0x10);
    int h = 0;
    if (fade) {
        h = fn_8021A9EC(0, 0);
    }
    if (ax || fade) {
        unsigned int v;
        for (v = 0; v < 0x80; v++) {
            if (ax) {
                fn_8024C670(0x7F - v);
            }
            if (fade) {
                fn_80219EAC(1);
                fn_8021A5FC(-1);
                fn_8021A1F0(v << 25, 0);
                fn_80219E64();
            }
            unsigned int t = fn_8042D324(lbl_80593BE8) + 4;
            while (fn_8042D324(lbl_80593BE8) < t) {
            }
        }
    }
    if (ax) {
        AXRegisterAuxACallback(0, 0);
        AXQuit();
    }
    VISetBlack(1);
    VIFlush();
    VIWaitForRetrace();
    OSResetSystem(reset, 0, reset);
}

extern "C" int fn_801AEFA0(void)
{
    int lang = OSGetLanguage();
    int r;
    switch (lang) {
    case 4:
        r = 3;
        break;
    case 1:
        r = 2;
        break;
    case 2:
        r = 1;
        break;
    case 0:
    case 3:
    case 5:
    default:
        r = 0;
        break;
    }
    return r;
}

extern "C" CSysLock *fn_801AF090(void)
{
    static CSysLock inst;
    return &inst;
}

extern "C" void fn_801AF0EC(register CSysLock *self)
{
}

extern "C" void fn_801AF10C(register CSysLock *self)
{
}

extern "C" void fn_801AF12C(register CSysLock *self)
{
    self->f0 = 0;
}
