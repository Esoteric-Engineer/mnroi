// Base constructor of Block (fn_8045F640): stores the vptr lbl_804F5BD8. Name is a guess.
extern char lbl_804F5BD8[];

class BlockBase
{
public:
    const void *vptr; // +0x0
    BlockBase();
};

BlockBase::BlockBase()
{
    vptr = lbl_804F5BD8;
}
