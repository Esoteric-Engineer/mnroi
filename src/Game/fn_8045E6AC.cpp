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
