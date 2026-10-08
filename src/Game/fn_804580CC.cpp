// Factory for an Obj90 (docs/versus.md section 5, row 2): the player record's actor picks the third setter value from lbl_804CF638.

struct Slot
{
    void *owner;
    char pad0[0x1C];
    int source; // +0x20
    char pad1[0x3C];
} __attribute__((aligned(8)));

extern Slot lbl_80567760[];
extern int lbl_804CF638[];
extern "C" void *fn_800ACFA8(int handle);
extern "C" void *fn_800B1568(void *actor);
extern "C" unsigned int fn_8009ABEC(void *entity);

class Obj90
{
public:
    char data[0x14];
    Obj90(register int a, register int b, register int c, register int d);
    void *operator new(unsigned size) __asm__("fn_8045C458");
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
