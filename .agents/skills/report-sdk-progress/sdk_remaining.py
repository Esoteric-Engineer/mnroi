#!/usr/bin/env python3
"""Report how much SDK code is still unsplit, by comparing symbols.txt to splits.txt.

Scans both SDK clusters by default (0x80169000-0x80196884 and 0x803FF3B0-0x804114EC, see
docs/sdk_libraries.md). Pass --lo/--hi to scan a single custom range instead.

Usage: sdk_remaining.py [--version GVLE69] [--lo 0x80169000 --hi 0x80196884] [--list]
"""
import argparse
import collections
import re
from pathlib import Path

ap = argparse.ArgumentParser()
ap.add_argument("--version", default="GVLE69")
ap.add_argument("--lo", type=lambda x: int(x, 0), default=None)
ap.add_argument("--hi", type=lambda x: int(x, 0), default=None)
ap.add_argument("--list", action="store_true", help="also list unsplit fn_ functions")
args = ap.parse_args()
CLUSTERS = [(0x80169000, 0x80196884), (0x803FF3B0, 0x804114EC)]
if args.lo is not None or args.hi is not None:
    CLUSTERS = [(args.lo if args.lo is not None else CLUSTERS[0][0], args.hi if args.hi is not None else CLUSTERS[0][1])]

cfg = Path("config") / args.version

# splits: lib -> [(start, end)] for .text, keyed by path prefix (Dolphin/os, Runtime.PPCEABI.H, ...)
splits, cur = [], None
for line in (cfg / "splits.txt").read_text().splitlines():
    m = re.match(r"^(\S+):$", line)
    if m:
        cur = m[1]
        continue
    m = re.search(r"\.text\s+start:0x([0-9A-F]+) end:0x([0-9A-F]+)", line)
    if m and cur:
        splits.append((int(m[1], 16), int(m[2], 16), cur))
splits.sort()

# text functions from symbols.txt
syms = []
for line in (cfg / "symbols.txt").read_text().splitlines():
    m = re.match(r"(\S+) = \.text:0x([0-9A-F]+); // type:function(?: size:0x([0-9A-F]+))?", line)
    if m:
        syms.append((int(m[2], 16), m[1], int(m[3] or "0", 16)))


def is_split(addr):
    return any(a <= addr < b for a, b, _ in splits)


in_range = [s for s in syms if any(lo <= s[0] < hi for lo, hi in CLUSTERS)]
unsplit = [s for s in in_range if not is_split(s[0])]
named = [s for s in unsplit if not s[1].startswith("fn_")]
anon = [s for s in unsplit if s[1].startswith("fn_")]

lib = lambda p: p.rsplit("/", 1)[0]
per_lib = collections.Counter(lib(p) for a, b, p in splits)

print("Ranges: " + ", ".join(f"{lo:#x}-{hi:#x}" for lo, hi in CLUSTERS) + f": {len(in_range)} functions")
for lo, hi in CLUSTERS:
    n = [s for s in unsplit if lo <= s[0] < hi]
    print(f"  {lo:#x}-{hi:#x}: {sum(1 for s in in_range if lo <= s[0] < hi)} functions, {len(n)} unsplit ({sum(s[2] for s in n)} bytes)")
print(f"  split:   {len(in_range) - len(unsplit)}")
print(f"  unsplit: {len(unsplit)} ({sum(s[2] for s in unsplit)} bytes)")
print(f"    named (real SDK names): {len(named)}")
print(f"    anonymous fn_*:         {len(anon)}")
print(f"Split files per library: {dict(per_lib)}")
print(f"Split .text span: {splits[0][0]:#x}-{max(b for _, b, _ in splits):#x}")
print("\nNamed but unsplit:")
for a, n, s in named:
    print(f"  {a:#x} {n} ({s:#x})")
if args.list:
    print("\nAnonymous unsplit:")
    for a, n, s in anon:
        print(f"  {a:#x} {n} ({s:#x})")
