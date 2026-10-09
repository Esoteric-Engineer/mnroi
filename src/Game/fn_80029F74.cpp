// The static initializer of the command-line parser's file: four screen-edge floats, then the Config flags object and the Version record built in fn_800288AC.cpp.

extern float lbl_8066B630;
extern float lbl_8066B634;

class Config {
public:
    char data[8];
    Config();
    ~Config();
};

class Version {
public:
    char data[0xB8];
    Version();
};

float lbl_8066D558 = 320.0f - lbl_8066B630 * 0.5f;
float lbl_8066D55C = lbl_8066D558 + lbl_8066B630 * 0.5f;
float lbl_8066D560 = 240.0f - lbl_8066B634 * 0.5f;
float lbl_8066D564 = lbl_8066B634 * 0.5f + lbl_8066D560 - 12.0f;
Config lbl_8066D568;
Version lbl_8052EA60;
