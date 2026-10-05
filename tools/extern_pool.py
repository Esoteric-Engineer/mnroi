#!/usr/bin/env python3

###
# Points a ProDG object's .rodata float pool at the original DOL's copy of it, in place.
#
# For a unit whose pool sits in another file's .rodata, so it cannot be claimed (see docs/prodg.md).
# Checks each literal against the original from the given address on, retargets the pool's relocations to dtk's lbl_<address> symbols, and empties the section.
# Only literals loaded with lfs or lfd are supported.
#
# Usage:
#   python3 tools/extern_pool.py build/GVLE69/src/file.o orig/GVLE69/sys/main.dol 0x8048DEA8
###

import argparse
import struct
from typing import Dict, List, Optional

SHT_SYMTAB = 2
SHT_RELA = 4
SHT_NOBITS = 8
SHT_REL = 9
SHN_UNDEF = 0
STB_GLOBAL = 1
R_PPC_ADDR16_LO = 4
# Primary opcodes of the loads a pool literal is read with, and the literal's size: lfs, lfsu, lfd, lfdu
LOAD_SIZES = {48: 4, 49: 4, 50: 8, 51: 8}

EHDR_SIZE = 0x34
SHDR = struct.Struct(">10I")
SYM = struct.Struct(">IIIBBH")
RELA = struct.Struct(">IIi")


class Section:
    def __init__(self, fields: tuple, data: bytes) -> None:
        (
            self.name,
            self.type,
            self.flags,
            self.addr,
            _,
            self.size,
            self.link,
            self.info,
            self.addralign,
            self.entsize,
        ) = fields
        self.data = bytearray(data)


class Dol:
    def __init__(self, path: str) -> None:
        with open(path, "rb") as f:
            self.data = f.read()
        offsets = struct.unpack_from(">18I", self.data, 0x00)
        addresses = struct.unpack_from(">18I", self.data, 0x48)
        sizes = struct.unpack_from(">18I", self.data, 0x90)
        self.sections = [s for s in zip(offsets, addresses, sizes) if s[2]]

    def read(self, address: int, size: int) -> Optional[bytes]:
        """`size` bytes of the image at `address`, or None if no section holds them."""
        for offset, start, length in self.sections:
            if start <= address and address + size <= start + length:
                begin = offset + address - start
                return self.data[begin : begin + size]
        return None


def map_pool(path: str, pool: bytes, sizes: Dict[int, int], dol: Dol, address: int) -> Dict[int, int]:
    """Map each literal's offset in `pool` to its address in the original, where the first one is at `address`.

    `sizes` has every literal's offset and size. Floats are 4-aligned and doubles 8-aligned in both copies."""
    mapping: Dict[int, int] = {}
    end = 0
    for offset in sorted(sizes):
        size = sizes[offset]
        if offset < end:
            raise SystemExit(f"{path}: the literal at .rodata+0x{offset:X} overlaps the one before it")
        if any(pool[end:offset]):
            raise SystemExit(f"{path}: .rodata+0x{end:X} is neither a float literal nor padding")
        if not mapping and address % size:
            raise SystemExit(f"{path}: 0x{address:08X} is not aligned for the first literal")
        address = (address + size - 1) & -size
        ours = pool[offset : offset + size]
        theirs = dol.read(address, size)
        if ours != theirs:
            there = theirs.hex() if theirs else "nothing"
            raise SystemExit(
                f"{path}: .rodata+0x{offset:X} ({ours.hex()}) differs from the original"
                f" at 0x{address:08X} ({there})"
            )
        mapping[offset] = address
        address += size
        end = offset + size
    if any(pool[end:]):
        raise SystemExit(f"{path}: .rodata+0x{end:X} is neither a float literal nor padding")
    return mapping


def c_string(table: bytes, offset: int) -> str:
    return table[offset : table.index(b"\0", offset)].decode()


def extern_pool(path: str, dol_path: str, address: int) -> None:
    with open(path, "rb") as f:
        data = f.read()
    if data[:4] != b"\x7fELF" or data[4] != 1 or data[5] != 2:
        raise SystemExit(f"{path}: not a 32-bit big-endian ELF")
    (e_shoff,) = struct.unpack_from(">I", data, 0x20)
    e_shentsize, e_shnum, e_shstrndx = struct.unpack_from(">HHH", data, 0x2E)
    if e_shentsize != SHDR.size:
        raise SystemExit(f"{path}: unexpected section header size")

    sections: List[Section] = []
    for i in range(e_shnum):
        fields = SHDR.unpack_from(data, e_shoff + i * e_shentsize)
        offset, size = fields[4], fields[5]
        body = b"" if fields[1] == SHT_NOBITS else data[offset : offset + size]
        sections.append(Section(fields, body))
    names = bytes(sections[e_shstrndx].data)

    pool_index = None
    for i, section in enumerate(sections):
        if c_string(names, section.name) == ".rodata":
            pool_index = i
    if pool_index is None or not sections[pool_index].data:
        raise SystemExit(f"{path}: no .rodata literal pool to point at 0x{address:08X}")
    pool = sections[pool_index]

    symtab = next((s for s in sections if s.type == SHT_SYMTAB), None)
    if symtab is None:
        raise SystemExit(f"{path}: no symbol table")
    strtab = sections[symtab.link]
    symbols = [
        list(SYM.unpack_from(symtab.data, i)) for i in range(0, len(symtab.data), SYM.size)
    ]

    literals: Dict[str, int] = {}

    def literal_symbol(name: str) -> int:
        """Index of the undefined global `name`, added to the symbol table if it isn't there."""
        if name not in literals:
            for i, (st_name, _, _, st_info, _, st_shndx) in enumerate(symbols):
                if st_shndx == SHN_UNDEF and i and c_string(bytes(strtab.data), st_name) == name:
                    literals[name] = i
                    break
            else:
                st_name = len(strtab.data)
                strtab.data += name.encode() + b"\0"
                literals[name] = len(symbols)
                symbols.append([st_name, 0, 0, STB_GLOBAL << 4, 0, SHN_UNDEF])
        return literals[name]

    # Every relocation against the pool, and the size of the literal each one loads
    references = []
    sizes: Dict[int, int] = {}
    for section in sections:
        if section.type == SHT_REL:
            raise SystemExit(f"{path}: REL relocations are not supported")
        if section.type != SHT_RELA:
            continue
        if section.info == pool_index:
            raise SystemExit(f"{path}: .rodata has relocations of its own, so it is not a literal pool")
        code = sections[section.info].data
        for i in range(0, len(section.data), RELA.size):
            r_offset, r_info, r_addend = RELA.unpack_from(section.data, i)
            symbol = symbols[r_info >> 8]
            if symbol[5] != pool_index:
                continue
            target = symbol[1] + r_addend
            references.append((section, i, target))
            if r_info & 0xFF != R_PPC_ADDR16_LO:
                continue
            (instruction,) = struct.unpack_from(">I", code, r_offset - 2)
            size = LOAD_SIZES.get(instruction >> 26)
            if size is None:
                raise SystemExit(f"{path}: 0x{r_offset - 2:X} reads .rodata with something other than lfs or lfd")
            if sizes.setdefault(target, size) != size:
                raise SystemExit(f"{path}: .rodata+0x{target:X} is loaded as both a float and a double")

    # The pool must be the original's before anything refers to the original's copy
    mapping = map_pool(path, bytes(pool.data), sizes, Dol(dol_path), address)

    for section, i, target in references:
        r_offset, r_info, _ = RELA.unpack_from(section.data, i)
        if target not in mapping:
            raise SystemExit(f"{path}: relocation at 0x{r_offset:X} does not point at a literal")
        index = literal_symbol(f"lbl_{mapping[target]:08X}")
        RELA.pack_into(section.data, i, r_offset, (index << 8) | (r_info & 0xFF), 0)

    symtab.data = bytearray(b"".join(SYM.pack(*symbol) for symbol in symbols))
    pool.data = bytearray()
    pool.addralign = 1

    # Lay the file out again: header, section contents, section headers
    out = bytearray(data[:EHDR_SIZE])
    headers = []
    for section in sections:
        while len(out) % 4:
            out.append(0)
        offset = len(out) if section.type else 0
        size = section.size if section.type == SHT_NOBITS else len(section.data)
        out += section.data
        headers.append(
            SHDR.pack(
                section.name,
                section.type,
                section.flags,
                section.addr,
                offset,
                size,
                section.link,
                section.info,
                section.addralign,
                section.entsize,
            )
        )
    while len(out) % 4:
        out.append(0)
    struct.pack_into(">I", out, 0x20, len(out))
    out += b"".join(headers)
    with open(path, "wb") as f:
        f.write(out)


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Point a ProDG object's .rodata literal pool at the original DOL's copy, in place"
    )
    parser.add_argument("object", help="ProDG object to fix up in place")
    parser.add_argument("dol", help="original DOL the pool is checked against")
    parser.add_argument("address", type=lambda s: int(s, 0), help="the pool's address in the original")
    args = parser.parse_args()
    extern_pool(args.object, args.dol, args.address)


if __name__ == "__main__":
    main()
