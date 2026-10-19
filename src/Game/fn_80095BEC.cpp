// PlayerSlot constructor (G+0x10, 8 slots of 0xB0 bytes): a default Vector at +0x90, CPU difficulty -1 at +0x64 and 0 at +0x80. docs/versus.md section 4.1.

class Vector
{
public:
    float x;
    float y;
    float z;
    float w;
    Vector();
} __attribute__((aligned(8)));

class PlayerSlot
{
public:
    char pad0[0x64];
    int difficulty; // +0x64
    char pad68[0x18];
    int unk80;      // +0x80
    char pad84[0xC];
    Vector pos;     // +0x90
    char padA0[0x10];
    PlayerSlot();
};

PlayerSlot::PlayerSlot()
{
    difficulty = -1;
    unk80 = 0;
}
