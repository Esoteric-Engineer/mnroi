// GameFlow::OnPadRemoved (the method behind OnPadRemoved__FUs): queues the player whose pad was pulled.
// A .c unit: the file is pair-less C++, so `this` is a register first parameter.

typedef struct GameFlow
{
    char unk0[4];
    int unk4;                  // +0x4
    int unk8;                  // +0x8
    char unkC[4];
    int unk10;                 // +0x10
    int unk14;                 // +0x14
    char unk18[0x26C];
    int numUnplugged;          // +0x284
    int unplugged[2];          // +0x288
} GameFlow;

extern char lbl_80593BE8[]; // the globals object of Game/fn_80443908.cpp
extern char lbl_80552110[]; // the game-state object G
extern char lbl_8052F060[]; // the level/world object
extern void *lbl_8066BE10;

extern int fn_804329E0(char *level);
extern int fn_804427FC(char *g);
extern char *fn_804427D0(char *g);
extern int fn_80442774(char *slot);
extern int fn_80442624(char *slot);
extern unsigned int fn_8043B31C(char *slot);
extern int fn_80094A9C(char *g);
extern int fn_80126DF0(void);
extern void fn_8010226C(int port);
extern int fn_8012D63C(int port);
extern void fn_801AA368(void);
extern void fn_801280F4(void);
extern void fn_801AF754(char *globals);
extern void fn_80112B2C(int a);
extern void fn_8011C284(void *obj, int a);
extern int fn_800B4FC0(GameFlow *flow);

void fn_800B4AB8(register GameFlow *this, unsigned short port)
{
    int found = 0;
    int flag = 1;
    int player = -1;

    if (fn_804329E0(lbl_8052F060)) {
        if (fn_804427FC(lbl_80552110)) {
            do {
                if (!fn_80442774(fn_804427D0(lbl_80552110)) &&
                    fn_80442624(fn_804427D0(lbl_80552110)) == port) {
                    player = fn_8043B31C(fn_804427D0(lbl_80552110));
                    found = 1;
                    break;
                }
            } while (fn_80094A9C(lbl_80552110));
        }
    } else {
        if (fn_80126DF0()) {
            fn_8010226C(port);
        }
        player = fn_8012D63C(port);
        if (player >= 0) {
            found = 1;
        }
    }

    if (found == 0) {
        return;
    }
    fn_801AA368();
    fn_801280F4();
    if (player != this->unplugged[0] && player != this->unplugged[1]) {
        register int n;
        this->unplugged[n = this->numUnplugged++] = player;
        this->unk4 = 1;
        if (fn_800B4FC0(this) == 1 && flag) {
            this->unk8 = 1;
            fn_801AF754(lbl_80593BE8);
            if (fn_804329E0(lbl_8052F060) && this->unk14 == 0) {
                fn_80112B2C(1);
                fn_8011C284(lbl_8066BE10, 1);
            }
        }
    }
}
