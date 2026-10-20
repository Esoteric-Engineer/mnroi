// FrameCtx::setMode (guessed name): stores the mode and its phase-flag mask; see docs/versus.md section 5, row 9d.
// fn_8002F95C tests a Config flag and discards it; fn_8002F9A8 is an empty stub (pending state 11 hook).
// fn_8002F9D0 appends a copy of the -addthing name to the list at +0x328 (16 entries max).

class FrameCtx
{
public:
    char pad0[0x64];
    int mode;           // +0x64
    unsigned int flags; // +0x68
};

extern "C" void fn_8002F884(register FrameCtx *self, int mode)
{
    switch (mode) {
    case 2: self->flags = 0x99; break;
    case 1: self->flags = 0x29; break;
    case 7: self->flags = 0x109; break;
    case 6: self->flags = 0xD1; break;
    case 3: self->flags = 0xDF; break;
    case 5: self->flags = 0xDD; break;
    case 4: self->flags = 0xDB; break;
    default: return;
    }
    self->mode = mode;
}

extern "C" int fn_80432968(unsigned int *self);
extern char lbl_8066D568[8];

extern "C" void fn_8002F95C()
{
    if (fn_80432968((unsigned int *)lbl_8066D568) == 0) {
        return;
    }
}

extern "C" void fn_8002F9A8(register FrameCtx *self)
{
}

extern "C" unsigned int strlen(const char *s);
extern "C" char *strcpy(char *dst, const char *src);

class ThingList
{
public:
    char pad0[0x328];
    unsigned int count; // +0x328
    char *names[16];    // +0x32C
};

extern "C" void fn_8002F9D0(register ThingList *self, char *name)
{
    if (self->count <= 15) {
        self->names[self->count] = new char[strlen(name) + 1];
        strcpy(self->names[self->count], name);
        self->count++;
    }
}
