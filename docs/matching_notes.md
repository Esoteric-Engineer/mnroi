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
- **A float (or double) argument must be written as a literal, and its `.rodata` pool claimed.** GCC puts each function's float literals in an anonymous `.rodata` pool, in order of first use, laid out per function in `.text` order, and loads each one late in the argument setup as its own `lis sym@ha` / `lfs sym@l(r9)` pair. Referencing dtk's `lbl_` instead changes the code: an `extern float` scalar becomes an `R_PPC_EMB_SDA21` load (small data, since the size is <= 8), and an `extern float x[]` makes GCC materialise the base with `lis` into a non-volatile *before* the call that computes another argument. So keep the literal and give the unit the pool's range in `splits.txt` (`Game/fn_8001C258.cpp`: `.rodata start:0x804845DC end:0x804845E8`), after checking no other unit references those `lbl_`s.
- **`objdiff_mismatches.py` can report a `DIFF_REPLACE` with `[R_PPC_NONE]` on the original side alone, on an indexed load right after an `addi rX, rX, sym@l`.** Both sides' instructions are byte-identical and `readelf -r` shows no relocation at that offset in either object: objdiff synthesises the entry. Confirm with `readelf -r` and treat it as matched (`Game/fn_8001C258.cpp`, the `lwzx` at 0x8001C3A8).
- **A claimed literal pool shows up as unmatched data in the progress table.** The `Data:` line counts objdiff's `matched_data`, which pairs data by symbol name, and a compiler-generated pool is anonymous where dtk's extracted object has `lbl_<addr>` symbols. `report.json` still gives the unit `complete_data` 100% and `main.dol` is `OK`, so there is nothing to chase; naming the pool is not possible without breaking the function (previous entry).
- **Linker-generated addresses (`_stack_addr`, `_stack_end`, `__ArenaLo`, `__ArenaHi`) are defined in [`ldscript.lcf`](../config/GVLE69/ldscript.lcf).** If `main.dol` differs only in `lis`/`addi` pairs near `0x8067xxxx`/`0x8068xxxx`, check these first.
- **`.sdata2` symbols work in compiled code** (see [`baseline.md`](baseline.md#small-data-r13-problem)). `Range Error for small data relocation` means `build.ninja` wasn't generated with `dtk-dev`, or `build/GVLE69/sda_bake.json` is missing. In asm, name the symbol instead of writing a raw `off(r13)`.

- **A missing or spurious `mr r0, r3` before a call result is stored: check the callee's declared
  return type.** A `char`- or `short`-returning function whose result is converted to `int` emits a
  bare `mr r0, r3` with no `extsb`/`extsh`, while an `int`- or pointer-returning one stores `r3`
  straight to the slot. The roster stat accessors are declared `char` for this reason, and their
  caller only matched once they were (`Game/handlers/characterselect.cpp`). That applies to a value
  stored into an argument temp; a plain assignment to a local (`info = fn_800B14A0(actor);`) copies
  through `r0` whatever the return type is (`Game/fn_80020E60.c`).
- **A C++ unit comes out 8 bytes over size, with two extra unreachable branches to the epilogue
  (`b .L` / `b .L` / `.L:` / epilogue).** `cc1plus` emits them at the end of every function that is
  not a constructor, and most of the DOL's C++ functions do not have them; a class returned by value
  is only where it was first noticed, not the cause. No release, flag (6138 option/form combinations
  on `cc1plus.exe`) or source shape fixes it; see [`prodg.md`](prodg.md#release). Stop instead of
  reshaping the source (`Game/fn_8002623C.cpp`, `Game/handlers/characterselect.cpp`).

- **A C++ constructor has exactly *one* trailing branch to the epilogue, not the pair.** So the
  `.c`-vs-`.cpp` trailing-branch test below must exempt constructors: a one-branch tail on a function
  that takes `this` in r30 and returns it in r3 is a `.cpp` constructor, not C. Verified by
  `Vector::Vector() { w = 1.0f; }` compiling byte for byte to 0x80428F74 (`__6Vector`).

- **`lhz` / `extsh` / `add this` / `lwz 0x4(same)` / `stw` to a frame temp / `mtlr` / `blrl` off a
  pointer loaded from a fixed object offset is a virtual call.** GCC 2.95 here has no vtable thunks,
  so a vtable entry is 8 bytes (`short delta; short index; void *pfn`) and a `-O0` call reads delta
  and pfn from one computed entry address with no index check. The vptr is placed *after* the data
  members, so a reconstructed class's data has to fill exactly the vptr's offset, and the entry at
  byte offset `N` is the `(N / 8) - 1`'th declared virtual function (`Actor+0x198`, slots 0x58 and
  0x60, in `Game/fn_8002623C.cpp`). Writing it as a struct of pointers-to-member instead evaluates
  the entry address twice and does not match.

- **The DOL copies a call result through a non-volatile (`mr r30, r3` / `mr r3, r30`) with no frame
  slot for it, and its `stmw`/`lmw` range is one register wider than yours.** `obey_regdecls` is on at
  `-O0`, so GCC 2.95 honours the `register` keyword there and only there: `register` gives the local a
  pseudo that register allocation puts in a call-saved register, while a plain local always gets a
  frame slot. Add `register` to the local (`Game/fn_80114420.cpp`, the actor in the player loop).

- **A `switch` dispatch tree whose ordering tests are `cmplwi` where yours are `cmpwi` means the
  switch expression is unsigned.** The equality tests are `cmpwi` either way, so the ordering ones are
  the only tell; declaring the callee that produces the index `unsigned int` is enough
  (`Game/fn_80114420.cpp`, `fn_8009ABEC`).

- **A field load off a global array that the DOL does as `add rX, <variable>, <base>` plus a load
  displacement, where ours folds the field offset into the symbol and uses `lwzx`/`lfsx`, means the
  type's alignment is not 4.** GCC applies the constant bitpos before the variable offset only when
  the reference's alignment equals the field mode's alignment, so a 4-aligned struct takes the folded
  path. `__attribute__((aligned(8)))` on the innermost type restores the DOL's shape; it also decides
  whether a 16-byte member copy's address folds into the symbol (`Game/fn_8002623C.cpp`, `Vector`).

- **`addi r0, rX, N` / `mr r3, r0` instead of `addi r3, rX, N` before a call is only about the frame
  offset.** GCC targets r3 directly only when the object is the first local (offset 8); anywhere else
  it goes through r0. It is not a constructor-vs-plain-call difference, and the two dead `mr r0, rX`
  that open a compiler-generated array-constructor loop come from the same place.

- **A unit a few instructions off size despite near-100% fuzzy%: check `.cpp` vs `.c`.** C++ (even `extern "C"`) adds a redundant second branch to the epilogue after every `return` that plain C skips. Oversized means the unit should be `.c` (`fn_80431CCC`); *undersized* by exactly the missing tail branches means it should be `.cpp`, including for a `void` function with no `return` statement, where the pair lands after the last body label (`Game/fn_8001C258.cpp`). See [`prodg.md`](prodg.md#flags). But C emits one branch per `return`, so a pair can equally be two `return;` statements in C: settle the language from the body (next bullet) before changing the extension (`Game/fn_80023010.c`).

- **`p->tbl[i].f` in an expression that also holds a call: cc1 and cc1plus order it differently.** cc1 loads `i`, emits the index `mulli`, then loads `tbl`; cc1plus loads `tbl` first into a non-volatile, which also grows the frame and the `stmw` range. No source rewrite moves it (index-first sums and `(char *)`/int casts all fold to the same tree), and cc1plus agrees with cc1 only when the base is a frame slot instead of a call, so this diff alone means the unit is `.c` (`Game/fn_80023010.c`).

- **Spare branches and pads at `-O0` come from statement shape, not expressions** (measured on `Game/fn_80023010.c`): a `break` on a `switch`'s textually last case still emits a branch to the switch's end, and so does a `default:` clause, so one spare branch there and a dispatch tree whose out-of-range tests already jump to the switch's end means the original had no `default:` (`Game/fn_80114420.cpp`); each `return` emits one branch to the epilogue; and a `nop` between the prologue and the first statement means the original's first statement was not a loop, since cc1 pads one that is, ahead of even a `for`'s init (`i = 0;` plus `while` drops the pad).

- **Two *identical* back-to-back branches to the epilogue at the end of an `if` body mean an explicit
  `else` whose own last statement returns, not the C++ function-end pair.** The first is the `return`'s
  branch, the second is the jump over the `else`, and both land on the epilogue because the else
  branch returns too; dropping the `else` loses one of them. Tell them apart by position: this pair
  sits mid-function with the else body after it, while the C++ pair ([`nonmatching.md`](nonmatching.md))
  is the last thing before the epilogue (`Game/fn_80443B70.c`, `fn_80443D44`).

## General

- Comments and whitespace don't affect output, except through `__LINE__`/`__FILE__` and inside string literals.
- Register allocation differences usually mean a different expression shape or variable lifetime. Reorder the locals, or add or remove a temporary.
- If you're stuck around 95% on register choice, [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) can brute-force equivalent C forms.
- C++ class layout must be exact. One wrong member offset breaks every function that uses the class, and vtable order follows the original's virtual declaration order.
- **A `\xNN` escape consumes every hex digit after it, not just two:** `"\xe9frez"` parses as `\xE9F` + `rez`. Close and reopen the string after the escape (`"\xe9" "frez"`).
