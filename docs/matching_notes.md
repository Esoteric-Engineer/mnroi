# Matching Notes

Reusable rules for getting a unit to match without breaking `main.dol`. Each entry is a symptom you can recognise, its cause, and the fix. Functions that are stuck live in [`nonmatching.md`](nonmatching.md). ProDG's flags and C++ conventions are in [`prodg.md`](prodg.md).

The MWCC notes from the SDK decomp (Dolphin SDK source shapes, MWCC data placement) were removed once the SDK was finished. They are in this file's git history if an SDK unit ever needs rework.

---

## Symbols and data

- **Reference dtk's symbol instead of defining fresh anonymous data.** A new `static` or string literal can score 100% in objdiff but land wherever the linker puts it, which breaks `main.dol`. `extern` dtk's symbol and leave its range unclaimed. If dtk named it `name$123`, first rename it to a plain identifier with `scope:global`, since `$` isn't valid C.
- **Hand-set names must not look auto-generated.** dtk regenerates `fn_*`/`lbl_*` names on every build, so renaming something *to* `lbl_<addr>` is silently reverted. Give it a real name.
- **`li r3, sym@sda21` where the DOL has `lis r9, sym@ha` / `addi r3, r9, sym@l` for an object's address** means the `extern` class is 8 bytes or less to the compiler, so it went to small data. Give the stub class a larger placeholder member (`char pad[0x300];`); a method call on it keeps the mangled name (`Game/fn_8002C690.cpp`).
- **Repeated builtin parameter types are not compressed in the mangled name:** a four-`int` constructor is `__6Obj118iiii`, not `iT1T1T1` (`T1` is for class types, `__4IterPcT1`). A wrong guess fails the link with `undefined: '<name>'` (`Game/fn_80456FF8.cpp`); `objdump -t` on the built object shows the emitted name.
- **Prefer referencing an unclaimed symbol over claiming its range.** Claiming even 4 bytes of `.sbss` can repack every other unclaimed symbol in that section. Override `scope:local` to `scope:global` in `symbols.txt` and use a plain `extern`. Hand-set attributes survive regeneration.
- **`undefined: '<name>'` after claiming a function means dtk renamed symbols.** Keep dtk's new name, set it `scope:global`, and update the `extern`s in other units, asm included. When two statics share a name, dtk gives the later one an `_<addr>` suffix (`AlarmHandler_80184B70`); define it non-`static` under that name.
- **Grep `symbols.txt` before hardcoding an address.** A raw `lis`/`addi` immediate stalls near 99% because the original has `R_PPC_ADDR16_HA`/`_LO` relocations. `sym@ha`/`sym@l` matches.
- **dtk's data symbols can be the wrong size.** The auto-namer merges unreferenced trailing objects and alignment padding into the preceding symbol, and sometimes names only part of a blob. Count the real objects, split or shrink the symbol in `symbols.txt`, and claim only what the unit defines. If a unit's data stays below 100% while `main.dol` matches, compare `readelf -sW` on `build/GVLE69/obj/<unit>.o` and `build/GVLE69/src/<unit>.o` to find the symbol whose size includes padding. It isn't always the last one.
- **Alignment padding between objects has no owner, so don't claim it.** dtk treats gaps of up to 8-byte alignment as padding by itself. For a larger alignment, add `align:N` to the following unit's line in `splits.txt` (and the alignment attribute in its source), then delete any `lbl_` dtk left in the gap. The same rule bites a claim that stops 4 bytes short of the next unit's `.rodata`: the leftover float becomes padding, and the unclaimed neighbour that reads it fails to link with `undefined: 'lbl_...'` (`scope:global` does not help), so claim that neighbour's function too (`Game/fn_800B4CF8.c`, `fn_800B5A08` with `fn_800B5AFC`).
- **To check whether a function was dead-stripped, grep `build/GVLE69/asm/`.** It holds the whole program (claimed units plus `auto_*`), so `grep -rn <symbol> build/GVLE69/asm/` is an exhaustive reference count. A string's presence only proves its file was linked: mwld drops functions nothing calls but keeps the file's data.
- **A table of code addresses must be typed function pointers, not raw bytes.** Hex constants match byte-for-byte, but they aren't relocations, so mwld dead-strips every function that only the table references, and `.text` comes out short.
- **A plain numeric table below 100% while `main.dol` matches: dtk read values that look like addresses as relocations.** Add `noreloc` to the symbol in `symbols.txt` (it needs a nonzero `size`).
- **The same in code: an `lis`/`ori` pair loading a constant that looks like an address comes back
  as `lis rX, sym@h` plus a `nop` carrying `[R_PPC_ADDR16_LO]`.** The bytes are identical, so
  `main.dol` is unaffected, but objdiff reports two `DIFF_ARG_MISMATCH`/`DIFF_REPLACE` lines against
  your plain immediates and the function never reaches 100%. Block both halves by instruction address
  in `config.yml`'s `block_relocations` (`.text:0x800B453C` and `.text:0x800B4540` for one pair), and
  check the invented target has other referrers first, or blocking can let mwld dead-strip it
  (`Game/fn_800B43F0.cpp`, four packed ARGB colors).
- **A zero word in `.text` that a `bl` targets is code, not padding.** dtk names it `pad_<addr>_text`. Check zero runs against branch targets before treating them as padding (`fn_801796B4`).
- **Claiming data whose owning unit is far later in link order needs no `link_order_callback`.** dtk re-slots the `auto_` objects around the claim. The exception is the common `.bss`/`.sbss` tail ([`common_bss.md`](common_bss.md)), where `dtk dol split` reports a cyclic dependency.
- **Data that only tail-of-`.text` functions read cannot be claimed by a unit that uses it, but a data-only unit can claim it.** The readers are linkonce functions ([`prodg.md`](prodg.md#inline-functions-and-the-tail-of-text)), so adding the `.data` range to one of their units makes `dtk dol split` fail with a cyclic link-order dependency, as a tail float pool does. A unit with a `.data` line and no `.text` splits and links (both measured on 0x804CA51C, [`versus.md`](versus.md#step-2-the-roster-data)). `.data` is laid out in link order, so the `.text` addresses that read the objects on either side bracket the file that really owns the block.
- **A float (or double) argument must be written as a literal, and its `.rodata` pool claimed.** GCC puts each function's float literals in an anonymous `.rodata` pool, in order of first use, laid out per function in `.text` order, and loads each one late in the argument setup as its own `lis sym@ha` / `lfs sym@l(r9)` pair. Referencing dtk's `lbl_` instead changes the code: an `extern float` scalar becomes an `R_PPC_EMB_SDA21` load (small data, since the size is <= 8), and an `extern float x[]` makes GCC materialise the base with `lis` into a non-volatile *before* the call that computes another argument. So keep the literal and give the unit the pool's range in `splits.txt` (`Game/fn_8001C258.cpp`: `.rodata start:0x804845DC end:0x804845E8`), after checking no other unit references those `lbl_`s.
- **Within a unit's `.rodata`, each function's string literals come before its float pool, not after.** `cc1plus` writes a string out as soon as it is first used, which is while the function's own body is still being expanded, but defers the float and double constants to the pool it dumps after the body. So a function's claimed range runs string(s) then floats, and an unsigned-to-float conversion's `0x4330000000000000` magic double is one of those pool entries, first in use order (`Game/fn_800B5BC4.cpp`, `DrawFrameRate`: `"%.0f"` at 0x8048BE4C, then the double and six floats).

- **A float pool's order is the order the constants are *forced into registers*, not the order they
  appear in the expression, so it reads the source's operand order back out.** `expand_expr` of a
  `REAL_CST` returns an immediate and pools nothing; the constant reaches the pool only when
  `expand_binop` needs it in a register, after the other operand has been expanded. So
  `320.0f - w * 0.5f` pools `0.5` first and emits `lfs w` / `lis 0.5@ha` / `lfs 0.5@l` / `fmuls` /
  `lis 320@ha` / `lfs 320@l` / `fsubs`, and a `fadds rD, r13, r0` whose product was computed first
  means the *other* operand is op0 (`Game/fn_800B7094.c`, four pool entries in 0x8048BEC0-0x8048BED0).
  The `extern const float lbl_<addr>[]` workaround below does not reproduce this: an array base is
  an address computation, so its `lis` is hoisted ahead of the whole statement instead of landing at
  the load.

- **But check the pool address first: one that breaks the unit's `.rodata` ordering sits in another file's `.rodata`, so it cannot be claimed. Keep the literals and give the unit `extern_pool=<address of its first literal>` in `configure.py`.** Pool addresses rise with `.text` order (`Game/fn_8002623C.cpp` -> 0x80484E58, `Dolphin/os/__cvt_fp2unsigned.c` -> 0x8049C1C8), so a `lis`/`lfs` pair reading from *below* that line belongs to an inline function, whose code was linked at the end of `.text` while its pool stayed with the file that included it ([`prodg.md`](prodg.md#inline-functions-and-the-tail-of-text)). Claiming the range makes `dtk dol split` fail with a cyclic dependency. `extern_pool` runs `tools/extern_pool.py` on the object: it checks the unit's pool against the original bytes at that address and points the relocations at dtk's `lbl_`s, so the code keeps the literal form's shape and nothing is claimed (`Game/fn_80447830.cpp`, `Game/fn_80448364.c` with two functions' pools back to back). A wrong constant fails the build there, which the progress report cannot see: its default relocation check treats any two pool references as equal (`fn_80448364` had 0.0f for a 1.0f and still read 100%). `extern const float lbl_<addr>[];` plus `lbl_<addr>[0]` is the older workaround and changes the code as soon as the literal is a call argument, a returned value or a compare operand (`Game/fn_80443B70.c`, `fn_80443E20`, where it does not).
- **A claimed float pool with an extra literal in the middle (a 1.0f the code never loads) is a pool entry of a linkonce function whose code went to the tail of `.text`.** Reproduce the gap with `static const float k __attribute__((section(".rodata"))) = 1.0f;` between the two functions: a plain `static const float` goes to `.sdata2`, and an unused `1.0f;` statement emits no pool entry (`Game/fn_8002FB08.c`). Such a static is emitted at the *end* of the file, so it only fits when the gap is after the last pool; for a gap before a later function's pool (the `-1.0f` orphan at 0x8048A75C in `Game/fn_80097750.cpp`), put `__asm__(".section .rodata\n\t.float -1.0\n\t.text");` between the two functions, which is emitted in source order.
- **`objdiff_mismatches.py` can report a `DIFF_REPLACE` with `[R_PPC_NONE]` on the original side alone, on an indexed load right after an `addi rX, rX, sym@l`.** Both sides' instructions are byte-identical and `readelf -r` shows no relocation at that offset in either object: objdiff synthesises the entry. Confirm with `readelf -r` and treat it as matched (`Game/fn_8001C258.cpp`, the `lwzx` at 0x8001C3A8); a `lwz`/`stb` with a displacement off an `addi r11, r9, sym@l` does the same (`Game/fn_80104504.cpp`, `Control_SetSelectInfo`).
- **A unit whose `.rodata` claim is not a multiple of the section's alignment shifts every later
  contribution, and `main.dol` comes out a few dozen bytes long.** The assembler pads a section's
  size up to its own alignment, which is 8 as soon as the pool holds a double (the
  unsigned-to-float magic), so a 0x34-byte claim becomes a 0x38-byte contribution and the next
  object starts 4 bytes late; the cascade of realignments is what makes the total delta larger than
  the padding. `objdump -s -j .rodata` on `build/GVLE69/{src,obj}/<unit>.o` shows identical bytes
  and a longer size. The fix is to extend the claim to the next 8-aligned boundary and define
  whatever objects fall inside it; a string literal belonging to a function further down the file is
  fine, as long as it goes **after** the last function in the source, since cc1 writes file-scope
  data where it is defined but dumps a function's pool ahead of that function's body
  (`Game/fn_800B46B0.c` defines `fn_800B5124`'s format string for this reason).

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
  return into a `void *` local; an `unsigned int` return into an `int` local is direct too
  (`Game/fn_804580CC.cpp`, `fn_80459474`). So the three store shapes pick the declaration: `mr r0, r3` means the
  types match exactly, a bare `stw r3` means they differ by a qualifier or pointer type
  (`Game/fn_80131060.c`, `fn_801311C0`), and `mr rNN, r3` into a call-saved register means two
  locals (next bullet).

- **`mr rNN, r3` into a call-saved register, then `stw rNN` to a frame slot that every later use
  reads back, is a C++ reference local: `T &x = f();`.** cc1plus wraps a reference's initializer in a
  `SAVE_EXPR`, whose register is kept alive for the whole function, and stores it to the reference's
  slot. `register T *tmp = f(); T *x = tmp;` in a `.c` unit gives the same code for a single one
  (`Game/fn_8044B1D4.c`, `Game/fn_80131060.c`'s `fn_80131294`), but not the same registers for two:
  the first reference's register is allocated ahead of the `register` parameters and the second
  one's after them, where `register` locals all come after (`Game/fn_804436D4.cpp`, declare the
  callee as returning `T &`).
  The same save-then-slot shape for an `int` result is `register int tmp = f(); int cap = tmp;` (`Game/fn_8043ED84.cpp`), and for a heap
  object whose virtual call reads the slot twice it is `Heap &heap = *f();` (`Game/fn_80440774.cpp`, `fn_804407E8`).

- **A C++ unit comes out 8 bytes over size, with two extra unreachable branches to the epilogue
  (`b .L` / `b .L` / `.L:` / epilogue).** `cc1plus` emits them unless an earlier function in the same
  translation unit set `current_function_return_value`. A constructor or a top-level `return <param/local/
  global/this>;` sets it, even in an unused inline function, and a `case` or a label clears it. In the
  original, the setter was usually a constructor or a header's inline function. Put
  `inline int sn_return_decl(int a) { return a; }` ahead of the unit's first function. See
  [`prodg.md`](prodg.md#the-function-end-branch-pair).

- **Definitions are emitted in source order, so one placed ahead of an earlier function shifts it.** The symptom is `main.dol` failing with single-byte diffs in the low byte of `bl` displacements at many call sites while every function still reads 100% in objdiff. Write the definitions in address order, a constructor's included (`Game/fn_8043C1EC.cpp`, `Byte1::Byte1`). A constructor *definition* carrying `__asm__("fn_XXXXXXXX")` fails in ngcas (`Unrecognised opcode ".l_f"`); rename the symbol to its mangled name instead (declarations may keep `__asm__`).

- **A C++ constructor has exactly *one* trailing branch to the epilogue, not the pair.** So the
  `.c`-vs-`.cpp` trailing-branch test below must exempt constructors: a one-branch tail on a function
  that takes `this` in r30 and returns it in r3 is a `.cpp` constructor, not C. Verified by
  `Vector::Vector() { w = 1.0f; }` compiling byte for byte to 0x80428F74 (`__6Vector`).
  That also makes a constructor the one function reachable inside a file blocked by the pair
  ([`nonmatching.md`](nonmatching.md)): give it a `.cpp` unit of its own (`Game/fn_800B43F0.cpp`).

- **A call result stored into a member with a bare `stw r3` (no `mr r0, r3`) is a member initializer,
  not an assignment.** `result = f();` in a constructor body always copies through `r0`, whatever the
  pointer types; `: result(f())` in the init list stores `r3` straight. The init list also fixes the
  order (base constructor, vptr, members in declaration order), so a base constructor the DOL calls
  first needs a real base class: declare `class Base { Base(); }`, rename its `fn_` symbol to the
  mangled `__4Base`, and make the vptr the first member, initialised first in the list
  (`Game/fn_80444034.cpp`).

- **A function that returns a plain `register int` local but still carries the branch pair: declare the local `unsigned int`.** A top-level `return <local>;` of the function's own return type sets `current_function_return_value` and drops the pair; the signedness mismatch makes the return expression a conversion, not a declaration, with no extra copy. A `char` local also keeps the pair but adds `mr r0` / `mr r3` (`Game/fn_804580CC.cpp`, `fn_804581A0`). If the DOL also stores the flag to a frame slot and reloads it (`stw r27, 0x8(r31)` / `lwz r0, 0x8(r31)` / `mr r3, r0`), add a plain `int result = found; return result;`; declare a call-result `register` local ahead of the flag when it must take the lower call-saved register (`fn_8045849C`).

- **A C++ *destructor* ends with one trailing branch too, so it is reachable in a pair-less file.**
  Its `if (__in_chrg & 1) __builtin_delete(this)` tail ([`prodg.md`](prodg.md#c)) is where that one
  branch comes from, which makes the destructor the second function (after the constructor) that a
  `.cpp` unit can pick out of a file blocked by the pair ([`nonmatching.md`](nonmatching.md))
  (`Game/fn_800B43F0.cpp`, `_._8GameFlow`).

- **A call on `this + N` as the first thing a constructor does is a member subobject's constructor,
  and an explicit call reproduces it.** GCC 2.95 emits member construction ahead of the body, so
  `fn_X((char *)this + 0xNN);` written as the body's first statement gives the same
  `addi r0, r30, 0xNN` / `mr r3, r0` / `bl`. That avoids naming the member's class and mangling its
  constructor just to get the prologue right (`Game/fn_800B43F0.cpp`, `GameFlow+0x18C`).

- **`lhz` / `extsh` / `add this` / `lwz 0x4(same)` / `stw` to a frame temp / `mtlr` / `blrl` off a
  pointer loaded from a fixed object offset is a virtual call.** GCC 2.95 here has no vtable thunks,
  so a vtable entry is 8 bytes (`short delta; short index; void *pfn`) and a `-O0` call reads delta
  and pfn from one computed entry address with no index check. The vptr is placed *after* the data
  members, so a reconstructed class's data has to fill exactly the vptr's offset, and the entry at
  byte offset `N` is the `(N / 8) - 1`'th declared virtual function (`Actor+0x198`, slots 0x58 and
  0x60, in `Game/fn_8002623C.cpp`). Writing it as a struct of pointers-to-member instead evaluates
  the entry address twice and does not match. The same shape on a call result (`mr r0, r3` / `mr r28, r0`, then the entry address in the
  next register) is `f()->slot(...)` on a class with `char data[N]` plus virtuals, not a hand-made entry
  struct with `register` locals, which gets the copies and registers wrong (`Game/fn_80436D88.cpp`).

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
  whether a 16-byte member copy's address folds into the symbol (`Game/fn_8002623C.cpp`, `Vector`). The same holds for a byte field read through a pointer member (`p->tbl->e[i].kind`, DOL `add` then `lbz 0x2b`, ours `addi 0x2b` then `lbzx`): `__attribute__((aligned(4)))` on the element struct (`Game/fn_8043C1EC.cpp`, `fn_8043C3C0`).

- **A field of an indexed element that the DOL reads as `mulli` / `addi rB, self, off` / `lwzx rX, rB, product`, or as `mulli` / `add rX, self, product` / `lwz f(rX)`, where pointer arithmetic gives `add rX, product, self` (and an extra `addi`): the element is in a real array member.** `self[i].f` and every cast or `(self + i)->f` spelling of it is a pointer sum, expanded with the product first; `self->entries[i].f` is an array reference, which computes the index into a register by itself and then follows the alignment rule above: a 4-aligned element gives the `addi`/`lwzx` form (`Game/fn_804396F8.c`, `Slot slots[2]`), an `aligned(8)` one the `add` plus displacement (`Game/fn_8043E148.cpp`).

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

- **`mr rN, r3` / `mr r3, rN` around a call result that is the receiver (or reference argument) of a method of a *base* class means the accessor returns a derived-class pointer.** The derived-to-base conversion saves the pointer in a whole-function pseudo, so it takes the first call-saved registers (`r30`, `r29`, ...); a same-class receiver gives the plain `mr r0, r3` / `mr r3, r0` pair. Declare `struct Sub : Obj { int pad; }`, make the accessor return `Sub *`, and call `acc(x)->get()`, with `__asm__("fn_XXXXXXXX")` on the base method (`Game/fn_80437B60.cpp`). Two copies with no frame slot (`mr r24, r3` / `mr r25, r24` / `mr r3, r25`) are two conversions, a base-qualified call: `acc(x)->Mid::get()` with `Sub : Mid : Obj` and `get` declared in `Obj`. Each conversion is one more saved value, which also moves the function's other saved values up ([`prodg.md`](prodg.md#register-allocation-at--o0)); two `register` locals give the copies but not the registers (`fn_80437E50`).

- **`p->arr[p->n++] = x` with two register copies before the index `slwi` is cc1plus; cc1 emits
  one.** Another `.c`-vs-`.cpp` test that needs no size evidence, and the extra copy widens the
  `stmw` range and the frame by one register (`Game/fn_800887AC.cpp`).

- **A guard whose last test is `bne Lafter` / `b Lbody`, with `Lbody` emitted immediately and
  holding one branch, is a negated conjunction: `if (!a || !b || !c) return;`.** `do_jump` reverses
  a test to a single `beq` only while it has no true-label, which is the case for every operand but
  the last; the last one gets both labels, so it keeps its own sense and is followed by a jump to
  the short-circuit label that `TRUTH_ORIF`/`TRUTH_NOT` created. Writing the same guard as
  `if (a == 0 || b == 0 || c == 0)` swaps the two labels and does not match, and
  `if (a && b && c) { ... }` is three plain `beq`s to one label with no fourth branch
  (`Game/fn_800B46B0.c`, `fn_800B47C0`).
- **A range guard whose first test (`blt`) lands on a label holding one `b` to the return block, while the second (`bgt`) lands on the block itself, plus a `b` over both to the body, is a ternary condition:** `if (id < 0 ? 1 : id > 4) return 0;`. `||`, `!(a && b)` and the goto forms all put both tests on the same label (`Game/fn_8009543C.c`).

- **`fcmpu` / `cror un, eq, lt` / `bso` (or `cror un, eq, gt`) on a float guard is an ordered `<=` (`>=`) in the source,** where `> 0.0f` negated gives a plain `ble`. Write the guard as the return condition: `if (f <= 0.0f || x != 1) return 0;` (`Game/fn_800AE534.cpp`, MOVESPEED).

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
- **A run of bare `b .Lend` instructions inside a `switch` (one per value) that the dispatch tree reaches as a single range is one `case N: break;` per value.** Writing `case 1: case 2: case 3: break;` emits one `b` and leaves the unit 4 bytes per merged case short; the dispatch still collapses the range (`Game/fn_8002E2C0.cpp`).
  order to write the `case` labels in.** The dispatch tree ahead of them depends only on the set of
  values, so it is no guide; recover value-to-body by simulating the compare/branch tree instead of
  reading it, and treat a body whose guard branches into the *next* body as a fall-through case rather
  than a `break` (`Game/fn_800B5BC4.cpp`, 71 cases in scrambled order with two fall-throughs).

- **A gap between two used frame slots is dead locals, not padding: `obey_regdecls` gives every
- **A pointer loaded, stored to a frame slot, then re-read a few instructions later for `addi rX, rY, N` (`lwz r0, 0x13c(r9)` / `stw r0, 0x58(r31)` / `addi r0, r31, 0x18` / `lwz r11, 0x58(r31)`) is a plain local, not a conversion temp:** `Node *n = p->node; r.set(&n->pos);`, and a derived-to-base conversion or reference gives a call-saved register (`r30`) instead. A frame slot the DOL shares between two locals (`0x10(r31)` for `slot` in one branch and `scene` later) means the first sits in its own `{ }` block; at function scope the second moves to the next slot (`Game/fn_800956D4.cpp`).
  plain local a slot whether or not the body reads it.** So reproduce the gap by declaring locals of
  the right sizes in the right order rather than hunting for a compiler temp; temps are allocated
  after all the declarations, above the locals. `DrawFrameRate`'s 0x18-byte and 4-byte holes are
  three such declarations the release build no longer reads (`Game/fn_800B5BC4.cpp`).

- **Spare branches and pads at `-O0` come from statement shape, not expressions** (measured on `Game/fn_80023010.c`): a `break` on a `switch`'s textually last case still emits a branch to the switch's end, and so does a `default:` clause, so one spare branch there and a dispatch tree whose out-of-range tests already jump to the switch's end means the original had no `default:` (`Game/fn_80114420.cpp`); each `return` emits one branch to the epilogue; and a `nop` between the prologue and the first statement means the original's first statement was not a loop, since cc1 pads one that is, ahead of even a `for`'s init (`i = 0;` plus `while` drops the pad; in `Game/fn_80439778.c` a `for` after plain statements had none, but two `for`s that followed another loop or an `if (...) return;` did, and `i = 0; while (i < n) { ...; i++; }` fixed both).

- **A `default:` clause whose branch lands on the epilogue label, past the switch's end label (which holds its own `b`), is `default: return;` in a `void` function, not `default: break;`.** `break` targets the switch end and leaves the unit at 99.8% (`Game/fn_801317D8.cpp`, `fn_801319D4`).

- **`rlwinm rX, rY, 0, n, n` with no record bit is a single-bit mask, `x & (1 << (31 - n))`, and
  `clrlwi rX, rY, 31` is `x & 1`.** GCC 2.95 picks `rlwinm` over `andi.` for every single-bit `&`, so a
  run of near-identical small getters differing only in `n` is a flags word's bit testers
  (`Game/fn_804428E0.c`, `fn_804432D8`-`fn_80443488`). After an `lbz`, a second `clrlwi rZ, rX, 24`
  on the mask's result means the field is a plain `unsigned char`, not a bitfield: the shorten rule
  for bitwise operators does the `&` in QImode and zero-extends it back to int, which is why the bit
  stays in place instead of being shifted down (`Game/fn_800B5BC4.cpp`, `GameFlow+0x1C`).

- **`(1 << n) & field` compiles to `sraw` / `clrlwi 31` where the DOL has `slw` / `and`: the field is `unsigned int`.** `fold` turns a signed `(1 << n) & x` test into `(x >> n) & 1`, and an unsigned operand blocks it. Likewise an extra `mr rX, r0` copy of a `register` parameter at its use in a comparison means the parameter is `char` or `short` (promoted, so reading it copies), not `int` (`Game/fn_804441A0.c`, `fn_80444370`).

- **`lis` / `addi r11` for a global's address followed by `lwz 0xNN(r11)`, where yours folds into `lis sym+0xNN@ha`, means the field is read through a struct pointer.** `*(int *)(sym + 0xNN)` folds the offset into the symbol; `((S *)sym)->field` with `char pad[0xNN]` before it does not (`Game/fn_804441A0.c`, `fn_80444454`).

- **`srwi r0, rX, N` / `xori r0, r0, 1` / `clrlwi r0, r0, 31` is `((x >> N) ^ 1) & 1` on an `unsigned int`.** `~(x >> N) & 1` gives `nor` and `((x >> N) & 1) ^ 1` swaps the last two instructions (`Game/fn_80434E0C.c`, `fn_80434F14`). A float read through a pointer field the DOL does as `lwz r11, off(r9)` / `lfs f0, N(r11)`, where a `char *` sum adds an `addi`, is a struct pointer with the float as a member.

- **A member increment with a dead `lwz r0, off(r31)` of the object pointer ahead of its `lwz r9` / `lwz r11` / `lwz r10, N(r11)` / `addi` / `stw` is `p->n++;`**, not `p->n = p->n + 1;`, which omits the dead load (`Game/fn_801B4628.c`).

- **A compound assignment whose stored register also feeds `mr r3` is one statement, `return x |= BIT;`.**
  Splitting it into `x |= BIT; return x;` reloads the field after the store, which shows up as an extra
  `lwz`; the returning form also adds one register copy before the store that the `void` setter beside
  it does not have (`Game/fn_804428E0.c`, `fn_8044324C` vs `fn_804432AC`).

- **`rlwinm rX, rY, 0, n, n` followed by `clrlwi rZ, rX, 16` on a getter's result is a 16-bit return, not a wider field.** Keep the `int` return type and write `return (unsigned short)(*(unsigned short *)(self + N) & MASK);`; the `unsigned short` return type would change the callers' prototypes (`Game/fn_804441A0.c`, `fn_80444CD0`).

- **A `void` function with *no* trailing branch to the epilogue is language-ambiguous, so it can be
  matched as `.c` even in a C++ file.** Both plain C and C++ with the pair's flag set emit
  nothing there, so when such a function's body has no C++-only construct, give it its own `.c` unit
  and write `this` as a `register` first parameter, which reproduces the C++ `this`-in-`r30` shape
  (the rest of the parameters still spill). It does not prove the file is C
  (`Game/fn_80088740.c`, next to the pair-less C++ `.nsc` parser). It scales to a whole file when
  *nothing* in it needs C++: a `.c` unit matched all 42 functions of the pair-less C++ file at
  0x800B7204-0x800B869C, static initializer included (`Game/fn_800B7204.c`).

- **An empty `void` method with one `b` to its epilogue (`mr r0, r3` / `b .L` / epilogue) is
  `.c` with an explicit `return;`.** Plain C emits that one branch per `return` and nothing for a bare
  `{ }`, so the empty body is 4 bytes short; `register T *this` supplies the `mr r0, r3` copy
  (`Game/fn_800B4CF8.c`, `fn_800B5524`).

- **A parameter spilled as `mr r0, rN` / `mr r9, r0` / `sth r9` is 16-bit, and `clrlwi`-on-read makes
  it unsigned.** Arguments arrive promoted to a word, so a 16-bit parameter needs the two copies to
  truncate before the halfword store, where an `int` one is a bare `stw`; reading it back as `lhz`
  plus a redundant `clrlwi rX, rY, 16` is the promotion back to `int` (`extsh` would be `short`).
  Declaring it `int` instead costs 8 bytes and reads the low half of the word slot, `lhz 0xa(r31)`
  (`Game/fn_800B5BC4.cpp`, the pad hooks).

- **Two *identical* back-to-back branches to the epilogue at the end of an `if` body mean an explicit
  `else` whose own last statement returns, not the C++ function-end pair.** The first is the `return`'s
  branch, the second is the jump over the `else`, and both land on the epilogue because the else
  branch returns too; dropping the `else` loses one of them. Tell them apart by position: this pair
  sits mid-function with the else body after it, while the C++ pair ([`nonmatching.md`](nonmatching.md))
  is the last thing before the epilogue (`Game/fn_80443B70.c`, `fn_80443D44`).
- **A generated `__static_initialization_and_destruction_0` and its `_GLOBAL_.I`/`_GLOBAL_.D`
  wrappers can be hand-written in a `.c` unit.** Real C++ static initialization is unusable wherever
  the DOL's `__sti` has no function-end branch pair ([`nonmatching.md`](nonmatching.md)), because
  cc1plus puts one on every generated `__sti`; where the DOL's has the pair, plain global definitions do (`Game/fn_80029F74.cpp`, with the globals' `.bss`/`.sbss` and the `.ctors`/`.dtors` words claimed). Writing the three functions by hand reproduces them
  exactly: `__sti(int initialize, int priority)` is `if (priority == 65535) { if (initialize) {
  <initializers>; ctor(&obj); } else { dtor(&obj, 2); } }` (65535 is GCC 2.95's default init
  priority, which it materialises as `li r9, 0` / `ori r9, r9, 0xffff`), and each wrapper is a
  `static void f(void)` that calls it with `(1, 65535)` / `(0, 65535)`. The `.ctors` and `.dtors`
  words come from `static void (*const e)(void) __attribute__((section(".ctors"))) = wrapper;`, with
  both ranges claimed in `splits.txt` (`Game/fn_800B7094.c`). The same works in a `.cpp` unit that already has the
  setter line, but `__sti` and `_GLOBAL_.I` must be non-`static` or mwld warns `FORCEACTIVE symbol ... not a global symbol` and `main.dol` comes out wrong, and `symbols.txt` names them with their C++ mangling (`..._0__Fii`, `fn_801040B8__Fv`) (`Game/handlers/characterselect.cpp`). A file with initializers but no
  destructors has only a `_GLOBAL_.I` and a `.ctors` word, and its `__sti` still ends the
  `if (initialize)` body with one branch over an empty `else`, so keep the `else { }`
  (`Game/fn_800B7204.c`).
- **mwld drops a whole object nothing outside references, `.ctors` word and all, so a static-init
  unit must define a symbol someone else uses.** The symptom is a link that succeeds while
  `.text` comes out short by exactly the unit's size and `.ctors`/`.dtors` by 4 bytes each; `.ctors`
  then starts 0x170 low in `objdump -h build/GVLE69/main.elf`. Claiming the file's own `.bss`/`.sbss`
  globals fixes it, which is what kept the original object alive too (`Game/fn_800B7094.c`).
- **An uninitialised global in a `.c` unit is COMMON, which lands in `.bss` and breaks every
  `@sda21` reference to it.** mwld says `Small data relocation (109) ... requires that symbol
  'lbl_X' ... be in a small data section but is in .bss`. `= 0.0f` makes it a definition but puts it
  in `.sdata`, 16 bytes of real data the DOL does not have;
  `__attribute__((section(".sbss")))` is what gives a nobits `.sbss` contribution
  (`Game/fn_800B7094.c`). C++ units are unaffected: C++ has no tentative definitions.

- **`cmpwi cr7, rX, 0` / `mfcr r0` / `extrwi r0, r0, 1, 30` feeding an argument register is `!x`.**
  GCC 2.95 materialises a logical negation as a value through the CR rather than a branch, and
  `extrwi ..., 1, 30` picks cr7's EQ bit. The call it belongs to still evaluates this argument ahead
  of the earlier ones, so argument 1 is loaded after the sequence
  (`Game/fn_800B7204.c`, `fn_804323E4(lbl_8066B690, !fn_804323B4(lbl_8066B690))`).

- **A call whose integer argument is loaded (`lwz r3`) after `f1`-`f4` is set up has that argument declared after the floats.** The moves into argument registers follow declaration order, and the float and integer register files are independent, so `r3` last means a prototype like `f(float, float, float, float, int, float)`, not an earlier evaluation of the local (`Game/fn_800B4CF8.c`, `fn_800B5124`'s call to `fn_800189E0`).

- **A prologue that spills `r5`-`r10` and, behind a `bne cr1`, `f1`-`f8` into a 0x78 frame is a variadic function, and an empty body reproduces it.** `void f(register void *a, register int b, ...) { }` gives the register-save area and the two `mr` copies of the named parameters (`Game/fn_80442010.c`, `fn_8044256C`).

- **`clrlwi rX, rY, 31` then a second `clrlwi rZ, rX, 24` before a `cmpwi` on a flag test means the parameter is `unsigned char`, but its callers pass an `int`.** A narrow definition conflicts with an `int` prototype in the same file, and a K&R definition adds copies. Declare the caller's prototype under another C name with `__asm__("fn_XXXXXXXX")` (`Game/fn_80445FD0.c`, `fn_80446214`).

- **`fadds fN, fM, fM` where the source has a doubling, and float temps in `f29`-`f31` with no `register` local, is `2.0f * expr` written as one expression.** `2.0f * x` folds to `x + x` with no pooled literal, and each saved sub-expression lands in a call-saved FPR when it spans calls; naming it as a `register float` adds an `fmr` copy. Several `fn_804352C8(v, i)` calls whose results are all loaded after the last call are one expression, not separate statements (`Game/fn_804467B0.c`).

- **A store through a call result, `*f(x) = v;`, comes out `mr r0, r3` / `mr rN, r0` / `stfs 0(rN)` in cc1plus and with the result used direct in cc1, so a pair-less function with that shape has no `.c` form.** The call-on-the-right variant (`*f(x) = g(v)`) shows `mr rN, r3` ... `mr rM, rN` before the store in cc1plus and a single register in cc1. So make it a `.cpp` unit with the setter line and `extern "C"` functions taking `register` parameters; the same goes for `p->arr[p->n++] = x` (`Game/fn_80446C80.cpp`, `Game/fn_800B4AB8.cpp`).
- **A cross-product-style expression whose result the DOL computes straight into `f31`/`f30`/`f29` and then stores to a frame slot (`fmuls f31, ...` / `fsubs f31, f31, f0` / `stfs f31, 0x8(r31)`), where yours uses `f0`: the value passes through a `register float` local.** The target pseudo is created before the expression's calls, so it spans them and takes a call-saved FPR. Write `register float rx; float x; rx = expr; x = rx;` (`Game/fn_80434864.c`, `fn_80434A18`, three of them).
- **A load through a call result, `out[0] = *f(v, 0);` (or `f(x)->field *= v;`, one call), comes out `mr r0, r3` / `mr rN, r0` / `lfs 0(rN)` in cc1plus (`mr r9, r3` in cc1), with a different call-saved register per statement.** Same as the store variant below: use a `.cpp` unit with the setter line and `extern "C"`. A reference local (`float &x = *f();`) adds a frame slot, so it is not the source (`Game/fn_80434BA4.cpp`; `Game/fn_80434420.cpp` for the store form).
- **A float parameter the DOL copies (`fmr f0, f1`) and then stores to a frame slot (`stfs f0, 0x8(r31)`) is a `register float` parameter plus a plain local copy: `register float s` / `float t = s;`.** A plain `float s` stores `f1` straight to the slot with no `fmr`. The integer parameters keep their own copies in declaration order (`Game/fn_80436000.c`, `fn_80436454`).
- **`li r0, 1` ahead of the load, then `cmpwi` / `bne` over `li r0, 0`, is `register int r = 1; if (*p == 0) r = 0; return r;`, not `!*p`.** The store-flag forms (`!x`, `x == 0`, `?:`) give `cmpwi cr7` / `mfcr` / `extrwi` instead, in `.c` and `.cpp` alike (`Game/fn_80436000.c`, `fn_80436294`). The same two-arm shape after a *call* (`mr r9, r3` / `li r0, 1` / `cmpwi r9` / `bne` / `li r0, 0`) is `return f(p) != 0 ? 1 : 0;`; a `register int` local takes a call-saved register there (`Game/fn_804580CC.cpp`, `fn_804588AC`). A value stored with `li r0, 0` first, then `beq`/`bne` to a shared `li r0, 1` before the `stw`, is a bare `||` stored to a member, `self->f = !a || (b & 0x10);`; a `register int __asm__("r0")` local gives the right `li`s but lets the compare temps reuse `r0` (`Game/fn_8002CE78.cpp`).
- **Float temps one register low (`f12` where the DOL has `f13`) after a clamp: the result was a `register float` local, and the DOL kept it in an expression temp.** A `register` float lives for the whole function and takes `f13` first; `return a >= lo ? (a <= hi ? a : hi) : lo;` leaves the temps at `f13` (`Game/fn_80446ACC.c`).

- **A constructor whose vptr store comes *before* a member initializer (`buf()`), with the vtable address as a plain `lis`/`addi`, has real virtual functions; a hand-written `vptr = sym;` in the body lands after the member init.** Declare a virtual in the base (so the vptr sits at `+0x0`) and a non-inline, never-defined virtual in the class (so its vtable is not emitted), and rename the DOL's vtable symbol to the compiler's `_vt.<len><Class>` in `symbols.txt`. A struct member's `buf()` is the `crclr` + `memset` libcall with a dead `mr r0, r3`; a `char[N]` member gives the three-temp loop instead (`Game/fn_8045F640.cpp`). `buf()` runs in declaration order, so stores that precede it in the DOL are `: flag(1), size(..), buf()` init-list entries; `memset` in the body or `buf = Chunk()` does not match (`Game/fn_8045F728.cpp`).

- **A destructor whose `__in_chrg` flag sits in a call-saved register (`mr r30, r4`), where the `.cpp` form spills it (`stw r4, 0x8(r31)` and a reload before `clrlwi 31`), is hand-written C.** Write `void f(register T *self, register int inChrg)` with the member destructors as plain calls with `2`, then `if (inChrg & 1) { __builtin_delete(self); } else { }` (the empty `else` is the `b` after the delete call); keep the `fn_XXXXXXXX` name, no mangling needed. A member guarded by `if (p) { if (p) g(p); else { } }` shows the same `b` after its call (`Game/fn_80447DBC.c`). The `GameFlow` destructor, which does spill, is the `.cpp` kind.

- **A string literal the DOL reads as `addi rX, r13, sym@l` (small data), in a unit whose `.sdata2` pool is cyclic to claim, is an `extern char sym[N]` with the real size.** An unsized `extern char sym[]` compiles to `lis` / `addi`; a known size <= 8 makes cc1 use `r13`, and the symbol stays unclaimed (`Game/fn_804488C0.c`, `"\r"` and `"\n\v"`).

- **A local array the DOL fills with `lis`/`addi sym@l` and an `lwz`/`lhz` copy, in a unit whose `.rodata` is cyclic to claim: copy from an extern struct of the same size.** A string initialiser compiles to the right code but points at the unit's own anonymous pool, so objdiff stays at ~96%. `struct Names { char c[0x18]; }; extern Names lbl_8049004E; Names names = lbl_8049004E;` gives the same block move against dtk's `lbl_`. A size of 8 or less makes cc1 use `r13` (`@sda21`), so declare the 6-byte one as `extern char lbl_80490048[];` and write `*(Chars *)lbl_80490048` (`Game/fn_804494AC.c`).
- **A bare `b` to the very next instruction, with no compare before it, is `goto L; L:`.** `if (1) {}`, `while (0);` and `{ }` emit nothing or different branches (`Game/fn_804491DC.c`, `fn_80449260`; `Game/fn_80448B24.c` uses the same).
- **A call whose pointer result the DOL stores straight into a frame slot (`stw r3`) instead of through `r0` wants a result type that differs from the local's by a qualifier:** declare the callee `const char *` and the local `char *` (`Game/fn_804494AC.c`, the iterator temporaries).

- **A `const T &` parameter bound to a by-value parameter whose spill slot the DOL puts *after* the locals: declare that parameter `register`.** A plain parameter gets its frame slot at function entry (slot 8, ahead of every local), but a `register` one is a pseudo until `&s` is taken, so the slot is allocated at the call and lands after the locals while the prologue still stores `r4` to it. The call's other arguments (`fn_8044A2D8(self, s, p, fn_80449C48(self))` with `const char *const &` and `void *const &` parameters) are C++ temporaries, which gives the `stw r3, slot` / `addi rN, r31, slot` shape and the early `addi r29` for the hoisted one. Declare a second prototype with `__asm__("fn_XXXXXXXX")` when two callers need different reference types (`Game/fn_80449930.cpp`, `fn_80449A6C`).

- **`bl f` / `mr r9, r3` / `mr r0, r9` / `mr r3, r0` in a function that returns the call's result: both are `char` (or `short`) returning.** A pointer or `int` result takes two copies; the extra one is the narrowing, with no `extsb` because the value is returned unchanged (`Game/fn_80449B80.cpp`, `fn_80449D58`). Callers that store the result into an `int` field look the same, so the width is a guess.
- **A dead `mr r0, r3` after a constructor call, then a fresh `addi r3, r31, N` for the method call, is a temporary: `return Iter(a, b).begin();`.** A named local (`Iter it(a, b); return it.begin();`) has no copy. A leaf constructor that shows `mr r0, r4` / `mr r9, r5` copies before its stores needs `register` parameters, with the members in the init list (`Game/fn_80449B80.cpp`, `Game/fn_8044A61C.cpp`).
- **`mr r9, rA` / `mr r8, rB` before `lbz` / `stb` in a byte loop is `*out++ = *first++;`.** Separate `*out = *first; first++; out++;` statements have no copies and load into other registers (`Game/fn_80449B80.cpp`, `fn_80449DA4`).
- **A file whose first function carries the pair and whose later ones do not: put `sn_return_decl` *after* the first function.** Ahead of it the first function loses its pair too (`Game/fn_80449B80.cpp`, `fn_80449B80` has three trailing branches, `fn_80449BE4` one). The same goes for the middle of a file: a class returned by value (`return list;`) does not set the flag, so put the setter line between the last pair-carrying function and the first pair-less one (`Game/fn_8010513C.cpp`, `Control_StartScreenFunction`).
- **A constant the DOL loads into a volatile temp (`li r9, 1` / `rlwinm r0, r9, ...`) where `register int f = 1;` lands in a call-saved register and a statement expression gives `li r0`:** pin it with `register int f __asm__("r9") = 1;` in its own block. The `if (f & 2)` is a compiler-generated array-destructor flag test (`Game/fn_8044A880.c`).

- **A copy constructor whose `this` is `r29` and whose source is `r30` (`mr r29, r3` / `mr r30, r4`, no frame slot for it) takes the reference parameter as `register`:** `Mat4(register const Mat4 &src)`; a plain `const T &` spills `r4` to a slot and puts `this` in `r30` (`Game/fn_8043A3BC.cpp`). The same holds for any reference parameter: `AptRef::operator=(register char *const &)` (`Game/fn_8044B5B0.cpp`).

- **A by-value class parameter (`void f(String s)`) is destroyed by the callee: `register` copy in `r30`, one `b` to a label, then `mr r3, r30` / `li r4, 2` / `bl <dtor>`.** Declare the parameter by value with a user-declared `~String()` and the shape comes out exactly, mangled `f__FG6String`; a pointer parameter plus an explicit destructor call does not (the `goto` label clears the pair flag) (`Game/fn_801044B0.cpp`). A temporary bound to a `const String &` parameter (`f(self, String(b), c)`) is destroyed by the caller instead, after a dead `mr r0, r3` and with its address formed through `r9` (`Game/fn_8044916C.cpp`).

- **`bl fn_XXXXXXXX` after `crclr cr1eq` and four `mr` argument copies for a 64-bit `/` is the libgcc call `__divdi3`, so name the callee that.** cc1 emits `bl __divdi3` for `long long / long long`; `fn_80179138` was renamed in `symbols.txt` and in its unit and `__div2i.c`. `OSGetTime() / (((LowMem *)0x80000000)->busClock / 4 / 1000)` gives the DOL's `lis r11, 0x8000` / `lwz 0xf8(r11)` (a bare `*(unsigned *)0x800000F8` folds into `ori`) (`Game/fn_80431CCC.c`, `fn_80432518`).
- **`x >= lo ? (x <= hi ? x : hi) : lo` with float literals, in a unit whose pool is cyclic, takes one `extern const float sym[]` per literal, used as `sym[0]`.** Sharing one array for both bounds adds an `addi` (`Game/fn_80431CCC.c`, the 0..1 clamp setters; their pool at 0x804854AC sits in the cycle through the Runtime units). `extern_pool` (above) is the alternative that keeps the literals.
- **`cmpw cr7` / `mfcr` / `extrwi 1, 30` in the `then` arm and `li r9, 0` in the `else` arm is `p != 0 ? a == b : 0`, not `p != 0 && a == b`** (`Game/fn_8043265C.c`, `fn_80432708`). The `&&` form hoists a `li` and branches the other way.
- **`lis sym@ha` ahead of the index `mulli`s and `addi sym@l` / `addi 0x20` after them is `sym[i].field[j].member`, a nested array reference in a struct, not a char-pointer sum.** Casting through `char *` folds the field offset into the symbol (`lis sym+0x20@ha`). `Obj` has to be padded to its true stride, `Entry entries[15]` plus tail (`Game/fn_8043265C.c`, `fn_80432764`).
- **A by-value class parameter's `bl _._NClass` is not a blocker when the destructor is still unclaimed:** rename it to `_._NClass` in `symbols.txt` and the call matches (when the destructor is a hand-written `.c` function, give it the name with the label trick below, as `Game/fn_804491DC.c` does for `_._6String`). Methods and constructors it needs are renamed to their mangled names the same way (`Game/fn_80432EE8.cpp`, `_._4Link`, `__4LinkRC4Link`; the by-value parameter shows in the symbol as `FPvG4Link`).
- **`lwz r0, A` / `stw r0, B` / `lwz r0, B` / `cmpwi` before a virtual `delete` of a pointer already held in slot A is a second local: `Link *dead = link; delete dead;`.** `delete link` tests slot A directly. A class with a `virtual ~T()` gets its vptr implicitly at the end of the data, so do not also declare a `vptr` member (it doubles the vptr and shifts the vtable load from `0x4` to `0x8`) (`Game/fn_80433058.cpp`).

- **A `.c` unit can define a symbol ngcas will not take as a function name (`_._4Link`) with a top-level `__asm__` label ahead of the function.** `__asm__("_._4Link")` on the definition makes cc1 emit a `.L_f*_._4Link_s:` label that ngcas rejects, and `.set` aliases are silently dropped, but `__asm__(".text\n\t.globl _._4Link\n\t.type _._4Link,@function\n_._4Link:");` placed directly before the function gives a second label at its address, and `__asm__(".size _._4Link, 0x60");` after it sizes it. The object then holds both `_._4Link` and the C name, and objdiff matches the former (`Game/fn_80433528.c`, a hand-written destructor whose callers need the mangled name). Units that call it by the C name declare it with `__asm__("_._4Link")`; on a declaration that is fine in C and C++ alike, and it is how every caller of a function renamed to its mangled name keeps compiling (`__asm__("__6StringPCc")`).

- **A function that ends `b .L` / `.L: mr r3, r30`, with the copy *after* the branch, returns a class by value; it is not a constructor.** The hidden result pointer arrives in `r3` and stays in `r30`, `this` (or a `register` first parameter) moves to `r29`, `return X(...);` constructs straight into the result and branches, and the result's address is copied back to `r3` after the return label. A constructor has the copy first (`mr r3, r30` / `b .L`). A `.c` function with the hidden pointer as a `register` first parameter gets r28/r30/r29 instead of r30/r29/r28, so it has to be `.cpp` (`Game/fn_8043B3DC.cpp`, `Flag`); its constructor can still be a `.c` function named by the mangled symbol (`__4Flagi`, `Game/fn_8043B4A4.c`). Returning a named local (`String res(...); return res;`) shows the copy constructor into `r30` with a dead `mr r0, r3`, then the local's destructor (`Game/fn_804473E8.cpp`, `Vector Key::value()`; `Game/fn_80448DA0.cpp`, `String IntToString(register int)`).

- **Three dead values right after the base-constructor call (`addi r0, rT, N` / `mr r11, r0`, `addi r9, rT, N` / `mr r11, r9`, `li r10, COUNT-1`) are an explicit array member initializer: `: Base(n), buf()`.** cc1plus makes the three register temporaries of its array-initialization loop (result, base, iterator) and then emits no loop for an element type without a constructor. `N` is the member's offset and `COUNT` its length (`Game/fn_80448CB0.cpp`, `char buf[0x40]` at `+0x8` in every `String` constructor). A constructor with an explicit `return;` before its end shows `b A` / `mr r3` / `b END` there, and an empty `else { }` after it adds one more `b` (`Game/fn_804493A0.cpp`).

- **A two-byte value assembled in a register (`slwi 8` / `or` / `rlwinm 0, 16, 23`) and stored with one `sth` is `char s[2] = { f(), 0 };` in C++.** The initializer holds a call, so it is built in a pseudo and stored whole. A two-`char` struct does the same in C, but cc1plus clears the register first (`li rN, 0`), because a C++ class has more `TYPE_FIELDS` than initializers (`Game/fn_80448DA0.cpp`).

- **Call-saved or float registers handed out in an order no declaration order reproduces: work out the lifetimes instead of permuting.** The `-O0` allocator sorts by lifetime, and a compiler-saved value (a reference local's initializer, an operand `fold` saves) can outlive or tie a `register` parameter, which no `register` local can. [`prodg.md`](prodg.md#register-allocation-at--o0) has the rule and how to dump the lifetimes (`Game/fn_804436D4.cpp`).

- **A member assigned a `?:` times a non-trivial operand (`self->target = CLAMP(v) * self->owner->scale;`) allocates differently in cc1 and cc1plus.** Both distribute the multiply into the arms and load the operand once, but cc1plus keeps the result in a register that is allocated ahead of the `register` parameter it reads (`f13`, with the parameter in `f12`), and cc1 after it. No `.c` rewrite reproduces that; the plain statement in a `.cpp` unit does (`Game/fn_8044655C.cpp`).

- **`lis`/`addi sym` then `addis rX, rY, 1` / `subi rZ, rX, N` is `sym + 0x10000 - N`, a field offset in a struct larger than 32 KB, not an absolute address.** There is no relocation on the `subi`, so a wrong layout shows as a two-byte `main.dol` difference with the unit at 99.99%; fix the offending member's offset (`Game/fn_8002623C.cpp`, `EffectSystem.extra` at `+0x9720`).

- **A relocation against `lbl_A+0xNN` where dtk's object has a second symbol `lbl_B`: dtk split one object at a referenced address.** Give `lbl_A` its real size in `symbols.txt` and delete `lbl_B`; dtk then writes every reference into the object as `lbl_A+offset`, which is what the compiler emits for a member (`lbl_80515030`, 0x9720 bytes).

- **Two counter increments an `-O2` unit keeps in source order (`lwz`/`addi`/`stw`, then the next `lwz`), where ours loads both first, are `volatile`.** The scheduler orders two volatile references and nothing else; one `volatile` is not enough. And read the loop's back-branch target before placing a statement inside the loop (`RealCore/fn_8023DAE0.c`).

- **A PowerPC instruction the compiler has no operator for (`frsqrte`) is inline asm, and the register numbers pick which temporaries are pinned.** `register double in __asm__("45") = x; register double d __asm__("44"); __asm__("frsqrte %0, %1" : "=f"(d) : "f"(in)); y = d;` reproduces `fmr f13, f0` / `frsqrte f12, f13` / `frsp f11, f12`: FPR names are numbers 32 + n here (`"f13"` is rejected), a plain `double` output gets a frame slot (`stfd`/`lfd`), and an unpinned `register double` takes `f13` ahead of the other temps (`Game/fn_80438044.cpp`, `fn_80438CC8`).
- **A dead `mr r0, r3` after each call that builds an object, then `addi r9, r31, N` / `mr r4, r9` for a later argument, is a chain of temporaries in one expression:** `f(a, b, T(1, 2).chain(T(3, s)).chain(T(4, 5)))` with `chain(const T &) const` and a `mutable` link. Four separate statements on named locals give no dead copy and `addi r0` / `mr r4, r0` instead (`Game/fn_80438044.cpp`, `fn_80438FAC`). A callee the unit does not own yet takes `__asm__("fn_XXXXXXXX")` on its member declaration.

- **A sum the DOL keeps unreassociated, `a*4` first and `b*0x90 + 0x198` added to it as a unit, where yours adds the constant to `a*4` (`slwi r11` / `addi r0, r11, 0x198`), is pointer arithmetic.** `fold` reassociates int sums but not pointer ones, so write it as pointers on a null base: `(int)((int *)((char *)((int *)0 + a) + (b * 0x90 + 0x198)) + a)`. Casts of the int terms, `offsetof`-style `&((S *)0)->arr[b]` and parenthesising do not change it (`Game/fn_804391E0.c`, `fn_804394C0`).

- **`fabs f13, f0` with no `frsp` on a `float` is `fabsf`, not `fabs`.** `extern float fabsf(float x);` expands inline to the bare `fabs`; `fabs`/`__builtin_fabs` widen to double and add a `frsp` (`Game/fn_8043B4A4.c`, `fn_8043B638`).

- **A chain of copies between register locals (`li r8, 8` / `mr r10, r8` / `ori r10` / `mr r0, r10`) is separate locals, and the allocator hands out volatiles in declaration order, so declare the last-used one first.** `register int n, m, t; t = c ? 8 : 0; m = t; ... n = m;` gives `t` r8, `m` r10, `n` r0; declaring `t` first hands them out the other way round (`Game/fn_8043B4A4.c`, `fn_8043B534`).

- **A virtual `delete` in hand-written C: write the call directly, `((void (*)(void *, int))e->pfn)((char *)self + e->delta, 3);`.** Naming the function pointer in a local adds a second frame slot (`0x10` next to the call's own `0x8`). An `if (self) { ... } else { }` supplies the `b` after the `blrl` (`Game/fn_8043B4A4.c`, `fn_8043B878`).

- **`mulli` / `addi` building an offset *before* the base's `lwz`, then `add rX, offset, base`, is a pointer plus a parenthesised int sum: `self->recs + (self->kind * 0x18 + 0x1c)`.** `&self->recs[...]` does the same. `(char *)0 + ... + (int)self->recs` and `(char *)(int expr) + (int)p` reassociate the constant onto the base and load the base first (`Game/fn_8043EB4C.c`, `fn_8043EB4C`).

- **A sum's operand order decides load order and register numbers, not just the add.** `self->w0 + n * tbl[idx]` matched where `n * tbl[idx] + self->w0` shifted every temp by one register (`Game/fn_8043EB4C.c`, `fn_8043EBB4`); `self->base->f7C + self->wC * 2` loads the pointer first and doubles with one `mr` / `add` (`Game/fn_8043E540.c`, `fn_8043E6C0`).

- **`subi` / `cmpwi` / `bge` / `li 0` clamping a load, with no frame slots, is one expression: `a + (x - 2 >= 0 ? x - 2 : 0)`.** `fold` turns the `?:` into a `MAX_EXPR` that works in expression temps; named `register` locals for the pieces take the registers the DOL's temps use, and plain locals add frame slots (`Game/fn_8043E540.c`, `fn_8043E604`). A float-free `x * 2` is `mr r0, rX` / `add rX, r0, rX`.

- **`stw rLo, 4(p)` then `srawi rT, rLo, 31` / `stw rT, 0(p)` is `*(long long *)p = (int)v;`; `li rT, 0` in place of the `srawi` is the unsigned variant** (`Game/fn_8043F5F0.c`, `fn_8043F7B8`, `fn_8043F7E8`).
- **A call returning a class of 8 bytes or less, with `crclr cr1eq` before the `bl`/`blrl` where the DOL has none: the class lacks a user-declared copy constructor.** Without one, the compiler treats it as a small aggregate; any user copy constructor (even undefined) removes the `crclr`. Larger classes never get it (`Game/fn_8044AE3C.cpp`, `AptObject`).

- **A dead 1-byte copy (`lbz r28, 0(r26)`, never read) allocated between parameters, and `li r0, 0` / `li r9, 0` / `stb r9` for a zero-initialised byte, are reproduced with pinned registers.** `register Tag c __asm__("r28") = *tag;` (a one-`char` struct gives the bare `lbz`) and `register int z __asm__("r0") = 0; register unsigned char zero __asm__("r9") = 0; Tag tag; tag.v = zero;`. The natural source was not found; the allocation matches bytes, not intent (`Game/fn_8044AE3C.cpp`). If a later call result then lands in `r11` where the DOL has `r0`, the pin is live too long: put the two pinned locals in a nested block that ends after the `tag.v = zero;` store (`Game/fn_8044C054.cpp`, `fn_8044C1B4`).
- **A one-argument front that passes an empty-class tag to its by-value-tag sibling (`li r0, 0` / `stw r0, 0xc(r31)`, a dead `li r0, 0`, `li r9, 0` / `stb r9, 0x10(r31)`, then `addi r0, r31, 0x10` as the last argument): a dead `int *p = 0;`, then in a nested block `register int z __asm__("r0") = 0; register unsigned char zero __asm__("r9") = 0; TagV tag; tag.v = zero;` and the call.** `TagV` is a one-`unsigned char` struct, and the call goes through a second prototype of the sibling taking `const TagV &` (`__asm__("fn_XXXXXXXX")`), since a by-value tag adds an `lbz`/`stb` copy (`Game/fn_8044AA94.cpp`, `fn_8044AB30`; the same in `fn_80448A28.cpp`, `fn_80448FD0.cpp`, `fn_8044D934.cpp`).

- **Jumps that land one `b` past an epilogue-bound `b`, with that `b` reached only by fall-through, are `return;`s plus an empty `else { }`.** Inside `if (c) { ...; return; ... } else { }` the `return`s branch to the epilogue label and the `then`-end `b` (jump over the empty `else`) sits ahead of the `else` label that the guard's `bne` skips to. An `else if` chain or a trailing `return;` instead puts every exit on the same side of that `b` (`Game/fn_8044FA9C.c`).

- **Four branches to the epilogue at a void function's end (a loop-exit `b`, a second `b` that the arms' early exits target, then the pair), with the early exits landing on the second one rather than on the epilogue, are `goto done;` plus `return; done: return;`.** A `return;` or `break;` in an arm jumps to the epilogue or the loop end, never to the middle of the run; only a user label does. Without the label the unit is 8 bytes short (`Game/fn_80028BAC.cpp`).
- **A constant (`.rodata` 8 bytes copied with `lwz`/`stw` to a frame slot, or an `int` stored from `lis`/`addi`) whose address the DOL passes as `addi r0, r31, N` / `mr r5, r0`, with the object being built at `addi r3, r31, 0x8` and its slot allocated *before* the constant's, is a `const T &` parameter bound to an rvalue, not a local.** A named local gets a slot at its declaration, ahead of the temporary; a reference-bound temporary comes after it and is not reused. Declare the constructor `Link(void *owner, const PmB &name) __asm__("__4LinkPvPCv")` (the mangled name in `symbols.txt` says `const void *`, but the caller never sees that) and call `Link(self, &FrameCtx::OnB)`. The by-value `Link`/`Cue` argument needs a user-declared copy constructor and destructor, or it is not passed by invisible reference and its temporary does not reuse slot 8 (`Game/fn_8002C824.cpp`).
- **A loop test where the DOL calls first and loads the `u16` counter after (`bl f` / `mr r0, r3` / `lhz` / `clrlwi 16` / `cmplw r9, r0`), where yours loads the counter into a call-saved register ahead of the call (`lhz r0` / `clrlwi r29, r0, 16`), is `i < f()` with `f` declared returning `unsigned short`.** Both operands are then `u16` and the shortened compare keeps the call first; an `int` or `unsigned` return loads `i` early, and writing `f() > i` only swaps the compare operands (`Game/fn_80097750.cpp`, `fn_800981FC`).
- **`cmpwi r0, 0` / `bne .L_rest` / `b .L_inc`, or `cmpwi r0, 1` / `beq .L_rest` / `b .L_inc`, with `.L_inc` the loop's increment, is `if (!x) continue;` / `if (f(h) != 1) continue;` in a `for`.** Writing the body as `if (x) { ... }` or ending a `while` with `i++` gives a single inverted branch instead (`Game/fn_80097750.cpp`, `fn_800981FC`).
- **A claim that starts 4 bytes into the original object (`.rodata` start 4 mod 8) and holds a double puts the double 4 bytes early, and `objdiff` shows `[.rodata]+0x28` where the DOL has `+0x2C`.** Start the claim at the preceding 8-aligned word and define that word (and any pad word at the end) in a top-level `__asm__(".section .rodata\n\t.globl lbl_X\nlbl_X:\n\t.float V\n\t.text");`; the `.globl` label is what lets the unit that reads the word through `extern_pool` link. The relocations then read `lbl_X+0xNN` in `objdiff` while `main.dol` matches (`Game/fn_80097750.cpp`).


## General

- Comments and whitespace don't affect output, except through `__LINE__`/`__FILE__` and inside string literals.
- Register allocation differences usually mean a different expression shape or variable lifetime. Reorder the locals, or add or remove a temporary.
- If you're stuck around 95% on register choice, [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) can brute-force equivalent C forms.
- C++ class layout must be exact. One wrong member offset breaks every function that uses the class, and vtable order follows the original's virtual declaration order.
- **A `\xNN` escape consumes every hex digit after it, not just two:** `"\xe9frez"` parses as `\xE9F` + `rez`. Close and reopen the string after the escape (`"\xe9" "frez"`).
