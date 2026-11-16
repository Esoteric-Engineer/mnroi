// cSoundEvent: plays sound param 0 when param 1 (the trigger mode) matches (docs/story.md row 8, section 4.1).

inline int sn_return_decl(int a) { return a; }

struct cScript {
    char d[0x24];
    char *vptr; // +0x24
};

struct cSoundEvent : cScript { // 0x2C
    int played; // +0x28, set once mode 3 has played
    cSoundEvent() __asm__("fn_804694FC");
};

extern char lbl_805723F4[];

extern "C" {

void fn_80435238(void *p, int v);
int fn_80079068(cScript *self, unsigned int i);
int fn_802128E0(cSoundEvent *self);
int fn_80212928(cSoundEvent *self);

void fn_802126F8(register cSoundEvent *self) // slot 3
{
    self->played = 0;
}

void fn_80212720(register cSoundEvent *self) // slot 4
{
    if (fn_80212928(self) == 0)
        fn_80435238(lbl_805723F4, fn_802128E0(self));
}

void fn_80212780(register cSoundEvent *self, int h, int other, int value) // slot 14
{
    if (self->played != 0 || fn_80212928(self) != 3)
        return;
    self->played = 1;
    fn_80435238(lbl_805723F4, fn_802128E0(self));
}

void fn_80212808(register cSoundEvent *self, int a, int b, int kind, float x, float y, float z, float w, int value) // slot 23
{
    if (fn_80212928(self) != 1)
        return;
    fn_80435238(lbl_805723F4, fn_802128E0(self));
}

cScript *fn_8021288C(register cSoundEvent *self)
{
    return new cSoundEvent;
}

int fn_802128E0(register cSoundEvent *self)
{
    return fn_80079068(self, 0);
}

int fn_80212928(register cSoundEvent *self)
{
    return fn_80079068(self, 1);
}

}
