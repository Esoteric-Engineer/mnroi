// Ensures G has a second player slot (cloning slot 0's character into a new one if not), then sets up both players' actors (guess).
// Slot and game-state fields: docs/versus.md section 4.1. The unit owns the 100.0f/0.0f pool at 0x8048A444.

inline int sn_return_decl(int a) { return a; }

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

class Root
{
public:
    char d[0x40];
    Root() __asm__("fn_8042D7B0");
    void set(Vector *v) __asm__("fn_8042E438");
};

typedef struct Node
{
    char unk0[0x10];
    Vector pos; // +0x10
} Node;

typedef struct Scene
{
    char unk0[0x10];
    int unk10; // +0x10
    char unk14[0x128];
    Node *unk13C; // +0x13C
} Scene;

// fn_800B1A98 is a base-class method and fn_80432924 returns the derived PEnt: that gives the DOL's receiver copy.
struct Ent
{
    char d[0x10];
    Scene *scene() __asm__("fn_800B1A98");
};

struct PEnt : Ent
{
    int pad;
};

typedef struct GameState
{
    char unk0[0x10];
    char slots[8][0xB0]; // +0x10
    int numPlayers;      // +0x590
} GameState;

// The actor's vtable is at +0x3AC; slot 5 (entry +0x30) is called through the base EBase.
struct EObj
{
    char d[0x3AC];
};

struct EBase : EObj
{
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5(int mode); // vtable +0x30
};

struct EMid : EBase
{
};

struct EActor : EMid
{
    int pad;
};

extern "C" {
extern char lbl_80552120[];
extern char lbl_8052F060[];
extern float lbl_8066B948;
extern PEnt *fn_80432924(void *g);
extern int fn_80434900(void *g);
extern char *fn_80443BC8(void *slot);
extern void *fn_800FD5FC(const char *name, int flag);
extern void *fn_800952A4(void *g, void *tmpl, int flag);
extern void fn_80443C4C(void *slot, int port);
extern void fn_80443C24(void *slot, int v);
extern int fn_80430050(void *level);
extern void fn_80096268(void *slot, int a, int b);
extern void *fn_8042FF2C(void *slot);
extern void fn_80031048(void *actor, float a, float b, int c, int d);
extern EActor *fn_80085954(void *actor);
extern void fn_800BD2D0(void *p, int v);
extern void *fn_800B1CC8(void *actor);
extern void fn_8042DCC0(void *root);
extern void fn_800AFAB0(void *actor, Scene *scene, void *world, void *root, int flag);
extern void fn_800B16D8(void *actor, void *out);
extern void *fn_800B1750(void *actor);
extern void fn_8042DC84(void *dst, void *src);
extern void fn_80429090(void *out, void *a, void *b, float s);
extern void fn_8042D80C(void *dst, void *src);
extern void fn_8042ED2C(void *root, void *a, void *b, float s);
extern void *fn_800B1724(void *actor);
extern void fn_8005A828(void *actor, void *p);
}

extern "C" void fn_800956D4(register GameState *g)
{
    PEnt *a = fn_80432924(g);
    void *b = 0;

    {
        void *slot;

        if ((unsigned int)fn_80434900(g) <= 1) {
            slot = fn_800952A4(g, fn_800FD5FC(fn_80443BC8(lbl_80552120), 0), 1);
            fn_80443C4C(slot, 1);
            fn_80443C24(slot, 0);
            fn_80096268(slot, fn_80430050(lbl_8052F060), 8);
            b = fn_8042FF2C(slot);
            g->numPlayers++;
        } else {
            slot = g->slots[1];
            b = fn_8042FF2C(slot);
        }
    }

    fn_80031048(a, 100.0f, 100.0f, 1, 1);
    fn_80031048(b, 100.0f, 100.0f, 1, 1);
    fn_800BD2D0(fn_80085954(a), 0);
    fn_800BD2D0(fn_80085954(b), 0);

    Scene *scene = a->scene();
    Root r18;
    if (scene->unk10 == 0) {
        fn_8042DCC0(&r18);
    } else {
        Node *node = fn_80432924(g)->scene()->unk13C;
        r18.set(&node->pos);
    }

    fn_800AFAB0(a, a->scene(), fn_800B1CC8(a), &r18, 0);

    Vector v60;
    fn_800B16D8(a, &v60);
    Vector v70;
    fn_8042DC84(&v70, fn_800B1750(a));
    Vector v80;
    Vector v90;
    float scale = lbl_8066B948;
    fn_80429090(&v80, &v60, &v70, scale);
    fn_8042D80C(&v90, &v70);
    Root ra8;
    fn_8042ED2C(&ra8, &v80, &v60, 0.0f);
    fn_800AFAB0(b, a->scene(), fn_800B1CC8(a), &ra8, 0);

    fn_8005A828(a, fn_800B1724(b));
    fn_8005A828(b, fn_800B1724(a));
    fn_80085954(a)->s5(2);
    fn_80085954(b)->s5(2);
}
