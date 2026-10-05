// Locale_GetString(String); the by-value String is destroyed here, through _._6String (Game/fn_804491DC.c).
class String {
public:
    char data[0x4C];
    String() __asm__("__6String");
    String(const String &s) __asm__("__6StringRC6String");
    ~String();
    void operator=(const char *s) __asm__("fn_80449A0C");
    const char *c_str() __asm__("fn_804496C8");
};

extern "C" const char *fn_8012F32C(void *locale, const char *key);
extern "C" void *fn_80427400();

inline int sn_return_decl(int a) { return a; }

String Locale_GetString(String key)
{
    String text;
    void *locale = fn_80427400();

    text = fn_8012F32C(locale, key.c_str());
    if (!key.c_str()) {
        return String(key);
    }
    return String(text);
}
