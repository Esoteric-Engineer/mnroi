// Constructor over Sink (fn_8045E270): replaces the vptr with lbl_804F5B60 and sets a flag at +0x8. Names are guesses.
extern char lbl_804F5B60[];

class Sink
{
public:
    const void *vptr; // +0x0
    Sink();
};

class SinkB : public Sink
{
public:
    int pad;  // +0x4
    int flag; // +0x8
    SinkB();
};

SinkB::SinkB()
{
    vptr = lbl_804F5B60;
    flag = 1;
}
