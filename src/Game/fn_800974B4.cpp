// Actor's constructor, the first function of the source file that ends at 0x8009B2E0.
// Field meanings are in docs/characters.md sections 3 and 5.

extern "C" void fn_800AC7F8(void *self);
extern "C" void __6Vector(void *self);
extern char lbl_804F4DA0[];

class Actor
{
public:
    Actor();

    char kind;      // +0x0
    char pad1[0x193];
    int f194;       // +0x194
    void *vptr;     // +0x198
    int f19C;
    int f1A0;       // +0x1A0
    int f1A4;
    int f1A8;
    int f1AC;       // +0x1AC, character type
    int f1B0;
    int f1B4;
    int f1B8;
    int f1BC;       // +0x1BC, model
    int f1C0;
    char pad1C4[0xC];
    char vec1D0[0x10];
    char vec1E0[0x10];
    char vec1F0[0x10];
    int f200;       // +0x200
    char f204;
    char f205;
    char pad206[2];
    int f208;
    int f20C;
    int f210;
    float f214;
    int f218;
    int f21C;
    int f220;
    int f224;
    int f228;
    int f22C;
    float f230;
    int f234;
};

Actor::Actor()
{
    fn_800AC7F8(this);
    vptr = lbl_804F4DA0;
    __6Vector(vec1D0);
    __6Vector(vec1E0);
    __6Vector(vec1F0);
    kind = 0xE;
    f1A0 = 0;
    f1A4 = 0;
    f1A8 = 0;
    f1AC = 0;
    f194 = 0;
    f1B0 = 0;
    f1B4 = 0;
    f1BC = 0;
    f20C = 0;
    f208 = 0;
    f210 = 0;
    f1C0 = 0;
    f200 = 0;
    f204 = 0;
    f205 = 0;
    f22C = 0;
    f214 = 1.0f;
    f218 = 0;
    f220 = 0;
    f21C = 0;
    f224 = 0;
    f228 = 0;
    f234 = 0;
    f230 = 1.0f;
}
