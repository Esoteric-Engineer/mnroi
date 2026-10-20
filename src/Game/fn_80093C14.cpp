// Hands the match over to player `side`: clears flag 2 on its actor, sets it on the other's, and plays PLAYER fields 170+side / 192+side.

class Slot
{
public:
    char pad0[0x30];
    unsigned flags; // +0x30
};

class GameState
{
public:
    char pad0[0x760];
    int phase;      // +0x760
    char pad1[0x38];
    int tblA[2];    // +0x79C
    char pad2[0xC];
    int tblB[2];    // +0x7B0
};

extern "C" Slot *fn_80443D44(GameState *g, int player);
extern "C" void fn_800528EC();
extern "C" int fn_800ACD20(Slot *actor, int id);
extern "C" void fn_800578E4(int a, int b, int c, Slot *d, int e, int f, int g);

extern "C" void fn_80093C14(register GameState *self, unsigned char side)
{
    Slot *actor = fn_80443D44(self, side);
    fn_80443D44(self, side)->flags &= ~2;
    fn_80443D44(self, 1 - side)->flags |= 2;
    if (actor) {
        fn_800528EC();
        fn_800578E4(fn_800ACD20(actor, self->tblA[side] + 0xAA), 0, 0, actor, self->tblB[side], 0, 0x3E7);
    }
    self->phase = side + 2;
}
