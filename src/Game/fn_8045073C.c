// Same state machine as fn_8044FA9C over the third callee set (docs/versus.md section 5, row 2).
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
extern int fn_8045849C(Actor *actor, int index);
extern void *fn_804583C8(int handle, int index);
extern void fn_8045855C(void *owner, Actor *actor, int index);
extern void fn_804561D4(void *owner);
extern void fn_804504C4(int index);
extern void fn_80450588(int index);
extern int fn_804505DC(Actor *actor, int index);
extern int fn_8045068C(Actor *actor, int index);

void fn_8045073C(void)
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
        fn_804504C4(index);
        fn_80115154(lbl_80567760[index].handle, 7);
        return;
    }
    if (fn_8045849C(actor, index) == 0)
    {
        fn_804504C4(index);
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
            fn_80450588(index);
        }
    }
    else if (lbl_80567760[index].free == 0 && fn_804505DC(actor, index) != 0)
    {
        fn_80450588(index);
    }
    else if (lbl_80567760[index].free != 0 && fn_8045068C(actor, index) != 0)
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
                lbl_80567760[index].owner = fn_804583C8(lbl_80567760[index].handle, index);
                lbl_80567760[index].state = 1;
            }
            return;
        }
        if (lbl_80567760[index].state == 1)
        {
            owner = lbl_80567760[index].owner;
            fn_8045855C(owner, actor, index);
            fn_804561D4(owner);
            return;
        }
        fn_804504C4(index);
        if (actor)
        {
            actor->link = 0;
        }
    }
    else
    {
    }
}
