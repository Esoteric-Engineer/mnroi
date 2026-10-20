// HUD overlays: fills the overlay records (both players' template names, without plr_/plr_alt, in 3 and 4) and packs each record's ovr_<name><lang> image into its overlay texture; see docs/versus.md section 4.4.

inline int sn_return_decl(int a) { return a; }

class Hud
{
public:
    char pad[0x340];
    char res[0x418C - 0x340]; // +0x340 image bank
    int versus;               // +0x418C
};

struct Vec2
{
    float x;
    float y;
};

struct OverlayInfo
{
    signed char modes; // +0x0, ANDed with both mode masks
    const char *name;  // +0x4 overlay texture
    char buf[0x50];    // +0x8 image name, without ovr_ and the language
    Vec2 offset;       // +0x58
    Vec2 uv0;          // +0x60
    Vec2 uv1;          // +0x68
    float width;       // +0x70
    float height;      // +0x74
};

struct Image;

struct List
{
    char pad[0x28];
};

struct PadState
{
    char pad[0x7E];
    unsigned short buttons; // +0x7E
};

extern "C" {
char *strcpy(char *dst, const char *src);
char *strstr(const char *s, const char *find);
char *fn_80131060(int player);
void fn_801B738C(char *name);
void fn_80006450(Hud *self, const char *name);
int strcmp(const char *a, const char *b);
int sprintf(char *buf, const char *fmt, ...);
int fn_802CD41C(void *image, int x, int y, int level);
void fn_802CD5D8(void *image, int x, int y, int level, int color);
int fn_80427400();
char *fn_8012EB48(int lang);
Image *fn_80017FB0(void *res, const char *name);
int fn_80426B04(void *image);
int fn_80426B54(void *image);
int fn_80426BA4(void *image);
int fn_80426BF4(void *image);
void fn_80426A54(Vec2 *v, float x, float y);
int fn_801308C0();
int fn_8013156C();
void *fn_801B4284(int capacity, const char *name);
void fn_801B4764(void *registry, void *key, void *value);
void *fn_801B4938(void *registry, void *key);
void fn_801B4524(void *registry, int a);
void fn_801B5BA8(List *list, int capacity, float grow);
void fn_801B5C74(List *list, int flags);
int fn_801B6A44(List *list);
Image *fn_801B5D3C(List *list, int i);
void fn_801B6040(List *list, void *item);
void fn_801B6768(List *list, void *item);
}

extern OverlayInfo lbl_8050F820[13];
extern char *lbl_804BFA00[];
extern char lbl_8057E430[];
extern const int lbl_8066FB70;

extern "C" void fn_800061CC(register Hud *self)
{
    int i;
    char *name0;
    char *name1;

    for (i = 0; i <= 12; i++) {
        strcpy(lbl_8050F820[i].buf, lbl_8050F820[i].name);
    }
    name0 = fn_80131060(0);
    name1 = fn_80131060(1);
    if (strstr(name0, "plr_alt")) {
        name0 += 7;
    } else {
        name0 += 4;
    }
    if (strstr(name1, "plr_alt")) {
        name1 += 7;
    } else {
        name1 += 4;
    }
    strcpy(lbl_8050F820[3].buf, name0);
    strcpy(lbl_8050F820[4].buf, name1);
    fn_801B738C(lbl_8050F820[3].buf);
    fn_801B738C(lbl_8050F820[4].buf);
    fn_80006450(self, "overlay1");
    if (self->versus) {
        fn_80006450(self, "overlay2");
    }
}

// Copies a w x h block of pixels from src (sx, sy) to dst (dx, dy).
extern "C" void fn_8000634C(void *dst, void *src, int dx, int dy, int sx, int sy, int w, int h)
{
    int x;
    int y;

    for (x = 0; x < w; x++) {
        for (y = 0; y < h; y++) {
            fn_802CD5D8(dst, dx + x, dy + y, 0, fn_802CD41C(src, sx + x, sy + y, 0));
        }
    }
}

// Packs the images of the overlay records that use `name` and match the mode into that texture, in rows,
// widest first, 2 pixels apart, and records each one's place and size in its record.
extern "C" void fn_80006450(register Hud *self, const char *name)
{
    register int unused = 2;
    int lang = fn_80427400();
    const char *suffix = fn_8012EB48(lang);
    void *dst = fn_80017FB0(self->res, name);
    if (dst == 0) {
        return;
    }
    float w = fn_80426B04(dst);
    float h = fn_80426B54(dst);
    int xoff = (((PadState *)lbl_8057E430)->buttons & 4) ? lbl_8066FB70 / 2 : 0;
    void *reg = fn_801B4284(13, "SOverlayInfo");
    char buf[0x50];
    List list;
    fn_801B5BA8(&list, 13, 1.0f);
    const int mode = self->versus ? (fn_801308C0() ? 4 : 2) : 1;
    const int mode2 = self->versus ? (fn_8013156C() ? 8 : 16) : -1;
    int i;
    for (i = 0; i <= 12; i++) {
        if (strcmp(lbl_804BFA00[i], name) == 0 && (lbl_8050F820[i].modes & mode) && (lbl_8050F820[i].modes & mode2)) {
            sprintf(buf, "ovr_%s%s", lbl_8050F820[i].buf, suffix);
            Image *image = fn_80017FB0(self->res, buf);
            if (image) {
                fn_801B6040(&list, image);
                fn_801B4764(reg, image, &lbl_8050F820[i]);
            }
        }
    }
    OverlayInfo *info = 0;
    int y = 0;
    while (fn_801B6A44(&list) > 0) {
        int x = 0;
        int n = fn_801B6A44(&list);
        void *best = fn_801B5D3C(&list, 0);
        int j;
        for (j = 1; j < n; j++) {
            void *e = fn_801B5D3C(&list, j);
            if (fn_80426B04(e) > fn_80426B04(best)) {
                best = e;
            }
        }
        fn_8000634C(dst, best, x, y, 0, 0, fn_80426B04(best), fn_80426B54(best));
        info = (OverlayInfo *)fn_801B4938(reg, best);
        info->width = fn_80426B04(best);
        info->height = fn_80426B54(best);
        fn_80426A54(&info->offset, fn_80426BA4(best) + xoff, fn_80426BF4(best));
        fn_80426A54(&info->uv0, x / w, y / h);
        fn_80426A54(&info->uv1, (fn_80426B04(best) + x) / w, (fn_80426B54(best) + y) / h);
        x += fn_80426B04(best) + 2;
        fn_801B6768(&list, best);
        int rowHeight = fn_80426B54(best);
        int more = 1;
        while (more) {
            void *fit = 0;
            n = fn_801B6A44(&list);
            int k;
            for (k = 0; k < n; k++) {
                void *e = fn_801B5D3C(&list, k);
                if (fn_80426B04(e) <= fn_80426B04(dst) - x && (fit == 0 || fn_80426B04(e) > fn_80426B04(fit))) {
                    fit = e;
                }
            }
            if (fit) {
                fn_8000634C(dst, fit, x, y, 0, 0, fn_80426B04(fit), fn_80426B54(fit));
                info = (OverlayInfo *)fn_801B4938(reg, fit);
                info->width = fn_80426B04(fit);
                info->height = fn_80426B54(fit);
                fn_80426A54(&info->offset, fn_80426BA4(fit) + xoff, fn_80426BF4(fit));
                fn_80426A54(&info->uv0, x / w, y / h);
                fn_80426A54(&info->uv1, (fn_80426B04(fit) + x) / w, (fn_80426B54(fit) + y) / h);
                x += fn_80426B04(fit) + 2;
                if (fn_80426B54(fit) > rowHeight) {
                    rowHeight = fn_80426B54(fit);
                }
                fn_801B6768(&list, fit);
                more = 1;
            } else {
                more = 0;
            }
        }
        y += rowHeight + 2;
    }
    fn_801B4524(reg, 0);
    fn_801B5C74(&list, 2);
}

// Read by fn_80007168 (unmatched); defined here so the .rodata claim ends 8-aligned.
extern const float lbl_80482C0C __attribute__((section(".rodata"))) = 30.0f;
