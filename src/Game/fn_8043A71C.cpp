// Flag-bit getters on two object types (flags words at +0x4 and +0x464, a halfword at +0x7E), plus empty stubs.
// C++: the first function carries the cc1plus function-end pair (docs/prodg.md).

typedef struct HalfFlags
{
    char unk0[0x7E];
    unsigned short flags; // +0x7E
} HalfFlags;

typedef struct WordFlags
{
    unsigned int unk0;
    unsigned int flags; // +0x4
} WordFlags;

typedef struct BigFlags
{
    char unk0[0x464];
    unsigned int flags; // +0x464
} BigFlags;

typedef struct Fields
{
    int unk0; // +0x0
    char unk4[0x80];
    int unk84; // +0x84
    char unk88[0x18];
    int unkA0; // +0xA0
} Fields;

extern "C" {

int fn_8043B16C(void *self);
int fn_8043B19C(void *self);

int fn_8043A71C(register HalfFlags *self)
{
    return (unsigned short)(self->flags & 0x20);
}

inline int sn_return_decl(int a) { return a; }

int fn_8043A758(register BigFlags *self)
{
    return self->flags & 0x400;
}

int fn_8043A788(register WordFlags *self)
{
    return self->flags & 0x20;
}

int fn_8043A7B8(register WordFlags *self)
{
    return self->flags & 0x800;
}

int fn_8043A7E8(register WordFlags *self)
{
    return self->flags & 0x1000;
}

int fn_8043A818(register WordFlags *self)
{
    return self->flags & 0x4000;
}

int fn_8043A848(register WordFlags *self)
{
    return self->flags & 0x8000;
}

int fn_8043A878(register void *self)
{
    register int r = 0;

    if (fn_8043B16C(self) || fn_8043B19C(self)) {
        r = 1;
    }
    return r;
}

int fn_8043A8E4(register WordFlags *self)
{
    return self->flags & 0x100000;
}

int fn_8043A914(register WordFlags *self)
{
    return self->flags & 0x200000;
}

int fn_8043A944(register WordFlags *self)
{
    return self->flags & 0x800000;
}

int fn_8043A974(register WordFlags *self)
{
    return self->flags & 0x1000000;
}

int fn_8043A9A4(register WordFlags *self)
{
    return self->flags & 0x2000000;
}

int fn_8043A9D4(register WordFlags *self)
{
    return self->flags & 0x4000000;
}

int fn_8043AA04(register WordFlags *self)
{
    return self->flags & 0x8000000;
}

int fn_8043AA34(register WordFlags *self)
{
    return self->flags & 0x10000000;
}

int fn_8043AA64(register Fields *self)
{
    return self->unkA0;
}

int fn_8043AA90(register Fields *self)
{
    return self->unk0;
}

int fn_8043AABC(register Fields *self)
{
    return self->unk84;
}

void fn_8043AAE8(register void *self)
{
}

void fn_8043AB08(register void *a, register void *b, register void *c)
{
}

void fn_8043AB30()
{
}

}
