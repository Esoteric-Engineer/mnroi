# Confirmed Non-Matches

Functions claimed as `NonMatching`, with what has already been tried. Don't re-guess these. When a unit flips to `Matching`, delete its entry and move any general lesson to [`matching_notes.md`](matching_notes.md).

No registered unit is `NonMatching` at the moment. What follows is the one compiler behaviour that used to park whole files, and one unclaimed family that is still stuck.

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
