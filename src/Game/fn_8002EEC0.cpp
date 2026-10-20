// Reads the LEVEL and NO_CUT_SCENES options from the ini; see docs/versus.md section 5, row 9d.

struct State {
    char pad0[0x5BB];
    char levelEnd; // +0x5BB
    char pad1[0x60];
    int levelSet;  // +0x61C
};

extern State lbl_80552110;
extern char lbl_805526AC[];
extern int lbl_8066B640;

extern "C" {
void *fn_801B7A48();
int fn_801B7DC4(void *ini, const char *key);
const char *fn_801B7E24(void *ini, const char *key);
int fn_801B7E9C(void *ini, const char *key);
char *strncpy(char *dst, const char *src, int n);
}

extern "C" void fn_8002EEC0()
{
    if (fn_801B7DC4(fn_801B7A48(), "LEVEL")) {
        strncpy(lbl_805526AC, fn_801B7E24(fn_801B7A48(), "LEVEL"), 0x20);
        lbl_80552110.levelEnd = 0;
        lbl_80552110.levelSet = 1;
    }
    lbl_8066B640 = fn_801B7E9C(fn_801B7A48(), "NO_CUT_SCENES") == 1 ? 0 : 1;
}
