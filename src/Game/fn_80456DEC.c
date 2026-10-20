// Allocator front for the 8-byte handle object that fn_80456E30 constructs (docs/versus.md section 5, row 2).
extern int fn_8024606C(int size);

int fn_80456DEC(register int size)
{
    return fn_8024606C(size);
}
