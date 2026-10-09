// First function of the file at 0x8002B9F0 (docs/versus.md section 5, row 9d): per-frame service calls, then a check on G.

inline int sn_return_decl(int a) { return a; }

extern "C" {
void fn_801336F0();
void fn_800924BC(void *g);
int fn_80432A0C(void *p);
void fn_8002F884(void *p, int v);
int fn_800936D0(void *g);
int fn_80093410(void *g);
void fn_80432DF8(void *p);
}

extern char lbl_80552110[];
extern char lbl_8052F060[];
extern char lbl_80572354[];
extern char lbl_8057237C[];

extern "C" void fn_8002B9F0(int arg)
{
    fn_801336F0();
    fn_800924BC(lbl_80552110);
    if (fn_80432A0C(lbl_8052F060) == 0x109) {
        fn_8002F884(lbl_8052F060, 3);
    }
    if (arg != 0) {
        if (fn_800936D0(lbl_80552110) == 0) {
            fn_80432DF8(lbl_80572354);
        }
    } else {
        if (fn_80093410(lbl_80552110) == 0) {
            fn_80432DF8(lbl_8057237C);
        }
    }
}
