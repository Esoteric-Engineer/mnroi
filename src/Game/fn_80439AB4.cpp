// Cue-vtable handle constructor that owns a 0x18-byte implementation (fn_8043A0A4); class names are guesses.

extern "C" char lbl_804F2E10[];

class OwnedCueImpl
{
public:
    char data[0x18];
    OwnedCueImpl(void *owner, const int *name);
};

class OwnedCue
{
public:
    OwnedCueImpl *impl; // +0x0
    const void *vptr;   // +0x4
    OwnedCue(void *owner, const int *name);
};

OwnedCue::OwnedCue(register void *owner, register const int *name)
{
    vptr = lbl_804F2E10;
    impl = new OwnedCueImpl(owner, name);
}
