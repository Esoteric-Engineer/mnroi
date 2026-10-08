// Constructor (guessed class RecArr) of an array of 0x40-byte records (docs/versus.md section 5, row 2).

extern "C" int fn_80119398(void *table, int size, void *attr);
extern char lbl_804975BC[];
extern char lbl_80568DF0[0x10];

class Attr
{
public:
    int a;                    // +0x0
    const void *b;            // +0x4
    mutable const Attr *link; // +0x8
    Attr(register int a, register const char *b);
};

struct Rec
{
    int w0;  // +0x0
    int w4;  // +0x4
    char pad8[0x14];
    int w1C; // +0x1C
    char pad20[0x20];
};

class RecArr
{
public:
    int count; // +0x0
    Rec *recs; // +0x4
    RecArr(register int n);
};

RecArr::RecArr(register int n)
{
    count = n;
    Attr attr(1, lbl_804975BC);
    recs = (Rec *)fn_80119398(lbl_80568DF0, n * 0x40, &attr);
    for (int i = 0; i < n; i++) {
        recs[i].w0 = 0;
        recs[i].w1C = 0;
        recs[i].w4 = 0;
    }
}
