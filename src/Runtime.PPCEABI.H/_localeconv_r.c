#pragma section R ".rodata.1"

extern const char lbl_8049C7D4[];
extern const char lbl_8049C7D8[];

struct lconv {
    const char* decimal_point;
    const char* thousands_sep;
    const char* grouping;
    const char* int_curr_symbol;
    const char* currency_symbol;
    const char* mon_decimal_point;
    const char* mon_thousands_sep;
    const char* mon_grouping;
    const char* positive_sign;
    const char* negative_sign;
    unsigned char int_frac_digits;
    unsigned char frac_digits;
    unsigned char p_cs_precedes;
    unsigned char p_sep_by_space;
    unsigned char n_cs_precedes;
    unsigned char n_sep_by_space;
    unsigned char p_sign_posn;
    unsigned char n_sign_posn;
};

__declspec(section ".rodata.1") const struct lconv lconv = {
    lbl_8049C7D8, lbl_8049C7D4, lbl_8049C7D4, lbl_8049C7D4, lbl_8049C7D4,
    lbl_8049C7D4, lbl_8049C7D4, lbl_8049C7D4, lbl_8049C7D4, lbl_8049C7D4,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

__declspec(section ".rodata.1") const char lbl_8049C7D4[4] = {0, 0, 0, 0};

__declspec(section ".rodata.1") const char lbl_8049C7D8[0x20] = {
    '.', 0, 0, 0,
    'C', 0, 0, 0,
    'C', '-', 'J', 'I', 'S', 0, 0, 0,
    'C', '-', 'E', 'U', 'C', 'J', 'P', 0,
    'C', '-', 'S', 'J', 'I', 'S', 0, 0,
};

/* maxExponent (strtod.c) shares this 8-aligned .sdata pool object with
 * __mb_cur_max; strtod.c's claim starts 4-mod-8, so this unit owns both. */
int lbl_8066C3A8 = 511;
int __mb_cur_max = 1;

unsigned char* _localeconv_r(void) {
    return (unsigned char*)&lconv;
}
