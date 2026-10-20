// Registry key hash: the sum of (i + 1) * lowercase(key[i]) over the first 127 characters, modulo the bucket count; docs/characters.md section 3.

extern char _ctype_[];

#define TOLOWER(c) ({ int _c = (c); ((_ctype_ + 1)[_c] & 1) ? _c + 0x20 : _c; })

unsigned int fn_801B4CA0(register const char *key, register unsigned int bucketCount)
{
    unsigned int sum;
    unsigned int i;

    sum = 0;
    i = 0;
    while (i <= 0x7E && *key != 0) {
        sum += (i + 1) * TOLOWER(*key);
        key++;
        i++;
    }
    sum = sum % bucketCount;
    return sum;
}
