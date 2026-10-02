// Newlib 1.11 string/strlen.c, built by SN ProDG.
#include <stddef.h>

#define UNALIGNED(X) ((long)X & (sizeof(long) - 1))
#define DETECTNULL(X) (((X) - 0x01010101) & ~(X) & 0x80808080)

size_t strlen(const char* str)
{
    const char* start = str;
    unsigned long* aligned_addr;

    if (!UNALIGNED(str)) {
        // Look for a null a word at a time, then find it bytewise.
        aligned_addr = (unsigned long*)str;
        while (!DETECTNULL(*aligned_addr))
            aligned_addr++;
        str = (char*)aligned_addr;
    }

    while (*str)
        str++;
    return str - start;
}
