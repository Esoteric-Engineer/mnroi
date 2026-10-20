---
name: decomp-ai
description: Run decomp-next aimed at the enemy AI code in this GameCube decomp (mnroi, GVLE69). It picks the next open target in docs/ai.md's target order (the AI manager, behavior registry, brains and tasks, the AI object, its script API and the behaviors) and byte-matches it. Use when asked to run "/decomp-ai" or to decompile the enemy AI.
---

# decomp-ai: decomp-next, aimed at the enemy AI

This is a wrapper. Read `.agents/skills/decomp-next/SKILL.md` and follow it exactly: its
preconditions, loop, rules, notes and report all apply. Only the steps below change.

## Changes to decomp-next

- **Before step 1, read `docs/ai.md` section 6 (Target Order) only**: the table and the row you
  land on. That is enough to pick a target. Read further sections *on demand*, once you know what
  you are working: section 2 for the file map and edges, section 3 for how the layers call each
  other, section 4 for the `AIObject` fields, profiles, behaviors and tasks, section 5 for the
  notes. Don't read the file end to end.
- **Step 1 (Choose):** if the user named a function or unit, work that one. Otherwise take the
  first row of `docs/ai.md` section 6 that is not done (check `configure.py`), and in it the next
  function after the unit's current `.text` end, so that the unit grows as one contiguous range
  from the row's first function. This replaces decomp-next's "next to an already-matched unit"
  rule. Two row shapes differ:
  - **Rows that start with "identify"** (10 and 11): read the range's code and callers first and
    write what it is into `docs/ai.md` section 2, then match it small to large.
  - **Linkonce rows** (5, the inline functions): one small unit per run of neighbours, like
    `Game/fn_80442010.c`, rather than one unit for the whole range.

  Still skip anything in `docs/nonmatching.md`. If the target is stuck, record it there and take the
  next function, then the next row, instead of leaving a gap in a unit.
- **Step 3 (Claim):** name a unit after its row's first function (`Game/fn_80132480.cpp`). If the
  unit already exists, extend its range rather than starting a new one. When the range reaches an
  already-matched unit, merge it in as `docs/ai.md` section 5 describes.
- **Names:** the AI class names in `docs/ai.md` (`AIObject`, `AIBrain`, `AITask`) are guesses, so
  keep C++ symbols unmangled (`extern "C"`) until a class name is confirmed; renaming a class later
  means redoing every mangled symbol. Names from strings in the DOL, such as the behavior names in
  section 4.3, may be used. Don't give leaf accessors guessed names: keep `fn_XXXXXXXX` until they
  get renamed in one pass.

## Recording what you learn

`docs/matching_notes.md` and `docs/nonmatching.md` rules from decomp-next still apply. In addition,
when matching a function tells you what an `AIObject` field, global, task id or brain does, update
the tables in `docs/ai.md` (and remove the item from its "Open Questions" if settled). Facts about
characters and tuning fields go in `docs/characters.md` and `tools/nvbtool.py` `FIELD_NAMES`. Keep
entries factual and short; mark guesses as guesses.

**`docs/ai.md` is a reference, not a log, and every line you add is a line every future run pays
for.** So write only what is expensive to re-derive from the DOL:

- **Do** record field types and meanings, confirmed file boundaries and why they are confirmed,
  which blocker stops a row, and facts about code that is still *unmatched*.
- **Don't** record what a matched function does: its source is the documentation, and
  `configure.py` is the authority on which units are matched. Don't narrate the work either: no "is
  now matched as X", no fuzzy percentages, no changelog of previous sessions. Git log holds that.
- When you finish a function, check whether that makes an existing passage redundant, and **delete
  it**. Updating the doc means pruning it as often as adding to it.
- Prefer a table row to a paragraph, and keep each row's status to one line.

**The notes go in `docs/`, not at the top of the unit.** Cap a source file's header comment at three
lines: what the function does, and which doc holds the rest (`docs/ai.md row N`). One line each is
worth spending on a local fact the next editor can't get from the docs: the `.rodata` pool the unit
owns, a symbol it renamed, a struct field only this file explains. Comments inside the file are
one-liners; an offset in a struct is a trailing `// +0xNN`. When you touch a matched AI unit whose
header calls it a "PLAYER state" step, correct it to the behavior or task it is.

## Report

Use decomp-next's report, and add one line on what the work taught about the AI, if anything (for
example "`AIObject+0x500` bit 0xE is the blocking flag"), and one naming the section 6 row you
worked and the next open target. If every row is done, or every open one is stuck, say that the
target order needs a planning session. Then the commit message as decomp-next specifies.
