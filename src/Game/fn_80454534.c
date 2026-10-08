// operator-new forwarder for the 8-byte object that fn_80454578 constructs (docs/versus.md section 5, row 2).
extern int fn_8024606C(void *p);

int fn_80454534(register void *self)
{
    return fn_8024606C(self);
}
