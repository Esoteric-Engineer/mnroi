// Four GameFlow teardown methods: the three the destructor calls, then fn_800B4764.
// A .c unit: the file is pair-less C++, so `this` is a register first parameter.
// The class and its fields are in docs/versus.md section 6.

typedef struct GameFlow
{
    char unk0[0x10];
    int unk10;                 // +0x10
    char unk14[0x158];
    int unk16C;                // +0x16C
    char unk170[0x8];
    int unk178;                // +0x178
    char unk17C[0x5C];
    int unk1D8;                // +0x1D8
} GameFlow;

extern char lbl_80593BE8[]; // the globals object of Game/fn_80443908.cpp

extern void fn_8002A624(void);
extern void fn_8044606C(GameFlow *flow);
extern void fn_800B5548(GameFlow *flow);
extern void fn_80232B78(int handle);
extern void fn_804325CC(char *globals);

void fn_800B46B0(register GameFlow *this)
{
}

void fn_800B46D0(register GameFlow *this)
{
}

void fn_800B46F0(register GameFlow *this)
{
    if (this->unk1D8) {
        this->unk1D8 = 0;
    }
    fn_8002A624();
    fn_8044606C(this);
    fn_800B5548(this);
    if (this->unk16C) {
        fn_80232B78(this->unk16C);
        this->unk16C = 0;
    }
}

void fn_800B4764(register GameFlow *this)
{
    if (this->unk178) {
        if (this->unk10) {
            fn_804325CC(lbl_80593BE8);
        }
        this->unk178 = 0;
    }
}
