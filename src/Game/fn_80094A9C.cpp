// G method: advances the slot iteration cursor (G+0x750) to the next slot that fn_8043B2C8 accepts; returns nonzero while slots remain. docs/versus.md section 4.1.

struct State {
    char pad0[0x590];
    unsigned int slotCount; // +0x590
    char pad594[0x1BC];
    void *cursor;           // +0x750
};

inline int sn_return_decl(int a) { return a; }

extern "C" {
int fn_8043B2C8(void *slot);

int fn_80094A9C(register State *self)
{
    unsigned int next;
    void *slot;
    unsigned int i;

    next = 0;
    slot = 0;
    for (i = 0; i < self->slotCount; i++) {
        slot = (char *)self + 0x10 + i * 0xB0;
        if (slot != 0 && self->cursor == slot) {
            next = i;
            break;
        }
    }
    next++;
    while (next < self->slotCount) {
        if (fn_8043B2C8((char *)self + 0x10 + next * 0xB0) != 0) {
            break;
        }
        next++;
    }
    if (next >= self->slotCount) {
        return 0;
    }
    self->cursor = (char *)self + 0x10 + next * 0xB0;
    return 1;
}
}
