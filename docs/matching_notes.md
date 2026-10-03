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
- **Within a unit's `.rodata`, each function's string literals come before its float pool, not after.** `cc1plus` writes a string out as soon as it is first used, which is while the function's own body is still being expanded, but defers the float and double constants to the pool it dumps after the body. So a function's claimed range runs string(s) then floats, and an unsigned-to-float conversion's `0x4330000000000000` magic double is one of those pool entries, first in use order (`Game/fn_800B5BC4.cpp`, `DrawFrameRate`: `"%.0f"` at 0x8048BE4C, then the double and six floats).

- **But check the pool address first: one that breaks the unit's `.rodata` ordering is another unit's literal, so reference it instead of claiming it.** Pool addresses rise with `.text` order (`Game/fn_8002623C.cpp` -> 0x80484E58, `Dolphin/os/__cvt_fp2unsigned.c` -> 0x8049C1C8), so a `lis`/`lfs` pair reading from *below* that line is a cross-TU reference, and claiming its range makes `dtk dol split` fail with a cyclic dependency, since the claim puts the unit both before (by `.rodata`) and after (by `.text`) that other unit. `extern const float lbl_<addr>[];` plus `lbl_<addr>[0]` gives the `ADDR16_HA`/`_LO` pair without claiming anything (`Game/fn_80443B70.c`, `fn_80443E20`: its 2^-31 sits in the 0x8009xxxx file's pool).
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
  through `r0` whatever the return type is (`Game/fn_80020E60.c`) **unless the assignment converts
  the pointer type**, which stores `r3` straight to the slot instead: `const char *key = f();` off a
  `char *`-returning `f` is direct, `char *key = f();` goes through `r0`, and so does a `void *`
  return into a `void *` local. So the three store shapes pick the declaration: `mr r0, r3` means the
  types match exactly, a bare `stw r3` means they differ by a qualifier or pointer type
  (`Game/fn_80131060.c`, `fn_801311C0`), and `mr rNN, r3` into a call-saved register means two
  locals (next bullet).

- **`mr rNN, r3` into a call-saved register, then `stw rNN` to a frame slot that every later use
  reads back, is two locals: a `register` one assigned to a plain one.** `register` alone puts the
  value in a call-saved register with no frame slot at all, and a plain local alone copies through
  `r0` or stores `r3` direct (previous bullet), so the shape needs
  `register T *tmp = f(); T *x = tmp;`, which also widens the `stmw`/`lmw` range by one register.
  This is what the roster accessors were stuck on (`Game/fn_8044B1D4.c`, `Game/fn_80131060.c`'s `fn_80131294`).

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

- **Two register copies before a byte store (`mr r0, r4` / `mr r11, r0` / `stb r11`) mean the
  parameter is `int` and the field `char`.** The second copy is the QImode conversion; an `int` field
  stores straight from the first copy (`Game/fn_804437D8.c`, `fn_80443860`). Before a *word* store
  the same pair means something else: the body assigned to a local of its own rather than to the
  parameter, and at `-O0` each `register` pseudo gets its own volatile
  (`register unsigned int clamped = value;` then `if (clamped > 2) clamped = 2;` in
  `Game/fn_804428E0.c`, where clamping the parameter in place emits one copy). `cmplwi` for the
  comparison is what makes the type unsigned.

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

- **Three register copies between an allocation call and a one-argument call (`mr r0, r3` /
  `mr rX, r0` / `mr r3, rX`) is a C++ `new T`, and settles the unit's language.** A plain nested
  call emits two copies, and no prototype, cast or temporary adds the third; only the
  new-expression's own temp does. The allocator is `__builtin_new` (`fn_801ACED4`,
  [`prodg.md`](prodg.md#c)), so a unit calling it is `.cpp` and the constructor that follows needs
  its mangled name in `symbols.txt` (`Game/fn_800887AC.cpp`).

- **`p->arr[p->n++] = x` with two register copies before the index `slwi` is cc1plus; cc1 emits
  one.** Another `.c`-vs-`.cpp` test that needs no size evidence, and the extra copy widens the
  `stmw` range and the frame by one register (`Game/fn_800887AC.cpp`).

- **A compare whose branch targets the instruction right after it is an `if` with an empty body, and
  a `b` to a label that itself only holds a `b` is an empty `else`.** The game's release build
  strips its diagnostics but keeps the test, so `if (x) { }` and `if (x) { ... } else { }` are
  normal source here; both are 1:1 reproducible. The empty body's branch polarity still gives the
  test's sense: `beq` to the next instruction is `if (x) { }`, `bne` is `if (!x) { }`
  (`Game/fn_80088740.c`). In a long `else if` chain, the *last* arm having a
  jump over the rest of the chain means the chain ends in an empty `else` too
  (`Game/fn_800887AC.cpp`, 20 of them).

- **`while (1)` emits two branches at the loop top (`b body` / `b end`), so a loop whose top holds
  only its test is `while (<test>)`.** `expand_exit_loop_if_false` always emits the conditional jump
  plus an unconditional one, and a constant condition degenerates to a pair. The `continue` target
  tells the two apart from `for`/`do`: `continue` branches to a `while`'s start label, i.e. the top,
  but to a separate end-of-body label in a `for (;;)` or `do`, so `continue`s that jump to the loop
  top rule out both (`Game/fn_800887AC.cpp`).

- **A C++ *leaf* method copies `this` into a volatile register (`mr r9, r3`, or `mr r0, r3` when the
  body never uses it), not into `r30`.** `this` is a pseudo, so the allocator only needs a call-saved
  register when the method calls something; a leaf method with that shape is therefore still ordinary
  C++ and needs no `register`-first-parameter `.c` workaround (`Game/fn_800B5BC4.cpp`,
  `DrawLoadProgress`, an empty two-`int` method). Judge the language from the trailing-branch count
  instead (next bullet).

- **A unit a few instructions off size despite near-100% fuzzy%: check `.cpp` vs `.c`.** C++ (even `extern "C"`) adds a redundant second branch to the epilogue after every `return` that plain C skips. Oversized means the unit should be `.c` (`fn_80431CCC`); *undersized* by exactly the missing tail branches means it should be `.cpp`, including for a `void` function with no `return` statement, where the pair lands after the last body label (`Game/fn_8001C258.cpp`). See [`prodg.md`](prodg.md#flags). But C emits one branch per `return`, so a pair can equally be two `return;` statements in C: settle the language from the body (next bullet) before changing the extension (`Game/fn_80023010.c`). The pair-carrying configuration *is* the one our `cc1plus` emits, so a cluster of pair-carrying functions inside a run of pair-less ones is a file boundary, not a blocker: give it its own `.cpp` unit and match it there (`Game/fn_80443908.cpp`, four functions between two `.c` runs).

- **`p->tbl[i].f` in an expression that also holds a call: cc1 and cc1plus order it differently.** cc1 loads `i`, emits the index `mulli`, then loads `tbl`; cc1plus loads `tbl` first into a non-volatile, which also grows the frame and the `stmw` range. No source rewrite moves it (index-first sums and `(char *)`/int casts all fold to the same tree), and cc1plus agrees with cc1 only when the base is a frame slot instead of a call, so this diff alone means the unit is `.c` (`Game/fn_80023010.c`).

- **A `switch`'s case bodies are emitted in source order, so the `.text` order of the bodies is the
  order to write the `case` labels in.** The dispatch tree ahead of them depends only on the set of
  values, so it is no guide; recover value-to-body by simulating the compare/branch tree instead of
  reading it, and treat a body whose guard branches into the *next* body as a fall-through case rather
  than a `break` (`Game/fn_800B5BC4.cpp`, 71 cases in scrambled order with two fall-throughs).

- **A gap between two used frame slots is dead locals, not padding: `obey_regdecls` gives every
  plain local a slot whether or not the body reads it.** So reproduce the gap by declaring locals of
  the right sizes in the right order rather than hunting for a compiler temp; temps are allocated
  after all the declarations, above the locals. `DrawFrameRate`'s 0x18-byte and 4-byte holes are
  three such declarations the release build no longer reads (`Game/fn_800B5BC4.cpp`).

- **Spare branches and pads at `-O0` come from statement shape, not expressions** (measured on `Game/fn_80023010.c`): a `break` on a `switch`'s textually last case still emits a branch to the switch's end, and so does a `default:` clause, so one spare branch there and a dispatch tree whose out-of-range tests already jump to the switch's end means the original had no `default:` (`Game/fn_80114420.cpp`); each `return` emits one branch to the epilogue; and a `nop` between the prologue and the first statement means the original's first statement was not a loop, since cc1 pads one that is, ahead of even a `for`'s init (`i = 0;` plus `while` drops the pad).

- **`rlwinm rX, rY, 0, n, n` with no record bit is a single-bit mask, `x & (1 << (31 - n))`, and
  `clrlwi rX, rY, 31` is `x & 1`.** GCC 2.95 picks `rlwinm` over `andi.` for every single-bit `&`, so a
  run of near-identical small getters differing only in `n` is a flags word's bit testers
  (`Game/fn_804428E0.c`, `fn_804432D8`-`fn_80443488`). After an `lbz`, a second `clrlwi rZ, rX, 24`
  on the mask's result means the field is a plain `unsigned char`, not a bitfield: the shorten rule
  for bitwise operators does the `&` in QImode and zero-extends it back to int, which is why the bit
  stays in place instead of being shifted down (`Game/fn_800B5BC4.cpp`, `GameFlow+0x1C`).

- **A compound assignment whose stored register also feeds `mr r3` is one statement, `return x |= BIT;`.**
  Splitting it into `x |= BIT; return x;` reloads the field after the store, which shows up as an extra
  `lwz`; the returning form also adds one register copy before the store that the `void` setter beside
  it does not have (`Game/fn_804428E0.c`, `fn_8044324C` vs `fn_804432AC`).

- **A `void` function with *no* trailing branch to the epilogue is language-ambiguous, so it can be
  matched as `.c` even in a C++ file.** Both plain C and the DOL's pair-less C++ configuration emit
  nothing there, so when such a function's body has no C++-only construct, give it its own `.c` unit
  and write `this` as a `register` first parameter, which reproduces the C++ `this`-in-`r30` shape
  (the rest of the parameters still spill). That is currently the only way to pick a function out of a
  file blocked by the pair ([`nonmatching.md`](nonmatching.md)); it does not prove the file is C
  (`Game/fn_80088740.c`, next to the pair-less C++ `.nsc` parser).

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
