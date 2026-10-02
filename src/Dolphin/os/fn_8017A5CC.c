extern void fn_8017A608(void);
extern void fn_801796B4(int);

#pragma section R ".rodata.1"
#pragma force_active on
__declspec(section ".rodata.1") const char BadAllocStr[] = "bad_alloc";
__declspec(section ".rodata.1") const char LibWarningNewStr[] =
    "\n*** Library warning ***\nYou must define an operator new\nsee Pro-DG documentation\n";
__declspec(section ".rodata.1") const char LibWarningNewArrayStr[] =
    "\n*** Library warning ***\nYou must define an operator new[]\nsee Pro-DG documentation\n";
__declspec(section ".rodata.1") const char LibWarningDeleteStr[] =
    "\n*** Library warning ***\nYou must define an operator delete\nsee Pro-DG documentation\n";
__declspec(section ".rodata.1") const char LibWarningDeleteArrayStr[] =
    "\n*** Library warning ***\nYou must define an operator delete[]\nsee Pro-DG documentation\n";
__declspec(section ".rodata.1") const char LibErrorHeapStr[] =
    "\n*** Library error ***\nException handling requires access to heap memory\n"
    "Hook _register_malloc to your malloc rountine - see ProDG manual.\n";
#pragma force_active reset

asm void __default_terminate(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 12(r1)
    bl      fn_8017A608
    // clang-format on
}

__declspec(section ".data") void (*__terminate_func)(void) = __default_terminate;

asm void terminate(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 12(r1)
    lis     r9, __terminate_func@ha
    lwz     r0, __terminate_func@l(r9)
    mtlr    r0
    blrl
    lwz     r0, 12(r1)
    mtlr    r0
    addi    r1, r1, 8
    blr
    // clang-format on
}

asm void fn_8017A608(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 12(r1)
    li      r3, 1
    crclr   6
    bl      fn_801796B4
    // clang-format on
}
