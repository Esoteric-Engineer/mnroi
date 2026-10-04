// A handle whose constructor allocates its 0x18-byte implementation object (fn_80444034).
// The vtable at lbl_804F2E28 is shared with the sibling at 0x8042841C. Class names are guesses.

extern "C" char lbl_804F2E28[];

class Impl
{
public:
    char data[0x18];
    Impl(void *owner, const void *name);
};

class Handle
{
public:
    Impl *impl;       // +0x0
    const void *vptr; // +0x4
    Handle(void *owner, const void *name);
};

Handle::Handle(register void *owner, register const void *name)
{
    vptr = lbl_804F2E28;
    impl = new Impl(owner, name);
}
