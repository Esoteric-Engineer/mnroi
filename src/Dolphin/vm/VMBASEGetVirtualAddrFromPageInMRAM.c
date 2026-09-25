extern unsigned long* lbl_8066F984;

unsigned long VMBASEGetVirtualAddrFromPageInMRAM(unsigned long page)
{
    return lbl_8066F984[page];
}
