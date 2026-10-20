// Returns 1 if `owner` is null, else whether fn_80111DB4(owner, index) is above the two words read for the record handle (docs/versus.md section 5, row 2).
typedef struct Record {
    char pad0[0x2C];
    int handle; // +0x2C
    char pad1[0x30];
} Record __attribute__((aligned(8)));

extern Record lbl_80567760[];
extern void fn_80111EB0(int handle, int *a, int *b, int flag);
extern int fn_80111DB4(int owner, int index);

int fn_80453EAC(int owner, int index)
{
    int a;
    int b;
    int sum;
    if (owner == 0)
    {
        return 1;
    }
    fn_80111EB0(lbl_80567760[index].handle, &a, &b, 1);
    sum = a + b;
    return fn_80111DB4(owner, index) > sum;
}
