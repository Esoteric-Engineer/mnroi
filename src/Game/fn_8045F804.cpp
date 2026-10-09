// Base constructor of Machine (fn_8045F728): stores the vptr lbl_804F5C10. Name is a guess.
extern char lbl_804F5C10[];

class MachineBase
{
public:
    const void *vptr; // +0x0
    MachineBase();
};

MachineBase::MachineBase()
{
    vptr = lbl_804F5C10;
}
