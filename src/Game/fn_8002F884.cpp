// FrameCtx::setMode (guessed name): stores the mode and its phase-flag mask; see docs/versus.md section 5, row 9d.

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
