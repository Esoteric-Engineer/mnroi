typedef struct __va_list_struct {
    char gpr;
    char fpr;
    char reserved[2];
    char* input_arg_area;
    char* reg_save_area;
} va_list[1];

extern int vprintf(const char* format, va_list arg);

void OSReport(const char* msg, ...)
{
    va_list args;
    __builtin_va_info(&args);
    vprintf(msg, args);
}
