# Matching Notes

Compiler/linker behavior and techniques learned while matching functions in this game. Helpful to review when a function is stuck short of 100%.

---

## Compiler gotchas

### GX setters: three source-shape levers

Scope: found on `Dolphin/gx` (`GC/1.2.5n`); untested on game code. For a GX setter whose instruction sequence is identical but registers/scheduling differ, sweep `{macro, declare-at-address} x {plain, const} x {gx local, direct}` before anything else (25 units matched this way).

- **`extern __GXDataStruct* const __GXData;`** Without `const`, a late extra `lwz rX,-11608(r13)` appears or `gx` lands a register too high (likely because MWCC assumes stores may alias the pointer). Highest yield.
- **Direct `__GXData->field` over a `gx` local**, once `const` is in. Keep a local only where the original really reloads (`GXCopyDisp`/`GXCopyTex` use both).
- **`volatile GXFifoObj GXWGFifo : 0xCC008000;`** instead of the cast macro. It changes scheduling, not just addressing, and is per-function (`GXSetTevOrder` and `GXSetViewport` prefer the macro).

Smaller findings:

- **`u32 c = *(u32*)&color;`** for a by-value `GXColor`: 68% -> 100% on `GXSetTevKColor`.
- **`phyAddr = (u32)dest & 0x3FFFFFFF;` temp** in `GXCopyDisp`/`GXCopyTex`. The mask emits nothing, but inlining `(u32)dest >> 5` drops `GXCopyDisp` from 100% to 47%.
- **`u8` for `GXBool` params** even when only forwarded: `GXSetCoPlanar` 7% -> 100%.
- **Named local for a compound `__rlwimi`** (`GXSetCullMode` `hwMode`), else it lands in `r0`.
- **`fcmpu` operand order follows source order:** `(lbl_80670770 == ptr[0])` matched `GXSetProjectionv`.

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

- **Redundant `b <next instruction>` branches at every loop head (often two or three in a row), plus a separate `cmplwi`/`blt` where ours folds the compare: `#pragma peephole off`.** In a loop-heavy function this is worth far more than the symptom suggests. It took `GXInit` from 84.7% to 99.2% in one change, restoring ~18 instructions across six loops. The original's peephole-off state comes from an `asm` function earlier in the real translation unit; a `static asm` stub at the top of the file produces byte-identical output to the pragma, so prefer the pragma, which emits no extra function.

- **Align-up arithmetic gets reassociated (`add size, a` first) when written with plain `unsigned long` temps:** use the SDK's shape instead: a `ROUNDUP(x, a)` macro `(((unsigned long)(x) + (a)-1) & ~((a)-1))`, with `unsigned char*` locals for the pointer add (`(u8*)ptr + size`). Took `OSAllocFromArenaLo` (`0x8017BBE4`) from 98% to 100%.

- **Loop tail emits `bne top; b exit` where ours emits `beq exit; b top`:** write the back-edge as `if (x != 0) { continue; } break;` instead of `if (x == 0) { break; }`. Took `OSCancelThread`'s inlined `UpdatePriority` loop from 99.86% to 100%.

- **Inlined `__OSGetEffectivePriority` loop gets the wrong registers (priority in r4, blocked thread in r5) and the frame comes out 8 bytes too big:** write it as a `static inline` helper, read the blocked thread's priority once into a local inside `if (b) { long bp = b->priority; if (bp < priority) priority = bp; }`, and assign straight to `thread->priority = EffPrio(thread)` with no function-scope temps. Took `OSResumeThread` (`0x80180804`) from 99% to 100%.

- **A base address hoisted into a saved register once (`lis`/`addi r31,RunQueue`), with later `r31+offset` uses (`addi r3,r31,0x730`):** keep a local `OSThreadQueue* rq = RunQueue;` and derive every use from `rq`. Referencing the global directly re-emits `lis`/`addi` at each use (89%). If two uses share the same `(u8*)rq + off` expression they get CSE'd into an extra saved register; write the second as `rq + 230` (pointer arithmetic, same address) instead. Also inline `OSGetCurrentThread` as a `static inline` reading `__gCurrentThread : 0x800000E4` (declare-at-address) to get the original's extra `addi r3,rX,0` copy. Matched `SelectThread` (`0x801800E8`).

- **Inlining:** A function may contain the inlined body of a method from a not-yet-reconstructed header. A `static` helper with a single caller can be inlined with no separate `bl`, which is why an original may have no call where a reference decomp appears to have one.

- **Early `return 0;` compiles to a bare `blr` where the original branches to the shared exit (`b .L_end`) in a tiny pointer-returning function: `#pragma peephole off`.** Restructuring into a single `r` result variable has no effect. Matched `__GXDefaultTlutRegionCallback` (`0x80190580`).

- **Redundant `b <next instruction>` no-op branches appear at loop/branch join points, sometimes doubled:** Translate literally rather than collapsing them.

- **C++ class layout must be exact:** One wrong member offset breaks matching in that class, and vtable order must match the original virtual declaration order.

---

## Data, symbols, and relocations

- **Fresh anonymous data doesn't reliably land at the original's address:**

  A plain-C `static` local or a fresh string literal can report 100% fuzzy, but the linker places it wherever, so the address computation bakes in the wrong small-data offset and `main.dol` breaks by a byte or two.

  The fix is to reference dtk's auto-detected symbol instead. dtk sometimes names these with a compiler-internal disambiguator such as `cmdTypeAndStatus$371`. `$` is not valid in this compiler, so rename it to a plain identifier in `symbols.txt` with `scope:global`, leave the range unclaimed in `splits.txt`, and use a plain `extern`.

- **dtk only preserves a hand-set symbol name if it doesn't look auto-generated:**

  Renaming a compiler literal (`@267 = .sdata2:0x8067078C`) to `lbl_8067078C` is silently reverted on the next build, because `lbl_*`/`fn_*` are dtk's own naming patterns and get regenerated. The rename also never reaches `build/GVLE69/sda_bake.json`, so your `extern` keeps an unbaked `R_PPC_EMB_SDA21` relocation where the original object has a plain `r13` offset. This is visible in `tools/objdiff_mismatches.py` as a `DIFF_REPLACE` on the `lfs`/`lwz`, not as a byte diff.

  Give it a real name instead (`GXInitZScaleConst`). That survives regeneration, lands in the bake list, and the relocation resolves. Same rule as the `cmdTypeAndStatus$371` case above.

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
- `GXLoadTexObjPreLoaded` (`0x8018E3A0`): body matches (99.88%, only `@sda21` symbol-name diffs), but the stack frame is `-0x28` vs `-0x40`. No effect: aliasing locals, adding/removing register writes, own TU, `#pragma scheduling on`. Hoisting the `GXTex*Ids[id]` reads makes it worse. Unused `volatile u32` locals close the 24-byte gap exactly, but that's padding, not a reconstruction, so it stays `NonMatching`.
- `__SetSURegs` (`0x8018E80C`, `Dolphin/gx/GXSetSUTexRegs.c`): `NonMatching`, 96.85%. Best clean-ish C is 38/40 instructions identical:
  - The single shared `gx + tcoord*4` `add` needs a second alias of the local `g = __GXData` pointer, with the two 16-bit `__rlwimi` inserts *reading* through the alias and writing through `g`.
  - It also needs the artificial `suTs1[w = tcoord]` in the last FIFO write; without it, codegen falls back to 48 diff lines.
  - Remaining: the original allocates the `s_bias` temp to r10 (ours r12) and schedules `li r5,0x61` before the first `clrlwi`. Ours leaves r10/r11 unused, so the `w = tcoord` hack is standing in for some real extra value.
  - No effect: local order, `u8`/`u32`/`int` bias, int casts, which pointer the bias/`tMode0`/`tImage0` reads use, `extern ... * const __GXData`, declare-at-address `GXWGFifo`. Plain-C `SET_REG_FIELD` is much worse.
  - decomp-permuter plateaued at score 35 after ~300k iterations.
- `GXSetTevColor` (`0x8018F480`, `Dolphin/gx/GXSetTevColor.c`): `NonMatching`, 55.83%. The color is one `lwz` word with 8-bit `rlwimi` fields, and the `224/225 + id*2` field is a plain `<< 24` init. The original interleaves the writes (one FIFO write for `regRA`, then `regBG` computed and written three times), which our source now mirrors.
  - Remaining: the original carries an `addi rX,rY,0` accumulator copy that our codegen folds away, so we come out one instruction short. No effect: a `u32 c = *(u32*)&color` local (which fixed the sibling `GXSetTevKColor`), local declaration order, `int id`, `reg = 0` + `<< 24` inserts, `* const __GXData`, declare-at-address `GXWGFifo`.
- `GXSetProjection` (`0x8018FF90`, `Dolphin/gx/GXTransform.c`): `NonMatching`, 97.37% at unit level; the unit's other function `GXSetProjectionv` is 100%. Uses the SDK's inline `asm` `WriteProjPS` (`psq_l`/`psq_st`), `int type`, and direct `__GXData->` access for the whole tail (a `gx2` local drops it to 71%).
  - Remaining: the original schedules `lwz r4,__GXData` immediately after `lis r5,0xcc01`, before the `li 0x10`/FIFO writes; ours emits it just before its first use, six instructions later, which rotates r4/r5/r6. No effect: a `mtxp` pointer local, a `projType` temp, reordering `bpSentNot` against the last FIFO write, assigning a `gx2` local after the `u8` write.
- `__GXSetViewport` (`0x80190248`, `Dolphin/gx/GXSetViewport.c`): `NonMatching`, 88.59%. Its caller `GXSetViewport` (`0x801902D8`) is 100%. The game's `__GXData` layout differs from ac-decomp: viewport floats sit at `0x4F4`-`0x508`, then `zOffset` (`0x50C`) and `zScale` (`0x510`), with no jitter/field logic. Needs `#pragma fp_contract off` (otherwise `fmadds`/`fnmsubs` appear) and `extern const f32` for `lbl_80670778` (0.5) / `lbl_8067077C` (342.0) instead of literals.
  - Remaining: FP scheduling and register allocation (the original loads 342.0 late into a reused `f6` and keeps everything inside f0-f9; ours spills into f10/f11). Brute-forced all 120 orderings of the `sy`/`ox`/`oy`/`zmin`/`zmax` statements; no effect from `zmin`/`zmax` locals vs inline.
- `GXSetScissorBoxOffset` (`0x80190398`, `Dolphin/gx/GXSetScissorBoxOffset.c`): `NonMatching`, 86.25%. Best form is declare-at-address `GXWGFifo`, direct `__GXData->bpSentNot`, and both shifts written inside the `SET_REG_FIELD` values (`(u32)(x_off + 342) >> 1`), which gets 13/16 instructions with only positions 3-5 differing.
  - Remaining: the original folds the first `>> 1` into the `rlwimi` (`rlwimi r4,r5,31,22,31`) *and* keeps an `addi r5,r4,0` accumulator copy; we can get one or the other, never both. `hx`/`hy` locals fold both shifts but drop the copy (1/16); no locals gives the copy but emits a separate `srwi` (13/16). No effect: `s32` locals, an intermediate `reg0`, declaration order, `* const __GXData`, a `gx` local.
- `AIInit` (`Dolphin/ai/AIInit.c`): `NonMatching`, 95.05%. The original keeps `ori r0,r0,0` nops where the `vol = 0` inserts fold away (ours emits `rlwimi` or drops them), copies `stack` to r30 (ours r31), and stores the u64 low words via separate `lbl_8066F424`-style symbols (ours reloc as `+4`). Hi/lo `u32` externs fix the relocs but drop to 17%.
- `GXSetTexCopyDst` (`0x801929BC`, `Dolphin/gx/GXSetTexCopyDst.c`): `NonMatching`, 94.41%. Needs `fmt` as `int`, `u16` width/height on the `fn_8018DDCC` (`__GetImageTileCount`) prototype, a direct `__rlwimi(cpTex, peTexFmt, 0, 28, 28)`, a `u8 mipmap` param, `extern ... * const __GXData` with direct access up to the call, and a `gx` local reloaded after it.
  - Remaining: the original emits the two argument copies as `addi r5,r7,0` then `addi r4,r8,0`, so `__GXData` can reuse the still-free r4; ours emits them in the opposite order and has to put `__GXData` in r6. No effect: `u32`/`int` `wd`/`ht`, `w`/`h` locals, a `g` local for the `cpTexZ`/`cpTex` block, moving `peTexFmt &= 7`, `#pragma scheduling off` (42%), `#pragma peephole off` (32%).
- `OSCreateThread` (`0x8018037C`, `Dolphin/os/OSCreateThread.c`): `NonMatching`, 99.51%. An unused `u64 fill = -1` local closes the 8-byte frame gap (padding, not reconstruction). Remaining: the original passes `&thread->context` as `addi r3,r31,0`; ours is `mr r3,r31`. No effect: casts, `+ 0`, a `ctx` local, call order, `#pragma peephole off` (87%), chained `fpr`/`psf` store (73%).
- `GXLoadLightObjImm` (`0x8018D8D4`, `Dolphin/gx/GXLoadLightObjImm.c`): `NonMatching`, 92.42%. This game's version takes `light` as a bitmask (`cntlzw`, `31 - n`, `& 7`, `<< 4`, `+ 0x600`), not ac-decomp's `GXLightID` switch. The zero/color/`psq_l`/`stw`/`psq_st` run only inlines via a `static inline` helper with an `asm {}` block (a `static asm` function stays a `bl`).
  - Remaining: the original keeps the `cntlzw` chain in r0, the fifo pointer in r4, and the first `stw` of the address is `stwu` (which also sets the pointer). Ours puts the chain in r4/r5 and emits a plain `stw` plus an `addi r5,r7,-0x8000`. Writing `*fifo = ...` through a `volatile u32*` local produces the `stwu` but shifts registers (92.4% either way). No effect: `idx` temp vs inline expression, `fifo` local ordering, `* const __GXData`, declare-at-address `GXWGFifo`.
- `__GXCleanGPFifo` (`0x80191F5C`, `Dolphin/gx/__GXCleanGPFifo.c`): `NonMatching`, 99.72%. Shape: `gpFifo = GXGetGPFifo(); if (!gpFifo) return;` (the null check comes *before* `GXGetCPUFifo()`, else 91%), `GXInitFifoPtrs` inlined twice (as `static inline` or hand-expanded, same result), 0x80-byte `GXFifoObj` struct copy. Remaining: the original frame is `-0xa8` with the dummy at `0x14(r1)`; ours is `-0x98` with it at `0x8(r1)`. Unused locals are dropped and don't help.
- `GXInit` (`0x801908D8`, `Dolphin/gx/GXInit.c`): `NonMatching`, 99.47%. Needs `#pragma peephole off`, `extern __GXDataStruct* const __GXData;` (without `const` the pointer is reloaded between every store in a straight-line block, 61%), `EnableWriteGatherPipe` as `static inline`, and a `GXFifoObj* fifoObj = &FifoObj;` local -- without the local the address is re-materialized at all four uses and the frame loses a saved register (96.4%).
  - Remaining: exactly one instruction. The original materializes the address straight into its saved register (`addi r31,r4,FifoObj@l`); ours routes it through r0 and adds `mr r30,r0`. That swaps r30/r31 for the rest of the function, which accounts for every other diff line.
  - No effect: initializer vs separate assignment statement, declaration order among the locals, `const`/`register`/`void*`/redundant cast on the local, `FifoObj` declared as `GXFifoObj[1]`/`u8[0x80]`/a file-local `static` definition, assigning the local at four different points in the body, mixing `&FifoObj` and the local across the call sites, and a real `static asm` function in place of the pragma. `#pragma scheduling off` is far worse (57%).
- `GXSetBlendMode` (`0x8018FC90`, `Dolphin/gx/GXSetBlendMode.c`): `NonMatching`, 90.0%. The blend-subtract and logic bits are written with the raw `cntlzw` result: `__rlwimi(reg, __cntlzw(3 - type), 6, 20, 20)` and `(..., __cntlzw(2 - type), 28, 30, 30)`. A `>> 5` or `== n` form emits a separate `srwi`/`srawi`, and the plain-C bit-0 field is a bare `rlwimi` of `type`.
  - Remaining: the original schedules `subfic r0,3; cntlzw r7,r0; subfic r0,2` (two temps, r7 kept live), ours uses `subfic r7,3; subfic r0,2; cntlzw r7,r7`. No effect: locals for the two `cntlzw` results, a `2 - type` temp, `u8`/`int` param types (`u8` is worse), `#pragma scheduling off` (71%) or `peephole off` (87%).
