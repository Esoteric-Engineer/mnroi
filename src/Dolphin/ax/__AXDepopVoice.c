typedef struct {
    unsigned char pad[0x52];
    short dpop[9];
} AXVPB;

extern unsigned long __AXSpbAL;
extern unsigned long __AXSpbAR;
extern unsigned long __AXSpbAS;
extern unsigned long __AXSpbAAL;
extern unsigned long __AXSpbAAR;
extern unsigned long __AXSpbAAS;
extern unsigned long __AXSpbABL;
extern unsigned long __AXSpbABR;
extern unsigned long __AXSpbABS;

void __AXDepopVoice(AXVPB* p)
{
    __AXSpbAL += p->dpop[0];
    __AXSpbAAL += p->dpop[1];
    __AXSpbABL += p->dpop[2];
    __AXSpbAR += p->dpop[3];
    __AXSpbAAR += p->dpop[4];
    __AXSpbABR += p->dpop[5];
    __AXSpbAS += p->dpop[6];
    __AXSpbAAS += p->dpop[7];
    __AXSpbABS += p->dpop[8];
}
