// Constructors of the 8-byte members the script classes hold (docs/story.md row 7).
// fn_8046B560-fn_8046B6C8 each pass the value on to the next, down to fn_8046B710.

struct Ref8 { // 8, name a guess
    int unk0;
    int value; // +0x4
};

extern "C" {

Ref8 *fn_8046B680(register Ref8 *self, register int value);
Ref8 *fn_8046B6C8(register Ref8 *self, register int value);
void fn_8046B710(register Ref8 *self, register int value);

Ref8 *fn_8046B530(register Ref8 *self)
{
    self->value = 0;
    return self;
}

Ref8 *fn_8046B560(register Ref8 *self, register int value)
{
    fn_8046B680(self, value);
    return self;
}

Ref8 *fn_8046B5A8(register Ref8 *self, register int value)
{
    fn_8046B560(self, value);
    return self;
}

Ref8 *fn_8046B5F0(register Ref8 *self, register int value)
{
    fn_8046B560(self, value);
    return self;
}

Ref8 *fn_8046B638(register Ref8 *self, register int value)
{
    fn_8046B5A8(self, value);
    return self;
}

Ref8 *fn_8046B680(register Ref8 *self, register int value)
{
    fn_8046B6C8(self, value);
    return self;
}

Ref8 *fn_8046B6C8(register Ref8 *self, register int value)
{
    fn_8046B710(self, value);
    return self;
}

void fn_8046B710(register Ref8 *self, register int value)
{
    self->value = value;
}

}
