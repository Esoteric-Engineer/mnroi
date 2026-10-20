// Attack volume setup (7 volumes of 0x80 bytes at ctrl+0x580): picks the two attachment (kind, index) pairs a volume spans by its number 1-7. docs/characters.md section 4.

class Volume
{
public:
    int kind;        // +0x00
    unsigned int number; // +0x04, 1-7
    char pad8[0x64];
    int fromKind;    // +0x6C
    int toKind;      // +0x70
    int fromIndex;   // +0x74
    int toIndex;     // +0x78
    void Setup(int a, int b);
};

__asm__(".text\n\t.globl fn_800F43D4\n\t.type fn_800F43D4,@function\nfn_800F43D4:");
void Volume::Setup(int a, int b)
{
    kind = a;
    number = b;
    switch (number) {
    case 1:
        fromKind = 3;
        fromIndex = 1;
        toKind = 5;
        toIndex = 1;
        break;
    case 2:
        fromKind = 3;
        fromIndex = 2;
        toKind = 5;
        toIndex = 2;
        break;
    case 3:
        fromKind = 0x15;
        fromIndex = 2;
        toKind = 0x17;
        toIndex = 2;
        break;
    case 4:
        fromKind = 0x15;
        fromIndex = 1;
        toKind = 0x17;
        toIndex = 1;
        break;
    case 5:
        fromKind = 0x28;
        fromIndex = 1;
        toKind = 0x2A;
        toIndex = 1;
        break;
    case 6:
        fromKind = 0x28;
        fromIndex = 2;
        toKind = 0x2A;
        toIndex = 2;
        break;
    case 7:
        fromKind = 0x2B;
        fromIndex = 0;
        toKind = 0x2C;
        toIndex = 0;
        break;
    default:
        break;
    }
}
__asm__(".size fn_800F43D4, 0x18C");
