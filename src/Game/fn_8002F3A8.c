// FrameCtx per-load setup (guessed): re-inits the renderer and loaders; see docs/versus.md section 5, row 9d.

void fn_801A9564(int v);
void fn_8010CDA0(void);
void fn_8008A7EC(void);
void fn_8007C8B0(void);
void fn_80048518(void);
void fn_80023C0C(void);
int fn_8042F298(void *c);
void fn_80090A68(const char *s, int v);
void fn_801A2108(const char *s, int v);
void fn_80058C2C(void);
void fn_80017FFC(void);
void fn_801B26DC(void);
void fn_80033A6C(void);
int fn_8002892C(void);
void fn_80126F0C(int a, int b);
void fn_800180D0(void);
void fn_804329B8(register void *self, register int v);

extern char lbl_8066D568[8];
extern const char lbl_80485850[]; // "global"
extern int lbl_8066C660;
extern int lbl_8066C600;
extern int lbl_8066B664;

int fn_8002F3A8(register void *self)
{
    lbl_8066C600 = 1;
    fn_801A9564(0x200000);
    fn_8010CDA0();
    fn_8008A7EC();
    fn_8007C8B0();
    fn_80048518();
    fn_80023C0C();
    if (fn_8042F298(lbl_8066D568) == 0 && lbl_8066B664 != 0) {
        fn_80090A68(lbl_80485850, 1);
        fn_801A2108(lbl_80485850, 0);
    }
    fn_80058C2C();
    lbl_8066C660 = 1;
    fn_80017FFC();
    lbl_8066C660 = 0;
    fn_801B26DC();
    fn_80033A6C();
    if (fn_8002892C() == 0) {
        return 0;
    }
    fn_801A9564(0);
    lbl_8066C600 = 0;
    fn_80126F0C(0, 0);
    fn_800180D0();
    fn_804329B8(self, 1);
    return 1;
}
