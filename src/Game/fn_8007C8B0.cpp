// Script system: init, the timed queue, the SCRIPT property and its parameters (docs/story.md row 5).
// Literal pool read from 0x80488028 (extern_pool).

inline int sn_return_decl(int a)
{
    return a;
}

extern "C" {

int fn_8007891C();
void fn_801BEE2C();
void *memset(void *p, int c, unsigned int n);
struct ScriptInst {
    char pad0[0x14];
    int count; // +0x14, queued messages
};

struct ScriptMsg { // 0x20
    ScriptInst *target; // +0x0
    unsigned int time;         // +0x4
    float f8;                  // +0x8
    float fc;                  // +0xC
    float f10;                 // +0x10
    float f14;                 // +0x14
    int f18;                   // +0x18
    unsigned char kind;        // +0x1C
    unsigned char prev;        // +0x1D
    unsigned char next;        // +0x1E
    unsigned char used;        // +0x1F
};

extern ScriptMsg lbl_8054DD80[]; // 128 slots
extern int lbl_8066B8AC;
extern int lbl_8066B8B0;

int fn_8007C8B0()
{
    fn_8007891C();
    fn_801BEE2C();
    memset(lbl_8054DD80, 0, 0x1000);
    lbl_8066B8AC = 0;
    lbl_8066B8B0 = 0xFF;
    return 1;
}

ScriptMsg *fn_8007DA4C();
unsigned int fn_8042EFF8(void *clock);
extern char lbl_80593BE8[];
void fn_8007D960(ScriptMsg *e);
void fn_8007E0C0(ScriptInst *t, unsigned char kind, float a, float b, float c, float d, int e);
void fn_8007DB54(ScriptMsg *e);
void fn_8007DFC4();

int fn_8007C910()
{
    ScriptMsg *e;

    while (fn_8007DA4C() && fn_8007DA4C()->time < fn_8042EFF8(lbl_80593BE8)) {
        e = fn_8007DA4C();
        e->target->count--;
        fn_8007D960(e);
        fn_8007E0C0(e->target, e->kind, e->f8, e->fc, e->f10, e->f14, e->f18);
        fn_8007DB54(e);
    }
    fn_8007DFC4();
    return 1;
}

struct ScriptProp {
    int type;
    char name[1]; // +0x4
};

struct ScriptEntity {
    char pad[0x14C];
    void *script; // +0x14C
};

void *fn_800789DC(char *name, int init);

int fn_8007CA10(ScriptEntity *ent, ScriptProp *prop, int x)
{
    void *script;

    switch (prop->type) {
    case 0x10:
        script = fn_800789DC(prop->name, 0);
        if (script == 0) {
            ent->script = 0;
            return 0;
        }
        ent->script = script;
        return 1;
    }
    return 0;
}

struct ParamLink { // 8
    int type;
    union {
        int v; // +0x4
        float f;
        char *str;
    };
};

struct ParamScript {
    char pad[0xC];
    unsigned int nlinks; // +0xC
    ParamLink *links;    // +0x10
};

struct ParamEntity {
    char pad[0x14C];
    ParamScript *script; // +0x14C
};

void *fn_801AC988(int size, char *tag, int line, int x);
int fn_801A8B60(void *buf, int size, int n, void *file);

#define SWAP32(x) ((unsigned int)(x) >> 24 | ((unsigned int)(x) >> 8 & 0xFF00) | ((unsigned int)(x) & 0xFF00) << 8 | (unsigned int)(x) << 24)

int fn_8007CABC(ParamEntity *ent, unsigned int count, void *file)
{
    ParamScript *s;
    unsigned int i;
    ParamLink *l;
    int len;

    s = ent->script;
    if (s == 0) {
    }
    s->links = (ParamLink *)fn_801AC988(count * 8, "Scripts:Params", 0xD4, 1);
    if (s->links == 0)
        return 0;
    for (i = 0; i < count; i++) {
        l = &s->links[i];
        if (fn_801A8B60(l, 4, 1, file) == 0)
            goto fail;
        l->type = SWAP32(l->type);
        switch (l->type) {
        case 1:
        case 3:
        case 4:
        case 5:
        case 10:
        case 11:
        case 12:
        case 13:
            if (fn_801A8B60(&l->v, 4, 1, file) != 1)
                goto fail;
            l->v = SWAP32(l->v);
            break;
        case 2:
            if (fn_801A8B60(&l->f, 4, 1, file) != 1)
                goto fail;
            *(unsigned int *)&l->f = SWAP32(*(unsigned int *)&l->f);
            break;
        case 7:
        case 8:
        case 9:
            if (fn_801A8B60(&len, 4, 1, file) != 1)
                goto fail;
            len = SWAP32(len);
            l->str = (char *)fn_801AC988(len + 1, "Scripts:Params", 0x107, 1);
            if (l->str == 0)
                goto nomem;
            if (len == 0)
                l->str[0] = 0;
            else if (fn_801A8B60(l->str, 1, len, file) != len)
                goto fail;
            break;
        }
    }
    s->nlinks = count;
    return 1;
fail:
    return 0;
nomem:
    return 0;
    return 1;
}

struct ScriptNode;

struct NodeScript {
    char pad[0x18];
    int count;         // +0x18
    ScriptNode *nodes; // +0x1C
};

struct NodeEnt {
    char pad[0x150];
    ScriptNode *nodes; // +0x150
};

struct ScriptNode { // 0x1C, on both its script's list and its entity's list
    NodeScript *script; // +0x0
    NodeEnt *ent;       // +0x4
    int value;          // +0x8
    ScriptNode *eprev;  // +0xC
    ScriptNode *enext;  // +0x10
    ScriptNode *sprev;  // +0x14
    ScriptNode *snext;  // +0x18
    ScriptNode() __asm__("fn_8007D220");
};

void fn_8007D34C(ScriptNode *self);
void fn_8007D280(ScriptNode *self, NodeScript *script, NodeEnt *ent, int value);
int fn_8007CF94(NodeScript *script, NodeEnt *ent, int value);
int fn_8007D0FC(NodeScript *script, NodeEnt *ent);
NodeEnt *fn_800ACFA8(int handle);

void fn_8007CE84(NodeEnt *ent)
{
    ScriptNode *node = ent->nodes;
    while (node) {
        ScriptNode *dead = node;
        fn_8007D34C(node);
        delete dead;
        node = ent->nodes;
    }
}

int fn_8007CF00(register NodeScript *script, int handle, int value)
{
    if (handle == 0)
        return 0;
    NodeEnt *ent = fn_800ACFA8(handle);
    if (ent == 0)
        return 0;
    return fn_8007CF94(script, ent, value);
}

int fn_8007CF94(register NodeScript *script, NodeEnt *ent, int value)
{
    ScriptNode *node = ent->nodes;
    while (node) {
        if (node->script == script) {
            node->value = value;
            return 1;
        }
        node = node->enext;
    }
    node = new ScriptNode;
    if (node == 0)
        return 0;
    fn_8007D280(node, script, ent, value);
    return 1;
}

int fn_8007D070(register NodeScript *script, int handle)
{
    if (handle == 0)
        return 0;
    NodeEnt *ent = fn_800ACFA8(handle);
    if (ent == 0)
        return 0;
    return fn_8007D0FC(script, ent);
}

int fn_8007D0FC(register NodeScript *script, NodeEnt *ent)
{
    ScriptNode *node = ent->nodes;
    while (node) {
        if (node->script == script && node->ent == ent) {
            ScriptNode *dead = node;
            fn_8007D34C(node);
            delete dead;
            return 1;
        }
        node = node->enext;
    }
    return 0;
}

void fn_8007D1B0(register NodeScript *script)
{
    while (script->nodes) {
        ScriptNode *dead = script->nodes;
        fn_8007D34C(script->nodes);
        delete dead;
    }
    if (script->count != 0) {
    }
}

ScriptNode *fn_8007D220(register ScriptNode *self)
{
    self->script = 0;
    self->ent = 0;
    self->value = 0;
    self->eprev = 0;
    self->enext = 0;
    self->sprev = 0;
    self->snext = 0;
    return self;
}

void fn_8007D280(register ScriptNode *self, NodeScript *script, NodeEnt *ent, int value)
{
    self->script = script;
    self->ent = ent;
    self->value = value;
    if (self->ent->nodes)
        self->ent->nodes->eprev = self;
    self->enext = self->ent->nodes;
    self->eprev = 0;
    self->ent->nodes = self;
    if (self->script->nodes)
        self->script->nodes->sprev = self;
    self->snext = self->script->nodes;
    self->sprev = 0;
    self->script->nodes = self;
    self->script->count++;
}

void fn_8007D34C(register ScriptNode *self)
{
    if (self->enext)
        self->enext->eprev = self->eprev;
    if (self->eprev)
        self->eprev->enext = self->enext;
    else
        self->ent->nodes = self->enext;
    if (self->snext)
        self->snext->sprev = self->sprev;
    if (self->sprev)
        self->sprev->snext = self->snext;
    else
        self->script->nodes = self->snext;
    self->script->count--;
}

ScriptMsg *fn_8007DA10(register int idx);
ScriptMsg *fn_8007DA9C(register ScriptMsg *e);
ScriptMsg *fn_8007DAF8(register ScriptMsg *e);
unsigned char fn_8007DB7C();
int fn_8007DC0C(register int idx);
int fn_8007D594(register ScriptInst *target, unsigned int time, unsigned char kind, float a, float b, float c, float d, int e);

int fn_8007D404(register ScriptInst *target, float delay, unsigned char kind, float a, float b, float c, float d, int e)
{
    return fn_8007D594(target, fn_8042EFF8(lbl_80593BE8) + (unsigned int)(delay * 1000.0f), kind, a, b, c, d, e);
}

int fn_8007D4F4(register ScriptInst *target, unsigned int delay, unsigned char kind, float a, float b, float c, float d, int e)
{
    return fn_8007D594(target, fn_8042EFF8(lbl_80593BE8) + delay, kind, a, b, c, d, e);
}

int fn_8007D594(register ScriptInst *target, unsigned int time, unsigned char kind, float a, float b, float c, float d, int e)
{
    ScriptMsg *msg;
    ScriptMsg *it;
    ScriptMsg *prev;
    unsigned char idx;
    unsigned char next;
    unsigned char pidx;

    if (time >= fn_8042EFF8(lbl_80593BE8) + 600000)
        return 0;
    prev = 0;
    idx = fn_8007DB7C();
    if (idx == 0xFF)
        return 0;
    msg = fn_8007DA10(idx);
    if (msg == 0)
        return 0;
    msg->target = target;
    msg->time = time;
    msg->kind = kind;
    msg->f8 = a;
    msg->fc = b;
    msg->f10 = c;
    msg->f14 = d;
    msg->f18 = e;
    msg->used = 1;
    target->count++;
    lbl_8066B8AC++;
    next = lbl_8066B8B0;
    pidx = 0xFF;
    it = fn_8007DA4C();
    while (it && it->time < msg->time) {
        prev = it;
        pidx = next;
        next = it->next;
        it = fn_8007DA9C(it);
    }
    msg->next = next;
    msg->prev = pidx;
    if (it)
        it->prev = idx;
    if (prev)
        prev->next = idx;
    else
        lbl_8066B8B0 = idx;
    return 1;
}

int fn_8007D7C4(register ScriptInst *target, unsigned char kind)
{
    ScriptMsg *it;
    ScriptMsg *next;
    int found;

    found = 0;
    if (target->count == 0)
        return 0;
    it = fn_8007DA4C();
    while (it) {
        next = fn_8007DA9C(it);
        if (it->target == target && it->kind == kind) {
            target->count--;
            fn_8007D960(it);
            fn_8007DB54(it);
            found = 1;
        }
        it = next;
    }
    return found;
}

int fn_8007D8B0(register ScriptInst *target)
{
    ScriptMsg *it;
    ScriptMsg *next;
    int found;

    found = 0;
    it = fn_8007DA4C();
    while (it) {
        next = fn_8007DA9C(it);
        if (it->target == target) {
            target->count--;
            fn_8007D960(it);
            fn_8007DB54(it);
            found = 1;
        }
        it = next;
    }
    return found;
}

void fn_8007D960(register ScriptMsg *e)
{
    if (fn_8007DA9C(e))
        fn_8007DA9C(e)->prev = e->prev;
    if (fn_8007DAF8(e))
        fn_8007DAF8(e)->next = e->next;
    if (e == fn_8007DA4C())
        lbl_8066B8B0 = e->next;
    lbl_8066B8AC--;
}

ScriptMsg *fn_8007DA10(register int idx)
{
    return &lbl_8054DD80[idx];
}

ScriptMsg *fn_8007DA4C()
{
    return lbl_8066B8B0 != 0xFF ? &lbl_8054DD80[lbl_8066B8B0] : 0;
}

ScriptMsg *fn_8007DA9C(register ScriptMsg *e)
{
    return e->next != 0xFF ? &lbl_8054DD80[e->next] : 0;
}

ScriptMsg *fn_8007DAF8(register ScriptMsg *e)
{
    return e->prev != 0xFF ? &lbl_8054DD80[e->prev] : 0;
}

void fn_8007DB54(register ScriptMsg *e)
{
    e->used = 0;
}

unsigned char fn_8007DB7C()
{
    unsigned char i;

    for (i = 0; i < 128; i++) {
        if (fn_8007DC0C(i))
            return i;
    }
    return 0xFF;
}

int fn_8007DC0C(register int idx)
{
    return lbl_8054DD80[idx].used != 1;
}

}
