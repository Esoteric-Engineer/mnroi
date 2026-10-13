// Property 0x14 (CASTID, guess) handler: copies the name into self+0xDC. Notes: docs/versus.md section 5, Step 17.

extern "C" {
char *strncpy(char *d, const char *s, unsigned int n);
char *strlwr(char *s);
}

struct Ent {
    char pad[0xDC];
    char name[0x1F]; // +0xDC
    char term; // +0xFB
};

extern "C" int fn_800AC750(Ent *self, int *prop, int arg)
{
    Ent *e = self; // dead local: the DOL copies self to a frame slot
    switch (prop[0]) {
    case 0x14:
        strncpy(self->name, (char *)(prop + 1), 0x20);
        self->term = 0;
        strlwr(self->name);
        return 1;
    default:
        return 0;
    }
}
