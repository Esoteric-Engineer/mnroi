// A handle whose constructor allocates its 0x18-byte implementation object (fn_804336D4).
// Class names are guesses; the vtable is lbl_804F3148, shared with the 8-byte-object handle at 0x804334D0.

extern "C" char lbl_804F3148[];

class LinkImpl
{
public:
    char data[0x18];
    LinkImpl(void *owner, const void *name);
};

class Link
{
public:
    LinkImpl *impl;   // +0x0
    const void *vptr; // +0x4
    Link(void *owner, const void *name);
};

Link::Link(register void *owner, register const void *name)
{
    vptr = lbl_804F3148;
    impl = new LinkImpl(owner, name);
}
