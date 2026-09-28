# Confirmed Non-Matches

Functions claimed as `NonMatching`, with what has already been tried. Don't re-guess these. When a unit flips to `Matching`, delete its entry and move any general lesson to [`matching_notes.md`](matching_notes.md).

---

## `CARDFastOpen` (`0x8040E1BC`, `Dolphin/card/CARDFastOpen.c`)

88.7% fuzzy, 0x104. Every instruction is present and in the original's order; what is left is a
saved-register rotation plus the one copy it costs (ours is 256 bytes, the original 260).

- Original: `fileInfo`=r31, `fileNo`=r30, `chan`=r29, `ent`=r28, and `result` stays in r3 across
  both compares, with `addi r4,r3,0` emitted between `cmpwi r3,0` and the `blt`.
- Ours: `ent`=r31, `fileInfo`=r30, `fileNo`=r29, `chan`=r28, and `result` is copied to r4 right
  after the `bl __CARDIsWritable`, so both compares read r4.

The two are one cause: MWCC at `-O4,p` always ranks this mid-function pointer local *above* the
parameters, so `ent` takes r31 and pushes each parameter down one. The original has the parameters
first and `ent` last.

Tried, none of which moved it off 88.7%:

- All 24 declaration permutations of `card`/`dir`/`ent`/`result`, and the same with one or two
  never-assigned padding locals added (note 99's `ReadFont` trick). Register allocation is
  completely insensitive to declaration order here.
- Removing `dir` (`ent = __CARDGetDirBlock(card) + fileNo`), reusing `dir` as the cursor
  (`dir += fileNo`), `ent` assigned inside the call argument
  (`__CARDIsWritable(card, ent = &dir[fileNo])`), and `ent` assigned after the call from the same
  expression (that one grows the frame to 0x30).
- Dropping `ent` entirely and letting CSE make the temp: `dir[fileNo].x`, `(dir + fileNo)->x`, and
  a byte-arithmetic macro `((CARDDir*)((char*)dir + fileNo * 0x40))`. MWCC splits the address into
  separate `dir` and `fileNo << 6` temps and recomputes the `add` at each use (61 diff lines).
- `&&` vs nested `if` vs ternary vs permission-test-first for the `CARD_RESULT_NOPERM` fixup;
  `__CARDIsPublic` as a `static`/`static inline` helper; assignment inside the condition.
- `if (result >= 0) {...}` vs `if (5 <= b && b < cBlock)` vs `!(...)`, and an early-return
  (three-`return __CARDPutControlBlock(...)`) shape to try to get the tail-merge that would explain
  the late `addi r4,r3,0`.
- `register` on the parameters, `const CARDDir* ent`, K&R parameter declarations (both orders).
- Pragmas: `scheduling off`, `peephole off`, `optimize_for_size on/off`, `no_register_coloring on`,
  `global_optimizer off`, `opt_common_subs off`, `opt_propagation off`, `opt_dead_assignments off`,
  `opt_lifetimes off`, `opt_partial_redundancies off`, `opt_strength_reduction off`,
  `opt_pointer_analysis off`, `opt_dead_code off`, `aggressive_inline on`.
- Flags: `-O4` / `-O4,s` / `-O3` / `-O2` (all worse), `-inline off/on/all`, `-schedule off`.
- Compiler versions 1.2.5, 1.3, 1.3.2, 1.3.2r, 2.0, 2.5, 2.6, 2.7 — all worse than 1.2.5n.

The one lead: **`#pragma optimization_level 1` (with the library's `-O4,p` otherwise) gives exactly
the original's register assignment** and drops the diff to 26 lines, but then loses the CSE of
`ent->startBlock`, adds `clrlwi`/`mr` shuffles, and turns the `-10` compare back into r4. So the
ranking the original used is reachable, just not from `-O4,p` with any source shape tried. A future
attempt should look for what else in the real TU (CARDOpen.c held `__CARDCompareFileName`,
`__CARDIsWritable`, `__CARDIsReadable`, `__CARDGetFileNo`, `CARDFastOpen`, `CARDOpen`, `CARDClose`)
could add a fifth register candidate.

Useful contrast: `CARDFastDeleteAsync` (`0x8040F064`) is the same front half and *matches* with the
plain `dir`/`ent` shape, and there the original also puts `ent` in r31. `CARDGetStatus`
(`0x8040F528`) matches with `ent` reusing `fileNo`'s register. So both orders occur in the original
objects; only this function wants parameters-first.
