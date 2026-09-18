typedef struct GXTexObj GXTexObj;
typedef int GXTexMapID;

extern void GXLoadTexObjPreLoaded(GXTexObj* obj, void* region, GXTexMapID id);

asm void GXLoadTexObj(register GXTexObj* obj, register GXTexMapID id)
{
    nofralloc
    mflr    r0
    stw     r0, 4(r1)
    stwu    r1, -24(r1)
    stw     r31, 20(r1)
    addi    r31, id, 0
    stw     r30, 16(r1)
    addi    r30, obj, 0
    lwz     r5, -11608(r13)
    lwz     r12, 1224(r5)
    mtlr    r12
    blrl
    addi    r4, r3, 0
    addi    r3, r30, 0
    addi    r5, r31, 0
    bl      GXLoadTexObjPreLoaded
    lwz     r0, 28(r1)
    lwz     r31, 20(r1)
    lwz     r30, 16(r1)
    addi    r1, r1, 24
    mtlr    r0
    blr
}
