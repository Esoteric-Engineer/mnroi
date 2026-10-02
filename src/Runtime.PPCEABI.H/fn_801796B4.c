// Called only by fn_8017A608 (`li r3, 1; crclr 6; bl`), which does not restore its own lr, so this is a noreturn stub:
// the illegal zero word halts the CPU and the `blr` is the epilogue the compiler emitted after it.
asm void fn_801796B4(int status)
{
    // clang-format off
    nofralloc
    opword  0
    blr
    // clang-format on
}
