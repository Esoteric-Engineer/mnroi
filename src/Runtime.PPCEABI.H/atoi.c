// Newlib 1.11 stdlib/atoi.c, built by SN ProDG.
#include <stddef.h>

extern long strtol(const char* str, char** end, int base);

int atoi(const char* s)
{
    return (int)strtol(s, NULL, 10);
}
