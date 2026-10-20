// Versus: picks the music/mode word lbl_8066BDF0 for a timed match (G+0x75C == 1); docs/versus.md section 5, row 9b.

struct State {
    char pad[0x75C];
    int timerMode; // +0x75C
};

extern State lbl_80552110; // the game-state object G
extern int lbl_8066BDF0;

extern "C" {
void fn_8011A824();
int Get594(State *g) __asm__("Get594__4Host");
void *fn_804317BC(State *g, int player);
int fn_80442774(void *slot);

void fn_8011AB34(int player)
{
    if (lbl_80552110.timerMode == 1) {
        fn_8011A824();
        if (Get594(&lbl_80552110) == 1 && fn_80442774(fn_804317BC(&lbl_80552110, player)) != 0) {
            lbl_8066BDF0 = 0x1F;
        } else {
            lbl_8066BDF0 = 0x21;
        }
    }
}
}
