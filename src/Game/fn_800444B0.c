// Common start for fn_800439B0 and fn_80043C5C: fills the clock record, then has fn_8003FE44 snapshot the participants in the active record list.

typedef struct {
    int a;              // +0x0
    float f;            // +0x4
} Pair;

typedef struct {
    int first;          // +0x0
    int second;         // +0x4
    unsigned int start; // +0x8
    int offset;         // +0xC
    unsigned int mask;  // +0x10
    unsigned int flags; // +0x14
    float f18;          // +0x18
    float f1C;          // +0x1C
    char pad20[0x8];
} Clock;

typedef struct {
    char pad0[0x8];
    unsigned int flags; // +0x8
} Holder;

typedef struct Rec {
    int handle;         // +0x0
    char pad4[0x8];
    unsigned int flags; // +0xC
    unsigned int mask;  // +0x10
    char pad14[0x20];
    void *list;         // +0x34
    Holder *holder;     // +0x38
    char pad3C[0x4];
    struct Rec *next;   // +0x40
} Rec;

typedef struct {
    char pad0[0x3F4];
    int target;         // +0x3F4
} Actor;

int fn_80435878(void *p);
int fn_800B0C58(void *actor);
int fn_800466D8(void *actor, int *kind);
int fn_80045E9C(void *actor);
void fn_800481E8(void);
int fn_800B13D8(void *actor);
unsigned int fn_8042EFF8(void *p);
float fn_80435650(void *p);
void fn_801AFC50(void *p, float a, float b);
void *fn_800ACFA8(int id);
void fn_8003FE44(void *actor, int a, int b);
int fn_800B0CC0(void *actor);

extern char lbl_80552110[];
extern char lbl_80593BE8[];
extern Clock lbl_8053EF18[8];
extern Pair lbl_8053F254[3];
extern Pair lbl_8053F26C[3];
extern Pair lbl_8053F2CC[3][3];
extern Clock *lbl_8066B798;
extern Rec *lbl_8066B774;
extern int lbl_8066B79C;
extern int lbl_8066B784;
extern float lbl_8066B7A4;
extern int lbl_8066B788;
extern int lbl_8066B78C;
extern int lbl_8066B794;
extern int lbl_8066B7A0;
extern int lbl_8066B768;
extern int lbl_8066B7AC;

int fn_800444B0(Actor *self, int mode, unsigned int flags)
{
    int kind;
    Actor *actor;

    if (fn_80435878(lbl_80552110))
        return 0;
    if (!self || !fn_800B0C58(self))
        return 0;
    if (mode)
        kind = 0;
    else if (!fn_800466D8(self, &kind))
        return 0;
    actor = self;
    if (!mode && fn_80045E9C(self))
        return 0;
    fn_800481E8();
    if (flags & 0x10) {
        Clock *clock = &lbl_8053EF18[0];
        clock->flags = 1;
        if (mode) {
            clock->first = fn_800B13D8(self);
            clock->second = 0;
        } else {
            clock->first = self->target;
            clock->second = fn_800B13D8(self);
        }
        clock->start = fn_8042EFF8(lbl_80593BE8);
        lbl_8066B798 = clock;
    } else {
        return 0;
    }
    lbl_8066B79C = 1;
    lbl_8066B784 = 0;
    lbl_8066B7A4 = fn_80435650(lbl_80593BE8);
    if (mode)
        fn_801AFC50(lbl_80593BE8, lbl_8053F2CC[1][kind].f, 0.0f);
    else
        fn_801AFC50(lbl_80593BE8, lbl_8053F2CC[0][kind].f, 0.0f);
    lbl_8066B798->flags |= 0xC;
    lbl_8066B798->flags |= flags;
    if (lbl_8066B798->flags & 0x10)
        lbl_8066B798->f1C = 0.0f;
    else
        lbl_8066B798->f1C = lbl_8053F254[kind].f;
    lbl_8066B798->f18 = lbl_8053F26C[kind].f;
    lbl_8066B798->offset = 0;
    lbl_8066B788 = 0;
    lbl_8066B78C = 0;
    lbl_8066B794 = fn_8042EFF8(lbl_80593BE8);
    {
        Rec *rec = lbl_8066B774;
        while (rec) {
            if (!rec->list) {
                rec = rec->next;
                continue;
            }
            if ((rec->flags & 1) && (rec->mask & lbl_8066B798->mask)) {
                void *other = fn_800ACFA8(rec->handle);
                if (other) {
                    if (fn_800B0C58(other)) {
                        if (fn_800B13D8(other) == lbl_8066B798->first || fn_800B13D8(other) == lbl_8066B798->second) {
                            fn_8003FE44(other, 0, 0);
                            rec->holder->flags |= 0x20;
                        }
                    } else if (fn_800B0CC0(other)) {
                        fn_8003FE44(other, 0, 0);
                        rec->holder->flags |= 0x20;
                        lbl_8066B788++;
                        rec->flags |= 0x40;
                    }
                }
            }
            rec = rec->next;
        }
    }
    if (mode) {
        lbl_8066B7A0 = 6;
    } else {
        lbl_8066B7A0 = 4;
        if (!lbl_8066B788 && !lbl_8066B78C)
            lbl_8066B7A0 = 5;
    }
    lbl_8066B768 = fn_8042EFF8(lbl_80593BE8);
    lbl_8066B79C = 0;
    lbl_8066B7AC = 0;
    return 1;
}
