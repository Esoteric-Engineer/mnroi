#!/usr/bin/env python3
"""EA RefPack codec: the compression of the nested UI archives in CLASH.BIG (tools/nbig.py).

Usage (from repo root):
  python3 tools/refpack.py d IN OUT    Decompress a file
  python3 tools/refpack.py c IN OUT    Compress a file
  python3 tools/refpack.py check       Decompress every compressed entry of CLASH.BIG, then compress
                                       it again and decompress that (about a minute and a half)

The compressor does not reproduce EA's streams byte for byte; its output is about 3% larger and
decompresses to the same bytes. Neither command writes under orig/.

A stream, big-endian:
  u16 flags 0x10FB           only 0x10FB occurs; 0x0100 would add a 3-byte field and 0x8000
                             make the sizes 4 bytes
  u24 unpacked size          the .BH third word of the entry (tools/bigtool.py)
  then commands until the end command. Each copies L literal bytes from the stream, then C bytes
  from D bytes back in the output (D >= 1, overlapping copies allowed):
    0x00-0x7F  2 bytes  0DDCCCLL DDDDDDDD          L 0-3, C 3-10, D 1-1024
    0x80-0xBF  3 bytes  10CCCCCC LLDDDDDD DDDDDDDD  L 0-3, C 4-67, D 1-16384
    0xC0-0xDF  4 bytes  110DCCLL DDDDDDDD DDDDDDDD CCCCCCCC
                                                   L 0-3, C 5-1028, D 1-131072
    0xE0-0xFB  1 byte   111LLLLL                   literals only, L = (LLLLL + 1) * 4, 4-112
    0xFC-0xFF  1 byte   111111LL                   the end, after L literals (0-3)
"""

import os
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))


def decompress(src):
    flags = src[0] << 8 | src[1]
    if src[1] != 0xFB:
        raise ValueError("not RefPack: %02X %02X" % (src[0], src[1]))
    p = 2 + (3 if flags & 0x0100 else 0)
    n = 4 if flags & 0x8000 else 3
    size = int.from_bytes(src[p:p + n], "big")
    p += n
    out = bytearray()
    while True:
        b0 = src[p]
        if b0 < 0x80:
            b1 = src[p + 1]
            p += 2
            lit, off, cnt = b0 & 3, ((b0 & 0x60) << 3) + b1 + 1, ((b0 & 0x1C) >> 2) + 3
        elif b0 < 0xC0:
            b1, b2 = src[p + 1], src[p + 2]
            p += 3
            lit, off, cnt = b1 >> 6, ((b1 & 0x3F) << 8) + b2 + 1, (b0 & 0x3F) + 4
        elif b0 < 0xE0:
            b1, b2, b3 = src[p + 1], src[p + 2], src[p + 3]
            p += 4
            lit, off, cnt = b0 & 3, ((b0 & 0x10) << 12) + (b1 << 8) + b2 + 1, ((b0 & 0x0C) << 6) + b3 + 5
        elif b0 < 0xFC:
            lit = ((b0 & 0x1F) << 2) + 4
            out += src[p + 1:p + 1 + lit]
            p += 1 + lit
            continue
        else:
            lit = b0 & 3
            out += src[p + 1:p + 1 + lit]
            break
        out += src[p:p + lit]
        p += lit
        start = len(out) - off
        if start < 0:
            raise ValueError("back reference before the start of the output")
        if off >= cnt:
            out += out[start:start + cnt]
        else:
            for i in range(cnt):
                out.append(out[start + i])
    if len(out) != size:
        raise ValueError("header says %d bytes, got %d" % (size, len(out)))
    return bytes(out)


def compress(data, window=0x4000, max_chain=48):
    """Greedy hash-chain compressor using the 2- and 3-byte commands and literal runs."""
    n = len(data)
    if n >= 1 << 24:
        raise ValueError("too large for a 3-byte size")
    out = bytearray(b"\x10\xFB" + n.to_bytes(3, "big"))
    head, prev = {}, [0] * n
    lit_start = p = 0

    def flush_literals(upto):
        nonlocal lit_start
        while upto - lit_start >= 4:
            run = min(112, (upto - lit_start) & ~3)
            out.append(0xE0 + (run - 4) // 4)
            out.extend(data[lit_start:lit_start + run])
            lit_start += run

    def insert(i):
        if i + 3 <= n:
            k = data[i:i + 3]
            prev[i] = head.get(k, -1)
            head[k] = i

    while p < n:
        best_len = best_off = 0
        if p + 3 <= n:
            cand = head.get(data[p:p + 3], -1)
            chain, limit = max_chain, min(n - p, 67)
            while cand >= 0 and chain and p - cand <= window:
                if data[cand + best_len:cand + best_len + 1] == data[p + best_len:p + best_len + 1]:
                    k = 0
                    while k < limit and data[cand + k] == data[p + k]:
                        k += 1
                    if k > best_len:
                        best_len, best_off = k, p - cand
                        if k == limit:
                            break
                cand = prev[cand]
                chain -= 1
        if best_len >= 3 and (best_off <= 1024 or best_len >= 4):
            flush_literals(p)  # leaves 0-3 literals, which the copy command carries
            lit, off = p - lit_start, best_off - 1
            if best_len <= 10 and best_off <= 1024:
                out += bytes((off >> 8 << 5 | (best_len - 3) << 2 | lit, off & 0xFF))
            else:
                out += bytes((0x80 | (best_len - 4), lit << 6 | off >> 8, off & 0xFF))
            out.extend(data[lit_start:p])
            for i in range(p, p + best_len):
                insert(i)
            p += best_len
            lit_start = p
        else:
            insert(p)
            p += 1
    flush_literals(n)
    out.append(0xFC + (n - lit_start))
    out.extend(data[lit_start:])
    return bytes(out)


def cmd_check():
    from bigtool import read_big_index, read_bh
    entries, _, _ = read_big_index()
    rows = read_bh()
    ok = True
    count = raw = packed = ours = 0
    start = time.time()
    with open("orig/GVLE69/files/CLASH.BIG", "rb") as f:
        for e, row in zip(entries, rows):
            if not row[2]:
                continue
            f.seek(e.offset)
            data = f.read(e.size)
            try:
                plain = decompress(data)
                if len(plain) != row[2]:
                    raise ValueError("%d bytes, .BH says %d" % (len(plain), row[2]))
                again = compress(plain)
                if decompress(again) != plain:
                    raise ValueError("does not survive compress and decompress")
            except (ValueError, IndexError) as err:
                print("%-56s %s" % (e.name, err))
                ok = False
                continue
            count += 1
            raw, packed, ours = raw + len(plain), packed + len(data), ours + len(again)
    print("%d compressed entries, %d bytes unpacked, %d packed (%d recompressed) in %ds, %s" % (
        count, raw, packed, ours, time.time() - start, "all round-trip" if ok else "INVALID"))
    sys.exit(0 if ok else 1)


def main(argv):
    if len(argv) == 2 and argv[1] == "check":
        cmd_check()
    if len(argv) != 4 or argv[1] not in ("d", "c"):
        raise SystemExit(__doc__)
    if argv[3].replace("\\", "/").startswith("orig/"):
        raise SystemExit("refusing to write under orig/: %s" % argv[3])
    data = open(argv[2], "rb").read()
    open(argv[3], "wb").write(decompress(data) if argv[1] == "d" else compress(data))


if __name__ == "__main__":
    main(sys.argv)
