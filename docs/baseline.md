# baseline.md

Or, "why the build is configured the way it is". A collection of reference notes for the non-obvious parts of this project's build setup.

See also:
- Decomp workflow: [`workflow.md`](workflow.md)
- Compiler gotchas [`matching_notes.md`](matching_notes.md)

## Binary Info

- **Single DOL:** No `.rel` modules, so no per-module config.
- **No debug symbols, no map file:** The disc ships a `GameGC.elf`, but it is stripped (no `.symtab`, no `.debug*`) and does not hash-match `main.dol`. Every symbol name and struct layout is reconstructed by hand (via dtk analyzer and Ghidra).
- **Game code is C++ at `-O4 -inline auto`:** Small functions were inlined away almost entirely; across all 17,161 functions only 2 leaf functions under 10 instructions exist in the game-code range.

## Toolkit Fork Reasoning

Stock decomp-toolkit can't produce a matching build. Three fixes are required, all in [`Esoteric-Engineer/mnroi-decomp-toolkit`](https://github.com/Esoteric-Engineer/mnroi-decomp-toolkit):

1. **OOM on split:** A relocation target outside all sections drove an allocation large enough to abort. Root cause was a crt0 address left sectionless.
2. **Duplicate `.rodata` sections:** This DOL is laid out as `.rodata → .data → .rodata`, with `.data` between two read-only regions.
  Original dtk named both regions `.rodata`, which CodeWarrior rejected. The fork suffixes duplicate names as `.rodata.1`. Consequently, a `WARN Unknown section .rodata.1` during splitting is expected.
3. **Small-data base-register conflict:** See below.

## Small-data (`r13`) Problem

This game addresses all small data through `r13` (`_SDA_BASE_ = 0x806734E0`): 13,359 accesses in `.text`, and none through `r2`. The entire 21 KB small-data span fits within one ~32 KB `r13` window. `_SDA2_BASE_` is loaded by crt0 but addresses nothing.

dtk names the read-only small-data segment `.sdata2`, so mwld emits it as `r2`-relative: mwld chooses the base register from the section name, not the address range. This changed 474 variables that the original accesses through `r13`, producing 1,554 differing bytes.

The usual linker fixes don't work: mwld emits only one `r13` small-data pair, and merging the segments changes the DOL layout.

The fork's `bake_conflicting_sda_relocations` pass drops `EMB_SDA21` relocations when mwld's section-derived base register differs from the original one, preserving dtk's instruction bytes.<br />
`_SDA2_BASE_` is pinned in [`../config/GVLE69/ldscript.lcf`](../config/GVLE69/ldscript.lcf) so crt0 matches.

Because this is fixed in the tool rather than the finished DOL, the *objects* stay correct and `objdiff` remains trustworthy.

> **Note:** This only covers code dtk extracts. Fresh code flipped to `Matching` can still hit `Range Error for small data relocation`. See [`matching_notes.md`](matching_notes.md#data-symbols-and-relocations).

## `config.yml` Reference

- **`skip_cfa_ranges`:** Hand-written Nintendo SDK supervisor-mode assembly that dtk's control-flow analysis cannot trace through (`bl .+4`, `rfi`, tail `b`).
    Located by scanning `.text` for `rfi`/`sc`/`mfmsr`/`mtmsr`/`tlbie`/`mtsr`. Bounds are approximate, refine as needed.
- **`force_active`:** Keeps functions that mwld's `-code_merging` would otherwise fold away as duplicates, which shifts every address after them.
    Add to this list only when a new match actually breaks `main.dol` (doesn't happen often).
- **`block_relocations` / `add_relocations` at `.init:0x80003160`:** crt0 loads the absolute address `0x8066FB50` through a `lis`/`ori` pair that dtk split across two symbols, binding the low half to the wrong target. That address falls in the padding gap between `.sbss` and `.sdata2`, so dtk left it sectionless.
    Retargeted to the `ABS` symbol `lbl_8066FB50`, which `ldscript.lcf` defines.
- **`fill_gaps`:** Left at its default `true`. Required, or the DOL is short by ~29 KB and every subsequent offset shifts.
- **`mw_comment_version: 11`:** A guess (CW 2.7+). Revisit if the real compiler version is ever pinned down.
