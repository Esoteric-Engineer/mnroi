#!/usr/bin/env python3
"""Print the motion sets Motions/<name>.nms (docs/characters.md section 4).

Usage (from repo root):
  python3 tools/nmstool.py list [substring]   Every motion of every set, by overlay
  python3 tools/nmstool.py check              Parse every set the way the game does

Text, read by fn_80090034 (Game/fn_8008FF48.cpp) one line at a time (fgets, 0x1FF bytes).
A line whose first byte is ';' is a comment. Tokens are split on " \\r\\t\\n" (strtok):
  numoverlays ...         ignored
  basedon <base>          male, female, brute, female2, humanpeon or brutepeon: the preloaded
                          set whose overlays fill in the states this file leaves out
  overlay [<name>]        closes the current overlay and starts the next (6 at most, the
                          first is unnamed); no name gives "ERROR__NONAME"
  <State> <file.nad> opt  one motion: the state name goes through fn_8008F3B8 (0 = unknown,
                          line skipped), the .nad through fn_80198DE4 (missing = skipped)
Options, until the line ends or a token starts with ';':
  fps <f>                 speed = max(f, 1) / 30 (default 1.0)
  dist <f>                clamped to [-10, 1000] (default 0)
  move <f>                stored as 1 / f, or 0 when f <= 0 (default 0)
  <flag>                  ORed in through the name table lbl_8054FD90 (fn_80090810); an unknown
                          name is ignored. The default flags come from lbl_8054F7C0[state].
A keyword with no value after it makes the game call atof(NULL); check reports that.
"""

import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from nvbtool import read_big_index, read_entry  # noqa: E402

DELIM = " \r\t\n"
BASES = ("male", "female", "brute", "female2", "humanpeon", "brutepeon")
MAX_OVERLAYS = 6
BUFFER = 0x174  # motions per overlay: lbl_8054FE10 is 0x22E0 bytes of 0x18


def tokens(line):
    out, cur = [], ""
    for c in line:
        if c in DELIM:
            if cur:
                out.append(cur)
            cur = ""
        else:
            cur += c
    if cur:
        out.append(cur)
    return out


def lines(data):
    """fgets(0x1FF) until EOF; a line read up to EOF itself is dropped (as the parser does)."""
    off = 0
    while off < len(data):
        end = data.find(b"\n", off)
        end = len(data) if end < 0 else end + 1
        end = min(end, off + 0x1FE)
        if end >= len(data) and not data.endswith(b"\n"):
            return
        yield data[off:end].decode("latin-1"), end - off == 0x1FE
        off = end


def parse(data):
    """Returns (base, overlays, problems); overlays is a list of (name, [motion, ...])."""
    base, problems = None, []
    overlays = [("", [])]
    for no, (line, cut) in enumerate(lines(data), 1):
        if cut:
            problems.append("line %d: longer than 0x1FE bytes, split by fgets" % no)
        if line[:1] == ";":
            continue
        tok = tokens(line)
        if not tok or tok[0].lower() == "numoverlays":
            continue
        key = tok[0].lower()
        if key == "basedon":
            if len(tok) < 2 or tok[1].lower() not in BASES:
                problems.append("line %d: basedon %r keeps the previous base" % (no, tok[1:2]))
            else:
                base = tok[1].lower()
            continue
        if key == "overlay":
            if len(overlays) >= MAX_OVERLAYS:
                problems.append("line %d: overlay %d is past the 6 the set holds" % (no, len(overlays) + 1))
            overlays.append((tok[1] if len(tok) > 1 else "ERROR__NONAME", []))
            continue
        if len(tok) < 2:
            continue
        motion = {"state": tok[0], "anim": tok[1], "fps": None, "dist": None, "move": None, "flags": []}
        i = 2
        while i < len(tok) and tok[i][0] != ";":
            opt = tok[i].lower()
            if opt in ("fps", "dist", "move"):
                if i + 1 >= len(tok):
                    problems.append("line %d: %s has no value (atof(NULL))" % (no, opt))
                    break
                motion[opt] = tok[i + 1]
                i += 2
                continue
            motion["flags"].append(tok[i])
            i += 1
        overlays[-1][1].append(motion)
        if len(overlays[-1][1]) > BUFFER:
            problems.append("line %d: more than 0x%x motions in one overlay" % (no, BUFFER))
    return base, overlays, problems


def nms_entries(index, sub=None):
    names = sorted(n for n in index if n.lower().endswith(".nms"))
    if sub:
        names = [n for n in names if sub.lower() in n]
    return names


def cmd_list(index, sub):
    for name in nms_entries(index, sub):
        base, overlays, problems = parse(read_entry(index, name))
        print("%s: basedon %s, %d overlays" % (name, base, len(overlays)))
        for oname, motions in overlays:
            print("  overlay %r: %d motions" % (oname, len(motions)))
            for m in motions:
                opts = " ".join("%s %s" % (k, m[k]) for k in ("fps", "dist", "move") if m[k])
                print("    %-28s %-36s %s %s" % (m["state"], m["anim"], opts, " ".join(m["flags"])))
        for p in problems:
            print("  ! " + p)


def cmd_check(index):
    entries = nms_entries(index)
    total, states, flags, bad = 0, set(), set(), 0
    for name in entries:
        _, overlays, problems = parse(read_entry(index, name))
        for _, motions in overlays:
            total += len(motions)
            for m in motions:
                states.add(m["state"].lower())
                flags.update(f.lower() for f in m["flags"])
        for p in problems:
            print("%-36s %s" % (name, p))
        bad += bool(problems)
    print("%d motion sets, %d motions, %d state names, %d flag names: %s" %
          (len(entries), total, len(states), len(flags),
           "all parse cleanly" if not bad else "%d with problems" % bad))
    print("flags: " + " ".join(sorted(flags)))
    sys.exit(0 if not bad else 1)


def main(argv):
    if len(argv) < 2 or argv[1] not in ("list", "check"):
        raise SystemExit(__doc__)
    index = read_big_index()
    if argv[1] == "check":
        cmd_check(index)
    cmd_list(index, argv[2] if len(argv) > 2 else None)


if __name__ == "__main__":
    main(sys.argv)
