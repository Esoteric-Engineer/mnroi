extern unsigned long* lbl_8066F984;

void __VMBASESetVirtualAddressForPageInMRAM(unsigned long page, unsigned long addr)
{
    lbl_8066F984[page] = addr;
}
