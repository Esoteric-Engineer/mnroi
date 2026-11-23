// A one-word setter (docs/core.md row 19). Names are placeholders.

struct Text
{
    char pad[0x38];
    int f38;
};

extern "C" void fn_8042E894(register Text *self, register int a)
{
    self->f38 = a;
}
