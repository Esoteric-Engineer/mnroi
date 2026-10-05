// Sets the line width kept at +0x4C and passes it on to GX in sixths of a pixel, when it changes.
typedef struct LineState
{
    char unk0[0x4C];
    float width; // +0x4C
} LineState;

extern void GXSetLineWidth(unsigned char width, int texOffsets);

void fn_80445E50(register LineState *self, register float width)
{
    if (width != self->width)
    {
        self->width = width;
        GXSetLineWidth((unsigned int)(self->width * 6.0f), 0);
    }
}
