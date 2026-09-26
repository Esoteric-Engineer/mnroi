typedef struct {
    unsigned char pad[0x52];
    short dpop[9];
} AXVPB;

extern unsigned long lbl_8066FA98;
extern unsigned long lbl_8066FA9C;
extern unsigned long lbl_8066FAA0;
extern unsigned long lbl_8066FAA4;
extern unsigned long lbl_8066FAA8;
extern unsigned long lbl_8066FAAC;
extern unsigned long lbl_8066FAB0;
extern unsigned long lbl_8066FAB4;
extern unsigned long lbl_8066FAB8;

void __AXDepopVoice(AXVPB* p)
{
    lbl_8066FA98 += p->dpop[0];
    lbl_8066FAA4 += p->dpop[1];
    lbl_8066FAB0 += p->dpop[2];
    lbl_8066FA9C += p->dpop[3];
    lbl_8066FAA8 += p->dpop[4];
    lbl_8066FAB4 += p->dpop[5];
    lbl_8066FAA0 += p->dpop[6];
    lbl_8066FAAC += p->dpop[7];
    lbl_8066FAB8 += p->dpop[8];
}
