// Thrower event 0x44

struct Move {
    char pad0[0x40];
    unsigned int modes; // +0x40, bit 1 << extra
    unsigned int id;    // +0x44
    char pad48[0x8];
};

struct MoveList {
    char pad0[0x44];
    unsigned int count; // +0x44
    Move *moves;        // +0x48
};

struct Actor {
    char pad0[0x304];
    unsigned int flags; // +0x304
};

struct State {
    char pad[0x75C];
};

extern State lbl_80552110; // the game-state object G

extern "C" {
int fn_800B13D8(void *self);
int fn_80042EBC(int id, int extra);
int fn_8005287C(void);
int fn_800419E8(int a);
int fn_80041ECC(void);
int fn_800479D0(int a);
int fn_800419AC(void);
int fn_800B0C1C(void *self);
Actor *fn_800B14C8(void *self);
void *fn_80085954(Actor *actor);
int fn_800CD2B8(void *ctrl);
void fn_800CD67C(void *ctrl, int a);
int fn_800436CC(void *self, int n, Move **moves);
int fn_8004322C(void *self, int n, Move **moves, int extra);
void fn_8003ECF0(int a);
int fn_800B0C58(void *self);
int fn_800B14A0(void *self);
int fn_80435878(State *g);
int fn_800439B0(int obj, MoveList *list);
int fn_80043C5C(int obj, MoveList *list);
void fn_80043F60(void *self, MoveList *list);
void fn_80043EA4(int move, void *self, int a);
extern const unsigned int lbl_80486748[5];
extern int lbl_8066B744;
extern int lbl_8066B74C;
extern int lbl_8066B75C;
extern int lbl_8066B760;
}

extern "C" int fn_80042378(void *self, MoveList *list, int value, int extra)
{
    if (value == 0xFFFF)
        value = fn_80042EBC(fn_800B13D8(self), extra);
    int n = 0;
    Move *found[32];
    unsigned int i;
    if (!fn_8005287C())
        return 0;
    if (list->count == 0)
        return 0;
    int skip = 0;
    switch (extra) {
    case 0:
        skip = fn_800419E8(1) || fn_80041ECC() || !fn_800479D0(0);
        break;
    case 1:
        skip = fn_800419E8(1) == 1;
        if (!skip) {
            skip = 1;
            if (fn_800B0C1C(self)) {
                void *ctrl = fn_80085954(fn_800B14C8(self));
                if (ctrl && fn_800CD2B8(ctrl) && (fn_800B14C8(self)->flags & 0x1000)) {
                    skip = 0;
                    fn_800CD67C(ctrl, 0);
                }
            }
        }
        break;
    case 2:
        skip = fn_800419E8(1) != 1 && !fn_800419AC();
        break;
    }
    if (skip)
        return 0;
    unsigned int mask = 0;
    switch (extra) {
    case 0:
        mask |= 1;
        break;
    case 1:
        mask |= 2;
        break;
    case 2:
        mask |= 4;
        break;
    }
    int ranged = 0;
    int range = -1;
    if (extra == 2) {
        for (unsigned int j = 0; j <= 4; j++) {
            if (value == lbl_80486748[j]) {
                ranged = 1;
                range = j;
                break;
            }
        }
    }
    for (i = 0; i < list->count; i++) {
        if ((list->moves[i].id == value
             || (list->moves[i].id >= lbl_80486748[range] && list->moves[i].id < lbl_80486748[range] + 10))
            && (list->moves[i].modes & mask))
            found[n++] = &list->moves[i];
    }
    if (n == 0)
        return 0;
    int move = 0;
    if (ranged)
        move = fn_800436CC(self, n, found);
    else
        move = fn_8004322C(self, n, found, extra);
    if (!move)
        return 0;
    if (extra == 2 && fn_800419AC())
        return 1;
    if (extra == 1 && fn_800419E8(1) == 2)
        fn_8003ECF0(0);
    if (!fn_800B0C58(self))
        return 0;
    int obj = fn_800B14A0(self);
    lbl_8066B74C = move;
    if (fn_80435878(&lbl_80552110))
        return 0;
    int ok = 0;
    switch (extra) {
    case 0:
        ok = fn_800439B0(obj, list);
        break;
    case 1:
        ok = fn_80043C5C(obj, list);
        break;
    case 2:
        if (!lbl_8066B744)
            fn_80043F60(self, list);
        fn_80043EA4(lbl_8066B74C, self, 1);
        ok = 1;
        break;
    }
    if (ok) {
        lbl_8066B75C = value;
        lbl_8066B760 = extra;
    }
    return ok;
}
