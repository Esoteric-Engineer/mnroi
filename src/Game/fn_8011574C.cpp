// fn_8011574C fills the two sound-event registries of lbl_80568DB0 with callbacks, keyed (bank << 9) | event; fn_80116C84 frees them. docs/characters.md section 5.
// The real name is unknown, so the symbol stays extern "C".

#define KEY(bank, event) (((bank) << 9) | (event))

struct Banks
{
    void *fallback; // +0x0
    void *events;   // +0x4
    int bank;       // +0x8
    int event;      // +0xC
    int arg;        // +0x10
    char pad[0x4];
};

extern Banks lbl_80568DB0;
extern const char lbl_804979DC[];

extern "C" {
void fn_80116C84();
void fn_801B4524(void *registry, int flag);
void *fn_801B4284(int capacity, const char *name);
void fn_801B4764(void *registry, int key, void (*callback)());
void fn_8010FC54();
void fn_8010FCA8();
void fn_8010FD28();
void fn_8010FD4C();
void fn_8010FDC0();
void fn_8010FE34();
void fn_8011056C();
void fn_8011063C();
void fn_80110968();
void fn_801109F8();
void fn_80110AA0();
void fn_80110B40();
void fn_80110D00();
void fn_80110DC4();
void fn_80110EA4();
void fn_80110F24();
void fn_80110FB8();
void fn_80111050();
void fn_80111110();
void fn_80111134();
void fn_801111DC();
void fn_801114A0();
void fn_80111540();
void fn_801115B0();
void fn_801115FC();
void fn_801116B0();
void fn_80111730();
void fn_801117D8();
void fn_80111854();
void fn_80116D1C();
void fn_80116D54();
void fn_80116D8C();
void fn_80116DC4();
void fn_80116DFC();
void fn_80116E20();
void fn_80116E58();
void fn_80116E90();
void fn_80116EC8();
void fn_80116F00();
void fn_80116F38();
void fn_80116F78();
void fn_80116FB8();
void fn_80116FDC();
void fn_80117014();
void fn_8011704C();
}

extern "C" void fn_8011574C()
{
    fn_80116C84();
    lbl_80568DB0.fallback = fn_801B4284(0x10C, lbl_804979DC);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 35), fn_80110D00);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 36), fn_80110D00);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 37), fn_80110D00);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 38), fn_80110D00);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 40), fn_80111050);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 51), fn_80110B40);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 20), fn_80110B40);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 19), fn_80111134);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 13), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 120), fn_801109F8);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 46), fn_80110DC4);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 118), fn_80110EA4);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 116), fn_80110968);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 10), fn_80110968);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 11), fn_80110968);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 22), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 21), fn_801115FC);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 39), fn_80110FB8);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 42), fn_80116F78);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 14), fn_8011056C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 121), fn_80116F38);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 15), fn_801116B0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 122), fn_80111730);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 34), fn_8010FC54);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 130), fn_801111DC);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 131), fn_801111DC);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 132), fn_801111DC);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 133), fn_801111DC);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 134), fn_801111DC);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 135), fn_801111DC);
    fn_801B4764(lbl_80568DB0.fallback, KEY(2000, 136), fn_801111DC);
    fn_801B4764(lbl_80568DB0.fallback, KEY(510, 49), fn_8010FD4C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(510, 50), fn_8010FDC0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(200, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(201, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(210, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(202, 12), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(202, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(211, 12), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(211, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(206, 12), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(206, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(207, 47), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(207, 119), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(201, 31), fn_80111110);
    fn_801B4764(lbl_80568DB0.fallback, KEY(201, 32), fn_80111110);
    fn_801B4764(lbl_80568DB0.fallback, KEY(223, 12), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(223, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(224, 12), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(224, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(227, 12), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(227, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(228, 12), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(228, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(229, 12), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(229, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(230, 12), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(230, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(231, 12), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(231, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(232, 12), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(232, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(239, 12), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(239, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(244, 12), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(244, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(248, 12), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(248, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(212, 12), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(212, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(219, 12), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(219, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(220, 12), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(220, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(221, 12), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(221, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(222, 12), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(222, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(216, 12), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(216, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(217, 12), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(217, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(249, 12), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(249, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(205, 12), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(205, 9), fn_8010FE34);
    fn_801B4764(lbl_80568DB0.fallback, KEY(250, 1), fn_801114A0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(251, 1), fn_801114A0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(252, 1), fn_801114A0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(253, 1), fn_801114A0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(254, 1), fn_801114A0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(255, 1), fn_801114A0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(275, 1), fn_801114A0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(276, 1), fn_801114A0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(280, 1), fn_801114A0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(281, 1), fn_801114A0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(284, 1), fn_801114A0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(285, 1), fn_801114A0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(279, 1), fn_801115B0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(289, 1), fn_801114A0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(278, 1), fn_801114A0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(204, 1), fn_8010FCA8);
    fn_801B4764(lbl_80568DB0.fallback, KEY(209, 1), fn_8010FD28);
    fn_801B4764(lbl_80568DB0.fallback, KEY(531, 1), fn_801114A0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(536, 1), fn_801114A0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(537, 1), fn_801114A0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(300, 112), fn_801117D8);
    fn_801B4764(lbl_80568DB0.fallback, KEY(300, 113), fn_80111854);
    fn_801B4764(lbl_80568DB0.fallback, KEY(3, 47), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(3, 119), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(3, 48), fn_80110F24);
    fn_801B4764(lbl_80568DB0.fallback, KEY(4, 47), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(4, 119), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(4, 48), fn_80110F24);
    fn_801B4764(lbl_80568DB0.fallback, KEY(17, 47), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(17, 119), fn_8011063C);
    fn_801B4764(lbl_80568DB0.fallback, KEY(17, 48), fn_80110F24);
    fn_801B4764(lbl_80568DB0.fallback, KEY(21, 0), fn_80111540);
    fn_801B4764(lbl_80568DB0.fallback, KEY(22, 0), fn_80111540);
    fn_801B4764(lbl_80568DB0.fallback, KEY(23, 0), fn_80111540);
    fn_801B4764(lbl_80568DB0.fallback, KEY(24, 0), fn_80111540);
    fn_801B4764(lbl_80568DB0.fallback, KEY(25, 0), fn_80111540);
    fn_801B4764(lbl_80568DB0.fallback, KEY(26, 0), fn_80111540);
    fn_801B4764(lbl_80568DB0.fallback, KEY(27, 0), fn_80111540);
    fn_801B4764(lbl_80568DB0.fallback, KEY(28, 0), fn_80111540);
    fn_801B4764(lbl_80568DB0.fallback, KEY(29, 0), fn_80111540);
    fn_801B4764(lbl_80568DB0.fallback, KEY(107, 7), fn_80110AA0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(185, 7), fn_80110AA0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(519, 7), fn_80110AA0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(524, 7), fn_80110AA0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(528, 7), fn_80110AA0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(526, 7), fn_80110AA0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(527, 7), fn_80110AA0);
    fn_801B4764(lbl_80568DB0.fallback, KEY(523, 7), fn_80110AA0);
    lbl_80568DB0.events = fn_801B4284(0x6A, lbl_804979DC);
    fn_801B4764(lbl_80568DB0.events, KEY(53, 1), fn_80116D8C);
    fn_801B4764(lbl_80568DB0.events, KEY(52, 1), fn_80116D1C);
    fn_801B4764(lbl_80568DB0.events, KEY(55, 1), fn_80116D54);
    fn_801B4764(lbl_80568DB0.events, KEY(51, 1), fn_80116DFC);
    fn_801B4764(lbl_80568DB0.events, KEY(54, 1), fn_80116DC4);
    fn_801B4764(lbl_80568DB0.events, KEY(57, 1), fn_80116FDC);
    fn_801B4764(lbl_80568DB0.events, KEY(58, 1), fn_80117014);
    fn_801B4764(lbl_80568DB0.events, KEY(14, 1), fn_8011704C);
    fn_801B4764(lbl_80568DB0.events, KEY(27, 1), fn_80116E58);
    fn_801B4764(lbl_80568DB0.events, KEY(28, 1), fn_80116E58);
    fn_801B4764(lbl_80568DB0.events, KEY(29, 1), fn_80116E58);
    fn_801B4764(lbl_80568DB0.events, KEY(265, 1), fn_80116E90);
    fn_801B4764(lbl_80568DB0.events, KEY(266, 1), fn_80116E90);
    fn_801B4764(lbl_80568DB0.events, KEY(257, 1), fn_80116E90);
    fn_801B4764(lbl_80568DB0.events, KEY(258, 1), fn_80116E90);
    fn_801B4764(lbl_80568DB0.events, KEY(259, 1), fn_80116E90);
    fn_801B4764(lbl_80568DB0.events, KEY(267, 1), fn_80116E90);
    fn_801B4764(lbl_80568DB0.events, KEY(269, 1), fn_80116E90);
    fn_801B4764(lbl_80568DB0.events, KEY(274, 1), fn_80116E90);
    fn_801B4764(lbl_80568DB0.events, KEY(277, 1), fn_80116E90);
    fn_801B4764(lbl_80568DB0.events, KEY(282, 1), fn_80116E90);
    fn_801B4764(lbl_80568DB0.events, KEY(283, 1), fn_80116E90);
    fn_801B4764(lbl_80568DB0.events, KEY(287, 1), fn_80116E90);
    fn_801B4764(lbl_80568DB0.events, KEY(288, 1), fn_80116E90);
    fn_801B4764(lbl_80568DB0.events, KEY(533, 1), fn_80116E90);
    fn_801B4764(lbl_80568DB0.events, KEY(534, 1), fn_80116E90);
    fn_801B4764(lbl_80568DB0.events, KEY(535, 1), fn_80116E90);
    fn_801B4764(lbl_80568DB0.events, KEY(132, 1), fn_80116EC8);
    fn_801B4764(lbl_80568DB0.events, KEY(50, 1), fn_80116EC8);
    fn_801B4764(lbl_80568DB0.events, KEY(144, 1), fn_80116EC8);
    fn_801B4764(lbl_80568DB0.events, KEY(110, 1), fn_80116EC8);
    fn_801B4764(lbl_80568DB0.events, KEY(131, 1), fn_80116EC8);
    fn_801B4764(lbl_80568DB0.events, KEY(145, 1), fn_80116EC8);
    fn_801B4764(lbl_80568DB0.events, KEY(130, 1), fn_80116EC8);
    fn_801B4764(lbl_80568DB0.events, KEY(186, 1), fn_80116EC8);
    fn_801B4764(lbl_80568DB0.events, KEY(264, 1), fn_80116EC8);
    fn_801B4764(lbl_80568DB0.events, KEY(117, 1), fn_80116EC8);
    fn_801B4764(lbl_80568DB0.events, KEY(107, 1), fn_80116EC8);
    fn_801B4764(lbl_80568DB0.events, KEY(506, 1), fn_80116EC8);
    fn_801B4764(lbl_80568DB0.events, KEY(516, 1), fn_80116EC8);
    fn_801B4764(lbl_80568DB0.events, KEY(175, 1), fn_80116EC8);
    fn_801B4764(lbl_80568DB0.events, KEY(517, 1), fn_80116EC8);
    fn_801B4764(lbl_80568DB0.events, KEY(519, 1), fn_80116EC8);
    fn_801B4764(lbl_80568DB0.events, KEY(169, 1), fn_80116EC8);
    fn_801B4764(lbl_80568DB0.events, KEY(518, 1), fn_80116EC8);
    fn_801B4764(lbl_80568DB0.events, KEY(522, 1), fn_80116EC8);
    fn_801B4764(lbl_80568DB0.events, KEY(524, 1), fn_80116EC8);
    fn_801B4764(lbl_80568DB0.events, KEY(528, 1), fn_80116EC8);
    fn_801B4764(lbl_80568DB0.events, KEY(526, 1), fn_80116EC8);
    fn_801B4764(lbl_80568DB0.events, KEY(527, 1), fn_80116EC8);
    fn_801B4764(lbl_80568DB0.events, KEY(56, 1), fn_80116F00);
    fn_801B4764(lbl_80568DB0.events, KEY(59, 1), fn_80116FB8);
    fn_801B4764(lbl_80568DB0.events, KEY(60, 1), fn_80116E20);
}

extern "C" void fn_80116C84()
{
    if (lbl_80568DB0.fallback != 0) {
        fn_801B4524(lbl_80568DB0.fallback, 1);
        lbl_80568DB0.fallback = 0;
    }
    if (lbl_80568DB0.events != 0) {
        fn_801B4524(lbl_80568DB0.events, 1);
        lbl_80568DB0.events = 0;
    }
}
