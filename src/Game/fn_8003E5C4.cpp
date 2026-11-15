// Per-frame update of the move and record system: keeps the move camera on its actor, ticks the clocks, and steps records with flag 0x20 clear in record states 3 and 4.

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
    char d[0x198];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual Vector *s7(); // vtable +0x40
};

struct Clock {
    int first;          // +0x0
    int second;         // +0x4
    unsigned int start; // +0x8
    int offset;         // +0xC
    unsigned int mask;  // +0x10
    unsigned int flags; // +0x14
    float f18;          // +0x18
    float f1C;          // +0x1C
    char pad20[0x4];
    int timer;          // +0x24
};

struct Rec {
    int handle;         // +0x0
    int last;           // +0x4
    unsigned int until; // +0x8
    unsigned int flags; // +0xC
    char pad10[0x24];
    void *list;         // +0x34
    char pad38[0x8];
    Rec *next;          // +0x40
};

extern char lbl_80593BE8[];
extern int lbl_8053EE80[3];
extern int lbl_8053EE8C[3];
extern Clock lbl_8053EF18[8];
extern int lbl_8066B744;
extern void *lbl_8066B74C;
extern void *lbl_8066B750;
extern Actor *lbl_8066B754;
extern int lbl_8066B75C;
extern int lbl_8066B764;
extern Rec *lbl_8066B774;
extern int lbl_8066B78C;
extern Clock *lbl_8066B798;
extern int lbl_8066B7A0;
extern unsigned int lbl_8066B7B4;

extern "C" {
void fn_800440B0(void);
Actor *fn_800ACFA8(int id);
int fn_800B0F0C(Actor *actor);
void *fn_800B1568(Actor *actor);
void fn_80043EA4(void *entry, void *self, int flag);
void fn_8003C5D8(void *cam, Vector *v);
void fn_8003C69C(void *cam);
void fn_8042DC84(Vector *dst, Vector *src);
Vector *fn_80430F74(void *cam);
void fn_80429090(Vector *out, Vector *a, void *b, float s);
float fn_800B2620(Actor *actor);
void fn_80036F98(void *cam, Vector *a, Vector *b);
void fn_80042984(void);
int fn_800419AC(void);
int fn_80047BF8(int *a, int *b);
void fn_8003F014(int a, int b, int c);
void fn_800449EC(int a);
int fn_804324EC(void *p);
void fn_800456C8(Clock *clock);
int fn_800419E8(int a);
int fn_8003F6C8(Rec *rec);
int fn_80046050(Rec *rec);
void fn_80044988(void);
float fn_80426A84(void *p);
void fn_8003ECF0(int a);
unsigned int fn_8042EFF8(void *p);
void fn_801AFC50(void *p, float a, float b);

void fn_8003E5C4(void)
{
    if (lbl_8066B7A0 == 2)
        fn_800440B0();
    if (lbl_8066B7A0 == 6 && lbl_8066B798 && lbl_8066B74C) {
        Actor *actor = fn_800ACFA8(lbl_8066B798->first);
        if (actor && fn_800B0F0C(actor))
            fn_80043EA4(lbl_8066B74C, fn_800B1568(actor), 0);
    }
    if (lbl_8066B744 && lbl_8066B798) {
        int index = 0;
        switch (lbl_8066B7A0) {
        case 2:
        case 3:
            index = 2;
            break;
        case 4:
        case 5:
            index = 0;
            break;
        case 6:
            index = 1;
            break;
        }
        if (lbl_8066B750) {
            Actor *focus = 0;
            if (lbl_8053EE80[index] == lbl_8066B75C) {
                switch (lbl_8053EE8C[index]) {
                case 1:
                case 4:
                    focus = fn_800ACFA8(lbl_8066B798->first);
                    break;
                case 2:
                case 5:
                    focus = fn_800ACFA8(lbl_8066B798->second);
                    break;
                }
            }
            Vector eye;
            Vector at;
            if (focus) {
                fn_8003C5D8(lbl_8066B750, focus->s7());
                fn_8003C69C(lbl_8066B750);
                fn_8042DC84(&at, focus->s7());
            } else {
                focus = fn_800ACFA8(lbl_8066B798->first);
                if (focus)
                    fn_8042DC84(&at, focus->s7());
                else
                    fn_80429090(&at, fn_80430F74(lbl_8066B750), (char *)lbl_8066B750 + 0x370, 10.0f);
            }
            if (focus)
                at.z += fn_800B2620(focus) * 0.5f;
            fn_80036F98(lbl_8066B750, fn_80430F74(lbl_8066B750), &at);
        }
        if (!lbl_8066B754 || fn_800ACFA8(lbl_8066B764) != lbl_8066B754)
            fn_80042984();
    }
    if (fn_800419AC()) {
        int kind;
        int id;
        if (fn_80047BF8(&kind, &id)) {
            if (kind == 5 || kind == 1)
                fn_8003F014(id, kind, 1);
            else
                fn_800449EC(0);
        } else {
            Clock *clock = lbl_8053EF18;
            for (int i = 0; i < 8; i++) {
                if ((clock->flags & 1) && (clock->flags & 0x20)) {
                    clock->timer -= fn_804324EC(lbl_80593BE8);
                    if (clock->timer < 0) {
                        fn_800456C8(clock);
                        clock->flags &= ~1;
                    }
                }
                clock++;
            }
        }
    }
    for (Rec *rec = lbl_8066B774; rec && fn_800419E8(0); rec = rec->next) {
        if ((rec->flags & 1) && !(rec->flags & 0x20) && rec->list) {
            switch (lbl_8066B7A0) {
            case 3:
                fn_8003F6C8(rec);
                break;
            case 4:
                fn_80046050(rec);
                break;
            }
        }
    }
    if (fn_800419E8(0)) {
        if (lbl_8066B7A0 == 3 && lbl_8066B78C == 0) {
            fn_80044988();
        } else if (lbl_8066B798->flags & 8) {
            lbl_8066B798->f1C -= fn_80426A84(lbl_80593BE8);
            lbl_8066B798->f18 -= fn_80426A84(lbl_80593BE8);
            if (lbl_8066B798->f18 <= 0.0f)
                fn_8003ECF0(0);
        }
    }
    if (lbl_8066B7B4 && fn_8042EFF8(lbl_80593BE8) > lbl_8066B7B4) {
        fn_800449EC(0);
        fn_801AFC50(lbl_80593BE8, 1.0f, 0.0f);
    }
}
}
