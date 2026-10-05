// Two float getters; C++ because each ends in the cc1plus branch pair (docs/prodg.md).

extern "C" {

float fn_804325F4(register char *self)
{
    return *(float *)(self + 0x60);
}

float fn_80432628(register char *self)
{
    return *(float *)(self + 0x64);
}

}
