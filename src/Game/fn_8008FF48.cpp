// Motion-set loading: the text .nms parser and the pre-tokenised .msres reader; docs/characters.md section 4.
// Owns .rodata 0x8048A1B0-0x8048A254; "Animation:Motions" (lbl_8048A16C) precedes the file's other pools, so it stays extern.

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

struct FlagName {
    unsigned int bit;
    const char *name;
};

extern "C" {
void *memset(void *dst, int c, unsigned n);
char *strncpy(char *dst, const char *src, unsigned n);
char *strtok(char *str, const char *delim);
int stricmp(const char *a, const char *b);
double atof(const char *s);
void *fn_801AD324(int size, const char *tag, int line);
void *fn_801AC988(int size, const char *tag, int line, int align);
void fn_801ACC0C(void *p);
void fn_801B4094(char *path, const char *ext);
int fn_801B3FBC(char *path, const char *ext);
void *fn_801A8368(const char *path, const char *mode, int flags);
void fn_801A875C(void *file);
void fn_801A953C(void *file);
int fn_801A8B60(void *dst, int size, int count, void *file);
void fn_801A8C08(char *buf, int size, void *file);
int fn_801A8C84(void *file);
int fn_801A8DC0(void *file);
void fn_80016570();
int fn_8008F3B8(char *name);
void *fn_80198DE4(char *name, int flags);
void fn_801991FC(void *anim);
void fn_801B4628(void *registry, void *key, void *value);
int fn_80090034(register MotionSet *set, int flags);
void fn_8008F53C(MotionSet *set);
int fn_8008F6A0(register MotionSet *set, MotionSet *base);
unsigned int fn_80090810(char *name);
char *fn_800909C4();
MotionSet *fn_80090BF8();
extern void *lbl_8066B8F4; // the motion-set registry
extern MotionSet *lbl_8066B8F8; // male.nms
extern MotionSet *lbl_8066B8FC; // female.nms
extern MotionSet *lbl_8066B900; // brute.nms
extern MotionSet *lbl_8066B904; // female2.nms
extern MotionSet *lbl_8066B908; // humanpeon.nms
extern MotionSet *lbl_8066B90C; // brutepeon.nms
extern unsigned int lbl_8054F7C0[]; // default flags by state
extern FlagName lbl_8054FD90[];
extern unsigned int lbl_8066D630; // lbl_8054FD90's count
extern Motion lbl_8054FE10[]; // the parse buffer
extern char *lbl_8066D634; // .msres buffer
extern int lbl_8066D638;   // its size
extern char *lbl_8066D63C; // cursor
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

extern "C" int fn_80090034(register MotionSet *set, int flags)
{
    void *file;
    char line[0x200];
    Overlay *overlay;
    unsigned int i;
    unsigned int j;
    unsigned int bits;
    int unused;
    char *tok;
    MotionSet *base;
    int animFlags;
    char path[0x80];
    Motion *motion;
    float fps;

    if (set->count)
        return 1;
    overlay = 0;
    unused = 0;
    base = 0;
    animFlags = 0x20000;
    if (flags)
        animFlags |= 0x800000;
    strncpy(path, set->name, 0x80);
    path[0x7F] = 0;
    fn_801B4094(path, "NMS");
    file = fn_801A8368(path, "rb", 6);
    if (!file)
        goto fail;
    fn_801A953C(file);
    overlay = set->overlays;
    overlay->n = 0;
    while (!fn_801A8C84(file)) {
        motion = &lbl_8054FE10[overlay->n];
        fn_801A8C08(line, 0x1FF, file);
        if (fn_801A8C84(file))
            break;
        if (line[0] == ';')
            continue;
        tok = strtok(line, " \r\t\n");
        if (!tok)
            continue;
        else if (!stricmp(tok, "numoverlays"))
            continue;
        else if (!stricmp(tok, "basedon")) {
            tok = strtok(0, " \r\t\n");
            if (!stricmp(tok, "male"))
                base = lbl_8066B8F8;
            else if (!stricmp(tok, "female"))
                base = lbl_8066B8FC;
            else if (!stricmp(tok, "brute"))
                base = lbl_8066B900;
            else if (!stricmp(tok, "female2"))
                base = lbl_8066B904;
            else if (!stricmp(tok, "humanpeon"))
                base = lbl_8066B908;
            else if (!stricmp(tok, "brutepeon"))
                base = lbl_8066B90C;
            continue;
        } else if (!stricmp(tok, "overlay")) {
            fn_8008F6A0(set, base);
            overlay = &set->overlays[set->count];
            tok = strtok(0, " \r\t\n");
            if (tok) {
                strncpy(overlay->name, tok, 0x20);
                overlay->name[0x1F] = 0;
            } else {
                strncpy(overlay->name, "ERROR__NONAME", 0x20);
                overlay->name[0x1F] = 0;
            }
            continue;
        }
        motion->state = fn_8008F3B8(tok);
        if (!motion->state)
            continue;
        tok = strtok(0, " \r\t\n");
        if (!tok)
            continue;
        motion->anim = fn_80198DE4(tok, animFlags);
        if (!motion->anim)
            continue;
        fn_80016570();
        motion->speed = 1.0f;
        motion->flags = lbl_8054F7C0[motion->state];
        motion->dist = 0.0f;
        motion->move = 0.0f;
        while ((tok = strtok(0, " \r\t\n"))) {
            if (*tok == ';')
                break;
            if (!stricmp(tok, "fps")) {
                tok = strtok(0, " \r\t\n");
                fps = atof(tok);
                if (fps < 1.0f)
                    fps = 1.0f;
                motion->speed = fps * 0.033333335f;
            } else if (!stricmp(tok, "dist")) {
                tok = strtok(0, " \r\t\n");
                motion->dist = atof(tok);
                motion->dist = motion->dist >= -10.0f
                                   ? (motion->dist <= 1000.0f ? motion->dist : 1000.0f)
                                   : -10.0f;
            } else if (!stricmp(tok, "move")) {
                tok = strtok(0, " \r\t\n");
                motion->move = atof(tok);
                if (motion->move > 0.0f)
                    motion->move = 1.0f / motion->move;
                else
                    motion->move = 0.0f;
            } else {
                bits = fn_80090810(tok);
                if (bits)
                    motion->flags |= bits;
                else {
                }
            }
        }
        overlay->n++;
    }
    if (overlay->n)
        fn_8008F6A0(set, base);
    fn_801A875C(file);
    if (!flags) {
        for (i = 0; i < set->count; i++) {
            overlay = &set->overlays[i];
            for (j = 0; j < overlay->n; j++) {
                if (overlay->items[j].anim) {
                    fn_801991FC(overlay->items[j].anim);
                    fn_80016570();
                }
            }
        }
    }
    return 1;
fail:
    goto close;
close:
    if (file)
        fn_801A875C(file);
    return 0;
}

extern "C" unsigned int fn_80090810(char *name)
{
    unsigned int i;

    for (i = 0; i < lbl_8066D630; i++) {
        if (!stricmp(lbl_8054FD90[i].name, name))
            return lbl_8054FD90[i].bit;
    }
    return 0;
}

extern "C" unsigned int fn_800908CC(char *str)
{
    char buf[0x80];
    char *tok;
    unsigned int bits;
    unsigned int bit;

    strncpy(buf, str, 0x80);
    buf[0x7F] = 0;
    tok = strtok(buf, " \r\t\n");
    bits = 0;
    while (tok) {
        bit = fn_80090810(tok);
        if (bit)
            bits |= bit;
        tok = strtok(0, " \r\t\n");
    }
    return bits;
}

extern "C" void fn_800909A0(int a, int b)
{
}

extern "C" char *fn_800909C4()
{
    char *tok = 0;

    if ((int)(lbl_8066D634 + lbl_8066D638) <= (int)lbl_8066D63C)
        return 0;
    if (*lbl_8066D63C)
        tok = lbl_8066D63C;
    while (*lbl_8066D63C)
        lbl_8066D63C++;
    lbl_8066D63C++;
    return tok;
}

extern "C" void fn_80090A68(char *name, int x)
{
    void *file;
    MotionSet *set;
    char path[0x80];
    char *tok;

    strncpy(path, name, 0x80);
    path[0x7F] = 0;
    fn_801B3FBC(path, "NMS");
    fn_801B4094(path, "msres");
    file = fn_801A8368(path, "rb", 6);
    if (!file)
        return;
    lbl_8066D638 = fn_801A8DC0(file);
    lbl_8066D63C = lbl_8066D634 = (char *)fn_801AC988(lbl_8066D638, lbl_8048A16C, 0x3EA, 2);
    fn_801A8B60(lbl_8066D634, lbl_8066D638, 1, file);
    while ((tok = fn_800909C4())) {
        set = fn_80090BF8();
        if (!set) {
        }
        strncpy(set->name, tok, 0x20);
        set->name[0x1F] = 0;
        set->refs = 1;
        fn_801B4628(lbl_8066B8F4, set->name, set);
        set->x130 = x;
    }
    fn_801A875C(file);
    fn_801ACC0C(lbl_8066D634);
}

extern "C" MotionSet *fn_80090BF8()
{
    MotionSet *set = 0;
    Overlay *overlay = 0;
    unsigned int i;
    unsigned int j;
    unsigned int bits;
    int unused1 = 0;
    int unused2 = 0;
    char *tok;
    Motion *motion;

    set = (MotionSet *)fn_801AD324(0x134, lbl_8048A16C, 0x41A);
    if (!set)
        goto fail;
    memset(set, 0, 0x134);
    overlay = set->overlays;
    overlay->n = 0;
    while ((tok = fn_800909C4())) {
        motion = &lbl_8054FE10[overlay->n];
        if (!stricmp(tok, "overlay")) {
            fn_8008F6A0(set, 0);
            overlay = &set->overlays[set->count];
            tok = fn_800909C4();
            if (tok) {
                strncpy(overlay->name, tok, 0x20);
                overlay->name[0x1F] = 0;
            } else {
                strncpy(overlay->name, "ERROR__NONAME", 0x20);
                overlay->name[0x1F] = 0;
            }
            continue;
        }
        motion->state = fn_8008F3B8(tok);
        if (!motion->state)
            continue;
        tok = fn_800909C4();
        motion->anim = fn_80198DE4(tok, 0x20000);
        if (!motion->anim)
            continue;
        motion->flags = 0;
        while ((tok = fn_800909C4())) {
            bits = fn_80090810(tok);
            if (bits)
                motion->flags |= bits;
        }
        overlay->n++;
    }
    if (overlay->n)
        fn_8008F6A0(set, 0);
    for (i = 0; i < set->count; i++) {
        for (j = 0; j < set->overlays[i].n; j++) {
            if (set->overlays[i].items[j].anim)
                fn_801991FC(set->overlays[i].items[j].anim);
        }
    }
    return set;
fail:
    if (set)
        fn_8008F53C(set);
    return 0;
}
