#!/usr/bin/env python3
"""Print the headers of the model bundles Bundles/<name>.ngm (docs/characters.md section 4).

Usage (from repo root):
  python3 tools/ngmtool.py list [substring]   Header and model records of every bundle
  python3 tools/ngmtool.py check              Parse every bundle to its last byte

Big-endian on disc (the readers fn_801A2108 and fn_80221C08 do no byte swap):
  +0x0  u32 version              5; the reader rejects any other value
  +0x4  u32                      read and ignored; 0 in character bundles, hash-like in levels
  +0x8  u32                      read and ignored; likewise
  +0xC  u32 model count          bundle +0x28
  +0x10 u32 entry count          bundle +0x30; allocates entry count * 8 bytes at bundle +0x2C
  +0x14 u32 data size            bundle +0x24; 0 loads no model
  then per model, a prefix (fn_801A2108; fn_801A3ECC sizes the model from the counts):
        s32 index                -1, or passed to fn_801A27D4 with the model
        u8  parts                model +0x8
        u8  nodes                model +0x9
        u8  meshes               model +0x4
        u16 attachments          model +0x154
  and a body (fn_80221C08):
        char name[0x20]          model +0x8C, its registry name
        u8  streams              model +0x5, at most 4
        u32 flags                model +0x0
        u8  [0x20]               model +0xB0
        per stream:              model +0x1C, 0x18 each
          u32 n; n render vertices, three u16 each: a vertex of this stream, a normal (an index
                                 into Misc/NormalTable.ngn) and a UV (into the UV list below)
          u16 m; m vertices of STRIDE[type] bytes, in model space:
                                 type 0: f32 position; rigid, bound to the mesh's one node
                                 type 1: f32 position; u32 node
                                 type 2: f32 position; f32 weight[3]; u8 node[3]; u8 0
          type > 2 (no file has one): n * 6 more bytes
        u16 n; n UVs             model +0x14; s16 u, v with 9 fraction bits (GXSetVtxAttrFmt in
                                 fn_8021AD30; fn_80223E38 scales by 512.0)
        u32 n; n * u16 indices   model +0x7C (n at +0x10); a short read fails the load. Each
                                 mesh's strip span and then its list span, in mesh order; an
                                 index is a render vertex of the mesh's stream, not mesh-relative
        per part:  char[0x20]    a material name, fn_80234628 (model +0x88); its block in
                                 Materials/Shaders/shaders.nsa names the shader and textures
        per node:  Vector a, b (w forced to 1.0); s8 parent; u8   (0x30 each at model +0x80)
                   a skeleton without rotations: a is the offset from the parent and -b the
                   position in the model, so a node's -b is its parent's -b plus its a (all but
                   42 of the 29,688 child nodes, those in helicopter.NOC); a parent comes before
                   its child
        u16, u16                 model +0x158, +0x15A (first node of a second chain, guess)
        per mesh:  s32 part index; u8 stream; u16 strip count; u16 list count; u16 render
                   vertices; u8, u8, u8; u8 n; n nodes   (0x5C each at model +0x18)
                   The render vertices are the next ones of the stream (they sum to its n).
                   fn_80223E38 draws the list (GX_TRIANGLES, count at mesh +0x16) and then the
                   strip (GX_TRIANGLESTRIP, +0x14). The strip joins its runs with repeated
                   indices; its even triangles and every list triangle are counter-clockwise
                   seen from outside (it agrees with the normals). The n nodes are every node
                   the mesh's vertices name; a type-0 mesh has exactly one.
        per attachment: u8 node; u8 kind; u16 index; four Vectors (a 4x4 matrix)
                   (0x50 each at model +0x150). Points effects (Misc/game.nfx markers) and
                   attack volumes are placed at, found by kind and index (docs/characters.md
                   section 4)

Misc/NormalTable.ngn (fn_80224F30, "Graphics:Normals"): u16 count (2609), then that many unit
f32 vectors; the renderer binds it as the normal array of every model (fn_802237AC).
"""

import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from nvbtool import read_big_index, read_entry  # noqa: E402

HEADER = ">6I"
RECORD = ">iBBBH"
STRIDE = (0xC, 0x10, 0x1C, 0xC, 0x10, 0x1C, 0, 0)  # lbl_806707F8, bytes per vertex by stream type


class Reader:
    def __init__(self, data, off):
        self.data = data
        self.off = off

    def take(self, fmt):
        vals = struct.unpack_from(">" + fmt, self.data, self.off)
        self.off += struct.calcsize(">" + fmt)
        return vals if len(vals) > 1 else vals[0]

    def skip(self, n):
        if self.off + n > len(self.data):
            raise ValueError("body runs past the end of the file")
        self.off += n


class Body:
    """Where one model's arrays are in the file; ngmexport.py decodes them."""

    def __init__(self):
        self.streams = []  # (type, render vertex offset, count, vertex offset, count)
        self.meshes = []   # (part, stream, strips, lists, render vertices, (u8, u8, u8), nodes)


def parse_body(r, parts, nodes, meshes, attachments):
    b = Body()
    b.name = r.take("32s").split(b"\0")[0].decode("latin-1")
    streams = r.take("B")
    if streams > 4:
        raise ValueError("%s: %d streams" % (b.name, streams))
    b.flags = r.take("I")
    r.skip(0x20)
    for _ in range(streams):
        kind = r.take("B")
        n = r.take("I")
        refs = r.off
        r.skip(n * 6)
        m = r.take("H")
        b.streams.append((kind, refs, n, r.off, m))
        r.skip(m * STRIDE[kind])
        if kind > 2:
            r.skip(n * 6)
    b.uv_count = r.take("H")
    b.uvs = r.off
    r.skip(b.uv_count * 4)
    b.index_count = r.take("I")
    b.indices = r.off
    r.skip(b.index_count * 2)
    b.parts = [r.take("32s").split(b"\0")[0].decode("latin-1") for _ in range(parts)]
    b.nodes = r.off
    b.node_count = nodes
    r.skip(nodes * 0x22)
    b.chains = r.take("HH")
    for _ in range(meshes):
        rec = r.take("iBHHH")
        flags = r.take("BBB")
        n = r.take("B")
        b.meshes.append(rec + (flags, r.data[r.off:r.off + n]))
        r.skip(n)
    b.attachments = r.off
    b.attachment_count = attachments
    r.skip(attachments * 0x44)
    return b


def parse(data):
    head = struct.unpack_from(HEADER, data, 0)
    r = Reader(data, struct.calcsize(HEADER))
    models = []
    for _ in range(head[3]):
        rec = r.take(RECORD[1:])
        models.append((rec, parse_body(r, *rec[1:])))
    return head, models, r.off


def ngm_entries(index, sub=None):
    names = sorted(n for n in index if n.endswith(".ngm"))
    if sub:
        names = [n for n in names if sub.lower() in n]
    return names


def cmd_list(index, sub):
    print("%-36s %3s %8s %8s %6s %7s %8s" % ("bundle", "ver", "+0x4", "+0x8", "models",
                                           "entries", "data"))
    for name in ngm_entries(index, sub):
        head, models, _ = parse(read_entry(index, name))
        print("%-36s %3d %8x %8x %6d %7d %8x" % (name, head[0], head[1], head[2], head[3],
                                               head[4], head[5]))
        for rec, body in models:
            print("    %-32s index %3d  parts %3d  nodes %3d  meshes %3d  attachments %3d" %
                  ((body.name,) + rec))


def cmd_check(index):
    ok = True
    entries = ngm_entries(index)
    for name in entries:
        data = read_entry(index, name)
        bad = []
        try:
            head, _, end = parse(data)
        except (ValueError, struct.error) as e:
            head, end = struct.unpack_from(HEADER, data, 0), None
            bad.append(str(e))
        if head[0] != 5:
            bad.append("version %d" % head[0])
        if head[3] and not head[5]:
            bad.append("models but no data size")
        if end is not None and end != len(data):
            bad.append("parse ends at 0x%x of 0x%x" % (end, len(data)))
        if bad:
            print("%-36s %s" % (name, ", ".join(bad)))
            ok = False
    print("%d model bundles, %s" % (len(entries), "all parsed to the last byte" if ok else "INVALID"))
    sys.exit(0 if ok else 1)


def main(argv):
    if len(argv) < 2 or argv[1] not in ("list", "check"):
        raise SystemExit(__doc__)
    index = read_big_index()
    if argv[1] == "check":
        cmd_check(index)
    cmd_list(index, argv[2] if len(argv) > 2 else None)


if __name__ == "__main__":
    main(sys.argv)
