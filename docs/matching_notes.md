# Matching Notes

Compiler/linker behavior and techniques learned while matching functions in this game. Helpful to review when a function is stuck short of 100%.

---

## Compiler gotchas

- **Dolphin SDK register writes use the CodeWarrior `__rlwimi` intrinsic, not plain C:**

  ```c
  #define SET_REG_FIELD(reg, size, shift, val)                    \
      (reg) = (u32)__rlwimi((int)(reg), (int)(val), (shift),      \
                            (32 - (shift) - (size)), (31 - (shift)))
  ```

  A bare `rlwimi` in the original is the giveaway. Plain C like `(reg & ~mask) | ((val & m) << shift)` gets around 65%; dropping the value mask gets around 53%. Only the intrinsic matches.

- **An `asm` function disables peephole optimization for every later function in the same translation unit** on GC/1.2.5n. Usual symptoms are lost displacement folding, lost record-form compares, and early returns turning into branches to the shared epilogue.

  The fix is adding `#pragma peephole on` immediately after the asm function closes. `#pragma scheduling on` is not needed. This matters in any unit that mixes an early asm function with later plain C, since address order often forces the asm function to appear first.

- **CodeWarrior treats an undeclared data symbol in `asm` as a local label:** declaring the existing external object before the asm function is required for `@ha`/`@l` relocations to compile.

- **Hardware-register arrays must use CodeWarrior's declare-at-address form, not a pointer-cast macro:**

  ```c
  volatile u32 __SIRegs[0x100] : 0xCC006400;      /* correct */
  #define __SIRegs ((volatile u32*)0xCC006400)    /* compiles, does NOT match */
  ```

  The macro form folds the index into the base register (`mulli`/`addis`/`stw`) instead of the original separate-index `stwx` form. Reference decomps often carry the `#define` behind an `#ifdef __MWERKS__ ... #else`; that fallback is unwanted.

- **Operand order matters on carry ops:** `ticks + *timeAdjustAddr` compiled to `addc r30,r30,r4` and matched; `*timeAdjustAddr + ticks` produced `addc r30,r4,r30` and also matched. When a function is one instruction off, try reversing the expression first.

- **A `static` helper called from two sites gets inlined unless told otherwise:** if the original keeps the `bl` (function 0% match, prologue lacks `mflr`), wrap the helper in `#pragma dont_inline on` / `#pragma dont_inline reset`. This took `__GXSetSUTexRegs` from 0% to 100%.

- **Register allocation stuck (wrong regs, `li` order) in a tiny GX setter: try the narrower param type.** `u32` vs `u8` for a `GXBool`-style parameter changed the allocation from 77% to 100% in `GXSetDither`, `GXSetColorUpdate` and `GXSetAlphaUpdate`.

- **A full-width `SET_REG_FIELD` (8-bit field at shift 0) loses the original's `clrrwi`, and a `u8` param adds a `clrlwi`:** use a `u32` param and write `__rlwimi((int)(reg & 0xFFFFFF00), (int)vol, 0, 24, 31)` explicitly. Matched `AISetStreamVolLeft` (68% -> 100%).

- **A `clrlwi rX,r3,24` right after a `bl` that the original lacks means the callee's return type is too narrow:** declare the extern as returning `u32` (locals too), even if the real function returns `u8`. Matched `AISetStreamPlayState` (92% -> 100%, alongside `(reg & ~1) | state` and `(reg & ~0x20) | 0x20` in plain C where the original has `clrrwi`/`rlwinm` + `ori` instead of `rlwimi`).

- **Original has `stwu` before `mr r4,r3` (arg copy after frame setup) in a tiny wrapper: add `#pragma peephole off`** before the function. Default codegen emits the copy first (63%); `#pragma scheduling off` alone gets 76-82% and misorders `li`/`crclr`. Peephole off alone is 100% (`OSRegisterVersion`, `0x8017B3C0`).

- **Original has `clrlwi` separate from a following `slwi` (indexing a table by a `u8` param), where ours emits a merged `clrlslwi`: add `#pragma peephole off`** at the top of the unit. Took `__OSSetExceptionHandler`/`__OSGetExceptionHandler` (`0x8017B234`/`0x8017B250`) from 66-75% to 100%.

- **Align-up arithmetic gets reassociated (`add size, a` first) when written with plain `unsigned long` temps:** use the SDK's shape instead: a `ROUNDUP(x, a)` macro `(((unsigned long)(x) + (a)-1) & ~((a)-1))`, with `unsigned char*` locals for the pointer add (`(u8*)ptr + size`). Took `OSAllocFromArenaLo` (`0x8017BBE4`) from 98% to 100%.

- **Loop tail emits `bne top; b exit` where ours emits `beq exit; b top`:** write the back-edge as `if (x != 0) { continue; } break;` instead of `if (x == 0) { break; }`. Took `OSCancelThread`'s inlined `UpdatePriority` loop from 99.86% to 100%.

- **Inlined `__OSGetEffectivePriority` loop gets the wrong registers (priority in r4, blocked thread in r5) and the frame comes out 8 bytes too big:** write it as a `static inline` helper, read the blocked thread's priority once into a local inside `if (b) { long bp = b->priority; if (bp < priority) priority = bp; }`, and assign straight to `thread->priority = EffPrio(thread)` with no function-scope temps. Took `OSResumeThread` (`0x80180804`) from 99% to 100%.

- **Inlining:** A function may contain the inlined body of a method from a not-yet-reconstructed header. A `static` helper with a single caller can be inlined with no separate `bl`, which is why an original may have no call where a reference decomp appears to have one.

- **Redundant `b <next instruction>` no-op branches appear at loop/branch join points, sometimes doubled:** Translate literally rather than collapsing them.

- **C++ class layout must be exact:** One wrong member offset breaks matching in that class, and vtable order must match the original virtual declaration order.

---

## Data, symbols, and relocations

- **Fresh anonymous data doesn't reliably land at the original's address:**

  A plain-C `static` local or a fresh string literal can report 100% fuzzy, but the linker places it wherever, so the address computation bakes in the wrong small-data offset and `main.dol` breaks by a byte or two.

  The fix is to reference dtk's auto-detected symbol instead. dtk sometimes names these with a compiler-internal disambiguator such as `cmdTypeAndStatus$371`. `$` is not valid in this compiler, so rename it to a plain identifier in `symbols.txt` with `scope:global`, leave the range unclaimed in `splits.txt`, and use a plain `extern`.

- **Prefer referencing an unclaimed symbol over claiming its range:**

  Claiming even a 4-byte `.sbss` range can repack every other unclaimed symbol in that section.

  The same applies to `.data` statics with cross-object callers. Claiming a range to define `Si` as a true `static` broke the link with `undefined: 'Si_804D1BBC'` from six still-unclaimed functions. Override `scope:local` to `scope:global` in `symbols.txt` and use a plain `extern` instead. Hand-set attributes persist across regeneration.

- **`addi` does not accept the bare-symbol sda21 trick:** "Bare symbol name, no base register" only works for instructions with a real `d(rA)` operand such as `lwz` or `lfd`. For address computations, use `la rD, symbol` and give the symbol a sized declaration such as `extern char lbl_8066C408[8];` rather than `[]`; the size is what fixes the relocation type.

  Getting it wrong produces the wrong relocation, visible via `tools/objdiff_mismatches.py`, not a byte diff.

- **Before hardcoding an address as a raw immediate because the target "isn't split yet", rebuild once and grep `symbols.txt`:** dtk's auto-namer may already have named it. Hardcoded `lis`/`addi` immediates stall around 99% because the original carries real `R_PPC_ADDR16_HA`/`_LO` relocations; switching to `symbol@ha`/`@l` matches immediately.

- **The auto-namer may only tag part of a merged data blob:**
  For example, it may name the first 0x30 bytes of a 0x98-byte blob and leave the rest as a separate `lbl_`. Auto-names also often come back as `scope:local`, and they may need a manual override to `scope:global` before your object can reference them.

- **A switch statement's compiler-generated jump table is a lone anonymous `.data` object, and MWCC always declares that section with 8-byte alignment, even though the table entries only need 4:** if the function is isolated into its own translation unit, claiming the original `.data` range in `splits.txt` still lands it 4 bytes late whenever the original address is only 4-mod-8 (true when the table wasn't the first `.data` item in the real, larger source file). `main.dol` breaks with thousands of tiny scattered diffs (everything after shifts) even though the function's own fuzzy match reports 100%. No fix found short of reconstructing the original file's other `.data` members first; treat as a blocker and pick a different target instead (confirmed on `VIGetTvFormat`, `0x8018992C`).

- **`.sdata2` symbols in compiled C are fine:** the `sda2_via_r13` option bakes those accesses as `r13` offsets (see [`baseline.md`](baseline.md#small-data-r13-problem)), so write them as ordinary C.<br />
  If `Range Error for small data relocation` appears, check that `build.ninja` was generated with the fork's `dtk-dev` and that `build/GVLE69/sda_bake.json` exists.

---

## General tactics

- Comments and whitespace do not affect output, except for `__LINE__`/`__FILE__` and whitespace inside string literals.
- Register allocation differences usually indicate a different expression shape or variable lifetime. Try reordering locals or introducing/removing a temporary.
- Instruction scheduling differences often come from the compiler hoisting a constant. Match the source structure rather than the instruction order directly.
- If you're stuck around 95% on register choice, [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) can brute-force equivalent C forms.

---

## Confirmed non-matches

Don't re-guess these.

- `fn_80171F8C` LCG-shaped PRNG updater. Same `0x41C64E6D`/`+12345` constants as MSL's `rand()`, but a different final step (`& 0x7FFFFFFF` on a shared struct field).
- No ac-decomp source exists for:
  - `div`/`memchr` (already named from instruction shape)
  - the `__ashldi3`/`__ashrdi3`/`__lshrdi3`/`fn_80179138` (`__divdi3`-shaped)/`fn_801796FC` (`__moddi3`-shaped) cluster
  - the buffered-stdio cluster (`fn_80177CF8`/`D24`/`E04`/`E24`/`ungetc`)
  - the ioctl-wrapper family (`fn_80178D48` and siblings)
  - the small `Dolphin/os` one-offs `fn_8017A620`, `fn_8017A70C`, `fn_8017A6CC`, `fn_8017B444`, `fn_8017FB84`, `fn_8017FD64`, `fn_8017FD74`
- `GXLoadTexObjPreLoaded` (`0x8018E3A0`): body matches (98.25%, only `@sda21` symbol-name diffs), but the stack frame is `-0x28` vs `-0x40`. No effect: aliasing locals, adding/removing register writes, own TU, `#pragma scheduling on`. Hoisting the `GXTex*Ids[id]` reads makes it worse. Unused `volatile u32` locals close the 24-byte gap exactly, but that's padding, not a reconstruction, so it stays `NonMatching`.
- `__SetSURegs` (`0x8018E80C`, `Dolphin/gx/GXSetSUTexRegs.c`): `NonMatching`. Best clean-ish C is 38/40 instructions identical:
  - The single shared `gx + tcoord*4` `add` needs a second alias of the local `g = __GXData` pointer, with the two 16-bit `__rlwimi` inserts *reading* through the alias and writing through `g`.
  - It also needs the artificial `suTs1[w = tcoord]` in the last FIFO write; without it, codegen falls back to 48 diff lines.
  - Remaining: the original allocates the `s_bias` temp to r10 (ours r12) and schedules `li r5,0x61` before the first `clrlwi`. Ours leaves r10/r11 unused, so the `w = tcoord` hack is standing in for some real extra value.
  - No effect: local order, `u8`/`u32`/`int` bias, int casts, which pointer the bias/`tMode0`/`tImage0` reads use, `extern ... * const __GXData`, declare-at-address `GXWGFifo`. Plain-C `SET_REG_FIELD` is much worse.
  - decomp-permuter plateaued at score 35 after ~300k iterations.
- `GXSetTevColorOp` (`0x8018F3B0`, `Dolphin/gx/GXSetTevColorOp.c`): `NonMatching`, about 80%. Only tail scheduling differs.
  - `op` must be `int` (`cmpwi`). The original reloads `__GXData` once before the FIFO writes and uses it for both the `tevc[stage]` store and `bpSentNot`.
  - Remaining: the original defers the clamp/out_reg `rlwimi`s until after the `stb`; ours hoists one above it. No effect: moving the `u8` write, a `z = 0` local. A long-lived `gx` local gives 90% but shifts registers.
- `GXSetTevAlphaOp` (`0x8018F418`, `Dolphin/gx/GXSetTevAlphaOp.c`): `NonMatching`, 80.38%. Identical shape and identical tail-scheduling diff to `GXSetTevColorOp` (uses `teva`); solving one should solve both.
- `GXSetTevColor` (`0x8018F480`, `Dolphin/gx/GXSetTevColor.c`): `NonMatching`, about 44%. The color is one `lwz` word with 8-bit `rlwimi` fields (`c >> 24`, `c`, `c >> 8`, `c >> 16`), and the `224/225 + id*2` field is a plain `<< 24` init.
  - Remaining: the original schedules `slwi id*2` before the color `lwz` and has no `addi rX,rY,0` accumulator copies. No effect: local order, `id2` temp, operand order, `u32*` param.
- `GXSetTevKColor` (`0x8018F4E0`): `NonMatching`, 85.8%. Same scheduling stall as `GXSetTevColor`. Worse: ac-decomp's `reg = 0` + last `<< 24` insert (42%), an `id2` temp (68%).
- `GXSetTevKColorSel` / `GXSetTevKAlphaSel` (`0x8018F544` / `0x8018F5A0`): `NonMatching`, 92.6% each. Only register allocation differs (original: `Kreg` in r7, `__GXData` reloaded into r3 before the FIFO writes). Reading `__GXData->` directly is worse (88%).
- `GXSetZTexture` (`0x8018F708`, `Dolphin/gx/GXSetZTexture.c`): `NonMatching`, about 31%. Shape is right (read `__GXData` directly after the switch, no local). Remaining: the `addi rX,rY,0` accumulator copy (as in `GXSetTevColor`) and an early `li r0,0xf4`. No effect: `zenv1 = 0` placement, open-coded `__rlwimi`, `zenv0 += 0`.
- `GXSetProjection` (`0x8018FF90`, `Dolphin/gx/GXTransform.c`): `NonMatching`, 93.66%. Uses the SDK's inline `asm` `WriteProjPS` (`psq_l`/`psq_st`), `int type`, and a second `__GXData` local reloaded after the branch.
  - Remaining: the original emits `lis r5,0xcc01` before the reload `lwz`; ours loads first, so registers rotate. No effect: a `fifo` pointer local, moving the reload after the `u8` write, all-`__GXData->` access.
- `__GXSetViewport` (`0x80190248`, `Dolphin/gx/GXSetViewport.c`): `NonMatching`, about 82.9%. Its caller `GXSetViewport` (`0x801902D8`) is 100%. The game's `__GXData` layout differs from ac-decomp: viewport floats sit at `0x4F4`–`0x508`, then `zOffset` (`0x50C`) and `zScale` (`0x510`), with no jitter/field logic. Needs `#pragma fp_contract off` (otherwise `fmadds`/`fnmsubs` appear) and `extern const f32` for `lbl_80670778` (0.5) / `lbl_8067077C` (342.0) instead of literals.
  - Remaining: FP scheduling and register allocation (the original loads 342.0 late into a reused `f6`). Brute-forced all 120 orderings of the `sy`/`ox`/`oy`/`zmin`/`zmax` statements (best 82.9%); no effect from `zmin`/`zmax` locals vs inline.
- `GXSetScissorBoxOffset` (`0x80190398`, `Dolphin/gx/GXSetScissorBoxOffset.c`): `NonMatching`, 90%. The original folds `>> 1` into the `rlwimi` (`rlwimi r4,r5,31,22,31`), which only happens when the shift is written inside the `SET_REG_FIELD` value for `x` (`hx >> 1`) and pre-shifted for `y`; `>> 1` on both, or ac-decomp's `hx`/`hy` locals, leaves a `srwi`.
  - Remaining: the original has an `addi r5,r4,0` accumulator copy (as in `GXSetTevColor`) and puts `x+342` in r5, `__GXData` in r3. No effect: gx local placement, plain-C masks (52%).
- `AIInit` (`Dolphin/ai/AIInit.c`): `NonMatching`, 94.78%. The original keeps `ori r0,r0,0` nops where the `vol = 0` inserts fold away (ours emits `rlwimi` or drops them), copies `stack` to r30 (ours r31), and stores the u64 low words via separate `lbl_8066F424`-style symbols (ours reloc as `+4`). Hi/lo `u32` externs fix the relocs but drop to 17%.
- `GXClearVtxDesc` (`0x8018C820`, `Dolphin/gx/GXClearVtxDesc.c`): `NonMatching`, 97.14%. Instruction sequence is identical; only registers differ (original: `gx` r4, zero r5, `rlwimi` temp r3; ours: zero r3, temp r5). A single `gx` local read once is required. Plain `SET_REG_FIELD(gx->vcdLo, ...)` gives 87-95% with `gx`/zero swapped; the `u32 vcdLo` temp (read back, insert, write) gives 97%. No effect: `zero` locals, `vcdHi` as the zero source, reloading `gx`.
- `GXSetCullMode` (`0x8018D660`, `Dolphin/gx/GXSetCullMode.c`): `NonMatching`, 97%. This game's version is a branchless front/back bit swap (`extrwi` + `rlwimi`), not ac-decomp's `switch`; only `__rlwimi((mode >> 1) & 1, mode, 1, 30, 30)` produces it (plain-C shifts/masks give `clrlslwi`+`mr`, 83-93%). Remaining: the original keeps the swap temp in r5 with `genMode` in r0 and `gx` in r4; ours puts the temp in r0 and `genMode` in r3 (reusing the dead param). Initializing `gx` first without a `hwMode` local gets `gx` right (97%); a `hwMode` local, `reg` temp, direct `__GXData->`, and `int` param give 88-96%.
- `__GXSetMatrixIndex` (`0x80190400`, `Dolphin/gx/__GXSetMatrixIndex.c`): `NonMatching`, 87.5%. Structure is right: `matIdxA`/`matIdxB` FIFO writes, then a `u16` `bpSentNot = 1` through a reloaded `__GXData`. The value must be read once into a local.
  - Remaining: the original schedules `lwz gx` after `li r0,8` and `lwz r4,0x80(r4)` after `li r3,0x10` (gx and the value share r4); ours hoists `lwz gx` above `li 8` and puts the value in r6. No effect: `gx` declared at function scope, at branch top, between the two `u8` writes, or per-branch local.
- `GXSetDispCopySrc` (`0x80192890`, `Dolphin/gx/GXSetDispCopySrc.c`): `NonMatching`, 98.39%. Instruction sequence is identical to ac-decomp's; only registers differ (original: zero r9, `wd` in r7, `ht` in r5; ours: zero r7). Best is a `u32 h = ht` local declared before `gx`. No effect: `w` temp, `wd - 1` temps, `u32` params, zero local, direct `__GXData->`. `GXSetTexCopySrc` (`0x8019290C`) has the same shape and should share the fix.
- `GXSetTexCopyDst` (`0x801929BC`, `Dolphin/gx/GXSetTexCopyDst.c`): `NonMatching`, 92.55%. Needs `fmt` as `int`, `u16` width/height on the `fn_8018DDCC` (`__GetImageTileCount`) prototype, a direct `__rlwimi(cpTex, peTexFmt, 0, 28, 28)`, a `u8 mipmap` param, and a `gx` local reloaded after the call.
  - Remaining: the original copies `wd` to r8 and `ht` to r7 (ours reversed) and reuses the `gx` register for the next `cpTex` insert. No effect: `u32`/`int` `wd`/`ht`, `w`/`h` locals, `gx` at function top.
- `GXSetCopyClamp` (`0x80192B10`, `Dolphin/gx/GXSetCopyClamp.c`): `NonMatching`, 96.36%. Instruction sequence is identical to ac-decomp's (`clmpT`/`clmpB` as `u8` locals, four 1-bit `SET_REG_FIELD`s).
- `GXSetTexCopySrc` (`0x8019290C`, `Dolphin/gx/GXSetTexCopySrc.c`): `NonMatching`, 98.39%. Same shape and same register-only diff as `GXSetDispCopySrc` (original: zero r9, `wd` r7, `ht` r5; ours: zero r7, `wd` r5, `ht` r9), offsets `0x1F0`/`0x1F4`. The `u32 h = ht` local is still the best. No effect: an added `u32 w = wd` local (97.6%, before or after `gx`), pre-subtracted `w`/`h` temps (90.6%). Solving one should solve both.
- `GXCopyTex` (`0x80193268`, `Dolphin/gx/GXCopyTex.c`): `NonMatching`, 89.8%. Same shape as `GXCopyDisp` plus a `cpTexZ` (`u8` at `0x200`) check that forces `peCtrl` to mode 3. Read `peCtrl`/`cpTexZ` via `__GXData->`, load a `gx` local once after the first `stb 0x61`, and reload `__GXData->` for the final `peCtrl` write and `bpSentNot`.
  - Remaining: the original has gx r7 / fifo r8 / `0x61` r9 and schedules `li r9,0x61`, `lwz gx` before `clrlwi.`; ours has r9/r7/r8 and hoists `lwz gx` and `li r10,0`. No effect: `gx` load before the `stb`, all-direct `__GXData->` (82.6%), early `gx` for `peCtrl` (88.6%).
- `GXClearBoundingBox` (`0x801933F4`, `Dolphin/gx/GXClearBoundingBox.c`): `NonMatching`. Same instructions as ac-decomp's `u32 reg` form; only scheduling differs (original: `li 0x61`, `lwz gx` r3, then fifo `lis` r5; ours reads `gx` last). No effect: `gx` local (top or mid-function), no `reg` local, `#pragma peephole/scheduling off`.
- `OSCreateThread` (`0x8018037C`, `Dolphin/os/OSCreateThread.c`): `NonMatching`, 99.51%. An unused `u64 fill = -1` local closes the 8-byte frame gap (padding, not reconstruction). Remaining: the original passes `&thread->context` as `addi r3,r31,0`; ours is `mr r3,r31`. No effect: casts, `+ 0`, a `ctx` local, call order, `#pragma peephole off` (87%), chained `fpr`/`psf` store (73%).
