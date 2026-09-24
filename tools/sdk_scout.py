#!/usr/bin/env python3
"""Scout the unidentified SDK functions and maintain docs/sdk_queue.tsv.

Usage (from repo root):
    python3 tools/sdk_scout.py queue            # refresh docs/sdk_queue.tsv (never overwrites hand-written notes)
    python3 tools/sdk_scout.py align [--all]    # print name proposals from ac-decomp
    python3 tools/sdk_scout.py hw [LO HI]       # which hardware blocks each function touches
    python3 tools/sdk_scout.py info ADDR        # callees, callers, hardware for one function

The proposals come from aligning our function sizes/order against the sibling ac-decomp (same
Dolphin SDK build) between functions both projects already name, so they are guesses: confirm the
code shape in ac-decomp before renaming. Library ranges live in LIBS below and are documented in
docs/sdk_libraries.md; keep the two in sync.
"""
import argparse
import bisect
import collections
import os
import re
import struct
import sys

SYMBOLS = "config/GVLE69/symbols.txt"
SPLITS = "config/GVLE69/splits.txt"
DOL = "orig/GVLE69/sys/main.dol"
QUEUE = "docs/sdk_queue.tsv"
AC_DIR = os.environ.get("AC_DECOMP", "../ac-decomp/config/GAFE01_00")
LO, HI = 0x80169000, 0x80196884  # confirmed SDK range (first cluster), see docs/sdk_libraries.md

# (start, end, our library, ac-decomp libraries it may match, or None to skip matching)
LIBS = [
    (0x80169000, 0x8016D000, "os", {"os"}),
    (0x8016D000, 0x8017A5CC, "libc", None),
    (0x8017A5CC, 0x801814F4, "os", {"os"}),
    (0x801814F4, 0x80181708, "exi", {"exi"}),
    (0x80181708, 0x80183070, "si", {"si"}),
    (0x80183070, 0x8018315C, "db", {"db"}),
    (0x8018315C, 0x80187B3C, "dvd", {"dvd"}),
    (0x80187B3C, 0x80189C10, "vi", {"vi"}),
    (0x80189C10, 0x8018B624, "pad", {"pad"}),
    (0x8018B624, 0x8018BF08, "ai", {"ai"}),
    (0x8018BF08, 0x80193E54, "gx", {"gx"}),
    (0x80193E54, 0x80195440, "exi", {"exi"}),
    (0x80195440, 0x80195E04, "exi", {"exi"}),
    (0x80195E04, 0x80196194, "odenotstub", {"odenotstub"}),
    (0x80196194, 0x80196884, "odemuexi2", {"OdemuExi2"}),
]
HW = {0x0: "CP", 0x1000: "PE", 0x2000: "VI", 0x3000: "PI", 0x4000: "MI", 0x5000: "DSP/AR",
      0x6000: "DVD", 0x6400: "SI", 0x6800: "EXI", 0x6C00: "AI", 0x8000: "FIFO"}
HW_SPAN = {0x6000: 0x400, 0x6400: 0x400, 0x6800: 0x400, 0x6C00: 0x400}

FUNC_RE = re.compile(r"(\S+) = \.text:(0x\w+); // type:function size:(0x\w+)")
ANON_RE = re.compile(r"(fn|lbl)_[0-9A-F]{8}$")


def load_funcs(path, lo=0, hi=1 << 32):
    out = {}
    for line in open(path):
        m = FUNC_RE.match(line)
        if m:
            a = int(m[2], 16)
            if lo <= a < hi:
                out.setdefault(a, (m[1], int(m[3], 16)))
    return sorted((a, n, s) for a, (n, s) in out.items())


def load_splits(path):
    spans, cur = [], None
    for line in open(path):
        if line.strip().endswith(":") and not line.startswith((" ", "\t")):
            cur = line.strip()[:-1]
        m = re.search(r"\.text\s+start:(0x\w+) end:(0x\w+)", line)
        if m and cur:
            spans.append((int(m[1], 16), int(m[2], 16), cur))
    return sorted(spans)


def lib_of(addr):
    for s, e, n, _ in LIBS:
        if s <= addr < e:
            return n
    return "unknown"


def ac_lib(spans, addr):
    for s, e, n in spans:
        if s <= addr < e:
            m = re.match(r"dolphin/(\w+)|(OdemuExi2)", n.replace("Dolphin/", "dolphin/"))
            return (m[1] or m[2]) if m else n
    return None


def propose():
    """Return {our_addr: (name, kind, ac_size)} for our unsplit anonymous functions."""
    ours = load_funcs(SYMBOLS, LO, HI)
    ac = load_funcs(os.path.join(AC_DIR, "symbols.txt"), 0x80078718, 0x800A9770)
    ac_spans = load_splits(os.path.join(AC_DIR, "splits.txt"))
    ours_spans = load_splits(SPLITS)
    named_ours = {n for _, n, _ in load_funcs(SYMBOLS) if not ANON_RE.match(n)}
    split = lambda a: any(s <= a < e for s, e, _ in ours_spans)
    ac_idx = {}
    for i, (_, n, _) in enumerate(ac):
        ac_idx.setdefault(n, i)
    anchors = [(i, ac_idx[n]) for i, (_, n, _) in enumerate(ours) if not ANON_RE.match(n) and n in ac_idx]
    tails, idx, prev = [], [], [-1] * len(anchors)
    for k, (_, j) in enumerate(anchors):  # longest monotone chain of anchors
        p = bisect.bisect_left(tails, j)
        if p == len(tails):
            tails.append(j); idx.append(k)
        else:
            tails[p] = j; idx[p] = k
        prev[k] = idx[p - 1] if p else -1
    k, chain = (idx[-1] if idx else -1), []
    while k != -1:
        chain.append(anchors[k]); k = prev[k]
    chain = [(-1, -1)] + chain[::-1] + [(len(ours), len(ac))]
    close = lambda a, b: abs(a - b) <= max(0x24, int(0.12 * max(a, b)))
    out = {}
    for (i0, j0), (i1, j1) in zip(chain, chain[1:]):
        O, A = ours[i0 + 1:i1], ac[j0 + 1:j1]
        n, m = len(O), len(A)
        score = lambda i, j: 2 if O[i][2] == A[j][2] else 1
        D = [[0] * (m + 1) for _ in range(n + 1)]
        for i in range(n - 1, -1, -1):
            for j in range(m - 1, -1, -1):
                D[i][j] = max(D[i + 1][j], D[i][j + 1],
                              D[i + 1][j + 1] + score(i, j) if close(O[i][2], A[j][2]) else 0)
        i = j = 0
        while i < n:
            if j < m and close(O[i][2], A[j][2]) and D[i][j] == D[i + 1][j + 1] + score(i, j):
                a, name, size = O[i]
                ok_libs = next((l for s, e, _, l in LIBS if s <= a < e), None)
                if (ANON_RE.match(name) and not split(a) and ok_libs
                        and ac_lib(ac_spans, A[j][0]) in ok_libs and A[j][1] not in named_ours):
                    out[a] = (A[j][1], "exact" if size == A[j][2] else "guess", A[j][2])
                i += 1; j += 1
            elif j < m and D[i][j] == D[i][j + 1] and D[i][j] != D[i + 1][j]:
                j += 1
            else:
                i += 1
    return out


# --- DOL access (for hw / info) ---------------------------------------------------------------
_dol = None


def word(a):
    global _dol
    if _dol is None:
        d = open(DOL, "rb").read()
        off = struct.unpack(">18I", d[0:72]); addr = struct.unpack(">18I", d[72:144])
        sz = struct.unpack(">18I", d[144:216])
        _dol = (d, off, addr, sz)
    d, off, addr, sz = _dol
    for i in range(18):
        if sz[i] and addr[i] <= a < addr[i] + sz[i]:
            o = off[i] + a - addr[i]
            return struct.unpack(">I", d[o:o + 4])[0]
    return None


def hw_hits(a, size):
    def cls(v):
        v &= 0xFFFF
        best = None
        for b in sorted(HW):
            if b <= v < b + HW_SPAN.get(b, 0x1000):
                best = HW[b]
        return best
    regs, hits = {}, collections.Counter()
    for p in range(a, a + size, 4):
        w = word(p)
        op, rd, ra, imm = w >> 26, (w >> 21) & 31, (w >> 16) & 31, w & 0xFFFF
        if op == 15 and ra == 0 and 0xCC00 <= imm <= 0xCC07:
            regs[rd] = imm
        elif op in (14, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 50, 52, 54) and ra in regs:
            if op == 14:
                regs[rd] = regs[ra]
            c = cls(imm)
            if c:
                hits[c] += 1
    return dict(hits)


def calls(a, size):
    for p in range(a, a + size, 4):
        w = word(p)
        if w >> 26 == 18 and w & 1 and not w & 2:  # bl
            disp = w & 0x03FFFFFC
            if disp & 0x02000000:
                disp -= 0x04000000
            yield p, (p + disp) & 0xFFFFFFFF


def cmd_hw(args):
    lo = int(args.lo, 16) if args.lo else LO
    hi = int(args.hi, 16) if args.hi else HI
    for a, n, s in load_funcs(SYMBOLS, lo, hi):
        h = hw_hits(a, s)
        if h:
            print(f"{a:08X} {n:30s} {s:#6x} {h}")


def cmd_info(args):
    addr = int(args.addr, 16)
    funcs = load_funcs(SYMBOLS)
    starts = [f[0] for f in funcs]
    i = bisect.bisect_right(starts, addr) - 1
    a, n, s = funcs[i]
    print(f"{a:08X} {n} size {s:#x} library {lib_of(a)}")
    print("hardware:", hw_hits(a, s) or "none")
    print("callees:")
    for p, t in calls(a, s):
        j = bisect.bisect_right(starts, t) - 1
        print(f"  {p:08X} -> {t:08X} {funcs[j][1] if funcs[j][0] == t else '?'}")
    print("callers:")
    seen = set()
    for fa, fn, fs in funcs:
        if fa < 0x80003100:
            continue
        for p, t in calls(fa, fs):
            if t == a and fn not in seen:
                seen.add(fn); print(f"  {p:08X} in {fn} ({lib_of(fa)})")


def cmd_align(args):
    for a, (name, kind, sz) in sorted(propose().items()):
        print(f"{a:08X} -> {name} ({kind}, ac size {sz:#x}) [{lib_of(a)}]")


NOTE_NAMED = "symbol already named; just needs split + match"
NOTE_LIBC = ("Newlib libc / libgcc, not MSL (see docs/sdk_libraries.md); names come from CFTKK-Decomp, "
             "code from upstream Newlib")
AUTO_NOTE_RE = re.compile(r"^ac-decomp size 0x[0-9a-f]+$")


def curated(note):
    """True if a person wrote this note, i.e. it is neither empty nor one the queue command generates."""
    return bool(note) and note not in (NOTE_NAMED, NOTE_LIBC) and not AUTO_NOTE_RE.match(note)


def cmd_queue(args):
    ours_spans = load_splits(SPLITS)
    split = lambda a: any(s <= a < e for s, e, _ in ours_spans)
    props = propose()
    old = {}
    if os.path.exists(QUEUE):
        for line in open(QUEUE).read().splitlines()[1:]:
            c = line.split("\t")
            if len(c) > 7:                            # stray tab inside the notes: fold it back in
                print(f"warning: {c[0]} has {len(c)} columns; merging the extras into notes", file=sys.stderr)
                c = c[:5] + ["; ".join(x for x in c[5:-1] if x)] + [c[-1]]
            if len(c) == 7:
                old[int(c[0], 16)] = c
    rows = {}
    for a, c in old.items():
        rows[a] = c
    for a, n, s in load_funcs(SYMBOLS, LO, HI):
        if n.startswith("lbl_") or (split(a) and a not in rows):
            continue
        c = rows.get(a) or [f"0x{a:08X}", "", "", lib_of(a), "unidentified", "", "open"]
        c[1] = f"0x{s:X}"
        c[3] = lib_of(a)
        if not ANON_RE.match(n):                      # already named in symbols.txt
            c[2] = n
            if c[6] == "open" and c[4] != "known" and not curated(c[5]):
                c[4], c[5] = "known", NOTE_NAMED
        elif c[4] == "unidentified" and not curated(c[5]):  # only re-guess rows nobody curated
            if lib_of(a) == "libc":
                c[5] = NOTE_LIBC
            elif a in props:
                name, kind, asz = props[a]
                c[2], c[4], c[5] = name, kind, f"ac-decomp size {asz:#x}"
        if split(a) and c[6] == "open":
            c[6] = "claimed"
        rows[a] = c
    with open(QUEUE, "w") as f:
        f.write("addr\tsize\tname\tlibrary\tconfidence\tnotes\tstatus\n")
        for a in sorted(rows):
            f.write("\t".join(rows[a][:7]) + "\n")
    cnt = collections.Counter((r[4], r[6]) for r in rows.values())
    print(f"{len(rows)} rows:", dict(cnt))


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("queue").set_defaults(fn=cmd_queue)
    p = sub.add_parser("align"); p.add_argument("--all", action="store_true"); p.set_defaults(fn=cmd_align)
    p = sub.add_parser("hw"); p.add_argument("lo", nargs="?"); p.add_argument("hi", nargs="?"); p.set_defaults(fn=cmd_hw)
    p = sub.add_parser("info"); p.add_argument("addr"); p.set_defaults(fn=cmd_info)
    args = ap.parse_args()
    if not os.path.exists(os.path.join(AC_DIR, "symbols.txt")) and args.cmd in ("align", "queue"):
        sys.exit(f"ac-decomp not found at {AC_DIR} (set AC_DECOMP to its config/GAFE01_00 dir)")
    args.fn(args)


if __name__ == "__main__":
    main()
