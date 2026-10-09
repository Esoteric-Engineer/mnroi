// Creates a Block: class operator new (size 0x28, file, line) then the constructor fn_8045F640. Names are guesses.
extern char lbl_804995A0[];

class Block
{
public:
    int data[10];
    Block();
    static void *operator new(unsigned size, const char *file, int line) __asm__("forward__3Fwdii");
};

class Maker
{
public:
    Block *make();
};

inline int sn_return_decl(int a) { return a; }

Block *Maker::make()
{
    return new (lbl_804995A0, 0) Block;
}
