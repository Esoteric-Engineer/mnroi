// Newlib 1.11 string/strchr.c, built by SN ProDG.
#include <stddef.h>

#define UNALIGNED(X) ((long)X & (sizeof(long) - 1))
#define LBLOCKSIZE (sizeof(long))
#define DETECTNULL(X) (((X) - 0x01010101) & ~(X) & 0x80808080)
// Nonzero if X contains the byte that fills MASK.
#define DETECTCHAR(X, MASK) (DETECTNULL(X ^ MASK))

char* strchr(const char* s1, int i)
{
    const unsigned char* s = (const unsigned char*)s1;
    unsigned char c = (unsigned char)i;
    unsigned long mask, j;
    unsigned long* aligned_addr;

    if (!UNALIGNED(s)) {
        mask = 0;
        for (j = 0; j < LBLOCKSIZE; j++)
            mask = (mask << 8) | c;

        // Stop at the first word holding a null or c; the bytewise search finds which.
        aligned_addr = (unsigned long*)s;
        while (!DETECTNULL(*aligned_addr) && !DETECTCHAR(*aligned_addr, mask))
            aligned_addr++;
        s = (unsigned char*)aligned_addr;
    }

    while (*s && *s != c)
        s++;
    if (*s == c)
        return (char*)s;
    return NULL;
}
