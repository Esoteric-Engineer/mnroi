// Small-object allocator wrapper over the tail's SOA class (docs/core.md row 15).
// Owns the .rodata 0x8049E680-0x8049E8FC: the two bin tables the APT glue passes in, then unread data.

struct SOABin
{
    unsigned int size;
    unsigned short f4;
    unsigned short count;
    unsigned short f8;
    unsigned short pad;
};

struct SOABins
{
    char data[0xA8];
};

class SOA
{
public:
    char data[0x298];
    SOA(int arg, SOABins *bins, char *a, char *b, char *c, char *d) __asm__("fn_804675D4");
};

struct SOAWrap
{
    SOA *soa;
};

extern "C" {
extern const SOABin lbl_8049E680[13] = {
    {4, 1000, 128, 1000, 0},
    {8, 1000, 64, 1000, 0},
    {12, 58000, 20000, 58000, 0},
    {16, 7600, 4000, 7600, 0},
    {24, 4000, 3000, 4000, 0},
    {32, 2400, 2400, 2400, 0},
    {64, 8000, 6000, 8000, 0},
    {128, 2500, 1200, 2500, 0},
    {256, 70, 30, 70, 0},
    {512, 60, 10, 60, 0},
    {1024, 20, 5, 20, 0},
    {1536, 5, 5, 5, 0},
    {2048, 5, 5, 5, 0},
};

extern const SOABin lbl_8049E71C[13] = {
    {4, 60, 60, 200, 0},
    {8, 100, 100, 500, 0},
    {12, 8000, 8000, 8000, 0},
    {16, 1700, 1700, 2000, 0},
    {24, 800, 800, 1000, 0},
    {32, 600, 600, 1000, 0},
    {64, 600, 600, 800, 0},
    {128, 600, 600, 600, 0},
    {256, 30, 30, 30, 0},
    {512, 6, 32, 20, 0},
    {1024, 5, 10, 10, 0},
    {1536, 3, 3, 5, 0},
    {2048, 2, 5, 5, 0},
};

void fn_80467494(SOABins *bins, char *a);
void fn_80467538(SOABins *bins, unsigned int size, int count);
void fn_804677A4(SOA *soa, int inChrg);
void fn_804677F8(SOA *soa, void *p);
int fn_80467894(SOA *soa, int a, int b);
void fn_8023E98C(void);
void fn_801ACC0C(void *p);
void __builtin_delete(void *p);

SOAWrap *fn_801B6AF0(register SOAWrap *self, const SOABin *table, int n, int arg, int unused)
{
    SOABins bins;
    char c0;
    int total;
    int i;
    int count;
    char d0;
    char d1;
    char d2;
    char d3;

    c0 = 0;
    fn_80467494(&bins, &c0);
    total = 0;
    for (i = 0; i < n; i++) {
        count = 0;
        count = table[i].count;
        fn_80467538(&bins, table[i].size, count);
        total += table[i].size * count;
    }
    d0 = 0;
    c0 = 0;
    d1 = 0;
    d2 = 0;
    d3 = 0;
    self->soa = new SOA(arg, &bins, &c0, &d1, &d2, &d3);
    return self;
}

void fn_801B6C68(register SOAWrap *self, int inChrg)
{
    fn_804677A4(self->soa, 2);
    fn_801ACC0C(self->soa);
    self->soa = 0;
    if (inChrg & 1)
        __builtin_delete(self);
    else
    {
    }
}

void fn_801B6CD4(register SOAWrap *self, void *p)
{
    return fn_804677F8(self->soa, p);
}

int fn_801B6D18(register SOAWrap *self, int a, int b)
{
    fn_8023E98C();
    return fn_80467894(self->soa, a, b);
}

void fn_801B6D70(void)
{
}
}

__asm__(".section .rodata
"
        "\t.4byte 0x42696E20, 0x25692825, 0x6929093A, 0x2025692F\n"
        "\t.4byte 0x25692F25, 0x6920095B, 0x2569206F, 0x76657266\n"
        "\t.4byte 0x6C6F7773, 0x5D095B25, 0x69205265, 0x71756573\n"
        "\t.4byte 0x74735D09, 0x5B256920, 0x62797465, 0x7320556E\n"
        "\t.4byte 0x64657220, 0x5574696C, 0x697A6564, 0x5D0A0000\n"
        "\t.4byte 0x25730000, 0x534F4120, 0x53697A65, 0x20256920\n"
        "\t.4byte 0x62797465, 0x732C2052, 0x65717565, 0x73747320\n"
        "\t.4byte 0x25692C20, 0x556E6465, 0x72205574, 0x696C697A\n"
        "\t.4byte 0x65642053, 0x70616365, 0x3A202569, 0x20627974\n"
        "\t.4byte 0x6573200A, 0x00000000, 0x5B435055, 0x5350414D\n"
        "\t.4byte 0x5D202537, 0x642C2025, 0x37642C20, 0x25730A00\n"
        "\t.4byte 0x3F800000, 0x00000000, 0x55492F65, 0x61666F6E\n"
        "\t.4byte 0x74300000, 0x55492F65, 0x61666F6E, 0x74310000\n"
        "\t.4byte 0x55492F65, 0x61666F6E, 0x74330000, 0x55492F65\n"
        "\t.4byte 0x61626566, 0x6E743000, 0x55492F65, 0x61626566\n"
        "\t.4byte 0x6E743100, 0x55492F65, 0x61626566, 0x6E743300\n"
        "\t.4byte 0x4575726F, 0x7374696C, 0x65204C54, 0x20537464\n"
        "\t.4byte 0x00000000, 0x4575726F, 0x7374696C, 0x65204C54\n"
        "\t.4byte 0x20537464, 0x20436F6E, 0x64656E73, 0x65640000\n"
        "\t.4byte 0x45415320, 0x53616E73, 0x436F6E64, 0x656E7365\n"
        "\t.4byte 0x64000000\n"
        "	.text");
