typedef unsigned short u16;
typedef unsigned int u32;

volatile u16 __DSPRegs[0x200] : 0xCC005000;

void DSPSendMailToDSP(u32 mail)
{
	__DSPRegs[0] = mail >> 16;
	__DSPRegs[1] = mail & 0xFFFF;
}
