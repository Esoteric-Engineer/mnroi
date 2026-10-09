// Constructor whose only work is constructing the member at +0x74 (fn_802BB700). Name is a guess.
extern "C" void fn_802BB700(void *);

class Cell
{
public:
    char pad[0x74];
    Cell();
};

Cell::Cell()
{
    fn_802BB700((char *)this + 0x74);
}
