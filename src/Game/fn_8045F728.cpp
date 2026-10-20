// Constructor over the base at fn_8045F804: vptr lbl_804F5B08, flag at +0x8, a zeroed 0x318-byte block at +0x18. Names are guesses.
class Base
{
public:
    Base() __asm__("__11MachineBase");
    virtual void first();
};

struct Chunk
{
    char b[0x318];
};

class Machine : public Base
{
public:
    int pad;       // +0x4
    int flag;      // +0x8
    int padC;      // +0xC
    int size;      // +0x10
    int zero;      // +0x14
    Chunk buf;     // +0x18
    int w330;      // +0x330
    int w334;      // +0x334
    Machine();
    virtual void second();
};

Machine::Machine() : flag(1), size(0x19000), zero(0), buf()
{
    w330 = 0;
    w334 = 0;
}
