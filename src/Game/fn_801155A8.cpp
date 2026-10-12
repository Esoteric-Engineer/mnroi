// Voice: does the sound-event bank have event 1 for this type ID? docs/characters.md section 5.

struct Banks {
    void *fallback; // +0x0
    void *events;   // +0x4
    char pad[0x10];
};

extern Banks lbl_80568DB0;
extern int lbl_8066B63C;
extern int lbl_8066BD04;

extern "C" {
unsigned int fn_801B4938(void *registry, unsigned int key);

int fn_801155A8(int bank)
{
    int event;

    if (lbl_8066B63C == 0) {
        return 0;
    }
    if (lbl_8066BD04 == 0) {
        return 0;
    }
    event = fn_801B4938(lbl_80568DB0.events, (bank << 9) | 1);
    if (event == 0) {
        event = fn_801B4938(lbl_80568DB0.fallback, 0xFA001);
    }
    return event != 0 ? 1 : 0;
}
}
