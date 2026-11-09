// Constraint per-frame update and end point tracking.

#define ABS(x) ((x) < 0.0f ? -(x) : (x))

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

struct Actor {
    char pad0[0x198];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(Vector *out, int z); // +0x30
};

struct Effect {
    char pad0[0x20];
    Vector pos;      // +0x20
    char pad30[0x18];
    unsigned char marker;      // +0x48
    unsigned char marker_id;   // +0x49
    char pad4A[0x7E];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10();
    virtual void s11(); // +0x60
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41();
    virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
    virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53();
    virtual void s54(); virtual void s55(); virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
    virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63(); virtual void s64(); virtual void s65();
    virtual void s66(); virtual void s67(); virtual void s68(); virtual void s69(); virtual void s70(); virtual void s71();
    virtual void s72();
    virtual void s73(void *list, float dt); // +0x250
    virtual int s74(void *list);            // +0x258
};

struct Constraint : Effect {
    char padD0[0x40];
    Vector end;      // +0x110
    char pad120[0x38];
    float f158;      // +0x158
    char pad15C[0x8];
    float length;    // +0x164
    char pad168[0x14];
    unsigned int flags; // +0x17C
    char pad180[0x4];
    int f184;        // +0x184
    char pad188[0x4];
    unsigned char f18C; // +0x18C
    char pad18D[0xC3];
    float rate;      // +0x250
    char pad254[0x15];
    unsigned char endmarker;    // +0x269
    unsigned char endmarker_id; // +0x26A
    unsigned char style;        // +0x26B
    char pad26C[0x24];
    Vector f290;     // +0x290
    int f2A0;        // +0x2A0
    int f2A4;        // +0x2A4
    int target;      // +0x2A8
};

extern char lbl_80593BE8[];
extern char lbl_8064E8A0[];

extern "C" {
int fn_803CCFD4(Constraint *self);
float fn_804310C0(Vector *a, Vector *b);
int fn_803CE040(Constraint *self);
float fn_80426A84(void *p);
Actor *fn_800ACFA8(int id);
int fn_800B0F0C(Actor *actor);
void *fn_800B1568(Actor *actor);
void *fn_8009AD80(void *player);
void *fn_800B1668(Actor *actor);
int fn_801A5104(void *model, unsigned char kind, unsigned short id, Vector *out, void *world);
int fn_8039D01C(Constraint *self);
void fn_8039C2E0(Constraint *self);
void fn_80394088(Constraint *self, float dt);
int fn_8039D708(Constraint *self);
int fn_8039D270(Constraint *self);
void fn_80393274(Constraint *self);
void fn_803ABF88(Constraint *self, float dt);
void fn_803AC0E0(Constraint *self, float dt);
void fn_803ABE98(Constraint *self);
int fn_803CD7F4(Constraint *self);
void fn_803AC5F8(Constraint *self, void *list);
int fn_803CE010(Constraint *self);
void fn_803BEC3C(Constraint *self, void *list, Vector *start, int a);
int fn_8039A230(Constraint *self, Vector *out, unsigned char kind, unsigned char id);
void fn_8042DC84(Vector *dst, Vector *src);
void fn_803BF1AC(Constraint *self, void *list, Vector *a, Vector *b);
int fn_8039CED4(Constraint *self);
float fn_80394C28(Constraint *self);
void fn_803AC7C4(Constraint *self, void *list);
void fn_803B5814(Constraint *self);
void fn_803B5968(Constraint *self, int a);
int fn_803BFE6C(Constraint *self, int a);
int fn_803C0EF0(Constraint *self, int a);
int fn_803C0AE8(Constraint *self, int a);
int fn_803C0158(Constraint *self, int a);

void fn_803BF77C(register Constraint *self)
{
    if (fn_803CCFD4(self)) {
        self->length = fn_804310C0(&self->pos, &self->end);
        self->length = ABS(self->length);
    } else if (fn_803CE040(self) && self->length != 0.0f) {
        self->length -= fn_80426A84(lbl_80593BE8) * self->rate;
        if (self->length < 0.0f)
            self->length = 0.0f;
    }
}

void fn_803BF874(register Constraint *self)
{
    if (self->target) {
        Actor *actor = fn_800ACFA8(self->target);
        if (actor) {
            self->flags |= 0x2000000;
            if (!fn_800B0F0C(actor) || !fn_8009AD80(fn_800B1568(actor)) || self->endmarker == 0xFF
                || !fn_801A5104(fn_8009AD80(fn_800B1568(actor)), self->endmarker, self->endmarker_id, &self->end, fn_800B1668(actor)))
                actor->s5(&self->end, 0);
        } else {
            self->target = 0;
        }
    }
}

void fn_803BF9D4(register Constraint *self)
{
    if (!fn_8039D01C(self))
        return;
    fn_8039C2E0(self);
    float dt = fn_80426A84(lbl_80593BE8);
    if (dt == 0.0f)
        return;
    fn_80394088(self, dt);
    if (fn_8039D708(self)) {
        self->s11();
        return;
    }
    fn_803BF874(self);
    if (!fn_8039D270(self))
        fn_80393274(self);
    fn_803BF77C(self);
    fn_803ABF88(self, dt);
    fn_803AC0E0(self, dt);
    fn_803ABE98(self);
    if (!fn_803CD7F4(self)) {
        fn_803AC5F8(self, lbl_8064E8A0);
        void *list = lbl_8064E8A0;
        if (!fn_803CCFD4(self))
            self->s73(list, dt);
        if (fn_803CE010(self) && !fn_803CCFD4(self)) {
            fn_803BEC3C(self, list, 0, self->f2A0);
        } else {
            Vector a;
            Vector b;
            if (!fn_8039A230(self, &a, self->marker, self->marker_id))
                fn_8042DC84(&a, &self->pos);
            if (fn_8039A230(self, &b, self->endmarker, self->endmarker_id))
                fn_803BF1AC(self, list, &a, &b);
            else
                fn_803BEC3C(self, list, &a, self->f2A0);
        }
    }
    self->f18C &= 0xFE;
}

void fn_803BFC88(register Constraint *self)
{
    if (!fn_8039CED4(self))
        return;
    if (self->f158 > 0.0f)
        return;
    if (fn_80394C28(self) == 0.0f)
        return;
    fn_8042DC84(&self->f290, &self->pos);
    fn_803AC7C4(self, lbl_8064E8A0);
    fn_803B5814(self);
    if (self->s74(lbl_8064E8A0))
        fn_803B5968(self, 0);
    fn_803B5814(self);
}

int fn_803BFD90(register Constraint *self, int a)
{
    self->f184 = 0;
    if (fn_803CCFD4(self))
        return fn_803BFE6C(self, a);
    switch (self->style) {
    case 5:
        return fn_803C0EF0(self, a);
        break;
    case 0:
        return fn_803C0AE8(self, a);
        break;
    }
    return fn_803C0158(self, a);
}
}
