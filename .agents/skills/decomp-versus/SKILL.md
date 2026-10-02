---
name: decomp-versus
description: Run decomp-next aimed at the versus-mode code in this GameCube decomp (mnroi, GVLE69). It picks the next unmatched function on the versus path (match setup handlers, venue/character select, the game-state fields they drive) and byte-matches it. Use when asked to run "/decomp-versus" or to decompile the versus mode.
---

# decomp-versus: decomp-next, aimed at versus mode

This is a wrapper. Read `.agents/skills/decomp-next/SKILL.md` and follow it exactly: its
preconditions, loop, rules, notes and report all apply. Only the steps below change.

## Changes to decomp-next

- **Before step 1, read `docs/versus.md`.** It maps the handler files, the match setup flow, the
  game-state object and the target order.
- **Step 1 (Choose):** if the user named a function or unit, work that one. Otherwise take the
  first unmatched function in `docs/versus.md` section 5, in that order. Within a file, take the
  next function after the unit's current `.text` end, so that the unit grows as one contiguous range
  from the file's first function. Still skip anything in `docs/nonmatching.md`. If that function is
  stuck, move on to the next file in section 5 instead of leaving a gap in the unit.
- **Step 3 (Claim):** when `docs/versus.md` section 2 gives the function's source file, name the
  unit after it (`Game/handlers/control.cpp`), not `Game/fn_XXXXXXXX.cpp`. If the unit already
  exists, extend its range rather than starting a new one.
- **Names:** the handler names in `symbols.txt` are the APT script names, not confirmed C++
  symbols. When the compiled name differs (GCC 2.95 mangling), rename the symbol to match what the
  unit emits; see `docs/versus.md` section 1.

## Recording what you learn

`docs/matching_notes.md` and `docs/nonmatching.md` rules from decomp-next still apply. In addition,
when matching a function tells you what a game-state field, slot field, match type or role index
means, update the tables in `docs/versus.md` (and remove the item from its "Open Questions" if
settled). Keep entries factual and short; mark guesses as guesses.

## Report

Use decomp-next's report, and add one line on what the work taught about versus mode, if anything
(for example "`G+0x75C` confirmed as timer mode"). Then the commit message as decomp-next
specifies.
