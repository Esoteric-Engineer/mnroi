// Passes the handle at +0xF0 of an entity to fn_800ACFA8. Row 19 of docs/versus.md.

inline int sn_return_decl(int a) { return a; }

extern "C" void *fn_800ACFA8(int handle);

struct Handle0F0 {
    char pad0[0xF0];
    int field; // +0xF0
    void *get();
};

__asm__(".text\n\t.globl fn_800CD9B0\n\t.type fn_800CD9B0,@function\nfn_800CD9B0:");
void *Handle0F0::get()
{
    return fn_800ACFA8(field);
}
__asm__(".size fn_800CD9B0, 0x44");
