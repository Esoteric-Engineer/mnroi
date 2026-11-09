// Steps a record in record states 4-6: its timed nodes while the clock's f1C is above 0, otherwise one held node.

inline int sn_return_decl(int a) { return a; }

struct Node {
    unsigned int time;  // +0x0
    char pad4[0x4];
    unsigned int flags; // +0x8
    char padC[0xB4];
    Node *next;         // +0xC0
};

struct Rec {
    int handle;         // +0x0
    int last;           // +0x4
    char pad8[0x4];
    unsigned int flags; // +0xC
    char pad10[0x24];
    Node *list;         // +0x34
    Node *f38;          // +0x38
    Node *f3C;          // +0x3C
};

struct Clock {
    char pad0[0x8];
    unsigned int start; // +0x8
    int offset;         // +0xC
    char pad10[0x4];
    unsigned int flags; // +0x14
    char pad18[0x4];
    float f1C;          // +0x1C
};

extern char lbl_80593BE8[];
extern Clock *lbl_8066B798;
extern int lbl_8066B788;
extern int lbl_8066B78C;
extern int lbl_8066B794;
extern int lbl_8066B7A0;

extern "C" {
int fn_8042EFF8(void *p);
void *fn_800ACFA8(int handle);
int fn_800B0C58(void *actor);
void fn_800465FC(Rec *rec);
void fn_800468B8(Rec *rec);
void fn_80046B4C(void *actor, Node *node, Rec *rec, int kind);
int fn_800B0CC0(void *actor);
int fn_80047988(void);

int fn_80046050(Rec *rec)
{
    int now = fn_8042EFF8(lbl_80593BE8);
    void *actor = fn_800ACFA8(rec->handle);
    if (!actor) {
        if (rec->flags & 0x40) {
            rec->flags &= ~0x40;
            if (fn_800B0C58(actor))
                lbl_8066B78C--;
            else
                lbl_8066B788--;
        }
        return 0;
    }
    if (lbl_8066B798->f1C > 0.0f) {
        if (!(rec->flags & 8)) {
            fn_800465FC(rec);
            fn_800468B8(rec);
            rec->flags |= 8;
        }
        Node *node = rec->list;
        while (node) {
            int t = node->time + lbl_8066B798->offset;
            if (node->time < lbl_8066B798->start) {
                node = node->next;
                continue;
            }
            if (t < lbl_8066B794) {
                node = node->next;
                continue;
            }
            if (t > now)
                break;
            if (t > rec->last && !(node->flags & 0x20))
                fn_80046B4C(actor, node, rec, 3);
            node = node->next;
        }
        rec->last = now;
    } else if (lbl_8066B798->flags & 4) {
        if (fn_800B0C58(actor)) {
            if (rec->f3C)
                fn_80046B4C(actor, rec->f3C, rec, 7);
        } else if (fn_800B0CC0(actor) && fn_80047988()) {
            fn_80046B4C(actor, rec->f38, rec, 3);
            if (rec->flags & 0x40) {
                rec->flags &= ~0x40;
                lbl_8066B788--;
            }
        }
        if (!lbl_8066B788 && !lbl_8066B78C && lbl_8066B7A0 == 4)
            lbl_8066B7A0 = 5;
    }
    return 1;
}
}
