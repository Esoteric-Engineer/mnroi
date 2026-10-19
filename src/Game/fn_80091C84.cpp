// G method: steps the match phase G+0x760 until a phase finishes for this frame; versus branches in docs/versus.md section 4.3.

class Slot
{
public:
    char pad0[0x30];
    unsigned flags; // +0x30
};

class GameState
{
public:
    char pad0[0x758];
    int f758;          // +0x758
    char pad75C[0x4];
    unsigned phase;    // +0x760
    char pad764[0x4];
    int f768;          // +0x768
    int f76C;          // +0x76C
    char pad770[0xC];
    int f77C;          // +0x77C
    char pad780[0x8];
    int timer;         // +0x788
};

extern GameState lbl_80552110; // the game-state object G
extern char lbl_80552920[];
extern char lbl_80593BE8[];
extern char lbl_8052F060[];
extern char lbl_8048A350[]; // "NOW"
extern char lbl_80572254[];
extern char lbl_8057209C[];
extern char lbl_8057237C[];
extern char lbl_80572354[];
extern char lbl_80571EA4[];
extern char lbl_80571F10[];
extern char lbl_8057E430[];
extern unsigned int lbl_8066B600;
extern int lbl_8066BE10;

extern "C" {
Slot *fn_80443D44(GameState *g, int player);
int fn_80432844(GameState *g);
int fn_80432870(GameState *g);
int fn_8009404C(GameState *g);
void fn_80092550(GameState *g, int x);
void fn_80092DA0(GameState *g);
void fn_80092B7C(GameState *g);
void fn_800939C4(GameState *g, int x);
void fn_80093C14(GameState *g, unsigned char side);
void fn_80092A84(GameState *g);
void fn_80093250(GameState *g);
void *fn_804317BC(GameState *g, int i);
void fn_8009717C(void *slot);
void fn_8011C008(int x, int cue);
int fn_8005287C(void);
void fn_800528EC(void);
void fn_80428EEC(void *x, int on);
void fn_80432D00(void *x, int on);
void fn_80432DF8(void *x);
void fn_8043323C(void *x, int y);
void fn_80431480(void *x, int y);
void fn_80132B88(void);
void fn_80132CDC(void);
void fn_8013367C(void);
void fn_80133658(void);
void fn_8007FF3C(void);
int fn_8042F024(void *clock);
void fn_8002D90C(void *level, char *name);

void fn_80091C84(register GameState *self)
{
    int done = 0;

    while (!done) {
        switch (self->phase) {
        case 0:
            if (lbl_8066B600 > 3) {
                fn_8011C008(lbl_8066BE10, 0x19);
                fn_80092DA0(self);
            } else {
                if (self->f76C == 0) {
                    fn_80092B7C(self);
                    fn_800939C4(self, 0);
                    fn_800939C4(self, 1);
                    self->f76C = 1;
                }
                fn_8011C008(lbl_8066BE10, 0x18);
                done = 1;
            }
            break;
        case 14:
            if (lbl_8066B600 <= 0x27)
                return;
            if (!fn_8005287C())
                return;
            fn_80428EEC(lbl_80572254, 1);
            lbl_80552110.phase = 4;
            fn_80132B88();
            fn_80432D00(lbl_80552920, 1);
            break;
        case 1:
            if (!fn_8005287C())
                return;
            fn_8011C008(lbl_8066BE10, 0x1a);
            fn_80093C14(self, 0);
            break;
        case 7:
            if (!fn_8005287C())
                return;
            if (self->f77C == 0) {
                fn_80428EEC(lbl_8057209C, 1);
                self->f77C = 1;
            }
            done = 1;
            break;
        case 16:
            fn_80443D44(&lbl_80552110, 0)->flags |= 2;
            fn_80443D44(&lbl_80552110, 1)->flags |= 2;
            fn_80431480(lbl_8057E430, 0);
            if (!fn_8005287C())
                return;
            fn_800528EC();
            self->phase = 7;
            done = 1;
            break;
        case 11:
            if (!fn_8005287C())
                return;
            if (self->f77C == 0) {
                fn_80432D00(lbl_80552920, 0);
                fn_80432DF8(lbl_8057237C);
                self->f77C = 1;
            }
            done = 1;
            break;
        case 12:
            if (!fn_8005287C())
                return;
            if (self->f77C == 0) {
                fn_80432D00(lbl_80552920, 0);
                fn_80432DF8(lbl_80572354);
                self->f77C = 1;
            }
            done = 1;
            break;
        case 2:
            if (!fn_8005287C())
                return;
            fn_80432D00(lbl_80552920, 1);
            fn_8011C008(lbl_8066BE10, 0x1b);
            fn_80093C14(self, 1);
            break;
        case 3:
            if (!fn_8005287C())
                return;
            fn_8043323C(lbl_80571EA4, 0);
            fn_8011C008(lbl_8066BE10, 0x1c);
            fn_80428EEC(lbl_80571F10, 1);
            self->phase = 9;
            self->timer = 2000;
            fn_800528EC();
            fn_80092A84(self);
            fn_80443D44(self, 1)->flags &= ~2;
            fn_80443D44(self, 0)->flags &= ~2;
            fn_80443D44(self, 1)->flags &= ~0x200;
            fn_80443D44(self, 0)->flags &= ~0x200;
            if (fn_80432844(self) || fn_80432870(self))
                fn_8007FF3C();
            break;
        case 9:
            self->timer -= fn_8042F024(lbl_80593BE8);
            self->f768 += fn_8042F024(lbl_80593BE8);
            if (self->timer > 0)
                return;
            self->phase = 4;
            if (fn_80432870(self)) {
                fn_80132CDC();
                fn_8013367C();
                fn_80132B88();
            }
            fn_80443D44(self, 1)->flags &= ~2;
            fn_80443D44(self, 0)->flags &= ~2;
            fn_80443D44(self, 1)->flags &= ~0x200;
            fn_80443D44(self, 0)->flags &= ~0x200;
            break;
        case 5:
            if (!fn_8005287C())
                return;
            fn_80093250(self);
            break;
        case 6:
            if (!fn_8005287C())
                return;
            if (fn_8009404C(self))
                break;
            if (fn_80432844(self) || fn_80432870(self)) {
                fn_80092550(self, 0);
                self->phase = 4;
            } else {
                fn_8002D90C(lbl_8052F060, lbl_8048A350);
                return;
            }
            break;
        case 13:
            self->timer -= fn_8042F024(lbl_80593BE8);
            self->f768 += fn_8042F024(lbl_80593BE8);
            if (self->timer > 0)
                return;
            fn_8009717C(fn_804317BC(self, self->f758));
            break;
        case 8:
            self->timer -= fn_8042F024(lbl_80593BE8);
            self->f768 += fn_8042F024(lbl_80593BE8);
            if (self->timer > 0)
                return;
            fn_80133658();
            lbl_80552110.phase = 7;
            break;
        case 4:
            if (fn_80432844(self) || fn_80432870(self))
                fn_8009404C(self);
            done = 1;
            break;
        default:
            done = 1;
            break;
        }
    }
}
}
