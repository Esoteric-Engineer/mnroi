extern unsigned long lbl_8066F980;

unsigned long* __VMBASEVirtualAddrToPageTableAddr(unsigned long addr)
{
    return (unsigned long*)(lbl_8066F980 | ((addr >> 6) & 0xFFC0) | ((addr >> 19) & 0x38));
}
