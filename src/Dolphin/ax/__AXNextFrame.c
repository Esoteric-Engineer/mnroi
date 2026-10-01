extern void* __AXGetStudio(void);
extern void* __AXGetPBs(void);
extern void __AXGetAuxAInput(unsigned long* out);
extern void __AXGetAuxAInputDpl2(unsigned long* out);
extern void __AXGetAuxAOutput(unsigned long* out);
extern void __AXGetAuxAOutputDpl2R(unsigned long* out);
extern void __AXGetAuxAOutputDpl2Ls(unsigned long* out);
extern void __AXGetAuxAOutputDpl2Rs(unsigned long* out);
extern void __AXGetAuxBInput(unsigned long* out);
extern void __AXGetAuxBOutput(unsigned long* out);
extern void __AXGetAuxBForDPL2(unsigned long* out);
extern void __AXGetAuxBOutputDPL2(unsigned long* out);
extern void DCFlushRange(void*, unsigned long);

extern unsigned short* __AXClWrite;
extern unsigned long __AXCommandListCycles;
extern unsigned long __AXCompressor;
extern unsigned long __AXClMode;
extern unsigned short lbl_804EF0C0[];

#define AXCL_WRITE(v)                                                       \
    *__AXClWrite = (unsigned short)(v);                                    \
    __AXClWrite++;

void __AXNextFrame(void* sbuffer, void* buffer)
{
    unsigned long data;
    unsigned short* pCommandList;
    unsigned char unused[56];

    __AXCommandListCycles = 0x1A9;
    pCommandList = __AXClWrite;
    data = (unsigned long)__AXGetStudio();
    AXCL_WRITE(0);
    AXCL_WRITE(data >> 0x10);
    AXCL_WRITE(data);
    __AXCommandListCycles += 0x2E44;

    switch (__AXClMode) {
    case 0:
        AXCL_WRITE(7);
        AXCL_WRITE((unsigned long)sbuffer >> 0x10);
        AXCL_WRITE((unsigned long)sbuffer);
        __AXCommandListCycles += 0x546;
        break;
    case 1:
        AXCL_WRITE(0x11);
        AXCL_WRITE((unsigned long)sbuffer >> 0x10);
        AXCL_WRITE((unsigned long)sbuffer);
        __AXCommandListCycles += 0x5E6;
        break;
    case 2:
        break;
    default:
        break;
    }

    data = (unsigned long)__AXGetPBs();
    AXCL_WRITE(2);
    AXCL_WRITE(data >> 0x10);
    AXCL_WRITE(data);
    AXCL_WRITE(3);

    if (__AXClMode == 2) {
        __AXGetAuxAInput(&data);
        if (data != 0) {
            AXCL_WRITE(0x13);
            AXCL_WRITE(data >> 0x10);
            AXCL_WRITE(data);
            __AXGetAuxAInputDpl2(&data);
            AXCL_WRITE(data >> 0x10);
            AXCL_WRITE(data);
            __AXGetAuxAOutput(&data);
            AXCL_WRITE(data >> 0x10);
            AXCL_WRITE(data);
            __AXGetAuxAOutputDpl2R(&data);
            AXCL_WRITE(data >> 0x10);
            AXCL_WRITE(data);
            __AXGetAuxAOutputDpl2Ls(&data);
            AXCL_WRITE(data >> 0x10);
            AXCL_WRITE(data);
            __AXGetAuxAOutputDpl2Rs(&data);
            AXCL_WRITE(data >> 0x10);
            AXCL_WRITE(data);
            __AXCommandListCycles += 0xDED;
        }
        AXCL_WRITE(0x10);
        __AXGetAuxBForDPL2(&data);
        AXCL_WRITE(data >> 0x10);
        AXCL_WRITE(data);
        __AXGetAuxBOutputDPL2(&data);
        AXCL_WRITE(data >> 0x10);
        AXCL_WRITE(data);
        __AXCommandListCycles += 0xDED;
    } else {
        __AXGetAuxAInput(&data);
        if (data != 0) {
            AXCL_WRITE(4);
            AXCL_WRITE(data >> 0x10);
            AXCL_WRITE(data);
            __AXGetAuxAOutput(&data);
            AXCL_WRITE(data >> 0x10);
            AXCL_WRITE(data);
            __AXCommandListCycles += 0xDED;
        }

        __AXGetAuxBInput(&data);
        if (data != 0) {
            AXCL_WRITE(5);
            __AXCommandListCycles += 0xDED;
            AXCL_WRITE(data >> 0x10);
            AXCL_WRITE(data);
            __AXGetAuxBOutput(&data);
            AXCL_WRITE(data >> 0x10);
            AXCL_WRITE(data);
        }
    }

    if (__AXCompressor) {
        AXCL_WRITE(0x12);
        AXCL_WRITE(0x8000);
        AXCL_WRITE(0xA);
        AXCL_WRITE((unsigned long)lbl_804EF0C0 >> 0x10);
        AXCL_WRITE((unsigned long)lbl_804EF0C0);
        __AXCommandListCycles += 0xBB8;
    }

    AXCL_WRITE(0xE);
    AXCL_WRITE((unsigned long)sbuffer >> 0x10);
    AXCL_WRITE((unsigned long)sbuffer);
    AXCL_WRITE((unsigned long)buffer >> 0x10);
    AXCL_WRITE((unsigned long)buffer);
    __AXCommandListCycles += 0x2710;
    AXCL_WRITE(0xF);
    __AXCommandListCycles += 2;
    DCFlushRange(pCommandList, 0x300);
}
