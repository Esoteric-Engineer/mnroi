// Identity: returns its argument. Row 19 of docs/versus.md.

struct Self {
    void *me();
};

__asm__(".text\n\t.globl fn_8042FB28\n\t.type fn_8042FB28,@function\nfn_8042FB28:");
void *Self::me()
{
    return this;
}
__asm__(".size fn_8042FB28, 0x30");
