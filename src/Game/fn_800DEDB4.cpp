// Entity method: tries to start the attack named by the target's PLAYER string 0xCE + fn_8009AC68(target); flags 0x2000 in a versus match, 0x80 / 0x100 at random (a third each). docs/versus.md section 5, row 25.

class Global
{
public:
    char pad0[0x28];
    int unk28; // +0x28
};

struct State {
    char pad[0x75C];
};

class ActorBase
{
public:
    int pad;
    char *GetString(int id) __asm__("fn_800ACD20");
    int IsAlive() __asm__("fn_800B13D8");
};

class ActorDerived : public ActorBase
{
public:
    int unk4;
};

extern State lbl_80552110; // the game-state object G
extern Global *lbl_8066D654;

extern "C" {
int fn_80432844(State *g);
int fn_80432870(State *g);
int fn_800B0C58(void *actor);
void fn_800924BC(State *g);
ActorDerived *Entity_GetActor(void *self);
int fn_8009AC68(void *actor);
unsigned int strlen(const char *s);
int fn_80171F8C();
int fn_800578E4(char *a, Global *b, void *c, void *d, int e, int f, int g);
void fn_80086410(void *actor);
void fn_8007EBE4(void *a, void *b);
}

extern "C" int fn_800DEDB4(register void *self, void *target)
{
    int flags = 0x100670;
    float roll;

    if (fn_80432844(&lbl_80552110) != 0 || fn_80432870(&lbl_80552110) != 0) {
        flags |= 0x2000;
    }
    if (target == 0 || fn_800B0C58(target) == 0) {
        return 0;
    }
    fn_800924BC(&lbl_80552110);
    if (Entity_GetActor(self)->GetString(fn_8009AC68(target) + 0xCE) == 0 || strlen(Entity_GetActor(self)->GetString(fn_8009AC68(target) + 0xCE)) == 0) {
        return 0;
    }
    roll = (float)fn_80171F8C() * 4.656612873077393e-10f;
    if (roll < 0.33f) {
        flags |= 0x80;
    } else if (roll < 0.66f) {
        flags |= 0x100;
    }
    lbl_8066D654->unk28 = Entity_GetActor(self)->IsAlive();
    if (fn_800578E4(Entity_GetActor(self)->GetString(fn_8009AC68(target) + 0xCE), lbl_8066D654, Entity_GetActor(self), target, flags, 0, 0x3E7) == 0) {
        return 0;
    }
    fn_80086410(target);
    fn_80086410(Entity_GetActor(self));
    fn_8007EBE4(target, Entity_GetActor(self));
    return 1;
}
