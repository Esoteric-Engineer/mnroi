// Forwarder through the actor's sub-object handle (docs/versus.md, row 8).

extern "C" {
void *fn_8032A228(void *self);
void *fn_80435340(void *self);
int fn_8043CA98(void *self);

int fn_8043C1EC(register void *self)
{
    return fn_8043CA98(fn_80435340(fn_8032A228(self)));
}
}
