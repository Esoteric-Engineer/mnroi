# Confirmed Non-Matches

Functions claimed as `NonMatching`, with what has already been tried. Don't re-guess these. When a unit flips to `Matching`, delete its entry and move any general lesson to [`matching_notes.md`](matching_notes.md).

Two registered units are `NonMatching` (`Game/fn_80437B60.cpp` and `Game/fn_804396F8.c`, below). Besides it, this file holds the one compiler behaviour that used to park whole files, and one unclaimed family that is still stuck.

---

## The C++ function-end branch pair

`cc1plus` ends a C++ function with two unreachable branches to the epilogue (`b .L5` / `b .L4` / `.L5:` /
`.L4:`) unless an earlier function in the same translation unit set `current_function_return_value`. A
constructor sets it, and so does a top-level `return` of a parameter, local, global or `this`, even
inside an unused inline function. Only a `case`/`default` or a user label clears it. No option changes it.

**Fix:** put `inline int sn_return_decl(int a) { return a; }` ahead of the unit's first function when the
original's flag was already set there (`Game/fn_800887AC.cpp`, `Game/handlers/characterselect.cpp` and
`Game/fn_8002623C.cpp` do). [`prodg.md`](prodg.md#the-function-end-branch-pair) has the code, the evidence
and the ordering rules, and `python3 tools/pair_map.py <address>` says which state a function was in. There
is no build-side workaround: the build used to have a per-unit `strip_fn_end_pair` that deleted the pair from
the assembly, and it was removed because it can't model a file where a `switch` brings the pair back.

---

## `fn_80437E50` (`Game/fn_80437B60.cpp`, 99.0%): register numbers around the `radius` call

0x80437E50-0x80438044, `extern_pool=0x80486868` (one 0.0f). Everything matches except register numbers: the
DOL has `h` of the first virtual call in `r29`, above the parameters (`r28`-`r26`), and the receiver of the
direct call `fn_802EA5D8` goes `mr r24, r3` / `mr r25, r24` / `mr r3, r25`, so those two sit above the second
virtual call's entry address (`r23`). By [`prodg.md`](prodg.md#register-allocation-at--o0) that means both are
whole-function saved values (`SAVE_EXPR`s), and the receiver is a derived-to-base reference conversion.
The source in the unit is two `register Handle *` locals (`a = f(); b = a; b->radius()`), which gives the
right instructions and size but the lifetimes of ordinary locals, so the registers come out one lower.
Tried for the receiver, none giving `r24` -> `r25` -> `r3` with no frame slot: result cast to a derived
class (`HandleD : Handle { int pad; }`, two levels too), accessor declared returning `HandleD *` or `HandleD &`,
method on `Handle` or free function taking `Handle *`, `Handle &`, `const Handle &`, `*(Handle *)&...`,
`Handle &hr = ...` (right pair, then `stw r25` to a slot), `register Handle &hr` (right pair plus a third copy
`r22`). Next to try: a form whose reference temp has no variable behind it, or `register ... __asm__("rN")`
pins on `a` and `b` (the `h` register would still be off).

---

## `fn_804396F8` (`Game/fn_804396F8.c`, 89.3%): the slot-field address

0x804396F8-0x80439778. The `fn_80439C64` call and the result stores match. The second argument of `fn_80058284` is
`*(int *)(self + 0x38 + (self->5C & 1) * 0x14)` and the DOL builds it as `lwz r0` / `clrlwi r9, r0, 31` /
`mulli r0, r9, 0x14` / `addi r9, r30, 0x38` / `lwzx r4, r9, r0`: index first, the base's constant folded into its own
`addi`, then an indexed load. Every form tried gives `lwz r9` / `clrlwi r0` / `mulli r9` / `add r11, r9, r30` /
`addi r9, r11, 0x38` / `lwz r4, 0(r9)` (8 bytes over): char-pointer sum, int-cast sum in either operand order,
`((T *)(self + 0x38))[k].f` and `[k * 5]` on an `int *`, a `char (*)[0x14]`, and the null-base pointer trick that
fixed `fn_804394C0` ([`matching_notes.md`](matching_notes.md)). The load also goes into `r0` first where ours uses `r9`.

---

## `fn_80448AC0`, `fn_80449020` and `fn_8044AB30` — the tag argument of the to-`String` wrappers (unclaimed)

0x80448AC0-0x80448B24, 0x80449020-0x80449084 and 0x8044AB30-0x8044AB94. Each is the one-argument front of a
three-function family that turns a value into a `String` returned by value, for `String`, `int` and
`const char *` in turn. The other two of each family are plain (see
[`matching_notes.md`](matching_notes.md), the by-value return tail):

- `fn_80448A28`, `IntToString__Fi` (`Game/fn_80448DA0.cpp`) and `fn_8044AA94` do the conversion from a
  `register` parameter (`return s;`, the digit loop, `return String(s);`).
- `fn_80448A74`, `fn_80448FD0` and `fn_8044AAE0` take `(const T &value, Tag)` and return the first one's result.
  The second parameter is unused and lands in `r29`, so it is a class passed by value: a dispatch tag. All
  six of these are matched (`Game/fn_80448A28.cpp`, `Game/fn_80448FD0.cpp`, `Game/fn_8044AA94.cpp`).
- The three here take `(const T &value)` and call the middle one. `String f(const String &s) { T *p = 0;
  return fn_80448A74(s, Tag()); }` with `struct Tag {};` reproduces everything except the tag's construction.

The DOL sets a 4-byte local to 0 (`li r0, 0` / `stw r0, 0xc(r31)`), then has a dead `li r0, 0`, then
`li r9, 0` / `stb r9, 0x10(r31)`, and passes `r31 + 0x10`. `Tag()` gives `li r0, 0` / `stb r0, 0x11(r31)` /
`li r0, 0` / `stb r0, 0x10(r31)` instead: the temporary gets a slot of its own, 4 bytes over. `li r9, 0` /
`stb r9` after a value in `r0` is how cc1plus copies an empty class (a named `Tag tag;` argument gives
`lbz r0, 0x10(r31)` / `li r9, 0` / `stb r9, 0x11(r31)`), so the DOL's source is an empty-class value that
expands to a constant in a register with no slot behind it. Tried without getting that: a named local (plain,
`register`, `const`, `= Tag()`, `= {}`), a file-scope `const Tag` (an `lbz` where the dead `li` is), a default
argument, template tags (`Type2Type<T>`, `Int2Type<0>`), a derived tag sliced to its base, `(p, Tag())`,
`z ? Tag() : Tag()`, a one-`char` struct, `*(Tag *)p`, and a reference or pointer parameter (one slot, but
`li r0, 0` / `stb r0` and no dead load).
