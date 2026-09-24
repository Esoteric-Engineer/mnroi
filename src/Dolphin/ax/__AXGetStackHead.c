typedef struct AXVPB AXVPB;

extern AXVPB* lbl_8064F228[];

AXVPB* __AXGetStackHead(unsigned long stack)
{
    return lbl_8064F228[stack];
}
