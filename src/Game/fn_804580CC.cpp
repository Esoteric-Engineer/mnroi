// Obj90/Obj92 factories, fn_804581A0 (record check caching a node handle at +0x50) and fn_804582F0 (record setup); docs/versus.md section 5, row 2.

struct Slot
{
    void *owner;
    char pad0[0x1C];
    int source; // +0x20
    int state24; // +0x24
    char pad1[4];
    int handle2C; // +0x2C
    char pad2a[0x20];
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
