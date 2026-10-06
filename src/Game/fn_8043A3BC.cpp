// Constructors of the 0x50-byte element and of the holder that array-constructs 64 of them (docs/versus.md, row 8).

extern "C" void fn_8042D7B0(void *self);

class Element
{
public:
    char data[0x50];
    Element();
};

Element::Element()
{
    fn_8042D7B0(this);
}

class Root
{
public:
    char data[0xB0]; // +0x0, constructed by fn_8042D7B0
    Root() __asm__("fn_8042D7B0");
};

class ElementSet : public Root
{
public:
    Element elements[64]; // +0xB0
    ElementSet();
};

ElementSet::ElementSet()
{
}
