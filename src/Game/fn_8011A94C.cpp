// Versus: picks the music/mode word for a match start; docs/versus.md section 5, row 9b.

struct State {
    char pad[0x75C];
    int timerMode; // +0x75C
};

extern State lbl_80552110; // the game-state object G
extern void *lbl_8066BE10;
extern int lbl_8066BDF0;
extern char lbl_80568E30[];

extern "C" {
void fn_8011A824();
int fn_80432844(State *g);
int fn_80432870(State *g);
int Get594(State *g) __asm__("Get594__4Host");
void *fn_804317BC(State *g, int player);
int fn_80442774(void *slot);
int fn_80457368(void *self);
void fn_8011C008(void *obj, int a);
void fn_8045E8B0(void *self, int a, int b);

void fn_8011A94C(int player, int a, int b)
{
    if (!fn_80432844(&lbl_80552110) && !fn_80432870(&lbl_80552110)) {
        return;
    }
    if (a == 0 && lbl_80552110.timerMode != 1) {
        if (fn_80457368(lbl_8066BE10) == 0x16) {
            fn_8011C008(lbl_8066BE10, 0x22);
        }
        fn_8011A824();
        if (Get594(&lbl_80552110) == 1 && fn_80442774(fn_804317BC(&lbl_80552110, player)) == 0) {
            lbl_8066BDF0 = 0x1F;
        } else {
            lbl_8066BDF0 = 0x21;
        }
    } else if (fn_80457368(lbl_8066BE10) != 0x16) {
        if (fn_80457368(lbl_8066BE10) == 0x26) {
            fn_8011C008(lbl_8066BE10, 0x1C);
        } else {
            if (b != 0) {
                fn_8011C008(lbl_8066BE10, 0x20);
            } else {
                fn_8011C008(lbl_8066BE10, 0x1E);
            }
            fn_8045E8B0(lbl_80568E30, 0x22, 0xED8);
        }
    }
}
}
