// game.nfx key lookup: a key's index in the 140 names of lbl_804DC2F0, ignoring case, or 0 ("invalid"); docs/characters.md "Effects".
// The real name is unknown, so the symbol stays extern "C".

inline int sn_return_decl(int a) { return a; }

extern char *lbl_804DC2F0[140];

extern "C" {
int stricmp(const char *a, const char *b);
}

extern "C" unsigned int fn_803944A4(const char *key)
{
    unsigned int i;

    for (i = 0; i < 140; i++) {
        if (stricmp(key, lbl_804DC2F0[i]) == 0) {
            return i;
        }
    }
    return 0;
}
