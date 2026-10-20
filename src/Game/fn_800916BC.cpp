// G method: resets the match counters, picks the phase by role index, and spawns each slot's record; also looks up the script classes cRingOut and cCameraEvent.

class GameState
{
public:
    char pad0[0x590];
    unsigned int slotCount; // +0x590
    char pad594[0x1CC];
    int phase;              // +0x760
    char pad764[0x4];
    int unk768;             // +0x768
    char pad76C[0x10];
    int unk77C;             // +0x77C
    int unk780;             // +0x780
    int unk784;             // +0x784
    int unk788;             // +0x788
};

extern void *lbl_8066D650;
extern void *lbl_8066D654;
extern int lbl_8066B92C;
extern char lbl_8048A334[]; // "cRingOut"
extern char lbl_8048A340[]; // "cCameraEvent"
extern char lbl_8057E430[];
extern char lbl_80572230[];

inline int sn_return_decl(int a) { return a; }

extern "C" {
int fn_80432844(GameState *g);
int fn_80432870(GameState *g);
void fn_80133658();
void fn_8013367C();
void fn_80095304(GameState *g);
void fn_80114010();
void fn_80443C24(void *slot, int index);
void fn_80096268(void *slot, int a, int b);
void *fn_800789DC(const char *name, int a);
int fn_80430910(void *x);
void fn_80428EEC(void *x, int v);

void fn_800916BC(register GameState *self, int a, int unused, int b)
{
    unsigned int i;
    void *slot;

    self->unk780 = 0;
    self->unk77C = 0;
    self->unk768 = 0;
    self->unk788 = 0;
    self->unk784 = 0;
    if (fn_80432844(self) != 0 || fn_80432870(self) != 0) {
        fn_80133658();
    } else {
        fn_8013367C();
    }
    if (fn_80432844(self) != 0 || fn_80432870(self) != 0) {
        self->phase = 0;
        fn_80095304(self);
    } else {
        self->phase = 0xE;
    }
    for (i = 0; i < self->slotCount; i++) {
        slot = (char *)self + 0x10 + i * 0xB0;
        if (i == self->slotCount - 1) {
            fn_80114010();
        }
        if (slot != 0) {
            fn_80443C24(slot, i);
            fn_80096268(slot, a, b);
        }
    }
    lbl_8066D650 = fn_800789DC(lbl_8048A334, 1);
    lbl_8066D654 = fn_800789DC(lbl_8048A340, 1);
    lbl_8066B92C = fn_80430910(lbl_8057E430);
    fn_80428EEC(lbl_80572230, 0);
}
}
