extern void DCFlushRange(void*, unsigned long);

extern unsigned char lbl_806570C0[];

extern long lbl_8066FA98;
extern long lbl_8066FA9C;
extern long lbl_8066FAA0;
extern long lbl_8066FAA4;
extern long lbl_8066FAA8;
extern long lbl_8066FAAC;
extern long lbl_8066FAB0;
extern long lbl_8066FAB4;
extern long lbl_8066FAB8;

#define UPDATE_STUDIO_LEVEL(accum, offset)                                   \
    level = (accum) / 160;                                                  \
                                                                              \
    if (level == 0)                                                         \
    {                                                                       \
        (accum) = 0;                                                        \
        *(long*)(studio + (offset)) = 0;                                    \
        *(short*)(studio + (offset) + 4) = 0;                               \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        if (level > 20)                                                     \
        {                                                                   \
            level = 20;                                                     \
        }                                                                   \
        else if (level < -20)                                              \
        {                                                                   \
            level = -20;                                                    \
        }                                                                   \
                                                                              \
        *(long*)(studio + (offset)) = (accum);                              \
        (accum) = (accum) - level * 160;                                    \
        *(short*)(studio + (offset) + 4) = (short)-level;                   \
    }

void __AXPrintStudio(void)
{
    long level;
    unsigned char* studio = lbl_806570C0;

    UPDATE_STUDIO_LEVEL(lbl_8066FA98, 0);
    UPDATE_STUDIO_LEVEL(lbl_8066FA9C, 6);
    UPDATE_STUDIO_LEVEL(lbl_8066FAA0, 12);
    UPDATE_STUDIO_LEVEL(lbl_8066FAA4, 18);
    UPDATE_STUDIO_LEVEL(lbl_8066FAA8, 24);
    UPDATE_STUDIO_LEVEL(lbl_8066FAAC, 30);
    UPDATE_STUDIO_LEVEL(lbl_8066FAB0, 36);
    UPDATE_STUDIO_LEVEL(lbl_8066FAB4, 42);
    UPDATE_STUDIO_LEVEL(lbl_8066FAB8, 48);

    DCFlushRange(studio, 0x36);
}
