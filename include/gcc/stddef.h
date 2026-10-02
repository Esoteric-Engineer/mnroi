#ifndef _STDDEF_H
#define _STDDEF_H

/* Freestanding <stddef.h> for SN ProDG (GCC 2.95), which ships without headers.
   The type macros come from ngccc's own predefines. */

typedef __PTRDIFF_TYPE__ ptrdiff_t;
typedef __SIZE_TYPE__ size_t;
#ifndef __cplusplus
typedef __WCHAR_TYPE__ wchar_t;
#endif

#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void*)0)
#endif

#define offsetof(type, member) ((size_t) & ((type*)0)->member)

#endif
