typedef struct AXVPB {
    unsigned char pad0[24];
    unsigned long index;      // 24
    unsigned long sync;       // 28
    unsigned char pad2[8];    // 32
    unsigned long extraCount; // 40
} AXVPB;

extern unsigned char lbl_80657100[];
extern unsigned long lbl_8066FAC8;

#define U16(base, off) (*(unsigned short*)((unsigned char*)(base) + (off)))
#define S16(base, off) (*(short*)((unsigned char*)(base) + (off)))
#define U32(base, off) (*(unsigned long*)((unsigned char*)(base) + (off)))

void __AXServiceVPB(AXVPB* p)
{
    unsigned char* pb;
    unsigned char* mirror = (unsigned char*)p + 312;
    unsigned long flags;
    unsigned long n;
    unsigned char* base = lbl_80657100;
    unsigned long* dst;
    unsigned long* src;

    lbl_8066FAC8++;
    pb = base + p->index * 244;
    flags = p->sync;

    if (flags == 0) {
        U16(mirror, 14) = U16(pb, 14);
        U16(mirror, 100) = U16(pb, 100);
        U16(mirror, 122) = U16(pb, 122);
        U16(mirror, 124) = U16(pb, 124);
        return;
    }

    if (flags & 0x80000000) {
        unsigned long* d = (unsigned long*)pb;
        unsigned long* s = (unsigned long*)mirror;
        d[0] = s[0];
        d[1] = s[1];
        d[2] = s[2];
        d[3] = s[3];
        d[4] = s[4];
        d[5] = s[5];
        d[6] = s[6];
        d[7] = s[7];
        d[8] = s[8];
        d[9] = s[9];
        d[10] = s[10];
        d[11] = s[11];
        d[12] = s[12];
        d[13] = s[13];
        d[14] = s[14];
        d[15] = s[15];
        d[16] = s[16];
        d[17] = s[17];
        d[18] = s[18];
        d[19] = s[19];
        d[20] = s[20];
        d[21] = s[21];
        d[22] = s[22];
        d[23] = s[23];
        d[24] = s[24];
        d[25] = s[25];
        d[26] = s[26];
        d[27] = s[27];
        d[28] = s[28];
        d[29] = s[29];
        d[30] = s[30];
        d[31] = s[31];
        d[32] = s[32];
        d[33] = s[33];
        d[34] = s[34];
        d[35] = s[35];
        d[36] = s[36];
        d[37] = s[37];
        d[38] = s[38];
        d[39] = s[39];
        d[40] = s[40];
        d[41] = s[41];
        d[42] = s[42];
        d[43] = s[43];
        d[44] = s[44];
        d[45] = s[45];
        d[46] = s[46];
        d[47] = s[47];
        d[48] = s[48];
        d[49] = s[49];
        d[50] = s[50];
        d[51] = s[51];

        n = p->extraCount;
        if (n != 0) {
            src = (unsigned long*)&((unsigned char (*)[256])(base + 0x4D00))[p->index];
            dst = (unsigned long*)((unsigned char*)p + 52);
            for (; n != 0; n--) {
                *dst++ = *src++;
            }
        }
        return;
    }

    if (flags & 0x1) {
        U16(pb, 8) = U16(mirror, 8);
        U16(pb, 10) = U16(mirror, 10);
    }
    if (flags & 0x2) {
        U16(pb, 12) = U16(mirror, 12);
    }
    if (flags & 0x4) {
        U16(pb, 14) = U16(mirror, 14);
    } else {
        U16(mirror, 14) = U16(pb, 14);
    }
    if (flags & 0x8) {
        U16(pb, 16) = U16(mirror, 16);
    }
    if (flags & 0x10) {
        U16(pb, 18) = U16(mirror, 18);
        U16(pb, 20) = U16(mirror, 20);
        U16(pb, 22) = U16(mirror, 22);
        U16(pb, 24) = U16(mirror, 24);
        U16(pb, 26) = U16(mirror, 26);
        U16(pb, 28) = U16(mirror, 28);
        U16(pb, 30) = U16(mirror, 30);
        U16(pb, 32) = U16(mirror, 32);
        U16(pb, 34) = U16(mirror, 34);
        U16(pb, 36) = U16(mirror, 36);
        U16(pb, 38) = U16(mirror, 38);
        U16(pb, 40) = U16(mirror, 40);
        U16(pb, 42) = U16(mirror, 42);
        U16(pb, 44) = U16(mirror, 44);
        U16(pb, 46) = U16(mirror, 46);
        U16(pb, 48) = U16(mirror, 48);
        U16(pb, 50) = U16(mirror, 50);
        U16(pb, 52) = U16(mirror, 52);
    }
    if (flags & 0x40) {
        U16(pb, 64) = U16(mirror, 64);
        U16(pb, 66) = U16(mirror, 66);
    } else if (flags & 0x20) {
        unsigned long* z;
        U16(pb, 54) = U16(mirror, 54);
        U16(pb, 56) = U16(mirror, 56);
        U16(pb, 58) = U16(mirror, 58);
        U16(pb, 60) = U16(mirror, 60);
        U16(pb, 62) = U16(mirror, 62);
        U16(pb, 64) = U16(mirror, 64);
        U16(pb, 66) = U16(mirror, 66);
        z = *(unsigned long**)((unsigned char*)p + 308);
        z[0] = 0;
        z[1] = 0;
        z[2] = 0;
        z[3] = 0;
        z[4] = 0;
        z[5] = 0;
        z[6] = 0;
        z[7] = 0;
        z[8] = 0;
        z[9] = 0;
        z[10] = 0;
        z[11] = 0;
        z[12] = 0;
        z[13] = 0;
        z[14] = 0;
        z[15] = 0;
    }
    if (flags & 0x80) {
        U16(pb, 68) = U16(mirror, 68);
        U16(pb, 70) = U16(mirror, 70);
        U16(pb, 72) = U16(mirror, 72);
        U16(pb, 74) = U16(mirror, 74);
        U16(pb, 76) = U16(mirror, 76);

        n = p->extraCount;
        if (n != 0) {
            dst = (unsigned long*)((unsigned char (*)[256])(base + 0x4D00))[p->index];
            src = (unsigned long*)((unsigned char*)p + 52);
            for (; n != 0; n--) {
                *dst++ = *src++;
            }
        }
    }
    if (flags & 0x100) {
        U16(pb, 82) = U16(mirror, 82);
        U16(pb, 84) = U16(mirror, 84);
        U16(pb, 86) = U16(mirror, 86);
        U16(pb, 88) = U16(mirror, 88);
        U16(pb, 90) = U16(mirror, 90);
        U16(pb, 92) = U16(mirror, 92);
        U16(pb, 94) = U16(mirror, 94);
        U16(pb, 96) = U16(mirror, 96);
        U16(pb, 98) = U16(mirror, 98);
    }
    if (flags & 0x400) {
        U16(mirror, 100) = U16(pb, 100);
        S16(pb, 102) = S16(mirror, 102);
    } else if (flags & 0x200) {
        U16(pb, 100) = U16(mirror, 100);
        S16(pb, 102) = S16(mirror, 102);
    }
    if (flags & 0x800) {
        U16(pb, 104) = U16(mirror, 104);
        U16(pb, 106) = U16(mirror, 106);
        U16(pb, 108) = U16(mirror, 108);
    }
    if (flags & 0x1E000) {
        if (flags & 0x2000) {
            U16(pb, 110) = U16(mirror, 110);
        }
        if (flags & 0x4000) {
            U32(pb, 114) = U32(mirror, 114);
        }
        if (flags & 0x8000) {
            U32(pb, 118) = U32(mirror, 118);
        }
        if (flags & 0x10000) {
            U32(pb, 122) = U32(mirror, 122);
        } else {
            U32(mirror, 122) = U32(pb, 122);
        }
    } else if (flags & 0x1000) {
        U32(pb, 110) = U32(mirror, 110);
        U32(pb, 114) = U32(mirror, 114);
        U32(pb, 118) = U32(mirror, 118);
        U32(pb, 122) = U32(mirror, 122);
    } else {
        U16(mirror, 122) = U16(pb, 122);
        U16(mirror, 124) = U16(pb, 124);
    }
    if (flags & 0x20000) {
        U32(pb, 126) = U32(mirror, 126);
        U32(pb, 130) = U32(mirror, 130);
        U32(pb, 134) = U32(mirror, 134);
        U32(pb, 138) = U32(mirror, 138);
        U32(pb, 142) = U32(mirror, 142);
        U32(pb, 146) = U32(mirror, 146);
        U32(pb, 150) = U32(mirror, 150);
        U32(pb, 154) = U32(mirror, 154);
        U32(pb, 158) = U32(mirror, 158);
        U32(pb, 162) = U32(mirror, 162);
    }
    if (flags & 0x80000) {
        U16(pb, 166) = U16(mirror, 166);
        U16(pb, 168) = U16(mirror, 168);
    } else if (flags & 0x40000) {
        U16(pb, 166) = U16(mirror, 166);
        U16(pb, 168) = U16(mirror, 168);
        U16(pb, 170) = U16(mirror, 170);
        U16(pb, 172) = U16(mirror, 172);
        U16(pb, 174) = U16(mirror, 174);
        U16(pb, 176) = U16(mirror, 176);
        U16(pb, 178) = U16(mirror, 178);
    }
    if (flags & 0x100000) {
        U16(pb, 180) = U16(mirror, 180);
        U16(pb, 182) = U16(mirror, 182);
        U16(pb, 184) = U16(mirror, 184);
    }
    if (flags & 0x400000) {
        U16(pb, 190) = U16(mirror, 190);
        U16(pb, 192) = U16(mirror, 192);
        return;
    }
    if (flags & 0x200000) {
        U16(pb, 186) = U16(mirror, 186);
        U16(pb, 188) = U16(mirror, 188);
        U16(pb, 190) = U16(mirror, 190);
        U16(pb, 192) = U16(mirror, 192);
    }
}
