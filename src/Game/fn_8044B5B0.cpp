// AptRef::operator[](int): the element reference, built through the three-word setter fn_804497E4 (docs/versus.md section 2).

class AptRef {
public:
    AptRef(void *object, char *name, int index) __asm__("fn_804497E4");
    AptRef operator[](int index);

    void *object; // +0x0
    char *name;   // +0x4
    int index;    // +0x8
};

// Emits no code; a top-level `return <parameter>;` makes cc1plus drop the function-end branch pair (docs/prodg.md).
inline int sn_return_decl(int a) { return a; }

AptRef AptRef::operator[](register int index)
{
    return AptRef(object, name, index);
}
