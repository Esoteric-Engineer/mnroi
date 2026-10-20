// cCutPlayer's slot refill step; docs/versus.md, row 8.
typedef struct Slot
{
    void *handle; // +0x0
    void *buffer; // +0x4
    int size;     // +0x8
    int *offset;  // +0xC
    int *total;   // +0x10
} Slot;

typedef struct cCutPlayer
{
    char pad0[0x30];
    void *buffer;     // +0x30
    Slot slots[2];    // +0x34
    unsigned refills; // +0x5C
} cCutPlayer;

extern int fn_80439C64(Slot *slot, unsigned *arg);
extern char *fn_80058284(void *a, void *b, int c);

void fn_804396F8(register cCutPlayer *self)
{
    int r;
    void *v;
    r = fn_80439C64(&self->slots[self->refills & 1], &self->refills);
    v = fn_80058284(self->buffer, self->slots[self->refills & 1].buffer, self->refills);
}
