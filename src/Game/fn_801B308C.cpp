// Tuning record lookup for an entity kind and name; docs/versus.md section 5, row 19.

inline int sn_return_decl(int a) { return a; }

extern "C" {
int fn_801B301C(char *a, char *b);
extern char lbl_8049E524[]; // "PLAYER"
}

extern "C" int fn_801B308C(unsigned int kind, char *name)
{
    char *prefix = 0;
    switch (kind) {
    case 0:
    case 2:
    case 7:
        prefix = lbl_8049E524;
        break;
    default:
        break;
    }
    if (prefix == 0)
        return 0;
    if (name == 0 || *name == 0)
        return 0;
    return fn_801B301C(prefix, name);
}
