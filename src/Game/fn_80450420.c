// Release the owner of record `index` in the 0x60-byte table lbl_80567760 and clear it, through fn_80456178.
// (docs/versus.md section 5, row 2)
typedef struct Record {
    void *owner; // +0x0
    char pad[0x5C];
} Record __attribute__((aligned(8)));

extern Record lbl_80567760[];
extern void fn_80456178(void *owner, int flags);

void fn_80450420(int index)
{
    if (lbl_80567760[index].owner)
    {
        void *owner = lbl_80567760[index].owner;
        if (owner)
        {
            fn_80456178(owner, 3);
        }
        else
        {
        }
        lbl_80567760[index].owner = 0;
    }
}
