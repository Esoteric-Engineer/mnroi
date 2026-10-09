#!/usr/bin/env python3

###
# Index and lookup for docs/matching_notes.md, so a run reads the symptom lines instead of the whole file.
#
# Usage:
#   python3 tools/notes_index.py              One line per entry: number and bold symptom
#   python3 tools/notes_index.py 12 40 41     Full text of those entries
#   python3 tools/notes_index.py -g mulli     Full text of every entry containing the text (case-insensitive)
###

import re
import sys
from typing import List, Tuple

NOTES = "docs/matching_notes.md"


def load() -> List[Tuple[str, str]]:
    entries: List[Tuple[str, str]] = []
    section = ""
    body: List[str] = []

    def flush() -> None:
        text = "\n".join(body).rstrip()
        if text:
            entries.append((section, text))
        body.clear()

    for line in open(NOTES, encoding="utf-8").read().split("\n"):
        if line.startswith("## "):
            flush()
            section = line[3:]
        elif line.startswith("- "):
            flush()
            body.append(line)
        elif body:
            body.append(line)
    flush()
    return entries


def lead(text: str) -> str:
    flat = re.sub(r"\s+", " ", text)
    m = re.match(r"- \*\*(.+?)\*\*", flat)
    return m.group(1) if m else flat[2:120]


def main() -> int:
    entries = load()
    args = sys.argv[1:]

    if not args:
        last = None
        for i, (section, text) in enumerate(entries, 1):
            if section != last:
                print(f"## {section}")
                last = section
            print(f"{i}\t{lead(text)}")
        return 0

    if args[0] == "-g":
        needle = " ".join(args[1:]).lower()
        hits = [i for i, (_, t) in enumerate(entries, 1) if needle in t.lower()]
    else:
        hits = [int(a) for a in args]

    for i in hits:
        if not 1 <= i <= len(entries):
            print(f"no entry {i} (1-{len(entries)})", file=sys.stderr)
            return 1
        print(f"[{i}]\n{entries[i - 1][1]}\n")
    if not hits:
        print("no match", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
