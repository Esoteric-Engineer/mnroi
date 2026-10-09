// FrameCtx level-load prepare (guessed): copies the names, loads the level and its set; see docs/versus.md section 5, row 9d.

inline int sn_return_decl(int a) { return a; }

extern "C" {
char *strncpy(char *dst, const char *src, unsigned n);
void fn_80018198();
void fn_8011406C();
void fn_801A9564(int a);
void fn_801B4094(char *path, const char *ext);
void fn_800617A8();
int fn_8042F268(void *p);
void fn_80432D50(void *p, float a);
void fn_80233218(char *p, int a);
void fn_80091578(void *g);
void fn_801A2108(char *p, int a);
void fn_800777C4(const char *p, int a);
void fn_80091648(void *g);
void fn_8019EBF8(char *p, int a);
struct Level;
Level *fn_800B271C(char *path, int flags);
void *fn_800A4DF8(const char *name, Level *lv, int a);
int fn_80020B4C(const char *s, int a);
void fn_80020BF8(int a);
void *fn_8009B35C(Level *lv, void *h);
void fn_80114420();
extern const char lbl_8048584C[]; // "ngl"
extern const char lbl_80485850[]; // "global"
extern const char lbl_80485858[]; // "GENERIC.NCL"
}

class GameFlow
{
public:
    char pad[0x300]; // size is a placeholder; > 8 keeps the instance out of .sdata
};

struct FrameCtx
{
    char pad0[0x3D0];
    int f3D0; // +0x3D0
};

struct Level
{
    char pad0[0x124];
    void *f124; // +0x124
};

extern GameFlow lbl_80552920;
extern char lbl_80552110[];
extern char lbl_8066D568[8];
extern int lbl_8066B664;

extern "C" Level *fn_8002CE78(register FrameCtx *self, const char *name, const char *name2, int flags)
{
    char path[0x80];
    char path2[0x80];
    Level *lv;
    void *r;
    fn_80018198();
    fn_8011406C();
    fn_801A9564(0x500000);
    strncpy(path, name, 0x20);
    path[0x1F] = 0;
    self->f3D0 = !name2 || (flags & 0x10);
    if (name2) {
        strncpy(path2, name2, 0x20);
        path2[0x1F] = 0;
    } else {
        strncpy(path2, name, 0x20);
        path2[0x1F] = 0;
    }
    fn_801B4094(path, lbl_8048584C);
    fn_801B4094(path2, lbl_8048584C);
    fn_800617A8();
    if (fn_8042F268(lbl_8066D568) == 0 && lbl_8066B664 != 0) {
        fn_80432D50(&lbl_80552920, 0.1f);
        fn_80233218(path2, 2);
        fn_80091578(lbl_80552110);
        fn_80432D50(&lbl_80552920, 0.2f);
        fn_801A2108(path2, 1);
        fn_800777C4(lbl_80485850, 1);
        fn_800777C4(path2, 0);
    }
    fn_801A9564(0x200000);
    fn_80091648(lbl_80552110);
    fn_8019EBF8(path2, 1);
    lv = fn_800B271C(path, flags);
    r = 0;
    fn_801A9564(0x40000);
    if (name2) {
        void *h = fn_800A4DF8(name2, lv, 0);
        if (h) {
            fn_80020B4C(lbl_80485858, 6);
            if (fn_80020B4C(name2, 0)) {
                fn_80020BF8(0);
            }
            r = fn_8009B35C(lv, h);
            lv->f124 = h;
        }
    }
    if (r == 0) {
        fn_8009B35C(lv, 0);
    }
    fn_801A9564(0x10000);
    fn_80114420();
    return lv;
}
