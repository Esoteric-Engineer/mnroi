#!/usr/bin/env python3
"""Report how much library (SDK, libc, runtime, SN stub) code and data is still unsplit.

Measures by address coverage, not by counting function symbols, so code that dtk only knows as
`lbl_` labels (no `type:function` symbol) is counted too. Checks:
  - .text of both library clusters (ranges and per-library labels come from tools/sdk_scout.py);
  - the whole .init section (boot/runtime code: __start and friends);
  - data sections: unsplit gaps inside the span that library data splits already cover;
  - build/<version>/report.json (if present): registered library units that don't fully match.

Usage (from repo root): sdk_remaining.py [--version GVLE69] [--lo 0x.. --hi 0x..] [--list]
"""
import argparse
import collections
import json
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, "tools")
import sdk_scout  # noqa: E402  (RANGES and LIBS are the single source of truth)

ap = argparse.ArgumentParser()
ap.add_argument("--version", default="GVLE69")
ap.add_argument("--lo", type=lambda x: int(x, 0), default=None)
ap.add_argument("--hi", type=lambda x: int(x, 0), default=None)
ap.add_argument("--list", action="store_true", help="also list every gap and every unsplit fn_ function")
args = ap.parse_args()
CLUSTERS = [(lo, hi) for lo, hi, _ in sdk_scout.RANGES]
if args.lo is not None or args.hi is not None:
    CLUSTERS = [(args.lo if args.lo is not None else CLUSTERS[0][0], args.hi if args.hi is not None else CLUSTERS[0][1])]

cfg = Path("config") / args.version
ANON = re.compile(r"^(fn|lbl|gap|pad)_[0-9A-F]{8}")

# splits: section -> [(start, end, unit)]
splits, cur = collections.defaultdict(list), None
for line in (cfg / "splits.txt").read_text().splitlines():
    m = re.match(r"^(\S+):$", line)
    if m:
        cur = m[1]
        continue
    m = re.search(r"^\s+(\.\S+)\s+start:0x([0-9A-F]+) end:0x([0-9A-F]+)", line)
    if m and cur:
        splits[m[1]].append((int(m[2], 16), int(m[3], 16), cur))
for v in splits.values():
    v.sort()

# symbols: (addr, name, section, type, size)
syms = []
for line in (cfg / "symbols.txt").read_text().splitlines():
    m = re.match(r"(\S+) = (\.\S+):0x([0-9A-F]+); // type:(\w+)(?:.*? size:0x([0-9A-F]+))?", line)
    if m:
        syms.append((int(m[3], 16), m[1], m[2], m[4], int(m[5] or "0", 16)))
syms.sort()


def gaps(section, lo, hi):
    """Address ranges in [lo, hi) that no split of `section` covers."""
    out, pos = [], lo
    for a, b, _ in splits.get(section, []):
        if b <= lo or a >= hi:
            continue
        if a > pos:
            out.append((pos, a))
        pos = max(pos, b)
    if pos < hi:
        out.append((pos, hi))
    return out


def by_lib(lo, hi):
    """Split [lo, hi) at sdk_scout.LIBS boundaries: [(lo, hi, lib)]."""
    cuts = sorted({lo, hi} | {x for s, e, _, _ in sdk_scout.LIBS for x in (s, e) if lo < x < hi})
    return [(a, b, sdk_scout.lib_of(a)) for a, b in zip(cuts, cuts[1:])]


def in_gaps(gs, a):
    return any(lo <= a < hi for lo, hi in gs)


def func_extents(section):
    return [(a, a + s) for a, _, sec, t, s in syms if sec == section and t == "function" and s]


def no_func_runs(section, lo, hi):
    """Runs in [lo, hi) that no sized function symbol covers (code dtk only knows as labels)."""
    out, pos = [], lo
    for a, b in func_extents(section):
        if b <= pos or a >= hi:
            continue
        if a > pos:
            out.append((pos, a))
        pos = max(pos, b)
    if pos < hi:
        out.append((pos, hi))
    return out


# --- .text of the library clusters -------------------------------------------------------------
text_gaps = [g for lo, hi in CLUSTERS for g in gaps(".text", lo, hi)]
funcs = [s for s in syms if s[2] == ".text" and s[3] == "function" and any(lo <= s[0] < hi for lo, hi in CLUSTERS)]
unsplit = [s for s in funcs if in_gaps(text_gaps, s[0])]
named = [s for s in unsplit if not ANON.match(s[1])]
anon = [s for s in unsplit if ANON.match(s[1])]
inside_func = lambda a: any(x <= a < y for x, y in func_extents(".text"))
named_labels = [s for s in syms if s[2] == ".text" and s[3] == "label" and not ANON.match(s[1])
                and in_gaps(text_gaps, s[0]) and not inside_func(s[0])]  # e.g. __cvt_fp2unsigned
lib_bytes = collections.Counter()
for a, b in text_gaps:
    for x, y, lib in by_lib(a, b):
        lib_bytes[lib] += y - x
label_only = [r for a, b in text_gaps for r in no_func_runs(".text", a, b) if r[1] - r[0] >= 0x40]

print(".text, library clusters (by address; lbl_-only code included)")
for lo, hi in CLUSTERS:
    g = [x for x in text_gaps if lo <= x[0] < hi]
    n = sum(1 for s in funcs if lo <= s[0] < hi)
    u = sum(1 for s in unsplit if lo <= s[0] < hi)
    print(f"  {lo:#x}-{hi:#x}: {sum(b - a for a, b in g)} of {hi - lo} bytes unsplit in {len(g)} gaps; "
          f"{u} of {n} function symbols unsplit")
print(f"  unsplit bytes by library: {dict(lib_bytes.most_common())}")
print(f"  unsplit function symbols: {len(unsplit)} ({len(named)} named, {len(anon)} anonymous fn_*)")
print(f"  code with no function symbol ({sum(b - a for a, b in label_only)} bytes in runs >= 0x40; needs function"
      " boundaries in symbols.txt before it can be split):")
for a, b in label_only:
    libs = ", ".join(sorted({lib for _, _, lib in by_lib(a, b)}))
    print(f"    {a:#x}-{b:#x}: {b - a} bytes [{libs}]")
print("  named but unsplit (functions, then named labels):")
for a, n, _, _, s in named:
    print(f"    {a:#x} {n} ({s:#x}) [{sdk_scout.lib_of(a)}]")
for a, n, *_ in named_labels:
    print(f"    {a:#x} {n} (label) [{sdk_scout.lib_of(a)}]")

# --- .init ---------------------------------------------------------------------------------------
init, init_unsplit = None, 0
dol = Path("orig") / args.version / "sys" / "main.dol"
if dol.exists():
    d = dol.read_bytes()[:0xE4]
    addrs, sizes = struct.unpack(">18I", d[0x48:0x90]), struct.unpack(">18I", d[0x90:0xD8])
    init = (addrs[0], addrs[0] + sizes[0])  # text0 is .init
if init:
    g = gaps(".init", *init)
    init_unsplit = sum(b - a for a, b in g)
    fs = [s for s in syms if s[2] == ".init" and s[3] == "function"]
    print(f"\n.init {init[0]:#x}-{init[1]:#x} (boot/runtime): {sum(b - a for a, b in g)} of {init[1] - init[0]} "
          f"bytes unsplit; functions: {', '.join(n for _, n, *_ in fs)}")

# --- data ------------------------------------------------------------------------------------------
lib_units = {u for a, b, u in splits.get(".text", []) if any(lo <= a < hi for lo, hi in CLUSTERS)}
lib_units |= {u for v in splits.values() for *_, u in v if u.startswith(("Dolphin/", "Runtime.PPCEABI.H/", "SN/"))}
print("\nData: unsplit gaps inside the span library data splits cover (probably library data)")
data_total = 0
for sec in sorted(splits):
    if sec in (".text", ".init"):
        continue
    own = [(a, b) for a, b, u in splits[sec] if u in lib_units]
    if not own:
        continue
    g = gaps(sec, own[0][0], max(b for _, b in own))
    n = sum(b - a for a, b in g)
    data_total += n
    print(f"  {sec:8} split {sum(b - a for a, b in own):6} bytes, gaps {n:6} bytes in {len(g)} runs"
          + (f": {', '.join(f'{a:#x}+{b - a:#x}' for a, b in g)}" if args.list else ""))
print(f"  total gaps: {data_total} bytes. Data of libraries outside that span (e.g. the second cluster's"
      " AX/CARD/VM/OS .data/.bss) is not located by this script.")

# --- registered units that don't fully match -------------------------------------------------------
report = Path("build") / args.version / "report.json"
if report.exists():
    bad = []
    for u in json.loads(report.read_text())["units"]:
        m, cats = u["measures"], u.get("metadata", {}).get("progress_categories", [])
        if "sdk" not in cats:
            continue
        code = (int(m.get("matched_code", 0)), int(m.get("total_code", 0)))
        data = (int(m.get("matched_data", 0)), int(m.get("total_data", 0)))
        if code[0] != code[1] or data[0] != data[1]:
            bad.append((u["name"].removeprefix("main/"), code, data))
    cat = next(c["measures"] for c in json.loads(report.read_text())["categories"] if c["id"] == "sdk")
    code_all = int(cat["total_code"]) + sum(b - a for a, b in text_gaps) + init_unsplit
    data_all = int(cat["total_data"]) + data_total
    print(f"\nAll library code (registered + unsplit .text + unsplit .init): {cat['matched_code']} of {code_all} "
          f"bytes matched = {100 * int(cat['matched_code']) / code_all:.2f}% (progress says {cat['matched_code_percent']:.2f}%,"
          " registered units only)")
    print(f"Library data: {cat['matched_data']} of at least {data_all} bytes matched = at most "
          f"{100 * int(cat['matched_data']) / data_all:.2f}% (second-cluster data not located, so not counted)")
    print(f"\nRegistered library units not fully matched (report.json): {len(bad)}")
    for n, c, dd in bad:
        what = [f"{k} {x}/{y}" for k, (x, y) in (("code", c), ("data", dd)) if x != y]
        print(f"  {n}: {', '.join(what)}")
else:
    print(f"\n({report} missing: run ninja first to list unmatched registered units)")

if args.list:
    print("\nAll .text gaps:")
    for a, b in text_gaps:
        print(f"  {a:#x}-{b:#x} ({b - a} bytes) [{', '.join(sorted({l for *_, l in by_lib(a, b)}))}]")
    print("\nAnonymous unsplit functions:")
    for a, n, _, _, s in anon:
        print(f"  {a:#x} {n} ({s:#x}) [{sdk_scout.lib_of(a)}]")
