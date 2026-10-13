// Reads the pointer at +0x3DC of an entity. Row 19 of docs/versus.md.

inline int sn_return_decl(int a) { return a; }

struct Field3DC {
    char pad0[0x3DC];
    void *field; // +0x3DC
    void *get();
};

__asm__(".text\n\t.globl fn_80085954\n\t.type fn_80085954,@function\nfn_80085954:");
void *Field3DC::get()
{
    return field;
}
__asm__(".size fn_80085954, 0x2C");
