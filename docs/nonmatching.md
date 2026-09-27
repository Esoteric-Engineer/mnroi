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

## `__AXServiceVPB` (`Dolphin/ax/__AXServiceVPB.c`, `0x804085F8`, size `0x74C`)

99.31% fuzzy. No reference source exists (AX audio mixer isn't in ac-decomp or CFTKK-Decomp; ac-decomp's
`dolphin/` tree has no `ax/` at all, and CFTKK-Decomp is names/sizes only, no `.c` files). Every line was
hand-transliterated from the disassembly of `build/GVLE69/obj/auto_01_804085F8_text.o`. The function syncs
one `AXVPB`'s parameter block (`p`) against its internal per-voice slot (`lbl_80657100 + p->index*244`, a
244-byte `AXPB`) and an app-visible mirror embedded at `p+312`, gated field-by-field on `p->sync`'s 23
individual bits, plus two runtime-length `p->extraCount`-word copies to/from a 256-byte-stride array at
`lbl_80657100 + (p->index<<8) + 0x4D00` (`lbl_8065BE00` in `__AXSyncPBs.c`'s naming). All field offsets,
widths (u16/s16/u32) and per-bit directions (mostly mirror→internal; bits 0x4, 0x10000 in the combined
0x1E000 group, and the `sync==0` early-return path swap direction based on the bit) were read directly off
the disasm and are believed correct — see [`matching_notes.md`](matching_notes.md) for the `base +
(index<<shift) + const` array-cast fix that got the add/addi order right.

**Still unmatched:** in the two `p->extraCount`-driven block-copy loops (the `sync & 0x80000000` "full
update" path and the `sync & 0x80` path), the original puts the simple `(u8*)p + 52` pointer in `r3`
(reusing `p`'s own register in place — `p` is dead after this point in both paths) and the array-indexed
`lbl_80657100`-relative pointer in `r5`/`r8`. Every C form tried puts the array-indexed pointer in `r3`
and `(u8*)p + 52` in a fresh register (`r6`/`r9`) instead — same instructions/immediates, just the two
pointers' registers swapped, in both loops identically. This costs the fuzzy score even though the loop
bodies that use them (the 8-word-unrolled-with-remainder `bdnz` copy, matching `__AXOutNewFrame`'s proven
`for(;n!=0;n--){*d++=*s++;}` shape) are otherwise byte-identical.

**Tried, no effect on which pointer gets `r3`:** swapping declaration order of the two pointer locals
(fixed the unrelated `pb`/`mirror` register swap earlier in this same function, so it's not a dead lever
in general); swapping assignment/statement order of the two pointers; hoisting both to function scope
(alongside `pb`/`mirror`/`base`, which is where the successful fixes for those locals live) instead of
block scope; `register` on one of the two; `unsigned char*` instead of `unsigned long*` for both, with
manual `+= 4` advances instead of `unsigned long*` post-increment; assigning `(AXVPB*)((u8*)p+52)` back
into `p` itself instead of a separate local (this changes the shape entirely — adds `addi rX,rY,0` copies
— so `p` is evidently *not* simply "still live in r3" the way the original's is). `#pragma scheduling off`
makes the whole function worse (94.2% vs. 99.3%), so it's off. No reference source exists to check the true
argument order/shape against.

