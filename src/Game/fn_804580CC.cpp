// Obj90/Obj92/ObjC (guessed name) factories, fn_804581A0 (record check caching a node handle at +0x50) and fn_804582F0 (record setup), fn_8045849C (actor check), fn_8045855C (record setup), fn_8045866C (actor check), fn_8045873C and fn_8045895C (record setups), fn_804589FC (`new ObjE(0)` factory), fn_80458A5C (actor check, height compare), fn_80458B4C (record setup passing an int percentage of two actor floats), fn_80458CDC (record setup), fn_80458D7C (`new ObjG` factory resetting record +0x34 from -1); docs/versus.md section 5, row 2.

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
    char pad2b[0x18];
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
