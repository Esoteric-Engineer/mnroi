typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef union {
    volatile u8 u8;
    volatile u16 u16;
    volatile u32 u32;
} GXFifoObj;

volatile GXFifoObj GXWGFifo : 0xCC008000;

#define GX_WRITE_RAS_REG(v)  \
    do {                     \
        GXWGFifo.u8 = 0x61;  \
        GXWGFifo.u32 = (v);  \
    } while (0)

void __GXSetTmemConfig(u32 config)
{
    switch (config) {
    case 2:
        GX_WRITE_RAS_REG(0x8c0d8000);
        GX_WRITE_RAS_REG(0x900dc000);
        GX_WRITE_RAS_REG(0x8d0d8800);
        GX_WRITE_RAS_REG(0x910dc800);
        GX_WRITE_RAS_REG(0x8e0d9000);
        GX_WRITE_RAS_REG(0x920dd000);
        GX_WRITE_RAS_REG(0x8f0d9800);
        GX_WRITE_RAS_REG(0x930dd800);
        GX_WRITE_RAS_REG(0xac0da000);
        GX_WRITE_RAS_REG(0xb00dc400);
        GX_WRITE_RAS_REG(0xad0da800);
        GX_WRITE_RAS_REG(0xb10dcc00);
        GX_WRITE_RAS_REG(0xae0db000);
        GX_WRITE_RAS_REG(0xb20dd400);
        GX_WRITE_RAS_REG(0xaf0db800);
        GX_WRITE_RAS_REG(0xb30ddc00);
        break;
    case 1:
        GX_WRITE_RAS_REG(0x8c0d8000);
        GX_WRITE_RAS_REG(0x900dc000);
        GX_WRITE_RAS_REG(0x8d0d8800);
        GX_WRITE_RAS_REG(0x910dc800);
        GX_WRITE_RAS_REG(0x8e0d9000);
        GX_WRITE_RAS_REG(0x920dd000);
        GX_WRITE_RAS_REG(0x8f0d9800);
        GX_WRITE_RAS_REG(0x930dd800);
        GX_WRITE_RAS_REG(0xac0da000);
        GX_WRITE_RAS_REG(0xb00de000);
        GX_WRITE_RAS_REG(0xad0da800);
        GX_WRITE_RAS_REG(0xb10de800);
        GX_WRITE_RAS_REG(0xae0db000);
        GX_WRITE_RAS_REG(0xb20df000);
        GX_WRITE_RAS_REG(0xaf0db800);
        GX_WRITE_RAS_REG(0xb30df800);
        break;
    case 0:
    default:
        GX_WRITE_RAS_REG(0x8c0d8000);
        GX_WRITE_RAS_REG(0x900dc000);
        GX_WRITE_RAS_REG(0x8d0d8400);
        GX_WRITE_RAS_REG(0x910dc400);
        GX_WRITE_RAS_REG(0x8e0d8800);
        GX_WRITE_RAS_REG(0x920dc800);
        GX_WRITE_RAS_REG(0x8f0d8c00);
        GX_WRITE_RAS_REG(0x930dcc00);
        GX_WRITE_RAS_REG(0xac0d9000);
        GX_WRITE_RAS_REG(0xb00dd000);
        GX_WRITE_RAS_REG(0xad0d9400);
        GX_WRITE_RAS_REG(0xb10dd400);
        GX_WRITE_RAS_REG(0xae0d9800);
        GX_WRITE_RAS_REG(0xb20dd800);
        GX_WRITE_RAS_REG(0xaf0d9c00);
        GX_WRITE_RAS_REG(0xb30ddc00);
        break;
    }
}
