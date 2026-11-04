// Havok, built at -O2: pointers to the 16-byte blocks of a rigid body's motion (the object at +0x50).
// The game reads the body's velocity through fn_80318EB4 (Game/fn_80067050.cpp) (docs/prodg.md, "Middleware").

typedef struct Motion {
    char d[0xF0];
} Motion;

typedef struct Body {
    char pad[0x50];
    Motion *motion; // +0x50
} Body;

char *fn_80318E78(Body *self)
{
    return self->motion->d + 0x90;
}

char *fn_80318E84(Body *self)
{
    return self->motion->d + 0x60;
}

char *fn_80318E90(Body *self)
{
    return self->motion->d + 0x40;
}

char *fn_80318E9C(Body *self)
{
    return self->motion->d + 0x80;
}

char *fn_80318EA8(Body *self)
{
    return self->motion->d + 0x10;
}

char *fn_80318EB4(Body *self)
{
    return self->motion->d + 0xD0;
}

char *fn_80318EC0(Body *self)
{
    return self->motion->d + 0xE0;
}
