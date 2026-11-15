---
name: decomp-story
description: Run decomp-next aimed at story mode and the level script system in this GameCube decomp (mnroi, GVLE69). It picks the next open target in docs/story.md's target order (the mission handlers, the chronicle, the save profile, the script class table and base class, and the 102 script classes) and byte-matches it. Use when asked to run "/decomp-story" or to decompile story mode, missions or level scripts.
---

# decomp-story: decomp-next, aimed at story mode

This is a wrapper. Read `.agents/skills/decomp-next/SKILL.md` and follow it exactly: its
preconditions, loop, rules, notes and report all apply. Only the steps below change.

## Changes to decomp-next

- **Before step 1, read `docs/story.md` section 6 (Target Order) only**: the table and the row you
  land on. That is enough to pick a target. Read the other sections *on demand*, once you know what
  you are working on: section 2 for the file map and edges, section 3 for the layers, section 4 for
  the base class, class table, missions, chronicle and profile, section 5 for the notes. Don't read
  the file end to end.
- **Step 1 (Choose):** if the user named a function or unit, work that one. Otherwise take the
  first row of `docs/story.md` section 6 that is not done (check `configure.py`), and in it the next
  function after the unit's current `.text` end, so that the unit grows as one contiguous range
  from the row's first function. This replaces decomp-next's "next to an already-matched unit"
  rule. Some rows have a different shape:
  - **Rows that say "identify first"** (2, 3 and 22): settle the file edge from the code, its
    `.rodata` and its callers, and write the edge and its evidence into `docs/story.md` section 2
    before matching.
  - **The linkonce row** (7, the inline functions): one small unit per run of neighbours, like
    `Game/fn_80442010.c`, rather than one unit for the whole range.
  - **The handler files** (rows 1 and 23): one unit for the whole file, grown from its first
    function. It claims `.ctors` and `.sbss` with the static initializer, as
    `Game/handlers/mainmenu.cpp` does.
  - **Rows with several files** (8): one unit per file, in the order the row lists them.

  Still skip anything in `docs/nonmatching.md`. If the target is stuck, record it there and take the
  next function, then the next row, instead of leaving a gap in a unit.
- **Step 3 (Claim):** name a unit after its file's first function (`Game/fn_8007891C.cpp`); a
  handler file keeps its source path (`Game/handlers/mission.cpp`). If the unit already exists,
  extend its range rather than starting a new one. **When the range reaches an already-matched
  unit, merge it in:** move that unit's source into this one, delete its `splits.txt` block, its
  `configure.py` entry and its source file, and require `main.dol: OK` as for any match. The rows
  name the units they absorb.
- **Names:**
  - The class names in `docs/story.md` are the DOL's registration strings. Use them as struct type
    names in source (`struct cSpawnPeon`).
  - Keep function symbols `fn_XXXXXXXX` and `extern "C"` until a method's real name is known;
    renaming later means redoing every mangled symbol.
  - A handler takes its GCC 2.95 mangled name when it matches, as the `control.cpp` handlers did
    (`docs/versus.md` section 1).
  - Don't give leaf accessors guessed names: keep `fn_XXXXXXXX` until they get renamed in one pass.
- **Class layouts** must keep the base class's vptr at +0x24 and start derived fields at +0x28
  (`docs/story.md` section 4.1).

## Recording what you learn

`docs/matching_notes.md` and `docs/nonmatching.md` rules from decomp-next still apply. In addition:

- When matching a function tells you what a base slot, class field, profile field, chronicle global
  or mission flag does, update the tables in `docs/story.md`, and remove the item from its
  "Open Questions" if it is settled.
- Facts about the `.nsc` record go in `docs/characters.md` section 4.
- Facts about the AI (the actor and AI classes call into it) go in `docs/ai.md`.
- A file format you decode (`.nsd`, `.nhg`) goes in a tool's docstring under `tools/`, with the tool,
  as `tools/nottool.py` does.

Keep entries factual and short; mark guesses as guesses.

**`docs/story.md` is a reference, not a log, and every line you add is a line every future run
pays for.** So write only what is expensive to re-derive from the DOL:

- **Do** record field types and meanings, confirmed file boundaries and why they are confirmed,
  which blocker stops a row, and facts about code that is still *unmatched*.
- **Don't** record what a matched function does: its source is the documentation, and
  `configure.py` is the authority on which units are matched. Don't narrate the work either: no
  "is now matched as X", no fuzzy percentages, no changelog of previous sessions. Git log holds that.
- When you finish a function, check whether that makes an existing passage redundant, and **delete
  it**. Updating the doc means pruning it as often as adding to it.
- Prefer a table row to a paragraph, and keep each row's status to one line.

**The notes go in `docs/`, not at the top of the unit.** Cap a source file's header comment at three
lines: what the function does, and which doc holds the rest (`docs/story.md row N`). One line each is
worth spending on a local fact the next editor can't get from the docs: the `.rodata` pool the unit
owns, a symbol it renamed, a struct field only this file explains. Comments inside the file are
one-liners; an offset in a struct is a trailing `// +0xNN`.
Keep them minimal: a function symbol (`// fn_8044B694`), a struct offset, or a literal's text is fine; an
explanation of *why* the source is shaped as it is belongs in `docs/matching_notes.md`, and a restatement of
what the code does is not needed. Don't repeat a comment that another unit's header already carries.

## Report

Use decomp-next's report. Add one line on what the work taught about story mode or the scripts,
if anything (for example which base slot turned out to be the per-frame update), and one line naming the section 6
row you worked and the next open target. If every row is done, or every open one is stuck, say that
the target order needs a planning session. Then give the commit message as decomp-next specifies.
