// Constructor of a list-derived class (docs/versus.md section 5, row 2); class names are guesses.
class List
{
public:
    List(int n, float f) __asm__("fn_801B5BA8");
};

class ListA : public List
{
public:
    ListA();
};

ListA::ListA() : List(4, 1.0f)
{
}

extern "C" void fn_801B5C74(void *self, int flag);
extern "C" void __builtin_delete(void *p);

// ListA destructor, hand-written C shape (matching_notes.md)
extern "C" void fn_8045E6F8(register void *self, register int inChrg)
{
    fn_801B5C74(self, 2);
    if (inChrg & 1) {
        __builtin_delete(self);
    } else {
    }
}
