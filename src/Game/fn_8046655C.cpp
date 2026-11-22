// The file layer's inline functions (docs/core.md row 18).

inline int sn_return_decl(int a) { return a; }

class FileRec {
public:
    char pad[0x128];
    unsigned int fsize;
    unsigned int pos;
};

extern "C" {
extern int lbl_8066BE48;

int fn_8046655C(void)
{
    return lbl_8066BE48;
}

int fn_80466584(register FileRec *self)
{
    return self->pos >= self->fsize;
}

unsigned int *fn_804665C4(register FileRec *self)
{
    return &self->pos;
}
}
