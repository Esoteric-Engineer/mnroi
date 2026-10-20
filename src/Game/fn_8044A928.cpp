// Const accessors of the string iterator pair class (Iter); see docs/versus.md.
inline int sn_return_decl(int a) { return a; }

struct Iter
{
    char *a;
    char *b;
    char *begin() const;
    char *end() const;
};

char *Iter::begin() const
{
    return a;
}

char *Iter::end() const
{
    return b;
}
