// Steps a record against the clock: fn_80046B4C for each node timed in (last, now]; on expiry drops flags 0x40/0x1 and its count in lbl_8066B78C/lbl_8066B788.
// The role-index branch is in docs/versus.md section 4.3.

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

struct Node {
    unsigned int time;  // +0x0
    char pad4[0xBC];
    Node *next;         // +0xC0
    char padC4[0xC];
} __attribute__((aligned(8)));

struct Clock {
    char pad0[0x8];
    unsigned int start; // +0x8
    int offset;         // +0xC
};

struct Rec {
    int handle;          // +0x0
    int last;            // +0x4
    unsigned int until;  // +0x8
    unsigned int flags;  // +0xC
    char pad10[0x10];
    Vector pos;          // +0x20
    float radius;        // +0x30
    Node *list;          // +0x34
};

struct Tmpl {
    char pad0[0x44];
    int type; // +0x44
};

struct EObj {
    char d[0x3AC];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5(int mode); // vtable +0x30
};

extern char lbl_80552110[]; // the game-state object G
extern char lbl_80593BE8[];
extern Clock *lbl_8066B798;
extern int lbl_8066B788;
extern int lbl_8066B78C;

extern "C" {
unsigned int fn_8042EFF8(void *p);
int fn_800ACFA8(int handle);
void fn_80046B4C(int actor, Node *node, Rec *rec, int kind);
void *fn_800B1724(int actor);
void fn_80429038(Vector *out, Vector *a, void *b);
void fn_8042DC84(Vector *dst, Vector *src);
float fn_80434040(Vector *v);
float fn_800B2670(int actor);
void fn_8042F76C(Vector *v);
void *fn_800B1750(int actor);
float fn_8042EBF4(Vector *v, void *b);
void fn_80435530(Vector *v, float f);
void fn_80065CB0(int actor, Vector *v);
void fn_8005A828(int actor, Vector *v);
int fn_800B0C58(int actor);
int fn_800B14A0(int actor);
Tmpl *fn_8009AF80(int x);
int fn_80085954(int actor);
int fn_800C4D70(int ctl, int a, float f, int b);
int fn_80041CB8(int handle);
EObj *fn_80085954_obj(int actor) __asm__("fn_80085954");
int fn_80085EEC(int actor);
int fn_800B0CC0(int actor);
void fn_800AFFD4(int actor, int on);
void fn_80044988(void);
int fn_8009404C(void *g);
int fn_80432844(void *g);
int fn_80432870(void *g);
void fn_80092550(void *g, int x);

int fn_8003F6C8(Rec *p)
{
    unsigned int now = fn_8042EFF8(lbl_80593BE8);
    int actor = fn_800ACFA8(p->handle);
    if (!actor) {
        if (p->flags & 0x40) {
            p->flags &= ~0x40;
            if (p->flags & 0x20)
                lbl_8066B78C--;
            else
                lbl_8066B788--;
        }
        p->flags &= ~1;
        return 0;
    }
    int done = 0;
    Node *node = p->list;
    while (node) {
        int t = node->time + lbl_8066B798->offset;
        if (node->time < lbl_8066B798->start) {
            node = node->next;
            continue;
        }
        if (t > now)
            break;
        if (t > p->last) {
            fn_80046B4C(actor, node, p, 3);
            node = node->next;
            continue;
        }
        node = node->next;
        if (!node)
            done = 1;
    }
    if (p->flags & 0x80) {
        Vector v;
        fn_80429038(&v, &p->pos, fn_800B1724(actor));
        Vector flat;
        fn_8042DC84(&flat, &v);
        flat.z = 0.0f;
        float d = fn_80434040(&flat);
        d -= fn_800B2670(actor);
        fn_8042F76C(&v);
        if (d > 0.1f && fn_8042EBF4(&v, fn_800B1750(actor)) > 0.0f) {
            fn_80435530(&v, p->radius);
            fn_80065CB0(actor, &v);
            fn_8005A828(actor, &p->pos);
        }
    }
    p->last = now;
    int hit = 0;
    if (done && fn_800B0C58(actor)) {
        int x = fn_800B14A0(actor);
        Tmpl *y = fn_8009AF80(x);
        if (y) {
            int type = y->type;
            if (type == 0xb || type == 0xac || type == 0xb3) {
                int ctl = fn_80085954(x);
                if (ctl && fn_800C4D70(ctl, 0, 0.0f, 0))
                    hit = 1;
            }
        }
    }
    if (now >= p->until || hit) {
        if (done) {
            if (fn_800B0C58(actor) && !fn_80041CB8(p->handle)) {
                int a = actor;
                EObj *b = fn_80085954_obj(a);
                if (b) {
                    if (fn_80085EEC(a))
                        b->s5(1);
                    else
                        b->s5(2);
                }
            }
            if (p->flags & 0x40) {
                if (fn_800B0C58(actor))
                    lbl_8066B78C--;
                else
                    lbl_8066B788--;
                p->flags &= ~0x40;
            }
            p->flags &= ~1;
            if ((p->flags & 0x200) && fn_800B0CC0(actor))
                fn_800AFFD4(actor, 1);
            if (lbl_8066B78C == 0) {
                fn_80044988();
                if (!fn_8009404C(lbl_80552110) && (fn_80432844(lbl_80552110) || fn_80432870(lbl_80552110)))
                    fn_80092550(lbl_80552110, 0);
            }
        }
    }
    return 1;
}
}
