typedef int BOOL;
typedef unsigned long u32;
typedef long s32;
typedef void (*DVDLowCallback)(u32);

typedef struct {
    s32 cmd;
    void* addr;
    u32 length;
    u32 offset;
    DVDLowCallback callback;
} DVDCommand;

extern u32 WorkAroundSeekLocation;
extern s32 NextCommandNumber;
extern DVDCommand CommandList[3];

BOOL DVDLowSeek(u32 offset, DVDLowCallback callback);

void SeekTwiceBeforeRead(void* addr, u32 length, u32 offset, DVDLowCallback callback)
{
    u32 newOffset;
    DVDCommand* list = CommandList;
    if ((offset & ~0x7FFF) == 0) {
        newOffset = 0;
    } else {
        newOffset = (offset & ~0x7FFF) + WorkAroundSeekLocation;
    }
    list[0].cmd = 2;
    list[0].offset = newOffset;
    list[0].callback = callback;
    list[1].cmd = 1;
    list[1].addr = addr;
    list[1].length = length;
    list[1].offset = offset;
    list[1].callback = callback;
    list[2].cmd = -1;
    NextCommandNumber = 0;
    DVDLowSeek(newOffset, callback);
}
