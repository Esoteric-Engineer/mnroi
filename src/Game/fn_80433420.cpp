// Constructors of the async loader (0x40 bytes) and the attract-movie object (0x18 bytes); names are guesses, see fn_80432B4C.cpp.

extern "C" void fn_80433BD4(void *self);

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
