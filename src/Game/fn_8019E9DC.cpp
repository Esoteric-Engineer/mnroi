// Builds Bundles/<name>.ngb into path; docs/versus.md row 23.

extern "C" {
int sprintf(char *dst, const char *fmt, ...);
void fn_801B4094(char *path, const char *ext);
extern const char lbl_8049D304[];
extern const char lbl_8049D310[];
}

inline int sn_return_decl(int a) { return a; }

extern "C" void fn_8019E9DC(const char *name, char *path)
{
    sprintf(path, lbl_8049D304, name);
    fn_801B4094(path, lbl_8049D310);
}
