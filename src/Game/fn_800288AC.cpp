// The first ten functions of the file that holds the command-line parser (docs/versus.md section 5, row 9c).
// Names are guesses: Version is the build-version record, Config the 8-byte flags object at lbl_8066D568.

inline int sn_return_decl(int a) { return a; }

extern "C" {
extern int sprintf(char *dst, const char *fmt, ...);
void fn_80431894(void *f, int on);
void fn_804318DC(void *f, int on);
void fn_80431924(void *f, int on);
void fn_8043196C(void *f, int on);
void fn_804319FC(void *f, int on);
void fn_80431A8C(void *f, int on);
void fn_80431AD4(void *f, int on);
void fn_80431B64(void *f, int on);
}

extern int lbl_8066D57C;
extern int lbl_8066D580;
extern char lbl_8052EB18[];
extern int lbl_8066B668;
extern int lbl_8066D570;
extern int lbl_8066D578;
extern int lbl_8066D574;
extern int lbl_8066B650;
extern int lbl_8066B64C;
extern "C" void fn_80430D0C(void *p, int v);

extern "C" {

void fn_800288AC() {}

int fn_800288C8() { return 1; }

int fn_800288EC() { return 1; }

void fn_80028910() {}

int fn_8002892C()
{
done:
    return 1;
}

}

class Version {
public:
    int major;   // +0x0
    int minor;   // +0x4
    int patch;   // +0x8
    int build;   // +0xC
    int pad10;
    const char *date; // +0x14
    char full[0x80];  // +0x18
    char shortv[0x20]; // +0x98
    Version();
};

Version::Version()
{
    major = 1;
    minor = 5;
    patch = 0x11;
    build = 0x117CC;
    date = "Aug 27 2005 01:28:06";
    sprintf(full, "RETAIL %d.%02d.%d (%d) %s", major, minor, patch, build, date);
    sprintf(shortv, "%d.%02d.%d", major, minor, patch);
}

class Config {
public:
    int a; // +0x0
    int b; // +0x4
    Config();
    ~Config();
    void fn_80028B08();
};

Config::Config()
{
    a = 0;
    b = 0;
    fn_80431894(this, 1);
    fn_804318DC(this, 1);
    fn_80431924(this, 1);
    fn_804319FC(this, 1);
    fn_8043196C(this, 1);
    fn_80431A8C(this, 0);
    fn_80431AD4(this, 0);
    fn_80431B64(this, 1);
}

Config::~Config() {}

void Config::fn_80028B08() {}

extern "C" void fn_80028B28()
{
    lbl_8066D57C = 1;
    lbl_8066D580 = 0;
    lbl_8052EB18[0] = 0;
    lbl_8066B668 = 0;
    fn_80430D0C(&lbl_8066D570, 0x18);
    fn_80430D0C(&lbl_8066D578, 0xFF);
    fn_80430D0C(&lbl_8066D574, 0);
    lbl_8066B650 = 0;
    lbl_8066B64C = 0;
}
