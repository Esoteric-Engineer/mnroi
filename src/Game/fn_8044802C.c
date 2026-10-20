// GX render-state cache: each setter compares against the cached field and calls GX only on change.
extern void fn_8021D694(void *self, int v);
extern void fn_8044895C(void *self, int v);
extern void GXSetZMode(unsigned char compareEnable, int func, unsigned char updateEnable);
extern void GXSetColorUpdate(unsigned char enable);
extern void GXSetNumTexGens(unsigned char n);
extern void GXSetNumChans(unsigned char n);
extern void GXSetNumTevStages(int n);
extern void GXSetNumIndStages(unsigned char n);

void fn_8044802C(register int *self, register int v)
{
    if (*self != v)
    {
        fn_8021D694(self, v);
    }
}

void fn_80448078(register char *self)
{
    if (*(unsigned char *)(self + 0x4) != 3)
    {
        *(unsigned char *)(self + 0x4) = 3;
        GXSetZMode(1, 3, 0);
        fn_8044895C(self, 1);
    }
}

void fn_804480DC(register char *self)
{
    if (*(unsigned char *)(self + 0x4) != 2)
    {
        *(unsigned char *)(self + 0x4) = 2;
        GXSetZMode(0, 3, 0);
        fn_8044895C(self, 1);
    }
}

void fn_80448140(register char *self)
{
    if (*(unsigned char *)(self + 0x4) != 7)
    {
        *(unsigned char *)(self + 0x4) = 7;
        GXSetZMode(1, 7, 1);
        fn_8044895C(self, 1);
    }
}

void fn_804481A4(register char *self, register int enable)
{
    if (*(int *)(self + 0x44) != enable)
    {
        GXSetColorUpdate(enable);
        *(int *)(self + 0x44) = enable;
    }
}

void fn_804481F4(register char *self, register int n)
{
    if (n != *(unsigned char *)(self + 0xA))
    {
        *(unsigned char *)(self + 0xA) = n;
        GXSetNumTexGens(*(unsigned char *)(self + 0xA));
    }
}

void fn_80448250(register char *self, register int n)
{
    n = 1;
    if (n != *(unsigned char *)(self + 0xB))
    {
        *(unsigned char *)(self + 0xB) = n;
        GXSetNumChans(*(unsigned char *)(self + 0xB));
    }
}

void fn_804482B0(register char *self, register int stages, register int ind)
{
    if (stages != *(unsigned char *)(self + 0x9))
    {
        *(unsigned char *)(self + 0x9) = stages;
        GXSetNumTevStages(stages);
    }
    if (ind != *(unsigned short *)(self + 0x12))
    {
        *(unsigned short *)(self + 0x12) = ind;
        GXSetNumIndStages(ind);
    }
}
