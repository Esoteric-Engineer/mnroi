// The file back end's inline function (docs/core.md row 18).

struct Block {
    int req;
    char *buf;
};

extern "C" Block *fn_80466A0C(register Block *self)
{
    self->req = 0;
    self->buf = 0;
    return self;
}
