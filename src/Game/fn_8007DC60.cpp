// Script notifications: broadcasts to the live instances and the entity event hooks (docs/story.md row 5).
// Literal pool read from 0x80488070 (extern_pool).

inline int sn_return_decl(int a)
{
    return a;
}

class ScriptInst
{
public:
    char pad0[0x14];
    int count;          // +0x14, queued messages
    char pad18[8];
    unsigned int flags; // +0x20
    virtual ~ScriptInst(); // slot 1
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8(unsigned char kind, float a, float b, float c, float d, int e);
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12(int handle);
    virtual void s13(int handle, int value);
    virtual void s14(int handle, int other, int value);
    virtual void s15(int handle, int other, int value);
    virtual void s16(int handle, int other, int value);
    virtual void s17();
    virtual void s18(int handle, int other, int value);
    virtual void s19(int handle, int value);
    virtual int s20(int handle, int other, int a, int b, float f, int value);
    virtual float s21(int handle, int other, int a, int b, float f, int c, int value);
    virtual void s22(int handle, int other, int a, int b, float f, int value);
    virtual void s23(int a, int b, int c, float x, float y, float z, float w, int value);
    virtual void s24(int a, int b, int c, float x, float y, float z, float w);
    virtual void s25();
    virtual void s26();
    virtual void s27(int handle, int other, int a, int b, int value);
    virtual void s28();
    virtual void s29(int handle, int a, int b, int c, int value);
    virtual void s30(int handle, int other, int value);
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual float s37(int handle, int word, int value);
    virtual void s38(int handle, int other, int value);
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43(int handle, int x, int value);
    virtual void s44();
    virtual void s45();
    virtual void s46();
    virtual int s47(int handle, int value);
    virtual int s48(int handle, int value);
    virtual void s49(int handle, int value);
    virtual void s50();
    virtual void s51();
    virtual void s52(int handle, int value, int a, float f);
    virtual void s53(int handle, float f, int a, int b);
    virtual void s54(float f, int a, int b);
    virtual void s55();
    virtual void s56();
    virtual void s57();
    virtual void s58();
    virtual void s59(int handle, int x);
    virtual void s60(int handle);
    virtual void s61(int handle, int x, int value);
    virtual void s62();
    virtual void s63();
};

extern "C" {

extern ScriptInst *lbl_8054D554[]; // the live instances
extern unsigned int lbl_8066D618;
int fn_800B13D8(void *actor);

void fn_8007DC60()
{
    unsigned int i;

    for (i = 0; i < lbl_8066D618; i++) {
        if (lbl_8054D554[i])
            lbl_8054D554[i]->s4();
    }
}

void fn_8007DD34()
{
    unsigned int i;

    for (i = 0; i < lbl_8066D618; i++) {
        if (lbl_8054D554[i])
            lbl_8054D554[i]->s5();
    }
}

void fn_8007DE08(void *actor)
{
    unsigned int i;

    for (i = 0; i < lbl_8066D618; i++) {
        if (lbl_8054D554[i])
            lbl_8054D554[i]->s60(fn_800B13D8(actor));
    }
}

void fn_8007DEF0()
{
    unsigned int i;

    for (i = 0; i < lbl_8066D618; i++) {
        if (lbl_8054D554[i])
            lbl_8054D554[i]->s6();
    }
}

void fn_8007DFC4()
{
    unsigned int i;

    for (i = 0; i < lbl_8066D618; i++) {
        if (lbl_8054D554[i] && (lbl_8054D554[i]->flags & 1))
            lbl_8054D554[i]->s63();
    }
}

void fn_8007E0C0(ScriptInst *target, unsigned char kind, float a, float b, float c, float d, int e)
{
    target->s8(kind, a, b, c, d, e);
}

struct InstNode {
    ScriptInst *script; // +0x0
    void *ent;          // +0x4
    int value;          // +0x8
    InstNode *eprev;    // +0xC
    InstNode *enext;    // +0x10
};

struct InstEnt {
    char pad[0x14C];
    ScriptInst *script; // +0x14C
    InstNode *nodes;    // +0x150
};

void fn_8007E160(InstEnt *ent)
{
    if (ent->script)
        ent->script->s12(fn_800B13D8(ent));
}

void fn_8007E1EC(InstEnt *ent)
{
    InstNode *node;

    if (ent->script)
        ent->script->s13(fn_800B13D8(ent), 0);
    node = ent->nodes;
    while (node) {
        node->script->s13(fn_800B13D8(ent), node->value);
        node = node->enext;
    }
}

void fn_8007E2FC(InstEnt *ent, void *other)
{
    InstNode *node;

    if (ent->script)
        ent->script->s14(fn_800B13D8(ent), fn_800B13D8(other), 0);
    node = ent->nodes;
    while (node) {
        node->script->s14(fn_800B13D8(ent), fn_800B13D8(other), node->value);
        node = node->enext;
    }
}

void fn_8007E430(InstEnt *ent, void *other)
{
    InstNode *node;

    if (ent->script)
        ent->script->s15(fn_800B13D8(ent), fn_800B13D8(other), 0);
    node = ent->nodes;
    while (node) {
        node->script->s15(fn_800B13D8(ent), fn_800B13D8(other), node->value);
        node = node->enext;
    }
}

void fn_8007E564(InstEnt *ent, void *other)
{
    InstNode *node;

    if (ent->script)
        ent->script->s16(fn_800B13D8(ent), fn_800B13D8(other), 0);
    node = ent->nodes;
    while (node) {
        node->script->s16(fn_800B13D8(ent), fn_800B13D8(other), node->value);
        node = node->enext;
    }
}

float fn_8007E698(InstEnt *ent, void *other, int a, int b, float f, int c)
{
    int h = other ? fn_800B13D8(other) : 0;
    float r = f;
    InstNode *node;

    if (ent->script)
        r = ent->script->s21(fn_800B13D8(ent), h, a, b, f, c, 0);
    node = ent->nodes;
    while (node) {
        if (r < 0.0f)
            return 0.0f;
        r = node->script->s21(fn_800B13D8(ent), h, a, b, f, c, node->value);
        node = node->enext;
    }
    return r;
}

int fn_8007E84C(InstEnt *ent, void *other, int a, int b, float f)
{
    int h = other ? fn_800B13D8(other) : 0;
    int ok = 1;
    InstNode *node;

    if (ent->script)
        ok = ent->script->s20(fn_800B13D8(ent), h, a, b, f, 0);
    if (ok == 0)
        return 0;
    node = ent->nodes;
    while (node) {
        ok = node->script->s20(fn_800B13D8(ent), h, a, b, f, 0);
        if (ok == 0)
            return 0;
        node = node->enext;
    }
    return 1;
}

InstEnt *fn_800ACFA8(int handle);
extern int lbl_8066B894;

void fn_8007E9F4(InstEnt *ent, void *other, int a, int b, float f)
{
    int h = other ? fn_800B13D8(other) : 0;
    InstNode *node;
    InstEnt *master;

    if (ent->script)
        ent->script->s22(fn_800B13D8(ent), h, a, b, f, 0);
    node = ent->nodes;
    while (node) {
        node->script->s22(fn_800B13D8(ent), h, a, b, f, node->value);
        node = node->enext;
    }
    master = fn_800ACFA8(lbl_8066B894);
    if (master && master->script)
        master->script->s22(fn_800B13D8(ent), h, a, b, f, 0);
}

void fn_8007EBE4(InstEnt *ent, void *other)
{
    InstNode *node;

    if (ent->script)
        ent->script->s30(fn_800B13D8(ent), fn_800B13D8(other), 0);
    node = ent->nodes;
    while (node) {
        node->script->s30(fn_800B13D8(ent), fn_800B13D8(other), node->value);
        node = node->enext;
    }
}

void fn_8007ED18(InstEnt *ent, int a, int b, int c, float x, float y, float z, float w)
{
    InstNode *node;

    if (ent->script)
        ent->script->s23(a, b, c, x, y, z, w, 0);
    node = ent->nodes;
    while (node) {
        node->script->s23(a, b, c, x, y, z, w, node->value);
        node = node->enext;
    }
}

void *fn_8043E450(int a, int b);

void fn_8007EE5C(InstEnt *ent, int a, int b)
{
    void *o = fn_8043E450(a, b);
    InstNode *node;

    if (ent->script)
        ent->script->s27(fn_800B13D8(ent), o ? fn_800B13D8(o) : 0, a, b, 0);
    node = ent->nodes;
    while (node) {
        node->script->s27(fn_800B13D8(ent), o ? fn_800B13D8(o) : 0, a, b, node->value);
        node = node->enext;
    }
}

float fn_8007EFE0(InstEnt *ent, int word)
{
    float r = -1.0f;
    float v;
    InstNode *node;

    if (ent->script)
        r = ent->script->s37(fn_800B13D8(ent), word, 0);
    node = ent->nodes;
    while (node) {
        v = node->script->s37(fn_800B13D8(ent), word, node->value);
        if (v == 0.0f)
            r = 0.0f;
        else
            r = r != -1.0f ? (r < v ? r : v) : v;
        node = node->enext;
    }
    return r;
}

void fn_8007F184(InstEnt *ent, void *other)
{
    int h = 0;
    if (other)
        h = fn_800B13D8(other);
    InstNode *node;

    if (ent->script)
        ent->script->s38(fn_800B13D8(ent), h, 0);
    node = ent->nodes;
    while (node) {
        node->script->s38(fn_800B13D8(ent), h, node->value);
        node = node->enext;
    }
}

void fn_8007F2C4(InstEnt *ent, int x)
{
    InstNode *node;

    if (ent->script)
        ent->script->s43(fn_800B13D8(ent), x, 0);
    node = ent->nodes;
    while (node) {
        node->script->s43(fn_800B13D8(ent), x, node->value);
        node = node->enext;
    }
}

int fn_8007F3E0(InstEnt *ent)
{
    int ok = 1;
    InstNode *node;

    if (ent->script)
        ok = ent->script->s47(fn_800B13D8(ent), 0);
    if (ok == 0)
        return 0;
    node = ent->nodes;
    while (node) {
        ok = node->script->s47(fn_800B13D8(ent), node->value);
        if (ok == 0)
            return 0;
        node = node->enext;
    }
    return 1;
}

int fn_8007F538(InstEnt *ent)
{
    int ok = 1;
    InstNode *node;

    if (ent->script)
        ok = ent->script->s48(fn_800B13D8(ent), 0);
    if (ok == 0)
        return 0;
    node = ent->nodes;
    while (node) {
        ok = node->script->s48(fn_800B13D8(ent), node->value);
        if (ok == 0)
            return 0;
        node = node->enext;
    }
    return 1;
}

void fn_8007F690(InstEnt *ent)
{
    InstNode *node;

    if (ent->script)
        ent->script->s49(fn_800B13D8(ent), 0);
    node = ent->nodes;
    while (node) {
        node->script->s49(fn_800B13D8(ent), node->value);
        node = node->enext;
    }
}

void fn_8007F7A0(InstEnt *ent, int a, float f)
{
    InstNode *node;

    if (ent->script)
        ent->script->s52(fn_800B13D8(ent), 0, a, f);
    node = ent->nodes;
    while (node) {
        node->script->s52(fn_800B13D8(ent), node->value, a, f);
        node = node->enext;
    }
}

void fn_8007F8C8(ScriptInst *script, void *ent, float f, int a, int b)
{
    script->s53(fn_800B13D8(ent), f, a, b);
}

void fn_8007F958(ScriptInst *script, float f, int a, int b)
{
    script->s54(f, a, b);
}

void fn_8007F9D4(InstEnt *ent, int x)
{
    InstNode *node;

    if (ent->script)
        ent->script->s59(fn_800B13D8(ent), x);
    node = ent->nodes;
    while (node) {
        node->script->s59(fn_800B13D8(ent), x);
        node = node->enext;
    }
}

void fn_8007FAE4(InstEnt *ent, int x)
{
    InstNode *node;

    if (ent->script)
        ent->script->s61(fn_800B13D8(ent), x, 0);
    node = ent->nodes;
    while (node) {
        node->script->s61(fn_800B13D8(ent), x, node->value);
        node = node->enext;
    }
}

void fn_8007FC00(InstEnt *ent, int a, int b, int c)
{
    InstNode *node;

    if (ent->script)
        ent->script->s29(fn_800B13D8(ent), a, b, c, 0);
    node = ent->nodes;
    while (node) {
        node->script->s29(fn_800B13D8(ent), a, b, c, node->value);
        node = node->enext;
    }
}

void fn_8007FD34(InstEnt *ent, void *other)
{
    InstNode *node;

    if (ent->script)
        ent->script->s18(fn_800B13D8(ent), fn_800B13D8(other), 0);
    node = ent->nodes;
    while (node) {
        node->script->s18(fn_800B13D8(ent), fn_800B13D8(other), node->value);
        node = node->enext;
    }
}

void fn_8007FE68()
{
    unsigned int i;

    for (i = 0; i < lbl_8066D618; i++) {
        if (lbl_8054D554[i])
            lbl_8054D554[i]->s31();
    }
}

void fn_8007FF3C()
{
    unsigned int i;

    for (i = 0; i < lbl_8066D618; i++) {
        if (lbl_8054D554[i])
            lbl_8054D554[i]->s32();
    }
}

void fn_80080010()
{
    unsigned int i;

    for (i = 0; i < lbl_8066D618; i++) {
        if (lbl_8054D554[i])
            lbl_8054D554[i]->s33();
    }
}

void fn_800800E4(int a, int b, int c, float x, float y, float z, float w)
{
    unsigned int i;

    for (i = 0; i < lbl_8066D618; i++) {
        if (lbl_8054D554[i])
            lbl_8054D554[i]->s24(a, b, c, x, y, z, w);
    }
}

void fn_800801F0(InstEnt *ent)
{
    InstNode *node;

    if (ent->script)
        ent->script->s19(fn_800B13D8(ent), 0);
    node = ent->nodes;
    while (node) {
        node->script->s19(fn_800B13D8(ent), node->value);
        node = node->enext;
    }
}

struct HActor;
struct HShapeInner {
    char pad[0x1C];
    int f1c; // +0x1C
};
struct HShape {
    char pad[0xB0];
    HShapeInner *fb0; // +0xB0
};

HActor *fn_800ACFA8A(int handle) __asm__("fn_800ACFA8");
int fn_804425F8(int handle);
int fn_8010CDCC(HActor *a, int id, void *e, int b, int c, int d, int f);
int fn_80097CE8(HActor *a, int anim, int mode, float speed, int set, float blend, float f);
HShape *fn_8009AD80(HActor *a);
void fn_8009AF28(HActor *a);
void fn_8019DB24(HShapeInner *p, float t);
void fn_80434864(HShape *p, int x);

HActor *fn_80080300(register int handle)
{
    HActor &a = *fn_800ACFA8A(fn_804425F8(handle));
    return &a;
}

int fn_80080358(register int handle, int id)
{
    HActor *a = fn_80080300(handle);
    if (a == 0)
        return 0;
    return fn_8010CDCC(a, id, 0, 0, 500, 0, 0);
}

}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.text"); // 0x8048807C-0x804880A0, "%s (guid=%d)" and "%s %s (guid=%d)"

extern "C" {

int fn_800803DC(register int handle, int anim, float speed)
{
    HActor *a = fn_80080300(handle);
    if (a == 0)
        return -2;
    return fn_80097CE8(a, anim, 1, speed, 0, 7.5f, -1.0f);
}

int fn_8008046C(register int handle, int anim, float speed)
{
    HActor *a = fn_80080300(handle);
    if (a == 0)
        return -2;
    return fn_80097CE8(a, anim, 0, speed, 0, 7.5f, -1.0f);
}

int fn_800804FC(register int handle)
{
    HActor *a = fn_80080300(handle);
    if (a == 0)
        return 0;
    if (fn_8009AD80(a) == 0)
        return 0;
    if (fn_8009AD80(a)->fb0 == 0)
        return 0;
    fn_8009AF28(a);
    return 1;
}

void fn_8008059C(register int handle, float t)
{
    HActor *a = fn_80080300(handle);
    if (a == 0)
        return;
    if (fn_8009AD80(a) == 0)
        return;
    if (fn_8009AD80(a)->fb0 == 0)
        return;
    if (fn_8009AD80(a)->fb0->f1c == 0)
        return;
    fn_8019DB24(fn_8009AD80(a)->fb0, t);
}

void fn_8008065C(register int handle, int x)
{
    HActor *a = fn_80080300(handle);
    if (a == 0)
        return;
    if (fn_8009AD80(a) == 0)
        return;
    fn_80434864(fn_8009AD80(a), x);
}

}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.text"); // 0x804880B0-0x804880C8

class HVec2
{
public:
    float x, y;
    HVec2() __asm__("fn_80426A2C");
};

extern "C" {

void fn_80426A54(HVec2 *v, float x, float y);
void *fn_801A5A0C(HShape *s, int name, int i);
int fn_80236760(void *p);
void fn_8022D9A8(void *p, int y, HVec2 *v, float t);

int fn_800806E0(register int handle, int name, int y, float fx, float fy, float t, int idx)
{
    HActor *a = fn_80080300(handle);
    if (a == 0)
        return 0;
    if (fn_8009AD80(a) == 0)
        return 0;
    if (t < 0.0f)
        t = 0.0f;
    if (idx < -1)
        idx = -1;
    HVec2 v;
    fn_80426A54(&v, fx, fy);
    void *p;
    int i = 0;
    int found = 0;
    if (idx == -1) {
    next:
        p = fn_801A5A0C(fn_8009AD80(a), name, i);
        if (p == 0)
            goto done;
        i++;
        if (fn_80236760(p) != 0x17)
            goto next;
        fn_8022D9A8(p, y, &v, t);
        found = 1;
        goto next;
    done:;
    } else {
        p = fn_801A5A0C(fn_8009AD80(a), name, i);
        if (p && fn_80236760(p) == 0x17) {
            fn_8022D9A8(p, y, &v, t);
            found = 1;
        }
    }
    return found;
}

}
