extern int __OSCurrHeap;

int OSSetCurrentHeap(int heap)
{
    int old = __OSCurrHeap;
    __OSCurrHeap = heap;
    return old;
}
