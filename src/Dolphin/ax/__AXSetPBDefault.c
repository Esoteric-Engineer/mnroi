#define U16(base, off) (*(unsigned short*)((unsigned char*)(base) + (off)))
#define U32(base, off) (*(unsigned long*)((unsigned char*)(base) + (off)))

void __AXSetPBDefault(void* p)
{
    U16(p, 0x146) = 0;
    U16(p, 0x16e) = 0;
    U32(p, 0x1c) = 0xa4;
    U32(p, 0x28) = 0;
    U32(p, 0x24) = 0;
    U32(p, 0x30) = (unsigned long)((unsigned char*)p + 0x34);
    U16(p, 0x184) = 0;
    U16(p, 0x182) = 0;
    U16(p, 0x180) = 0;
    U16(p, 0x17e) = 0;
    U16(p, 0x17c) = 0;
    U16(p, 0x1f2) = 0;
}
