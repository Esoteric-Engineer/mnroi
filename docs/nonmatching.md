# Confirmed Non-Matches

Functions claimed as `NonMatching`, with what has already been tried. Don't re-guess these. When a unit flips to `Matching`, delete its entry and move any general lesson to [`matching_notes.md`](matching_notes.md).

---

## `__ARChecksize` (`0x80404BB0`, `Dolphin/ar/__ARChecksize.c`)

~33% fuzzy. `ac-decomp`'s `ar.c` gives the algorithm shape (probe ARAM by DMA'ing a test
pattern and reading it back at increasing offsets to size the expansion pak), and that source
was used as the starting point, but **this build's actual disassembly diverges from ac-decomp's
published source in ways that need to be reverse-engineered from scratch, not adapted**:

- `__ARWaitForDMA`/`__ARWriteDMA`/`__ARReadDMA` (`static` in ac-decomp) must be `static inline`
  here to get MWCC to fold them into `__ARChecksize` at all (plain `static` left them as
  separate out-of-line functions called via `bl`, ~2160 bytes total instead of the target's 6132).
- `__ARClearInterrupt` is **not** called via `bl` anywhere in the target (no such relocation
  exists in the object). ac-decomp's `__ARWriteDMA`/`__ARReadDMA` call the real
  `__ARClearInterrupt`, but here it must be a second `static inline` copy of the body
  (`tmp = __DSPRegs[5]; tmp = (tmp & ~0x88) | 0x20; __DSPRegs[5] = tmp;`) local to this unit,
  same pattern as the `__CARDCheckSum` note in `matching_notes.md`. The real, separately-linked
  `__ARClearInterrupt` (`Dolphin/ar/__ARClearInterrupt.c`, already `Matching`) has some other
  caller elsewhere that still needs the out-of-line copy.
- The target caches pointers to `&__DSPRegs[16..21]` (the six DMA control registers) **once**
  near the top of the function (six `addi rN,r23,0x5000`-style base+offset computations) and
  reuses those cached registers via `sthu`/plain `sth`/`lhz` across *every* inlined DMA op for
  the rest of the function, rather than re-deriving `__DSPRegs[N]` from the array base each time.
  A straightforward transliteration of ac-decomp's `__ARWriteDMA`/`__ARReadDMA` bodies (as
  written above) does not reproduce this hoisting.
- The relocation list only contains `memset` (x5), `DCFlushRange` (x7), `DCInvalidateRange`
  (x5), `PPCSync` (x10) — no `__ARClearInterrupt`. ac-decomp's structure predicts exactly one
  `DCInvalidateRange` (before the first read) and 5 `PPCSync` (one per read attempt); the target
  has `DCInvalidateRange` before **every** read attempt and **two** `PPCSync` per read attempt,
  meaning the real control flow around each nested read differs from ac-decomp's (order of
  invalidate/read/sync, and something call-shaped that resolves to `PPCSync` a second time per
  attempt — not yet identified).
- There are **8 distinct 32-byte-aligned stack buffers** in the target (traced via the
  `clrrwi rX,rY,5` alignment ops: `test_data`, `dummy_data`, plus **six** more), not the 3
  ac-decomp declares (`test_data`, `dummy_data`, one shared `buffer` reused across all nested
  `if`/`else` levels). This means the real source almost certainly declares a **separate**
  `u8 buffer_pad[63]` local at each nesting level instead of reusing one `buffer`, and likely
  has **one more nested probe level than ac-decomp's 4** (6 buffers implies 6 read attempts
  total, not 5) — i.e. this SDK build may support one additional ARAM expansion size tier.
  ac-decomp's own offset/size pairs for the nested checks already look internally inconsistent
  (e.g. probes `+0x01000000` but on match adds only `+0x400000`), so its source may itself be an
  imperfect decompilation of this same function and should not be trusted for the exact branch
  count or offsets — only for the general shape.
- CFTKK-Decomp has no source for this function (symbol/size only, no shipped binary in that
  repo to cross-check), so it can't help refine the branch count either.

**Next steps for whoever picks this up:** trace the full disassembly (`build/GVLE69/obj/Dolphin/ar/__ARChecksize.o`,
1533 lines via `objdump -dr`) branch-by-branch from scratch — don't start from ac-decomp's C.
Map each of the 8 aligned buffers and each conditional (`bne`) target to reconstruct the real
nesting and the real offset/size table, then write C matching that shape (separate `u8 ..._pad[63]`
per branch, inline `__ARClearInterrupt` copy, `static inline` DMA helpers as above).

---
