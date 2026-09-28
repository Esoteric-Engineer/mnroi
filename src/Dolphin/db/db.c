typedef unsigned long u32;
typedef struct OSContext OSContext;

extern void __DBExceptionDestination(void); // same file, right after DBInit
extern void OSReport(const char* msg, ...);
extern void OSDumpContext(OSContext* context);
extern void PPCHalt(void);

// OSReport's argument, under dtk's auto name because the asm below reaches it by that.
char lbl_804D1D28[] = "DBExceptionDestination\n";

// .sbss comes out in reverse declaration order: __DBInterface must precede DBVerbose.
unsigned int DBVerbose;
void* __DBInterface;

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

asm void __DBExceptionDestinationAux(void)
{
    // clang-format off
    nofralloc
    mflr    r0
    lis     r3, lbl_804D1D28@ha
    stw     r0, 4(r1)
    addi    r3, r3, lbl_804D1D28@l
    crclr   4*cr1+eq
    stwu    r1, -0x18(r1)
    stw     r31, 0x14(r1)
    lwz     r4, 0xC0(r0)
    addis   r31, r4, 0x8000
    bl      OSReport
    mr      r3, r31
    bl      OSDumpContext
    bl      PPCHalt
    lwz     r0, 0x1C(r1)
    lwz     r31, 0x14(r1)
    addi    r1, r1, 0x18
    mtlr    r0
    blr
    // clang-format on
}

asm void __DBExceptionDestination(void)
{
    // clang-format off
    nofralloc
    mfmsr   r3
    ori     r3, r3, 0x30
    mtmsr   r3
    b       __DBExceptionDestinationAux
    // clang-format on
}

#pragma peephole on

// ac-decomp's __DBInterface is a struct DBInterface*; exceptionMask is at +4
u32 __DBIsExceptionMarked(unsigned char exception)
{
    u32 mask = 1 << exception;
    return ((u32*)__DBInterface)[1] & mask;
}

void DBPrintf(char* str, ...) { }
