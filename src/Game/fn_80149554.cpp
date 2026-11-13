// cAIMessages: the 64-entry queue of messages to actors, posted by fn_80149A6C and delivered once a frame. docs/ai.md row 10.
// .rodata 0x8049B2A0 (the queue's two OSReport strings) is extern_pool; the file's header strings follow it.

#include <stdarg.h>

inline int sn_return_decl(int a) { return a; }

// A message to the actor with id `target` (fn_80463230 reads kind, fn_8046325C target)
struct AIMessage {
    int kind; // +0x0
    int target; // +0x4
};
struct AIMessage0 : AIMessage { // the actor gets fn_8007EFE0(arg)
    int arg; // +0x8
    AIMessage0(int target, int arg) __asm__("fn_80463288");
};
struct AIMessage1 : AIMessage { // the actor gets fn_8007F184 with actor `other`
    int other; // +0x8
    AIMessage1(int target, int other) __asm__("fn_804632E0");
};
struct AIMessage2 : AIMessage { // the actor gets fn_8007F2C4(0)
    AIMessage2(int target) __asm__("fn_80463338");
};

struct Ent {
    int pad;
};
struct Actor : Ent { // matching_notes 49
    int x;
};

extern "C" {
int fn_8046325C(AIMessage *m);
int fn_80463230(AIMessage *m);
Actor *fn_80442080(void *ai);
int fn_800B13D8(Ent &e);
Ent *fn_800ACFA8(int id);
int fn_800B0C58(Ent *e);
int fn_80085EEC(Ent *e);
float fn_8007EFE0(Ent *e, int arg);
void fn_8007F184(Ent *e, Ent *other);
void fn_8007F2C4(Ent *e, int a);
void OSReport(const char *fmt, ...);
void fn_80149660(AIMessage *m);
void fn_801498E8(AIMessage *m);
AIMessage *fn_801499A4(void);
}

extern AIMessage *lbl_80571CB0[64];
extern int lbl_8066F1AC; // count
extern int lbl_8066F1B0; // write index
extern int lbl_8066F1B4; // read index

extern "C" void fn_80149554(void)
{
}

// Delivers the queued messages addressed to ai's actor (from the write index, as the original does).
extern "C" void fn_80149570(void *ai)
{
    int unused = 0;
    int i;
    for (i = 0; i < lbl_8066F1AC; i++) {
        unsigned int slot = (lbl_8066F1B0 + i) % (sizeof lbl_80571CB0 / sizeof lbl_80571CB0[0]);
        AIMessage *m = lbl_80571CB0[slot];
        if (m && fn_8046325C(m) == fn_800B13D8(*fn_80442080(ai))) {
            fn_80149660(m);
            lbl_80571CB0[slot] = 0;
        }
    }
}

// Delivers m to its actor and frees it.
extern "C" void fn_80149660(AIMessage *msg)
{
    int id = fn_8046325C(msg);
    Ent &e = *fn_800ACFA8(id);
    if (!&e)
        return;
    if (!fn_800B0C58(&e))
        return;
    if (fn_80085EEC(&e))
        return;
    switch (fn_80463230(msg)) {
    case 0: {
        AIMessage0 *m = (AIMessage0 *)msg;
        float r = fn_8007EFE0(&e, m->arg);
        delete m;
        break;
    }
    case 1: {
        AIMessage1 *m = (AIMessage1 *)msg;
        fn_8007F184(&e, fn_800ACFA8(m->other));
        delete m;
        break;
    }
    case 2: {
        AIMessage2 *m = (AIMessage2 *)msg;
        fn_8007F2C4(&e, 0);
        delete m;
        break;
    }
    }
}

extern "C" void fn_801497A8(void)
{
    while (lbl_8066F1AC) {
        AIMessage *m = fn_801499A4();
        while (!m && lbl_8066F1AC)
            m = fn_801499A4();
        if (m)
            fn_80149660(m);
    }
}

extern "C" void fn_80149844(void)
{
    while (lbl_8066F1AC) {
        AIMessage *m = fn_801499A4();
        if (!m) {
        }
        delete m;
    }
}

extern "C" void fn_801498B0(void)
{
    fn_80149844();
}

extern "C" void fn_801498E8(AIMessage *m)
{
    if (lbl_8066F1AC >= sizeof lbl_80571CB0 / sizeof lbl_80571CB0[0]) {
        if (m)
            delete m;
        OSReport("cAIMessages::Enqueue() ERROR: Trying to enqueue into a full queue.\n", 0, 0, 0, 0);
        return;
    }
    lbl_80571CB0[lbl_8066F1B0] = m;
    lbl_8066F1B0 = ++lbl_8066F1B0 % (sizeof lbl_80571CB0 / sizeof lbl_80571CB0[0]);
    lbl_8066F1AC++;
}

extern "C" AIMessage *fn_801499A4(void)
{
    if (lbl_8066F1AC == 0) {
        OSReport("cAIMessages::Dequeue() ERROR: Trying to dequeue from an empty queue.\n", 0, 0, 0, 0);
        return 0;
    }
    AIMessage *m = lbl_80571CB0[lbl_8066F1B4];
    lbl_80571CB0[lbl_8066F1B4] = 0;
    lbl_8066F1B4 = ++lbl_8066F1B4 % (sizeof lbl_80571CB0 / sizeof lbl_80571CB0[0]);
    lbl_8066F1AC--;
    return m;
}

// Posts a message of the given kind to the actor `target`: kind 0 (target, arg), 1 (target, other), 2 (target).
extern "C" void fn_80149A6C(int kind, int sender, ...)
{
    if (sender) {
        va_list ap;
        va_start(ap, sender);
        int a;
        int b;
        switch (kind) {
        case 0:
            a = va_arg(ap, int);
            b = va_arg(ap, int);
            fn_801498E8(new AIMessage0(a, b));
            break;
        case 1:
            b = va_arg(ap, int);
            a = va_arg(ap, int);
            fn_801498E8(new AIMessage1(b, a));
            break;
        case 2:
            b = va_arg(ap, int);
            fn_801498E8(new AIMessage2(b));
            break;
        }
        va_end(ap);
    }
}
