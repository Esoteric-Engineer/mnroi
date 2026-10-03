# Confirmed Non-Matches

Functions claimed as `NonMatching`, with what has already been tried. Don't re-guess these. When a unit flips to `Matching`, delete its entry and move any general lesson to [`matching_notes.md`](matching_notes.md).

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
