// GameFlow::OnPadRemoved (the method behind OnPadRemoved__FUs): queues the player whose pad was pulled.
// The file is pair-less C++; `this` is written as a register first parameter to keep the fn_ name.

struct GameFlow
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
};

extern char lbl_80593BE8[]; // the globals object of Game/fn_80443908.cpp
extern char lbl_80552110[]; // the game-state object G
extern char lbl_8052F060[]; // the level/world object
extern void *lbl_8066BE10;

extern "C" {
int fn_804329E0(char *level);
int fn_804427FC(char *g);
char *fn_804427D0(char *g);
int fn_80442774(char *slot);
int fn_80442624(char *slot);
unsigned int fn_8043B31C(char *slot);
int fn_80094A9C(char *g);
int fn_80126DF0(void);
void fn_8010226C(int port);
int fn_8012D63C(int port);
void fn_801AA368(void);
void fn_801280F4(void);
void fn_801AF754(char *globals);
void fn_80112B2C(int a);
void fn_8011C284(void *obj, int a);
int fn_800B4FC0(GameFlow *flow);
}

inline int sn_return_decl(int a) { return a; }

extern "C" void fn_800B4AB8(register GameFlow *self, unsigned short port)
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
    if (player != self->unplugged[0] && player != self->unplugged[1]) {
        self->unplugged[self->numUnplugged++] = player;
        self->unk4 = 1;
        if (fn_800B4FC0(self) == 1 && flag) {
            self->unk8 = 1;
            fn_801AF754(lbl_80593BE8);
            if (fn_804329E0(lbl_8052F060) && self->unk14 == 0) {
                fn_80112B2C(1);
                fn_8011C284(lbl_8066BE10, 1);
            }
        }
    }
}
