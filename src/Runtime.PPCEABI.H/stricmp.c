#pragma optimize_for_size on
#pragma peephole off

extern int tolower(int c);

int stricmp(const char* s1, const char* s2)
{
    int c1, c2;
    while (*s1 != 0 && (c1 = tolower(*s1), c2 = tolower(*s2), c1 == c2)) {
        s1++;
        s2++;
    }
    c1 = tolower(*(unsigned char*)s1);
    c2 = tolower(*(unsigned char*)s2);
    return c1 - c2;
}
