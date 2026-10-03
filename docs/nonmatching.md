# Confirmed Non-Matches

Functions claimed as `NonMatching`, with what has already been tried. Don't re-guess these. When a unit flips to `Matching`, delete its entry and move any general lesson to [`matching_notes.md`](matching_notes.md).

---

## `Game/handlers/characterselect.cpp` — `clashCharSelect_GetCharList`

0x801037B0-0x80103BAC, 99.2% fuzzy. Every instruction matches and the frame layout is identical; the
unit is 8 bytes over size because our build emits **three** branches to the epilogue where the
original has one:

- Original: copy constructor, destructor, `b .L`, then `.L: mr r3, r30` and the epilogue.
- Ours: the same, then `b .L` twice more.

The two extras are unreachable, and they are not a source-shape artifact. Every C++ function that
returns a class by value emits them on all five bundled ProDG releases (`return local;`,
`return T(local);`, `return T(args);`, `(T)local`, `inline`, `static`, nested scopes, returns inside
loops and non-final returns all tested), while 123 of the DOL's 127 aggregate-return epilogues have a
single branch. The four that have three are POD structs copied inline, which is the one case our
compilers do reproduce. See [`prodg.md`](prodg.md#release).

Also tried, with no effect: all five releases, all five assemblers (plus `ngcasm`), every `-f` option
string in `cc1plus.exe` (1564 candidates in both `-f` and `-fno-` forms; only
`-fprefix-function-name` changed anything, by renaming the symbol), `-fno-exceptions`,
`-fno-rtti`, `-fpcc-struct-return`, `-freg-struct-return`, and `-O1`/`-O2` (which drop the `-O0`
spills the original has). Note that `ngccc` silently discards options it does not recognise, so flag
experiments must drive `CPP.exe` and `cc1plus.exe` directly.

`clashCharSelect_GetPrevCharList` (0x80103BAC) ends with the same copy/destructor/return sequence, so
the rest of the file is blocked the same way.

---

## `Game/fn_8044B1D4.c` — roster field accessors

All 8 functions (`fn_8044B1D4`, `fn_8044B234`, `fn_8044B298`, `fn_8044B2FC`, `fn_8044B360`,
`fn_8044B3C4`, `fn_8044B428`, `fn_8044B48C`; 0x8044B1D4-0x8044B4EC) sit at 99.0-99.04% fuzzy, each
stuck on exactly the same one-register diff. Shape, instruction count and size are all byte-for-byte
right; only the register number differs:

- Original: `stmw r27, 0x14(r1)` (frame 0x28), copies the `fn_80431CCC` return value through
  `mr r27, r3` before `stw r27, 0x8(r31)`, restores with `lmw r27, -0x14(r11)`.
- Ours: `stmw r28, 0x10(r1)` (frame 0x20), copies through the volatile `mr r0, r3` instead, restores
  `lmw r28, -0x10(r11)`.

So the original reserves one extra non-volatile register (r27) purely to hold the `CharacterRecord *`
local across the `stw` to its frame slot, where ours uses `r0` as a throwaway copy. The result is
read back from the frame slot either way (`lwz r9, 0x8(r31)`), never from r27 again, so the extra
register is functionally dead — a pure register-allocation artifact of GCC 2.95's `-O0` pass, not a
reachable behavior difference.

Tried without effect on the register choice (all reproduce the exact same `r0`-based output, or move
further away): combined vs. split declaration+init, `volatile` on the local, wrapping the assignment
in `(x = call())->field`, an explicit redundant cast on the call result, K&R-style parameter
declarations, an unprototyped (K&R) `extern` for `fn_80431CCC`, byte-pointer arithmetic instead of a
struct pointer, a dummy initializer, and a second named local for the final return value (each of
these last few also changed the instruction shape, not just the register, so they're confirmed wrong
in addition to not fixing the register). The source given here is otherwise an exact byte/instruction
match and is the believed-correct C; whatever controls this specific register choice in ProDG's GCC
2.95 hasn't been found. Try [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) next.
