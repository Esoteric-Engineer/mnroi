// Advances an animation channel by `dt`. (docs/characters.md section 4). Returns 1 when the channel ended or faded out.

struct Event {
    float frame;           // +0x0
    unsigned short type;   // +0x4
    unsigned short param;  // +0x6
    unsigned int value;    // +0x8
};

struct Clip {
    char pad0[0x28];
    float length;          // +0x28
    unsigned int count;    // +0x2C, per-track state words
    char pad30[0xC];
    unsigned int nEvents;  // +0x3C
    Event *events;         // +0x40
};

struct Channel {
    float speed;           // +0x00
    float time;            // +0x04
    float weight;          // +0x08
    float fadeRate;        // +0x0C
    char pad10[0x4];
    unsigned int flags;    // +0x14, motion flags (0x1 noloop, 0x10 endpause, 0x20 endtag) and state bits
    char pad18[0x4];
    Clip *clip;            // +0x1C
    int *state;            // +0x20, clip->count ints
    char pad24[0x8];
};

struct Animator {
    Channel main;          // +0x00
    Channel blend;         // +0x2C
};

typedef void (*EventFn)(Channel *ch, Animator *anim, int type, float frame, int param, unsigned int value);

inline int sn_return_decl(int a) { return a; }

extern "C" {
void *memset(void *dst, int value, unsigned n);
extern EventFn lbl_8066C58C; // the animation event handler
int fn_80465A0C(Channel *ch); // flags & 0x400000: fading out
int fn_80465A9C(Channel *ch); // flags & 0x200000: events muted
void fn_8019DACC(Channel *ch, int a);
void fn_8019C408(Animator *anim);
void fn_8019DB24(Channel *ch, float time);

int fn_8019B2D4(register Channel *ch, float dt, Animator *anim, int quiet)
{
    float step;
    float loops;
    unsigned int i;
    float t;
    float d;

    if (!ch->clip || dt == 0.0f)
        return 0;
    if (fn_80465A0C(ch)) {
        ch->weight -= ch->fadeRate * dt;
        if (ch->weight <= 0.0f) {
            fn_8019DACC(ch, 1);
            return 1;
        }
    }
    if (ch->flags & 0x1000)
        return 0;
    step = dt * ch->speed;
    t = ch->time + step;
    if (lbl_8066C58C && ch->clip->nEvents && !fn_80465A9C(ch) && !quiet) {
        for (i = 0; i < ch->clip->nEvents; i++) {
            d = ch->clip->events[i].frame - t;
            if (d > 0.0f)
                break;
            if (-d <= step) {
                Clip *clip = ch->clip;
                ch->time = ch->clip->events[i].frame;
                lbl_8066C58C(ch, anim, ch->clip->events[i].type, ch->clip->events[i].frame,
                             ch->clip->events[i].param, ch->clip->events[i].value);
                if (!ch->clip || ch->clip != clip)
                    return 0;
                if (ch->time != ch->clip->events[i].frame)
                    return 0;
            }
        }
    }
    ch->time = t;
    if (ch->time >= ch->clip->length) {
        if (ch->flags & 0x10) {
            ch->flags |= 0x1000;
            ch->time = ch->clip->length;
            if ((ch->flags & 0x20) && !fn_80465A9C(ch) && !quiet)
                lbl_8066C58C(ch, anim, 0x14, ch->time, 0, 0);
            return 0;
        }
        if (ch->flags & 1) {
            unsigned int flags = ch->flags;
            if ((ch->flags & 0x20) && !fn_80465A9C(ch) && !quiet) {
                Clip *clip = ch->clip;
                d = ch->time - ch->clip->length;
                lbl_8066C58C(ch, anim, 0x14, ch->time, 0, 0);
                if (ch->clip == clip) {
                    if (ch->time >= ch->clip->length) {
                        if (ch == &anim->blend)
                            fn_8019C408(anim);
                        ch->time = ch->clip->length;
                    }
                    if (ch->time == 0.0f)
                        ch->time = d;
                } else {
                    return 0;
                }
            } else {
                if (ch == &anim->blend)
                    fn_8019C408(anim);
                ch->time = ch->clip->length;
            }
            if ((flags & 0x2004) && anim->main.clip)
                fn_8019DB24(&anim->main, 0.0f);
            return 1;
        }
        loops = ch->time / ch->clip->length;
        if (loops != 0.0f) {
            while (loops >= 1.0f) {
                if (!fn_80465A9C(ch) && !quiet)
                    lbl_8066C58C(ch, anim, 0x1E, ch->time, 0, 0);
                t -= ch->clip->length;
                loops -= 1.0f;
            }
            memset(ch->state, 0, ch->clip->count * 4);
            if (lbl_8066C58C && ch->clip->nEvents && !fn_80465A9C(ch) && !quiet) {
                step = t;
                for (i = 0; i < ch->clip->nEvents; i++) {
                    d = ch->clip->events[i].frame - t;
                    if (d > 0.0f)
                        break;
                    if (-d <= step) {
                        Clip *clip = ch->clip;
                        ch->time = ch->clip->events[i].frame;
                        lbl_8066C58C(ch, anim, ch->clip->events[i].type, ch->clip->events[i].frame,
                                     ch->clip->events[i].param, ch->clip->events[i].value);
                        if (!ch->clip || ch->clip != clip)
                            return 0;
                        if (ch->time != ch->clip->events[i].frame)
                            return 0;
                    }
                }
            }
            ch->time = t;
        }
    }
    return 0;
}
}
