// Allocates a motion set, names it <name> and, unless told not to, parses <name>.nms into it; docs/versus.md row 23.

struct MotionSet {
    int refs;       // +0x00
    char name[0x20]; // +0x04
    char pad24[0x134 - 0x24];
};

extern "C" {
void *memset(void *dst, int c, unsigned n);
char *strncpy(char *dst, const char *src, unsigned n);
void *fn_801AD324(int size, const char *tag, int line);
int fn_80090034(MotionSet *set, int flags);
void fn_8008F53C(MotionSet *set);
extern const char lbl_8048A16C[]; // "Animation:Motions"
}

extern "C" MotionSet *fn_8008FF48(char *name, int flags, int noParse)
{
    MotionSet *set = (MotionSet *)fn_801AD324(0x134, lbl_8048A16C, 0x24E);

    if (!set)
        goto fail;
    memset(set, 0, 0x134);
    strncpy(set->name, name, 0x20);
    set->name[0x1F] = 0;
    if (!noParse && !fn_80090034(set, flags))
        goto fail;
    return set;
fail:
    if (set)
        fn_8008F53C(set);
    return 0;
}
