// AI inline function: a random float between a and b + 1.
// docs/ai.md row 5. Pool at 0x8049BAE8 (extern_pool), in another file's .rodata.

inline int sn_return_decl(int a) { return a; }

extern "C" float fn_804358A4(void);

extern "C" float fn_80464448(register float a, register float b)
{
    return a + (b + 1.0f - a) * fn_804358A4();
}
