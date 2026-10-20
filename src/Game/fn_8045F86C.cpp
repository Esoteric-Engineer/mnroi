// Zeroes four words; called through Chain::setup in fn_8045F49C.cpp. Name is a guess.
inline int sn_return_decl(int a) { return a; }

class Quad4
{
public:
    int a; // +0x0
    int b; // +0x4
    int c; // +0x8
    int d; // +0xC
    void clear();
};

void Quad4::clear()
{
    a = 0;
    b = 0;
    c = 0;
    d = 0;
}
