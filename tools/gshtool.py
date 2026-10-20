#!/usr/bin/env python3
"""Read and rewrite the UI image banks (.gsh) and shape geometry (.geo) of the APT movies.

Usage (from repo root):
  python3 tools/gshtool.py list NAME|-f FILE               The images of a bank
  python3 tools/gshtool.py decode NAME|-f FILE DIR [IMAGE ...]   Write images as DIR/<image>.png
  python3 tools/gshtool.py set IN OUT IMAGE=PNG ...        Write a copy of the bank IN with images replaced
  python3 tools/gshtool.py geo NAME|-f FILE [ID ...]       The shape records of a .geo
  python3 tools/gshtool.py check                           Rebuild every bank and .geo byte for byte

NAME is a bank in CLASH.BIG (hud/hudeng.1.gsh) or a nested archive (screens/clashCharSelect, see
tools/nbig.py), whose .gsh or .geo is meant. `set` keeps each image's size and palette size; the
PNG must have the image's size. It never writes under orig/. As a module, read_gsh()/build_gsh(),
add_images(), read_geo()/build_geo() and add_shapes() edit the files in memory.

An APT IMAGE character's texture id is the name of a bank entry ("36"), and a SHAPE character's
geometry is the .geo record with the character's id (tools/aptdump.py prints both).

.gsh, EA "ShpG", big-endian except the total size:
  +0x0  "ShpG"
  +0x4  u32 LE total size
  +0x8  u32 image count
  +0xC  u32 directory size: from 0 to the end of the tag
  +0x10 per image {u32 offset; u32 size; NUL-terminated name}, then an 8-byte tag ("G428" and four
        zero bytes; "G427" in the HUD banks). The UI movies' banks list the images sorted by name
        as strings, the HUD banks do not.
  The records follow in directory order, each 0x20-aligned; each gap starts with as much of
  "Buy ERTS" as fits. The file ends 0x20-aligned or right after the last record.
  An image record is blocks, each with a 0x20-byte header whose first word is a type byte and a
  24-bit 0x4001, and whose second word is the offset of the next block (0 in the last):
    image    type 0x10 + GX format: 0x19 C8 (2,544 images), 0x18 C4 (244, the 1x1 HUD pos_*/text_*)
             +0x8 u32 0x20, the pixel offset; +0xC u32 pixel size; +0x10 two u32, usually 0;
             +0x18 u32 width; +0x1C u32 height; then the pixels (tools/gxtex.py)
    palette  type 0x30 + GX palette format: 0x32 RGB5A3, 0x30 IA8 (20, the HUD's rage effects)
             +0x8 u32 0x20; +0xC u32 size, the colours rounded up to 0x10 bytes; +0x18 u32 colour
             count; +0x1C u32 1; then the colours
    0x7C     16 bytes {u32 2; u32 1; u32 x; u32 y} after the palette (656 images; guess: a hot spot)
    0x6F     one image has a comment block

.geo, little-endian: the shapes of the movie's SHAPE characters
  +0x0  u32 record count
  +0x4  per record its u32 offset; the records follow back to back, sorted by id as strings
  record: u32 id (the SHAPE character), u32 shape count, then per shape a u32 item count and items:
    u32 0, u32 1, u32 colour                      solid fill style
    u32 0, u32 0, u32 colour, u32 (0; 1 in 10), u32 texture id, f32 matrix[16]
                                                  texture fill style: the image of the bank entry
                                                  named by the id; a 4x4 matrix, row-major, the
                                                  translation in elements 12 and 13
    u32 0, u32 2, u32 colour, f32 width           line style
    u32 1, three f32[3] points                    a triangle (z is 0 in every file)
    u32 2, two f32[3] points                      a line
"""

import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gxtex  # noqa: E402
import nbig  # noqa: E402
from nvbtool import read_big_index, read_entry  # noqa: E402

PAD = b"Buy ERTS"
PALETTE_FORMATS = {0: gxtex.IA8, 1: gxtex.RGB565, 2: gxtex.RGB5A3}


# .gsh

class Bank:
    def __init__(self, names, records, tag, pad_end):
        self.names = names      # in directory order
        self.records = records  # {name: record bytes}
        self.tag = tag
        self.pad_end = pad_end  # whether the file ends 0x20-aligned


def read_gsh(data):
    if data[:4] != b"ShpG":
        raise ValueError("not a ShpG bank: %r" % data[:4])
    count, head = struct.unpack_from(">II", data, 8)
    names, records, p = [], {}, 16
    for _ in range(count):
        off, size = struct.unpack_from(">II", data, p)
        end = data.index(b"\0", p + 8)
        name = data[p + 8:end].decode("latin-1")
        names.append(name)
        records[name] = data[off:off + size]
        p = end + 1
    return Bank(names, records, data[p:head], len(data) % 0x20 == 0)


def build_gsh(bank):
    names = bank.names
    head = 16 + sum(8 + len(n) + 1 for n in names) + len(bank.tag)
    offsets, pos = [], head
    for n in names:
        pos += -pos % 0x20
        offsets.append(pos)
        pos += len(bank.records[n])
    out = bytearray(b"ShpG" + bytes(4) + struct.pack(">II", len(names), head))
    for n, off in zip(names, offsets):
        out += struct.pack(">II", off, len(bank.records[n])) + n.encode("latin-1") + b"\0"
    out += bank.tag
    for n, off in zip(names, offsets):
        gap = off - len(out)
        out += (PAD + bytes(gap))[:gap] + bank.records[n]
    if bank.pad_end:
        out += bytes(-len(out) % 0x20)
    struct.pack_into("<I", out, 4, len(out))
    return bytes(out)


def blocks(record):
    """[(type, offset)] of the blocks of an image record."""
    out, p = [], 0
    while True:
        word, nxt = struct.unpack_from(">II", record, p)
        out.append((word >> 24, p))
        if not nxt:
            return out
        p += nxt


class Picture:
    """The image and palette blocks of a record."""

    def __init__(self, record):
        bl = dict(blocks(record))
        img = next(p for t, p in blocks(record) if 0x10 <= t < 0x20)
        self.format = record[img] - 0x10
        _, _, self.pixel_off, self.pixel_size = struct.unpack_from(">IIII", record, img)
        self.pixel_off += img
        self.width, self.height = struct.unpack_from(">II", record, img + 0x18)
        pal = next((p for t, p in bl.items() if 0x30 <= t < 0x40), None)
        self.palette_format = self.palette_off = None
        self.colours = 0
        if pal is not None:
            self.palette_format = PALETTE_FORMATS[record[pal] - 0x30]
            self.colours = struct.unpack_from(">I", record, pal + 0x18)[0]
            self.palette_off = pal + struct.unpack_from(">I", record, pal + 8)[0]

    def palette(self, record):
        cols = struct.unpack_from(">%dH" % self.colours, record, self.palette_off)
        return [gxtex.texel(self.palette_format, c, None) for c in cols]

    def decode(self, record):
        data = record[self.pixel_off:self.pixel_off + self.pixel_size]
        return gxtex.decode(self.format, data, self.width, self.height, self.palette(record) if self.colours else None)


def quantize(pixels, n):
    """Median cut of RGBA tuples to at most n colours: (palette, {pixel: index})."""
    counts = {}
    for p in pixels:
        counts[p] = counts.get(p, 0) + 1
    boxes = [list(counts)]
    while len(boxes) < n:
        spans = [(max(c[i] for c in b) - min(c[i] for c in b), i, k) for k, b in enumerate(boxes) if len(b) > 1
                 for i in range(4)]
        if not spans:
            break
        _, ch, k = max(spans)
        box = sorted(boxes.pop(k), key=lambda c: c[ch])
        total, run, cut = sum(counts[c] for c in box), 0, 1
        for j, c in enumerate(box[:-1]):
            run += counts[c]
            if run * 2 >= total:
                cut = j + 1
                break
        boxes += [box[:cut], box[cut:]]
    palette = []
    for b in boxes:
        w = sum(counts[c] for c in b)
        palette.append(tuple((sum(c[i] * counts[c] for c in b) + w // 2) // w for i in range(4)))
    index = {}
    for c in counts:
        index[c] = min(range(len(palette)), key=lambda j: sum((c[i] - palette[j][i]) ** 2 for i in range(4)))
    return palette, index


def encode_record(record, rgba):
    """The record with its pixels and palette re-encoded from RGBA bytes of the same size."""
    pic = Picture(record)
    if pic.format not in (gxtex.C4, gxtex.C8) or pic.palette_format is None:
        raise SystemExit("only C4 and C8 images with a palette are encoded")
    pixels = [tuple(rgba[i:i + 4]) if rgba[i + 3] else (0, 0, 0, 0) for i in range(0, len(rgba), 4)]
    palette, index = quantize(pixels, pic.colours)
    vals = [index[pixels[y * pic.width + x]] if x < pic.width and y < pic.height else 0
            for x, y in gxtex.blocks(pic.format, pic.width, pic.height)]
    if pic.format == gxtex.C4:
        data = bytes(vals[i] << 4 | vals[i + 1] for i in range(0, len(vals), 2))
    else:
        data = bytes(vals)
    out = bytearray(record)
    out[pic.pixel_off:pic.pixel_off + len(data)] = data
    colours = [gxtex.to_colour(pic.palette_format, c) for c in palette]
    colours += [0] * (pic.colours - len(colours))
    out[pic.palette_off:pic.palette_off + 2 * pic.colours] = struct.pack(">%dH" % pic.colours, *colours)
    return bytes(out)


def add_images(bank, new):
    """Add images to a bank: new = {name: (template image, RGBA bytes of the template's size)}.
    A sorted directory stays sorted; an unsorted one gets the new names at the end."""
    sort = bank.names == sorted(bank.names)
    for name, (template, rgba) in new.items():
        if name in bank.records:
            raise SystemExit("image %s exists" % name)
        bank.records[name] = encode_record(bank.records[template], rgba)
        bank.names.append(name)
    if sort:
        bank.names.sort()
    return bank


# .geo

def read_geo(data):
    """[(id, shapes)]; a shape is a list of items:
    ("solid", colour), ("texture", colour, flag, texture id, matrix), ("line style", colour, width),
    ("triangle", p0, p1, p2), ("line", p0, p1)."""
    count = struct.unpack_from("<I", data, 0)[0]
    offsets = struct.unpack_from("<%dI" % count, data, 4)
    records = []
    p = 4 + 4 * count
    for off in offsets:
        if off != p:
            raise ValueError("record at 0x%X, expected 0x%X" % (off, p))
        rid, nshapes = struct.unpack_from("<II", data, p)
        p += 8
        shapes = []
        for _ in range(nshapes):
            n = struct.unpack_from("<I", data, p)[0]
            p += 4
            items = []
            for _ in range(n):
                kind = struct.unpack_from("<I", data, p)[0]
                if kind == 0:
                    fill = struct.unpack_from("<I", data, p + 4)[0]
                    if fill == 1:
                        items.append(("solid", struct.unpack_from("<I", data, p + 8)[0]))
                        p += 12
                    elif fill == 0:
                        colour, flag, tex = struct.unpack_from("<III", data, p + 8)
                        items.append(("texture", colour, flag, tex, struct.unpack_from("<16f", data, p + 20)))
                        p += 84
                    elif fill == 2:
                        items.append(("line style",) + struct.unpack_from("<If", data, p + 8))
                        p += 16
                    else:
                        raise ValueError("record %d: fill style %d" % (rid, fill))
                elif kind in (1, 2):
                    pts = struct.unpack_from("<%df" % (9 if kind == 1 else 6), data, p + 4)
                    items.append(("triangle" if kind == 1 else "line",) +
                                 tuple(pts[i:i + 3] for i in range(0, len(pts), 3)))
                    p += 40 if kind == 1 else 28
                else:
                    raise ValueError("record %d: item kind %d" % (rid, kind))
            shapes.append(items)
        records.append((rid, shapes))
    if p != len(data):
        raise ValueError("parse ends at 0x%X of 0x%X" % (p, len(data)))
    return records


def build_geo(records):
    body = bytearray()
    offsets = []
    base = 4 + 4 * len(records)
    for rid, shapes in records:
        offsets.append(base + len(body))
        body += struct.pack("<II", rid, len(shapes))
        for items in shapes:
            body += struct.pack("<I", len(items))
            for it in items:
                if it[0] == "solid":
                    body += struct.pack("<III", 0, 1, it[1])
                elif it[0] == "texture":
                    body += struct.pack("<IIIII16f", 0, 0, it[1], it[2], it[3], *it[4])
                elif it[0] == "line style":
                    body += struct.pack("<IIIf", 0, 2, it[1], it[2])
                else:
                    body += struct.pack("<I", 1 if it[0] == "triangle" else 2)
                    body += b"".join(struct.pack("<3f", *pt) for pt in it[1:])
    return struct.pack("<%dI" % (len(records) + 1), len(records), *offsets) + bytes(body)


def add_shapes(records, new):
    """Add records copied from others: new = {id: (template id, {old texture id: new texture id})}.
    The records stay sorted by id as strings."""
    by_id = dict(records)
    for rid, (template, textures) in new.items():
        if rid in by_id:
            raise SystemExit("record %d exists" % rid)
        by_id[rid] = [[it[:3] + (textures.get(it[3], it[3]),) + it[4:] if it[0] == "texture" else it
                       for it in items] for items in by_id[template]]
    return sorted(by_id.items(), key=lambda r: str(r[0]))


# Commands

def load(index, args, ext):
    """The .gsh or .geo bytes named by args (NAME or -f FILE) and the rest of args."""
    if args and args[0] == "-f" and len(args) > 1:
        return open(args[1], "rb").read(), args[2:]
    if not args:
        raise SystemExit(__doc__)
    name = args[0].lower()
    if name in index or name + ext in index:
        return read_entry(index, name if name in index else name + ext), args[1:]
    for inner, data in nbig.get(index, args[0]):
        if inner.lower().endswith(ext):
            return data, args[1:]
    raise SystemExit("%s holds no %s" % (args[0], ext))


def banks(index):
    """[(name, bytes)] of every .gsh: the nested archives' and the loose ones."""
    out = []
    for name in nbig.archives(index):
        out += [(name + ":" + inner, data) for inner, data in nbig.load(read_entry(index, name))
                if inner.lower().endswith((".gsh", ".geo"))]
    out += [(n, read_entry(index, n)) for n in sorted(index) if n.endswith(".gsh")]
    return out


def writable(path):
    if path.replace("\\", "/").startswith("orig/"):
        raise SystemExit("refusing to write under orig/: %s" % path)
    return path


def cmd_list(bank):
    for name in bank.names:
        rec = bank.records[name]
        pic = Picture(rec)
        print("%-24s %4dx%-4d %-3s %3d colours  blocks %s" % (
            name, pic.width, pic.height, gxtex.FORMAT_NAMES[pic.format], pic.colours,
            " ".join("%02X" % t for t, _ in blocks(rec))))


def cmd_geo(records, want):
    for rid, shapes in records:
        if want and rid not in want:
            continue
        print("record %d: %d shapes" % (rid, len(shapes)))
        for items in shapes:
            for it in items:
                if it[0] == "texture":
                    m = it[4]
                    print("    texture %s colour %08X flag %d  [%g %g; %g %g] + (%g, %g)" % (
                        it[3], it[1], it[2], m[0], m[1], m[4], m[5], m[12], m[13]))
                elif it[0] in ("solid", "line style"):
                    print("    %s colour %08X%s" % (it[0], it[1], " width %g" % it[2] if len(it) > 2 else ""))
                else:
                    print("    %-8s %s" % (it[0], "  ".join("(%g, %g, %g)" % pt for pt in it[1:])))


def cmd_check(index):
    ok = True
    gsh = geo = images = 0
    for name, data in banks(index):
        try:
            if name.lower().endswith(".geo"):
                geo += 1
                if build_geo(read_geo(data)) != data:
                    raise ValueError("rebuilt file differs")
                continue
            gsh += 1
            bank = read_gsh(data)
            if build_gsh(bank) != data:
                raise ValueError("rebuilt file differs")
            for n in bank.names:
                pic = Picture(bank.records[n])
                pic.decode(bank.records[n])
                if pic.pixel_size != gxtex.data_size(pic.format, pic.width, pic.height):
                    raise ValueError("image %s: pixel size 0x%X" % (n, pic.pixel_size))
                images += 1
        except (ValueError, KeyError, StopIteration, struct.error) as e:
            print("%-64s %s" % (name, e))
            ok = False
    print("%d banks (%d images), %d .geo files, %s" % (gsh, images, geo,
                                                      "all rebuilt byte for byte" if ok else "INVALID"))
    sys.exit(0 if ok else 1)


def main(argv):
    cmd = argv[1] if len(argv) > 1 else ""
    if cmd == "set" and len(argv) >= 5:
        bank = read_gsh(open(argv[2], "rb").read())
        for edit in argv[4:]:
            if "=" not in edit:
                raise SystemExit(__doc__)
            name, path = edit.split("=", 1)
            if name not in bank.records:
                raise SystemExit("no image %s" % name)
            pic = Picture(bank.records[name])
            w, h, rgba = gxtex.read_png(open(path, "rb").read())
            if (w, h) != (pic.width, pic.height):
                raise SystemExit("%s is %dx%d, image %s is %dx%d" % (path, w, h, name, pic.width, pic.height))
            bank.records[name] = encode_record(bank.records[name], rgba)
        open(writable(argv[3]), "wb").write(build_gsh(bank))
        return
    if cmd not in ("list", "decode", "geo", "check"):
        raise SystemExit(__doc__)
    index = read_big_index()
    if cmd == "check":
        cmd_check(index)
    elif cmd == "geo":
        data, rest = load(index, argv[2:], ".geo")
        cmd_geo(read_geo(data), {int(x) for x in rest})
    else:
        data, rest = load(index, argv[2:], ".gsh")
        bank = read_gsh(data)
        if cmd == "list":
            cmd_list(bank)
            return
        if not rest:
            raise SystemExit(__doc__)
        out = writable(rest[0])
        os.makedirs(out, exist_ok=True)
        for name in rest[1:] or bank.names:
            rec = bank.records[name]
            pic = Picture(rec)
            path = os.path.join(out, name + ".png")
            open(path, "wb").write(gxtex.write_png(pic.width, pic.height, pic.decode(rec)))
            print("wrote %s" % path)


if __name__ == "__main__":
    main(sys.argv)
