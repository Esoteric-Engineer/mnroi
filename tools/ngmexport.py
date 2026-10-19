#!/usr/bin/env python3
"""Export the models of the bundles Bundles/<name>.ngm to glTF 2.0: mesh, skeleton, skin weights,
materials and textures (docs/characters.md section 4; the file layout is in tools/ngmtool.py).

Usage (from repo root):
  python3 tools/ngmexport.py export NAME OUT_DIR [MODEL ...]      One bundle (NAME: wolverine)
  python3 tools/ngmexport.py export -f FILE OUT_DIR [MODEL ...]   The same from an extracted or edited .ngm
  python3 tools/ngmexport.py check                                Convert every model in memory

`export` writes each model of the bundle, or only the MODELs named (Wolverine.nod or Wolverine), to
OUT_DIR/<model>.glb (a .NOC model keeps its extension: amdoor_static.NOC -> amdoor_static_NOC.glb). With --gltf right after `export` it writes <model>.gltf, <model>.bin and the
textures as .png files instead. A bundle from -f takes its textures from the .ngt and .tpl next to
it when they are there, else from CLASH.BIG. It never writes under orig/.

What the export makes of the file:
  Vertices    Position, normal (Misc/NormalTable.ngn) and UV (s16 / 512). The game is Z-up and
              glTF Y-up: (x, y, z) becomes (x, z, -y).
  Triangles   One primitive per mesh record: its strip (degenerate triangles dropped, odd ones
              turned) and its list.
  Skeleton    One joint per node, node_00 on; the file has no names and no rotations, so the rest
              pose is the node positions and each inverse bind matrix a translation. Every vertex
              is skinned: a type-2 vertex to its three nodes, type 1 to its node, type 0 to its
              mesh's one node.
  Materials   One per part, from the part's block in Materials/Shaders/*.nsa (the first one when a
              name has several, guess). The first `texture` is the base colour and the shader sets
              the alpha mode, masked MASK and alpha, add, glass, alphamultiply BLEND (guesses from
              the names). Materials are one-sided: the engine starts with GX_CULL_FRONT, which
              keeps these triangles, but fn_8046E020 changes the mode per draw (not traced). The
              block's keys are kept in the material's extras.
  Textures    By name: the image of the bundle's .tpl at the name's line in its .ngt (the two
              always have the same count), then Bundles/global.*, then a loose <name>.tpl
              anywhere in CLASH.BIG. Which one the game prefers is not traced. Image 0 only.
  Not exported  The attachment records (0x50 each), and the mesh records' three u8s, which
              are not understood.

check builds every model of every bundle without writing, verifies the indices, joints and
weights, and lists the parts with no material block and the textures it cannot find.
"""

import json
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from nvbtool import read_big_index, read_entry  # noqa: E402
from ngmtool import STRIDE, ngm_entries, parse  # noqa: E402
from gxtex import decode, read_tpl, write_png  # noqa: E402

NORMALS = "Misc/NormalTable.ngn"
NSA = ["Materials/Shaders/%s.nsa" % n for n in ("shaders", "definitions", "editor", "constraints")]
GLOBAL = "bundles/global"
UV_SCALE = 1.0 / 512
BLEND = ("alpha", "add", "glass", "alphamultiply")
WRAP = {0: 33071, 1: 10497, 2: 33648}  # GX_CLAMP, GX_REPEAT, GX_MIRROR

FLOAT, UBYTE, USHORT = 5126, 5121, 5123
ARRAY_BUFFER, ELEMENT_ARRAY_BUFFER = 34962, 34963


def to_gltf(v):
    return (v[0], v[2], -v[1])


def read_normals(index):
    data = read_entry(index, NORMALS)
    n = struct.unpack_from(">H", data, 0)[0]
    return [to_gltf(struct.unpack_from(">3f", data, 2 + 12 * i)) for i in range(n)]


def parse_nsa(text, out):
    """Add each block of a .nsa material library to out, {lowercased name: (name, [(key, value)])}."""
    depth, name, keys = 0, None, None
    for line in text.splitlines():
        line = line.split("//")[0].strip()
        if not line or line.startswith(";"):
            continue
        if line.startswith("{"):
            depth += 1  # "{" opens the block; "{ps2" and "{xbox" open a platform's override
            continue
        if line.startswith("}"):
            depth -= 1
            if depth == 0 and name is not None:
                out.setdefault(name.lower(), (name, keys))
                name = None
            continue
        if depth == 0:
            name, keys = line.split()[0], []
        elif depth == 1:
            key, _, value = line.partition(" ") if " " in line else line.partition("\t")
            keys.append((key.split()[0], value.strip()))


def read_materials(index):
    out = {}
    for path in NSA:
        parse_nsa(read_entry(index, path).decode("latin-1"), out)
    return out


def decode_tpl(data, image):
    """(width, height, RGBA bytes, wrap s, wrap t) of one image of a TPL file."""
    im = read_tpl(data)[0][image]
    return im.width, im.height, decode(im.format, im.base(), im.width, im.height), im.header[4], im.header[5]


class Textures:
    """Finds a texture by name: the bundle's .ngt/.tpl, then global's, then a loose .tpl."""

    def __init__(self, index, bundle_files):
        self.index = index
        self.sources = []  # ({lowercased name: image}, tpl bytes)
        for ngt, tpl in bundle_files + [self.archive_pair(GLOBAL)]:
            if ngt is not None and tpl is not None:
                names = ngt.decode("latin-1").split()
                self.sources.append(({n.lower(): i for i, n in reversed(list(enumerate(names)))}, tpl))
        self.loose = {}
        for name in sorted(index):
            if name.endswith(".tpl") and not name.startswith("bundles/"):
                self.loose.setdefault(os.path.basename(name)[:-4], name)

    def archive_pair(self, base):
        get = lambda ext: read_entry(self.index, base + ext) if base + ext in self.index else None
        return get(".ngt"), get(".tpl")

    def find(self, name):
        """(tpl bytes, image) or None."""
        for names, tpl in self.sources:
            if name.lower() in names:
                return tpl, names[name.lower()]
        loose = self.loose.get(name.lower())
        return (read_entry(self.index, loose), 0) if loose else None


# glTF

class Builder:
    def __init__(self):
        self.bin = bytearray()
        self.views, self.accessors = [], []

    def view(self, blob, target=None):
        while len(self.bin) % 4:
            self.bin.append(0)
        v = {"buffer": 0, "byteOffset": len(self.bin), "byteLength": len(blob)}
        if target:
            v["target"] = target
        self.bin += blob
        self.views.append(v)
        return len(self.views) - 1

    def accessor(self, ctype, kind, fmt, values, target, bounds=False):
        flat = [x for v in values for x in v] if kind != "SCALAR" else values
        a = {"bufferView": self.view(struct.pack("<%d%s" % (len(flat), fmt), *flat), target),
             "componentType": ctype, "count": len(values), "type": kind}
        if bounds:
            a["min"] = [min(v[i] for v in values) for i in range(3)]
            a["max"] = [max(v[i] for v in values) for i in range(3)]
        self.accessors.append(a)
        return len(self.accessors) - 1


def strip_triangles(ix):
    out = []
    for i in range(len(ix) - 2):
        a, b, c = ix[i], ix[i + 1], ix[i + 2]
        if a != b and b != c and a != c:
            out.append((a, b, c) if i % 2 == 0 else (b, a, c))
    return out


class Model:
    """One model of a bundle, decoded from the offsets ngmtool.parse_body found."""

    def __init__(self, data, body, normals):
        self.name, self.parts = body.name, body.parts
        self.uvs = [(u * UV_SCALE, v * UV_SCALE)
                    for u, v in struct.iter_unpack(">hh", data[body.uvs:body.uvs + 4 * body.uv_count])]
        indices = struct.unpack_from(">%dH" % body.index_count, data, body.indices)
        self.world, self.parent = [], []
        for i in range(body.node_count):
            off = body.nodes + 0x22 * i
            b = struct.unpack_from(">3f", data, off + 0x10)
            self.world.append(to_gltf((-b[0], -b[1], -b[2])))
            self.parent.append(struct.unpack_from(">b", data, off + 0x20)[0])
        streams = []
        for kind, refs, n, verts, m in body.streams:
            refs = struct.unpack_from(">%dH" % (3 * n), data, refs)
            streams.append((kind, refs, verts))
        self.meshes, self.errors = [], []
        start, off = [0] * len(streams), 0
        for part, stream, strips, lists, count, _, nodes in body.meshes:
            kind, refs, verts = streams[stream]
            lo = start[stream]
            start[stream] += count
            tris = strip_triangles(indices[off:off + strips])
            tris += [tuple(indices[i:i + 3]) for i in range(off + strips, off + strips + lists, 3)]
            off += strips + lists
            if any(not lo <= i < lo + count for t in tris for i in t):
                self.errors.append("%s: a mesh index outside its render vertices" % self.name)
                continue
            mesh = {"part": part, "tris": [tuple(i - lo for i in t) for t in tris],
                    "pos": [], "nrm": [], "uv": [], "joints": [], "weights": []}
            for r in range(lo, lo + count):
                vi, ni, ui = refs[3 * r:3 * r + 3]
                p = verts + vi * STRIDE[kind]
                mesh["pos"].append(to_gltf(struct.unpack_from(">3f", data, p)))
                mesh["nrm"].append(normals[ni])
                if self.uvs:
                    mesh["uv"].append(self.uvs[ui])
                if kind == 2:
                    w = struct.unpack_from(">3f", data, p + 12)
                    j = tuple(data[p + 24:p + 27])
                    total = sum(w)
                    if abs(total - 1) > 1e-3:
                        self.errors.append("%s: weights sum to %g" % (self.name, total))
                    w = tuple(x / total for x in w) if total else (1.0, 0.0, 0.0)
                else:
                    j = (struct.unpack_from(">I", data, p + 12)[0] if kind == 1 else nodes[0],)
                    w = (1.0,)
                if max(j) >= len(self.world):
                    self.errors.append("%s: vertex names node %d of %d" % (self.name, max(j), len(self.world)))
                mesh["joints"].append((j + (0, 0, 0))[:4])
                mesh["weights"].append((w + (0.0, 0.0, 0.0))[:4])
            self.meshes.append(mesh)

    def gltf(self, materials, textures, separate):
        """(glTF JSON, binary buffer, {png name: bytes}), with the images in the buffer unless separate."""
        g = Builder()
        mats, images, image_files, tex_index = [], [], {}, {}
        samplers, gl_textures = [], []
        for part in self.parts:
            name, keys = materials.get(part.lower(), (part, None))
            m = {"name": part, "pbrMetallicRoughness": {"metallicFactor": 0.0, "roughnessFactor": 1.0}}
            shader = next((v.split()[0].lower() for k, v in keys or () if k.lower() == "shader" and v), "")
            texname = next((v.split()[0] for k, v in keys or () if k.lower() == "texture" and v), part)
            if keys is not None:
                m["extras"] = {"nsa": [[k, v] for k, v in keys]}
            if shader == "masked":
                m["alphaMode"], m["alphaCutoff"] = "MASK", 0.5
            elif shader in BLEND:
                m["alphaMode"] = "BLEND"
            if texname.lower() not in tex_index:
                tex_index[texname.lower()] = None
                found = textures.find(texname)
                if found:
                    w, h, rgba, ws, wt = decode_tpl(*found)
                    blob = write_png(w, h, rgba)
                    if separate:
                        image_files[texname + ".png"] = blob
                        images.append({"name": texname, "uri": texname + ".png"})
                    else:
                        images.append({"name": texname, "mimeType": "image/png", "bufferView": g.view(blob)})
                    samplers.append({"magFilter": 9729, "minFilter": 9729,
                                     "wrapS": WRAP.get(ws, 10497), "wrapT": WRAP.get(wt, 10497)})
                    gl_textures.append({"source": len(images) - 1, "sampler": len(samplers) - 1})
                    tex_index[texname.lower()] = len(gl_textures) - 1
            if tex_index[texname.lower()] is not None:
                m["pbrMetallicRoughness"]["baseColorTexture"] = {"index": tex_index[texname.lower()]}
            mats.append(m)

        prims = []
        for mesh in self.meshes:
            if not mesh["tris"]:
                continue
            attrs = {"POSITION": g.accessor(FLOAT, "VEC3", "f", mesh["pos"], ARRAY_BUFFER, True),
                     "NORMAL": g.accessor(FLOAT, "VEC3", "f", mesh["nrm"], ARRAY_BUFFER),
                     "JOINTS_0": g.accessor(UBYTE, "VEC4", "B", mesh["joints"], ARRAY_BUFFER),
                     "WEIGHTS_0": g.accessor(FLOAT, "VEC4", "f", mesh["weights"], ARRAY_BUFFER)}
            if mesh["uv"]:
                attrs["TEXCOORD_0"] = g.accessor(FLOAT, "VEC2", "f", mesh["uv"], ARRAY_BUFFER)
            ix = g.accessor(USHORT, "SCALAR", "H", [i for t in mesh["tris"] for i in t], ELEMENT_ARRAY_BUFFER)
            prims.append({"attributes": attrs, "indices": ix, "material": mesh["part"]})

        nodes = [{"name": model_stem(self.name), "mesh": 0, "skin": 0}]
        roots = []
        for i, (pos, parent) in enumerate(zip(self.world, self.parent)):
            local = pos if parent < 0 else tuple(pos[k] - self.world[parent][k] for k in range(3))
            nodes.append({"name": "node_%02d" % i, "translation": list(local)})
            if parent < 0:
                roots.append(1 + i)
            else:
                nodes[1 + parent].setdefault("children", []).append(1 + i)
        ibm = [(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -p[0], -p[1], -p[2], 1) for p in self.world]
        skin = {"joints": list(range(1, 1 + len(self.world))),
                "inverseBindMatrices": g.accessor(FLOAT, "MAT4", "f", ibm, None)}
        if roots:
            skin["skeleton"] = roots[0]

        doc = {"asset": {"version": "2.0", "generator": "mnroi tools/ngmexport.py"},
               "scene": 0, "scenes": [{"name": self.name, "nodes": [0] + roots}],
               "nodes": nodes, "meshes": [{"name": model_stem(self.name), "primitives": prims}],
               "skins": [skin], "materials": mats}
        if gl_textures:
            doc.update(textures=gl_textures, images=images, samplers=samplers)
        doc.update(accessors=g.accessors, bufferViews=g.views, buffers=[{"byteLength": len(g.bin)}])
        return doc, bytes(g.bin), image_files


def model_stem(name):
    stem, ext = os.path.splitext(name)
    if ext.lower() != ".nod":
        stem += ext.replace(".", "_")
    return stem.replace("/", "_").replace("\\", "_")


def glb(doc, blob):
    text = json.dumps(doc, separators=(",", ":")).encode()
    text += b" " * (-len(text) % 4)
    blob += b"\0" * (-len(blob) % 4)
    body = (struct.pack("<I4s", len(text), b"JSON") + text + struct.pack("<I4s", len(blob), b"BIN\0") + blob)
    return struct.pack("<4sII", b"glTF", 2, 12 + len(body)) + body


def find_ngm(index, name):
    for cand in (name, "bundles/%s" % name, "bundles/%s.ngm" % name):
        if cand.lower() in index:
            return cand.lower()
    raise SystemExit("no bundle %s in CLASH.BIG (python3 tools/ngmtool.py list)" % name)


def cmd_export(index, args):
    separate = bool(args) and args[0] == "--gltf"
    args = args[1:] if separate else args
    if len(args) < 2 or (args[0] == "-f" and len(args) < 3):
        raise SystemExit(__doc__)
    if args[0] == "-f":
        path, out, wanted = args[1], args[2], args[3:]
        data = open(path, "rb").read()
        base = os.path.splitext(path)[0]
        side = lambda ext: open(base + ext, "rb").read() if os.path.exists(base + ext) else None
        archive = "bundles/" + os.path.basename(base).lower()
        get = lambda ext: side(ext) or (read_entry(index, archive + ext) if archive + ext in index else None)
        pair = (get(".ngt"), get(".tpl"))
    else:
        entry = find_ngm(index, args[0])
        out, wanted = args[1], args[2:]
        data = read_entry(index, entry)
        base = entry[:-4]
        pair = tuple(read_entry(index, base + ext) if base + ext in index else None for ext in (".ngt", ".tpl"))
    if os.path.abspath(out).startswith(os.path.abspath("orig") + os.sep) or out.replace("\\", "/").startswith("orig/"):
        raise SystemExit("refusing to write under orig/")
    normals, materials = read_normals(index), read_materials(index)
    textures = Textures(index, [pair])
    _, models, _ = parse(data)
    wanted = {w.lower() for w in wanted}
    os.makedirs(out, exist_ok=True)
    done = 0
    for rec, body in models:
        if wanted and body.name.lower() not in wanted and model_stem(body.name).lower() not in wanted:
            continue
        model = Model(data, body, normals)
        for e in sorted(set(model.errors)):
            print("warning: " + e)
        doc, blob, files = model.gltf(materials, textures, separate)
        stem = os.path.join(out, model_stem(body.name))
        if separate:
            doc["buffers"][0]["uri"] = os.path.basename(stem) + ".bin"
            open(stem + ".bin", "wb").write(blob)
            for name, png_bytes in files.items():
                open(os.path.join(out, name), "wb").write(png_bytes)
            open(stem + ".gltf", "w").write(json.dumps(doc, indent=1))
            written = stem + ".gltf"
        else:
            open(stem + ".glb", "wb").write(glb(doc, blob))
            written = stem + ".glb"
        tris = sum(len(m["tris"]) for m in model.meshes)
        untextured = [m["name"] for m in doc["materials"] if "baseColorTexture" not in m["pbrMetallicRoughness"]]
        print("wrote %s: %d triangles, %d joints, %d materials%s" % (
            written, tris, len(model.world), len(doc["materials"]),
            "; no texture for " + ", ".join(untextured) if untextured else ""))
        done += 1
    if not done:
        raise SystemExit("no model of that name in the bundle (python3 tools/ngmtool.py list)")


def cmd_check(index):
    normals, materials = read_normals(index), read_materials(index)
    loose = {os.path.basename(n)[:-4] for n in index if n.endswith(".tpl") and not n.startswith("bundles/")}
    global_names = {n.lower() for n in read_entry(index, GLOBAL + ".ngt").decode("latin-1").split()}
    errors, no_block, no_texture = [], set(), set()
    count = tris = 0
    for entry in ngm_entries(index):
        data = read_entry(index, entry)
        base = entry[:-4]
        names = set(global_names)
        if base + ".ngt" in index:
            names |= {n.lower() for n in read_entry(index, base + ".ngt").decode("latin-1").split()}
        for rec, body in parse(data)[1]:
            model = Model(data, body, normals)
            errors += model.errors
            count += 1
            tris += sum(len(m["tris"]) for m in model.meshes)
            for part in body.parts:
                name, keys = materials.get(part.lower(), (part, None))
                if keys is None:
                    no_block.add(part)
                tex = next((v.split()[0] for k, v in keys or () if k.lower() == "texture" and v), part)
                if tex.lower() not in names and tex.lower() not in loose:
                    no_texture.add(tex)
    for e in sorted(set(errors)):
        print(e)
    print("parts with no material block (%d): %s" % (len(no_block), ", ".join(sorted(no_block))))
    print("textures not found (%d): %s" % (len(no_texture), ", ".join(sorted(no_texture))))
    print("%d models, %d triangles, %s" % (count, tris, "no errors" if not errors else "%d ERRORS" % len(errors)))
    sys.exit(1 if errors else 0)


def main(argv):
    if len(argv) < 2 or argv[1] not in ("export", "check"):
        raise SystemExit(__doc__)
    index = read_big_index()
    if argv[1] == "check":
        cmd_check(index)
    cmd_export(index, argv[2:])


if __name__ == "__main__":
    main(sys.argv)
