// Per-frame tick of an entity class: runs its current state method, a pointer to member at +0x4EC, or else the state table entry for its type (docs/versus.md section 5, row 25).

class Entity;
typedef void (Entity::*State)();

struct StateEntry {
    State run; // +0x0
    char pad8[0x4C];
};

class Entity {
public:
    char pad0[0x8];
    unsigned char type; // +0x8
    char pad9[0x4E3];
    State state;        // +0x4EC
    virtual void v0();
};

struct Globals {
    char pad[0x75C];
};

extern Globals lbl_80552110; // the game-state object G
extern StateEntry lbl_8066A160[];

inline int sn_return_decl(int a) { return a; }

extern "C" {
int fn_800BA6D0(Entity *self);
int fn_80041AE0();
void *fn_800CE5F4(Entity *self);
void fn_8003CEBC(void *x);
int fn_80446C04(Globals *g);
int fn_80432844(Globals *g);
int fn_80432870(Globals *g);
int fn_80095B24(Globals *g);
void fn_800C7AD4(Entity *self);

void fn_800BF7FC(register Entity *self)
{
    if (fn_800BA6D0(self) != 0) {
        if (fn_80041AE0() != 0) {
            fn_8003CEBC(fn_800CE5F4(self));
        }
        return;
    }
    if (fn_80041AE0() != 0) {
        return;
    }
    if (fn_80446C04(&lbl_80552110) != 0 || fn_80432844(&lbl_80552110) != 0 || fn_80432870(&lbl_80552110) != 0) {
        if (fn_80095B24(&lbl_80552110) == 0) {
            fn_800C7AD4(self);
            return;
        }
    }
    if (self->state != 0) {
        (self->*(self->state))();
    } else if (lbl_8066A160[self->type].run != 0) {
        (self->*(lbl_8066A160[self->type].run))();
    }
}
}
