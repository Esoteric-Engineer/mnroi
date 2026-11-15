#ifndef _STDARG_H
#define _STDARG_H

/* SN ProDG's <stdarg.h>: egcs's PowerPC V.4 va-ppc.h with SN's two changes, marked below (docs/prodg.md). */

typedef struct __va_list_tag {
    char gpr;               /* next of r3-r10 in the register save area */
    char fpr;               /* next of f1-f8 */
    char *overflow_arg_area; /* next argument passed on the stack */
    char *reg_save_area;    /* r3-r10, then f1-f8 */
} __va_list[1], __gnuc_va_list[1];

typedef __gnuc_va_list va_list;

typedef struct {
    long __gp_save[8];
    double __fp_save[8];
} __va_regsave_t;

#define __va_overflow(AP) (AP)->overflow_arg_area

#define __VA_FP_REGSAVE(AP, TYPE) \
    ((TYPE *)(void *)(&(((__va_regsave_t *)(AP)->reg_save_area)->__fp_save[(int)(AP)->fpr])))

#define __VA_GP_REGSAVE(AP, TYPE) \
    ((TYPE *)(void *)(&(((__va_regsave_t *)(AP)->reg_save_area)->__gp_save[(int)(AP)->gpr])))

/* SN copies the list by assignment; egcs used __builtin_memcpy, which calls memcpy at -O0 */
#define __va_start_common(AP, FAKE) (*(AP) = *(struct __va_list_tag *)__builtin_saveregs())

#define va_start(AP, LASTARG) (__builtin_next_arg(LASTARG), __va_start_common(AP, 0))

#define __va_float_p(TYPE) (__builtin_classify_type(*(TYPE *)0) == 8)
#define __va_longlong_p(TYPE) ((__builtin_classify_type(*(TYPE *)0) == 1) && (sizeof(TYPE) == 8))
#define __va_aggregate_p(TYPE) (__builtin_classify_type(*(TYPE *)0) >= 12)
#define __va_size(TYPE) ((sizeof(TYPE) + sizeof(long) - 1) / sizeof(long))

/* SN dereferences inside the statement expression (egcs: `*({ ... __ptr; })`), which keeps __ptr in r9 */
#define va_arg(AP, TYPE)                                                                       \
    __extension__(({                                                                              \
        register TYPE *__ptr;                                                                      \
                                                                                                   \
        if (__va_float_p(TYPE) && (AP)->fpr < 8) {                                                 \
            __ptr = __VA_FP_REGSAVE(AP, TYPE);                                                     \
            (AP)->fpr++;                                                                           \
        }                                                                                          \
                                                                                                   \
        else if (__va_aggregate_p(TYPE) && (AP)->gpr < 8) {                                        \
            __ptr = *__VA_GP_REGSAVE(AP, TYPE *);                                                  \
            (AP)->gpr++;                                                                           \
        }                                                                                          \
                                                                                                   \
        else if (!__va_float_p(TYPE) && !__va_aggregate_p(TYPE) && (AP)->gpr + __va_size(TYPE) <= 8 \
                 && (!__va_longlong_p(TYPE) || (AP)->gpr + __va_size(TYPE) <= 8)) {               \
            if (__va_longlong_p(TYPE) && ((AP)->gpr & 1) != 0)                                     \
                (AP)->gpr++;                                                                       \
                                                                                                   \
            __ptr = __VA_GP_REGSAVE(AP, TYPE);                                                     \
            (AP)->gpr += __va_size(TYPE);                                                          \
        }                                                                                          \
                                                                                                   \
        else if (!__va_float_p(TYPE) && !__va_aggregate_p(TYPE) && (AP)->gpr < 8) {                \
            (AP)->gpr = 8;                                                                         \
            __ptr = (TYPE *)(void *)(__va_overflow(AP));                                           \
            __va_overflow(AP) += __va_size(TYPE) * sizeof(long);                                   \
        }                                                                                          \
                                                                                                   \
        else if (__va_aggregate_p(TYPE)) {                                                         \
            __ptr = *(TYPE **)(void *)(__va_overflow(AP));                                         \
            __va_overflow(AP) += sizeof(TYPE *);                                                   \
        } else {                                                                                   \
            __ptr = (TYPE *)(void *)(__va_overflow(AP));                                           \
            __va_overflow(AP) += __va_size(TYPE) * sizeof(long);                                   \
        }                                                                                          \
                                                                                                   \
        *__ptr;                                                                                    \
    }))

#define va_end(AP) ((void)0)

#endif
