// Slot method: ends a round for this slot's player (flag 0x10 on the slot, phase 5, effect 0xAD + slot+0x6C). docs/versus.md section 5, row 25.

class Actor
{
public:
    char pad0[0x30];
    unsigned flags; // +0x30
};

class Slot
{
public:
    char pad0[0x34];
    unsigned flags; // +0x34
    char pad38[0x34];
    int unk6C; // +0x6C
    int unk70; // +0x70
};

class GameState
{
public:
    char pad0[0x760];
    int phase;      // +0x760
    char pad764[0x54];
    Slot *unk7B8;   // +0x7B8
};

class Global
{
public:
    char pad0[0x28];
    int unk28; // +0x28
};

extern GameState lbl_80552110;
extern Global *lbl_8066D654;
extern char lbl_80572030[];

inline int sn_return_decl(int a) { return a; }

extern "C" {
void fn_80216E48(int a);
void fn_80092EA8(GameState *g);
void fn_800528EC();
int fn_8043B31C(Slot *slot);
Actor *fn_8042FF2C(Slot *slot);
int fn_800ACD20(Actor *actor, int id);
void fn_800578E4(int a, int b, int c, Actor *d, int e, int f, int g);
int fn_80432844(GameState *g);
int fn_80432870(GameState *g);
Actor *fn_80443D44(GameState *g, int player);
void fn_80080010();
void fn_80133658();
void fn_80428EEC(void *x, int v);

void fn_8009717C(register Slot *self)
{
    register Actor *actor;
    register int effect;
    Actor *other;

    fn_80216E48(0);
    fn_80092EA8(&lbl_80552110);
    lbl_80552110.unk7B8 = self;
    fn_800528EC();
    lbl_8066D654->unk28 = fn_8043B31C(self);
    actor = fn_8042FF2C(self);
    effect = fn_800ACD20(actor, self->unk6C + 0xAD);
    fn_800578E4(effect, 0, 0, fn_8042FF2C(self), self->unk70, 0, 0x3E7);
    if (fn_80432844(&lbl_80552110) != 0 || fn_80432870(&lbl_80552110) != 0) {
        other = fn_80443D44(&lbl_80552110, 1 - fn_8043B31C(self));
        other->flags |= 2;
        fn_80080010();
    }
    self->flags |= 0x10;
    fn_80133658();
    lbl_80552110.phase = 5;
    fn_80428EEC(lbl_80572030, fn_8043B31C(self));
}
}
