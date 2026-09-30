int __OSCurrHeap = -1;

int OSSetCurrentHeap(int heap)
{
    int old = __OSCurrHeap;
    __OSCurrHeap = heap;
    return old;
}
