typedef int BOOL;

typedef struct SIControl {
    long chan;
    unsigned int poll;
    unsigned int inputBytes;
    void* input;
    void* callback;
} SIControl;

typedef struct SIPacket {
    long chan;
    char pad[28];
} SIPacket;

extern SIControl Si;
extern SIPacket Packet[4];

BOOL SIIsChanBusy(long chan) {
    return Packet[chan].chan != -1 || Si.chan == chan;
}
