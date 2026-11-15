// Adds a snapshot node for `actor` to its record when the counter lbl_8066B784 is nonzero.

struct Record {
    char pad0[0xC];
    int flags;          // +0xC
};

struct Node {
    char pad0[0x8];
    int flags;          // +0x8
    int owner;          // +0xC
    char matrix[0x40];  // +0x10
    char vec50[0x10];   // +0x50
    char vec60[0x10];   // +0x60
    float f70;          // +0x70
};

struct Body {
    char pad0[0x298];
    float f298;         // +0x298
};

extern "C" {
int fn_800B1D78(void *actor);
void *fn_800B1CC8(void *actor);
void *fn_800531AC(void);
int fn_80430024(void *cam);
void fn_800449EC(int a);
Record *fn_800459F8(void *actor, int create, int id);
int fn_80045630(void);
Node *fn_80045BA4(void);
void fn_800B1624(void *actor, void *out);
int fn_80067050(void *actor, void *out);
int fn_80067148(void *actor, void *out);
int fn_800B13D8(void *actor);
int fn_800B0CC0(void *actor);
Body &fn_800B1478(void *actor);
void fn_80045C28(Record *rec, Node *node);

extern int lbl_8066B784;

void fn_8004076C(void *owner, void *actor, int c, int d)
{
    void *cam;
    Record *rec;
    Node *node;

    if (!lbl_8066B784)
        return;
    if (fn_800B1D78(actor) || !fn_800B1CC8(actor))
        return;
    cam = fn_800531AC();
    if (cam && fn_80430024(cam))
        fn_800449EC(0);
    rec = fn_800459F8(actor, 0, 0);
    if (!rec) {
        rec = fn_800459F8(actor, 1, fn_80045630());
        if (!rec)
            return;
        rec->flags |= 2;
    }
    node = fn_80045BA4();
    if (!node)
        return;
    fn_800B1624(actor, node->matrix);
    fn_80067050(actor, node->vec50);
    fn_80067148(actor, node->vec60);
    node->flags |= 8;
    if (owner)
        node->owner = fn_800B13D8(owner);
    else
        node->owner = 0;
    if (fn_800B0CC0(actor))
        node->f70 = fn_800B1478(actor).f298;
    else
        node->f70 = 0.0f;
    fn_80045C28(rec, node);
}
}
