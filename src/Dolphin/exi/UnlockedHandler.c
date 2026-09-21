typedef unsigned long u32;
typedef long s32;

extern s32 fn_80195480(s32 chan, u32 dev, u32* id);

#pragma scheduling off
void UnlockedHandler(s32 chan, void* context)
{
    u32 id;

    fn_80195480(chan, 0, &id);
}
