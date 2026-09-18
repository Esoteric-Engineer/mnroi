extern void* __DBInterface; // ac-decomp's Dolphin/db/db.c struct DBInterface* pointer; dtk auto-detected this .sbss slot's size (4) but not its scope
extern unsigned int DBVerbose; // same file, the adjacent .sbss BOOL right after __DBInterface
extern void __DBExceptionDestination(void); // same file, right after DBInit

// void DBInit(void) -- see ac-decomp's Dolphin/db/db.c:
//   __DBInterface = OSPhysicalToCached(0x40);
//   __DBInterface->ExceptionDestination = (void*)OSCachedToPhysical(__DBExceptionDestination);
//   DBVerbose = TRUE;
asm void DBInit(void)
{
    // clang-format off
    nofralloc
    lis     r4, -32768
    addi    r0, r4, 64
    lis     r3, __DBExceptionDestination@ha
    stw     r0, __DBInterface
    addi    r3, r3, __DBExceptionDestination@l
    addis   r0, r3, -32768
    stw     r0, 72(r4)
    li      r0, 1
    stw     r0, DBVerbose
    blr
    // clang-format on
}
