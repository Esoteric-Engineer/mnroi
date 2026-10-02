#!/usr/bin/env python3

###
# Renames an MWCC object's .rodata.1 section (and .rela.rodata.1) to .rodata, in place.
#
# MWCC's predefined .rodata is always 8-byte aligned, but the GCC-built runtime's read-only data only needs 4, so those units declare it as .rodata.1 instead.
# This folds it back into .rodata so it links in order with the ProDG objects. Objects without .rodata.1 are untouched.
#
# Usage:
#   python3 tools/fold_rodata.py build/GVLE69/src/file.o
###

import argparse
import struct

OLD = b".rodata.1\0"
NEW = b".rodata\0\0\0"


def fold_rodata(path: str) -> None:
    with open(path, "r+b") as f:
        data = bytearray(f.read())
        if data[:4] != b"\x7fELF" or data[4] != 1 or data[5] != 2:
            raise SystemExit(f"{path}: not a 32-bit big-endian ELF")
        (e_shoff,) = struct.unpack_from(">I", data, 0x20)
        e_shentsize, e_shnum, e_shstrndx = struct.unpack_from(">HHH", data, 0x2E)
        shstrtab = e_shoff + e_shstrndx * e_shentsize
        offset, size = struct.unpack_from(">II", data, shstrtab + 0x10)
        names = data[offset : offset + size]
        if OLD not in names:
            return
        data[offset : offset + size] = names.replace(OLD, NEW)
        f.seek(0)
        f.write(data)


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Rename an MWCC object's .rodata.1 section to .rodata, in place"
    )
    parser.add_argument("object", help="MWCC object to fix up in place")
    args = parser.parse_args()
    fold_rodata(args.object)


if __name__ == "__main__":
    main()
