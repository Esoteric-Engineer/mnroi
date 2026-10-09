// FrameCtx level-load "when" dispatch (guessed): "NOW" applies at once, else queues; see docs/versus.md section 5, row 9d.

inline int sn_return_decl(int a) { return a; }

extern "C" {
int strcmp(const char *a, const char *b);
void fn_8002D994(void *ctx);
void fn_80433198(void *owner, int a, int b);
extern const char lbl_80485888[]; // "NOW"
extern char lbl_8057229C[];
}

struct State {
    char pad0[0x760];
    int phase; // +0x760
};
extern State lbl_80552110;

extern "C" int fn_8002D90C(register void *self, const char *when)
{
    if (strcmp(when, lbl_80485888) == 0) {
        fn_8002D994(self);
    } else {
        fn_80433198(lbl_8057229C, 0, 0xBB8);
    }
    lbl_80552110.phase = 0xF;
    return 1;
}
