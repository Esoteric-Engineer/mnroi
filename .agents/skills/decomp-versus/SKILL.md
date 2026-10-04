---
name: decomp-versus
description: Run decomp-next aimed at the versus-mode code in this GameCube decomp (mnroi, GVLE69). It picks the next unmatched function on the versus path (match setup handlers, venue/character select, the character roster and loading, the game-state fields they drive) and byte-matches it. Use when asked to run "/decomp-versus" or to decompile the versus mode.
---

# decomp-versus: decomp-next, aimed at versus mode

This is a wrapper. Read `.agents/skills/decomp-next/SKILL.md` and follow it exactly: its
preconditions, loop, rules, notes and report all apply. Only the steps below change.

## Changes to decomp-next

- **Before step 1, read `docs/versus.md` section 5 (Target Order) only** — the status table plus
  whichever "files and boundaries" subsection covers the step you land on. That is enough to pick a
  target and know its blocker. Read further sections *on demand*, once you know what you are
  working: section 2 for the file map, section 3 for the setup flow, section 4 for the game-state
  and slot fields, section 6 for `GameFlow`. Don't read the file end to end; it is a reference, and
  reading all of it costs more than it returns. Same for `docs/characters.md` in the character
  steps: go to the section the target needs.
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
settled). Facts about characters (IDs, roster fields, NVB field meanings, what a new character
needs) go in `docs/characters.md`. Keep entries factual and short; mark guesses as guesses.

**`docs/versus.md` is a reference, not a log, and every line you add is a line every future run
pays for.** So write only what is expensive to re-derive from the DOL:

- **Do** record field types and meanings, confirmed file boundaries and why they are confirmed,
  which blocker stops a file, what the next target is, and facts about code that is still
  *unmatched*.
- **Don't** record what a matched function does — its source is the documentation, and `configure.py`
  is the authority on which units are matched. Don't narrate the work either: no "is now matched
  as X", no "the unit now covers", no "as earlier guessed", no fuzzy percentages, no running
  changelog of previous sessions. Git log holds that.
- When you finish a function, check whether that makes an existing passage redundant, and **delete
  it**. A file whose prose walkthrough is now readable source should lose the walkthrough and keep
  only the field table. Updating the doc means pruning it as often as adding to it.
- Prefer a table row to a paragraph, and keep each step's status to one row.

**The notes go in `docs/`, not at the top of the unit.** Cap a source file's header comment at at most
three lines: what the function does, and which doc holds the rest. One line each is worth spending on
a local fact the next editor can't get from the docs — the `.rodata` pool the unit owns, a symbol it
renamed, a struct field that only this file explains. Nothing else: no diff walkthrough, no fuzzy
percentage, no list of what was ruled out, no repeat of a `matching_notes.md` rule. Comments inside
the file are one-liners too; an offset in a struct is a trailing `// +0xNN`, not a paragraph. The
existing long headers in `src/Game/` predate this rule — don't copy their length.

## Report

Use decomp-next's report, and add one line on what the work taught about versus mode, if anything
(for example "`G+0x75C` confirmed as timer mode"). Then the commit message as decomp-next
specifies.
