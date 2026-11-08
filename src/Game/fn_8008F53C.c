// fn_8008F53C: drops a reference to a motion set, freeing it on the last one.
// fn_8008F59C: frees a motion set: its registry entry, each overlay's animations and buffer, then the set.

typedef struct Motion
{
    int state;          // +0x00
    void *anim;         // +0x04
    unsigned int flags; // +0x08
    float speed;        // +0x0C
    float dist;         // +0x10
    float move;         // +0x14
} Motion;

typedef struct Overlay
{
    char name[0x20]; // +0x00
    char pad20[0x4];
    unsigned int n;  // +0x24
    Motion *items;   // +0x28
} Overlay;

typedef struct MotionSet
{
    int refs;            // +0x000
    char name[0x20];     // +0x004
    unsigned int count;  // +0x024
    Overlay overlays[6]; // +0x028
    int x130;            // +0x130
} MotionSet;

extern void *lbl_8066B8F4; // the motion-set registry
extern void fn_80090F7C(MotionSet *set);
extern void fn_80091028(MotionSet *set);
extern void fn_801B4AA8(void *registry, char *key);
extern void fn_8019A51C(void *anim);
extern void fn_801ACC44(void *p);

int fn_8008F53C(register MotionSet *set)
{
    set->refs--;
    if (set->refs)
        return 1;
    fn_80090F7C(set);
    return 1;
}

void fn_8008F59C(register MotionSet *set)
{
    unsigned int i;
    unsigned int j;

    fn_80091028(set);
    fn_801B4AA8(lbl_8066B8F4, set->name);
    for (i = 0; i < set->count; i++) {
        if (set->overlays[i].n) {
            for (j = 0; j < set->overlays[i].n; j++)
                fn_8019A51C(set->overlays[i].items[j].anim);
            fn_801ACC44(set->overlays[i].items);
        }
    }
    fn_801ACC44(set);
}
