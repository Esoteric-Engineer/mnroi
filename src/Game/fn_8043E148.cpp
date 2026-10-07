// Entry-slot test: nonzero word at +0x4 of the 0x30-byte entry (docs/versus.md, row 8).

inline int sn_return_decl(int a)
{
    return a;
}

typedef struct Entry
{
    char pad[4];
    int word; // +0x4
    char tail[0x28];
} Entry;

extern "C" int fn_8043E148(register Entry *self, register int i)
{
    return self[i].word != 0;
}
