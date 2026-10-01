extern void* __CallbackStack;
extern void* __OldStack;

asm void __AICallbackStackSwitch(register void* cb)
{
    // clang-format off
    nofralloc
    mflr    r0
    stw     r0, 4(r1)
    stwu    r1, -0x18(r1)
    stw     r31, 0x14(r1)
    mr      r31, r3
    lis     r5, __OldStack@ha
    addi    r5, r5, __OldStack@l
    stw     r1, 0(r5)
    lis     r5, __CallbackStack@ha
    addi    r5, r5, __CallbackStack@l
    lwz     r1, 0(r5)
    subi    r1, r1, 8
    mtlr    r31
    blrl
    lis     r5, __OldStack@ha
    addi    r5, r5, __OldStack@l
    lwz     r1, 0(r5)
    lwz     r0, 0x1c(r1)
    lwz     r31, 0x14(r1)
    addi    r1, r1, 0x18
    mtlr    r0
    blr
    // clang-format on
}
