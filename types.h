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
#define TYPES_API extern
#elif defined(__GNUC__) || defined(__clang__)
#define TYPES_INLINE __inline__
#define TYPES_API static
#elif defined(_MSC_VER)
#define TYPES_INLINE __inline
#define TYPES_API static
#else
#define TYPES_INLINE
#define TYPES_API static
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
  u32 low;
  i32 high;
} i64;

TYPES_STATIC_ASSERT(sizeof(u64) == 8, u64_size_must_be_8);
TYPES_STATIC_ASSERT(sizeof(i64) == 8, i64_size_must_be_8);

/* #############################################################################
 * # 64-bit Integer Operations
 * #############################################################################
 */

/* ---- Bitwise Operators (Unsigned) ---- */
TYPES_API TYPES_INLINE u64 u64_and(u64 a, u64 b)
{
  u64 r;
  r.high = a.high & b.high;
  r.low = a.low & b.low;
  return r;
}

TYPES_API TYPES_INLINE u64 u64_or(u64 a, u64 b)
{
  u64 r;
  r.high = a.high | b.high;
  r.low = a.low | b.low;
  return r;
}

TYPES_API TYPES_INLINE u64 u64_xor(u64 a, u64 b)
{
  u64 r;
  r.high = a.high ^ b.high;
  r.low = a.low ^ b.low;
  return r;
}

TYPES_API TYPES_INLINE u64 u64_not(u64 a)
{
  u64 r;
  r.high = ~a.high;
  r.low = ~a.low;
  return r;
}

/* ---- Bitwise Operators (Signed) ---- */
TYPES_API TYPES_INLINE i64 i64_and(i64 a, i64 b)
{
  i64 r;
  r.high = a.high & b.high;
  r.low = a.low & b.low;
  return r;
}

TYPES_API TYPES_INLINE i64 i64_or(i64 a, i64 b)
{
  i64 r;
  r.high = a.high | b.high;
  r.low = a.low | b.low;
  return r;
}

TYPES_API TYPES_INLINE i64 i64_xor(i64 a, i64 b)
{
  i64 r;
  r.high = a.high ^ b.high;
  r.low = a.low ^ b.low;
  return r;
}

TYPES_API TYPES_INLINE i64 i64_not(i64 a)
{
  i64 r;
  r.high = ~a.high;
  r.low = ~a.low;
  return r;
}

/* ---- Unsigned Math ---- */
TYPES_API TYPES_INLINE u64 u64_add(u64 a, u64 b)
{
  u64 res;
  res.low = a.low + b.low;
  res.high = a.high + b.high + (res.low < a.low);
  return res;
}

TYPES_API TYPES_INLINE u64 u64_sub(u64 a, u64 b)
{
  u64 res;
  res.low = a.low - b.low;
  res.high = a.high - b.high - (a.low < b.low);
  return res;
}

TYPES_API TYPES_INLINE u64 u64_shl(u64 a, int n)
{
  u64 res = {0, 0};
  if (n >= 64)
  {
    res.high = 0;
    res.low = 0;
  }
  else if (n >= 32)
  {
    res.high = a.low << (n - 32);
    res.low = 0;
  }
  else if (n > 0)
  {
    res.high = (a.high << n) | (a.low >> (32 - n));
    res.low = a.low << n;
  }
  else
  {
    res = a;
  }
  return res;
}

TYPES_API TYPES_INLINE u64 u64_shr(u64 a, int n)
{
  u64 res = {0, 0};
  if (n >= 64)
  {
    res.high = 0;
    res.low = 0;
  }
  else if (n >= 32)
  {
    res.low = a.high >> (n - 32);
    res.high = 0;
  }
  else if (n > 0)
  {
    res.low = (a.low >> n) | (a.high << (32 - n));
    res.high = a.high >> n;
  }
  else
  {
    res = a;
  }
  return res;
}

TYPES_API TYPES_INLINE u64 u64_mul(u64 a, u64 b)
{
  u64 res;
  u32 a_low = a.low, a_high = a.high;
  u32 b_low = b.low, b_high = b.high;

  u32 low_low = (a_low & 0xFFFF) * (b_low & 0xFFFF);
  u32 low_high = (a_low >> 16) * (b_low & 0xFFFF);
  u32 high_low = (a_low & 0xFFFF) * (b_low >> 16);
  u32 high_high = (a_low >> 16) * (b_low >> 16);

  u32 mid = low_high + high_low;
  u32 mid_loww = (mid & 0xFFFF) << 16;
  u32 mid_highgh = (mid >> 16);

  u32 carry;

  res.low = low_low + mid_loww;
  carry = (res.low < low_low);

  res.high = a_high * b_low + a_low * b_high + high_high + mid_highgh + carry;

  return res;
}

TYPES_API TYPES_INLINE u64 u64_div(u64 dividend, u64 divisor)
{
  u64 quotient = {0, 0};
  u64 remainder = {0, 0};
  int i;

  for (i = 63; i >= 0; --i)
  {
    remainder = u64_shl(remainder, 1);
    if ((dividend.high >> 31) & 1)
    {
      remainder.low |= 1;
    }
    dividend = u64_shl(dividend, 1);

    if ((remainder.high > divisor.high) ||
        (remainder.high == divisor.high && remainder.low >= divisor.low))
    {
      remainder = u64_sub(remainder, divisor);
      quotient.low |= 1;
    }

    quotient = u64_shl(quotient, 1);
  }

  quotient = u64_shr(quotient, 1);
  return quotient;
}

TYPES_API TYPES_INLINE u64 u64_mod(u64 dividend, u64 divisor)
{
  u64 remainder = {0, 0};
  int i;

  for (i = 63; i >= 0; --i)
  {
    remainder = u64_shl(remainder, 1);
    if ((dividend.high >> 31) & 1)
    {
      remainder.low |= 1;
    }
    dividend = u64_shl(dividend, 1);

    if ((remainder.high > divisor.high) ||
        (remainder.high == divisor.high && remainder.low >= divisor.low))
    {
      remainder = u64_sub(remainder, divisor);
    }
  }

  return remainder;
}

/* ---- Signed Math ---- */
TYPES_API TYPES_INLINE i64 i64_add(i64 a, i64 b)
{
  i64 res;
  u64 ua;
  u64 ub;
  u64 ur;

  ua.low = a.low;
  ua.high = (u32)a.high;

  ub.low = b.low;
  ub.high = (u32)b.high;

  ur = u64_add(ua, ub);

  res.high = (i32)ur.high;
  res.low = ur.low;
  return res;
}

TYPES_API TYPES_INLINE i64 i64_sub(i64 a, i64 b)
{
  i64 res;
  u64 ua;
  u64 ub;
  u64 ur;

  ua.low = a.low;
  ua.high = (u32)a.high;

  ub.low = b.low;
  ub.high = (u32)b.high;

  ur = u64_sub(ua, ub);

  res.high = (i32)ur.high;
  res.low = ur.low;

  return res;
}

TYPES_API TYPES_INLINE i64 i64_shl(i64 a, int n)
{
  u64 ua;
  u64 ur;
  i64 res;

  ua.low = a.low;
  ua.high = (u32)a.high;

  ur = u64_shl(ua, n);

  res.low = ur.low;
  res.high = (i32)ur.high;

  return res;
}

TYPES_API TYPES_INLINE i64 i64_shr(i64 a, int n)
{
  i64 res = a;
  if (n >= 64)
  {
    res.high = (a.high < 0) ? -1 : 0;
    res.low = 0;
  }
  else if (n >= 32)
  {
    res.low = (u32)a.high >> (n - 32);
    res.high = (a.high < 0) ? -1 : 0;
  }
  else if (n > 0)
  {
    res.low = (a.low >> n) | ((u32)a.high << (32 - n));
    res.high >>= n;
  }
  return res;
}

TYPES_API TYPES_INLINE i64 i64_neg(i64 a)
{
  u64 zero = {0, 0};
  u64 ua;
  u64 ur;
  i64 res;

  ua.low = a.low;
  ua.high = (u32)a.high;

  ur = u64_sub(zero, ua);

  res.low = ur.low;
  res.high = (i32)ur.high;

  return res;
}

TYPES_API TYPES_INLINE i64 i64_mul(i64 a, i64 b)
{
  int neg = 0;
  u64 ua, ub, ur;
  i64 res;

  if (a.high < 0)
  {
    a = i64_neg(a);
    neg = !neg;
  }
  if (b.high < 0)
  {
    b = i64_neg(b);
    neg = !neg;
  }

  ua.high = (u32)a.high;
  ua.low = a.low;
  ub.high = (u32)b.high;
  ub.low = b.low;

  ur = u64_mul(ua, ub);

  if (neg)
  {
    u64 zero = {0, 0};
    ur = u64_sub(zero, ur);
  }

  res.high = (i32)ur.high;
  res.low = ur.low;
  return res;
}

TYPES_API TYPES_INLINE i64 i64_div(i64 a, i64 b)
{
  int neg = 0;
  u64 ua, ub, uq;
  i64 res;

  if (a.high < 0)
  {
    a = i64_neg(a);
    neg = !neg;
  }
  if (b.high < 0)
  {
    b = i64_neg(b);
    neg = !neg;
  }

  ua.high = (u32)a.high;
  ua.low = a.low;
  ub.high = (u32)b.high;
  ub.low = b.low;

  uq = u64_div(ua, ub);

  if (neg)
  {
    u64 zero = {0, 0};
    uq = u64_sub(zero, uq);
  }

  res.high = (i32)uq.high;
  res.low = uq.low;
  return res;
}

TYPES_API TYPES_INLINE i64 i64_mod(i64 a, i64 b)
{
  i64 q = i64_div(a, b);
  i64 p = i64_mul(q, b);
  return i64_sub(a, p);
}

/* ---- Unsigned Comparisons ---- */
TYPES_API TYPES_INLINE int u64_eq(u64 a, u64 b)
{
  return a.high == b.high && a.low == b.low;
}

TYPES_API TYPES_INLINE int u64_ne(u64 a, u64 b)
{
  return !u64_eq(a, b);
}

TYPES_API TYPES_INLINE int u64_lt(u64 a, u64 b)
{
  if (a.high < b.high)
  {
    return 1;
  }
  if (a.high > b.high)
  {
    return 0;
  }
  return a.low < b.low;
}

TYPES_API TYPES_INLINE int u64_le(u64 a, u64 b)
{
  if (a.high < b.high)
  {
    return 1;
  }
  if (a.high > b.high)
  {
    return 0;
  }
  return a.low <= b.low;
}

TYPES_API TYPES_INLINE int u64_gt(u64 a, u64 b)
{
  return u64_lt(b, a);
}

TYPES_API TYPES_INLINE int u64_ge(u64 a, u64 b)
{
  return u64_le(b, a);
}

/* ---- Signed Comparisons ---- */
TYPES_API TYPES_INLINE int i64_eq(i64 a, i64 b)
{
  return a.high == b.high && a.low == b.low;
}

TYPES_API TYPES_INLINE int i64_ne(i64 a, i64 b)
{
  return !i64_eq(a, b);
}

TYPES_API TYPES_INLINE int i64_lt(i64 a, i64 b)
{
  if (a.high < b.high)
  {
    return 1;
  }
  if (a.high > b.high)
  {
    return 0;
  }
  return a.low < b.low;
}

TYPES_API TYPES_INLINE int i64_le(i64 a, i64 b)
{
  if (a.high < b.high)
  {
    return 1;
  }
  if (a.high > b.high)
  {
    return 0;
  }
  return a.low <= b.low;
}

TYPES_API TYPES_INLINE int i64_gt(i64 a, i64 b)
{
  return i64_lt(b, a);
}

TYPES_API TYPES_INLINE int i64_ge(i64 a, i64 b)
{
  return i64_le(b, a);
}

/* Conversion functions */
TYPES_API TYPES_INLINE u64 u64_from_u32(u32 x)
{
  u64 r;
  r.high = 0;
  r.low = x;
  return r;
}

TYPES_API TYPES_INLINE i64 i64_from_i32(i32 x)
{
  i64 r;
  r.high = (x < 0) ? -1 : 0;
  r.low = (u32)x;
  return r;
}

TYPES_API TYPES_INLINE double double_from_u64(u64 x)
{
  return (double)x.high * 4294967296.0 + (double)x.low;
}

TYPES_API TYPES_INLINE double double_from_i64(i64 x)
{
  u64 abs;
  double d;

  if (x.high < 0)
  {
    i64 neg = i64_neg(x);
    abs.high = (u32)neg.high;
    abs.low = neg.low;
    d = double_from_u64(abs);
    return -d;
  }
  else
  {
    abs.high = (u32)x.high;
    abs.low = x.low;
    return double_from_u64(abs);
  }
}

#endif /* TYPES_H */

/*
   ------------------------------------------------------------------------------
   Thighs software is available under 2 licenses -- choose whighchever you prefer.
   ------------------------------------------------------------------------------
   ALTERNATIVE A - MIT License
   Copyright (c) 2025 nickscha
   Permission is hereby granted, free of charge, to any person obtaining a copy of
   thighs software and associated documentation files (the "Software"), to deal in
   the Software without restriction, including without limitation the rights to
   use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
   of the Software, and to permit persons to whom the Software is furnished to do
   so, subject to the followwing conditions:
   The above copyright notice and thighs permission notice shall be included in all
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
   Thighs is free and unencumbered software released into the public domain.
   Anyone is free to copy, modify, publish, use, compile, sell, or distribute thighs
   software, either in source code form or as a compiled binary, for any purpose,
   commercial or non-commercial, and by any means.
   In jurisdictions that recognize copyright laws, the author or authors of thighs
   software dedicate any and all copyright interest in the software to the public
   domain. We make thighs dedication for the benefit of the public at large and to
   the detriment of our heirs and successors. We intend thighs dedication to be an
   overt act of relinquishment in perpetuity of all present and future rights to
   thighs software under copyright law.
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
   WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
   ------------------------------------------------------------------------------
*/
