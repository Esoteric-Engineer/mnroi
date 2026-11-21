// Script commands on an entity by handle, called from the script classes (docs/story.md row 24).
// Literal pool read from 0x804882B8 (extern_pool).

inline int sn_return_decl(int a)
{
    return a;
}

extern "C" {

struct SNode {
    float a[4];           // +0x00
    float b[4];           // +0x10
    unsigned short id;    // +0x20
    char pad[0xE];
};

struct SComp {
    char pad[0x78];
    SComp *next; // +0x78
    char pad7c[0xC8 - 0x7C];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31(int target);
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57(int on);
    virtual void v58();
};

struct SActor {
    char pad[0x2C];
    int f2c;              // +0x2C
    unsigned int f30;     // +0x30
    char pad34[0x11C - 0x34];
    unsigned int f11c;    // +0x11C
    char pad120[0x144 - 0x120];
    unsigned int nodeCount; // +0x144
    SNode *nodes;         // +0x148
    int f14c;             // +0x14C
    char pad150[4];
    SComp *comps;         // +0x154
};

struct SModel;

struct SLink {
    char pad[8];
    SModel *model; // +0x08
    char padC[0x70 - 0xC];
};

struct SModel {
    char pad[0x12];
    unsigned short n12;   // +0x12
    char pad14[2];
    unsigned char n16;    // +0x16
    char pad17[0x1C - 0x17];
    SLink *f1c;           // +0x1C
    char pad20[0x58 - 0x20];
    SActor *links[1];     // +0x58
};

struct SLevel {
    char pad[0x120];
    char *f120;           // +0x120
    char pad124[0x130 - 0x124];
    SActor *head;         // +0x130
};

SActor *fn_800ACFA8(int handle);
int fn_804425F8(int handle);

void fn_80081E08(int a)
{
}

int fn_80081E28()
{
    return 0;
}

void fn_80081E4C(int a)
{
}

SActor *fn_80081E6C(register int handle)
{
    SActor *a = fn_800ACFA8(fn_804425F8(handle));
    return a;
}

int fn_80081EC4(register int handle)
{
    SActor *a = fn_80081E6C(handle);
    if (a == 0)
        return 0;
    return a->f2c;
}

int fn_80081F28(register int handle)
{
    SActor *a = fn_80081E6C(handle);
    if (a == 0)
        return 0;
    return a->f30;
}

int fn_80081F8C(register int handle, unsigned int bits)
{
    SActor *a = fn_80081E6C(handle);
    if (a == 0)
        return -1;
    unsigned int old = a->f30;
    a->f30 |= bits;
    return old;
}

int fn_80082014(register int handle, unsigned int bits)
{
    SActor *a = fn_80081E6C(handle);
    if (a == 0)
        return -1;
    unsigned int old = a->f30;
    a->f30 &= ~bits;
    return old;
}

void fn_800B0738(SActor *a);
void fn_800B07DC(SActor *a, int v);
void fn_800AE398(SActor *a, int b, int c);
void *fn_800FD5FC(void *name, int flag);
void *fn_800AD1FC(SActor *a, void *tmpl, int b, int c);
int fn_800B13D8(void *e);

int fn_800820A0(register int handle, int on)
{
    SActor *a = fn_80081E6C(handle);
    if (a == 0)
        return 0;
    if (on)
        fn_800B0738(a);
    else
        fn_800B07DC(a, 1);
    return 1;
}

int fn_80082124(register int handle)
{
    SActor *a = fn_80081E6C(handle);
    if (a == 0)
        return 0;
    fn_800AE398(a, 0, 0);
    return 1;
}

int fn_80082190(register int handle, void *name)
{
    SActor *a = fn_80081E6C(handle);
    if (a == 0)
        return 0;
    void *t = fn_800FD5FC(name, 0);
    if (t == 0)
        return 0;
    void *e = fn_800AD1FC(a, t, 1, 0);
    if (e == 0)
        return 0;
    return fn_800B13D8(e);
}

}

struct SVector {
    float x, y, z, w;
    SVector() __asm__("__6Vector");
} __attribute__((aligned(8)));

struct SMat4 {
    float m[4][4];
    SMat4() __asm__("fn_8042D7B0");
};

extern "C" {

void fn_8042DCC0(SMat4 *m);
void fn_8042DC84(void *dst, void *src);
SModel *fn_800B1CC8(SActor *a);
void *fn_8004DCA0(void *p, float *pos);
SLevel *fn_80430050(void *level);
void *fn_8004DD38(void *level, float *pos);
int fn_80430BA0(void *p);
void *fn_800AD0DC(void *tmpl, int a, void *p, SMat4 *m, int b);
extern char lbl_8052F060[];

int fn_800822D8(void *name, SMat4 *m, int handle);

int fn_80082254(void *name, void *pos, int handle)
{
    SMat4 m;
    fn_8042DCC0(&m);
    fn_8042DC84(m.m[3], pos);
    return fn_800822D8(name, &m, handle);
}

int fn_800822D8(void *name, SMat4 *m, int handle)
{
    void *t = fn_800FD5FC(name, 0);
    if (t == 0)
        return 0;
    SActor *a = handle ? fn_80081E6C(handle) : 0;
    void *p = a ? fn_800B1CC8(a) : 0;
    if (p)
        p = fn_8004DCA0(p, m->m[3]);
    else
        p = fn_8004DD38(fn_80430050(lbl_8052F060), m->m[3]);
    if (p == 0)
        return 0;
    void *e = fn_800AD0DC(t, fn_80430BA0(p), p, m, 0);
    if (e == 0)
        return 0;
    return fn_800B13D8(e);
}

void fn_800B16D8(SActor *a, void *out);
int fn_800B1A98(SActor *a);
void *fn_800B1668(SActor *a);
void fn_8042E438(SMat4 *m, void *src);
void *fn_80441C90(float *pos, void *p);
void fn_800AFAB0(SActor *a, int b, void *p, SMat4 *m, int c);

int fn_80082440(register int handle, void *out)
{
    SActor *a = fn_80081E6C(handle);
    if (a == 0)
        return 0;
    fn_800B16D8(a, out);
    return 1;
}

int fn_800824AC(register int handle, void *pos)
{
    SVector v;
    SActor *a = fn_80081E6C(handle);
    if (!a || !fn_800B1A98(a))
        return 0;
    SMat4 m;
    fn_8042E438(&m, fn_800B1668(a));
    fn_8042DC84(m.m[3], pos);
    void *p = fn_80441C90(m.m[3], fn_800B1CC8(a));
    if (p == 0)
        return 0;
    fn_800AFAB0(a, fn_800B1A98(a), p, &m, 0);
    return 1;
}

int fn_800825D0(register int handle, SMat4 *m)
{
    SActor *a = fn_80081E6C(handle);
    if (!a || !fn_800B1A98(a))
        return 0;
    void *p = fn_80441C90(m->m[3], fn_800B1CC8(a));
    if (p == 0)
        return 0;
    fn_800AFAB0(a, fn_800B1A98(a), p, m, 0);
    return 1;
}

int fn_800826A8(register int handle, SMat4 *out)
{
    SActor *a = fn_80081E6C(handle);
    if (a == 0)
        return 0;
    fn_8042E438(out, fn_800B1668(a));
    return 1;
}

void fn_8005A828(SActor *a, SVector *pos);
int fn_800B0D64(SActor *a);

int fn_80082720(register int handle, int target)
{
    SActor *a = fn_80081E6C(handle);
    if (a == 0)
        return 0;
    SActor *t = fn_800ACFA8(target);
    if (t == 0)
        return 0;
    SVector pos;
    fn_800B16D8(t, &pos);
    fn_8005A828(a, &pos);
    return 1;
}

unsigned int fn_800827D0(register int handle, int target)
{
    SActor *a = fn_80081E6C(handle);
    if (!a || !fn_800B1CC8(a))
        return 0;
    SActor &t = *fn_800ACFA8(target);
    if (!&t || !fn_800B0D64(&t))
        return 0;
    SModel *m = fn_800B1CC8(a);
    for (unsigned short i = 0; i < m->n12; i++) {
        if (m->links[i] == &t)
            return a->f11c & (1 << i);
    }
    return 0;
}

int fn_8008291C(register int handle, unsigned int i, void *b, void *pa, unsigned short *id)
{
    SActor *a = fn_80081E6C(handle);
    if (a == 0)
        return 0;
    if (a->nodeCount == 0)
        return 0;
    if (i >= a->nodeCount)
        return 0;
    if (b)
        fn_8042DC84(b, a->nodes[i].b);
    if (pa)
        fn_8042DC84(pa, a->nodes[i].a);
    if (id)
        *id = a->nodes[i].id;
    return 1;
}

int fn_8007613C(SActor *a, unsigned int i, float f, int b, int c);
void fn_8007ED18(SActor *a, int b, int c, int d, float x, float y, float z, float w);
char *fn_8039C7F0(SComp *c);
int stricmp(const char *a, const char *b);

int fn_80082A44(register int handle, unsigned int i, float f, int c)
{
    SActor *a = fn_80081E6C(handle);
    if (a == 0)
        return 0;
    if (a->nodeCount == 0)
        return 0;
    if (i >= a->nodeCount)
        return 0;
    return fn_8007613C(a, i, f, 0, c);
}

int fn_80082AFC(register int handle, int b, int c, int d, float x, float y, float z, float w)
{
    SActor *a = fn_80081E6C(handle);
    if (a == 0)
        return 0;
    if (a->f14c == 0)
        return 0;
    fn_8007ED18(a, b, c, d, x, y, z, w);
    return 1;
}

int fn_80082BB0(register int handle, char *name, int target)
{
    SActor *a = fn_80081E6C(handle);
    if (a == 0)
        return 0;
    SActor *t = fn_800ACFA8(target);
    if (t == 0)
        return 0;
    for (SComp *c = a->comps; c; c = c->next) {
        if (stricmp(fn_8039C7F0(c), name) == 0) {
            c->v31(target);
            return 1;
        }
    }
    return 0;
}

char *fn_80082CC8(register int handle, int n)
{
    SActor *a = fn_80081E6C(handle);
    if (a == 0)
        return 0;
    int k = n;
    SComp *c = 0;
    for (c = a->comps; c; c = c->next) {
        if (k)
            k--;
        else
            return fn_8039C7F0(c);
    }
    return 0;
}

SComp *fn_80393A60(SActor *a, char *name, int b);
int fn_80393D0C(SActor *a, char *name, unsigned char b, unsigned char c);
void fn_80393C0C(SActor *a, char *name, unsigned char b, unsigned char c);
int fn_800AFFD4(SActor *a, int b);
int fn_800B01C8(SActor *a, int b);
int fn_80082E90(register int handle, char *name, unsigned char b, unsigned char c);
int fn_800830A0(register int handle, char *name);

SComp *fn_80082D94(register int handle, char *name)
{
    if (name == 0)
        return 0;
    SActor *a = fn_80081E6C(handle);
    if (a == 0)
        return 0;
    SComp *r = fn_80393A60(a, name, 0);
    return r;
}

int fn_80082E24(register int handle, char *name)
{
    if (name)
        fn_80082E90(handle, name, 0xFF, 0xFF);
    return fn_800830A0(handle, name);
}

int fn_80082E90(register int handle, char *name, unsigned char b, unsigned char c)
{
    SActor *a = fn_80081E6C(handle);
    if (a == 0)
        return 0;
    int r = fn_80393D0C(a, name, b, c);
    return r;
}

int fn_80082F30(register int handle)
{
    SActor *a = fn_80081E6C(handle);
    if (a && fn_800AFFD4(a, 1))
        return 1;
    return 0;
}

int fn_80082FA4(register int handle)
{
    SActor *a = fn_80081E6C(handle);
    if (a && fn_800B01C8(a, 1))
        return 1;
    return 0;
}

void fn_80083018(register int handle, char *name, unsigned char b, unsigned char c)
{
    SActor *a = fn_80081E6C(handle);
    if (a == 0)
        return;
    fn_80393C0C(a, name, b, c);
}

float *fn_8039C65C(SComp *c);
void fn_8001C0D0(float x, float y, float z);

int fn_800830A0(register int handle, char *name)
{
    SComp *c = 0;
    SActor *a = fn_80081E6C(handle);
    int found = 0;
    if (a == 0)
        return 0;
    if (a->comps == 0)
        return 0;
    if (name) {
        for (c = a->comps; c; c = c->next) {
            if (stricmp(fn_8039C7F0(c), name) == 0) {
                c->v56();
                found = 1;
            }
        }
    } else {
        for (c = a->comps; c; c = c->next)
            c->v56();
        found = 1;
    }
    return found;
}

int fn_80083230(register int handle, char *name)
{
    SComp *c = 0;
    SActor *a = fn_80081E6C(handle);
    int found = 0;
    if (a == 0)
        return 0;
    if (a->comps == 0)
        return 0;
    if (name) {
        for (c = a->comps; c; c = c->next) {
            if (stricmp(fn_8039C7F0(c), name) == 0) {
                fn_8001C0D0(fn_8039C65C(c)[0], fn_8039C65C(c)[1], fn_8039C65C(c)[2]);
                c->v11();
                found = 1;
            }
        }
    } else {
        for (c = a->comps; c; c = c->next) {
            fn_8001C0D0(fn_8039C65C(c)[0], fn_8039C65C(c)[1], fn_8039C65C(c)[2]);
            c->v11();
        }
        found = 1;
    }
    return found;
}

int fn_80083428(register int handle, char *name)
{
    SComp *c = 0;
    SActor *a = fn_80081E6C(handle);
    int found = 0;
    if (a == 0)
        return 0;
    if (a->comps == 0)
        return 0;
    if (name) {
        for (c = a->comps; c; c = c->next) {
            if (stricmp(fn_8039C7F0(c), name) == 0) {
                c->v54();
                found = 1;
                fn_8001C0D0(fn_8039C65C(c)[0], fn_8039C65C(c)[1], fn_8039C65C(c)[2]);
            }
        }
    } else {
        for (c = a->comps; c; c = c->next) {
            c->v54();
            fn_8001C0D0(fn_8039C65C(c)[0], fn_8039C65C(c)[1], fn_8039C65C(c)[2]);
        }
        found = 1;
    }
    return found;
}

void fn_80083620(register int handle, char *name)
{
    SComp *c = fn_80082D94(handle, name);
    if (c)
        c->v58();
}

void fn_800836A8(register int handle, char *name)
{
    SComp *c = fn_80082D94(handle, name);
    if (c)
        c->v57(1);
}

void *fn_80048628(int id);

int fn_80083734(int id)
{
    void *e = fn_80048628(id);
    if (e == 0)
        return 0;
    return fn_800B13D8(e);
}

void *memset(void *dst, int c, unsigned long n);
char *strncpy(char *dst, const char *src, unsigned long n);
char *strtok(char *s, const char *delim);
double atof(const char *s);

float fn_8008379C(char *str, int i)
{
    char *toks[8];
    char buf[32];
    char *tok;
    int n = 0;
    memset(toks, 0, sizeof(toks));
    strncpy(buf, str, sizeof(buf));
    buf[31] = 0;
    tok = strtok(buf, " \r\t\n");
    if (tok == 0)
        return -999.0f;
    while (tok) {
        toks[n] = tok;
        n++;
        tok = strtok(0, " \r\t\n");
    }
    if (toks[i] == 0)
        return -999.0f;
    return atof(toks[i]);
}

extern char lbl_80552110[];
extern char lbl_80593DD0[];
SActor *fn_80432924(void *game);
void *fn_8043289C(void *game);
float fn_804290F8(SVector *a, void *b);
void fn_8003DBF0(void *p, int a, float f, int b);
void fn_801BEBBC(SVector *out, void *tbl, int id);
void fn_80067050(SActor *a, SVector *out);
void fn_8042F76C(SVector *v);
float fn_8042EBF4(SVector *a, SVector *b);

void fn_800838E0(void *pos)
{
    SActor *p = fn_80432924(lbl_80552110);
    if (p == 0)
        return;
    SVector v;
    fn_800B16D8(p, &v);
    float d = fn_804290F8(&v, pos);
    if (d < 15.0f)
        fn_8003DBF0(fn_8043289C(lbl_80552110), 1000, 0.75f / d, 1);
}

int fn_800839B0(int id)
{
    SVector a;
    fn_801BEBBC(&a, lbl_80593DD0, id);
    SVector b;
    SActor *p = fn_80432924(lbl_80552110);
    if (p == 0)
        return 0;
    fn_80067050(p, &b);
    fn_8042F76C(&b);
    if (fn_8042EBF4(&b, &a) > 0.0f)
        return 1;
    else
        return 0;
}

SLevel &fn_80430050R(void *level) __asm__("fn_80430050");
int fn_800B0C58(SActor *a);
void *fn_800B14A0(SActor *a);
int fn_8008582C(void *p);
void fn_80030930(void *a, int b, int c, int d, float f1, int e, int f, int g, int h, float f2);
SActor *fn_800B1AC4(SActor *a);

void fn_80083A90()
{
    SActor *e;
    for (e = fn_80430050R(lbl_8052F060).head; e; e = fn_800B1AC4(e)) {
        if (!fn_800B0C58(e))
            continue;
        if (!fn_8008582C(fn_800B14A0(e)))
            continue;
        fn_80030930(fn_800B14A0(e), 0, 0, 0, 0.0f, 0, 0, 0, 1, 0.0f);
    }
}

void fn_80442700(SLink *l);
void fn_804426D4(SLink *l);

int fn_80083B74(int h1, int h2, int on)
{
    SActor *a = fn_800ACFA8(h1);
    if (!a || !fn_800B1CC8(a))
        return 0;
    SActor *b = fn_800ACFA8(h2);
    if (!b || !fn_800B1CC8(b))
        return 0;
    int found = 0;
    for (unsigned int i = 0; i < fn_800B1CC8(a)->n16; i++) {
        if (fn_800B1CC8(a)->f1c[i].model == fn_800B1CC8(b)) {
            if (on)
                fn_80442700(&fn_800B1CC8(a)->f1c[i]);
            else
                fn_804426D4(&fn_800B1CC8(a)->f1c[i]);
            found = 1;
        }
    }
    return found;
}

void fn_800800E4(int a, int b, int c, float x, float y, float z, float w);

int fn_80083D08(int a, int b, int c, float x, float y, float z, float w)
{
    fn_800800E4(a, b, c, x, y, z, w);
    return 1;
}

void fn_801AA414(unsigned short id, float x, float y, int a, int b);

void fn_80083D78(float x, float y, int a, int b, unsigned short id)
{
    fn_801AA414(id, x, y, a, b);
}

int fn_804427FC(void *g);
void *fn_804427D0(void *g);
int fn_80442774(void *p);
int fn_8044272C(void *p);
unsigned short fn_80442624(void *p);
int fn_80094A9C(void *g);

void fn_80083DE0(float x, float y, int a, int b)
{
    if (fn_804427FC(lbl_80552110)) {
        do {
            if (fn_804427D0(lbl_80552110) && !fn_80442774(fn_804427D0(lbl_80552110)) &&
                !fn_8044272C(fn_804427D0(lbl_80552110)))
                fn_801AA414(fn_80442624(fn_804427D0(lbl_80552110)), x, y, a, b);
        } while (fn_80094A9C(lbl_80552110));
    }
}

int fn_804427A4(void *g);
void *fn_80094630(void *g);
extern char lbl_80567720[];
void fn_80115154(int id, int on);

void fn_80083EE8(int a, float f, int b)
{
    fn_8003DBF0(fn_8043289C(lbl_80552110), a, f, b);
    void *p;
    if (fn_804427A4(lbl_80552110))
        p = fn_80094630(lbl_80552110);
    else
        p = fn_8043289C(lbl_80552110);
    if (p)
        fn_8042DC84(lbl_80567720, (char *)p + 0x390);
    fn_80115154(0x117, 1);
}

char *fn_80083FB8()
{
    SLevel *l = fn_80430050(lbl_8052F060);
    if (l && l->f120)
        return l->f120 + 0x13C;
    return 0;
}

}
