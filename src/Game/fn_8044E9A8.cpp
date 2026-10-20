// APT script-variable setters on AptRef (docs/versus.md section 2): store a value through the typed builders fn_8044DB94/DC04/DE90/DF00.

struct AptRef {
    void *object; // +0x0
    char *name;   // +0x4
    int index;    // +0x8
};

extern "C" void *fn_8044B8B0(void *object);
extern "C" int fn_80102F10(void *object, char *name);
extern "C" int fn_8010329C(void *object, char *name);
extern "C" void fn_80102FD0(void *object, int slot, int index);
extern "C" void fn_8044DB94(void *self, const char *b, int c);
extern "C" void fn_8044DC04(void *self, int a, const char *b, int c);
extern "C" void fn_8044DE90(void *self, const char *b, int c);
extern "C" void fn_8044DF00(void *self, int a, const char *b, int c);

// Emits no code; a top-level `return <parameter>;` makes cc1plus drop the function-end branch pair (docs/prodg.md).
inline int sn_return_decl(int a) { return a; }

extern "C" {
void *fn_8044E9A8(register char *self)
{
    return self + 0x20;
}

void fn_8044E9D4(register AptRef *self, register int value)
{
    if (self->index < 0) {
        fn_8044DB94(fn_8044B8B0(self->object), self->name, value);
    } else {
        int slot = fn_80102F10(self->object, self->name);
        if (slot < 0) {
            slot = fn_8010329C(self->object, self->name);
        }
        fn_8044DC04(fn_8044B8B0(self->object), self->index, self->name, value);
        fn_80102FD0(self->object, slot, self->index);
    }
}

void fn_8044EA98(register AptRef *self, register int value)
{
    if (self->index < 0) {
        fn_8044DB94(fn_8044B8B0(self->object), self->name, value);
    } else {
        int slot = fn_80102F10(self->object, self->name);
        if (slot < 0) {
            slot = fn_8010329C(self->object, self->name);
        }
        fn_8044DC04(fn_8044B8B0(self->object), self->index, self->name, value);
        fn_80102FD0(self->object, slot, self->index);
    }
}

void fn_8044EB5C(register AptRef *self, register const int *value)
{
    if (self->index < 0) {
        fn_8044DE90(fn_8044B8B0(self->object), self->name, *value);
    } else {
        int slot = fn_80102F10(self->object, self->name);
        if (slot < 0) {
            slot = fn_8010329C(self->object, self->name);
        }
        fn_8044DF00(fn_8044B8B0(self->object), self->index, self->name, *value);
        fn_80102FD0(self->object, slot, self->index);
    }
}

void fn_8044EC20(register AptRef *self, register int value)
{
    if (self->index < 0) {
        fn_8044DB94(fn_8044B8B0(self->object), self->name, value);
    } else {
        int slot = fn_80102F10(self->object, self->name);
        if (slot < 0) {
            slot = fn_8010329C(self->object, self->name);
        }
        fn_8044DC04(fn_8044B8B0(self->object), self->index, self->name, value);
        fn_80102FD0(self->object, slot, self->index);
    }
}
}
