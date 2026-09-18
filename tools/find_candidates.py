#!/usr/bin/env python3
"""List small/frameless leaf functions in not-yet-claimed code.

Usage (from repo root, after a build):
    python3 tools/find_candidates.py [--start ADDR] [--end ADDR] [--min N] [--max N]

Disassembles every auto-generated .text object and prints each function with no calls and no stack frame, sorted by address.
Defaults to the SDK range, since game code was compiled with -O4 -inline auto.
"""
import argparse
import collections
import glob
import os
import re
import subprocess
import sys

OBJDUMP = "build/binutils/powerpc-eabi-objdump"
OBJ_GLOB = "build/GVLE69/obj/auto_*_text.o"

CALL_RE = re.compile(r"\b(bl|bctrl|blrl)\b")
FRAME_RE = re.compile(r"\b(stwu|stmw|mflr)\b")


def functions(path):
    """Yield (address, name, [instructions]) for each function in an auto-generated object."""
    # The section's base address is encoded in the filename, e.g. auto_01_800034A0_text.o.
    base = int(re.search(r"auto_\d+_([0-9A-Fa-f]{8})_text", path).group(1), 16)
    out = subprocess.run([OBJDUMP, "-d", "--no-show-raw-insn", path],
                         capture_output=True, text=True, check=True).stdout
    funcs = collections.OrderedDict()
    cur = None
    for line in out.splitlines():
        m = re.match(r"^([0-9a-f]+) <(.+)>:", line)
        if m:
            cur = (base + int(m.group(1), 16), m.group(2))
            funcs[cur] = []
            continue
        m = re.match(r"^\s+[0-9a-f]+:\t(.*)$", line)
        if m and cur:
            funcs[cur].append(m.group(1).strip())
    for (addr, name), ins in funcs.items():
        yield addr, name, ins


def main():
    p = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    p.add_argument("--start", type=lambda s: int(s, 16), default=0x80169000, help="hex, default SDK start")
    p.add_argument("--end", type=lambda s: int(s, 16), default=0xFFFFFFFF, help="hex, default no limit")
    p.add_argument("--min", type=int, default=3, help="minimum instruction count (default 3)")
    p.add_argument("--max", type=int, default=16, help="maximum instruction count (default 16)")
    args = p.parse_args()

    paths = sorted(glob.glob(OBJ_GLOB))
    if not paths or not os.path.exists(OBJDUMP):
        sys.exit("No auto-generated objects or objdump found. Run `ninja` and `ninja build/binutils` first.")

    for path in paths:
        for addr, name, ins in functions(path):
            if not (args.start <= addr < args.end and args.min <= len(ins) <= args.max):
                continue
            text = " ".join(ins)
            if CALL_RE.search(text) or FRAME_RE.search(text):
                continue
            globals_ = "  (loads globals)" if re.search(r"\blis\b", text) else ""
            print("%08X  %-32s %2d%s" % (addr, name, len(ins), globals_))


if __name__ == "__main__":
    main()
