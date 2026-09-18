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

- **`addi` does not accept the bare-symbol sda21 trick.** "Bare symbol name, no base register" only works for instructions with a real `d(rA)` operand such as `lwz` or `lfd`. For address computations, use `la rD, symbol` and give the symbol a sized declaration such as `extern char lbl_8066C408[8];` rather than `[]`; the size is what fixes the relocation type.

  Getting it wrong produces the wrong relocation, visible via `tools/objdiff_mismatches.py`, not a byte diff.

- **Before hardcoding an address as a raw immediate because the target "isn't split yet", rebuild once and grep `symbols.txt`:** dtk's auto-namer may already have named it. Hardcoded `lis`/`addi` immediates stall around 99% because the original carries real `R_PPC_ADDR16_HA`/`_LO` relocations; switching to `symbol@ha`/`@l` matches immediately.

- **The auto-namer may only tag part of a merged data blob:**
  For example, it may name the first 0x30 bytes of a 0x98-byte blob and leave the rest as a separate `lbl_`. Auto-names also often come back as `scope:local`, and they may need a manual override to `scope:global` before your object can reference them.

- **`_SDA2_BASE_` / `r2` is vestigial:** All small data goes through `r13` (see [`baseline.md`](baseline.md)). The toolkit fork handles this for extracted and `NonMatching` code, but not for new code flipped to `Matching`.

  If a C file references a symbol dtk labels `.sdata2` (for example `__GXData` at `0x80670788`), `mwld` routes it through `r2`. Because this game's `.sdata2` symbols are often outside `r2`'s ~32 KB window, the link fails with `Range Error for small data relocation`. This currently blocks `GXSetTexRegionCallback` / `GXSetTlutRegionCallback` (`0x8018E7E4`, `0x8018E7F8`) until the fork patches this relocation class post-link, or the data range is reclassified as `.sdata`.

  Not every reference to `__GXData` hits this: `GXLoadTexObjPreLoaded` (`0x8018E3A0`) reads/writes through it (`gx->tlutRegionCallback(...)`, `gx->tImage0[id]`, etc.) and links fine via `r13`, matching the original's own `-11608(r13)` access. The `r2` routing only seems to bite the two `Set*Callback` setters above, and `GXLoadTlut` (`0x8018E5D8`, `Dolphin/gx/GXLoadTlut.c`): the body is byte-identical (98.42% fuzzy, only the `@sda21` symbol name differs), but flipping it to `Matching` fails with the same `Range Error for small data relocation`. Left `NonMatching` until the fork fixes this.

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
- `GXLoadTexObjPreLoaded` (`0x8018E3A0`, `Dolphin/gx/GXLoadTexObjPreLoaded.c`): body matches byte-for-byte (98.25% fuzzy → the only real diffs are cosmetic symbol-name text on `@sda21` relocations), but the prologue/epilogue frame size is stuck at `-0x28(r1)` vs the original's `-0x40(r1)` (24 bytes short). Tried: reordering/aliasing locals (`t`/`r`/`gx` pointer copies — no effect, fully optimized away), removing/adding `SET_REG_FIELD`/`GX_WRITE_RAS_REG` calls (no effect), pre-computing the `GXTex*Ids[id]` table reads into named locals (changes instruction order, makes it worse), splitting into its own translation unit (no effect), `#pragma scheduling on` (no effect). Only forcing extra *unused* `volatile u32` locals reproduced the missing 24 bytes exactly, which confirms the original reserves stack for something we're not modeling, not a scheduling artifact — but that's not an honest reconstruction, so left `NonMatching`.
