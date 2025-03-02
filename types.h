/* types.h - v0.1 - public domain data structures - nickscha 2025

A C89 standard compliant, single header, nostdlib (no C Standard Library) type defines I use.

LICENSE

  Placed in the public domain and also MIT licensed.
  See end of file for detailed license information.

*/
#ifndef TYPES_H
#define TYPES_H

/* #############################################################################
 * # COMPILER SETTINGS
 * #############################################################################
 */
/* Check if using C99 or later (inline is supported) */
#if __STDC_VERSION__ >= 199901L
#define TYPES_INLINE inline
#elif defined(__GNUC__) || defined(__clang__)
#define TYPES_INLINE __inline__
#elif defined(_MSC_VER)
#define TYPES_INLINE __inline
#else
#define TYPES_INLINE
#endif

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef float f32;
typedef double f64;
typedef u8 b8;
typedef int b32;

#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif

#define U8_MAX 255U
#define U8_MIN 0U
#define U16_MAX 65535U
#define U16_MIN 0U
#define U32_MAX 4294967295U
#define U32_MIN 0U
#define I8_MAX 127
#define I8_MIN (-I8_MAX - 1)
#define I16_MAX 32767
#define I16_MIN (-I16_MAX - 1)
#define I32_MAX 2147483647
#define I32_MIN (-I32_MAX - 1)
#define BIT(n) (1U << (n))
#define BIT_SET(x, n) ((x) |= BIT(n))
#define BIT_CLEAR(x, n) ((x) &= (u8)~BIT(n))
#define BIT_TOGGLE(x, n) ((x) ^= BIT(n))
#define BIT_CHECK(x, n) (((x) & BIT(n)) != 0)

#define TYPES_STATIC_ASSERT(c, m) typedef char types_assert_##m[(c) ? 1 : -1]

TYPES_STATIC_ASSERT(sizeof(u8) == 1, u8_size_must_be_1);
TYPES_STATIC_ASSERT(sizeof(u16) == 2, u16_size_must_be_2);
TYPES_STATIC_ASSERT(sizeof(u32) == 4, u32_size_must_be_4);
TYPES_STATIC_ASSERT(sizeof(i8) == 1, i8_size_must_be_1);
TYPES_STATIC_ASSERT(sizeof(i16) == 2, i16_size_must_be_2);
TYPES_STATIC_ASSERT(sizeof(i32) == 4, i32_size_must_be_4);
TYPES_STATIC_ASSERT(sizeof(f32) == 4, f32_size_must_be_4);
TYPES_STATIC_ASSERT(sizeof(f64) == 8, f64_size_must_be_8);
TYPES_STATIC_ASSERT(sizeof(b8) == 1, b8_size_must_be_1);
TYPES_STATIC_ASSERT(sizeof(b32) == 4, b32_size_must_be_4);

/* #############################################################################
 * # 64-bit Integer Emulation for C89
 * #############################################################################
 */
typedef struct u64
{
  u32 low;
  u32 high;
} u64;

typedef struct i64
{
  i32 low;
  i32 high;
} i64;

TYPES_STATIC_ASSERT(sizeof(u64) == 8, u64_size_must_be_8);
TYPES_STATIC_ASSERT(sizeof(i64) == 8, i64_size_must_be_8);

/* #############################################################################
 * # 64-bit Integer Operations
 * #############################################################################
 */
TYPES_INLINE u64 u64_add(u64 a, u64 b)
{
  u64 result;
  result.low = a.low + b.low;
  result.high = a.high + b.high + (result.low < a.low);
  return result;
}

TYPES_INLINE u64 u64_sub(u64 a, u64 b)
{
  u64 result;
  result.low = a.low - b.low;
  result.high = a.high - b.high - (a.low < b.low);
  return result;
}

TYPES_INLINE u64 u64_and(u64 a, u64 b)
{
  u64 result;
  result.low = a.low & b.low;
  result.high = a.high & b.high;
  return result;
}

TYPES_INLINE u64 u64_or(u64 a, u64 b)
{
  u64 result;
  result.low = a.low | b.low;
  result.high = a.high | b.high;

  return result;
}

TYPES_INLINE u64 u64_xor(u64 a, u64 b)
{
  u64 result;
  result.low = a.low ^ b.low;
  result.high = a.high ^ b.high;
  return result;
}

TYPES_INLINE u64 u64_not(u64 a)
{
  u64 result;
  result.low = ~a.low;
  result.high = ~a.high;
  return result;
}

TYPES_INLINE u64 u64_nand(u64 a, u64 b)
{
  u64 result;
  result.low = ~(a.low & b.low);
  result.high = ~(a.high & b.high);

  return result;
}

TYPES_INLINE i64 i64_add(i64 a, i64 b)
{
  i64 result;
  result.low = a.low + b.low;
  result.high = a.high + b.high + (result.low < a.low);
  return result;
}

TYPES_INLINE i64 i64_sub(i64 a, i64 b)
{
  i64 result;
  result.low = a.low - b.low;
  result.high = a.high - b.high - (a.low < b.low);
  return result;
}

TYPES_INLINE i64 i64_and(i64 a, i64 b)
{
  i64 result;
  result.low = a.low & b.low;
  result.high = a.high & b.high;

  return result;
}

TYPES_INLINE i64 i64_or(i64 a, i64 b)
{
  i64 result;
  result.low = a.low | b.low;
  result.high = a.high | b.high;

  return result;
}

TYPES_INLINE i64 i64_xor(i64 a, i64 b)
{
  i64 result;
  result.low = a.low ^ b.low;
  result.high = a.high ^ b.high;

  return result;
}

TYPES_INLINE i64 i64_not(i64 a)
{
  i64 result;
  result.low = ~a.low;
  result.high = ~a.high;

  return result;
}

TYPES_INLINE i64 i64_nand(i64 a, i64 b)
{
  i64 result;
  result.low = ~(a.low & b.low);
  result.high = ~(a.high & b.high);

  return result;
}

#endif /* TYPES_H */

/*
   ------------------------------------------------------------------------------
   This software is available under 2 licenses -- choose whichever you prefer.
   ------------------------------------------------------------------------------
   ALTERNATIVE A - MIT License
   Copyright (c) 2025 nickscha
   Permission is hereby granted, free of charge, to any person obtaining a copy of
   this software and associated documentation files (the "Software"), to deal in
   the Software without restriction, including without limitation the rights to
   use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
   of the Software, and to permit persons to whom the Software is furnished to do
   so, subject to the following conditions:
   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
   ------------------------------------------------------------------------------
   ALTERNATIVE B - Public Domain (www.unlicense.org)
   This is free and unencumbered software released into the public domain.
   Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
   software, either in source code form or as a compiled binary, for any purpose,
   commercial or non-commercial, and by any means.
   In jurisdictions that recognize copyright laws, the author or authors of this
   software dedicate any and all copyright interest in the software to the public
   domain. We make this dedication for the benefit of the public at large and to
   the detriment of our heirs and successors. We intend this dedication to be an
   overt act of relinquishment in perpetuity of all present and future rights to
   this software under copyright law.
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
   WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
   ------------------------------------------------------------------------------
*/
