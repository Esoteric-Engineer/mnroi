// Range and state checks before an action starts, then GLOBALS fields 0x4D/0x4F pick a mode; docs/versus.md row 21.

struct Pair {
    int a;   // +0x0
    float f; // +0x4
};

struct Entry {
    int a;   // +0x0
    int key; // +0x4
    int c;   // +0x8
    int on;  // +0xC
};

extern "C" {
int fn_800419E8(int a);
int fn_80041ECC(void);
int fn_800479D0(int a);
int fn_800B0C1C(void *self);
int fn_800466D8(void *self, int *kind);
float fn_804358A4(void);
int fn_800B0C58(void *self);
int fn_800B14A0(void *self);
int fn_80085D3C(int actor);
int fn_80095608(int actor);
int fn_80085EEC(int actor);
int fn_800B13D8(void *self);
int fn_800444B0(void *self, int a, int b);
void fn_80043F60(void *self, int b);
void fn_80043EA4(void *obj, void *self, int a);
unsigned int fn_80433D70(void *record, int id, int slot);
void fn_80043190(void *obj, int mode);
extern float lbl_8066B7B8;
extern int lbl_8066B780;
extern void *lbl_8066B74C;
extern void *lbl_8066B75C;
extern void *lbl_8066C6C8; // the GLOBALS record
extern Pair lbl_8053F284[3][3];
extern Entry lbl_8053EE98[8];
}

extern "C" int fn_800439B0(void *self, int b)
{
    int kind;
    float dist;
    int x;
    int i;

    if (fn_800419E8(1) || fn_80041ECC() || !fn_800479D0(0) || !fn_800B0C1C(self))
        return 0;
    if (!fn_800466D8(self, &kind))
        return 0;
    dist = fn_804358A4();
    if (dist > lbl_8066B7B8 * lbl_8053F284[0][kind].f)
        return 0;
    if (fn_800B0C58(self)) {
        x = fn_800B14A0(self);
        if (fn_80085D3C(x) || fn_80095608(x)) {
            if (fn_80085EEC(x))
                return 0;
            else
                for (i = 0; i < lbl_8066B780; i++)
                    if (lbl_8053EE98[i].on != 0 && lbl_8053EE98[i].key == fn_800B13D8(self))
                        return 0;
        }
    }
    i = fn_800444B0(self, 0, 0x10);
    if (i) {
        fn_80043F60(self, b);
        fn_80043EA4(lbl_8066B74C, self, 1);
        if (kind) {
            x = 0;
            if (kind == 1)
                x = fn_80433D70(lbl_8066C6C8, 0x4F, 0);
            else
                x = fn_80433D70(lbl_8066C6C8, 0x4D, 0);
            if (x == 1 || x == 2)
                fn_80043190(lbl_8066B75C, x);
        }
    }
    return i;
}
