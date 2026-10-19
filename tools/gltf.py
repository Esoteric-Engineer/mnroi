#!/usr/bin/env python3
"""Read glTF 2.0 models (.glb, or .gltf with its .bin and images): accessors, node matrices, skins
and images. The input side of a new character's model; tools/ngmtool.py writes the .ngm.

Usage (from repo root):
  python3 tools/gltf.py info FILE     Meshes, primitives, skins, materials and images of a model
  python3 tools/gltf.py check         Export every model of CLASH.BIG with tools/ngmexport.py in
                                      memory, read it back and compare it with the .ngm

As a module: g = GLB(path or bytes); g.accessor(i) gives an accessor's values (tuples, or numbers for
SCALAR), g.world() each node's 4x4 matrix in the scene, g.image(i) an image as (width, height, RGBA
bytes) (PNG only), g.material_texture(m) the image of a material's base colour.

Matrices are 4x4 row-major lists of lists (glTF stores them column-major). glTF is Y-up and the game
Z-up; ngmexport writes (x, y, z) as (x, z, -y), and nothing here converts back.
"""

import json
import math
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from gxtex import read_png  # noqa: E402

COMP = {5120: "b", 5121: "B", 5122: "h", 5123: "H", 5125: "I", 5126: "f"}
NCOMP = {"SCALAR": 1, "VEC2": 2, "VEC3": 3, "VEC4": 4, "MAT2": 4, "MAT3": 9, "MAT4": 16}
NORM = {5120: 127.0, 5121: 255.0, 5122: 32767.0, 5123: 65535.0}


def mat_mul(a, b):
    return [[sum(a[i][k] * b[k][j] for k in range(4)) for j in range(4)] for i in range(4)]


def mat_vec(m, v, w=1.0):
    x, y, z = v
    return tuple(m[i][0] * x + m[i][1] * y + m[i][2] * z + m[i][3] * w for i in range(3))


def identity():
    return [[1.0 if i == j else 0.0 for j in range(4)] for i in range(4)]


def trs(t=(0, 0, 0), r=(0, 0, 0, 1), s=(1, 1, 1)):
    x, y, z, w = r
    m = [[1 - 2 * (y * y + z * z), 2 * (x * y - z * w), 2 * (x * z + y * w), t[0]],
         [2 * (x * y + z * w), 1 - 2 * (x * x + z * z), 2 * (y * z - x * w), t[1]],
         [2 * (x * z - y * w), 2 * (y * z + x * w), 1 - 2 * (x * x + y * y), t[2]],
         [0.0, 0.0, 0.0, 1.0]]
    for i in range(3):
        for j in range(3):
            m[i][j] *= s[j]
    return m


def col_major(v):
    return [[v[c * 4 + r] for c in range(4)] for r in range(4)]


def normalize(v):
    n = math.sqrt(sum(c * c for c in v)) or 1.0
    return tuple(c / n for c in v)


class GLB:
    def __init__(self, src):
        self.dir = ""
        if isinstance(src, str):
            self.dir = os.path.dirname(src)
            src = open(src, "rb").read()
        self.bin = b""
        if src[:4] == b"glTF":
            o = 12
            while o < len(src):
                n, t = struct.unpack_from("<II", src, o)
                chunk = src[o + 8:o + 8 + n]
                if t == 0x4E4F534A:
                    self.j = json.loads(chunk)
                elif t == 0x004E4942:
                    self.bin = chunk
                o += 8 + n
        else:
            self.j = json.loads(src)
            uri = self.j.get("buffers", [{}])[0].get("uri")
            if uri:
                self.bin = open(os.path.join(self.dir, uri), "rb").read()
        self._world = None

    def view(self, i):
        bv = self.j["bufferViews"][i]
        o = bv.get("byteOffset", 0)
        return self.bin[o:o + bv["byteLength"]], bv.get("byteStride")

    def accessor(self, i):
        a = self.j["accessors"][i]
        nc = NCOMP[a["type"]]
        fmt = COMP[a["componentType"]]
        size = struct.calcsize("<" + fmt)
        data, stride = self.view(a["bufferView"])
        base = a.get("byteOffset", 0)
        stride = stride or size * nc
        norm = a.get("normalized", False) and a["componentType"] in NORM
        out = []
        for k in range(a["count"]):
            v = struct.unpack_from("<%d%s" % (nc, fmt), data, base + k * stride)
            if norm:
                v = tuple(x / NORM[a["componentType"]] for x in v)
            out.append(v if nc > 1 else v[0])
        return out

    def local(self, n):
        node = self.j["nodes"][n]
        if "matrix" in node:
            return col_major(node["matrix"])
        return trs(node.get("translation", (0, 0, 0)), node.get("rotation", (0, 0, 0, 1)), node.get("scale", (1, 1, 1)))

    def world(self):
        """{node: 4x4 matrix in the scene}; self.parent maps each child to its parent."""
        if self._world is None:
            self.parent = {c: i for i, n in enumerate(self.j["nodes"]) for c in n.get("children", [])}
            w = {}

            def get(i):
                if i not in w:
                    w[i] = mat_mul(get(self.parent[i]), self.local(i)) if i in self.parent else self.local(i)
                return w[i]
            for i in range(len(self.j["nodes"])):
                get(i)
            self._world = w
        return self._world

    def image_bytes(self, i):
        im = self.j["images"][i]
        if "uri" in im:
            return open(os.path.join(self.dir, im["uri"]), "rb").read()
        return self.view(im["bufferView"])[0]

    def image(self, i):
        return read_png(self.image_bytes(i))

    def material_texture(self, mat):
        """The image index of material mat's base colour texture, or None."""
        t = self.j["materials"][mat].get("pbrMetallicRoughness", {}).get("baseColorTexture")
        return None if t is None else self.j["textures"][t["index"]].get("source")


def cmd_info(g):
    j = g.j
    for m in j.get("meshes", []):
        print("mesh %s" % m.get("name"))
        for p in m["primitives"]:
            a = p["attributes"]
            n = j["accessors"][a["POSITION"]]["count"]
            tris = j["accessors"][p["indices"]]["count"] // 3 if "indices" in p else n // 3
            print("    material %s: %d vertices, %d triangles, %s" % (
                p.get("material"), n, tris, " ".join(sorted(a))))
    for s in j.get("skins", []):
        print("skin: %d joints" % len(s["joints"]))
    for i, m in enumerate(j.get("materials", [])):
        print("material %d %s: image %s" % (i, m.get("name"), g.material_texture(i)))
    for i, im in enumerate(j.get("images", [])):
        w, h, _ = g.image(i)
        print("image %d %s: %dx%d" % (i, im.get("name"), w, h))


def cmd_check():
    import ngmexport as X
    from nvbtool import read_big_index, read_entry

    class NoTextures:
        def find(self, name):
            return None

    f32 = lambda v: struct.unpack("<%df" % len(v), struct.pack("<%df" % len(v), *v))
    index = read_big_index()
    normals, materials = X.read_normals(index), X.read_materials(index)
    errors, count = [], 0
    for entry in X.ngm_entries(index):
        data = read_entry(index, entry)
        for _, body in X.parse(data)[1]:
            model = X.Model(data, body, normals)
            doc, blob, _ = model.gltf(materials, NoTextures(), False)
            g = GLB(X.glb(doc, blob))
            count += 1
            meshes = [m for m in model.meshes if m["tris"]]
            prims = g.j["meshes"][0]["primitives"]
            bad = len(prims) != len(meshes)
            for p, m in zip(prims, meshes):
                a = p["attributes"]
                bad |= g.accessor(a["POSITION"]) != [f32(v) for v in m["pos"]]
                bad |= g.accessor(a["JOINTS_0"]) != m["joints"]
                bad |= g.accessor(p["indices"]) != [i for t in m["tris"] for i in t]
            world = g.world()
            for i, pos in enumerate(model.world):
                got = mat_vec(world[1 + i], (0.0, 0.0, 0.0))
                bad |= max(abs(got[k] - pos[k]) for k in range(3)) > 1e-4
            if bad:
                errors.append("%s %s: read back differs" % (entry, body.name))
    for e in errors:
        print(e)
    print("%d models exported and read back, %s" % (count, "all match" if not errors else "%d DIFFER" % len(errors)))
    sys.exit(1 if errors else 0)


def main(argv):
    if len(argv) == 2 and argv[1] == "check":
        cmd_check()
    if len(argv) == 3 and argv[1] == "info":
        cmd_info(GLB(argv[2]))
        return
    raise SystemExit(__doc__)


if __name__ == "__main__":
    main(sys.argv)
