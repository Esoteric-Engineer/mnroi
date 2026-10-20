// Record constructor for the 0x60-byte table lbl_80567760: a Vector at +0x10 (docs/versus.md section 5, row 2).

extern "C" void __6Vector(void *self);

class Record
{
public:
    Record();
};

Record::Record()
{
    __6Vector((char *)this + 0x10);
}
