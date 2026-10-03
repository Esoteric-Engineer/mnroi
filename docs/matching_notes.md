# Matching Notes

Reusable rules for getting a unit to match without breaking `main.dol`. Each entry is a symptom you can recognise, its cause, and the fix. Functions that are stuck live in [`nonmatching.md`](nonmatching.md). ProDG's flags and C++ conventions are in [`prodg.md`](prodg.md).

The MWCC notes from the SDK decomp (Dolphin SDK source shapes, MWCC data placement) were removed once the SDK was finished. They are in this file's git history if an SDK unit ever needs rework.

---

## Symbols and data

- **Reference dtk's symbol instead of defining fresh anonymous data.** A new `static` or string literal can score 100% in objdiff but land wherever the linker puts it, which breaks `main.dol`. `extern` dtk's symbol and leave its range unclaimed. If dtk named it `name$123`, first rename it to a plain identifier with `scope:global`, since `$` isn't valid C.
- **Hand-set names must not look auto-generated.** dtk regenerates `fn_*`/`lbl_*` names on every build, so renaming something *to* `lbl_<addr>` is silently reverted. Give it a real name.
- **Prefer referencing an unclaimed symbol over claiming its range.** Claiming even 4 bytes of `.sbss` can repack every other unclaimed symbol in that section. Override `scope:local` to `scope:global` in `symbols.txt` and use a plain `extern`. Hand-set attributes survive regeneration.
- **`undefined: '<name>'` after claiming a function means dtk renamed symbols.** Keep dtk's new name, set it `scope:global`, and update the `extern`s in other units, asm included. When two statics share a name, dtk gives the later one an `_<addr>` suffix (`AlarmHandler_80184B70`); define it non-`static` under that name.
- **Grep `symbols.txt` before hardcoding an address.** A raw `lis`/`addi` immediate stalls near 99% because the original has `R_PPC_ADDR16_HA`/`_LO` relocations. `sym@ha`/`sym@l` matches.
- **dtk's data symbols can be the wrong size.** The auto-namer merges unreferenced trailing objects and alignment padding into the preceding symbol, and sometimes names only part of a blob. Count the real objects, split or shrink the symbol in `symbols.txt`, and claim only what the unit defines. If a unit's data stays below 100% while `main.dol` matches, compare `readelf -sW` on `build/GVLE69/obj/<unit>.o` and `build/GVLE69/src/<unit>.o` to find the symbol whose size includes padding. It isn't always the last one.
- **Alignment padding between objects has no owner, so don't claim it.** dtk treats gaps of up to 8-byte alignment as padding by itself. For a larger alignment, add `align:N` to the following unit's line in `splits.txt` (and the alignment attribute in its source), then delete any `lbl_` dtk left in the gap.
- **To check whether a function was dead-stripped, grep `build/GVLE69/asm/`.** It holds the whole program (claimed units plus `auto_*`), so `grep -rn <symbol> build/GVLE69/asm/` is an exhaustive reference count. A string's presence only proves its file was linked: mwld drops functions nothing calls but keeps the file's data.
- **A table of code addresses must be typed function pointers, not raw bytes.** Hex constants match byte-for-byte, but they aren't relocations, so mwld dead-strips every function that only the table references, and `.text` comes out short.
- **A plain numeric table below 100% while `main.dol` matches: dtk read values that look like addresses as relocations.** Add `noreloc` to the symbol in `symbols.txt` (it needs a nonzero `size`).
- **A zero word in `.text` that a `bl` targets is code, not padding.** dtk names it `pad_<addr>_text`. Check zero runs against branch targets before treating them as padding (`fn_801796B4`).
- **Claiming data whose owning unit is far later in link order needs no `link_order_callback`.** dtk re-slots the `auto_` objects around the claim. The exception is the common `.bss`/`.sbss` tail ([`common_bss.md`](common_bss.md)), where `dtk dol split` reports a cyclic dependency.
- **Linker-generated addresses (`_stack_addr`, `_stack_end`, `__ArenaLo`, `__ArenaHi`) are defined in [`ldscript.lcf`](../config/GVLE69/ldscript.lcf).** If `main.dol` differs only in `lis`/`addi` pairs near `0x8067xxxx`/`0x8068xxxx`, check these first.
- **`.sdata2` symbols work in compiled code** (see [`baseline.md`](baseline.md#small-data-r13-problem)). `Range Error for small data relocation` means `build.ninja` wasn't generated with `dtk-dev`, or `build/GVLE69/sda_bake.json` is missing. In asm, name the symbol instead of writing a raw `off(r13)`.

- **A `NonMatching` leaf function stuck a few instructions oversized despite near-100% fuzzy%: check `.cpp` vs `.c`.** C++ (even `extern "C"`) adds a redundant second branch to the epilogue after every `return` that plain C skips. See [`prodg.md`](prodg.md#flags).

## General

- Comments and whitespace don't affect output, except through `__LINE__`/`__FILE__` and inside string literals.
- Register allocation differences usually mean a different expression shape or variable lifetime. Reorder the locals, or add or remove a temporary.
- If you're stuck around 95% on register choice, [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) can brute-force equivalent C forms.
- C++ class layout must be exact. One wrong member offset breaks every function that uses the class, and vtable order follows the original's virtual declaration order.
- **A `\xNN` escape consumes every hex digit after it, not just two:** `"\xe9frez"` parses as `\xE9F` + `rez`. Close and reopen the string after the escape (`"\xe9" "frez"`).
