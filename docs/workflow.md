# Decomp Workflow

Commands, per-function loop, how to choose what to work on.

See also:
- First-time setup: [`README.md`](../README.md#building).
- Compiler/linker gotchas: [`matching_notes.md`](matching_notes.md).
- Functions stuck as `NonMatching`: [`nonmatching.md`](nonmatching.md).

`configure.py`'s object list is the source of truth for what is currently matched.

---

## 0. Guiding Rule

**The build must always end with `main.dol: OK`.**

That line means the built DOL is byte-for-byte identical to the original. If it ever stops saying `OK`, stop and fix that before doing anything else.

The workflow is designed so this is hard to break; see the `NonMatching` safety net in section 2.

---

## 1. Everyday Commands

| Command | What it does |
|---|---|
| `ninja` | Build everything. Prints progress %. |
| `python3 configure.py progress` | Print progress without building |
| `rm -rf build/GVLE69 && ninja` | Full rebuild from scratch (a few seconds; keeps downloaded tools) |
| `python3 configure.py --dtk build/tools/dtk-dev` | Re-configure by hand (after editing `configure.py`) |
| `python3 tools/diff_dol.py` | Byte-diff the built DOL against the original, broken down by segment |
| `python3 tools/find_candidates.py` | List small leaf functions that are good first targets |
| `python3 tools/objdiff_mismatches.py <unit> <function>` | Print only the instructions that still differ |

The `--dtk` argument is recorded in `build.ninja`, so plain `ninja` re-runs `configure.py` with it automatically. If you ever run a bare `python3 configure.py`, it falls back to downloading stock dtk and the build stops matching. Re-run it with `--dtk build/tools/dtk-dev`.

Use `tools/diff_dol.py` when `main.dol: OK` stops being OK. It maps each differing byte back to a virtual address, which usually lands directly on the bad instruction.

---

## 2. Per-Function Loop

### Step 1: Pick a function and find its bounds

See section 4 for how to choose *which* function. Look it up in `config/GVLE69/symbols.txt`:

```
GXInitTlutRegion = .text:0x8018E764; // type:function size:0x38 scope:global
```

Following the format of `end` = `start + size`:<br />
`0x8018E764 + 0x38` = `0x8018E79C`.

### Step 2: Claim the address range in `splits.txt`

Add a unit to `config/GVLE69/splits.txt` (blank line between units, tab-indented body):

```
Dolphin/gx/GXInit.c:
	.text       start:0x8018E764 end:0x8018E79C
```

The unit's ranges must cover whole functions. dtk preserves hand-added units when it regenerates the file.<br />
Multiple functions from one source file go in as multiple lines, or one wider range if they're contiguous.

> **Also rename the placeholder symbol in `symbols.txt`, in the same edit:** If the function is still named `fn_801834FC` and you're extending a file already flagged `Matching`, the link breaks immediately with `undefined: 'fn_801834FC', referenced from '…'`. This means some other still-unclaimed caller is referencing the old name.

Reference: [`splits.md`](splits.md)

### Step 3: Register the object in `configure.py`

Add to a library in `config.libs`:

```python
DolphinLib(
    "gx",
    [
        Object(NonMatching, "Dolphin/gx/GXInit.c"),
    ],
),
```

> **The `Object` name must be character-for-character identical to the `splits.txt` unit name:** If they differ, the build silently ignores your source. `configure.py` prints `Missing configuration for <name>` when a unit has no matching object.

**`NonMatching` vs `Matching`:**

| Flag | Compiles your source? | What gets **linked** |
|---|---|---|
| `NonMatching` | Yes (so objdiff can compare) | The **original extracted** object |
| `Matching` | Yes | **Your** compiled object |

Always start `NonMatching`. The DOL stays byte-perfect no matter how wrong your C is. Only flip to `Matching` once you're at 100%.<br />
Once a file is flagged `Matching`, adding a new function to it breaks `main.dol` until that function matches too.

### Step 4: Write the C and iterate

Create the source file at `src/<unit name>` (e.g. `src/Dolphin/gx/GXInit.c`), then run `ninja` and read the progress line for your category:

```
SDK Code: 65.36% fuzzy, 0.00% matched, 0.00% linked (0 / 1 files)
```

Compare the two disassemblies, adjust (see [`matching_notes.md`](matching_notes.md), and [`nonmatching.md`](nonmatching.md) if it is a known stall), and repeat until:

```
SDK Code: 100.00% fuzzy, 100.00% matched
```

### Step 5: Flip to `Matching` and verify

Change `NonMatching` to `Matching` in `configure.py`, run `ninja`, and confirm both:

```
build/GVLE69/main.dol: OK          <- the DOL still matches
SDK Code: 100.00% ... 100.00% linked
```

**On `force_active`:** a newly-matched function with no visible caller may get dropped by `mwld`'s `-code_merging`, shifting everything after it. The fix is adding its name to `force_active` in `config/GVLE69/config.yml`. Most matches need no entry, so only add one if `main.dol: OK` breaks.

---

## 3. Reading the diff

`build/GVLE69/src/...` is yours, `build/GVLE69/obj/...` is the original.

### objdiff GUI (primary)

Download from [encounter/objdiff](https://github.com/encounter/objdiff), set *Project directory* to this repo. It reads `objdiff.json` and rebuilds automatically on file changes.<br />
Unit names are prefixed with `main/`, e.g. `main/Dolphin/gx/GXInit`. Auto-generated units (everything not yet decompiled) are hidden by default.

### objdump (fast)

binutils isn't downloaded by a normal build; fetch it once with `ninja build/binutils`.

```bash
build/binutils/powerpc-eabi-objdump -d --no-show-raw-insn build/GVLE69/src/Dolphin/gx/GXInit.o
build/binutils/powerpc-eabi-objdump -d --no-show-raw-insn build/GVLE69/obj/Dolphin/gx/GXInit.o
```

### `tools/objdiff_mismatches.py` (exact per-instruction diff)

For an unlinked object, raw objdump output is noisy. This tool wraps the bundled `build/tools/objdiff-cli` and prints only the instructions that differ.

```bash
python3 tools/objdiff_mismatches.py Dolphin/dvd/dvdfs DVDConvertPathToEntrynum
```

It is stricter than the progress numbers. `report.json` runs objdiff with the default `functionRelocDiffs=none`, which flags a relocation only when the other side has none, so a reloc to the wrong symbol or addend still counts as 100% there. After renaming, splitting or resizing a symbol that matched units reference, check those units with this tool, or run `build/tools/objdiff-cli report generate --config functionRelocDiffs=all -o <file>` and look for anything below 100%.

### Decoding a data constant before you use it

When a function references a string or table you intend to reproduce, read the original bytes first rather than guessing:

1. Find the auto-generated data object covering the address (`build/GVLE69/obj/auto_*`).
2. `objdump -h` it to get the section's base VMA (also encoded in the filename).
3. `objdump -s` at the byte offset and decode.

---

## 4. Choosing what to work on

**Start with SDK code (`0x80168770`+; the first 0x2DE4 bytes are SN Systems' debug stub, see [`sdk_libraries.md`](sdk_libraries.md)), not game code.** Game code (`0x800034A0`–`0x80168768`) is C++ compiled with `-O4 -inline auto`, which inlined away essentially every small function (see [`baseline.md`](baseline.md)). SDK code is plain C with normal small functions, and its structure is publicly documented across other GameCube decomps.

Most of the 17,161 functions are still `fn_XXXXXXXX`. Naming is a large part of the work ahead.

### Finding candidates

```bash
python3 tools/find_candidates.py              # SDK range, 3–16 instructions
python3 tools/find_candidates.py --help       # other ranges/sizes
```

Good first-function traits: **leaf** (no `bl`), **no stack frame** (no `stwu`/`mflr`), small, and ideally operating only on its arguments (no `lis` global loads).

Beyond the trivial-leaf tier, the most productive strategy is to pick the next unclaimed function immediately after one you just matched, then identify it by source order in a reference decomp. That keeps each unit's claimed range contiguous.

### Reference decomp for SDK/runtime code (same compiler)

`configure.py` pins `GC/1.2.5n` for the Dolphin SDK libraries and `GC/1.3.2` for `Runtime.PPCEABI.H`/game code. Conveniently, [ACreTeam/ac-decomp](https://github.com/ACreTeam/ac-decomp) (Animal Crossing, GameCube) uses this exact pairing, and has a complete SDK tree.

Clone it as a sibling repo (`../ac-decomp`) and grep it directly. Key paths:

- `src/static/dolphin/<lib>/`: SDK source
- `include/dolphin/*.h`: headers, struct layouts, register addresses
- `src/static/Runtime.PPCEABI.H/`, `src/static/MSL_C.PPCEABI.bare.H/`: compiler runtime and C-library internals

> **Check ac-decomp before reconstructing any SDK-range function:** Search for a raw struct offset, the surrounding constants, or the function's apparent purpose.

Only use it as a reference, not a blind copy source. Struct layouts, flags, and function bodies can drift between games on the same SDK build, so every ported function still needs the normal compile-and-verify loop.

---

## 5. Files you edit

| File | What it holds |
|---|---|
| `src/**` | Your reconstructed C/C++ |
| `include/**` | Your reconstructed headers |
| `config/GVLE69/splits.txt` | Which address ranges belong to which source file |
| `config/GVLE69/symbols.txt` | Symbol names, addresses, sizes, scope |
| `configure.py` | Object registry, compiler flags, `Matching` status |
| `config/GVLE69/config.yml` | `force_active`, `skip_cfa_ranges`, relocation fixups |

**On regeneration:** dtk rewrites `symbols.txt` and `splits.txt` on every build.
- Hand-named symbols, hand-set attributes and hand-added splits **are preserved**.
- Auto-generated `fn_*` / `lbl_*` names are **not preserved**.
