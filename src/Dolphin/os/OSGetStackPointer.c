asm unsigned long OSGetStackPointer(void)
{
    nofralloc

    mr      r3, r1
    blr
}
