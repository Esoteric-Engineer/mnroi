// Stores a Vector's three floats through element pointers; the .cpp form is needed for the store-through-call shape (docs/matching_notes.md).

inline int sn_return_decl(int a) { return a; }

extern "C" float *fn_80438360(void *self, int i);

extern "C" void fn_80436878(register void *self, register float *v)
{
    *fn_80438360(self, 0) = v[0];
    *fn_80438360(self, 1) = v[1];
    *fn_80438360(self, 2) = v[2];
}
