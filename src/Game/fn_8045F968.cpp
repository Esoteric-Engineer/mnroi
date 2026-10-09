// Block::addRef: increments the count at +0x24 and returns it (fn_8045F9A0 is the release). Names are guesses.
class Block
{
public:
    int data[9]; // +0x0
    int refs;    // +0x24
    int addRef();
};

inline int sn_return_decl(int a) { return a; }

int Block::addRef()
{
    return ++refs;
}
