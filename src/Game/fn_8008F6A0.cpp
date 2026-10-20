// Closes the motion set's current overlay: inherits the states the parse left out from base's overlay of the same index, then copies the buffer out; docs/characters.md section 4.

struct Motion {
    int state;          // +0x00
    void *anim;         // +0x04
    unsigned int flags; // +0x08
    float speed;        // +0x0C
    float dist;         // +0x10
    float move;         // +0x14
};

struct Overlay {
    char name[0x20];   // +0x00
    char pad20[0x4];
    unsigned int n;    // +0x24
    Motion *items;     // +0x28
};

struct MotionSet {
    int refs;              // +0x000
    char name[0x20];       // +0x004
    unsigned int count;    // +0x024
    Overlay overlays[6];   // +0x028
    int x130;              // +0x130
};

extern "C" {
void *memcpy(void *dst, const void *src, unsigned n);
void *fn_801AD324(int size, const char *tag, int line);
void *fn_80198DE4(void *anim, int flags);
extern Motion lbl_8054FE10[]; // the parse buffer
extern const char lbl_8048A16C[]; // "Animation:Motions"
}

extern "C" int fn_8008F6A0(register MotionSet *set, MotionSet *base)
{
    Overlay *dst = &set->overlays[set->count];

    if (base) {
        Overlay *src = &base->overlays[set->count];
        unsigned int i;

        for (i = 0; i < src->n; i++) {
            unsigned int j;
            Motion *item = &src->items[i];

            for (j = 0; j < dst->n; j++) {
                if (item->state == lbl_8054FE10[j].state)
                    break;
            }
            if (j == dst->n) {
                memcpy(&lbl_8054FE10[dst->n], item, sizeof(Motion));
                lbl_8054FE10[dst->n].anim = fn_80198DE4(item->anim, 0x20000);
                dst->n++;
            }
        }
    }
    if (dst->n) {
        dst->items = (Motion *)fn_801AD324(dst->n * sizeof(Motion), lbl_8048A16C, 0x17A);
        if (!dst->items)
            goto fail;
        memcpy(dst->items, lbl_8054FE10, dst->n * sizeof(Motion));
    } else
        dst->items = 0;
    if (set->count <= 5) {
        set->count++;
        return 1;
    }
    return 0;
fail:
    return 0;
}
