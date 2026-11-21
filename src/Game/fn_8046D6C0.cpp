// A 4-byte-element array and a pooled object with a vtable at +0x0, then the destructors of cRingOut,
// cEndMission, cCountDown and cSoundEvent (docs/story.md row 7). Array layout as in Game/fn_8043ED84.cpp.

inline int sn_return_decl(int a) { return a; }

struct IntArray {
    int *data;        // +0x0
    int n;            // +0x4
    unsigned int cap; // +0x8
};

struct PoolObj {
    char *vptr; // +0x0, lbl_80502F18
};

struct ArrayHolder : PoolObj {
    IntArray arr; // +0x4
};

class Heap {
public:
    char data[0x3C]; // the vptr follows at +0x3C
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void release(void *p, int size, int align); // vtable +0x30
};

struct cScript {
    char d[0x28];
};
struct cRingOut : cScript {};
struct cEndMission : cScript {};
struct cCountDown : cScript {};
struct cSoundEvent : cScript {};

extern "C" {

Heap *fn_802E29A8();
void fn_802E1A24(register IntArray *self, int elemSize);
void __builtin_delete(void *p);
void fn_8007975C(cScript *self, int inChrg);
void fn_8046D960(register PoolObj *self, register int inChrg);
void fn_8046DA28(register IntArray *self, register int inChrg);
int fn_8046D9F8(register IntArray *self);
void fn_8046DA78(register IntArray *self);
void fn_8046DAD4(register void *p);
void fn_8046DB48(register void *p, register int count, register int align);

extern char lbl_80502F18[];

void fn_8046D6C0(register void *self, register int a)
{
}

void fn_8046D6E4(register ArrayHolder *self, register int inChrg)
{
    fn_8046DA28(&self->arr, 2);
    fn_8046D960(self, inChrg);
}

}

inline void sn_label_decl() { clear:; }

extern "C" {

int fn_8046D734(register IntArray *self)
{
    return self->n;
}

int *fn_8046D768(register IntArray *self, register int i)
{
    return &self->data[i];
}

int fn_8046D7AC(register IntArray *self, register const int *key)
{
    int i;

    i = 0;
    while (i < self->n) {
        if (self->data[i] == *key)
            return i;
        i++;
    }
    return -1;
}

void fn_8046D83C(register IntArray *self, register const int *v)
{
    if (self->n == fn_8046D9F8(self))
        fn_802E1A24(self, 4);
    self->data[self->n++] = *v;
}

void fn_8046D8C8(register IntArray *self, register int i)
{
    self->n--;
    self->data[i] = self->data[self->n];
}

PoolObj *fn_8046D92C(register PoolObj *self)
{
    self->vptr = lbl_80502F18;
    return self;
}

void fn_8046D960(register PoolObj *self, register int inChrg)
{
    self->vptr = lbl_80502F18;
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}

IntArray *fn_8046D9B8(register IntArray *self)
{
    self->data = 0;
    self->n = 0;
    self->cap = 0x80000000;
    return self;
}

int fn_8046D9F8(register IntArray *self)
{
    return self->cap & 0x3FFFFFFF;
}

void fn_8046DA28(register IntArray *self, register int inChrg)
{
    fn_8046DA78(self);
    if (inChrg & 1)
        fn_8046DAD4(self);
}

void fn_8046DA78(register IntArray *self)
{
    if ((self->cap & 0x80000000) == 0)
        fn_8046DB48(self->data, fn_8046D9F8(self), 0x14);
}

void fn_8046DAD4(register void *p)
{
    fn_802E29A8()->release(p, 0xC, 0x14);
}

void fn_8046DB48(register void *p, register int count, register int align)
{
    Heap &heap = *fn_802E29A8();

    heap.release(p, count * 4, align);
}

void fn_8046DBD4(register cRingOut *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046DC14(register cEndMission *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046DC54(register cCountDown *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

void fn_8046DC94(register cSoundEvent *self, register int inChrg)
{
    fn_8007975C(self, inChrg);
}

}
