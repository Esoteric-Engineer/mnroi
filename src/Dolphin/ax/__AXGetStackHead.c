typedef struct AXVPB AXVPB;

AXVPB* __AXStackHead[32];
AXVPB* __AXStackTail[32];

AXVPB* __AXGetStackHead(unsigned long stack)
{
    return __AXStackHead[stack];
}
