// Adds a snapshot node for an actor to its record, and one for the actor its controller holds.

struct Snap {
    int f0;           // +0x0
    int f4;           // +0x4
    float f8;         // +0x8
    int fC;           // +0xC
    float f10;        // +0x10
    int f14;          // +0x14
    int f18;          // +0x18
    float f1C;        // +0x1C
    int f20;          // +0x20
    float f24;        // +0x24
    int f28;          // +0x28
    float f2C;        // +0x2C
    float f30;        // +0x30
    float f34;        // +0x34
    int f38;          // +0x38
    int f3C;          // +0x3C
    int f40;          // +0x40
    char pad44[0x4];
    float f48;        // +0x48
    int f4C;          // +0x4C
};

struct Node {
    char pad0[0x8];
    unsigned int flags; // +0x8
    char padC[0x4];
    char matrix[0x40];  // +0x10
    char vec50[0x10];   // +0x50
    char vec60[0x10];   // +0x60
    union {
        Snap snap;
        float f70;
    };                  // +0x70
};

struct Record {
    char pad0[0xC];
    unsigned int flags; // +0xC
};

struct Anim {
    float f0;  // +0x0
    float f4;  // +0x4
    char pad8[0xC];
    int f14;   // +0x14
    int f18;   // +0x18
    int f1C;   // +0x1C
    char pad20[0xC];
    float f2C; // +0x2C
    float f30; // +0x30
    char pad34[0xC];
    int f40;   // +0x40
    int f44;   // +0x44
    int f48;   // +0x48
    char pad4C[0xC];
    float f58; // +0x58
    float f5C; // +0x5C
    float f60; // +0x60
    char pad64[0x8];
    int f6C;   // +0x6C
    char pad70[0x4];
    int f74;   // +0x74
};

struct Player {
    char pad0[0x30];
    int f30;    // +0x30
    char pad34[0x2E8];
    float f31C; // +0x31C
};

struct Body {
    char pad0[0x298];
    float f298; // +0x298
};

extern int lbl_8066B784;
extern int lbl_8066B79C;

extern "C" {
void *fn_800531AC(void);
int fn_80430024(void *cam);
void fn_800449EC(int a);
int fn_800B1D78(void *actor);
int fn_800B0CC0(void *actor);
int fn_800B1CC8(void *actor);
int fn_800B1228(void *actor);
int fn_800B13D8(void *actor);
Record *fn_800459F8(void *actor, int create, int id);
int fn_80045630(void);
Node *fn_80045BA4(void);
void fn_800B1624(void *actor, void *out);
int fn_80067050(void *actor, void *out);
int fn_80067148(void *actor, void *out);
int fn_800B0C58(void *actor);
void fn_80048274(void *actor, int mask, float f, int on);
int fn_800B0F0C(void *actor);
Player *fn_800B1568(void *actor);
Anim *fn_8009AF80(Player *player);
float fn_804355EC(float *v);
int fn_800B14A0(Player *player);
int fn_800B14A0_id(void *actor) __asm__("fn_800B14A0");
void fn_80042110(Node *node, int id);
int fn_800B0C58_player(Player *player) __asm__("fn_800B0C58");
void *fn_80085928(Player *player);
int fn_800CC6DC(void *ctl);
int fn_800CC514(void *ctl);
Body *fn_800B1478(void *actor);
void fn_80045C28(Record *rec, Node *node);
void *fn_80085954(int id);
void *fn_800CD9B0(void *ctl);
int fn_800B0E54(void *actor);
void fn_8004076C(void *owner, void *actor, int c, int d);

void fn_8003FE44(void *actor, int a, int b)
{
    void *cam = fn_800531AC();
    if (cam && fn_80430024(cam))
        fn_800449EC(0);
    if (!lbl_8066B784 && !lbl_8066B79C)
        return;
    if ((fn_800B1D78(actor) && !fn_800B0CC0(actor)) || !fn_800B1CC8(actor))
        return;
    if (fn_800B1228(actor))
        return;
    int id = fn_800B13D8(actor);
    Record *rec = fn_800459F8(actor, a, b);
    if (!rec) {
        rec = fn_800459F8(actor, 1, fn_80045630());
        if (!rec)
            return;
        rec->flags |= 2;
    }
    Node *node = fn_80045BA4();
    if (!node)
        return;
    fn_800B1624(actor, node->matrix);
    fn_80067050(actor, node->vec50);
    fn_80067148(actor, node->vec60);
    if (fn_800B0C58(actor))
        fn_80048274(actor, 0xFFFF0000, 1.0f, 1);
    if (fn_800B0F0C(actor)) {
        Player *player = fn_800B1568(actor);
        Anim *an = fn_8009AF80(player);
        if (an) {
            node->flags |= 1;
            Snap &s = node->snap;
            s.f18 = an->f1C;
            s.f20 = an->f14;
            s.f14 = an->f18;
            s.f1C = an->f4;
            s.f24 = an->f0;
            if (fn_804355EC(&an->f2C) > 0.0f) {
                s.f4 = an->f48;
                s.fC = an->f40;
                s.f0 = an->f44;
                s.f8 = an->f30;
                s.f10 = an->f2C;
            } else {
                s.f4 = an->f1C;
                s.fC = an->f14;
                s.f0 = an->f18;
                s.f8 = an->f4;
                s.f10 = an->f0;
            }
            s.f28 = an->f74;
            s.f38 = an->f6C;
            s.f2C = an->f5C;
            s.f34 = an->f58;
            s.f30 = an->f60;
            fn_80042110(node, fn_800B14A0(player));
        }
        if (fn_800B0C58_player(player)) {
            Player *p = player;
            void *ctl = fn_80085928(p);
            if (ctl) {
                node->snap.f40 = fn_800CC6DC(ctl);
                node->snap.f3C = fn_800CC514(ctl);
                node->flags |= 0x10;
            }
            node->snap.f48 = p->f31C;
            node->snap.f4C = p->f30;
        }
    }
    if (fn_800B0CC0(actor)) {
        Body *body = fn_800B1478(actor);
        node->f70 = body->f298;
        node->flags |= 0x100;
    }
    fn_80045C28(rec, node);
    if (fn_800B0C58(actor)) {
        int x = fn_800B14A0_id(actor);
        if (x && fn_80085954(x)) {
            void *ctl = fn_80085954(x);
            if (ctl && fn_800CD9B0(ctl)) {
                void *held = fn_800CD9B0(ctl);
                if (held && fn_800B0E54(held))
                    fn_8004076C(actor, held, 1, 0);
            }
        }
    }
}
}
