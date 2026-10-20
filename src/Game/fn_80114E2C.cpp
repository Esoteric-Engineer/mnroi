// Plays event 1 of record i's sound bank (lbl_80567760[i]+0x2C), or of bank 2000 (none is registered), through lbl_80568DB0.events;
// docs/characters.md section 5. The real name is unknown, so the symbol stays extern "C".

struct Banks
{
    void *fallback; // +0x0
    void *events;   // +0x4
    int bank;       // +0x8
    int event;      // +0xC
    int arg;        // +0x10
    int record;     // +0x14
};

struct Record
{
    char pad0[0x2C];
    int bank;       // +0x2C
    char pad30[0x30];
} __attribute__((aligned(8))); // matching_notes 42

extern Banks lbl_80568DB0;
extern Record lbl_80567760[48];

extern "C" {
void *fn_801B4938(void *registry, int key);
}

extern "C" void fn_80114E2C(int i)
{
    void (*callback)();

    lbl_80568DB0.record = i;
    callback = (void (*)())fn_801B4938(lbl_80568DB0.events, (lbl_80567760[i].bank << 9) | 1);
    if (callback == 0) {
        callback = (void (*)())fn_801B4938(lbl_80568DB0.events, (2000 << 9) | 1);
    }
    if (callback != 0) {
        callback();
    }
}
