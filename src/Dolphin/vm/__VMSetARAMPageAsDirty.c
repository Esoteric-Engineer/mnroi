extern unsigned long* lbl_8066F974;

void __VMSetARAMPageAsDirty(unsigned long addr)
{
    lbl_8066F974[(addr >> 12) & 0x1FFF] |= 0x80000000;
}
