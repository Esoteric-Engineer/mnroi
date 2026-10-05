// Control_ChangeScreen(String): NonMatching, docs/nonmatching.md.
class String {
public:
    char data[0x4C];
    ~String();
};

extern "C" {
const char *fn_804496C8(String *self);
void fn_8012D788(const char *screen);
}

inline int sn_return_decl(int a) { return a; }

void Control_ChangeScreen(String screen)
{
    fn_8012D788(fn_804496C8(&screen));
}
