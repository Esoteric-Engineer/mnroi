// Constraint start (slot 5), hand-over to the target actor (slot 32) and impulse along the chain (slot 22).

__asm__(".section .rodata\n\t.globl lbl_804BD0D0\nlbl_804BD0D0:\n\t.float 1\n\t.text");

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

struct Matrix {
    float m[16];
} __attribute__((aligned(8)));

struct Owner {
    char pad0[0x78];
    Matrix world; // +0x78
};

struct Effect {
    char pad0[0x20];
    Vector pos;      // +0x20
    char pad30[0x18];
    unsigned char marker;      // +0x48
    unsigned char marker_id;   // +0x49
    char pad4A[0x36];
    Owner *owner;    // +0x80
    char pad84[0x44];
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(Vector *pos, int z); // +0xE8
    virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40();
    virtual void s41(); virtual void s42();
    virtual void s43(int a); // +0x160
    virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
    virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
    virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59(); virtual void s60(); virtual void s61();
    virtual void s62(); virtual void s63(); virtual void s64(); virtual void s65(); virtual void s66();
    virtual void s67(); // +0x220
    virtual void s68(); virtual void s69(); virtual void s70(); virtual void s71(); virtual void s72(); virtual void s73();
    virtual void s74();
    virtual unsigned int s75(); // +0x260
};

struct Point {
    char pad0[0x24];
    float f24; // +0x24
};

struct Constraint : Effect {
    char padD0[0x40];
    Vector end;      // +0x110
    char pad120[0x44];
    float length;    // +0x164
    char pad168[0xC];
    int f174;        // +0x174
    char pad178[0x84];
    float f1FC;      // +0x1FC
    char pad200[0x69];
    unsigned char endmarker;    // +0x269
    unsigned char endmarker_id; // +0x26A
    char pad26B[0x25];
    Vector f290;     // +0x290
    int f2A0;        // +0x2A0
    int f2A4;        // +0x2A4
    int target;      // +0x2A8
};

extern "C" {
void fn_803AB27C(Constraint *self);
void fn_8042DC84(Vector *dst, Vector *src);
int fn_803CE0A0(Constraint *self);
int fn_803CE0D0(Constraint *self);
void fn_80428FA8(Vector *v, float x, float y, float z);
void fn_8042D7B0(Matrix *m);
int fn_8039A660(Constraint *self, Matrix *m, unsigned char kind, unsigned char id, int z);
void fn_80435754(Vector *v, Matrix *m);
void fn_80429090(Vector *out, Vector *a, Vector *b, float s);
void fn_80393698(Owner *owner, Constraint *self);
void *fn_800ACFA8(int id);
void fn_80393938(void *actor, Constraint *self, int a);
int fn_8039D148(Constraint *self);
void fn_8039D820(Constraint *self, int a);
Point *fn_803CEC54(Constraint *self, unsigned int i);
void fn_8042FE08(Point *p, Vector *v, float s);

void fn_803BE35C(register Constraint *self)
{
    self->f1FC = -1.0f;
    self->target = 0;
    fn_803AB27C(self);
    fn_8042DC84(&self->f290, &self->pos);
    fn_8042DC84(&self->end, &self->pos);
    self->end.x += 0.01f;
    self->end.y += 0.01f;
    self->end.z += 0.01f;
    if (fn_803CE0A0(self) || fn_803CE0D0(self)) {
        Vector v8;
        Vector dir;
        if (fn_803CE0D0(self)) {
            fn_80428FA8(&dir, 0.0f, 0.0f, 1.0f);
        } else {
            fn_80428FA8(&dir, 1.0f, 0.0f, 0.0f);
            if (self->owner) {
                Matrix m;
                fn_8042D7B0(&m);
                if (fn_8039A660(self, &m, self->marker, self->marker_id, 0))
                    fn_80435754(&dir, &m);
                else
                    fn_80435754(&dir, &self->owner->world);
            }
        }
        fn_80429090(&v8, &self->end, &dir, self->length);
        self->s28(&v8, 0);
    }
    self->s67();
    self->f2A0 = 1;
}

void fn_803BE5B8(register Constraint *self)
{
    if (self->target) {
        if (self->owner)
            fn_80393698(self->owner, self);
        void *actor = fn_800ACFA8(self->target);
        if (actor) {
            self->marker = self->endmarker;
            self->marker_id = self->endmarker_id;
            self->endmarker = 0xFF;
            self->endmarker_id = 0xFF;
            fn_80393938(actor, self, 1);
        } else {
            self->s43(0);
            if (!fn_8039D148(self))
                fn_8039D820(self, 1);
        }
        self->target = 0;
    }
}

void fn_803BE6BC(register Constraint *self, Vector *v)
{
    if (!v || !self->f174)
        return;
    unsigned int n = self->s75();
    float w = 0.0f;
    if (self->f2A0) {
        for (unsigned int i = 0; i < n; i++, w += 1.0f) {
            Point *p = fn_803CEC54(self, i);
            float f = w / (float)n;
            if (p->f24 == 0.0f)
                continue;
            fn_8042FE08(p, v, f);
        }
    } else {
        for (unsigned int i = 0; i < n; i++, w += 1.0f) {
            Point *p = fn_803CEC54(self, i);
            float f = w / (float)n;
            if (p->f24 == 0.0f)
                continue;
            fn_8042FE08(p, v, 1.0f - f);
        }
    }
}
}

__asm__(".section .rodata\n\t.globl lbl_804BD0F4\nlbl_804BD0F4:\n\t.float 0\n\t.text");
