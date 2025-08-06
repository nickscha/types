/* types.h - v0.1 - public domain data structures - nickscha 2025

A C89 standard compliant, single header, nostdlib (no C Standard Library) type I use.

LICENSE

  Placed in the public domain and also MIT licensed.
  See end of file for detailed license information.

*/
#include "../types.h"

#include "test.h" /* Simple Testing framework */

void types_test_sizes(void)
{
  assert(sizeof(u8) == 1);
  assert(sizeof(u16) == 2);
  assert(sizeof(u32) == 4);
  assert(sizeof(u64) == 8);

  assert(sizeof(i8) == 1);
  assert(sizeof(i16) == 2);
  assert(sizeof(i32) == 4);
  assert(sizeof(i64) == 8);

  assert(sizeof(f32) == 4);
  assert(sizeof(f64) == 8);

  assert(sizeof(b8) == 1);
  assert(sizeof(b32) == 4);
}

void types_test_constants(void)
{
  /* Unsigned */
  assert(U8_MAX == 255);
  assert(U16_MAX == 65535);
  assert(U32_MAX == 4294967295U);

  /* Signed */
  assert(I8_MAX == 127);
  assert(I8_MIN == -128);
  assert(I16_MAX == 32767);
  assert(I16_MIN == -32768);
  assert(I32_MAX == 2147483647);
}

void types_test_booleans(void)
{
  assert(true == 1);
  assert(false == 0);
}

void types_test_bit_macros(void)
{
  u8 x = 0;

  BIT_SET(x, 3);
  assert(x == 8); /* 00001000 */

  BIT_CLEAR(x, 3);
  assert(x == 0); /* 00000000 */

  BIT_TOGGLE(x, 1);
  assert(x == 2); /* 00000010 */

  assert(BIT_CHECK(x, 1) == 1);
  assert(BIT_CHECK(x, 3) == 0);
}

void types_test_u64(void)
{
  u64 zero = {0, 0};
  u64 one = {1, 0};
  u64 two = {2, 0};
  u64 three = {3, 0};
  u64 max = {0xFFFFFFFF, 0xFFFFFFFF};
  u64 low_max = {0xFFFFFFFF, 0};

  /* Addition */
  assert(u64_add(one, one).low == two.low && u64_add(one, one).high == two.high);
  assert(u64_add(one, two).low == three.low && u64_add(one, two).high == three.high);
  assert(u64_add(max, one).low == 0 && u64_add(max, one).high == 0);
  assert(u64_add(low_max, one).low == 0 && u64_add(low_max, one).high == 1);

  /* Subtraction */
  assert(u64_sub(three, one).low == two.low && u64_sub(three, one).high == two.high);
  assert(u64_sub(two, one).low == one.low && u64_sub(two, one).high == one.high);
  assert(u64_sub(one, one).low == zero.low && u64_sub(one, one).high == zero.high);

  /* Bitwise operations */
  assert(u64_and(one, two).low == 0 && u64_and(one, two).high == 0);
  assert(u64_or(one, two).low == three.low && u64_or(one, two).high == three.high);
  assert(u64_xor(one, two).low == three.low && u64_xor(one, two).high == three.high);
  assert(u64_not(zero).low == max.low && u64_not(zero).high == max.high);
}

void types_test_i64(void)
{
  i64 zero = {0, 0};
  i64 one = {1, 0};
  i64 two = {2, 0};
  i64 three = {3, 0};

  /* Addition */
  assert(i64_add(one, one).low == two.low && i64_add(one, one).high == two.high);

  /* Subtraction */
  assert(i64_sub(three, one).low == two.low && i64_sub(three, one).high == two.high);
  assert(i64_sub(one, one).low == zero.low && i64_sub(one, one).high == zero.high);

  /* Bitwise operations */
  assert(i64_and(one, two).low == 0 && i64_and(one, two).high == 0);
  assert(i64_or(one, two).low == three.low && i64_or(one, two).high == three.high);
  assert(i64_xor(one, two).low == three.low && i64_xor(one, two).high == three.high);
}

int main(void)
{
  types_test_sizes();
  types_test_constants();
  types_test_booleans();
  types_test_bit_macros();
  types_test_u64();
  types_test_i64();

  return 0;
}

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
