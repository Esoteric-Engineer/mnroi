// Forwards to fn_8024606C on the record's own pointer (docs/versus.md section 5, row 2).
extern int fn_8024606C(void *p);

int fn_804543DC(register void *self)
{
    return fn_8024606C(self);
}
