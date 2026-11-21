// Script commands on actors by handle, and the script globals' static init (docs/story.md row 5).
// Literal pool read from 0x80488190 (extern_pool).

inline int sn_return_decl(int a)
{
    return a;
}

extern "C" {

struct SActor;
struct SEnt;

SActor *fn_800ACFA8(int handle);
int fn_804425F8(int handle);
SActor *fn_80081E6C(int handle);
int fn_800B0C1C(SActor *a);
void *fn_800B24AC(SActor *a);
void fn_8043C0C8(void *p);
void fn_8043E4D4(void *p);
int fn_80095608(SActor *a);
extern char lbl_80552110[];
SEnt *fn_80432924(void *game);
void *fn_804328E0(void *game);
char fn_80442624(void *p);
int fn_800B13D8(SEnt *e);

SActor *fn_800808D0(register int handle)
{
    SActor &a = *fn_800ACFA8(fn_804425F8(handle));
    return &a;
}

void fn_80080928(register int handle, int on)
{
    SActor *a = fn_800808D0(handle);
    if (a == 0)
        return;
    if (fn_800B24AC(a) == 0)
        return;
    if (on)
        fn_8043C0C8(fn_800B24AC(a));
    else
        fn_8043E4D4(fn_800B24AC(a));
}

SActor *fn_800809CC(register int handle)
{
    SActor *a = fn_80081E6C(handle);
    if (!a || !fn_800B0C1C(a))
        return 0;
    return a;
}

int fn_80080A44(register int handle)
{
    SActor *a = fn_800809CC(handle);
    if (a == 0)
        return 0;
    if (fn_80095608(a) == 0)
        return 0;
    return 1;
}

char fn_80080ABC()
{
    if (fn_80432924(lbl_80552110)) {
        return fn_80442624(fn_804328E0(lbl_80552110));
    } else {
        return 0;
    }
}

int fn_80080B34()
{
    if (fn_80432924(lbl_80552110)) {
        register SEnt *e = fn_80432924(lbl_80552110);
        return fn_800B13D8(e);
    } else {
        return 0;
    }
}

int fn_800B0DA0(SActor *a);
int fn_800B0CC0(SActor *a);
int fn_8009AC94(SActor *a);
int fn_800A3E54(SActor *a);
void fn_800A3E80(SActor *a, int v);
void fn_800A3EB0(SActor *a, int v);
int fn_800A4508(SActor *a);

SActor *fn_80080BA8(register int handle)
{
    SActor *a = fn_80081E6C(handle);
    if (!a || !fn_800B0DA0(a))
        return 0;
    return a;
}

int fn_80080C20(register int handle)
{
    SActor *a = fn_80080BA8(handle);
    if (a == 0)
        return 0;
    return fn_8009AC94(a);
}

}

class SVector
{
public:
    float x, y, z, w;
    SVector() __asm__("__6Vector");
} __attribute__((aligned(8)));

class SMat4
{
public:
    float m[4][4];
    SMat4() __asm__("fn_8042D7B0");
};

struct SObj {
    char pad[0x2D0];
    SVector vel; // +0x2D0
};

extern "C" {

int fn_801BC9DC(SVector *from, SVector *to, float speed, float g, float *t);
void *fn_800FD5FC(void *name, int x);
void fn_80429038(SVector *out, SVector *a, SVector *b);
void fn_8042F76C(SVector *v);
float *fn_8042FB28(SVector *v);
float fn_8042FE6C(SVector *v);
extern char lbl_80593DD0[];
void fn_801BEBBC(SVector *a, void *b, SVector *c);
void fn_801BC080(SMat4 *m, SVector *v);
void fn_8042DC84(void *dst, void *src);
SObj *fn_800503B8(void *tmpl, SMat4 *m, SActor *owner, int h, int a, int b, int c, int d);
void fn_8006683C(SObj *o, SActor *owner);
void fn_8042FDBC(SVector *out, SVector *v, float f);
void fn_80065CB0(SObj *o, SVector *v);
void fn_80065AF8(SObj *o, int a, int b);
void fn_8009FDC4(SObj *o, int a);
int fn_800B13D8A(void *e) __asm__("fn_800B13D8");

int fn_80080C88(void *name, SVector *from, SVector *to, float speed, int handle)
{
    float t;
    void *tmpl;

    if (!fn_801BC9DC(from, to, speed, 20.0f, &t))
        return 0;
    tmpl = fn_800FD5FC(name, 0);
    if (tmpl == 0)
        return 0;
    SVector dir;
    fn_80429038(&dir, to, from);
    fn_8042F76C(&dir);
    SVector v;
    *fn_8042FB28(&v) = speed;
    fn_8042FB28(&v)[2] = fn_8042FE6C(&dir);
    fn_8042FB28(&v)[1] = 0.0f;
    fn_801BEBBC(&dir, lbl_80593DD0, &v);
    SMat4 m;
    fn_801BC080(&m, &dir);
    fn_8042DC84((char *)&m + 0x30, from);
    SActor *owner = fn_800ACFA8(handle);
    SObj *obj = fn_800503B8(tmpl, &m, owner, owner ? fn_800B13D8A(owner) : 0, 0, 0, 0, 1);
    if (obj == 0)
        return 0;
    if (owner)
        fn_8006683C(obj, owner);
    fn_8042FDBC(&obj->vel, &dir, t);
    fn_80065CB0(obj, &obj->vel);
    fn_80065AF8(obj, 1, 0);
    fn_8009FDC4(obj, 1);
    return fn_800B13D8A(obj);
}

SActor *fn_80080EFC(register int handle)
{
    SActor *a = fn_80081E6C(handle);
    if (!a || !fn_800B0CC0(a))
        return 0;
    return a;
}

int fn_80080F74(register int handle, int v)
{
    SActor *a = fn_80080EFC(handle);
    if (a == 0)
        return -1;
    int old = fn_800A3E54(a);
    fn_800A3E80(a, v);
    return old;
}

int fn_80080FF4(register int handle, int v)
{
    SActor *a = fn_80080EFC(handle);
    if (a == 0)
        return -1;
    int old = fn_800A3E54(a);
    fn_800A3EB0(a, v);
    return old;
}

int fn_80081074(register int handle)
{
    SActor *a = fn_80080EFC(handle);
    if (a == 0)
        return 0;
    return fn_800A4508(a);
}

}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.text"); // 0x80488198-0x804881C0

extern "C" {

float fn_800A2F94(SActor *a, SActor *src, int kind, int type, float dmg, int b, int c, float f, int flags);
int fn_800B0D64(SActor *a);
void fn_8009B83C(SActor *a, int v);

float fn_800810DC(register int handle, float dmg, int type, int kind, int src, int flags)
{
    SActor *a = fn_80080EFC(handle);
    if (a == 0)
        return -1.0f;
    SActor *s = fn_800ACFA8(src);
    return fn_800A2F94(a, s, kind, type, dmg, 0, 0, 0.0f, flags);
}

SActor *fn_80081190(register int handle)
{
    SActor *a = fn_80081E6C(handle);
    if (!a || !fn_800B0D64(a))
        return 0;
    return a;
}

int fn_80081208(register int handle, int v)
{
    SActor *a = fn_80081190(handle);
    if (a == 0)
        return 0;
    fn_8009B83C(a, v);
    return 1;
}

struct SItem { // 0x1C0
    int f0;
    unsigned int flags; // +0x4
    char pad8[0x1B8];
};

struct SPoint { // 0x50
    char pad0[8];
    int type; // +0x8
    char padC[0x44];
};

struct SItemOwner {
    char pad0[0x10];
    unsigned int npoints; // +0x10
    char pad14[0x118];
    SItem *items;         // +0x12C
    char pad130[0xC];
    SPoint *points;       // +0x13C
};

extern char lbl_8052F060[];
SItemOwner *fn_80430050(void *p);
unsigned int fn_80442680(int handle);
unsigned int fn_80442654(SItemOwner *o);
int fn_8042F07C(SItem *item);

SItem *fn_80081274(register int handle)
{
    if (fn_80430050(lbl_8052F060) == 0)
        return 0;
    if (fn_80442680(handle) >= fn_80442654(fn_80430050(lbl_8052F060)))
        return 0;
    return &fn_80430050(lbl_8052F060)->items[fn_80442680(handle)];
}

int fn_80081338(register int handle)
{
    SItem *item = fn_80081274(handle);
    if (item == 0)
        return 0;
    return !fn_8042F07C(item);
}

void fn_800813AC(register int handle, int on)
{
    SItem *item = fn_80081274(handle);
    if (item == 0)
        return;
    if (on)
        item->flags &= ~0x40;
    else
        item->flags |= 0x40;
}

int fn_8002D9C4(void *level);
int fn_8002D90C(void *level, char *name);
extern int lbl_8066B644;
int fn_800578E4(int a, int b, int c, int d, int e, int f, int g);
int fn_80058130(int a, int b);
int fn_80058184(int a, int b);
int fn_8002E5B0(void *level, char *name, int v);
int fn_80020BF8(int a);
int fn_80020B4C(char *s, int a);
int fn_800B0C58(SActor *a);
void fn_8007072C(SActor *a);
void fn_800AF800(SActor *a, SItemOwner *level, SPoint *p, int x);

void fn_80081438()
{
    fn_8002D9C4(lbl_8052F060);
}

void fn_80081470(char *name)
{
    fn_8002D90C(lbl_8052F060, name);
}

int fn_800814B0(int a, int b, int c)
{
    if (lbl_8066B644 == 0)
        return 0;
    return fn_800578E4(a, b, 0, 0, c, 0, 999);
}

int fn_80081528(int a, int b)
{
    return fn_80058130(a, b);
}

int fn_80081574(int a, int b)
{
    return fn_80058184(a, b);
}

int fn_800815C0(char *name, int v)
{
    fn_8002E5B0(lbl_8052F060, name, v);
    return 1;
}

int fn_80081610(int a)
{
    return fn_80020BF8(a);
}

int fn_80081654(char *s, int a)
{
    return fn_80020B4C(s, a);
}

int fn_800816A0(int handle)
{
    SActor &a = *fn_800ACFA8(handle);
    if (!&a || !fn_800B0C58(&a))
        return 0;
    SPoint *found = 0;
    unsigned int i;
    for (i = 0; i < fn_80430050(lbl_8052F060)->npoints; i++) {
        SPoint *p = &fn_80430050(lbl_8052F060)->points[i];
        if (p->type != 0)
            continue;
        found = p;
        break;
    }
    if (found == 0)
        return 0;
    fn_8007072C(&a);
    fn_800AF800(&a, fn_80430050(lbl_8052F060), found, 0);
    return 1;
}

int fn_800817DC(int handle)
{
    SActor &a = *fn_800ACFA8(handle);
    if (!&a || !fn_800B0C58(&a))
        return 0;
    SPoint *found = 0;
    unsigned int i;
    for (i = 0; i < fn_80430050(lbl_8052F060)->npoints; i++) {
        SPoint *p = &fn_80430050(lbl_8052F060)->points[i];
        if (p->type != 1)
            continue;
        found = p;
        break;
    }
    if (found == 0)
        return 0;
    fn_8007072C(&a);
    fn_800AF800(&a, fn_80430050(lbl_8052F060), found, 0);
    return 1;
}

int fn_80081918(int handle)
{
    SActor &a = *fn_800ACFA8(handle);
    if (!&a || !fn_800B0C58(&a))
        return 0;
    SPoint *found = 0;
    unsigned int i;
    for (i = 0; i < fn_80430050(lbl_8052F060)->npoints; i++) {
        SPoint *p = &fn_80430050(lbl_8052F060)->points[i];
        if (p->type != 5)
            continue;
        found = p;
        break;
    }
    if (found == 0)
        return 0;
    fn_8007072C(&a);
    fn_800AF800(&a, fn_80430050(lbl_8052F060), found, 0);
    return 1;
}

void fn_80086410(SActor *a);
void fn_800B1F80(SActor *a);
void fn_80070228(SActor *a, int b, float f, int c, int d, int e);
void fn_80133658();
void fn_801336F0();
void fn_800924BC(void *game);

struct SFlags30 {
    char pad[0x30];
    unsigned int flags; // +0x30
};

struct SFlags300 {
    char pad[0x300];
    unsigned int flags; // +0x300
};

SFlags300 *fn_800B14A0(SActor *a);
SFlags30 *fn_800ACFA8F(int handle) __asm__("fn_800ACFA8");

struct SGame {
    char pad[0x760];
    int f760; // +0x760
};

int fn_80081A54(int handle)
{
    SActor &a = *fn_800ACFA8(handle);
    if (!&a || !fn_800B0C58(&a))
        return 0;
    fn_80086410(&a);
    return 1;
}

int fn_80081AD0(int handle)
{
    SFlags30 *a = fn_800ACFA8F(handle);
    if (a == 0)
        return 0;
    a->flags |= 2;
    return 1;
}

int fn_80081B40(int handle)
{
    SActor *a = fn_800ACFA8(handle);
    if (a == 0)
        return 0;
    fn_800B1F80(a);
    if (fn_800B0C58(a))
        fn_800B14A0(a)->flags |= 0x40;
    return 1;
}

}

__asm__(".section .rodata\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.long 0x6F727068\n\t.text"); // 0x804881C8-0x80488228, "CAsyncLoader:Instance" and "invalid" among them

extern "C" {

int fn_80081BD4(int handle)
{
    SActor &a = *fn_800ACFA8(handle);
    if (!&a || !fn_800B0C58(&a))
        return 0;
    fn_80070228(&a, 0, 0.0f, 0, 0, 0);
    return 1;
}

void fn_80081C68()
{
    ((SGame *)lbl_80552110)->f760 = 15;
}

void fn_80081C94()
{
    fn_80133658();
}

void fn_80081CC4()
{
    fn_801336F0();
    fn_800924BC(lbl_80552110);
}

extern float lbl_8066B8B8;
extern float lbl_8066B8BC;
extern float lbl_8066D620;
extern float lbl_8066D624;
extern float lbl_8066D628;
extern float lbl_8066D62C;

void fn_80081D00(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            lbl_8066D620 = 320.0f - lbl_8066B8B8 * 0.5f;
            lbl_8066D624 = lbl_8066D620 + lbl_8066B8B8 * 0.5f;
            lbl_8066D628 = 240.0f - lbl_8066B8BC * 0.5f;
            lbl_8066D62C = lbl_8066B8BC * 0.5f + lbl_8066D628 - 12.0f;
        } else {
        }
    }
}

void fn_80081DCC(void)
{
    fn_80081D00(1, 65535);
}

}

static void (*const sCtorEntry)(void) __attribute__((section(".ctors"))) = fn_80081DCC;
