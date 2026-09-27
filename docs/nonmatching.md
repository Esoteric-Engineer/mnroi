# Confirmed Non-Matches

Functions claimed as `NonMatching`, with what has already been tried. Don't re-guess these. When a unit flips to `Matching`, delete its entry and move any general lesson to [`matching_notes.md`](matching_notes.md).

Checked across every entry below, none of these helped: compiler versions `GC/1.0` to `2.0` (`1.2.5n` is best or tied everywhere), `-O4,s`/`-O4`/`-O3`/`-O2`, `-inline off`, `-use_lmw_stmw on`, and `#pragma scheduling off`/`peephole off`/both.

---

## `__AXPrintStudio` (`Dolphin/ax/__AXPrintStudio.c`, `0x80408134`, size `0x3F8`)

59.25% fuzzy (right side 1056 bytes vs. original 1016). Not a printing function despite the name:
it recomputes 9 hardware-mixer-bus level meters (main/auxA/auxB × L/R/S, matching CFTKK/ac-decomp
position exactly between `__AXGetStudio` and `__AXSPBInit`) from 9 separate `.sbss` accumulators
(`lbl_8066FA98`..`lbl_8066FAB8`, each its own 4-byte symbol, *not* an array — ruling out a real
`for` loop over an array), writes `{raw:long, level:short}` pairs at 6-byte stride into the
`__AXGetStudio` struct (`lbl_806570C0`), then `DCFlushRange`s it. Per entry: `level = accum/160;
if (level==0) { accum=0; entry={0,0}; } else { clamp level to [-20,20]; entry.raw=accum; accum -=
level*160; entry.level=(short)-level; }`. Confirmed by matching the *shape* of blocks 2-9 exactly
(clamp compares, the reload-after-store idiom below, addressing mode) — the remaining gap is
entirely block 1 (the first entry, ~40 bytes).

**What matches (blocks 2-9, ~950 of 1016 bytes, all shape/branch/register-identical):**
- No cached `raw` local: `*(long*)(studio+off) = accum;` then `accum = accum - level*160;` directly
  on the global (not a temp) reproduces the original's odd "read global once for the divide+first
  store, then reload it fresh from memory for the remainder subtraction" pattern. Introducing a
  `long raw = accum;` local instead keeps `raw` live across the branch and costs ~15% match and
  40+ bytes (extra register, no reload). This is the single highest-value structural fix found.
- A `studio` pointer local (`unsigned char* studio = lbl_806570C0;`), used only via
  `studio + offset` casts, is required to get the address loaded once and reused for all 9 blocks
  (`r3` in the original) instead of recomputed per block: no `studio` local (bare
  `lbl_806570C0 + offset` in the macro body) reproduces the address load 9 times and drops to
  29.8%.
- `long`, not `int`, for the 9 `.sbss` accumulators and the local `level` (58.66% vs 59.25% fuzzy
  with `int`; smaller regression than most `int`/`long` swaps in this codebase, but still the
  wrong direction — see the general `int`/`long` coloring rule above).

**Still unmatched (block 1 only):** the original computes the magic-number reciprocal for `/160`
into `r3` (scratch, dies immediately), then loads `&lbl_806570C0` directly into `r3` (reusing that
now-dead register), then loads `raw`, i.e. `studio`'s home register is `r3` from its very first
materialization. In every C form tried, MWCC instead materializes `&lbl_806570C0` into `r4` first
(before or interleaved with the magic-number build, regardless of textual statement order — this
compiler's `-O4,p` allocator is insensitive to statement/declaration reordering here, confirmed by
~15 no-op experiments below) and then needs an extra `addi r3,r4,0` copy to move it to its
permanent home in `r3`. That extra copy makes `r4` unavailable for `level`'s live range in block 1
only, bumping `level` to `r6` there (blocks 2-9 use `r4` for `level`, matching the original, once
`studio` is already resident in `r3` from block 1 onward — so the fix is purely about how `studio`
is *first* materialized, not its steady-state register).

**Tried, no effect on block 1 (all still produce the `r4`-then-copy-to-`r3` shape):** hoisting
`studio` before vs. interleaved with the first division; `long raw`/`level` as function-scope vs.
per-block locals; `register unsigned char* studio`; `unsigned char* const studio`; a
`static inline GetStudioBase(void){return lbl_806570C0;}` wrapper (mimics `__AXGetStudio`'s own
return-in-r3 convention); `&lbl_806570C0[0]` instead of the bare array-decay; a `(void)studio;`
pin statement; passing `studio` vs. the bare global to the final `DCFlushRange` call. Since blocks
2-9 already match once `studio` is resident, the fix is specifically about the *first*
materialization and likely needs either the exact original source shape (unknown — no reference
source exists for this SDK cluster, see `docs/sdk_libraries.md` "Second SDK cluster") or
`decomp-permuter`.

