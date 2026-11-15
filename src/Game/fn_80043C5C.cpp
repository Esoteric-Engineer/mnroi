// Mode-1 move start: after the range checks, flags every other active actor with bit 0x2 at +0x30 and records their ids.

struct Node {
    char pad0[0x30];
    unsigned int flags; // +0x30
};

struct Scene {
    char pad0[0x130];
    Node *head; // +0x130
};

struct Clock {
    char pad0[0x14];
    unsigned int flags; // +0x14
};

extern "C" {
int fn_800419E8(int a);
int fn_80041ECC(void);
int fn_800B0C1C(void *self);
int fn_800444B0(void *self, int a, int b);
void fn_80043F60(void *self, void *list);
void fn_80043EA4(void *move, void *self, int a);
Scene &fn_80430050(void *p);
int fn_800B13D8(void *self);
void *fn_800B14C8(void *self);
void *fn_80085954(void *actor);
Node *fn_800CD9B0(void *ctrl);
Node *fn_800B1AC4(Node *node);
extern void *lbl_8066B74C;
extern Clock *lbl_8066B798;
extern char lbl_8052F060[];
extern unsigned int lbl_8066B7B0;
extern int lbl_8053F0D8[32];
}

extern "C" int fn_80043C5C(void *self, void *list)
{
    int r;
    Node *node;
    Node *next;
    void *ctrl;
    Node *held;

    if (fn_800419E8(1) || fn_80041ECC())
        return 0;
    if (!fn_800B0C1C(self))
        return 0;
    r = fn_800444B0(self, 1, 0x10);
    if (r) {
        fn_80043F60(self, list);
        fn_80043EA4(lbl_8066B74C, self, 1);
        lbl_8066B798->flags |= 0x40;
        for (node = fn_80430050(lbl_8052F060).head; node; node = next) {
            if (!(node->flags & 2) && fn_800B0C1C(node) && node != self && lbl_8066B7B0 < 32) {
                lbl_8053F0D8[lbl_8066B7B0++] = fn_800B13D8(node);
                node->flags |= 2;
                ctrl = fn_80085954(fn_800B14C8(node));
                if (ctrl) {
                    held = fn_800CD9B0(ctrl);
                    if (held && lbl_8066B7B0 < 32) {
                        lbl_8053F0D8[lbl_8066B7B0++] = fn_800B13D8(held);
                        held->flags |= 2;
                    }
                }
            }
            next = fn_800B1AC4(node);
        }
    }
    return r;
}
