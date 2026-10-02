typedef struct FILE FILE;

struct _reent {
    int _errno;
    FILE* _stdin;
    FILE* _stdout;
    FILE* _stderr;
    int _inc;
    char _emergency[25];
    int _current_category;
    const char* _current_locale;
    int __sdidinit;
    void (*__cleanup)(struct _reent*);
    void* _result;
    int _result_k;
    void* _p5s;
    void* _freelist;
    int _cvtlen;
    char* _cvtbuf;
    // Unverified: no caller in this build dereferences these fields by name, only the leading word is non-zero in the DOL, so the rest is kept as an opaque zero-filled blob.
    unsigned long _new0;
    unsigned char _new1[0xF0 - 4];
    void* _atexit;
    unsigned char _atexit0[0x8C];
    unsigned char __sglue[0xC];
    unsigned char __sf[3][0x60];
};

#pragma section R ".rodata.1"
__declspec(section ".rodata.1") const char lbl_8049C8D8[2] = "C";

static struct _reent impure_data = {
    0,
    (FILE*)&impure_data.__sf[0],
    (FILE*)&impure_data.__sf[1],
    (FILE*)&impure_data.__sf[2],
    0,
    {0},
    0,
    lbl_8049C8D8,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    1,
    {0},
    0,
    {0},
    {0},
    {{0}},
};

// __sfp's preset-buffer table: 10 {char* base; int size;} pairs, one per _sn_iobf slot.
// Here, not in __sfp.c, because 0x804D061C is 4-mod-8 and impure_data's start is the nearest 8-aligned one. Real size 0x50; the 4 bytes to __terminate_func are mwld's pad.
char lbl_804D061C[0x50] = {0};

struct _reent* lbl_8066C3B0 = &impure_data;
char* lbl_8066C3B4 = lbl_804D061C;
