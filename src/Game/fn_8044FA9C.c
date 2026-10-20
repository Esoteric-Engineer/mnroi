// State machine for table record G2+0x14 in lbl_80567760 (docs/versus.md section 5, row 2).
typedef struct Record {
    void *owner; // +0x0
    char pad0[0x1C];
    int source; // +0x20
    char pad1[0x8];
    int handle; // +0x2C
    int state; // +0x30
    char pad2[0x18];
    int free; // +0x4C
    char pad3[0x10];
} Record __attribute__((aligned(8)));

typedef struct Actor {
    char pad[0x168];
    int link; // +0x168
} Actor;

typedef struct Cursor {
    char pad[0x14];
    int index; // +0x14
} Cursor;

extern Record lbl_80567760[];
extern Cursor lbl_80568DB0;
extern int lbl_8066BD04;
extern int lbl_8066BD14;
extern int lbl_8066BD18;

extern Actor *fn_800ACFA8(int handle);
extern int fn_800B1078(Actor *actor);
extern void fn_80115154(int handle, int mode);
extern int fn_804581A0(Actor *actor, int index);
extern void *fn_804580CC(int handle, int index);
extern void fn_804582F0(void *owner, Actor *actor, int index);
extern void fn_80456064(void *owner);
extern void fn_8044F824(int index);
extern void fn_8044F8E8(int index);
extern int fn_8044F93C(Actor *actor, int index);
extern int fn_8044F9EC(Actor *actor, int index);

void fn_8044FA9C(void)
{
    int index;
    int word;
    Actor *actor;
    void *owner;
    index = ((Cursor *)&lbl_80568DB0)->index;
    word = lbl_80567760[index].source;
    actor = fn_800ACFA8(word);
    if (lbl_80567760[index].state == 3 || actor == 0 || fn_800B1078(actor) != 0)
    {
        fn_8044F824(index);
        fn_80115154(lbl_80567760[index].handle, 7);
        return;
    }
    if (fn_804581A0(actor, index) == 0)
    {
        fn_8044F824(index);
        if (actor)
        {
            actor->link = 0;
        }
        return;
    }
    if (lbl_8066BD04 == 0 || lbl_8066BD14 != 0)
    {
        if (lbl_80567760[index].free == 0)
        {
            fn_8044F8E8(index);
        }
    }
    else if (lbl_80567760[index].free == 0 && fn_8044F93C(actor, index) != 0)
    {
        fn_8044F8E8(index);
    }
    else if (lbl_80567760[index].free != 0 && fn_8044F9EC(actor, index) != 0)
    {
        lbl_80567760[index].state = 0;
        lbl_80567760[index].free = 0;
    }
    if (lbl_80567760[index].free == 0)
    {
        if (lbl_80567760[index].state == 0)
        {
            if (lbl_8066BD18 != 0)
            {
                lbl_80567760[index].owner = fn_804580CC(lbl_80567760[index].handle, index);
                lbl_80567760[index].state = 1;
            }
            return;
        }
        if (lbl_80567760[index].state == 1)
        {
            owner = lbl_80567760[index].owner;
            fn_804582F0(owner, actor, index);
            fn_80456064(owner);
            return;
        }
        fn_8044F824(index);
        if (actor)
        {
            actor->link = 0;
        }
    }
    else
    {
    }
}
