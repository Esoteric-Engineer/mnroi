#!/usr/bin/env python3
"""List, unpack and build the nested UI archives Apt/**/<name>.big inside CLASH.BIG.

Usage (from repo root):
  python3 tools/nbig.py list [substring]          Every nested archive and its files
  python3 tools/nbig.py unpack NAME DIR           The files of one archive (NAME: screens/clashCharSelect)
  python3 tools/nbig.py unpack -f FILE DIR        The same from an extracted or edited archive
  python3 tools/nbig.py pack OUT FILE ...         A compressed archive of the FILEs, in that order
  python3 tools/nbig.py rename NAME NEW OUT       A copy of an archive with its files named NEW.*
  python3 tools/nbig.py check                     Rebuild every archive byte for byte

An archive is a RefPack stream (tools/refpack.py) of a BIGF file; all 709 in CLASH.BIG are
compressed. Each holds <name>.apt, <name>.const and <name>.geo, and 664 of them <name>.gsh, named
after the archive itself: an archive copied under a new name needs its files renamed (`rename`).
`pack` and `rename` compress the result, since the game unpacks these in place and complains about
a stream that is not smaller than its output (docs/characters.md section 5). Neither writes under orig/.

BIGF, big-endian except the total size:
  +0x0  "BIGF"
  +0x4  u32 LE total size
  +0x8  u32 file count
  +0xC  u32 index size: from 0 to the end of the tag
  +0x10 per file {u32 offset; u32 size; NUL-terminated name}
        then an 8-byte tag, "L231" and four zero bytes ("L234" in apt/clash/screens/test.big)
  The files follow in index order, each starting 0x80-aligned; nothing pads the last one.
"""

import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import refpack  # noqa: E402
from nvbtool import read_big_index, read_entry  # noqa: E402

ALIGN = 0x80
TAG = b"L231\0\0\0\0"


def load(data):
    """[(name, bytes)] of an archive, compressed or not."""
    return parse(data)[0]


def parse(data):
    """([(name, bytes)], tag) of an archive, compressed or not."""
    if data[:2] == b"\x10\xfb":
        data = refpack.decompress(data)
    if data[:4] != b"BIGF":
        raise ValueError("not a BIGF archive: %r" % data[:4])
    count, index_size = struct.unpack_from(">II", data, 8)
    files, p = [], 16
    for _ in range(count):
        off, size = struct.unpack_from(">II", data, p)
        end = data.index(b"\0", p + 8)
        files.append((data[p + 8:end].decode("latin-1"), data[off:off + size]))
        p = end + 1
    return files, data[p:index_size]


def save(files, compress=True, tag=TAG):
    """The bytes of an archive of [(name, bytes)]."""
    index_size = 16 + sum(8 + len(n) + 1 for n, _ in files) + len(tag)
    pos = index_size
    index, body = bytearray(), bytearray()
    for name, data in files:
        pos += -pos % ALIGN
        index += struct.pack(">II", pos, len(data)) + name.encode("latin-1") + b"\0"
        body += bytes(pos - index_size - len(body)) + data
        pos += len(data)
    raw = (b"BIGF" + struct.pack("<I", pos) + struct.pack(">II", len(files), index_size) +
           bytes(index) + tag + bytes(body))
    return refpack.compress(raw) if compress else raw


def rename(files, new):
    """The files of an archive named after another archive: clashCharSelect.apt -> NEW.apt."""
    return [(new + os.path.splitext(name)[1], data) for name, data in files]


def archives(index, sub=None):
    names = sorted(n for n in index if n.endswith(".big"))
    return [n for n in names if sub.lower() in n] if sub else names


def find(index, name):
    """The CLASH.BIG entry of a nested archive: a full path, or its end (screens/clashCharSelect)."""
    want = name.lower().replace("\\", "/")
    want = want if want.endswith(".big") else want + ".big"
    if want in index:
        return want
    hits = [n for n in archives(index) if n.endswith("/" + want)]
    if len(hits) != 1:
        raise SystemExit("%s: %d nested archives match (python3 tools/nbig.py list)" % (name, len(hits)))
    return hits[0]


def get(index, name):
    """[(name, bytes)] of a nested archive in CLASH.BIG."""
    return load(read_entry(index, find(index, name)))


def writable(path):
    if path.replace("\\", "/").startswith("orig/"):
        raise SystemExit("refusing to write under orig/: %s" % path)
    return path


def cmd_list(index, sub):
    for name in archives(index, sub):
        print(name)
        for inner, data in load(read_entry(index, name)):
            print("    %8X %s" % (len(data), inner))


def cmd_check(index):
    ok = True
    entries = archives(index)
    for name in entries:
        packed = read_entry(index, name)
        raw = refpack.decompress(packed) if packed[:2] == b"\x10\xfb" else packed
        try:
            files, tag = parse(raw)
            if save(files, False, tag) != raw:
                raise ValueError("rebuilt archive differs")
            stem = os.path.basename(name)[:-4]
            if any(os.path.splitext(n)[0].lower() != stem for n, _ in files):
                raise ValueError("a file not named after the archive")
        except (ValueError, struct.error) as e:
            print("%-56s %s" % (name, e))
            ok = False
    print("%d nested archives, %s" % (len(entries), "all rebuilt byte for byte" if ok else "INVALID"))
    sys.exit(0 if ok else 1)


def main(argv):
    cmd = argv[1] if len(argv) > 1 else ""
    if cmd == "pack" and len(argv) >= 4:
        files = [(os.path.basename(p), open(p, "rb").read()) for p in argv[3:]]
        open(writable(argv[2]), "wb").write(save(files))
        return
    if cmd not in ("list", "unpack", "rename", "check"):
        raise SystemExit(__doc__)
    index = read_big_index()
    if cmd == "check":
        cmd_check(index)
    elif cmd == "list" and len(argv) <= 3:
        cmd_list(index, argv[2] if len(argv) > 2 else None)
    elif cmd == "unpack" and len(argv) in (4, 5):
        files = load(open(argv[3], "rb").read()) if argv[2] == "-f" else get(index, argv[2])
        out = writable(argv[-1])
        os.makedirs(out, exist_ok=True)
        for name, data in files:
            open(os.path.join(out, name), "wb").write(data)
            print("wrote %s" % os.path.join(out, name))
    elif cmd == "rename" and len(argv) == 5:
        open(writable(argv[4]), "wb").write(save(rename(get(index, argv[2]), argv[3])))
    else:
        raise SystemExit(__doc__)


if __name__ == "__main__":
    main(sys.argv)
