// Constructor over the base at fn_8045F838 (BlockBase): the vtable lbl_804F5B98, a zeroed 0x1C-byte block at +0x8 and a flag at +0x24. Names are guesses.
extern "C" void *memset(void *dst, int c, unsigned int n);
extern "C" int fn_80126AB8(void *self);

class Base
{
public:
    Base() __asm__("__9BlockBase");
    virtual void first();
};

struct Chunk
{
    char b[0x1C];
};

class Block : public Base
{
public:
    int pad; // +0x4
    Chunk buf; // +0x8
    int ready; // +0x24
    Block();
    virtual void second();
};

Block::Block() : buf()
{
    ready = 1;
    memset(&buf, 0, 0x1C);
    fn_80126AB8(&buf);
}
