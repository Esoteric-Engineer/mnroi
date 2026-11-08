// Motion-set lookups by state (docs/characters.md section 4):
// the clip, flags and speed of a state's motion, and the dist, speed and move-rate getters over the base overlay.

struct Motion {
    int state;          // +0x00
    struct Clip *anim;  // +0x04
    unsigned int flags; // +0x08
    float speed;        // +0x0C
    float dist;         // +0x10
    float move;         // +0x14, 1 / the .nms `move` value
};

struct Clip {
    char pad0[0x28];
    float length; // +0x28
};

struct Overlay {
    char name[0x20]; // +0x00
    char pad20[0x4];
    unsigned int n;  // +0x24
    Motion *items;   // +0x28
};

struct MotionSet {
    int refs;            // +0x000
    char name[0x20];     // +0x004
    unsigned int count;  // +0x024
    Overlay overlays[6]; // +0x028
    int x130;            // +0x130
};

extern "C" int fn_80171F8C(void);

// The clip of `state` in overlay `ov`. A run of entries for the same state (none flagged 0x400, `special`)
// are variants: `f` in [0, 1) picks one, a negative `f` a random one.
extern "C" Clip *fn_8008F8EC(register Overlay *ov, int state, unsigned int *flags, float *scale, float f)
{
    unsigned int count = 0;
    unsigned int k;
    unsigned int i;
    unsigned int n;

    for (i = 0; i < ov->n; i++) {
        if (ov->items[i].state == state) {
            k = i;
            for (; i < ov->n; i++) {
                if (ov->items[i].state == state && !(ov->items[i].flags & 0x400))
                    count++;
                else
                    break;
            }
            if (count > 1) {
                if (f >= 0.0f)
                    n = (unsigned int)((float)count * f);
                else
                    n = (unsigned int)((float)fn_80171F8C() * 4.656612873077393e-10f * (float)count);
                k = k + n >= k ? (k + n <= k + count ? k + n : k + count) : k;
            }
            *flags = ov->items[k].flags;
            *scale = ov->items[k].speed;
            return ov->items[k].anim;
        }
    }
    return 0;
}

// The clip of `state` in overlay `idx`.
extern "C" Clip *fn_8008FC18(register MotionSet *set, int state, unsigned int *flags, float *scale, unsigned int idx, float f)
{
    Clip *clip;

    if (idx >= set->count)
        idx = 0;
    clip = fn_8008F8EC(&set->overlays[idx], state, flags, scale, f);
    if (!clip && idx)
        clip = fn_8008F8EC(&set->overlays[0], state, flags, scale, f);
    return clip;
}

extern "C" Clip *fn_8008FCEC(register MotionSet *set, int state, int idx, float f)
{
    unsigned int flags;
    float scale;

    return fn_8008FC18(set, state, &flags, &scale, idx, f);
}

// `dist` of `state` in the base overlay, 0 when absent.
extern "C" float fn_8008FD58(register MotionSet *set, int state)
{
    unsigned int i;

    for (i = 0; i < set->overlays[0].n; i++) {
        if (set->overlays[0].items[i].state == state)
            return set->overlays[0].items[i].dist;
    }
    return 0.0f;
}

// `fps / 30` of `state` in the base overlay, 30 when absent.
extern "C" float fn_8008FDF0(register MotionSet *set, int state)
{
    unsigned int i;

    for (i = 0; i < set->overlays[0].n; i++) {
        if (set->overlays[0].items[i].state == state)
            return set->overlays[0].items[i].speed;
    }
    return 30.0f;
}

// The playback rate for moving at `v`: v * clip length / `move`, 30 when absent.
extern "C" float fn_8008FE88(register MotionSet *set, int state, float v)
{
    unsigned int i;

    for (i = 0; i < set->overlays[0].n; i++) {
        if (set->overlays[0].items[i].state == state)
            return set->overlays[0].items[i].move * v * set->overlays[0].items[i].anim->length;
    }
    return 30.0f;
}
