// Task methods (enter, exit, update per class), from SLEEP on; see docs/ai.md row 12 and section 4.4.
// Owns .rodata 0x8049B838-0x8049B840 (0.0f per function).

struct Ent {
    int pad;
};

struct PEnt : Ent { // matching_notes 44
    int x;
};

struct Self {
    void *ai;    // +0x0
    void *brain; // +0x4
};

extern "C" {
void *fn_80464068(void *ai);
void *fn_80462780(void *ai);
void fn_804618B0(void *set);
int fn_80151B90(void *brain, void *task);
void *fn_8015105C(void *brain, int id);
void fn_8046412C(void *ai, int bit);
void fn_80464170(void *ai, int bit);
float fn_80461F94(void *ai);
float fn_8046439C(void *ai);
float fn_80461F10(void *ai);
float fn_80461F68(void *ai);
float fn_80464318(void *ai);
float fn_80461EE4(void *ai);
void fn_80442130(void *ai, unsigned int bit);
void fn_80442174(void *ai, unsigned int bit);
PEnt *fn_80442080(void *ai);
int fn_80133208(void *actor);
int fn_801368B8(void *ai);
float fn_8015E64C(void *ai);
float fn_800B1884(Ent &actor, int id);
void *fn_80134870(void *ai);
int fn_800B0C58(void *actor);
void *fn_804420D8(void *ai);
void fn_8014F7B0(void *list, int mode);
char *fn_804420AC(void *ai);
int fn_800B13D8(void *actor);
void fn_8014B63C(char *mover, int handle, int flag);
}

inline int sn_return_decl(int a) { return a; } // sets the flag: no function-end branch pair (prodg.md)

// SLEEP enter
extern "C" int fn_80152AE8(register Self *self)
{
    fn_804618B0(fn_80464068(self->ai));
    fn_804618B0(fn_80462780(self->ai));
    return 1;
}

// SLEEP exit
extern "C" int fn_80152B48(register Self *self)
{
    return 1;
}

// SLEEP update
extern "C" int fn_80152B70(register Self *self)
{
    if (fn_80151B90(self->brain, self)) {
        fn_8015105C(self->brain, 1);
    } else {
    }
    return 1;
}

// SEARCH enter
extern "C" int fn_80152BD0(register Self *self)
{
    fn_8046412C(self->ai, 0);
    fn_8046412C(self->ai, 5);
    fn_8046412C(self->ai, 3);
    if (fn_80461F94(self->ai) > 0.0f)
        fn_8046412C(self->ai, 1);
    if (fn_8046439C(self->ai) > 0.0f)
        fn_8046412C(self->ai, 2);
    fn_8046412C(self->ai, 6);
    fn_804618B0(fn_80462780(self->ai));
    fn_80442130(self->ai, 0x1a);
    fn_80442130(self->ai, 0x1c);
    fn_80442130(self->ai, 0);
    if (fn_80133208(fn_80442080(self->ai))) {
        if (fn_80461F10(self->ai) > 0.0f)
            fn_80442130(self->ai, 1);
        else if (fn_80461F68(self->ai) > 0.0f)
            fn_80442130(self->ai, 2);
        if (fn_80464318(self->ai) > 0.0f)
            fn_80442130(self->ai, 0x1d);
    }
    fn_80442130(self->ai, 3);
    fn_80442130(self->ai, 4);
    fn_80442130(self->ai, 0xf);
    if (fn_801368B8(self->ai)) {
        register float d = fn_8015E64C(self->ai);
        if (d >= fn_800B1884(*fn_80442080(self->ai), 0xd4))
            fn_80442130(self->ai, 0xe);
    }
    fn_80442130(self->ai, 0x15);
    fn_80442130(self->ai, 0x16);
    fn_80442130(self->ai, 0x17);
    fn_80442130(self->ai, 0x1b);
    if (!fn_80134870(self->ai) || (fn_80134870(self->ai) && !fn_800B0C58(fn_80134870(self->ai))))
        fn_8014F7B0(fn_804420D8(self->ai), 0);
    if (fn_80134870(self->ai))
        fn_8014B63C(fn_804420AC(self->ai), fn_800B13D8(fn_80134870(self->ai)), 1);
    return 1;
}

// SEARCH exit
extern "C" int fn_80152EB8(register Self *self)
{
    fn_80464170(self->ai, 4);
    if (fn_80461F94(self->ai) > 0.0f)
        fn_80464170(self->ai, 1);
    if (fn_8046439C(self->ai) > 0.0f)
        fn_80464170(self->ai, 2);
    if (fn_80461EE4(self->ai) > 0.0f)
        fn_80442174(self->ai, 0x12);
    return 1;
}
