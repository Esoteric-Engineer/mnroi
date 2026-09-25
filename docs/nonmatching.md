# Confirmed Non-Matches

Functions claimed as `NonMatching`, with what has already been tried. Don't re-guess these. When a unit flips to `Matching`, delete its entry and move any general lesson to [`matching_notes.md`](matching_notes.md).

Checked across every entry below, none of these helped: compiler versions `GC/1.0` to `2.0` (`1.2.5n` is best or tied everywhere), `-O4,s`/`-O4`/`-O3`/`-O2`, `-inline off`, `-use_lmw_stmw on`, and `#pragma scheduling off`/`peephole off`/both.

- `UnlockSram` (`0x8017F2E4`, `Dolphin/os/OSUnlockSram.c`, static `UnlockSram` in the SDK's `OSRtc.c`, global here because `OSGetSoundMode`/`OSSetGbsMode`/... call it): `NonMatching`, 98.07% (size 0x33C exact, 4 diff lines). ac-decomp's body plus the game's gbs sanitise (`if (Scb.offset <= 0x14)`, `(mode & 0x7C00) == 0x5000 || (mode & 0xC0) == 0xC0` -> `gbsMode = 0`) and a `static inline` copy of `WriteSram` (the unit, not the `WriteSram.c` one, inlines it).
  - What got it there: `SramControlBlock* scb = &Scb;` at the top (gives the `lis`/`addi r31` base up front and the `stmw r27`), `unsigned long mode` (a `u16` gives `cmpwi`, the original is `cmplwi`), an `OSSramEx*` local for the `sth 0x28(r4)` store, and a nested `{ unsigned long* poff = &scb->offset; ... }` block after the checksum loop for the `addi r30,r31,0x40` that the original keeps live across the `EXI*` calls (C89: the declaration must open a block; at function scope the `addi` moves to the prologue, 12 diff lines).
  - Remaining: the original schedules `addi r30,r31,0x40` before `lwz r0,0x40(r31)` and `addi r4,r31,0x14` before `lhz r3,0x3c(r31)`; ours puts each load first.
  - No effect: `poff` read/compare via `*poff` or `scb->offset`, `> `/`<` operand order, `const`/`register` qualifiers, split declaration and assignment of `mode`, `#pragma opt_lifetimes off`. Worse: `&Scb.offset` (8), `volatile` `poff` (18), `#pragma scheduling off` (64), `peephole off` (70), `opt_common_subs`/`opt_propagation off` (12).
