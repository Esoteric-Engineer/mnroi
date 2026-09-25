typedef unsigned long u32;

typedef struct TEXDescriptor {
    void* textureHeader;
    void* CLUTHeader;
} TEXDescriptor;

typedef struct TEXPalette {
    u32 versionNumber;
    u32 numDescriptors;
    TEXDescriptor* descriptorArray;
} TEXPalette;

TEXDescriptor* TEXGet(TEXPalette* pal, u32 id) {
    return &pal->descriptorArray[id];
}
