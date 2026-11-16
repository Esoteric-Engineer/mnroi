// Script class table and base class methods (docs/story.md row 4, section 4.1).
// Literal pool read from 0x80487C80 (extern_pool). The base virtuals follow the static init, in slot order.

inline int sn_return_decl(int a)
{
    return a;
}

class cScript;

struct ScriptClass { // 0x28
    char name[0x20];
    cScript *prototype; // +0x20
    int count;          // +0x24, live instances
};

struct ScriptLink { // 8
    int type;
    union {
        void *p; // +0x4
        int v;
        unsigned int u;
        float f;
        char *str;
    };
};

class cScript
{
public:
    ScriptClass *entry;  // +0x0
    int id;              // +0x4
    cScript *owner;      // +0x8
    unsigned int nlinks; // +0xc
    ScriptLink *links;   // +0x10
    int f14;             // +0x14
    int f18;             // +0x18
    int f1c;             // +0x1c
    int f20;             // +0x20
    cScript() __asm__("fn_80441FAC");
    virtual ~cScript();          // slot 1
    virtual cScript *clone();    // slot 2
    virtual void slot3();        // slot 3
};

extern "C" {

void *fn_801B4284(int capacity, char *name);
void *fn_801B48AC(void *table, char *name);
void fn_801ACC0C(void *p);
void fn_8007D1B0(cScript *self);
void fn_8007D8B0(cScript *self);
ScriptClass *fn_8007A2C4(cScript *self);
void fn_8007A2F0(cScript *self, ScriptClass *entry);
void fn_80078FDC(cScript *self, cScript *owner);
int fn_800B13D8(cScript *actor);
int atoi(const char *s);
double atof(const char *s);
int sprintf(char *buf, const char *fmt, ...);

extern char lbl_8054DD54[];
extern char lbl_8054D130[]; // Sub24
extern char lbl_8066D5FC[];
extern char lbl_8066D604[];
extern char lbl_8066D60C[];
extern char lbl_804F4810[]; // the base vtable

void fn_801B54E8(void *self, int n, float f);
void Sub24_dtor(void *self, int flags) __asm__("_._5Sub24");
int *fn_80441FE0(void *self, int a);
void __builtin_delete(void *p);

extern int lbl_8066B898;
extern void *lbl_8066D614;
extern unsigned int lbl_8066D618;
extern int lbl_8066D61C;
extern cScript *lbl_8054D554[];

int fn_8007891C()
{
    if (lbl_8066B898 != 0)
        return 0;
    lbl_8066D614 = fn_801B4284(0x3F, "ScriptClasses");
    lbl_8066D618 = 0;
    lbl_8066D61C = 1;
    lbl_8066B898 = 1;
    return 1;
}

ScriptClass *fn_80078994(char *name)
{
    return (ScriptClass *)fn_801B48AC(lbl_8066D614, name);
}

cScript *fn_800789DC(char *name, int init)
{
    cScript *copy;
    ScriptClass *entry;
    cScript *proto;

    copy = 0;
    entry = fn_80078994(name);
    if (entry == 0)
        return 0;
    proto = entry->prototype;
    if (proto == 0)
        return 0;
    copy = proto->clone();
    if (copy != 0) {
        fn_8007A2F0(copy, entry);
        copy->nlinks = 0;
        copy->links = 0;
        copy->f14 = 0;
        copy->f18 = 0;
        copy->f1c = 0;
        if (init != 0)
            fn_80078FDC(copy, 0);
    }
    return copy;
}

void fn_80078CE0(cScript *self);

void fn_80078B10(cScript *self)
{
    unsigned int i;
    ScriptLink *link;

    fn_8007D1B0(self);
    fn_8007D8B0(self);
    fn_80078CE0(self);
    if (self->links != 0) {
        for (i = 0; i < self->nlinks; i++) {
            link = &self->links[i];
            if (link->p != 0 && (link->type == 7 || link->type == 8 || link->type == 9))
                fn_801ACC0C(link->p);
        }
        fn_801ACC0C(self->links);
    }
    delete self;
}

void fn_80078C58(cScript *self)
{
    lbl_8054D554[lbl_8066D618++] = self;
    if (fn_8007A2C4(self) != 0)
        fn_8007A2C4(self)->count++;
}

void fn_80078CE0(cScript *self)
{
    unsigned int i;

    for (i = 0; i < lbl_8066D618; i++) {
        if (lbl_8054D554[i] == self) {
            lbl_8054D554[i] = lbl_8054D554[--lbl_8066D618];
            if (fn_8007A2C4(self) != 0)
                fn_8007A2C4(self)->count--;
            return;
        }
    }
    return;
}

cScript *fn_80078DD4(register cScript *self)
{
    return new cScript;
}

struct ScriptSource {
    char pad[0x14C];
    cScript *links; // +0x14C
};

void fn_80078E28(register cScript *self, ScriptSource *src, cScript **map)
{
    cScript *list;
    unsigned int i;
    cScript *t;

    list = src->links;
    for (i = 0; i < list->nlinks; i++) {
        switch (list->links[i].type) {
        case 3:
        case 5:
        case 10:
        case 11:
        case 12:
        case 13:
            switch (list->links[i].v) {
            case -2:
                list->links[i].v = 0;
                break;
            case -1:
                list->links[i].v = 0;
                break;
            default:
                t = map[list->links[i].v];
                if (t != 0)
                    list->links[i].v = fn_800B13D8(t);
            }
            break;
        }
    }
}

void fn_80078FDC(register cScript *self, cScript *owner)
{
    self->id = lbl_8066D61C++;
    self->owner = owner;
    fn_80078C58(self);
    self->slot3();
}

int fn_80079068(register cScript *self, unsigned int i)
{
    if (i >= self->nlinks)
        return 0;
    switch (self->links[i].type) {
    case 1:
        return self->links[i].v;
    case 3:
    case 5:
    case 10:
    case 11:
    case 12:
    case 13:
        return self->links[i].v;
    case 2:
        return (int)self->links[i].f;
    case 7:
    case 8:
    case 9:
        return atoi(self->links[i].str);
    default:
        return 0;
    }
}

unsigned int fn_800791C8(register cScript *self, unsigned int i)
{
    if (i >= self->nlinks)
        return 0;
    switch (self->links[i].type) {
    case 1:
        return self->links[i].u;
    case 3:
    case 5:
    case 10:
    case 11:
    case 12:
    case 13:
        return self->links[i].u;
    case 2:
        return (unsigned int)self->links[i].f;
    case 7:
    case 8:
    case 9:
        return atoi(self->links[i].str);
    default:
        return 0;
    }
}

float fn_8007935C(register cScript *self, unsigned int i)
{
    if (i >= self->nlinks)
        return 0.0f;
    switch (self->links[i].type) {
    case 1:
        return self->links[i].v;
    case 3:
    case 5:
    case 10:
    case 11:
    case 12:
    case 13:
        return self->links[i].u;
    case 2:
        return self->links[i].f;
    case 7:
    case 8:
    case 9:
        return atof(self->links[i].str);
    default:
        return 0.0f;
    }
}

char *fn_800794FC(register cScript *self, unsigned int i)
{
    if (i >= self->nlinks)
        return "Invalid Param";
    switch (self->links[i].type) {
    case 1:
        sprintf(lbl_8054DD54, "%d", self->links[i].v);
        return lbl_8054DD54;
    case 3:
    case 5:
    case 10:
    case 11:
    case 12:
    case 13:
        sprintf(lbl_8054DD54, "%u", self->links[i].u);
        return lbl_8054DD54;
    case 2:
        sprintf(lbl_8054DD54, "%f", self->links[i].f);
        return lbl_8054DD54;
    case 7:
    case 8:
    case 9:
        return self->links[i].str;
    default:
        return 0;
    }
}

void fn_800796A4(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            fn_801B54E8(lbl_8054D130, 0x19, 0.2f);
            fn_80441FE0(lbl_8066D5FC, 0);
            fn_80441FE0(lbl_8066D604, 1);
            fn_80441FE0(lbl_8066D60C, 2);
        } else {
            Sub24_dtor(lbl_8054D130, 2);
        }
    }
}

}

inline int sn_return_decl2(int a)
{
    return a;
}

struct cScriptVptr {
    char pad[0x24];
    void *vptr; // +0x24
};

extern "C" {

void fn_8007975C(register cScript *self, register int inChrg) // slot 1
{
    ((cScriptVptr *)self)->vptr = lbl_804F4810;
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}

void fn_800797B4(register cScript *self) // slot 3
{
}

cScript *fn_800797D4(register cScript *self)
{
    return self->owner;
}

void fn_80079800(register cScript *self) // slot 4
{
    return;
}

void fn_80079824(register cScript *self) // slot 5
{
    return;
}

void fn_80079848(register cScript *self) // slot 6
{
    return;
}

void fn_8007986C(register cScript *self) // slot 7
{
    return;
}

void fn_80079890(register cScript *self, register int a0, register float f1, register float f2, register float f3, register float f4, register int a5) // slot 8
{
    return;
}

int fn_800798CC(register cScript *self, register int a0, register int a1, register int a2, register int a3) // slot 9
{
    return 1;
}

void fn_80079904(register cScript *self, register int a0, register int a1) // slot 10
{
    return;
}

void fn_80079930(register cScript *self, register int a0, register int a1, register int a2) // slot 11
{
    return;
}

void fn_80079960(register cScript *self, register int a0) // slot 12
{
    return;
}

void fn_80079988(register cScript *self, register int a0, register int a1) // slot 13
{
    return;
}

void fn_800799B4(register cScript *self, register int a0, register int a1, register int a2) // slot 14
{
    return;
}

void fn_800799E4(register cScript *self, register int a0, register int a1, register int a2) // slot 15
{
    return;
}

void fn_80079A14(register cScript *self, register int a0, register int a1, register int a2) // slot 16
{
    return;
}

int fn_80079A44(register cScript *self, register int a0, register int a1, register int a2) // slot 17
{
    return 0;
}

void fn_80079A78(register cScript *self, register int a0, register int a1, register int a2) // slot 18
{
    return;
}

void fn_80079AA8(register cScript *self, register int a0, register int a1) // slot 19
{
    return;
}

int fn_80079AD4(register cScript *self, register int a0, register int a1, register int a2, register float f3) // slot 20
{
    return 1;
}

float fn_80079B0C(register cScript *self, register int a0, register int a1, register int a2, register int a3, register float f4, register int a5, register int a6) // slot 21
{
    return f4;
}

void fn_80079B40(register cScript *self, register int a0, register int a1, register int a2, register float f3) // slot 22
{
    return;
}

void fn_80079B74(register cScript *self, register int a0, register int a1, register int a2, register float f3, register float f4, register float f5, register float f6, register int a7) // slot 23
{
    return;
}

void fn_80079BB8(register cScript *self, register int a0, register int a1, register int a2, register float f3, register float f4, register float f5, register float f6) // slot 24
{
    return;
}

void fn_80079BF8(register cScript *self, register int a0, register int a1, register int a2) // slot 25
{
    return;
}

int fn_80079C28(register cScript *self, register int a0, register int a1, register int a2, register int a3) // slot 26
{
    return 1;
}

void fn_80079C60(register cScript *self, register int a0, register int a1, register int a2) // slot 27
{
}

void fn_80079C8C(register cScript *self, register int a0, register int a1) // slot 28
{
    return;
}

void fn_80079CB8(register cScript *self, register int a0, register int a1, register int a2) // slot 29
{
    return;
}

void fn_80079CE8(register cScript *self, register int a0, register int a1, register int a2) // slot 30
{
    return;
}

void fn_80079D18(register cScript *self) // slot 31
{
    return;
}

void fn_80079D3C(register cScript *self) // slot 32
{
    return;
}

void fn_80079D60(register cScript *self) // slot 33
{
    return;
}

void fn_80079D84(register cScript *self) // slot 34
{
    return;
}

void fn_80079DA8(register cScript *self) // slot 35
{
    return;
}

void fn_80079DCC(register cScript *self) // slot 36
{
    return;
}

float fn_80079DF0(register cScript *self, register int a0, register int a1, register int a2) // slot 37
{
    return -1.0f;
}

void fn_80079E28(register cScript *self, register int a0, register int a1, register int a2) // slot 38
{
    return;
}

void fn_80079E58(register cScript *self, register int a0, register int a1) // slot 39
{
    return;
}

void fn_80079E84(register cScript *self, register int a0, register int a1) // slot 40
{
    return;
}

void fn_80079EB0(register cScript *self, register int a0, register int a1) // slot 41
{
    return;
}

void fn_80079EDC(register cScript *self, register int a0, register int a1, register int a2) // slot 42
{
    return;
}

void fn_80079F0C(register cScript *self, register int a0, register int a1, register int a2) // slot 43
{
    return;
}

void fn_80079F3C(register cScript *self, register int a0, register int a1) // slot 44
{
    return;
}

void fn_80079F68(register cScript *self, register int a0, register int a1) // slot 45
{
    return;
}

void fn_80079F94(register cScript *self, register int a0, register int a1) // slot 46
{
    return;
}

int fn_80079FC0(register cScript *self, register int a0, register int a1) // slot 47
{
    return 1;
}

int fn_80079FF0(register cScript *self, register int a0, register int a1) // slot 48
{
    return 1;
}

void fn_8007A020(register cScript *self, register int a0, register int a1) // slot 49
{
    return;
}

void fn_8007A04C(register cScript *self, register int a0, register int a1, register int a2) // slot 50
{
    return;
}

void fn_8007A07C(register cScript *self, register int a0, register int a1, register int a2, register float f3, register float f4, register float f5) // slot 51
{
    return;
}

void fn_8007A0B8(register cScript *self, register int a0, register int a1, register int a2, register float f3) // slot 52
{
}

void fn_8007A0E8(register cScript *self, register int a0, register float f1, register int a2, register int a3) // slot 53
{
}

void fn_8007A118(register cScript *self, register float f0, register int a1, register int a2) // slot 54
{
}

void fn_8007A144(register cScript *self, register int a0) // slot 55
{
}

void fn_8007A168(register cScript *self, register int a0, register int a1, register int a2) // slot 56
{
    return;
}

void fn_8007A198(register cScript *self, register int a0, register int a1, register int a2) // slot 57
{
    return;
}

void fn_8007A1C8(register cScript *self, register int a0, register int a1, register int a2) // slot 58
{
    return;
}

void fn_8007A1F8(register cScript *self, register int a0, register int a1) // slot 59
{
    return;
}

void fn_8007A224(register cScript *self, register int a0) // slot 60
{
    return;
}

void fn_8007A24C(register cScript *self, register int a0, register int a1, register int a2) // slot 61
{
}

void fn_8007A278(register cScript *self, register int a0, register int a1) // slot 62
{
}

void fn_8007A2A0(register cScript *self) // slot 63
{
    return;
}

ScriptClass *fn_8007A2C4(register cScript *self)
{
    return self->entry;
}

void fn_8007A2F0(register cScript *self, register ScriptClass *entry)
{
    self->entry = entry;
}

}

inline void sn_label_decl() { clear:; } // the pair on the two wrappers (prodg.md)

extern "C" {

void fn_8007A318(void)
{
    fn_800796A4(1, 65535);
}

void fn_8007A35C(void)
{
    fn_800796A4(0, 65535);
}

}

static void (*const sCtorEntry)(void) __attribute__((section(".ctors"))) = fn_8007A318;
static void (*const sDtorEntry)(void) __attribute__((section(".dtors"))) = fn_8007A35C;
