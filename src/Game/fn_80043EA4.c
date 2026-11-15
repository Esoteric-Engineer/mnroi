// Chained-move camera: take the camera for a move, place it from the move entry, and give it back.
// The camera is the one fn_8043289C(lbl_80552110) returns; its matrix is at +0x360.

typedef struct Mat4 {
    float m[16];
} Mat4;

typedef struct MoveEntry {
    float m[16];        // +0x0, camera offset from the actor
    unsigned int modes; // +0x40
    int id;             // +0x44
    float f48;          // +0x48, passed to fn_8003C9B0
} MoveEntry;

typedef struct Camera {
    char pad0[0x360];
    float m360[16]; // +0x360
} Camera;

void fn_8042D7B0(Mat4 *m);
void fn_804356C8(Mat4 *dst, void *src);
void fn_8043570C(void *out, void *a, void *b);
void fn_80047A30(void *self, Mat4 *m);
void *fn_800B1668(void *actor);
void fn_8003C69C(Camera *cam);
void fn_8003C9B0(Camera *cam, float v);
Camera *fn_8043289C(char *g);
float fn_8043520C(Camera *cam);
int fn_800B13D8(void *actor);
int fn_800419E8(int a);
extern char lbl_80552110[];
extern int lbl_8066B744;    // a move camera is active
extern Camera *lbl_8066B750; // the camera in use
extern void *lbl_8066B754;  // the actor it follows
extern void *lbl_8066B758;  // the move list
extern int lbl_8066B764;    // the actor's id
extern int lbl_8066B818;
extern int lbl_8066B7A0;
extern int lbl_8066B700;
extern float lbl_8066D5E0; // the camera's fn_8043520C value before the move

void fn_80043EA4(MoveEntry *move, void *self, int adjust)
{
    Mat4 unused;
    Mat4 m;

    fn_8042D7B0(&unused);
    fn_8042D7B0(&m);
    fn_804356C8(&m, move);
    if (adjust)
        fn_80047A30(self, &m);
    fn_8043570C(lbl_8066B750->m360, fn_800B1668(lbl_8066B754), &m);
    fn_8003C69C(lbl_8066B750);
    fn_8003C9B0(lbl_8066B750, move->f48);
}

void fn_80043F60(void *self, void *list)
{
    int fresh;

    if (lbl_8066B744 == 0) {
    }
    lbl_8066B744 = 1;
    fresh = !lbl_8066B750;
    lbl_8066B750 = fn_8043289C(lbl_80552110);
    lbl_8066B754 = self;
    lbl_8066B758 = list;
    lbl_8066B818 = 1;
    lbl_8066B764 = fn_800B13D8(self);
    if (fresh)
        lbl_8066D5E0 = fn_8043520C(lbl_8066B750);
}

void fn_80044014(int force)
{
    if ((fn_800419E8(1) && lbl_8066B7A0 == 3) || force) {
        if (lbl_8066B750)
            fn_8003C9B0(lbl_8066B750, lbl_8066D5E0);
        lbl_8066B744 = 0;
        lbl_8066B818 = 0;
        lbl_8066B750 = 0;
        lbl_8066B700 = 0;
    }
}
