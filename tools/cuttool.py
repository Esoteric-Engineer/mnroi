#!/usr/bin/env python3
"""Read and rebuild the in-engine cutscenes (Cutscenes/*.cut in CLASH.BIG).

Usage (from repo root):
  python3 tools/cuttool.py list NAME|-f FILE      Header, actors and chunks of one cutscene
  python3 tools/cuttool.py check                  Rebuild every .cut byte for byte from its parts

NAME is a file in CLASH.BIG (am_4 or cutscenes/am_4.cut). As a module, read_cut()/build_cut() parse
and rebuild a file; build_cut() recomputes every count and size from the parts.

The streamer, cCutPlayer (Game/fn_80438044.cpp to Game/fn_80439E94.c), reads the header, then one chunk at a
time; fn_80439778 swaps the header (fn_80057FF8) and records (fn_80057AE8) and drops a file whose
magic is not 0x2715 or whose chunk sizes go over 0x4B001, and fn_80058284 lays out and swaps each
chunk (all in Game/fn_80057AE8.c except the streamer). Little-endian:
  +0x0   u32 magic 0x2715 (10 shipped files have 0x2714 and 7 are something else; the streamer
         does not queue them)
  +0x4   u32 flags (0, 16, 32, 48, 16384 or 32816; not traced)
  +0x8   u32 chunk count
  +0xC   u32 actor count
  +0x10  f32 frame rate (29.97)
  +0x14  char[0x20] x 3, audio stream names (.asf); +0x74 char[0x20] x 4, scene names
  +0xF4  u8 per chunk, 1 or 2 (not traced), up to +0x18C
  +0x18C, +0x190, +0x194: three pointers the game fills in, 0 in the file
  +0x198 u32 size of each chunk
  then the actors, 0x90 each: u32 (0), u32 (not traced), char[0x48] name, f32 4x4 matrix
       (row-major, the placement; translation in elements 12-14)
  then u32 per chunk, 0 (the game's chunk pointers), then the chunks back to back
Chunk, n being the number of actors in it:
  +0x0   u32 (not traced); +0x4 u32 n; +0x8, +0xC f32 (not traced); +0x10, +0x14 pointers, 0
  n actor records as above, then n u32, 0 or stale (the game's animation pointers)
  n animations, each an .ngb animation (tools/ngbtool.py): a 0x50-byte header (+0x2C track count;
       the game sets bit 0x10000 of +0x20), the tracks {u32 bone, u32 channel, u32 key count,
       pointer}, then each track's keys, 12 bytes {f32 frame, s16 a, b, c, d}
  n u32 event counts (only the low byte is read), then each animation's events, 12 bytes
       {f32 frame, u16 type, u16 param, u32 value}
Pointer fields hold the authoring tool's stale values and are kept as they are. In mov_8.cut the
size of chunk 3 is 24 bytes more than the chunk; every other shipped 0x2715 file is consistent.
Six shipped files have a chunk over 0x4B001 bytes (check lists them).
"""

import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from nvbtool import read_big_index, read_entry  # noqa: E402

MAGIC = 0x2715
HEADER = 0x198
RECORD = 0x90
ANIM = 0x50
LIMIT = 0x4B001


class Actor:
    def __init__(self, record, anim_ptr, header, tracks, events, event_word):
        self.record = record        # 0x90 bytes
        self.anim_ptr = anim_ptr    # the stale pointer word
        self.header = header        # 0x50 bytes; +0x2C is rewritten from the tracks
        self.tracks = tracks        # [(16-byte track, keys bytes)]
        self.events = events        # bytes, 12 each
        self.event_word = event_word  # the count word's upper 3 bytes

    @property
    def name(self):
        return self.record[8:0x50].split(b"\0")[0].decode("latin-1")


class Chunk:
    def __init__(self, head, actors):
        self.head = head            # 0x18 bytes; +0x4 is rewritten from the actors
        self.actors = actors


class Cut:
    def __init__(self, header, records, chunk_words, chunks, sizes):
        self.header = header        # 0x198 bytes; +0x8 and +0xC are rewritten
        self.records = records      # [0x90 bytes]
        self.chunk_words = chunk_words
        self.chunks = chunks
        self.sizes = sizes          # the file's size table, which build_cut() recomputes

    def field(self, fmt, off):
        return struct.unpack_from("<" + fmt, self.header, off)[0]

    def names(self):
        out = []
        for off in range(0x14, 0xF4, 0x20):
            s = self.header[off:off + 0x20].split(b"\0")[0]
            out.append(s.decode("latin-1"))
        return out


def u32(data, off):
    return struct.unpack_from("<I", data, off)[0]


def read_chunk(data, b):
    n = u32(data, b + 4)
    p = b + 0x18
    records = [data[p + i * RECORD:p + (i + 1) * RECORD] for i in range(n)]
    p += n * RECORD
    ptrs = [u32(data, p + 4 * i) for i in range(n)]
    p += 4 * n
    anims = []
    for i in range(n):
        header = data[p:p + ANIM]
        count = u32(header, 0x2C)
        p += ANIM
        heads = [data[p + 16 * t:p + 16 * (t + 1)] for t in range(count)]
        p += 16 * count
        tracks = []
        for h in heads:
            size = 12 * u32(h, 8)
            tracks.append((h, data[p:p + size]))
            p += size
        anims.append((header, tracks))
    counts = [data[p + 4 * i:p + 4 * i + 4] for i in range(n)]
    p += 4 * n
    actors = []
    for i in range(n):
        size = 12 * counts[i][0]
        actors.append(Actor(records[i], ptrs[i], anims[i][0], anims[i][1], data[p:p + size], counts[i][1:]))
        p += size
    if p > len(data):
        raise ValueError("chunk at 0x%X runs past the end" % b)
    return Chunk(data[b:b + 0x18], actors), p - b


def read_cut(data):
    if len(data) < HEADER or u32(data, 0) != MAGIC:
        raise ValueError("not a 0x%X cutscene: magic 0x%X" % (MAGIC, u32(data, 0) if len(data) >= 4 else 0))
    nchunks, nrecords = u32(data, 8), u32(data, 0xC)
    p = HEADER
    sizes = list(struct.unpack_from("<%dI" % nchunks, data, p))
    p += 4 * nchunks
    records = [data[p + i * RECORD:p + (i + 1) * RECORD] for i in range(nrecords)]
    p += nrecords * RECORD
    words = list(struct.unpack_from("<%dI" % nchunks, data, p))
    p += 4 * nchunks
    chunks = []
    for _ in range(nchunks):
        chunk, size = read_chunk(data, p)
        chunks.append(chunk)
        p += size
    if p != len(data):
        raise ValueError("%d bytes after the last chunk" % (len(data) - p))
    return Cut(data[:HEADER], records, words, chunks, sizes)


def build_chunk(chunk):
    n = len(chunk.actors)
    out = bytearray(chunk.head)
    struct.pack_into("<I", out, 4, n)
    for a in chunk.actors:
        out += a.record
    for a in chunk.actors:
        out += struct.pack("<I", a.anim_ptr)
    for a in chunk.actors:
        header = bytearray(a.header)
        struct.pack_into("<I", header, 0x2C, len(a.tracks))
        out += header
        for h, keys in a.tracks:
            h = bytearray(h)
            struct.pack_into("<I", h, 8, len(keys) // 12)
            out += h
        for _, keys in a.tracks:
            out += keys
    for a in chunk.actors:
        out += bytes([len(a.events) // 12]) + a.event_word
    for a in chunk.actors:
        out += a.events
    return bytes(out)


def build_cut(cut, sizes=None):
    """The file; sizes overrides the recomputed chunk sizes (mov_8.cut's table is off)."""
    chunks = [build_chunk(c) for c in cut.chunks]
    header = bytearray(cut.header)
    struct.pack_into("<II", header, 8, len(chunks), len(cut.records))
    out = bytearray(header)
    out += struct.pack("<%dI" % len(chunks), *(sizes or [len(c) for c in chunks]))
    for r in cut.records:
        out += r
    out += struct.pack("<%dI" % len(chunks), *cut.chunk_words)
    for c in chunks:
        out += c
    return bytes(out)


def cuts(index):
    return sorted(n for n in index if n.endswith(".cut"))


def load(index, args):
    if args and args[0] == "-f" and len(args) > 1:
        return open(args[1], "rb").read()
    if not args:
        raise SystemExit(__doc__)
    name = args[0].lower()
    for cand in (name, name + ".cut", "cutscenes/" + name, "cutscenes/" + name + ".cut"):
        if cand in index:
            return read_entry(index, cand)
    raise SystemExit("no cutscene %s" % args[0])


def cmd_list(cut):
    print("flags %d, %.2f fps, %d chunks, %d actors" % (cut.field("I", 4), cut.field("f", 0x10), len(cut.chunks), len(cut.records)))
    names = cut.names()
    print("streams: %s" % ", ".join(n for n in names[:3] if n))
    print("scenes:  %s" % ", ".join(n for n in names[3:] if n))
    print("chunk bytes: %s" % " ".join(str(b) for b in cut.header[0xF4:0xF4 + len(cut.chunks)]))
    for r in cut.records:
        t = struct.unpack_from("<3f", r, 0x50 + 12 * 4)
        print("  actor %-24s at (%g, %g, %g)" % (r[8:0x50].split(b"\0")[0].decode("latin-1"), t[0], t[1], t[2]))
    for i, c in enumerate(cut.chunks):
        print("chunk %d: %s" % (i, ", ".join("%s (%d tracks, %d keys, %d events)" % (
            a.name, len(a.tracks), sum(len(k) // 12 for _, k in a.tracks), len(a.events) // 12) for a in c.actors)))


def cmd_check(index):
    ok = True
    good = other = 0
    for name in cuts(index):
        data = read_entry(index, name)
        if u32(data, 0) != MAGIC:
            other += 1
            continue
        try:
            cut = read_cut(data)
        except (ValueError, struct.error) as e:
            print("%-40s %s" % (name, e))
            ok = False
            continue
        rebuilt = build_cut(cut)
        if rebuilt != data:
            if build_cut(cut, cut.sizes) == data:
                computed = [len(build_chunk(c)) for c in cut.chunks]
                bad = [i for i, (a, b) in enumerate(zip(cut.sizes, computed)) if a != b]
                print("%-40s size table differs from chunk %s (%s)" % (name, bad, ", ".join(
                    "%d for %d bytes" % (cut.sizes[i], computed[i]) for i in bad)))
            else:
                print("%-40s rebuilt file differs" % name)
                ok = False
                continue
        big = [i for i, s in enumerate(cut.sizes) if s > LIMIT]
        if big:
            print("%-40s chunks %s are over 0x%X bytes, which the streamer rejects" % (name, big, LIMIT))
        good += 1
    print("%d cutscenes rebuilt byte for byte, %d files without magic 0x%X skipped, %s" % (
        good, other, MAGIC, "OK" if ok else "INVALID"))
    sys.exit(0 if ok else 1)


def main(argv):
    cmd = argv[1] if len(argv) > 1 else ""
    if cmd not in ("list", "check"):
        raise SystemExit(__doc__)
    index = read_big_index()
    if cmd == "check":
        cmd_check(index)
    else:
        cmd_list(read_cut(load(index, argv[2:])))


if __name__ == "__main__":
    main(sys.argv)
