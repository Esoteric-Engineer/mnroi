// Voice: does the sound-event bank have this event for this type ID? docs/characters.md section 5.

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

int fn_801154D8(int bank, int event)
{
    int found;

    if (lbl_8066B63C == 0) {
        return 0;
    }
    if (lbl_8066BD04 == 0) {
        return 0;
    }
    found = fn_801B4938(lbl_80568DB0.fallback, (bank << 9) | event);
    if (found == 0) {
        found = fn_801B4938(lbl_80568DB0.fallback, event | 0xFA000);
    }
    return found != 0 ? 1 : 0;
}
}
