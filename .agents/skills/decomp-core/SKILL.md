---
name: decomp-core
description: Run decomp-next aimed at the engine's core layer in this GameCube decomp (mnroi, GVLE69). It picks the next open target in docs/core.md's target order (the shared classes' inline functions in the tail of .text, the memory manager, the file layer and CLASH.BIG, BufferAllocator, the VFS, the containers, stdVar, the geometry helpers, pad input, the system monitor) and byte-matches it. Use when asked to run "/decomp-core" or to decompile the core, Std, memory, file or container code.
---

# decomp-core: decomp-next, aimed at the core layer

This is a wrapper. Read `.agents/skills/decomp-next/SKILL.md` and follow it exactly: its
preconditions, loop, rules, notes and report all apply. Only the steps below change.

## Changes to decomp-next

- **Before step 1, read `docs/core.md` section 6 (Target Order) only**: the table and the row you
  land on. That is enough to pick a target. Read the other sections *on demand*, once you know what
  you are working on: section 2 for the file map and edges, section 4 for the open-file table,
  search folders, memory manager and vtables, section 5 for the tail. Don't read the file end to end.
- **Step 1 (Choose):** if the user named a function or unit, work that one. Otherwise take the
  first row of `docs/core.md` section 6 that is not done (check `configure.py`), and in it the next
  function after the unit's current `.text` end, so that the unit grows as one contiguous range
  from the row's first function. This replaces decomp-next's "next to an already-matched unit"
  rule. Some rows have a different shape:
  - **Rows whose next action says "identify"**: settle the file edge from the code, its `.rodata`
    (a file's pools are one run, in `.text` order), the `.ctors` entries, the function-end pair
    (`tools/pair_map.py`) and the callers. Write the edge and its evidence into `docs/core.md`
    section 2, and remove the question from section 7, before matching.
  - **The linkonce rows** (1, the tail part of 9, 18 and 19): one small unit per run of neighbours,
    like `Game/fn_8042FB28.cpp`, rather than one unit for the whole range. A function whose float
    pool sits in another file's `.rodata` takes `extern_pool=<address of its first literal>` on its
    `Object` (`docs/prodg.md`, "Inline functions and the tail of `.text`"). In row 19, claim only
    the functions section 5's rule classes as generic; leave the HUD-only and render-only ones.
  - **Files with a `_GLOBAL_.I`**: the unit that claims it gets the `.ctors` word automatically,
    and it claims the `.bss`/`.sbss` range its static initializer's objects settle, as
    `Game/handlers/mainmenu.cpp` does.
  - **The gap rows** (16 and 17): extend the matched neighbour whose file the function belongs to,
    or merge (below). Several neighbours in the tuning area are C (`.c`); keep a unit's language.

  Still skip anything in `docs/nonmatching.md`. If the target is stuck, record it there and take the
  next function, then the next row, instead of leaving a gap in a unit.
- **Step 3 (Claim):** name a unit after its file's first function (`Game/fn_801ABA48.cpp`), or
  after its source path when the DOL gives one (`Std/BufferAllocator.cpp`,
  `Std/stdBigHashedVFS.cpp`; register it in the `Game` library). If the unit already exists,
  extend its range rather than starting a new one. **When the range reaches an already-matched
  unit of the same file, merge it in:** move that unit's source into this one, delete its
  `splits.txt` block, its `configure.py` entry and its source file, repoint the docs and tool
  docstrings that cite it (`grep -rn` its path in `docs/` and `tools/`), and require
  `main.dol: OK` as for any match.
- **Names:**
  - Keep function symbols `fn_XXXXXXXX` and `extern "C"` until row 20; renaming later means redoing
    every unit that references them. Names dtk already gives (`__builtin_new`, `__6Vector`,
    `__5ColorUcUcUcUc`) stay as they are.
  - The stdio names in `docs/core.md` section 4 (`fopen`, `fread`) are guesses for the docs only.
    Don't give them to symbols, and don't declare them with the libc names in source.
  - **Declare classes locally in each unit**, as the matched units declare `Vector`. Don't add a
    shared header: its inline functions would emit linkonce copies into every unit that includes it.
- **Renames that ripple:** a matched unit that references a symbol you rename by its old name
  breaks the link. After a rename or a resize of a symbol other units use, run
  `build/tools/objdiff-cli report generate --config functionRelocDiffs=all -o <scratch file>` and
  check nothing drops below 100% (`docs/workflow.md` section 3).

## Recording what you learn

`docs/matching_notes.md` and `docs/nonmatching.md` rules from decomp-next still apply. In addition:

- When matching a function tells you what a record field, heap, file type or class slot does,
  update the tables in `docs/core.md` section 4, and remove the item from section 7 if it is
  settled.
- Facts about the `.BIG`/`.BH` format go in the docstrings of `tools/bigtool.py` or `tools/nbig.py`.
- Facts about the tuning code go in `docs/characters.md` section 4.

Keep entries factual and short; mark guesses as guesses.

**`docs/core.md` is a reference, not a log, and every line you add is a line every future run
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
lines: what the function does, and which doc holds the rest (`docs/core.md row N`). One line each is
worth spending on a local fact the next editor can't get from the docs: the `.rodata` pool the unit
owns, a symbol it renamed, a struct field only this file explains. Comments inside the file are
one-liners; an offset in a struct is a trailing `// +0xNN`.
Keep them minimal: a function symbol (`// fn_801A8B60`), a struct offset, or a literal's text is fine; an
explanation of *why* the source is shaped as it is belongs in `docs/matching_notes.md`, and a restatement of
what the code does is not needed. Don't repeat a comment that another unit's header already carries.

## Report

Use decomp-next's report. Add one line on what the work taught about the core layer, if anything
(for example what a field of the open-file record holds), and one line naming the section 6 row you
worked and the next open target. If every row is done, or every open one is stuck, say that the
target order needs a planning session. Then give the commit message as decomp-next specifies.
