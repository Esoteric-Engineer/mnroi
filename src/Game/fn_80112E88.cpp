// Calls fn_8010E1F4 while no versus role index is set (docs/versus.md section 5, row 25).

struct State {
    char pad[0x75C];
};

extern State lbl_80552110; // the game-state object G

extern "C" {
void fn_8010E1F4();
int fn_80432844(State *g);
int fn_80432870(State *g);

void fn_80112E88(int a)
{
    if (!fn_80432844(&lbl_80552110) && !fn_80432870(&lbl_80552110)) {
        fn_8010E1F4();
    }
}
}
