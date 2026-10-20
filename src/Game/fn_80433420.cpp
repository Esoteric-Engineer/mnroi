// Constructors of the async loader (0x40 bytes), the attract-movie object (0x18 bytes) and Link's copy constructor; names are guesses, see fn_80432B4C.cpp.

extern "C" void fn_80433BD4(void *self) __asm__("__8LoadList");

class CAsyncLoader
{
public:
    int unk0;
    int unk4;
    char sub8[0x38]; // +0x8, built by fn_80433BD4
    CAsyncLoader();
};

CAsyncLoader::CAsyncLoader()
{
    unk0 = 0;
    unk4 = 0;
    fn_80433BD4(sub8);
}

class cAttractMovie
{
public:
    int unk0;
    int unk4;
    int unk8;
    int unkC;
    int unk10; // 6
    int unk14; // 60000
    cAttractMovie();
};

cAttractMovie::cAttractMovie()
{
    unk0 = 0;
    unk4 = 0;
    unk8 = 0;
    unkC = 0;
    unk10 = 6;
    unk14 = 60000;
}

extern "C" char lbl_804F3148[];
extern "C" void fn_8042A350(void *impl);

class Link
{
public:
    void *impl;       // +0x0
    const void *vptr; // +0x4
    Link(const Link &other);
};

Link::Link(register const Link &other)
{
    vptr = lbl_804F3148;
    fn_8042A350(other.impl);
    impl = other.impl;
}
