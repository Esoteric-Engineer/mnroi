// FrameCtx startup (guessed): subsystem init, the four ini files, then the per-level load hooks; see docs/versus.md section 5, row 9d.

void fn_8023EC38(void);
void fn_8023D994(int v);
void fn_8023DBE4(void);
void fn_801ABA48(void);
void fn_801A9564(int v);
int fn_801AD68C(void);
void fn_801AD6F0(int v);
void fn_801A7BF8(void);
void fn_801B6D70(void);
int fn_8002A100(void);
int fn_8019FCFC(int v);
void fn_801A7DF0(int v);
void fn_80432BC4(void);
void fn_80432C3C(void);
void fn_80432B4C(void);
int fn_80427400(void);
int fn_8002EF98(void);
void fn_8012ED58(int p, int lang);
void *fn_8042D4CC(void);
void fn_80015960(void *p, int a, int b);
void fn_80101A78(void);
void fn_800B5594(void *flow, int v);
void fn_80219CD8(void);
void *fn_801B7A48(void);
void fn_801B7AA0(void *ini, int a, int b, int c);
void fn_801B8530(void *ini, const char *name, int v);
void fn_8002EEC0(void);
void fn_801A9974(void *p);
void fn_800FC1F8(void);
void fn_800FC320(void);
void fn_8002A210(void);
void fn_800288EC(void);
int fn_8042F298(void *c);
int fn_80430CD8(void *flags, int bit);
void fn_80198D14(const char *s, int v);
void fn_80232EBC(const char *s, int v);
void fn_801A1EEC(const char *s, int v);
void fn_8023597C(const char *s, int v);
void fn_800909A0(const char *s, int v);
void fn_8019EBF8(const char *s, int v);
void fn_80233218(const char *s, int v);
void fn_80061678(void);
void fn_800B94E8(void);
void fn_80033860(void);
void fn_801B2620(void);
void fn_801AF6C4(void *p);
void fn_8039E22C(void *p);
void fn_80118FF8(void);
int fn_8011CA74(void);
int fn_80122228(void);

extern char lbl_8066D568[8];
extern void fn_80028B08__6Config(void *self);
extern int lbl_8066D578;
extern char lbl_80552920[];
extern char lbl_80589260[];
extern char lbl_80593BE8[];
extern char lbl_8064AA80[];
extern const char lbl_80485850[]; // "global"
extern int lbl_8066C660;
extern int lbl_8066C600;
extern int lbl_8066B668;
extern int lbl_8066B664;
extern int lbl_8066B6C4;
extern int lbl_8066B6C8;
extern int lbl_8066B6CC;

int fn_8002F070(register void *self)
{
    register int p;

    lbl_8066C660 = 0;
    fn_8023EC38();
    fn_8023D994(100);
    fn_8023DBE4();
    fn_801ABA48();
    lbl_8066C600 = 1;
    fn_801A9564(0x200000);
    fn_801AD6F0(fn_801AD68C());
    fn_80028B08__6Config(lbl_8066D568);
    fn_801A7BF8();
    fn_801B6D70();
    if (fn_8002A100() == 0) {
        return 0;
    }
    if (fn_8019FCFC(0) == 0) {
    }
    fn_801A7DF0(0);
    fn_80432BC4();
    fn_80432C3C();
    fn_80432B4C();
    p = fn_80427400();
    fn_8012ED58(p, fn_8002EF98());
    fn_80015960(fn_8042D4CC(), 2, 0);
    fn_80101A78();
    fn_800B5594(lbl_80552920, lbl_8066B668 == 0);
    fn_80219CD8();
    fn_801B7AA0(fn_801B7A48(), 200, 20000, 2);
    fn_801B8530(fn_801B7A48(), "ini/common.ini", 0);
    fn_801B8530(fn_801B7A48(), "ini/sku.ini", 0);
    fn_801B8530(fn_801B7A48(), "ini/locale.ini", 0);
    fn_801B8530(fn_801B7A48(), "ini/user.ini", 0);
    fn_8002EEC0();
    fn_801A9974(lbl_80589260);
    fn_800FC1F8();
    fn_800FC320();
    fn_8002A210();
    fn_800288EC();
    if (fn_8042F298(lbl_8066D568) != 0) {
        if (fn_80430CD8(&lbl_8066D578, 4) != 0) {
            fn_80198D14(lbl_80485850, 0);
        }
        if (fn_80430CD8(&lbl_8066D578, 1) != 0) {
            fn_80232EBC(lbl_80485850, 0);
        }
        if (fn_80430CD8(&lbl_8066D578, 2) != 0) {
            fn_801A1EEC(lbl_80485850, 0);
        }
        if (fn_80430CD8(&lbl_8066D578, 8) != 0) {
            fn_8023597C(lbl_80485850, 0);
        }
        if (fn_80430CD8(&lbl_8066D578, 0x10) != 0) {
            fn_800909A0(lbl_80485850, 0);
        }
    } else if (lbl_8066B664 != 0) {
        fn_8019EBF8(lbl_80485850, 0);
        fn_80233218(lbl_80485850, 0);
    }
    fn_80061678();
    fn_800B94E8();
    fn_80033860();
    fn_801B2620();
    fn_801AF6C4(lbl_80593BE8);
    fn_8039E22C(lbl_8064AA80);
    fn_801A9564(0);
    lbl_8066C600 = 0;
    fn_80118FF8();
    lbl_8066B6C4 = fn_80427400();
    lbl_8066B6C8 = fn_8011CA74();
    lbl_8066B6CC = fn_80122228();
    return 1;
}
