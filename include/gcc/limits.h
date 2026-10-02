#ifndef _LIMITS_H
#define _LIMITS_H

/* Freestanding <limits.h> for SN ProDG (GCC 2.95), which ships without headers.
   Plain char is signed: cc1 sign-extends it (extsb), even though ngccc's
   preprocessor step defines __CHAR_UNSIGNED__. */

#define CHAR_BIT 8
#define MB_LEN_MAX 1

#define SCHAR_MIN (-128)
#define SCHAR_MAX 127
#define UCHAR_MAX 255

#define CHAR_MIN SCHAR_MIN
#define CHAR_MAX SCHAR_MAX

#define SHRT_MIN (-32768)
#define SHRT_MAX 32767
#define USHRT_MAX 65535

#define INT_MIN (-INT_MAX - 1)
#define INT_MAX 2147483647
#define UINT_MAX 4294967295U

#define LONG_MIN (-LONG_MAX - 1L)
#define LONG_MAX 2147483647L
#define ULONG_MAX 4294967295UL

#define LONG_LONG_MIN (-LONG_LONG_MAX - 1LL)
#define LONG_LONG_MAX 9223372036854775807LL
#define ULONG_LONG_MAX 18446744073709551615ULL

#endif
