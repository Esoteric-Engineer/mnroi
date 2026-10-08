// operator-new forwarder for the object the handler at 0x8010D268 allocates (docs/versus.md section 5, row 2).
extern int fn_8024606C(void *p);

int fn_8045466C(register void *self)
{
    return fn_8024606C(self);
}
