#!/usr/bin/env python3
"""Append-only edits of APT UI movies (the format is in tools/aptdump.py).

Usage (from repo root):
  python3 tools/aptpatch.py check     Rebuild every movie in CLASH.BIG unedited, byte for byte, and
                                      with an export and a string added, read back by aptdump

As a module:
  apt = Apt(apt_bytes, const_bytes)
  i = apt.const_int(19)                   a new .const item
  s = apt.push_str(block, "thumb18")      an item that PushData in the action block at block pushes as
                                          that string (the block's ConstantPool grows)
  at = apt.find_push(block, pred)         the PushData whose operands satisfy pred
  apt.set_push(at, items)                 replace its operand list
  apt.add_frame_item(...), apt.add_export(name, character)
  apt_bytes, const_bytes = apt.build()

Every pointer in an .apt is an absolute file offset, so new data is appended to the end of the file
and an existing count and pointer pair is pointed at it; nothing that exists moves. It cannot insert
code or grow anything in place. The .const is rebuilt: its item table grows, which moves the strings
after it, so the string items' offsets are adjusted.

What the game needs (docs/characters.md section 4): nothing may be reachable twice. A copied sprite
that shared the original's frame items and action blocks broke both, so a copy duplicates every
frame item, action block and PushData/ConstantPool index array. An action block must keep its
address modulo 4, since operand padding depends on it.
"""

import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import aptdump as A  # noqa: E402


class Apt:
    def __init__(self, apt, const):
        self.d = bytearray(apt)
        if const[:len(A.CONST_MAGIC)] != A.CONST_MAGIC:
            raise ValueError("bad .const header")
        self.apt_off, count, self.items_off = struct.unpack_from(">III", const, 0x14)
        self.items = [list(struct.unpack_from(">II", const, self.items_off + 8 * i)) for i in range(count)]
        self.n_orig = count
        self.const_head = const[:self.items_off]
        self.strings = bytearray(const[self.items_off + 8 * count:])
        self.strings_base = self.items_off + 8 * count  # original offset of the strings blob
        self.new_strings = {}                           # item index -> offset inside self.strings
        self.r = A.R(self.d)

    # ---- .const -----------------------------------------------------------------------------
    def _add_item(self, typ, value):
        self.items.append([typ, value])
        return len(self.items) - 1

    def const_str(self, s):
        self.strings += b"\0" * (-len(self.strings) % 4)
        off = len(self.strings)
        self.strings += s.encode("latin-1") + b"\0"
        i = self._add_item(1, 0)
        self.new_strings[i] = off
        return i

    def const_int(self, v):
        return self._add_item(7, v & 0xFFFFFFFF)

    def const_pool(self, pool_index):
        return self._add_item(8, pool_index)

    def const_value(self, idx, pool=None):
        """Decoded value of a const item, following a pool lookup when `pool` is given."""
        typ, v = self.items[idx]
        if typ == 8 and pool is not None:
            return self.const_value(pool[v])
        if typ == 1:
            if idx in self.new_strings:
                off = self.new_strings[idx]
            else:
                off = v - self.strings_base
            end = self.strings.index(b"\0", off)
            return self.strings[off:end].decode("latin-1")
        if typ == 7:
            return v - (1 << 32) if v & 0x80000000 else v
        return (typ, v)

    # ---- .apt -------------------------------------------------------------------------------
    def u32(self, o):
        return struct.unpack_from(">I", self.d, o)[0]

    def put32(self, o, v):
        struct.pack_into(">I", self.d, o, v & 0xFFFFFFFF)

    def append(self, data, align=4):
        self.d += b"\0" * (-len(self.d) % align)
        off = len(self.d)
        self.d += data
        return off

    def append_u32s(self, values):
        return self.append(b"".join(struct.pack(">I", v & 0xFFFFFFFF) for v in values))

    def append_str(self, s):
        return self.append(s.encode("latin-1") + b"\0")

    # action blocks: `block` is the address of the block's first instruction (its ConstantPool)
    def pool(self, block):
        if self.d[block] != 0x88:
            raise ValueError("no ConstantPool at 0x%X" % block)
        p = A.al4(block + 1)
        n, ptr = self.u32(p), self.u32(p + 4)
        return [self.u32(ptr + 4 * i) for i in range(n)]

    def extend_pool(self, block, item_indices):
        """Add const items to the block's constant pool; returns the pool index of the first."""
        old = self.pool(block)
        p = A.al4(block + 1)
        self.put32(p, len(old) + len(item_indices))
        self.put32(p + 4, self.append_u32s(old + list(item_indices)))
        return len(old)

    def push_str(self, block, s):
        """A const item that makes PushData (inside `block`) push the string `s`."""
        return self.const_pool(self.extend_pool(block, [self.const_str(s)]))

    def get_push(self, at):
        if self.d[at] != 0x96:
            raise ValueError("no PushData at 0x%X" % at)
        p = A.al4(at + 1)
        n, ptr = self.u32(p), self.u32(p + 4)
        return [self.u32(ptr + 4 * i) for i in range(n)]

    def set_push(self, at, items):
        if self.d[at] != 0x96:
            raise ValueError("no PushData at 0x%X" % at)
        p = A.al4(at + 1)
        self.put32(p, len(items))
        self.put32(p + 4, self.append_u32s(items))

    def walk(self, p, end=None):
        """Yield (address, opcode) for each instruction of the block at p, into function bodies too."""
        d = self.d
        while end is None or p < end:
            at = p
            op = d[p]
            p += 1
            yield at, op
            if op == 0x00 and end is None:
                return
            if op in A.STR_OPS or op in A.I32_OPS or op in A.BR_OPS or op in (0xB4, 0xB7):
                p = A.al4(p) + 4
            elif op in A.CONST_BYTE_OPS or op in (0xB5, 0xB9):
                p += 1
            elif op in (0xA3, 0xB6):
                p += 2
            elif op in (0x83, 0x88, 0x96):
                p = A.al4(p) + 8
            elif op == 0x9B:
                p = A.al4(p)
                size = struct.unpack_from(">i", d, p + 12)[0]
                p += 24
                yield from self.walk(p, p + size)
                p += size
            elif op == 0x8E:
                p = A.al4(p)
                size = struct.unpack_from(">i", d, p + 16)[0]
                p += 28
                yield from self.walk(p, p + size)
                p += size

    def find_push(self, block, pred):
        """Address of the one PushData in `block` whose decoded operand list satisfies pred."""
        pool = self.pool(block)
        hits = []
        for at, op in self.walk(block):
            if op == 0x96:
                vals = [self.const_value(i, pool) for i in self.get_push(at)]
                if pred(vals):
                    hits.append(at)
        if len(hits) != 1:
            raise ValueError("expected one matching PushData in block 0x%X, found %d" % (block, len(hits)))
        return hits[0]

    # movie structure
    def character(self, n):
        chars = self.u32(self.apt_off + 24)
        return self.u32(chars + 4 * n)

    def frame(self, char_ptr, f):
        """(count, items pointer, address of the frame record) of frame f of a movie/sprite."""
        frames = self.u32(char_ptr + 12)
        rec = frames + 8 * f
        return self.u32(rec), self.u32(rec + 4), rec

    def frame_actions(self, char_ptr, f):
        n, items, _ = self.frame(char_ptr, f)
        out = []
        for i in range(n):
            it = self.u32(items + 4 * i)
            if self.u32(it) == 1:
                out.append(self.u32(it + 4))
        return out

    def frame_places(self, char_ptr, f):
        """[(item pointer, name)] of the PlaceObject items of a frame."""
        n, items, _ = self.frame(char_ptr, f)
        out = []
        for i in range(n):
            it = self.u32(items + 4 * i)
            if self.u32(it) == 3:
                out.append((it, self.r.s(self.u32(it + 52))))
        return out

    def add_frame_item(self, char_ptr, f, item_ptr):
        n, items, rec = self.frame(char_ptr, f)
        new = self.append_u32s([self.u32(items + 4 * i) for i in range(n)] + [item_ptr])
        self.put32(rec, n + 1)
        self.put32(rec + 4, new)

    def exports(self):
        n, ptr = self.u32(self.apt_off + 48), self.u32(self.apt_off + 52)
        return [(self.r.s(self.u32(ptr + 8 * i)), self.u32(ptr + 8 * i + 4)) for i in range(n)]

    def add_export(self, name, char_id):
        n, ptr = self.u32(self.apt_off + 48), self.u32(self.apt_off + 52)
        old = bytes(self.d[ptr:ptr + 8 * n])
        name_ptr = self.append_str(name)
        new = self.append(old + struct.pack(">II", name_ptr, char_id))
        self.put32(self.apt_off + 48, n + 1)
        self.put32(self.apt_off + 52, new)

    # ---- output -----------------------------------------------------------------------------
    def build(self):
        added = len(self.items) - self.n_orig
        shift = 8 * added
        new_base = self.strings_base + shift
        items = bytearray()
        for i, (typ, v) in enumerate(self.items):
            if typ == 1:
                v = new_base + self.new_strings[i] if i in self.new_strings else v + shift
            items += struct.pack(">II", typ, v)
        head = bytearray(self.const_head)
        struct.pack_into(">I", head, 0x18, len(self.items))
        return bytes(self.d), bytes(head) + bytes(items) + bytes(self.strings)


def cmd_check():
    ok = True
    count = 0
    for name, apt, const in A.movies():
        try:
            if Apt(apt, const).build() != (apt, const):
                raise ValueError("unedited rebuild differs")
            p = Apt(apt, const)
            p.add_export("aptpatch_check", 0)
            item = p.const_str("aptpatch_check")
            new_apt, new_const = p.build()
            out, _ = A.dump(new_apt, new_const)
            if "  export name='aptpatch_check' char=0" not in out:
                raise ValueError("added export not read back")
            if A.read_const(new_const)[1][item] != ("str", "aptpatch_check"):
                raise ValueError("added string not read back")
        except (ValueError, IndexError, struct.error) as e:
            print("%-56s %s" % (name, e))
            ok = False
        count += 1
    print("%d movies, %s" % (count, "all rebuilt byte for byte, and edited" if ok else "INVALID"))
    sys.exit(0 if ok else 1)


def main(argv):
    if len(argv) == 2 and argv[1] == "check":
        cmd_check()
    raise SystemExit(__doc__)


if __name__ == "__main__":
    main(sys.argv)
