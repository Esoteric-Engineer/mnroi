// Release table record `index` through fn_8044FDD0, bump its +0x3C count and clear +0x48/+0x4C (docs/versus.md section 5, row 2).
typedef struct Record {
    char pad0[0x3C];
    int count; // +0x3C
    char pad1[0x8];
    int a; // +0x48
    int b; // +0x4C
    char pad2[0x10];
} Record __attribute__((aligned(8)));

extern Record lbl_80567760[];
extern int lbl_8066BD1C;
extern void fn_8044FDD0(int index);

void fn_8044FE74(int index)
{
    fn_8044FDD0(index);
    lbl_80567760[index].count++;
    lbl_80567760[index].a = 0;
    lbl_80567760[index].b = 0;
    lbl_8066BD1C = lbl_8066BD1C - 1;
}
