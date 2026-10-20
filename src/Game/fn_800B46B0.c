// The four GameFlow teardown methods, then fn_800B47C0, the per-frame draw of the versus loading
// screen. The class and its fields are in docs/versus.md section 6.
// A .c unit: the file is pair-less C++, so `this` is a register first parameter.
// Owns the .rodata pool at 0x8048BD68-0x8048BDB8, which reaches past its own literals (see below).

typedef struct Vec2
{
    float x;
    float y;
} Vec2;

// A loading-screen image; only its size is known.
typedef struct Image
{
    char unk0[0x58];
    unsigned short width;  // +0x58
    unsigned short height; // +0x5A
} Image;

typedef struct GameFlow
{
    char unk0[0x10];
    int unk10;                 // +0x10
    char unk14[0x158];
    int unk16C;                // +0x16C
    Image *image170;           // +0x170
    Image *image174;           // +0x174
    int unk178;                // +0x178
    char unk17C[0x5C];
    int unk1D8;                // +0x1D8
} GameFlow;

extern char lbl_80593BE8[]; // the globals object of Game/fn_80443908.cpp
extern void *lbl_8066D6DC;  // the overlay text object (docs/versus.md section 6)

extern void fn_8002A624(void);
extern void fn_8044606C(GameFlow *flow);
extern void fn_800B5548(GameFlow *flow);
extern void fn_80232B78(int handle);
extern void fn_804325CC(char *globals);

extern Vec2 *fn_8042ACC0(Vec2 *v, float x, float y);
extern void fn_80426A54(Vec2 *v, float x, float y);
extern int fn_800FE284(int index);
extern int fn_80426E88(void *text, int font);
extern void fn_8042E894(void *text, int a);
extern void fn_800186C8(int a, Image *image, int b, int c, Vec2 *pos, float w, float h,
                        float alpha, int color);

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

void fn_800B47C0(register GameFlow *this)
{
    Vec2 offset;
    int color1;
    int color2;
    float width;
    float height;
    Vec2 pos;

    if (!this->unk178 || !this->image170 || !this->image174) {
        return;
    }

    fn_8042ACC0(&offset, -15.0f, -15.0f);
    color1 = 0xFFFF0000; // color1, color2, width and height are stored and never read
    color2 = -1;
    width = this->image170->width;
    height = this->image170->height + this->image174->height;
    fn_80426E88(lbl_8066D6DC, fn_800FE284(3));
    fn_8042ACC0(&pos, 0.0f, 0.0f);
    fn_800186C8(0, 0, 0x31, 0, &pos, 640.0f, 480.0f, 255.0f, 0);
    fn_80426A54(&pos, offset.x + 192.0f, offset.y + 184.0f);
    fn_800186C8(0, this->image170, 0xC, 0, &pos, this->image170->width, this->image170->height,
                255.0f, 0xFFFFFF);
    fn_80426A54(&pos, offset.x + 192.0f, offset.y + 312.0f);
    fn_800186C8(0, this->image174, 0xC, 0, &pos, this->image174->width, this->image174->height,
                255.0f, 0xFFFFFF);
    fn_8042E894(lbl_8066D6DC, 0);
    return; // two jumps to the epilogue here: don't collapse the pair
    return;
}

// fn_800B5124's format string (Game/fn_800B4CF8.c), defined here so this unit's .rodata ends 8-aligned
const char lbl_8048BD9C[] = "kT_INSERT_CONTROLLER%d_NGC";
