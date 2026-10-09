// Record-table factories, actor checks and record setups over the 0x60-byte `lbl_80567760` table
// (guessed class names `Obj90`..`ObjH`); docs/versus.md section 5, row 2.

struct Slot
{
    void *owner;
    char pad0[0x1C];
    int source; // +0x20
    int state24; // +0x24
    char pad1[4];
    int handle2C; // +0x2C
    char pad2a[4];
    int handle34; // +0x34
    int id38; // +0x38
    char pad2b[0xC];
    int free48; // +0x48
    char pad2c[4];
    void *node; // +0x50
    char pad2[0xC];
} __attribute__((aligned(8)));

extern Slot lbl_80567760[];
extern int lbl_804CF638[];
extern "C" void *fn_800ACFA8(int handle);
extern "C" void *fn_800B1568(void *actor);
extern "C" unsigned int fn_8009ABEC(void *entity);
extern int lbl_8066BD60;

struct Node
{
    int check() __asm__("fn_8039CFE4");
};

struct Obj
{
    int get(int id) __asm__("fn_800ACD20");
    void *attach(int a, int b) __asm__("fn_80393A60");
    Node *find(void *n) __asm__("fn_80393B28");
};

struct Sub : Obj
{
    int pad;
};

extern "C" Sub *fn_800B14C8(void *actor);

class Obj90
{
public:
    char data[0x14];
    Obj90(register int a, register int b, register int c, register int d);
    void *operator new(unsigned size) __asm__("fn_8045C458");
};

class Obj92
{
public:
    char data[0x14];
    Obj92(register int a, register int b, register int c, register int d);
    void *operator new(unsigned size) __asm__("fn_8045C5F0");
};

extern "C" Obj90 *fn_804580CC(register int handle, register int index)
{
    int value = 0;
    void *actor = fn_800ACFA8(lbl_80567760[index].source);
    if (actor != 0) {
        value = lbl_804CF638[fn_8009ABEC(fn_800B1568(actor))];
    }
    return new Obj90(0, 100, value, 1);
}

extern "C" int fn_804581A0(register void *actor, register int index)
{
    if (lbl_8066BD60 != 0) {
        return 0;
    }
    if (lbl_80567760[index].node == 0) {
        void *a = fn_800ACFA8(lbl_80567760[index].source);
        if (a != 0) {
            lbl_80567760[index].node = fn_800B14C8(a)->attach(fn_800B14C8(a)->get(0x65), 0);
        }
    }
    {
        Node *n = (Node *)lbl_80567760[index].node;
        n = fn_800B14C8(actor)->find(n);
        register unsigned int found = 0;
        if (n != 0) {
            if (n->check()) {
                found = 1;
            }
        }
        return found;
    }
}

extern "C" void fn_80112214(void *rec, int handle, int flag);
extern "C" int fn_80118C64(int v);
extern "C" int fn_80118C3C(int v);
extern "C" void fn_8045C38C(void *self, int v);
extern "C" void fn_8045C33C(void *self, int v);
extern "C" void fn_8045C414(void *self, int v);
extern int lbl_8066F06C;
extern int lbl_8066F068;
extern char lbl_80567770[];

extern "C" void fn_804582F0(register void *self, register int unused, register int index)
{
    fn_80112214(lbl_80567770 + index * 0x60, lbl_80567760[index].handle2C, 1);
    fn_8045C38C(self, fn_80118C64(lbl_8066F06C));
    fn_8045C33C(self, fn_80118C3C(lbl_8066F068));
    if (lbl_80567760[index].state24 > 0x257) {
        fn_8045C414(self, 1);
    } else {
        fn_8045C414(self, 0);
    }
}

extern "C" Obj92 *fn_804583C8(register int handle, register int index)
{
    int value = 0;
    void *actor = fn_800ACFA8(lbl_80567760[index].source);
    if (actor != 0) {
        value = lbl_804CF638[fn_8009ABEC(fn_800B1568(actor))];
    }
    return new Obj92(0, 50, 900, value);
}

extern "C" int fn_800B0C1C(void *actor);
extern "C" void *fn_80085954(void *entity);
extern "C" int fn_800CCA08(void *p);
extern int lbl_8066BD30;

extern "C" int fn_8045849C(register void *actor, register int index)
{
    if (lbl_8066BD60 != 0) {
        return 0;
    }
    if (fn_800B0C1C(actor)) {
        register void *p;
        register unsigned int found = 0;
        if (lbl_8066BD30 != 0 || (p = fn_80085954(fn_800B14C8(actor)), fn_800CCA08(p))) {
            found = 1;
        }
        int result = found;
        return result;
    }
    return 0;
}

extern "C" void fn_8045C524(void *self, int v);
extern "C" void fn_8045C4D4(void *self, int v);
extern "C" void fn_8045C568(void *self, int v);

extern "C" void fn_8045855C(register void *self, register int unused, register int index)
{
    fn_80112214(lbl_80567770 + index * 0x60, lbl_80567760[index].handle2C, 1);
    fn_8045C524(self, fn_80118C64(lbl_8066F06C));
    fn_8045C4D4(self, fn_80118C3C(lbl_8066F068));
    fn_8045C568(self, 0x384);
}

class ObjC
{
public:
    char data[0xC];
    ObjC(register int a, register int b);
    void *operator new(unsigned size) __asm__("fn_8045D2E8");
};

extern "C" ObjC *fn_80458608(register int handle, register int index)
{
    return new ObjC(0, 0);
}

struct Pos
{
    float pad[2];
    float z; // +0x8
};

extern "C" int fn_8005ABF0(void *actor);
extern "C" float fn_800670CC(void *actor);
extern "C" unsigned int fn_8010C7EC(void *obj, int a, int b);
extern "C" Pos *fn_800B1724(void *actor);
extern char lbl_8066D808[8];

extern "C" int fn_8045866C(register void *actor, register int index)
{
    register unsigned int found = 0;
    if (fn_8005ABF0(actor)) {
        register float height = fn_800670CC(actor);
        if (height > (float)fn_8010C7EC(lbl_8066D808, 1, 0x65)) {
            if (fn_800B1724(actor)->z > -30.0f) {
                found = 1;
            }
        }
    }
    return found;
}

extern "C" void fn_8045D2A4(void *self, int v);
extern "C" void fn_8045D254(void *self, int v);

extern "C" void fn_8045873C(register void *self, register int unused, register int index)
{
    fn_80112214(lbl_80567770 + index * 0x60, lbl_80567760[index].handle2C, 1);
    fn_8045D2A4(self, fn_80118C64(lbl_8066F06C));
    fn_8045D254(self, fn_80118C3C(lbl_8066F068));
}

class ObjD
{
public:
    char data[0x10];
    ObjD(register int a, register int b, register int c);
    void *operator new(unsigned size) __asm__("fn_8045B474");
};

extern "C" ObjD *fn_804587DC(register int handle, register int index)
{
    int value = 0;
    void *actor = fn_800ACFA8(lbl_80567760[index].source);
    if (actor != 0) {
        value = lbl_804CF638[fn_8009ABEC(fn_800B1568(actor))];
    }
    return new ObjD(0, 50, value);
}

extern "C" int fn_800CCA88(void *p);

extern "C" int fn_804588AC(register void *actor, register int index)
{
    if (lbl_8066BD60 != 0) {
        return 0;
    }
    if (actor != 0 && fn_800B0C1C(actor)) {
        register void *p = fn_80085954(fn_800B14C8(actor));
        return fn_800CCA88(p) != 0 ? 1 : 0;
    }
    return 0;
}

extern "C" void fn_8045B430(void *self, int v);
extern "C" void fn_8045B3E0(void *self, int v);

extern "C" void fn_8045895C(register void *self, register int unused, register int index)
{
    fn_80112214(lbl_80567770 + index * 0x60, lbl_80567760[index].handle2C, 1);
    fn_8045B430(self, fn_80118C64(lbl_8066F06C));
    fn_8045B3E0(self, fn_80118C3C(lbl_8066F068));
}

class ObjE
{
public:
    char data[8];
    ObjE(register int a);
    void *operator new(unsigned size) __asm__("fn_8045D140");
};

extern "C" ObjE *fn_804589FC(register int handle, register int index)
{
    return new ObjE(0);
}

extern "C" int fn_800CCAB8(void *p);
extern "C" float fn_80086730(void *entity);
extern "C" float fn_8008677C(void *entity);

extern "C" int fn_80458A5C(register void *actor, register int index)
{
    if (lbl_8066BD60 != 0) {
        return 0;
    }
    if (actor != 0 && fn_800B0C1C(actor)) {
        register void *p;
        register unsigned int found = 0;
        p = fn_80085954(fn_800B14C8(actor));
        if (fn_800CCAB8(p) != 0) {
            register float a = fn_80086730(fn_800B14C8(actor));
            if (a < fn_8008677C(fn_800B14C8(actor))) {
                found = 1;
            }
        }
        return found;
    }
    return 0;
}

extern "C" void fn_8045D0FC(void *self, int v);

extern "C" void fn_80458B4C(register void *self, register void *actor, register int index)
{
    int value = 0;
    if (actor != 0 && fn_800B0C1C(actor)) {
        register float a = fn_80086730(fn_800B14C8(actor));
        value = (int)(a * 1000.0f / fn_8008677C(fn_800B14C8(actor)));
    }
    fn_8045D0FC(self, value);
}

class ObjF
{
public:
    char data[0x14];
    ObjF(register int a, register int b, register int c, register int d);
    void *operator new(unsigned size) __asm__("fn_8045CD4C");
};

extern "C" int fn_8010DDAC(int handle);

extern "C" ObjF *fn_80458C18(register int handle, register int index)
{
    int value = fn_8010DDAC(handle);
    return new ObjF(0, 0, 50, value);
}

extern "C" int fn_80458C94(register void *actor, register int index)
{
    if (lbl_8066BD60 != 0) {
        return 0;
    }
    return 1;
}

extern "C" void fn_8045CD04(void *self, int v);
extern "C" void fn_8045CCB4(void *self, int v);

extern "C" void fn_80458CDC(register void *self, register int unused, register int index)
{
    fn_80112214(lbl_80567770 + index * 0x60, lbl_80567760[index].handle2C, 1);
    fn_8045CD04(self, fn_80118C64(lbl_8066F06C));
    fn_8045CCB4(self, fn_80118C3C(lbl_8066F068));
}

class ObjG
{
public:
    char data[0x1C];
    ObjG(register int a, register int b, register int c, register int d, register int e, register int f);
    void *operator new(unsigned size) __asm__("fn_8045C9F8");
};

extern "C" int fn_8010D3C4(int handle);

extern "C" ObjG *fn_80458D7C(register int handle, register int index)
{
    int value = fn_8010D3C4(handle);
    if (lbl_80567760[index].handle34 == -1) {
        lbl_80567760[index].handle34 = 0;
    }
    return new ObjG(0, 0, 50, 0, value, lbl_80567760[index].handle34);
}

extern int lbl_8066BDF8;
extern int lbl_8066BE04;

extern "C" int fn_80458E48(register void *actor, register int index)
{
    if (lbl_80567760[index].handle2C == 0x108 && lbl_8066BDF8 == 0x30 && lbl_8066BE04 == 1) {
        return 0;
    }
    if (lbl_80567760[index].handle2C == 0x204 && lbl_80567760[index].handle34 == 1) {
        return 0;
    }
    if (lbl_8066BD60 != 0) {
        return 0;
    }
    return 1;
}

extern "C" void fn_8045C9B0(void *self, int v);
extern "C" void fn_8045C960(void *self, int v);

extern "C" void fn_80458F0C(register void *self, register int unused, register int index)
{
    fn_80112214(lbl_80567770 + index * 0x60, lbl_80567760[index].handle2C, 1);
    int v = fn_80118C64(lbl_8066F06C);
    fn_8045C9B0(self, v);
    fn_8045C960(self, fn_80118C3C(lbl_8066F068));
}

class ObjH
{
public:
    char data[0x10];
    ObjH(register int a, register int b, register int c);
    void *operator new(unsigned size) __asm__("fn_8045C208");
};

extern "C" ObjH *fn_80458FB0(register int handle, register int index)
{
    return new ObjH(0, 0, 50);
}

extern "C" int fn_80459018(register void *actor, register int index)
{
    if (lbl_8066BD60 != 0) {
        return 0;
    }
    return 1;
}

extern "C" void fn_8045C17C(void *self, int v);
extern "C" void fn_8045C12C(void *self, int v);
extern "C" void fn_8045C1C4(void *self, int v);

extern "C" void fn_80459060(register void *self, register void *actor, register int index)
{
    fn_80112214(lbl_80567770 + index * 0x60, lbl_80567760[index].handle2C, 1);
    fn_8045C17C(self, fn_80118C64(lbl_8066F06C));
    fn_8045C12C(self, fn_80118C3C(lbl_8066F068));
    float h = fn_800670CC(actor);
    int value = (int)(h * 200.0f);
    if (value < 0) {
        value = 0;
    }
    if (value > 1000) {
        value = 1000;
    }
    fn_8045C1C4(self, value);
}

class ObjI
{
public:
    char data[0x14];
    ObjI(register int a, register int b, register int c, register int d);
    void *operator new(unsigned size) __asm__("fn_8045D4E8");
};

extern "C" ObjI *fn_80459168(register int handle, register int index)
{
    int value = 0;
    void *actor = fn_800ACFA8(lbl_80567760[index].source);
    if (actor != 0) {
        value = fn_8010D3C4(fn_8009ABEC(fn_800B1568(actor)));
    }
    return new ObjI(0, 0, 0, value);
}

struct Obj2
{
    int get() __asm__("fn_800B1138");
};

struct Sub2 : Obj2
{
    int pad;
};

extern "C" Sub2 *fn_800B1478(void *actor);
extern "C" int fn_800B0CC0(void *actor);

extern "C" int fn_80459230(register void *actor, register int index)
{
    if (lbl_8066BD60 != 0) {
        return 0;
    }
    if (fn_800B0CC0(actor)) {
        int v = fn_800B1478(actor)->get();
        return v == 0;
    }
    return 0;
}

extern "C" void fn_8045D45C(void *self, int v);
extern "C" void fn_8045D40C(void *self, int v);
extern "C" void fn_8045D4A4(void *self, int v);

extern "C" void fn_804592D0(register void *self, register void *actor, register int index)
{
    fn_80112214(lbl_80567770 + index * 0x60, lbl_80567760[index].handle2C, 1);
    fn_8045D45C(self, fn_80118C64(lbl_8066F06C));
    fn_8045D40C(self, fn_80118C3C(lbl_8066F068));
    fn_8045D4A4(self, lbl_80567760[index].state24);
}

class ObjJ
{
public:
    char data[0x14];
    ObjJ(register int a, register int b, register int c, register int d);
    void *operator new(unsigned size) __asm__("fn_8045B820");
};

extern "C" int fn_800B0C58(void *actor);

extern "C" ObjJ *fn_8045938C(register int handle, register int index)
{
    void *actor = fn_800ACFA8(lbl_80567760[index].source);
    int value = 0;
    if (actor != 0 && fn_800B0C58(actor)) {
        value = lbl_804CF638[fn_8009ABEC(fn_800B1568(actor))];
    }
    return new ObjJ(0, 0, 1000, value);
}

struct ActorInfo
{
    unsigned int getA() __asm__("fn_8009B04C");
    unsigned int getB() __asm__("fn_8009AFC8");
};

struct ActorInfoSub : ActorInfo
{
    int pad;
};

extern "C" ActorInfoSub *fn_800B14A0(void *actor);
extern "C" int fn_800B13D8(void *actor);

extern "C" int fn_80459474(register void *actor, register int index)
{
    if (lbl_8066BD60 != 0) {
        return 0;
    }
    if (actor != 0 && fn_800B0C58(actor)) {
        if (lbl_80567760[index].id38 == -1) {
            int v = fn_800B14A0(actor)->getA();
            if (v == 0) {
                v = fn_800B14A0(actor)->getB();
            }
            lbl_80567760[index].id38 = v;
            for (unsigned int i = 0; i <= 0x2F; i++) {
                if (i == index) {
                    continue;
                }
                if (lbl_80567760[i].free48 != 0 && lbl_80567760[i].handle2C == 0x39
                    && lbl_80567760[i].source == fn_800B13D8(actor)) {
                    return 0;
                }
            }
        }
        int w = fn_800B14A0(actor)->getA();
        if (w == 0) {
            w = fn_800B14A0(actor)->getB();
        }
        return lbl_80567760[index].id38 == w;
    }
    return 0;
}

extern "C" void fn_8045B7D8(void *self, int v);
extern "C" void fn_8045B788(void *self, int v);

extern "C" void fn_80459670(register void *self, register void *actor, register int index)
{
    fn_80112214(lbl_80567770 + index * 0x60, lbl_80567760[index].handle2C, 1);
    fn_8045B7D8(self, fn_80118C64(lbl_8066F06C));
    fn_8045B788(self, fn_80118C3C(lbl_8066F068));
}

class ObjK
{
public:
    char data[0x14];
    ObjK(register int a, register int b, register int c, register int d);
    void *operator new(unsigned size) __asm__("fn_8045BFE8");
};

extern "C" ObjK *fn_80459710(register int handle, register int index)
{
    void *actor = fn_800ACFA8(lbl_80567760[index].source);
    int value = 0;
    if (actor != 0 && fn_800B0C58(actor)) {
        value = lbl_804CF638[fn_8009ABEC(fn_800B1568(actor))];
    }
    return new ObjK(0, 0, 1000, value);
}

extern "C" int fn_804597F8(register void *actor, register int index)
{
    if (actor != 0 && fn_800B0C58(actor)) {
        if (lbl_80567760[index].id38 == -1) {
            int v = fn_800B14A0(actor)->getA();
            if (v == 0) {
                v = fn_800B14A0(actor)->getB();
            }
            lbl_80567760[index].id38 = v;
            for (unsigned int i = 0; i <= 0x2F; i++) {
                if (i == index) {
                    continue;
                }
                if (lbl_80567760[i].free48 != 0 && lbl_80567760[i].handle2C == 0x3A
                    && lbl_80567760[i].source == fn_800B13D8(actor)) {
                    return 0;
                }
            }
        }
        int w = fn_800B14A0(actor)->getA();
        if (w == 0) {
            w = fn_800B14A0(actor)->getB();
        }
        return lbl_80567760[index].id38 == w;
    }
    return 0;
}

extern "C" void fn_8045BFA0(void *self, int v);
extern "C" void fn_8045BF50(void *self, int v);

extern "C" void fn_804599E0(register void *self, register void *actor, register int index)
{
    fn_80112214(lbl_80567770 + index * 0x60, lbl_80567760[index].handle2C, 1);
    fn_8045BFA0(self, fn_80118C64(lbl_8066F06C));
    fn_8045BF50(self, fn_80118C3C(lbl_8066F068));
}

class ObjL
{
public:
    char data[0x18];
    ObjL(register int a, register int b, register int c, register int d, register int e);
    void *operator new(unsigned size) __asm__("fn_8045BB98");
};

extern "C" ObjL *fn_80459A80(register int handle, register int index)
{
    void *actor = fn_800ACFA8(lbl_80567760[index].source);
    int value = 0;
    if (actor != 0 && fn_800B0C58(actor)) {
        value = lbl_804CF638[fn_8009ABEC(fn_800B1568(actor))];
    }
    return new ObjL(0, 0, 0x32, value, 0);
}

extern "C" int fn_80459B6C(register void *actor, register int index)
{
    if (lbl_8066BD60 != 0) {
        return 0;
    }
    return 1;
}

extern "C" void fn_8045BB0C(void *self, int v);
extern "C" void fn_8045BABC(void *self, int v);
extern "C" void fn_8045BB54(void *self, int v);

extern "C" void fn_80459BB4(register void *self, register void *actor, register int index)
{
    fn_80112214(lbl_80567770 + index * 0x60, lbl_80567760[index].handle2C, 1);
    fn_8045BB0C(self, fn_80118C64(lbl_8066F06C));
    fn_8045BABC(self, fn_80118C3C(lbl_8066F068));
    float h = fn_800670CC(actor);
    int value = (int)(h * 200.0f);
    if (value < 0) {
        value = 0;
    }
    if (value > 1000) {
        value = 1000;
    }
    fn_8045BB54(self, value);
}

inline int sn_return_decl(int a) { return a; }

struct Level
{
    int pad0;
    int value; // +0x4
    int value2; // +0x8
    int value3; // +0xC
};

extern "C" void fn_80459CBC(register Level *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 100) {
        v = 100;
    }
    self->value = v;
}

extern "C" void fn_80459D00(register Level *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 100) {
        v = 100;
    }
    self->value2 = v;
}

extern "C" void fn_80459D44(register Level *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 100) {
        v = 100;
    }
    self->value3 = v;
}

extern "C" void fn_802460AC(void *p);

extern "C" void fn_80459D88(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_80459DC0(register Level *self, register int v)
{
    if (v < 0) {
        v = 0;
    } else if (v > 10) {
        v = 10;
    }
    self->value = v;
}

extern "C" void fn_80459E04(register void *self)
{
    fn_802460AC(self);
}

extern "C" void fn_80459E3C(register void *self)
{
    fn_802460AC(self);
}
