# Confirmed Non-Matches

Functions claimed as `NonMatching`, with what has already been tried. Don't re-guess these. When a unit flips to `Matching`, delete its entry and move any general lesson to [`matching_notes.md`](matching_notes.md).

No registered unit is `NonMatching`. One compiler behaviour used to park whole files:

## The C++ function-end branch pair

`cc1plus` ends a C++ function with two unreachable branches to the epilogue (`b .L5` / `b .L4` / `.L5:` /
`.L4:`) unless an earlier function in the same translation unit set `current_function_return_value`. A
constructor sets it, and so does a top-level `return` of a parameter, local, global or `this`, even
inside an unused inline function. Only a `case`/`default` or a user label clears it. No option changes it.

**Fix:** put `inline int sn_return_decl(int a) { return a; }` ahead of the unit's first function when the
original's flag was already set there (`Game/fn_800887AC.cpp`, `Game/handlers/characterselect.cpp` and
`Game/fn_8002623C.cpp` do). [`prodg.md`](prodg.md#the-function-end-branch-pair) has the code, the evidence
and the ordering rules, and `python3 tools/pair_map.py <address>` says which state a function was in. There
is no build-side workaround: the build used to have a per-unit `strip_fn_end_pair` that deleted the pair from
the assembly, and it was removed because it can't model a file where a `switch` brings the pair back.

## Unclaimed: AI manager static init (`fn_80137D98`, `_GLOBAL_.I` 0x80137EB4, `_GLOBAL_.D` 0x80137EF0)

The end of `Game/fn_80132480.cpp`'s file (`docs/ai.md` row 6). Real globals reproduce the DOL's
`__static_initialization_and_destruction_0` exactly in a scratch compile, pair-less after the unit's
setter: `Volumes lbl_80569890; Rec lbl_8056996C[16];` with constructors `__asm__("fn_80461430")` /
`__asm__("fn_804619C8")`, plus `fn_801ACFD4` renamed `__builtin_vec_delete`. The destructors are the
blocker: an `__asm__` label on a destructor makes cc1plus drop its calls (it emits only the
`__builtin_delete` branch), and a destructor can't be redeclared outside its class, so the calls only appear
as the mangled `_._4Perc` / `_._3Rec`. That needs the real class names. Hand-writing it fails too: the
generated code tests the unfolded constants `&lbl_8056996C != 0` and `1 & 2`. Matching also claims `.bss`
0x80569890-0x8056A72C and the `.ctors`/`.dtors` words.
