# baseline.md

Or, "why the build is configured the way it is". A collection of reference notes for the non-obvious parts of this project's build setup.

See also:
- Decomp workflow: [`workflow.md`](workflow.md)
- Compiler gotchas [`matching_notes.md`](matching_notes.md)

## Binary Info

- **Single DOL:** No `.rel` modules, so no per-module config.
- **No debug symbols, no map file:** The disc ships a `GameGC.elf`, but it is stripped (no `.symtab`, no `.debug*`) and does not hash-match `main.dol`. Every symbol name and struct layout is reconstructed by hand (via dtk analyzer and Ghidra).
  Its `.text` and its constructor lists are byte-identical to `main.dol`'s, though, so its section headers show the original link's layout: `.init`, `.text`, `.ctors`, `.dtors`, `.rodata`, `.data`, `.bss`, `.sdata`, `.sbss`, `.sdata2`. `splits.txt` uses those names.
- **Two compilers:** The Dolphin SDK is Nintendo's prebuilt MWCC output. Everything else (the game's C++, Newlib/libgcc, the VM library and SN's debug stub) was built with SN Systems ProDG, a GCC 2.95 build, and linked by SN's linker. The project compiles SDK units with MWCC and the rest with ProDG, and links everything with mwld. See [`prodg.md`](prodg.md).

## Memory Map

Library code sits in two clusters inside `.text`, with game code on either side. All library code and data is split and matched, so every remaining `auto_` unit is game code or game data.

| `.text` range | Contents |
|---|---|
| `.init` 0x80003100-0x800034A0 | SN's crt0 (`__start`) and its helpers |
| 0x800034A0-0x80168768 | Game |
| 0x80168770-0x80196884 | Library: SN debug stub, compiler runtime, Newlib libc/libm, OS, SI, DB, DVD, VI, PAD, AI, GX, EXI, odenotstub, OdemuExi2 |
| 0x80196884-0x803FF3B0 | Game. About half of these functions have no frame pointer, so some files were built with other flags (see [`prodg.md`](prodg.md#flags)) |
| 0x803FF3B0-0x804114EC | Library: Newlib libm/libc, VM, `__save_gpr`/`__restore_gpr`, OS, MTX, AR, ARQ, AX, DSP, CARD, GX display lists, texPalette |
| 0x804114EC-0x804825A0 | Game |

In `configure.py`, the Dolphin SDK is the `DolphinLib` entries, Newlib/libgcc and the compiler runtime are `Runtime.PPCEABI.H`, the debug stub is `SN`, and game code is `Game`. Most of `Runtime.PPCEABI.H`, `SN` and the VM library is `nofralloc` asm transcribed from the GCC output, not C.

## Toolkit Fork Reasoning

Stock decomp-toolkit can't produce a matching build. These fixes are required, all in [`Esoteric-Engineer/mnroi-decomp-toolkit`](https://github.com/Esoteric-Engineer/mnroi-decomp-toolkit):

1. **OOM on split:** A relocation target outside all sections drove an allocation large enough to abort. Root cause was a crt0 address left sectionless.
2. **Duplicate section names:** dtk named two read-only regions `.rodata`, which CodeWarrior rejected, so the fork suffixes duplicate names (`.rodata.1`). With fix 4 this DOL no longer has duplicates.
3. **Small-data base-register conflict:** See below.
4. **ProDG constructor lists:** SN's tools store `.ctors` and `.dtors` in one DOL section, each list starting with `-1`, which stock dtk doesn't recognise. The fork splits that section into `.ctors` and `.dtors` when it reads the DOL, keeps the `-1` entries first in link order, and merges the two back into one section in `elf2dol`. See [`prodg.md`](prodg.md#constructor-and-destructor-lists).

## Small-data (`r13`) Problem

This game addresses all small data through `r13` (`_SDA_BASE_ = 0x806734E0`): 13,359 accesses in `.text`, and none through `r2`. The entire 21 KB small-data span fits within one ~32 KB `r13` window. `_SDA2_BASE_` is loaded by crt0 but addresses nothing.

dtk names the read-only small-data segment `.sdata2`, so mwld emits it as `r2`-relative: mwld chooses the base register from the section name, not the address range. That breaks every access the original makes to it through `r13`.

The usual linker fixes don't work: mwld emits only one `r13` small-data pair, and merging the segments changes the DOL layout.

The fork's `sda2_via_r13` option (enabled in `config.yml`) carries those accesses through the link as `r13`-based `@l` relocations (`R_PPC_ADDR16_LO`), which `mwld` resolves without a range check, and resolves them into `r13` displacements after the link:

- **Split objects:** `bake_conflicting_sda_relocations` turns each `EMB_SDA21` relocation from an `r13` instruction to `.sdata2`/`.sbss2` into an `ADDR16_LO` on the same target, keeping the `r13`. It also writes `build/GVLE69/sda_bake.json`, the `.sdata2`/`.sbss2` symbol names.
- **Compiled objects:** `tools/project.py` runs `dtk elf bake-sda` on each one before linking, which does the same to every `EMB_SDA21` relocation whose target is in `.sdata2`/`.sbss2`, or is undefined and named in that file. Without it, C referencing a `.sdata2` symbol (e.g. `__GXData`) fails with `Range Error for small data relocation`.
- **Linked ELF:** the link step then runs `dtk elf resolve-sda` on `main.elf`. Each `ADDR16_LO` on an `r13`-based load, store or `addi` that targets `.sdata2`/`.sbss2` gets the displacement `symbol + addend - _SDA_BASE_` from the final layout and becomes an `EMB_SDA21` relocation again. Nothing else uses that combination, since `r13` is reserved.

Because every access is resolved from the final layout, `.sdata2` constants keep working when sections change size. `_SDA2_BASE_` is pinned in [`../config/GVLE69/ldscript.lcf`](../config/GVLE69/ldscript.lcf) so crt0 matches (mwld's warning that the linker script redefines it is expected); nothing addresses data through `r2`. Because the fix is in the tool rather than the finished DOL, the *objects* stay correct and `objdiff` remains trustworthy.

A compiled object can only reach an `.sdata2` object through a symbol some object defines: an `extern` of a name that only exists in `symbols.txt` (e.g. another unit's anonymous literal) fails to link as `undefined`. Give the owning unit a real definition of it (see `C_MTXOrtho.c`), or address it from a defined symbol in the same object (`GXTexObjMinLodScaleConst-32` in `GXTexture.c`).

## Shifted Builds

A mod that changes a function's size moves every address after it, so the whole DOL has to relink correctly at new addresses. This was tested on 2026-10-02 by padding the start of `.text` (in `Game/fn_800092CC.cpp`) and the start of various `.rodata`/`.data` units, then diffing the shifted DOL against the original and booting it in Dolphin through a scripted versus match.

**What relinks correctly:** every pointer in `.data`/`.rodata`, all 171 constructors, crt0's section bounds, and the arena (which follows `.sdata2`). Video, input, menus, character loading and gameplay match the original.

**Fixed for this:**

- `fn_800350F4` (7 KB, reached only through a pointer) was in `skip_cfa_ranges`, because its inline FP epilogue looks like the `_restfpr_14` sled. dtk analyses nothing in a skipped range, so its 77 data references and 213 branches stayed raw numbers. It is now a function in `symbols.txt` that ends where the sled starts; dtk still names the sled `__restore_fpr`, and the function falls through into it as in the original.
- 17 `lis` instructions whose low half sits after a branch join, or whose high half is kept in a saved register or CTR, had no relocation. They now have `add_relocations` entries.
- dtk relocated six words of pixel data in the embedded `SHPG` texture bank `lbl_804BFA80` that only look like pointers. They now have `block_relocations` entries.

**Not fixed:**

- **Audio screeches in some shifted builds**: the DSP output saturates (RMS ~32,700 against ~1,000-2,000) from boot. It happens only when the code moves by an amount that is not a multiple of 0x200 **and** some data after `0x8049C1D0` (`.rodata` from the Newlib constants onward, or `.data`) moves by exactly the same amount. Any shift that is a multiple of 0x200, or one that changes the distance between code and that data, plays correctly. It reproduces with the cached interpreter and with DSP LLE, so it is the game's behaviour rather than Dolphin's JIT or DSP HLE. The cause is not found yet. Until it is, keep each change's size growth a multiple of 0x200 bytes (pad the end of the changed unit's `.text`).

## `config.yml` Reference

- **`skip_cfa_ranges`:** Hand-written Nintendo SDK supervisor-mode assembly that dtk's control-flow analysis cannot trace through (`bl .+4`, `rfi`, tail `b`).
    Located by scanning `.text` for `rfi`/`sc`/`mfmsr`/`mtmsr`/`tlbie`/`mtsr`. Bounds are approximate, refine as needed.
- **`force_active`:** Keeps functions that mwld's `-code_merging` would otherwise fold away as duplicates, which shifts every address after them.
    Add to this list only when a new match actually breaks `main.dol` (doesn't happen often).
    It also keeps `__DTOR_LIST__`, `_ctors` and `_dtors` alive for the constructor lists (see [`prodg.md`](prodg.md#constructor-and-destructor-lists)).
- **`block_relocations` / `add_relocations` at `.init:0x80003160`:** crt0 loads the absolute address `0x8066FB50` through a `lis`/`ori` pair that dtk split across two symbols, binding the low half to the wrong target. That address falls in the padding gap between `.sbss` and `.sdata2`, so dtk left it sectionless.
    Retargeted to the `ABS` symbol `lbl_8066FB50`, which `ldscript.lcf` defines as `ADDR(.sbss) + SIZEOF(.sbss)`, so the clear follows `.sbss` if it changes size.
- **`fill_gaps`:** Left at its default `true`. Required, or the DOL is short by ~29 KB and every subsequent offset shifts.
- **`mw_comment_version: 11`:** A guess (CW 2.7+). Revisit if the real compiler version is ever pinned down.
