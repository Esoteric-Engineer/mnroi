// Release table record `index` through fn_8044FDD0 and set its +0x4C word to 1 (docs/versus.md section 5, row 2).
typedef struct Record {
    char pad0[0x4C];
    int b; // +0x4C
    char pad1[0x10];
} Record __attribute__((aligned(8)));

extern Record lbl_80567760[];
extern void fn_8044FDD0(int index);

void fn_8044FF38(int index)
{
    fn_8044FDD0(index);
    lbl_80567760[index].b = 1;
}
