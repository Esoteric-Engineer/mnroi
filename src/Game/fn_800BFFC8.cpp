// Per-frame match-time bookkeeping while a versus role index is set.

struct State {
    char pad[0x760];
    int phase;  // +0x760
    char pad764[0x4];
    int unk768; // +0x768
};

extern State lbl_80552110; // the game-state object G
extern char lbl_80593BE8[];

inline int sn_return_decl(int a) { return a; }

extern "C" {
int fn_80432844(State *g);
int fn_80432870(State *g);
int fn_800CD7D4(void *self);
unsigned int fn_800CC498(void *self);
void fn_80092550(State *g, int unused);
int fn_8042F024(void *x);

void fn_800BFFC8(register void *self)
{
    if (fn_80432844(&lbl_80552110) || fn_80432870(&lbl_80552110)) {
        if (fn_800CD7D4(self) != 0 || fn_800CC498(self) > 2000) {
            fn_80092550(&lbl_80552110, 0);
        } else if (lbl_80552110.phase != 0xD) {
            lbl_80552110.unk768 = lbl_80552110.unk768 + fn_8042F024(lbl_80593BE8);
        }
    }
}
}
