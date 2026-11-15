// Ends the move and record system and resets its tables.

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

struct Actor {
    char pad0[0x30];
    unsigned int f30; // +0x30
};

struct Clock {
    int first;          // +0x0
    int second;         // +0x4
    char pad8[0xC];
    unsigned int flags; // +0x14
    char pad18[0x10];
};

struct Rec {
    char pad0[0x40];
    Rec *next; // +0x40
};

struct Break {
    Vector a;  // +0x0
    Vector v;  // +0x10
    int id;    // +0x20
    int other; // +0x24
    float f;   // +0x28
};

extern int lbl_8053F0D8[];
extern unsigned int lbl_8066B7B0;
extern Clock *lbl_8066B798;
extern int lbl_8066B790;
extern Rec *lbl_8066B774;
extern int lbl_8066B784;
extern int lbl_8066B7A8;
extern Break lbl_8053ECF0[];
extern unsigned int lbl_8066B7AC;
extern int lbl_8066B7A0;
extern int lbl_8066B75C;
extern int lbl_8066B760;
extern int lbl_8053F3D4[];
extern int lbl_8053EE80[];
extern int lbl_8053EE8C[];
extern Clock lbl_8053EF18[];
extern int lbl_8053F238[];
extern int lbl_8066B78C;
extern int lbl_8066B788;
extern int lbl_8066B7B4;

extern "C" {
Actor *fn_800ACFA8(int id);
int fn_800B0C1C(Actor *actor);
int fn_800B14C8(Actor *actor);
void *fn_80085954(int id);
int fn_800CD288(void *ctl);
void fn_800CD634(void *ctl, int on);
void fn_80044014(int force);
void fn_800458EC(Rec *rec, int a);
int fn_800B0CC0(Actor *actor);
Actor *fn_800B1478(Actor *actor);
int fn_800A3F14(Actor *actor);
int fn_800A3588(Actor *actor, Actor *other, float f, Vector *a, Vector *v, float g);
void fn_80044E5C(int a);
void fn_80041B18(void);

void fn_800449EC(int a)
{
    unsigned int i;
    for (i = 0; i < lbl_8066B7B0; i++) {
        Actor *actor = fn_800ACFA8(lbl_8053F0D8[i]);
        if (actor)
            actor->f30 &= ~2;
    }
    lbl_8066B7B0 = 0;
    if (lbl_8066B798) {
        Actor *actor = fn_800ACFA8(lbl_8066B798->first);
        if (actor && fn_800B0C1C(actor)) {
            void *ctl = fn_80085954(fn_800B14C8(actor));
            if (ctl && fn_800CD288(ctl))
                fn_800CD634(ctl, 0);
        }
        actor = fn_800ACFA8(lbl_8066B798->second);
        if (actor && fn_800B0C1C(actor)) {
            void *ctl = fn_80085954(fn_800B14C8(actor));
            if (ctl && fn_800CD288(ctl))
                fn_800CD634(ctl, 0);
        }
        lbl_8066B790 = 0;
        lbl_8066B798->flags &= ~1;
        lbl_8066B798 = 0;
    }
    fn_80044014(1);
    Rec *rec = lbl_8066B774;
    int zero = 0;
    while (rec) {
        Rec *next = rec->next;
        fn_800458EC(rec, zero);
        rec = next;
    }
    lbl_8066B774 = 0;
    lbl_8066B784 = 0;
    lbl_8066B7A8 = 0;
    if (!a) {
        Break *e = lbl_8053ECF0;
        unsigned int j;
        for (j = 0; j < lbl_8066B7AC; j++) {
            Actor *target = fn_800ACFA8(e->id);
            if (target && fn_800B0CC0(target)) {
                Actor *body = fn_800B1478(target);
                if (!fn_800A3F14(body))
                    fn_800A3588(body, fn_800ACFA8(e->other), e->f, &e->a, &e->v, 0.0f);
            }
            e++;
        }
    }
    lbl_8066B7AC = 0;
    lbl_8066B7A0 = 0;
    lbl_8066B75C = -1;
    lbl_8066B760 = -1;
    unsigned int k;
    for (k = 0; k < 3; k++) {
        lbl_8053F3D4[k] = 0;
        lbl_8053EE80[k] = -1;
        lbl_8053EE8C[k] = -1;
    }
    Clock *clock = lbl_8053EF18;
    unsigned int n;
    for (n = 0; n < 8; n++) {
        clock->flags &= ~1;
        clock++;
    }
    fn_80044E5C(1);
    fn_80041B18();
    unsigned int m;
    for (m = 0; m < 7; m++)
        lbl_8053F238[m] = 0;
    lbl_8066B78C = 0;
    lbl_8066B788 = 0;
    lbl_8066B7B4 = 0;
}
}
