// Resets four {int, float} tables, then loads GLOBALS fields 0x3D-0x4B into them; docs/versus.md row 21.
// Owns the .rodata pool 0x80486538-0x8048654C.

typedef struct Pair
{
    int a;   // +0x0
    float f; // +0x4
} Pair;

extern float fn_80433D20(void *record, int id, int slot);
extern int fn_80433D70(void *record, int id, int slot);
extern void fn_80043000(int which, int b, unsigned int c, unsigned int d);
extern void *lbl_8066C6C8;
extern Pair lbl_8053F254[3];
extern Pair lbl_8053F26C[3];
extern Pair lbl_8053F284[3][3];
extern Pair lbl_8053F2CC[3][3];

void fn_80044E5C(int only)
{
    unsigned int j;
    unsigned int i;
    unsigned int lo;
    unsigned int hi;
    unsigned int c;
    int d;

    lo = 0;
    hi = 3;
    if (only != 0)
    {
        lo = 0;
        hi = lo + 1;
    }
    i = lo;
    while (i < hi)
    {
        lbl_8053F254[i].f = 0.2f;
        lbl_8053F254[i].a = 0;
        lbl_8053F26C[i].f = 0.8f;
        lbl_8053F26C[i].a = 0;
        i++;
    }
    j = 0;
    while (j <= 2)
    {
        for (i = lo; i < hi; i++)
        {
            lbl_8053F284[j][i].f = 0.0f;
            lbl_8053F284[j][i].a = 0;
            lbl_8053F2CC[j][i].f = 1.0f;
            lbl_8053F2CC[j][i].a = 0;
        }
        j++;
    }
    if (only == 0 && lbl_8066C6C8 != 0)
    {
        lbl_8053F284[2][1].f = fn_80433D20(lbl_8066C6C8, 0x46, 0) * 0.01f;
        lbl_8053F284[2][1].a = 0;
        lbl_8053F284[0][1].f = fn_80433D20(lbl_8066C6C8, 0x47, 0) * 0.01f;
        lbl_8053F284[0][1].a = 0;
        lbl_8053F284[1][1].f = 0.0f;
        lbl_8053F284[1][1].a = 0;
        lbl_8053F2CC[2][1].f = fn_80433D20(lbl_8066C6C8, 0x48, 0) * 0.01f;
        lbl_8053F2CC[2][1].a = 0;
        lbl_8053F2CC[0][1].f = fn_80433D20(lbl_8066C6C8, 0x49, 0) * 0.01f;
        lbl_8053F2CC[0][1].a = 0;
        lbl_8053F2CC[1][1].f = 0.0f;
        lbl_8053F2CC[1][1].a = 0;
        c = fn_80433D70(lbl_8066C6C8, 0x4A, 0);
        d = fn_80433D70(lbl_8066C6C8, 0x4B, 0);
        fn_80043000(1, 0, c, d);
        lbl_8053F284[2][2].f = fn_80433D20(lbl_8066C6C8, 0x3D, 0) * 0.01f;
        lbl_8053F284[2][2].a = 0;
        lbl_8053F284[0][2].f = fn_80433D20(lbl_8066C6C8, 0x3E, 0) * 0.01f;
        lbl_8053F284[0][2].a = 0;
        lbl_8053F284[1][2].f = 0.0f;
        lbl_8053F284[1][2].a = 0;
        lbl_8053F2CC[2][2].f = fn_80433D20(lbl_8066C6C8, 0x3F, 0) * 0.01f;
        lbl_8053F2CC[2][2].a = 0;
        lbl_8053F2CC[0][2].f = fn_80433D20(lbl_8066C6C8, 0x40, 0) * 0.01f;
        lbl_8053F2CC[0][2].a = 0;
        lbl_8053F2CC[1][2].f = 0.0f;
        lbl_8053F2CC[1][2].a = 0;
        c = fn_80433D70(lbl_8066C6C8, 0x41, 0);
        d = fn_80433D70(lbl_8066C6C8, 0x42, 0);
        fn_80043000(2, 0, c, d);
    }
}
