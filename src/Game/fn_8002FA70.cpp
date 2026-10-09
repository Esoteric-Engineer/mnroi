// FrameCtx attract-movie check (guessed): in state 5, a successful movie-name check sets state 3; see docs/versus.md section 5, row 9d.

struct FrameCtx;

extern "C" int fn_80432D74(void *p);
extern "C" int fn_8002E570(FrameCtx *self, const char *s);

extern char lbl_80552920[];
extern int lbl_8066B6C0;

extern "C" int fn_8002FA70(register FrameCtx *self)
{
    if (fn_80432D74(lbl_80552920) == 0) {
        return 0;
    }
    if (lbl_8066B6C0 != 5) {
        return 0;
    }
    if (fn_8002E570(self, "Attract_Mode.bik") != 0) {
        lbl_8066B6C0 = 3;
    }
    return 1;
}
