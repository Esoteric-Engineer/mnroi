// fn_8008F3B8: the index of a motion-state name in the table lbl_8054F1F0 (0x174 entries), 0 if it is not there.
// fn_8008F470: returns the motion set <name> from the motion-set registry, loading it on a miss.

typedef struct MotionSet
{
    int refs;     // +0x00
    char name[1]; // +0x04, the registry key
} MotionSet;

extern void *lbl_8066B8F4; // the motion-set registry
extern void *fn_801B48AC(void *registry, char *name);
extern void fn_801B4628(void *registry, void *key, void *value);
extern void fn_80443908(MotionSet *set);
extern void fn_80091028(MotionSet *set);
extern MotionSet *fn_8008FF48(char *name, int a, int b);
extern char *lbl_8054F1F0[0x174]; // motion-state names
extern int stricmp(const char *a, const char *b);

int fn_8008F3B8(const char *name)
{
    unsigned int i;

    i = 0;
    while (i <= 0x173) {
        if (lbl_8054F1F0[i] != 0 && stricmp(lbl_8054F1F0[i], name) == 0)
            return i;
        i++;
    }
    return 0;
}

MotionSet *fn_8008F470(char *name, int a, int b)
{
    MotionSet *set = fn_801B48AC(lbl_8066B8F4, name);

    if (set) {
        fn_80443908(set);
        fn_80091028(set);
        return set;
    }
    set = fn_8008FF48(name, a, b);
    if (!set)
        return 0;
    set->refs = 1;
    fn_801B4628(lbl_8066B8F4, set->name, set);
    return set;
}
