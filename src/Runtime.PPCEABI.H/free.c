extern void OSPanic(void);

// SN malloc stubs' "malloc"/"free"/"realloc"/"calloc" messages, pooled here in address order.
// The stub names are shifted by one: free() reads the "malloc" message below, realloc.c reads the "free" one.
// "realloc"/"calloc" are dead-stripped but kept alive by sharing this pool.
#pragma section R ".rodata.1"
__declspec(section ".rodata.1") const char lbl_8049C224[126] =
    "\n*** Library error ***\nAn external call has been made to 'malloc'\n"
    "Calling function address: 0x%X\nPlease See the ProDG manual\n";

__declspec(section ".rodata.1") const char lbl_8049C2A4[0x17C] =
    "\n*** Library error ***\nAn external call has been made to 'free'\n"
    "Calling function address: 0x%X\nPlease See the ProDG manual\n" "\0"
    "\n*** Library error ***\nAn external call has been made to 'realloc'\n"
    "Calling function address: 0x%X\nPlease See the ProDG manual\n" "\0\0"
    "\n*** Library error ***\nAn external call has been made to 'calloc'\n"
    "Calling function address: 0x%X\nPlease See the ProDG manual\n";

asm void free(void)
{
    // clang-format off
    nofralloc
    stwu    r1, -8(r1)
    mflr    r0
    stw     r0, 12(r1)
    mflr    r6
    lis     r5, lbl_8049C224@ha
    subi    r6, r6, 4
    addi    r5, r5, lbl_8049C224@l
    li      r3, 0
    li      r4, 0
    crclr   6
    bl      OSPanic
    lwz     r0, 12(r1)
    mtlr    r0
    addi    r1, r1, 8
    blr
    // clang-format on
}
