#!/usr/bin/env python3
"""List the functions that read tuning fields, best decompilation target first
(docs/versus.md section 5, rows 20, 21 and 28; the fields are docs/characters.md section 4).

Usage (from repo root, after a build: it reads build/GVLE69/asm):
  python3 tools/nvbreaders.py CLASS [-m SIZE]  Unclaimed readers of PLAYER or GLOBALS fields, ranked;
                                               -m leaves out functions of SIZE bytes or more
  python3 tools/nvbreaders.py CLASS -a         Every reader, claimed ones too, in address order
  python3 tools/nvbreaders.py CLASS field ID   Every function that reads one field

A reader is a call of one of the getters below with the id in r4: `li r4, <id>`, or `<base> + i`
(`addi r0, rN, <base>` then `mr r4, r0`), printed as `<base>+` and counted as the one field at the
base, since the run's length is not in the call. The ranking is greedy: each line is the unclaimed
function with the most not-yet-covered fields per byte, where a field is covered once a function
in splits.txt, or a line above, reads it.

  PLAYER   fn_800B1884 (float), fn_800B18EC (int), fn_800ACD20 (name or string): (entity, id)
  GLOBALS  fn_80433D20 (float), fn_80433D70 (int): (record, id, slot), called on lbl_8066C6C8
"""
import bisect
import glob
import re
import sys

ASM = "build/GVLE69/asm"
SYMBOLS = "config/GVLE69/symbols.txt"
SPLITS = "config/GVLE69/splits.txt"
WRAPPERS = ("fn_800B1884", "fn_800B18EC", "fn_800ACD20")
GETTERS = {"PLAYER": WRAPPERS, "GLOBALS": ("fn_80433D20", "fn_80433D70")}


def load_asm():
    """{address: instruction text}. The directory keeps stale files, so key by address."""
    lines = {}
    for path in glob.glob(ASM + "/**/*.s", recursive=True):
        for line in open(path, errors="ignore"):
            m = re.match(r"/\* ([0-9A-F]{8}) [0-9A-F]{8}  .. .. .. .. \*/\s+(.*)", line)
            if m:
                lines[int(m.group(1), 16)] = m.group(2).strip()
    if not lines:
        raise SystemExit("no disassembly under %s: build first" % ASM)
    return lines


def load_functions():
    out = []
    for line in open(SYMBOLS):
        m = re.match(r"(\S+) = \.text:0x([0-9A-F]+); // .*type:function.*?size:0x([0-9A-F]+)", line)
        if m:
            out.append((int(m.group(2), 16), int(m.group(3), 16), m.group(1)))
    out.sort()
    return out


def load_claims():
    out = []
    for line in open(SPLITS):
        m = re.match(r"\s+\.text\s+start:0x([0-9A-F]+) end:0x([0-9A-F]+)", line)
        if m:
            out.append((int(m.group(1), 16), int(m.group(2), 16)))
    out.sort()
    return out


def site_id(lines, addr):
    """(id, indexed) for the call at addr: the constant in r4, or the base of `base + i`.
    (None, False) when r4 is neither."""
    for k in range(1, 12):
        text = lines.get(addr - 4 * k, "")
        m = re.match(r"li r4, (-?0x[0-9a-f]+|-?\d+)$", text)
        if m:
            return int(m.group(1), 0), False
        if text == "mr r4, r0":
            for j in range(k + 1, k + 8):
                prev = lines.get(addr - 4 * j, "")
                m = re.match(r"addi r0, r\d+, (0x[0-9a-f]+|\d+)$", prev)
                if m:
                    return int(m.group(1), 0), True
                if re.match(r"(?!st|cmp)\w+\.? r0,", prev) or prev.startswith("bl "):
                    break
            return None, False
        if text.startswith("bl ") or re.match(r"(mr|addi|lwz|lbz|lhz) r4,", text):
            return None, False
    return None, False


def main(argv):
    if len(argv) < 2 or argv[1].upper() not in GETTERS:
        raise SystemExit(__doc__)
    cls = argv[1].upper()
    lines = load_asm()
    functions = load_functions()
    starts = [f[0] for f in functions]
    claims = load_claims()
    claim_starts = [c[0] for c in claims]

    def owner(addr):
        return functions[bisect.bisect_right(starts, addr) - 1]

    def claimed(addr):
        i = bisect.bisect_right(claim_starts, addr) - 1
        return i >= 0 and claims[i][0] <= addr < claims[i][1]

    readers = {}  # function -> set of ids, the bases of indexed reads included
    bases = {}    # function -> set of ids that are such bases
    loose = {}    # function -> call sites whose id is neither
    for addr, text in lines.items():
        if not text.startswith("bl ") or text.split()[1] not in GETTERS[cls]:
            continue
        f = owner(addr)
        if f[2] in WRAPPERS:
            continue
        fid, indexed = site_id(lines, addr)
        if fid is None:
            loose[f] = loose.get(f, 0) + 1
            continue
        readers.setdefault(f, set()).add(fid)
        if indexed:
            bases.setdefault(f, set()).add(fid)

    def show(f, ids):
        return " ".join("%d+" % i if i in bases.get(f, ()) else str(i) for i in sorted(ids))

    if argv[2:3] == ["field"]:
        fid = int(argv[3], 0)
        for f in sorted(readers):
            near = [b for b in bases.get(f, ()) if b < fid < b + 8]
            if fid in readers[f] or near:
                print("%s  0x%X%s%s" % (f[2], f[1], "" if fid in readers[f] else "  (may reach it: indexes from %d)" % near[0],
                                        "  (claimed)" if claimed(f[0]) else ""))
        return
    if argv[2:3] == ["-a"]:
        for f in sorted(set(readers) | set(loose)):
            print("%s  0x%-5X %s%s%s" % (f[2], f[1], show(f, readers.get(f, ())),
                                          "  +%d computed" % loose[f] if f in loose else "",
                                          "  (claimed)" if claimed(f[0]) else ""))
        return

    covered = set()
    for f, ids in readers.items():
        if claimed(f[0]):
            covered |= ids
    every = set().union(*readers.values()) if readers else set()
    cap = int(argv[3], 0) if argv[2:3] == ["-m"] else None
    todo = {f: ids for f, ids in readers.items() if not claimed(f[0]) and (cap is None or f[1] < cap)}
    print("%s: %d fields have a reader, %d of them in claimed code; %d unclaimed readers%s"
          % (cls, len(every), len(covered), len(todo), " under 0x%X bytes" % cap if cap else ""))
    while todo:
        best = max(todo, key=lambda f: (len(todo[f] - covered) / f[1], -f[0]))
        new = todo.pop(best) - covered
        if not new:
            break
        covered |= new
        print("%s  0x%-5X +%-2d (%d of %d)  %s"
              % (best[2], best[1], len(new), len(covered), len(every), show(best, new)))
    if todo:
        print("%d more unclaimed readers add no new field (list them with -a)" % (len(todo) + 1))


if __name__ == "__main__":
    main(sys.argv)
