// Draws a mesh by its stream's type; types 1, 2, 4 and 5 are skinned first (fn_802244BC).

struct Mesh {
    char pad0[0x3D];
    unsigned char stream; // +0x3D
};

struct Instance;
struct Renderer;

extern "C" {
int fn_8043C3C0(Mesh *mesh);
int fn_80430B30(Instance *inst);
void *fn_80466140(Instance *inst);
int fn_80223940(Renderer *self, Mesh *mesh, Instance *inst);
int fn_802237AC(Renderer *self, Mesh *mesh, void *p, Instance *inst);
void fn_802244BC(Instance *inst, unsigned char n);
int fn_80223B50(Renderer *self, Mesh *mesh, void *p, Instance *inst);
int fn_80223CC4(Renderer *self, Mesh *mesh, void *p, Instance *inst);

int fn_8022362C(register Renderer *self, Mesh *mesh, Instance *inst)
{
    switch (fn_8043C3C0(mesh)) {
    case 0:
    case 3:
        if (fn_80430B30(inst) && fn_80223940(self, mesh, inst))
            return 0;
        return fn_802237AC(self, mesh, fn_80466140(inst), inst);
    case 2:
    case 5:
        fn_802244BC(inst, mesh->stream);
        return fn_80223B50(self, mesh, fn_80466140(inst), inst);
    case 1:
    case 4:
        fn_802244BC(inst, mesh->stream);
        return fn_80223CC4(self, mesh, fn_80466140(inst), inst);
    default:
        return -1;
    }
}
}
