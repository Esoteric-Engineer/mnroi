// Default virtuals of the VFS's RealCore base class, vtable 0x804F6888 (docs/core.md row 18, section 4.4).

struct Fs;

extern "C" {
int fn_80466A44(register Fs *self) // +0x10
{
    return 1;
}

void fn_80466A74(register Fs *self) // +0x18
{
}

int fn_80466A9C(register Fs *self, register int a, register int b, register int c) // +0x38
{
    return 0;
}

int fn_80466AD8(register Fs *self, register int a) // +0x58
{
    return 0;
}

long long fn_80466B0C(register Fs *self) // +0x60
{
    return 0;
}

void *fn_80466B40(register Fs *self) // +0x68
{
    return self;
}

int fn_80466B70(register Fs *self) // +0x70
{
    return 0;
}
}
